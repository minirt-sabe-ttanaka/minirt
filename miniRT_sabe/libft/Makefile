# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabe <sabe@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/09 15:06:46 by sabe              #+#    #+#              #
#    Updated: 2025/03/23 14:50:52 by sabe             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRCS = ft_memcpy.c	ft_strlcat.c ft_atoi.c	ft_memmove.c	ft_strlcpy.c ft_bzero.c	ft_memset.c	ft_strlen.c ft_calloc.c	ft_putchar_fd.c	ft_strmapi.c ft_isalnum.c	ft_putendl_fd.c	ft_strncmp.c ft_isalpha.c	ft_putnbr_fd.c	ft_strnstr.c ft_isascii.c	ft_putstr_fd.c	ft_strrchr.c ft_isdigit.c	ft_split.c	ft_strtrim.c ft_isprint.c	ft_strchr.c	ft_substr.c ft_itoa.c	ft_strdup.c	ft_tolower.c ft_memchr.c	ft_striteri.c	ft_toupper.c ft_memcmp.c	ft_strjoin.c
SRCS_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
INCLUDES = -I.

ifdef WITH_BONUS
OBJS += $(OBJS_BONUS)
endif

$(NAME) :	$(OBJS)
	ar rc $@ $^

all : $(NAME)

bonus:
	make WITH_BONUS=1

%.o:%.c
	$(CC) -c  $(CFLAGS) $^ -o $@ $(INCLUDES)

clean :
	rm -f $(OBJS) $(OBJS_BONUS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
