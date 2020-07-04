#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int chip8(const char *const file);

__attribute__((noreturn))
static void help(const char *const bin, const int code)
{
    static const char _help[] = "\
DESCRIPTION:\n\
\t%s is an interpreter for chip8 programs.\n\n\
USAGE: %s prog\n\
\tprog\tis the Chip-8 program you wanna interpret.\n";

    fprintf(!code ? stdout : stderr, _help, bin, bin);
    exit(code);
}

static void check_help(const char *const arg, const char *const bin)
{
    static const char *const helps[3] = {"-h", "-help", "--help"};

    for (int i = 0; i != 3; i += 1)
        if (!strcmp(arg, helps[i]))
            help(bin, 0);
}

static int check_args(int ac, char *av[])
{
    for (int i = 1; av[i]; i += 1)
        check_help(av[i], *av);
    if (ac != 2)
        return 1;
    return access(av[1], R_OK);
}

int main(int ac, char *av[])
{
    if (check_args(ac, av))
        help(*av, 84);
    return chip8(av[1]);
}
