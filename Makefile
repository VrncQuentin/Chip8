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
PINSTR			=	instructions
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

INSTR			=\
	equality.c		\
	flow.c			\
	math_logic.c	\

SRCS			=\
	initChip8.c		\
	runChip8.c		\
	dumpChip8.c		\
	instructions.c	\
	drawScreen.c	\

SRC				=\
	$(addprefix $(PINSTR)/, $(INSTR))	\
	$(addprefix $(PSRC)/, $(SRCS))		\
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
	$(CC) $(OBJ) -o $(BIN) $(LDFLAGS)

debug:	CPPFLAGS += -DSCREEN
debug:	CFLAGS += -g3
debug:	all
# [END] Main Rules


# Conversion Rules
%.o:	%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
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
