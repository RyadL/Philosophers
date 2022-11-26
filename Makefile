# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlanani <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/24 16:37:11 by rlanani           #+#    #+#              #
#    Updated: 2022/06/24 16:37:12 by rlanani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

HEADER = philo.h

SRCS = philo.c\
       creation_list.c\
       creation_mutex.c\
	   creation_threads.c\
	   file.c\
	   utils.c\
	   utils2.c\
	   file2.c\
	   
OBJS = $(SRCS:.c=.o)

RM = rm -f

CFLAGS = -Wall -Wextra -Werror 

all : $(NAME) 

$(NAME) :$(OBJS)
	gcc -pthread -g $(SRCS) $(CFLAGS) ${HEADER} -o $(NAME)

.c.o:
	gcc ${CFLAGS} -c $< -o ${<:.c=.o}

clean : 
	$(RM) $(OBJS)
	
fclean : 
	$(RM) $(OBJS) $(NAME)

re : fclean all

.PHONY: fclean re all clean
