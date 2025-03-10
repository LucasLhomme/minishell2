##
## EPITECH PROJECT, 2024
## Makefile Root
## File description:
## MakeFile dans le fichier root
##

NAME = mysh
DEBUG = -g
CFLAGS += -g -Wall -Wextra -W -Iinclude -Isrc/lib/include

SRC =	./src/main.c\
./src/execute_command.c\
./src/shell.c\
./src/command_cd.c\
./src/command_env.c\
./src/setenv.c\
./src/unsetenv.c\

OBJ  	=	 $(SRC:.c=.o)
LIBMY = libmy.a

all: 	$(NAME)

$(NAME):	$(OBJ) $(LIBMY)
		gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LIBMY)

$(LIBMY):
		$(MAKE) -C src/lib all

clean:
		$(MAKE) -C src/lib clean
		rm -f $(OBJ)
		rm -f $(LIBMY)

fclean: clean
		rm -f $(NAME) debug $(OBJ) $(LIBMY)

re:
		$(MAKE) fclean
		$(MAKE) all

debug: 	$(DEBUG)

$(DEBUG):	$(OBJ) $(LIBMY)
		gcc -g $(CFLAGS) -o debug $(OBJ) $(LIBMY)

redebug:
		$(MAKE) fclean
		$(MAKE) debug
