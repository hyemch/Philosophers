CC 		=	cc
CFLAGS	=	-Wall -Wextra -Werror
# -g3 -fsanitize=thread

NAME	= 	philo

INC_DIR	=	-I ./inc

INC		=	$(INC_DIR)/philo.h

SRC		=	src/main.c \
			src/init.c \
			src/utils.c \
			src/philo.c \
			src/philo_eat.c \
			src/philo_monitoring.c \
			src/philo_utils.c \

OBJ		=	$(SRC:.c=.o)

PHILO	=	-lpthread

RM		=	rm -f

all		:	$(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(NAME)	:	$(OBJ)
	$(CC) $(CFLAGS) $(INC_DIR) $(OBJ) -o $(NAME) $(PHILO)

clean	:
	$(RM) $(OBJ)

fclean	: clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re