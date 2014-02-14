##
## Makefile for abstract in /home/dellam_a/Projet/AbstractVM
##
## Made by
## Login   <dellam_a@epitech.net>
##
## Started on  Mon Feb 10 15:22:39 2014
## Last update Fri Feb 14 10:11:01 2014 
##

SRC=		Operand.cpp \
		Exception.cpp \
		VMachine.cpp \
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
