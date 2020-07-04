##
## EPITECH PROJECT, 2019
## project name
## File description:
## Makefile
##

# Fundamentals.
#################
SHELL			=	/bin/bash
RM				=	-@rm -rf
CC				=	gcc
MAKE			=	@make
#################


# Paths.
#################
PINC			=	include
PSRC			=	src
#################


# Source Files.
#################
MAIN			=	main.c

SRCS			=\
	chip8.c

SRC				=\
	$(addprefix $(PSRC)/, $(SRCS))	\
	$(MAIN)
#################


# Flags.
#################
CPPFLAGS		+=	-iquote $(IP)
CFLAGS			+=	-Wall -Wextra -Wshadow
#################


# Conversions to .o.
#################
OBJ				=	$(SRC:.c=.o)
#################


# Names.
#################
BIN				=	chip-8
#################


# Main Rules
$(BIN):	$(OBJ)
	$(CC) $(OBJ) -o $@

debug:	CFLAGS += -g3 -fanalyzer
debug:	.DEFAULT
# [END] Main Rules


# Conversion Rules
%.o:	%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
#[END] Conversion Rules

# Clean Rules
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(BIN)
# [END] Clean Rules

# Misc
re:	fclean
re: .DEFAULT

.PHONY: re fclean clean debug $(BIN)
.DEFAULT: $(BIN)
# [END] Misc
