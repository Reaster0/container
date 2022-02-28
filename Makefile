# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/20 13:35:59 by earnaud           #+#    #+#              #
#    Updated: 2022/02/26 20:09:21 by earnaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		:= main.cpp

OBJS		:= $(SRCS:.cpp=.o)
DEP			:= $(SRCS:.cpp=.d)
NAME		:= container
CXX			:= clang++
CXXFLAGS	:= -std=c++98 -g3 -fstandalone-debug -MMD -MP -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
			$(RM) $(OBJS) $(DEP)
		
fclean:		clean
			$(RM) $(NAME)

re:			fclean all

-include $(DEP)