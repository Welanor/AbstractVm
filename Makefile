##
## Makefile for abstract in /home/dellam_a/Projet/AbstractVM
##
## Made by
## Login   <dellam_a@epitech.net>
##
## Started on  Mon Feb 10 15:22:39 2014
## Last update Wed Feb 12 20:12:45 2014 
##

SRC=		Operand.cpp \
		main.cpp

OBJS=		$(SRC:.cpp=.o)

CC=		g++

CXXFLAGS=	-Wall -Wextra -Werror

NAME=		avm

RM= 		rm -f

$(NAME):	$(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean	all
