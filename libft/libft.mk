LIBFT_SHORT_NAME := ft

LIBFT_SRC := \
	ft_isspace.c \
	ft_memcpy.c \
	ft_memcmp.c \
	ft_memmove.c \
	ft_memset.c \
	ft_stpncpy.c \
	ft_stpncpyz.c \
	ft_strchr.c \
	ft_strcmp.c \
	ft_strjoin.c \
	ft_strlen.c \
	ft_strncpy.c \
	ft_strncpyz.c \
	ft_strnlen.c \
	hashmap/hashmap_clean.c \
	hashmap/hashmap_clean_key.c \
	hashmap/hashmap_get.c \
	hashmap/hashmap_hash_crc32.c \
	hashmap/hashmap_init.c \
	hashmap/hashmap_set.c \
	hashmap/hashmap_unset.c \
	printer/printer_bin.c \
	printer/printer_char.c \
	printer/printer_endl.c \
	printer/printer_flush.c \
	printer/printer_init.c \
	printer/printer_int.c \
	printer/printer_long.c \
	printer/printer_numeric_length.c \
	printer/printer_str.c \
	printer/printer_uint.c \
	printer/printer_ulong.c \
	ft_arrdel.c \
	ft_arrdup.c \
	ft_arrlen.c \
	ft_atoi.c \
	ft_itoa.c \
	ft_strdup.c \
	ft_strsub.c \
	ft_strequ.c \
	ft_memalloc.c \
	ft_strfjoin.c \
	ft_strsplit.c \
	ft_wslen.c \
	ft_isnotprint.c \
	ft_first_char_unicode.c \
	ft_u8_strequ.c \
	ft_u8_strfjoin.c \
	ft_u8_strjoin.c \
	ft_u8_strlen.c \
	ft_u8_strnew.c \
	ft_u8_strsplit.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_memchr.c \
	ft_strsize.c \
	ft_putstr.c \
	ft_carac_nb.c \
	ft_wchar_len.c \
	ft_ustrlen.c \
	ft_u8_strdup.c \

LIBFT_NAME := lib$(LIBFT_SHORT_NAME)
CPPFLAGS += -I$(LIBFT_NAME)
LDFLAGS += -L$(LIBFT_NAME)
LDLIBS += -l$(LIBFT_SHORT_NAME)

OBJDIR ?= .
LIBFT_OBJ_PREFIX := $(OBJDIR)/$(LIBFT_NAME)/
LIBFT_OBJ := $(addprefix $(LIBFT_OBJ_PREFIX),$(LIBFT_SRC:.c=.o))
LIBFT_BIN := $(LIBFT_NAME)/$(LIBFT_NAME).a

.PHONY: libft
libft: $(LIBFT_BIN)

$(LIBFT_BIN): $(LIBFT_OBJ)
	$(AR) rcs $@ $^

-include $(LIBFT_OBJ:.o=.d)

.PHONY: libft_clean
libft_clean:
	$(RM) $(LIBFT_OBJ)
	@$(RM) $(LIBFT_OBJ:.o=.d)
	@rmdir -p $(sort $(dir $(LIBFT_OBJ))) 2>/dev/null || true

.PHONY: libft_fclean
libft_fclean: libft_clean
	$(RM) $(LIBFT_BIN)

.PHONY: libft_re
libft_re:
	$(MAKE) libft_fclean
	$(MAKE) libft
