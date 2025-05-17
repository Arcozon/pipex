NAME =  pipex

S_SRC_SPLIT_CMD =  cpy_arg.c  len_dollar.c  len_one_arg.c  mllc_all.c
D_SRC_SPLIT_CMD =  split_cmd/
SRC_SPLIT_CMD =  $(addprefix $(D_SRC_SPLIT_CMD), $(S_SRC_SPLIT_CMD))

S_SRC_CMDS =  $(SRC_SPLIT_CMD)  find_exe.c  init_cmd.c
D_SRC_CMDS =  cmds/
SRC_CMDS =  $(addprefix $(D_SRC_CMDS), $(S_SRC_CMDS))

S_SRC_HEREDOC =  heredoc.c  heredoc_exp.c  heredoc_no_exp.c
D_SRC_HEREDOC =  heredoc/
SRC_HEREDOC =  $(addprefix $(D_SRC_HEREDOC), $(S_SRC_HEREDOC))

SRC =  $(SRC_HEREDOC)  $(SRC_CMDS)  main.c  setup.c  utils2.c  utils.c  error.c  free.c
D_SRC =  src/

D_INC = inc/

D_BUILD = .build/
OBJ =  $(addprefix $(D_BUILD), $(SRC:.c=.o))

CC =  cc
FLAGS = -Wall -Wextra -Werror -MMD

RM =  rm -rf

all:	$(NAME)
	echo $(OBJ)
	echo $(SRC)

$(NAME):	$(OBJ)
	$(CC) -o$@ $^

$(OBJ): $(D_BUILD)%.o:	$(D_SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -I$(D_INC) -c $< -o $@ 

clean:
	$(RM) $(D_BUILD)

fclean: clean
	$(RM) $(NAME)

re: fclean
	make all

-include DEPS = $(addprefix $(D_BUILD), $(SRC:.c=.d))

.PHONY: re fclean clean all $(CC) $(FLAGS) $(RM)

