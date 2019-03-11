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
	history/history.c \
	history/init_shell_history.c \
	history/list_history.c \
	history/up_history.c \
	lexer/func.c \
	lexer/lexer.c \
	main.c \
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
	builtin/built_unsetenv.c\
	readline/line_editing.c \
    readline/signal_handler.c\
    readline/line_editing_errors_controler.c\
	readline/character_controler.c\
	readline/calculate_pos.c\
	readline/print_controler.c\
	readline/input_controler.c\
	readline/movement_controler.c\
	readline/special_movement_controler.c\
	readline/del_controler.c\
	readline/copy_controler.c\
	readline/utils.c\
	readline/free_controler.c

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
