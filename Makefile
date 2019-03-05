NAME ?= 21sh

SRC := \
	cleaner/fatal_exit.c \
	cleaner/free_term.c \
	env/addlast_envl.c \
	env/envarr_2_envl.c \
	env/get_env_val.c \
	env/init_shell_envl.c \
	env/push_env.c \
	history/controler_history.c \
	history/down_history.c \
	history/file_history.c \
	history/history.c \
	history/init_shell_history.c \
	history/list_history.c \
	history/up_history.c \
	lexer/func.c \
	lexer/lexer.c \
	main.c \
	readline/readline.c \
	readline/rl_buffer.c \
	readline/rl_copy.c \
	readline/rl_cut.c \
	readline/rl_delete_ctrl.c \
	readline/rl_delete_line.c \
	readline/rl_moving_ctrl.c \
	readline/rl_moving_esc.c \
	readline/rl_paste.c \
	readline/rl_prompt.c \
	readline/rl_termcaps.c \
	readline/rl_undo.c \
	signal/ft_signal.c \
	terminal/shell.c \
	terminal/terminal.c \
	ft.c \
	builtin/built_history.c \
	builtin/built_exclaim.c \
	builtin/built_cd.c \
	builtin/built_echo.c \
	builtin/built_env.c \
	builtin/built_env_extra.c \
	builtin/built_setenv.c \
	builtin/built_unsetenv.c

CFLAGS ?=
CPPFLAGS ?= -Wall -Wextra -Werror
LDLIBS ?=
CPPFLAGS += -MMD -MP -Isrc
#LDLIBS += -ltermcap
LDLIBS += -lncurses

OBJDIR ?= obj
SRCDIR := src
OBJ_PREFIX := $(OBJDIR)/$(SRCDIR)/
OBJ := $(addprefix $(OBJ_PREFIX),$(SRC:.c=.o))

.PHONY: all
all: $(NAME)

-include libft/libft.mk

$(NAME): $(OBJ) $(LIBFT_BIN)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $(filter %.c,$^)

-include $(OBJ:.o=.d)

.PHONY: clean
clean: local_clean libft_clean

.PHONY: fclean
fclean: local_clean libft_fclean
	$(RM) $(NAME)

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: local_clean
local_clean:
	$(RM) $(OBJ)
	@$(RM) $(OBJ:.o=.d)
	@rmdir -p $(sort $(dir $(OBJ))) 2>/dev/null || true
