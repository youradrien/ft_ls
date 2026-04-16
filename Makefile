# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: you <you@student.42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/16                               #+#    #+#              #
#    Updated: 2026/04/16                               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = ft_ls
CC = cc
CFLAGS = -Wall -Wextra #-Werror 
# sanitize
CFLAGS += #-fsanitize=address #-fsanitize=undefined

SRC_DIR = src
INC_DIR     = includes
SRCS = $(addprefix $(SRC_DIR)/, \
	main.c \
	utils.c \
	parse.c \
	print.c \
)
OBJS = $(SRCS:.c=.o)

INCLUDES    = -I$(INC_DIR)


# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
