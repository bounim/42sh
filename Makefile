NAME ?= 21sh

SRC := \
	cleaner/fatal_exit.c \
	cleaner/free_term.c \
	env/addlast_envl.c \
	env/envarr_2_envl.c \
	env/get_env_val.c \
	env/init_shell_envl.c \
	env/push_env.c \
	env/dup_envl.c \
	env/free_envl.c \
	env/print_envl.c \
	env/envl_to_envarr.c \
	execution/execution.c \
	execution/redir.c \
	history/controler_history.c \
	history/down_history.c \
	history/init_shell_history.c \
	history/list_history.c \
	history/up_history.c \
	history/search_in_history.c\
	history/search_in_history_actions.c\
	history/file_from_history.c \
	history/resize_history.c \
	history/free_history.c \
	history/print_search.c \
	history/history_utils.c \
	lexer/func.c \
	lexer/func2.c \
	lexer/func3.c \
	lexer/lexer.c \
	lexer/token.c \
	lexer/debug.c \
	main.c \
	signal/ft_signal.c \
	signal/signal_handler.c \
	terminal/shell.c \
	terminal/run_shell.c \
	terminal/terminal.c \
	ft.c \
	builtin/start_builtin.c \
	builtin/built_history.c \
	builtin/built_cd.c \
	builtin/built_cd_opts.c \
	builtin/built_cd_extra.c \
	builtin/built_echo.c \
	builtin/built_env.c \
	builtin/built_extra.c \
	builtin/built_setenv.c \
	builtin/built_unsetenv.c\
	builtin/check_builtin.c \
	builtin/built_set.c \
	builtin/built_unset.c \
	builtin/built_export.c \
	builtin/built_alias.c \
	builtin/built_unalias.c \
	builtin/built_alias_extra.c \
	builtin/built_jobs.c \
	builtin/built_jobs_extra.c \
	builtin/built_fg.c \
	builtin/built_bg.c \
	builtin/built_type.c \
	builtin/built_debug.c \
	builtin/replace_exclaim.c \
	builtin/replace_exclaim_extra.c \
	builtin/find_path.c \
	builtin/print_general_error.c \
	builtin/check_opts.c \
	builtin/built_exit.c \
	readline/readline.c \
	readline/get_term_pos.c \
	readline/prompt_controler.c \
	readline/readline_errors_controler.c \
	readline/character_controler.c \
	readline/calculate_pos.c \
	readline/print_controler.c \
	readline/input_controler.c \
	readline/movement_controler.c \
	readline/special_movement_controler.c \
	readline/del_controler.c \
	readline/copy_controler.c \
	readline/copy_conditions.c \
	readline/return_fn.c \
	readline/free_controler.c \
	readline/special_del_controler.c \
	readline/handle_ctrl_c.c \
	readline/drag_char.c \
	readline/transpose_cursor_placement.c \
	readline/transpose_conditions.c \
	readline/transpose_word.c \
	readline/list_buff_transform.c \
	readline/add_to_undo_list.c \
	readline/undo_last_editing_command.c \
	readline/utils.c \
	readline/utils_input_controler.c \
	readline/vi_command_mode.c \
	readline/vi_movement_controler.c \
	readline/vi_special_movement_controler.c \
	readline/vi_search_char.c \
	readline/vi_insert.c \
	readline/vi_delete_controler.c \
	readline/vi_replace.c \
	readline/vi_yank_paste.c \
	readline/vi_repeat_search_char.c \
	readline/vi_repeat_search_fn.c \
	readline/vi_undo.c \
	readline/vi_delete_motion_c.c \
	job_control/manage_job.c \
	job_control/put_in_xground.c \
	job_control/launch_job.c \
	job_control/launch_proc.c \
	job_control/stop_job.c \
	job_control/continue_job.c \
	job_control/init_job.c \
	job_control/creat_job.c \
	job_control/job_info.c \
	parser/parser.c \
	parser/parser_destroy.c \
	parser/parser_func.c \
	parser/parser_node.c \
	parser/parser_printer.c \
	parser/is.c \
	expansions/expansions.c

CFLAGS ?=
CPPFLAGS ?= -Wall -Wextra -Werror -g3
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
