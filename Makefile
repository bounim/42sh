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
	history/history_cmd.c \
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
	tmpfunc.c \
	utils/canonical_path.c

TEST_CANONICAL_PATH_NAME := canonical_path
TEST_CANONICAL_PATH_SRC := \
	utils/canonical_path.c

TEST := \
	$(TEST_CANONICAL_PATH_NAME)

CFLAGS ?=
CPPFLAGS ?= -Wall -Wextra -Werror
LDLIBS ?=
CPPFLAGS += -MMD -MP -Isrc
LDLIBS += -ltermcap

OBJDIR ?= obj
SRCDIR := src
OBJ_PREFIX := $(OBJDIR)/$(SRCDIR)/
OBJ := $(addprefix $(OBJ_PREFIX),$(SRC:.c=.o))
TESTDIR := test
TEST_OBJ_PREFIX := $(OBJDIR)/$(TESTDIR)/

TEST_CANONICAL_PATH_OBJ := $(TEST_OBJ_PREFIX)$(TEST_CANONICAL_PATH_NAME).o \
	$(addprefix $(OBJ_PREFIX),$(TEST_CANONICAL_PATH_SRC:.c=.o))

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
	$(RM) $(NAME) test/$(TEST_CANONICAL_PATH_NAME)

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: local_clean
local_clean:
	$(RM) $(OBJ) $(TEST_CANONICAL_PATH_OBJ)
	@$(RM) $(OBJ:.o=.d) $(TEST_CANONICAL_PATH_OBJ:.o=.d)
	@rmdir -p $(sort $(dir $(OBJ))) 2>/dev/null || true

.PHONY: test
test: $(addprefix test_,$(TEST))

$(TESTDIR)/$(TEST_CANONICAL_PATH_NAME): $(TEST_CANONICAL_PATH_OBJ) $(LIBFT_BIN)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(TEST_CANONICAL_PATH_OBJ) $(LDLIBS)

.PHONY: test_$(TEST_CANONICAL_PATH_NAME)
test_$(TEST_CANONICAL_PATH_NAME): $(TESTDIR)/$(TEST_CANONICAL_PATH_NAME)
	$^
