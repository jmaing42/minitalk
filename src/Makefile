Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)
MAKE := $(MAKE) $(if $(filter 1,$(V) $(VERBOSE)),,--no-print-directory)

# This variable will be used only if source files are not hardcoded
SRCS ?= $(shell find . -name "*.c" | xargs)
SRCS_SERVER := $(filter ./server_%,$(SRCS))
SRCS_CLIENT := $(filter ./client_%,$(SRCS))
SRCS_LIBFT := $(filter-out $(SRCS_SERVER) $(SRCS_CLIENT),$(SRCS))

NAME_SERVER := server
NAME_CLIENT := client
OTHER_USEFUL_FILES := .editorconfig .gitignore

CC := clang
CCLD := clang
AR := ar
CFLAGS := -Wall -Wextra -Werror
TMPS := $(OTHER_USEFUL_FILES)

TMP_DIR := tmp

all: $(NAME_SERVER) $(NAME_CLIENT) $(OTHER_USEFUL_FILES)
bonus: all
clean:
	$Qrm -rf $(OTHER_USEFUL_FILES) tmp
fclean: clean
	$Qrm -f $(NAME_SERVER) $(NAME_CLIENT)
re:
	$Q$(MAKE) fclean
	$Q$(MAKE) all
.PHONY: all bonus clean fclean re

.editorconfig:
	$Qprintf "root = true\n\n[*]\ncharset = utf-8\nend_of_line = lf\nindent_size = 4\nindent_style = tab\ninsert_final_newline = true\ntrim_trailing_whitespace = true\n" > .editorconfig
.gitignore:
	$Qprintf ".*\ntmp\n" > .gitignore

ifeq ($(MOULINETTE_MODE),1)

CC := cc
CCLD := cc

else

PROFILE ?= release
ifeq ($(PROFILE),release)
CFLAGS += -O3 -DNDEBUG
else ifeq ($(PROFILE),debug)
CFLAGS += -g3 -DDEBUG
else
$(error Bad profile)
endif

TARGET ?= production
ifeq ($(TARGET),production)
CFLAGS += -DNDEVELOPMENT
else ifeq ($(TARGET),development)
CFLAGS += -DDEVELOPMENT
else
$(error Bad target)
endif

SUFFIX := .$(TARGET).$(PROFILE)$(if $(SANITIZER),.$(SANITIZER))
CFLAGS += $(if $(SANITIZER),-fsanitize=$(SANITIZER),) -std=c99 -pedantic -MMD -DNO_MOULINETTE
LDFLAGS += $(if $(SANITIZER),-fsanitize=$(SANITIZER),)

-include $(TMP_DIR)/$(SRCS:.c=$(SUFFIX).d)

endif

$(TMP_DIR)/%.a:
	$Qmkdir -p $(@D)
	$Q$(AR) rcs $@ $^
$(TMP_DIR)/%$(SUFFIX).o: %.c
	$Qmkdir -p $(@D)
	$Q$(CC) $(CFLAGS) -o $@ -c $<
$(TMP_DIR)/%$(SUFFIX).exe: $(TMP_DIR)/libft$(SUFFIX).a
	$Q$(CCLD) $(LDFLAGS) -o $@ $^

$(TMP_DIR)/libft$(SUFFIX).a: $(patsubst ./%.c,$(TMP_DIR)/%$(SUFFIX).o,$(SRCS_LIBFT))
$(TMP_DIR)/$(NAME_SERVER)$(SUFFIX).exe: $(patsubst ./%.c,$(TMP_DIR)/%$(SUFFIX).o,$(SRCS_SERVER))
$(TMP_DIR)/$(NAME_CLIENT)$(SUFFIX).exe: $(patsubst ./%.c,$(TMP_DIR)/%$(SUFFIX).o,$(SRCS_CLIENT))

.PHONY: $(NAME_SERVER) $(NAME_CLIENT)
$(NAME_SERVER): $(TMP_DIR)/$(NAME_SERVER)$(SUFFIX).exe
	$Qcp $(TMP_DIR)/$(NAME_SERVER)$(SUFFIX).exe $(NAME_SERVER)
$(NAME_CLIENT): $(TMP_DIR)/$(NAME_CLIENT)$(SUFFIX).exe
	$Qcp $(TMP_DIR)/$(NAME_CLIENT)$(SUFFIX).exe $(NAME_CLIENT)
