# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aeryilma <aeryilma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 01:30:29 by aeryilma          #+#    #+#              #
#    Updated: 2022/12/29 01:30:45 by aeryilma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = $(INCLUDE) -Wall -Werror -Wextra
INCLUDE = -IInclude/
CC = gcc

# LDFLAGS="-L/opt/homebrew/opt/readline/lib"
# CPPFLAGS="-I/opt/homebrew/opt/readline/include"

SRC = $(shell find src -name "*.c")
SRCDIR = $(sort $(dir $(SRC)))
SRCFLS = $(notdir $(SRC))

OUTPREFIX = builds/
OBJ = $(addprefix $(OUTPREFIX), $(SRCFLS:.c=.o))

vpath %.c $(SRCDIR)
$(OUTPREFIX)%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: outfolder $(NAME)
	@echo "Done"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline -Ireadline -L$(LDFLAGS) -I$(CPPFLAGS)

outfolder:
	@echo "Building Minishell"
	@if [ ! -d $(OUTPREFIX) ]; then echo "$(OUTPREFIX) folder created."; fi
	@mkdir -p $(OUTPREFIX);
	@echo "Compiling Files..."

clean:
	@echo "Cleaning Objects..."
	@if [ -d $(OUTPREFIX) ]; then rm -rf $(OUTPREFIX); fi

fclean: clean
	@echo "Cleaning Program..."
	@if [ ! -d $(NAME) ]; then rm -rf $(NAME); fi
	@echo "Done"

re: fclean seperate all

seperate:
	@echo "-----------------"

.PHONY:
	all clean fclean re seperate

check:
	@echo "SRC : "
	@echo $(SRC)
	@echo "\nSRCDIR : "
	@echo $(SRCDIR)
	@echo "\nSRCFLS : "
	@echo $(SRCFLS)
	@echo "\nOBJ : "
	@echo $(OBJ)