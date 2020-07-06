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
PBUILD			=	.build
PBIN			=	/usr/bin
#################

# Names.
#################
C8VM			=	c8vm
C8C				=	c8c
#################


# Main Rules
.DEFAULT: build
build: setup-build
	-@cmake $(OPTIONS) -B $(PBUILD)
	$(MAKE) --no-print-directory -C $(PBUILD)

debug: fclean
debug: OPTIONS += -DUSE_DEBUG=ON
debug: .DEFAULT

release: fclean
release: OPTIONS += -DUSE_PROD=ON
release: .DEFAULT

install: release
	@echo -e "$(CYAN)Moving $(BIN) to $(PBIN) (requires sudo)$(RESET)"
	@sudo mv $(BIN) $(PBIN)

uninstall:
	@echo -e "$(CYAN)Removing $(BIN) from $(PBIN) (requires sudo)$(RESET)"
	@sudo rm $(PBIN)/$(BIN)
# [END] Main Rules

# Clean Rules
clean:
	$(RM) $(PBUILD)

fclean: clean
	$(RM) $(C8VM) $(C8C)
# [END] Clean Rules

# Misc
re:	fclean
re: .DEFAULT

setup-build:
	-@mkdir -p $(PBUILD)

.PHONY: build debug release install uninstall clean fclean re setup-build
# [END] Misc
