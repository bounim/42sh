NAME ?= 21sh

SRC := \
	main.c \
	lexer/lexer.c \
	lexer/operator.c \
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
