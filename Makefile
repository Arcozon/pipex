NAME =  pipex
B_NAME = pipex_bonus

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

B_D_BUILD = .bonus_build/
B_OBJ =  $(addprefix $(B_D_BUILD), $(SRC:.c=.o))

CC =  cc
FLAGS = -Wall -Wextra -Werror -MMD
B_FLAGS = $(FLAGS) -DPPX_BONSUS=1

RM =  rm -rf

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o$@ $^

$(OBJ): $(D_BUILD)%.o:	$(D_SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -I$(D_INC) -c $< -o $@

bonus: $(B_NAME)

$(B_NAME):	$(B_OBJ)
	$(CC) -o$@ $^

$(B_OBJ): $(B_D_BUILD)%.o:	$(D_SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(B_FLAGS) -I$(D_INC) -c $< -o $@

clean:
	$(RM) $(D_BUILD) $(B_D_BUILD)

fclean: clean
	$(RM) $(NAME) $(B_NAME)

re: fclean
	make all

DEPS = $(addprefix $(D_BUILD), $(SRC:.c=.d))
B_DEPS = $(addprefix $(B_D_BUILD), $(SRC:.c=.d))
-include $(DEPS) $(B_DEPS)

.PHONY: re fclean clean all bonus $(CC) $(FLAGS) $(B_FLAGS) $(RM)
