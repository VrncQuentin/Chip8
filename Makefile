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

#Flags.
#################
CPPFLAGS		+=	-iquote $(PINC)
CFLAGS			+=	-Wall -Wextra -Wshadow
LDFLAGS			+=
#################


# Source Files.
#################
MAIN			=	main.c

SRCS			=\
	initChip8.c		\
	runChip8.c		\
	instructions.c	\

SRC				=\
	$(addprefix $(PSRC)/, $(SRCS))	\
	$(MAIN)
#################


# Conversions to .o.
#################
OBJ				=	$(SRC:.c=.o)
#################

# Names.
#################
BIN				=	c8i
#################

# Main Rules
all:	$(BIN)
$(BIN):	$(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LDFLAGS) -g3

debug:	CFLAGS += -g3
debug:	all
# [END] Main Rules


# Conversion Rules
%.o:	%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -g3 -c $< -o $@
#[END] Conversion Rules

# Clean Rules
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(BIN)
# [END] Clean Rules

# Misc
re:	fclean all
.PHONY: re fclean clean all debug
# [END] Misc
