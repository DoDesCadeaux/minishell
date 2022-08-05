# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/05 15:00:54 by pamartin          #+#    #+#              #
#    Updated: 2022/08/05 15:00:57 by pamartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= 	minishell

### DIRECTORY
HEADER			=	./include/
SOURCE			=	./src/
OBJ_TMP			=	./obj/

### FILES
SRC 			= 	main.c prototype_main.c parsing.c clone_envp.c echo.c envp.c get_path.c utils_envp.c work_directory.c
OBJ				= 	$(addprefix $(OBJ_TMP), $(SRC:%.c=%.o))
$(OBJ_TMP)%.o	:	$(SOURCE)%.c
##						$(CC) $(FLAGS) -c $< -o $@ $(INCLUDE)
						$(CC)  -c $< -o $@ $(INCLUDE)


### COMMANDS
CC				=	gcc
FLAGS			=	-Wall -Wextra -Werror -fsanitize=address
LIB 			= 	./libft/libft.a
INCLUDE			= 	-I $(HEADER)
RM				=	rm -rf
MAKE 			= 	make

### NAME
$(NAME)			:	$(OBJ_TMP) $(OBJ)
	$(MAKE) -C Libft
#	$(CC) $(FLAGS) $(INCLUDE) $(LIB) -o $(NAME) $(OBJ)
	$(CC)  $(INCLUDE) $(LIB) -lreadline -o $(NAME) $(OBJ)

$(OBJ_TMP)		:	
	mkdir -p $(OBJ_TMP)	

### RULES
all 		: $(NAME)

clean		:
	$(RM) $(OBJ)
	$(MAKE) clean -C libft

fclean		:		clean
	$(RM) $(NAME)
	$(MAKE) fclean -C libft

re			:		fclean all
