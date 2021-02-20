NAME = libft.a
INC = .
CC = gcc 
CFLAGS = -Wall -Wextra -Werror
ARC = ar rcs 
OUTPUT = a.out

PRINTF_SRCS = $(wildcard print/printf/*.c)
GNL_SRCS = $(wildcard print/get_next_line/*.c)

SRCS = $(wildcard convert/*.c) \
	   $(wildcard is/*.c) \
	   $(wildcard lst/*.c) \
	   $(wildcard mem/*.c) \
	   $(wildcard print/*.c) \
	   $(wildcard str/*.c) \
	   $(PRINTF_SRCS) \
	   $(GNL_SRCS)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(ARC) $(NAME) $(OBJS)

%.o:%.c $(INC)
	@$(CC) $(CFLAGS) -I./$(INC) -o $@ -c $< 

clean:
	@echo "Cleaning libft"
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME) a.out

re: fclean
	@echo "Recompliling libft"
	@make all

.PHONY: clean fclean all re
