##
## Makefile for abstract in /home/dellam_a/Projet/AbstractVM
##
## Made by
## Login   <dellam_a@epitech.net>
##
## Started on  Mon Feb 10 15:22:39 2014
## Last update Fri Feb 21 18:09:34 2014 
##

SRC=		FactoryIOperand.cpp \
		Exception.cpp \
		Cpu.cpp \
		Chipset.cpp \
		main.cpp

OBJS=		$(SRC:.cpp=.o)

CC=		g++

CXXFLAGS=	-Wall -Wextra -Werror -g

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
