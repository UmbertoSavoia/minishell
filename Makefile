NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

MKDIR = mkdir -p
RM = rm -f
RMDIR = rm -rf

SRC_DIR = srcs
OBJ_DIR = objs

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

SRC = $(foreach dir, $(SRC_DIR), $(foreach file, $(wildcard $(dir)/*c), $(notdir $(file))))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

all: $(NAME)

$(OBJ_DIR)/%.o : %.c
	@$(MKDIR) $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "Compiling... %-33.33s\r" $@

$(NAME): $(OBJ)
	@make bonus -C ./libft
	@echo "\033[0;32mCreating        libft.a   \033[0;0m"
	@$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -o $(NAME)
	@echo "\033[0;32mCreating        MINISHELL\033[0;0m"

clean:
	@make clean -C ./libft
	@$(RMDIR) $(OBJ_DIR)
	@echo "\033[0;31mCleaning        folder objs\033[0;0m"

fclean: clean
	@make fclean -C ./libft
	@$(RM) $(NAME)
	@echo "\033[0;31mRemove          MINISHELL\033[0;0m"

re: fclean all
