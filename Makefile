# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/20 13:35:59 by earnaud           #+#    #+#              #
#    Updated: 2022/01/09 16:10:58 by earnaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		:= main.cpp
HEADER		:= vector.hpp \
				iterator.hpp \
				reverse_iterator.hpp \
				stack.hpp \
				iterator_traits.hpp

OBJS		:= $(SRCS:.cpp=.o)
NAME		:= container
CC			:= clang++
CFLAGS		:= -Wall -Wextra -Werror -std=c++98 -g -fstandalone-debug
%.o:		%.cpp $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			$(RM) $(OBJS)
		
fclean:		clean
			$(RM) $(NAME)

re:			fclean all
