##
## EPITECH PROJECT, 2019
## project name
## File description:
## Makefile
##

#################
SHELL			=	/bin/bash
RM				=	-@rm -rf
BUILD_DIR		=	.build
BIN				=	chip8
#################

# Main Rules
all:	$(BIN)
$(BIN):
	@mkdir -p $(BUILD_DIR)
	@cmake $(OPTIONS) -B $(BUILD_DIR)
	@make --no-print-directory -C $(BUILD_DIR)
	@mv $(BUILD_DIR)/$(BIN) .
#	@make -j `nproc` --no-print-directory -C $(BUILD_DIR)

debug: OPTIONS	+=	-DUSE_DEBUG=ON
debug:	all
# [END] Main Rules


# Clean Rules
clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(BIN)
# [END] Clean Rules

# Misc
re:	fclean all
.PHONY: re fclean clean all debug $(BIN)
.DEFAULT: all
# [END] Misc
