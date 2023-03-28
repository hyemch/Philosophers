CC 		=	cc
CFLAGS	=	-Wall -Wextra -Werror

NAME	= 	philo

INC_DIR	=	-I.

INC		=	$(INC_DIR)/philo.h

SRC		=	philo.c

OBJ		=	$(SRC:.c=.o)

RM		=	rm -f

all		:	$(NAME)

$(NAME)	:	$(OBJ)
	make -C $(LIB)
	$(CC) $(CFLAGS) $(INC_DIR) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean	:
	$(RM) $(OBJ)

fclean	: clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re