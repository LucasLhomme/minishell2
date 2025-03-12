##
## EPITECH PROJECT, 2025
## B-CPE-200-LIL-2-1-robotfactory-lucas.lhomme
## File description:
## Makefile
##

# Colors
RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
ORANGE=\033[1;33m
NC=\033[0m # No Color

# Variables
NAME = mysh
CFLAGS = -g -Wall -Wextra -W -Iinclude -Ilib/include -fdiagnostics-color=always
SRC =	./src/main.c\
		./src/shell/shell.c\
		./src/commands/execute_command.c\
		./src/commands/cd/command_cd.c\
		./src/commands/env/command_env.c\
		./src/commands/env/setenv.c\
		./src/commands/env/unsetenv.c\

OBJ = $(SRC:.c=.o)
LIBMY = libmy.a

# Temporary file to store errors and warnings
ERRORS_FILE = .make_errors_warnings

# Default target
all: $(LIBMY) $(NAME)
	@if [ -f $(ERRORS_FILE) ]; then \
		ERRORS=$$(grep -c "error:" $(ERRORS_FILE)); \
		WARNINGS=$$(grep -c "warning:" $(ERRORS_FILE)); \
		rm -f $(ERRORS_FILE); \
		if [ $$ERRORS -eq 0 ] && [ $$WARNINGS -eq 0 ]; then \
			echo "$(GREEN)Build successful!$(NC)"; \
			echo "$(ORANGE)"; \
			echo "                                     @@@@@@@@@@@@  @@@@@@@@@@@@"; \
			echo "                                   @@@@@@@@@@@@@@  @@@@@@@@@@@@@@"; \
			echo "                                 @@@@@@@@@@@@@@@    @@@@@@@@@@@@@@@"; \
			echo "                               @@@@@@@@@@@@@@@        @@@@@@@@@@@@@@@"; \
			echo "                              @@@@@@@@@@@@@@            @@@@@@@@@@@@@@"; \
			echo "                             @@@@@@@@@@@@@                @@@@@@@@@@@@@"; \
			echo "                      @@     @@@@@@@@@@                      @@@@@@@@@@     @@"; \
			echo "                      @@     @@@@@@@@@     @@@@@@@@@@@@@@     @@@@@@@@@     @@"; \
			echo "                      @@@     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@@@@@@     @@@"; \
			echo "                      @@@@     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@     @@@@"; \
			echo "                       @@@@@    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    @@@@@"; \
			echo "                         @@@@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@@@@@"; \
			echo "                           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"; \
			echo "                     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"; \
			echo "                    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"; \
			echo "                  @@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   @@@"; \
			echo "                  @@  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@"; \
			echo "                  @  @@@@@      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@      @@@@@  @"; \
			echo "                    @@@        @@@@@@@@@@@@@     @@     @@@@@@@@@@@@@        @@@"; \
			echo "                    @@        @@@@@                              @@@@@        @@"; \
			echo "                    @        @@@@@@                              @@@@@@        @"; \
			echo "                             @@@@@@@@@                        @@@@@@@@@"; \
			echo "                              @@@@@@@@                        @@@@@@@@"; \
			echo "                               @@@@@@@@                      @@@@@@@@"; \
			echo "                                  @@@@                        @@@@"; \
			echo "$(NC)"; \
		elif [ $$ERRORS -eq 0 ]; then \
			echo "$(ORANGE)Build successful but with $(MAGENTA)$$WARNINGS warnings!$(NC)"; \
		else \
			echo "$(RED)Build Failed!!!!$(NC): $(MAGENTA)Warnings: $$WARNINGS$(NC) $(RED)Errors: $$ERRORS$(NC)"; \
		fi; \
	else \
		echo "$(GREEN)Build successful!$(NC)"; \
	fi

# Compilation de l'exécutable principal
$(NAME): $(OBJ)
	@echo "$(YELLOW)Building $@...$(NC)"
	@OUTPUT=$$(gcc $(CFLAGS) -o $@ $^ $(LIBMY) 2>&1); \
	echo "$$OUTPUT" >> $(ERRORS_FILE); \
	ERRORS=$$(echo "$$OUTPUT" | grep -c "error:"); \
	WARNINGS=$$(echo "$$OUTPUT" | grep -c "warning:"); \
	if [ $$ERRORS -ne 0 ] || [ $$WARNINGS -ne 0 ]; then \
		echo "$$OUTPUT"; \
	fi;

# Compilation des fichiers objets
%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@OUTPUT=$$($(CC) $(CFLAGS) -c $< -o $@ 2>&1); \
	echo "$$OUTPUT" >> $(ERRORS_FILE); \
	ERRORS=$$(echo "$$OUTPUT" | grep -c "error:"); \
	WARNINGS=$$(echo "$$OUTPUT" | grep -c "warning:"); \
	if [ $$ERRORS -ne 0 ] || [ $$WARNINGS -ne 0 ]; then \
		echo "$$OUTPUT"; \
	fi;

# Compilation de la bibliothèque
$(LIBMY):
	@echo "$(BLUE)Building library...$(NC)"
	@$(MAKE) --no-print-directory -C lib all

# Nettoyage des fichiers objets et temporaires
clean:
	@echo "$(RED)Cleaning up...$(NC)"
	@$(MAKE) --no-print-directory -C lib clean
	@rm -f $(OBJ)
	@rm -f $(ERRORS_FILE)

# Nettoyage complet
fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBMY)

# Rebuild tout
re: fclean all

# Mode debug
debug: CFLAGS += -g
debug: $(NAME)

# Rebuild en mode debug
redebug: fclean debug

# Phony targets
.PHONY: all clean fclean re debug redebug