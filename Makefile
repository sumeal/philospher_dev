NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

FILES = main.c \
		activities.c \
		init.c \
		libft.c \
		parsing.c \
		routine.c \
		utils.c

OFILES = $(FILES: .c=.o)

$(NAME) : $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

%.0: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all : $(NAME)

clean:
	rm -f $(OFILES)

fclean:
	rm -f $(NAME)

re: fclean all

me:
	$(MAKE) fclean
	$(MAKE) all
	$(MAKE) clean

.PHONY: all clean fclean re me
