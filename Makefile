# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpuiu <cpuiu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/28 12:47:45 by cpuiu             #+#    #+#              #
#    Updated: 2024/02/20 11:00:19 by cpuiu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I./Libft -I./include -g -pthread

LIBFTDIR = ./Libft
LIBFT = $(LIBFTDIR)/libft.a 
LIBFT_PATH = ./Libft

OBJSDIR = objs

SRCSDIR = srcs

INCLUDES = philos.h $(LIBFT_PATH)/libft.h

PHILO_MAIN = $(SRCSDIR)/main.c
OBJ_PIPEX_MAIN = $(OBJSDIR)/main.o
SRC_FILES = $(SRCSDIR)/errors.c $(SRCSDIR)/initializing.c $(SRCSDIR)/new_atoi.c $(SRCSDIR)/monitoring.c $(SRCSDIR)/routine.c $(SRCSDIR)/thread.c
OBJ_FILES = $(OBJSDIR)/errors.o $(OBJSDIR)/initializing.o $(OBJSDIR)/new_atoi.o $(OBJSDIR)/monitoring.o $(OBJSDIR)/routine.o $(OBJSDIR)/thread.o

NAME = philo

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c $(INCLUDES) | $(OBJSDIR)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_FILES) $(OBJ_PIPEX_MAIN) $(LIBFT)
		$(CC) $(CFLAGS) $^ -o $@ -L$(LIBFTDIR) -lft

$(LIBFT):
	make -C $(LIBFTDIR) && make clean -C $(LIBFTDIR)

all: $(NAME)

clean:
	$(RM) -r $(OBJSDIR) $(OBJSDIR_BONUS)

fclean: clean
		$(RM) $(NAME)
		make fclean -C $(LIBFTDIR)

re: fclean all

$(OBJSDIR):
	mkdir -p $(OBJSDIR)

.PHONY: all clean fclean re
