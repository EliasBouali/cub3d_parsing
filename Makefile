NAME    := cub3d
CC      := cc
CFLAGS  := -Wall -Wextra -Werror
INCS    := -Iinclude

SRCS    := src/file/file_validation.c \
           src/file/read_file.c \
           src/file/split_lines.c \
           src/parse/parse_headers.c \
					 src/parse/parse_map_block.c \
           src/utils/second_utils.c \
           src/utils/utils.c \
           src/main.c

OBJS    := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCS) $(OBJS) -o $(NAME)

# Règle générique .c → .o
%.o: %.c include/cubd3.h
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
