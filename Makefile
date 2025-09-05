CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = main.c data_init.c utils_functions.c routine.c data_checker.c death_flag.c
OBJ = $(SRCS:.c=.o)
TARGET = philo

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re