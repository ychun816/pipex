# Colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
CYAN=\033[1;36m
MAGENTA = \033[0;35m
NC = \033[0m

#LIBFT
NAME = libft.a

SRC = \
	nbr/ft_atoi.c \
	nbr/ft_itoa.c \
	nbr/ft_putnbr_fd.c \
	\
	str/ft_putstr_fd.c \
	str/ft_split.c \
	str/ft_strchr.c \
	str/ft_strdup.c \
	str/ft_striteri.c \
	str/ft_strjoin.c \
	str/ft_strlcat.c \
	str/ft_strlcpy.c \
	str/ft_strlen.c \
	str/ft_strmapi.c \
	str/ft_strncmp.c \
	str/ft_strnstr.c \
	str/ft_strrchr.c \
	str/ft_strtrim.c \
	str/ft_substr.c \
	str/ft_tolower.c \
	str/ft_toupper.c \
	str/ft_bzero.c \
	str/ft_putchar_fd.c \
	str/ft_putendl_fd.c \
	\
	other/ft_calloc.c \
	\
	is/ft_isalnum.c \
	is/ft_isalpha.c \
	is/ft_isascii.c \
	is/ft_isdigit.c \
	is/ft_isprint.c \
	\
	mem/ft_memchr.c \
	mem/ft_memcmp.c \
	mem/ft_memcpy.c \
	mem/ft_memmove.c \
	mem/ft_memset.c \
	\
	lst/ft_lstnew.c \
	lst/ft_lstadd_front.c \
	lst/ft_lstsize.c \
	lst/ft_lstlast.c \
	lst/ft_lstadd_back.c \
	lst/ft_lstdelone.c \
	lst/ft_lstclear.c \
	lst/ft_lstiter.c \
	lst/ft_lstmap.c \
	\
	gnl/get_next_line_bonus.c \
	gnl/get_next_line_utils.c \
	gnl/get_next_line.c \
	\
	printf/ft_printf_base.c \
	printf/ft_printf_hexa.c \
	printf/ft_printf_ptr.c \
	printf/ft_printf_tools.c \
	printf/ft_printf_unsigned.c \
	printf/ft_printf.c \

OBJS = ${SRC:.c=.o}

#FLAGS
CC = cc
CFLAGS = -Wall -Wextra -Werror

.c.o:
	@${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}
	@echo "$(CYAN)Compiled $<$(NC)"

$(NAME): $(OBJS)
	@ar rcs ${NAME} ${OBJS}
	@echo "$(GREEN)Successful compilation of $(MAGENTA)libft$(NC)"

all: $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re