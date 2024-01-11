# Makefile

CC = cc
CFLAGS = -Wextra -Wall -Werror
PRINTF = ./printf/libftprintf.a
NAME = Minitalk

all : $(NAME)

$(NAME) : printff server client

server : server.c
	$(CC) $(CFLAGS) $< -o $@ $(PRINTF)

client : client.c
	$(CC) $(CFLAGS) $< -o $@ $(PRINTF)

bonus : printff bserver bclient

bserver : server_bonus.c
	$(CC) $(CFLAGS) $< -o $@ $(PRINTF)

bclient : client_bonus.c
	$(CC) $(CFLAGS) $< -o $@ $(PRINTF)

printff :
	make -C ./printf

clean:
	rm -f server client bserver bclient
	make -C ./printf clean

fclean : clean
	make -C ./printf fclean