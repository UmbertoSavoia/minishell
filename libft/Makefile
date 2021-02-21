NAME = libft.a
HEADER = libft.h
CFLAGS = -Wall -Wextra -Werror
AR = ar -rc
RM = rm -f

BSRCS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
		ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
SRCS = $(filter-out $(BSRCS), $(wildcard *.c))
OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(AR) $@ $^

bonus: $(BOBJS) $(OBJS)
		$(AR) $(NAME) $^

%.o: %.c $(HEADER)
		gcc $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(OBJS) $(BOBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all
