NAME = client
CC = gcc
RM = rm -rf
CFLAGS=	-Wall -Wextra -Werror
LIBFT= ./libft/libft.a

SRV = ./Server/server.c
CLIE = ./Client/client.c

OBJS = (SRV:%.c=%.o)
OBJC = (SRV:%.c=%.o)



all:
	@make clean -C libft
	@make -C libft
	@$(CC) $(CFLAGS) $(SRV) $(LIBFT) -o ./Server/srv
	@$(CC) $(CFLAGS) $(CLIE) $(LIBFT) -o ./Client/cli

clean:
	@make clean -C libft

fclean:
	@make fclean -C libft
	@$(RM) ./Server/srv 
	@$(RM) ./Client/cli