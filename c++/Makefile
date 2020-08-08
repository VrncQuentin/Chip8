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
CC				=	g++-10
MAKE			=	@make
#################

# Paths.
#################
PCOMMON			=	common
PGUI			=	gui
PSUBWIN			=	$(PGUI)/subwins
PINTERP			=	interpreter
#################


#Flags.
#################
CPPFLAGS		=	-iquote .
CFLAGS			=	-Wall -Wextra -Wshadow -std=2a
LDFLAGS			=	-lsfml-graphics -lsfml-window -lsfml-system
#################


# Source Files.
#################
MAIN			=	main.cpp
GUI				=	GUI.cpp
SUBWINS			=\
	ASubwin.cpp	\
	Stats.cpp	\

ALL				=\
	$(addprefix $(PGUI)/, $(GUI))			\
	$(addprefix $(PSUBWIN)/, $(SUBWINS))	\
	$(MAIN)
#################


# Conversions to .o.
#################
OBJ			=	$(ALL:.cpp=.o)
#################

# Names.
#################
BIN				=	chip8
#################

# Main Rules
all:	$(BIN)
$(BIN):	$(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LDFLAGS)

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
