NAME = client
CC = gcc
RM = rm -rf
CFLAGS=	-Wall -Wextra -Werror
LIBFT= ./libft/libft.a

SRV = ./Server/ft_server.c
CLIE = ./Client/ft_client.c

OBJS = (SRV:%.c=%.o)
OBJC = (SRV:%.c=%.o)



all:
	@make clean -C libft
	@make -C libft
	@$(CC) $(CFLAGS) $(SRV) $(LIBFT) -o ./Server/server
	@$(CC) $(CFLAGS) $(CLIE) $(LIBFT) -o ./Client/client

clean:
	@make clean -C libft

fclean:
	@make fclean -C libft
	@$(RM) ./Server/server 
	@$(RM) ./Client/client