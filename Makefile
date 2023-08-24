# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 09:39:09 by alde-fre          #+#    #+#              #
#    Updated: 2023/08/23 12:29:43 by olimarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

# directories
SRCDIR	=	./src
INCDIR	=	./inc
OBJDIR	=	./obj

# src / includes / obj files
SRC		=	logs.c \
			main.c \
			settings.c \
			time_utils.c \
			manager/heartbeats.c \
			manager/manager.c \
			worker/worker.c \

OBJ		= 	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

DEPENDS :=	$(patsubst %.o,%.d,$(OBJ))

CC = cc
RM = rm -rf
MKDIR = mkdir -p

CFLAGS	= -MMD -MP -Wall -Wextra -Werror -g

all: obj $(NAME)

obj:
	$(MKDIR) $(OBJDIR)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $+

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(MKDIR) $(@D)
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEPENDS)

.PHONY: all clean fclean re
