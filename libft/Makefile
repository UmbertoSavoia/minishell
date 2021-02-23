NAME = libft.a
HEADER = libft.h
CFLAGS = -Wall -Wextra -Werror -g
AR = ar -rc
RM = rm -f

BSRCS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
		ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
SRCS = $(filter-out $(BSRCS), $(wildcard *.c))
OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS:.c=.o)

all: $(NAME) bonus

$(NAME): $(OBJS)
		@$(AR) $@ $^

bonus: $(BOBJS) $(OBJS)
		@$(AR) $(NAME) $^
		@printf "Making        libft.a \r"

%.o: %.c $(HEADER)
		@gcc $(CFLAGS) -c $< -o $@
		@printf "Compiling... %-33.33s \r" $@

clean:
		@$(RM) $(OBJS) $(BOBJS)
		@echo "\033[0;31mCleaning        objs\033[0;0m"

fclean: clean
		@$(RM) $(NAME)
		@echo "\033[0;31mCleaning        libft.a\033[0;0m"

re: fclean all
