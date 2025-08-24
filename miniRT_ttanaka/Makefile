NAME		=	miniRT

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f
RM_DIR		=	rm -rf

INC_DIR		=	inc
INCLUDES	=	-I$(INC_DIR)

SRC_DIR		=	src
OBJ_DIR		=	obj

SRCS		=	$(wildcard $(SRC_DIR)/*.c)
OBJS		=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

HEADERS		=	$(wildcard $(INC_DIR)/*.h)

MLX_PATH	=	mlx
MLX_LIB		=	$(MLX_PATH)/libmlx.a
INCLUDES	+=	-I$(MLX_PATH)
MLX_FLAGS	=	-L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	make -C $(MLX_PATH)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) Makefile
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM_DIR) $(OBJ_DIR)
	make clean -C $(MLX_PATH)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(MLX_LIB)

re: fclean all

.PHONY: all clean fclean re