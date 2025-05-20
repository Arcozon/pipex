NAME =  pipex
NB_NAME = pipex_nobonus

S_SRC_SPLIT_CMD =  cpy_arg.c  len_dollar.c  len_one_arg.c  mllc_all.c
D_SRC_SPLIT_CMD =  split_cmd/
SRC_SPLIT_CMD =  $(addprefix $(D_SRC_SPLIT_CMD), $(S_SRC_SPLIT_CMD))

S_SRC_CMDS =  $(SRC_SPLIT_CMD)  find_exe.c  init_cmd.c
D_SRC_CMDS =  cmds/
SRC_CMDS =  $(addprefix $(D_SRC_CMDS), $(S_SRC_CMDS))

S_SRC_HEREDOC =  heredoc.c  heredoc_exp.c  heredoc_no_exp.c
D_SRC_HEREDOC =  heredoc/
SRC_HEREDOC =  $(addprefix $(D_SRC_HEREDOC), $(S_SRC_HEREDOC))

S_SRC_UTILS =  error.c  free.c  utils2.c  utils.c
D_SRC_UTILS =  utils/
SRC_UTILS =  $(addprefix $(D_SRC_UTILS), $(S_SRC_UTILS))

SRC =  $(SRC_HEREDOC)  $(SRC_CMDS)  $(SRC_UTILS)  main.c  setup.c  exec.c
D_SRC =  src/

D_INC = inc/

D_BUILD = .build/
OBJ =  $(addprefix $(D_BUILD), $(SRC:.c=.o))

NB_D_BUILD = .nobonus_build/
NB_OBJ =  $(addprefix $(NB_D_BUILD), $(SRC:.c=.o))

CC =  cc
FLAGS = -Wall -Wextra -Werror -MMD -g
NB_FLAGS = $(FLAGS) -DPPX_BONUS=0

RM =  rm -rf

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o$@ $^

$(OBJ): $(D_BUILD)%.o:	$(D_SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -I$(D_INC) -c $< -o $@

nobonus: $(NB_NAME)

$(NB_NAME):	$(NB_OBJ)
	$(CC) -o$@ $^

$(NB_OBJ): $(NB_D_BUILD)%.o:	$(D_SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(NB_FLAGS) -I$(D_INC) -c $< -o $@

clean:
	$(RM) $(D_BUILD) $(NB_D_BUILD)

fclean: clean
	$(RM) $(NAME) $(NB_NAME)

re: fclean
	make all

DEPS = $(addprefix $(D_BUILD), $(SRC:.c=.d))
NB_DEPS = $(addprefix $(NB_D_BUILD), $(SRC:.c=.d))
-include $(DEPS) $(NB_DEPS)

.PHONY: re fclean clean all nobonus $(CC) $(FLAGS) $(B_FLAGS) $(RM)
