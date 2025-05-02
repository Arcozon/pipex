NAME =  pipex

SRC = 
D_SRC = ./src/

D_BUILD = ./.build/
OBJ =  $(addprefix $(D_BUILD), $(SRC:.c=.o))
B_OBJ = $(addprefix $(D_BUILD), $(BSRC:.c=.o))

S_INC =  

CC =  cc
FLAGS = -Wall -Wextra -Werror -MMD

RM =  rm -rf

all:	$(NAME)

$(NAME):	$(OBJ)
	

bonus:	$(B_OBJ) $(OBJ)
	

$(OBJ): $(D_BUILD)%.o:	$(D_SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(D_BUILD)

fclean: clean
	$(RM) $(NAME)

re: fclean
	make all

-include DEPS = $(addprefix $(D_BUILD), $(SRC:.c=.d))

.PHONY: re fclean clean all bonus $(CC) $(FLAGS) $(RM) $(AR)

