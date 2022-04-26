NAME = libft.a
HEADER = libft.h
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

C_FILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
		ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
		ft_strlcpy.c ft_strlcat.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
		ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
		get_next_line.c get_next_line_utils.c ft_printf.c ft_printf_utils.c

B_C_FILES = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

ifdef WITH_BONUS
OBJS = $(C_FILES:%.c=%.o) $(B_C_FILES:%.c=%.o)
else
OBJS = $(C_FILES:%.c=%.o)
endif

all: $(NAME)

%.o: %.c $(HEADER)
	@$(CC) -c $(CFLAGS) -o $@ $<

$(NAME): $(OBJS)
	@ar -ru $(NAME) $^

bonus:
	@$(MAKE) WITH_BONUS=1

clean:
	@$(RM) *.o

fclean: clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re bonus