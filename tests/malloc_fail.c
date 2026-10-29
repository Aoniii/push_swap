/*
 * Malloc failure injection, loaded with LD_PRELOAD by the testers.
 *
 * It replaces malloc() and free() of the program to: - make the Nth call to
 * malloc() return NULL (N = $MALLOC_FAIL_AT, 0 or unset = never fail) - count
 * the blocks that are still allocated when the program ends
 *
 * At the end of the program, it writes "<malloc calls> <blocks not freed>" in
 * the file $MALLOC_FAIL_REPORT. If the program crashes, the file is not
 * written, so the tester knows it crashed.
 *
 * Build: cc -shared -fPIC -o malloc_fail.so malloc_fail.c This file is not part
 * of push_swap, it doesn't follow the norm and is not checked by the norminette
 * mode of the testers.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// The real malloc and free of glibc, used to do the actual allocation
extern void *__libc_malloc(size_t size);
extern void __libc_free(void *ptr);

static long calls = 0; // number of malloc() calls so far
static long alive = 0; // blocks allocated and not freed yet
static long fail_at = -1; // -1 = not read from the environment yet

void *malloc(size_t size) {
	void *ptr;

	if (fail_at == -1) {
		// getenv() doesn't allocate, so it's safe to call it from malloc()
		const char *value = getenv("MALLOC_FAIL_AT");
		fail_at = value ? atol(value) : 0;
	}
	calls++;
	if (calls == fail_at)
		return (NULL);
	ptr = __libc_malloc(size);
	if (ptr)
		alive++;
	return (ptr);
}

void free(void *ptr) {
	// free(NULL) does nothing, so it must not be counted
	if (ptr)
		alive--;
	__libc_free(ptr);
}

/*
 * Called automatically when the program ends normally (return from main or
 * exit()), not when it is killed by a signal (segfault, abort...).
 */
__attribute__((destructor)) static void report(void) {
	const char	*path = getenv("MALLOC_FAIL_REPORT");
	char		buffer[64];
	int			fd;
	int			len;

	if (!path)
		return;
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return;
	// snprintf() with only numbers doesn't call malloc()
	len = snprintf(buffer, sizeof(buffer), "%ld %ld\n", calls, alive);
	write(fd, buffer, len);
	close(fd);
}
