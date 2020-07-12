/* Libc */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
/* Project */
#include "interpreter.h"

USE_FONTS_TAB;

static void cl_fd(int *fd)
{
    if (*fd != -1)
        close(*fd);
}

static void initDefaultValues(struct Chip8 *c)
{
    c->memory.beginProg = c->memory.buf + LOAD_ADDR;
    c->memory.fonts = c->memory.buf;
    memcpy(c->memory.fonts, FONTS, sizeof(FONTS));
}

static int loadProgInMem(char const *fp, uint8_t *memory, size_t *sz)
{
    struct stat st = {0};
    __attribute__((cleanup(cl_fd)))int fd = open(fp, O_RDONLY);

    if (fd == -1)
        return 1;
    fstat(fd, &st);
    if (st.st_size > MEMORY_SIZE - LOAD_ADDR)
        return 1;
    if (read(fd, memory, st.st_size) == -1)
        return 1;
    *sz = st.st_size;
    return 0;
}

int initChip8(struct Chip8 *c, char const *fp)
{
    initDefaultValues(c);
    if (loadProgInMem(fp, c->memory.beginProg, &c->memory.progSize))
        return 1;
    return 0;
}
