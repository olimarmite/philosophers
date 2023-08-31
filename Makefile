# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 09:39:09 by alde-fre          #+#    #+#              #
#    Updated: 2023/08/30 18:58:58 by olimarti         ###   ########.fr        #
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
			manager/heartbeats.c \
			manager/manager.c \
			manager/manager_init.c \
			manager/manager_destroy.c \
			worker/worker.c \
			worker/shared_ressources.c \
			utils/time_utils.c \
			utils/ft_atoi.c \
			utils/mutex_getter_setter.c \
			worker/philo_logic.c \
			worker/philo_forks_utils.c \
			worker/philo_state_utils.c \
			worker/philo_starting_utils.c \

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
