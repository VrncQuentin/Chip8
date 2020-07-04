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

# Colors.
#################
RESET			=	\033[0m
CYAN			=	\033[1;94m
#################

# Paths.
#################
PINC			=	include
PSRC			=	src
PBIN			=	/usr/bin
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
CPPFLAGS		+=	-iquote $(PINC)
CFLAGS			+=	-Wall -Wextra -Wshadow
PROD_FLAGS		=	-O2 -march=native
DEBUG_FLAGS		=	-g3 -fanalyzer
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
.DEFAULT: build

$(BIN):	$(OBJ)
	$(CC) $(OBJ) -o $@

debug:	fclean
debug:	CFLAGS += $(DEBUG_FLAGS)
debug:	$(BIN)

build:	fclean
build:	CFLAGS += $(PROD_FLAGS)
build:	$(BIN)

install: .DEFAULT
	@echo -e "$(CYAN)Moving $(BIN) to $(PBIN) (requires sudo)$(RESET)"
	@sudo mv $(BIN) $(PBIN)

uninstall:
	@echo -e "$(CYAN)Removing $(BIN) from $(PBIN) (requires sudo)$(RESET)"
	@sudo rm $(PBIN)/$(BIN)
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

.PHONY: re fclean clean debug build install $(BIN)
# [END] Misc
