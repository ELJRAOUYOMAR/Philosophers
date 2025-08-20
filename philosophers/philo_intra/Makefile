NAME	=	philo
CC		=   cc
RM		=	rm -rf
CFLAGS  =	-Wall -Wextra -Werror

SOURCE_FILES =	philo.c			\
				init.c			\
				controller.c	\
				examination.c	\
				philo_routines.c	\
				time.c			\
				utils.c			\
				clean_up.c		\
		
SRCS 	=	${SOURCE_FILES}

OBJS	=	${SRCS:.c=.o}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re 

.SECONDARY: $(OBJS)