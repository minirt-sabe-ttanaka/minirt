CC := cc
CFLAGS := -Wall -Werror -Wextra

# submodule / library paths (override from command line if needed)
LIBFT_PATH := libft
GNL_PATH ?=        # set to get_next_line path if you use it (leave empty to ignore)
MLX_PATH ?= minilibx

SRC_DIR := src
OBJ_DIR := obj
INCLUDE_DIR := include

# collect sources (recursive)
SRC_FILES := $(shell find $(SRC_DIR) -type f -name '*.c' 2>/dev/null)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# library artifacts
LIBFT := $(LIBFT_PATH)/libft.a
ifeq ($(strip $(GNL_PATH)),)
GNL :=
else
GNL := $(GNL_PATH)/libget_next_line.a
endif
MLX := $(MLX_PATH)/libmlx.a

# include dirs (adjust if your headers live in subfolders)
INCLUDES := -I$(INCLUDE_DIR) -I$(LIBFT_PATH) -I$(MLX_PATH)
ifeq ($(strip $(GNL_PATH)),)
else
INCLUDES += -I$(GNL_PATH)
endif

# detect platform
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    # macOS
    EXTRA_LINK := -framework OpenGL -framework AppKit -lm
else
    # assume Linux with X11
    EXTRA_LINK := -lXext -lX11 -lm
endif

NAME := minirt

.PHONY: all clean fclean re libft mlx gnl

all: $(NAME)

# Link step: use static libs if present (libft, gnl, mlx)
# show linking command for debug (no @)
$(NAME): $(OBJ_FILES) $(LIBFT) $(MLX) $(GNL)
	@echo "Linking: $(NAME)"
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES) $(LIBFT) $(GNL) $(MLX) $(EXTRA_LINK)

# compile c -> o (preserve directory structure)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# build libft if needed
$(LIBFT):
	@if [ -d $(LIBFT_PATH) ]; then \
		$(MAKE) -C $(LIBFT_PATH); \
	else \
		echo "Warning: $(LIBFT_PATH) not found, skipping libft build"; \
	fi

# build get_next_line lib if path provided
$(GNL):
	@if [ -n "$(GNL)" ]; then \
		if [ -d "$(GNL_PATH)" ]; then \
			$(MAKE) -C $(GNL_PATH); \
		else \
			echo "Warning: $(GNL_PATH) not found, skipping get_next_line build"; \
		fi \
	else \
		:; \
	fi

# build minilibx (platform-dependent Makefile inside)
$(MLX):
	@if [ -d $(MLX_PATH) ]; then \
		$(MAKE) -C $(MLX_PATH); \
	else \
		echo "Warning: $(MLX_PATH) not found, skipping mlx build"; \
	fi

# clean project objects (and delegate to submodules)
clean:
	@if [ -d $(LIBFT_PATH) ]; then $(MAKE) -C $(LIBFT_PATH) fclean || true; fi
	@if [ -n "$(GNL)" ] && [ -d "$(GNL_PATH)" ]; then $(MAKE) -C $(GNL_PATH) fclean || true; fi
	@if [ -d $(MLX_PATH) ]; then $(MAKE) -C $(MLX_PATH) clean || true; fi
	@rm -rf $(OBJ_DIR)

# full clean (binary + objects)
fclean: clean
	@rm -f $(NAME)

re: fclean all