NAME		=	miniRT

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address

RM			=	rm -f
RM_DIR		=	rm -rf

INC_DIR		=	inc
INCLUDES	=	-I$(INC_DIR)

SRC_DIR		=	src
OBJ_DIR		=	obj

SRCS_MAIN	=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/camera.c \
				$(SRC_DIR)/plot.c \
				$(SRC_DIR)/utils.c

SRCS_RAY	=	$(SRC_DIR)/ray/ray.c

SRCS_SHAPE	=	$(SRC_DIR)/shape/cylinder.c \
                $(SRC_DIR)/shape/plane.c \
                $(SRC_DIR)/shape/sphere.c

SRCS_MAT	=	$(SRC_DIR)/material/dielectric.c \
                $(SRC_DIR)/material/diffuse_light.c \
                $(SRC_DIR)/material/lambertian.c \
                $(SRC_DIR)/material/metal.c

SRCS_HIT	=	$(SRC_DIR)/hittable/hittable_lst.c \
				$(SRC_DIR)/hittable/bvh/bucket.c \
				$(SRC_DIR)/hittable/bvh/bvh_build_info.c \
				$(SRC_DIR)/hittable/bvh/bvh_builder.c \
				$(SRC_DIR)/hittable/bvh/bvh_interface.c \
				$(SRC_DIR)/hittable/bvh/partition.c \
				$(SRC_DIR)/hittable/bvh/sah.c \
				$(SRC_DIR)/hittable/bvh/traverse_utils.c

SRC_AABB	=	$(SRC_DIR)/AABB/aabb_utils1.c \
				$(SRC_DIR)/AABB/aabb_utils2.c \

SRCS_PARSE	=	$(SRC_DIR)/parse/parse.c \
                $(SRC_DIR)/parse/parse_utils.c \
                $(SRC_DIR)/parse/parse_color.c \
                $(SRC_DIR)/parse/parse_coords.c \
                $(SRC_DIR)/parse/parse_error_print.c \
                $(SRC_DIR)/parse/parse_double.c \
                $(SRC_DIR)/parse/parse_material.c \
                $(SRC_DIR)/parse/set_env.c \
                $(SRC_DIR)/parse/set_objs_1.c \
                $(SRC_DIR)/parse/set_objs_2.c

SRCS_UTILS	=	$(SRC_DIR)/utils/color/color.c \
				$(SRC_DIR)/utils/color/color_utils_1.c \
				$(SRC_DIR)/utils/color/color_utils_2.c \
                $(SRC_DIR)/utils/ft_math/calculation.c \
                $(SRC_DIR)/utils/ft_math/clamp.c \
                $(SRC_DIR)/utils/ft_math/random.c \
                $(SRC_DIR)/utils/vector/vec.c \
                $(SRC_DIR)/utils/vector/vec_utils_1.c \
                $(SRC_DIR)/utils/vector/vec_utils_2.c \
                $(SRC_DIR)/utils/vector/vec_utils_3.c \
                $(SRC_DIR)/utils/vector/vec_random.c \

SRCS_LIBFT	=	$(SRC_DIR)/utils/libft/ft_atoi.c \
                $(SRC_DIR)/utils/libft/ft_calloc.c \
                $(SRC_DIR)/utils/libft/ft_isdigit.c \
                $(SRC_DIR)/utils/libft/ft_isspace.c \
                $(SRC_DIR)/utils/libft/ft_memset.c \
                $(SRC_DIR)/utils/libft/ft_put_fd.c \
                $(SRC_DIR)/utils/libft/ft_split.c \
                $(SRC_DIR)/utils/libft/ft_strarr_len.c \
                $(SRC_DIR)/utils/libft/ft_string.c \
                $(SRC_DIR)/utils/libft/ft_strlen.c \
                $(SRC_DIR)/utils/libft/ft_strtod.c \
                $(SRC_DIR)/utils/libft/ft_strtod_utils1.c \
                $(SRC_DIR)/utils/libft/ft_strtod_utils2.c

SRCS		=	$(SRCS_MAIN) $(SRCS_RAY) $(SRCS_SHAPE) $(SRCS_MAT) \
				$(SRCS_HIT) $(SRC_AABB) $(SRCS_PARSE) $(SRCS_UTILS) $(SRCS_LIBFT)

OBJS		=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

GNL_DIR		=	get_next_line
GNL_SRCS	=	$(GNL_DIR)/get_next_line.c \
                $(GNL_DIR)/get_next_line_utils.c
GNL_OBJS	=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(GNL_SRCS))

HEADERS		=	$(INC_DIR)/aabb.h \
                $(INC_DIR)/camera.h \
                $(INC_DIR)/hittable.h \
                $(INC_DIR)/material.h \
                $(INC_DIR)/minirt.h \
                $(INC_DIR)/parse.h \
                $(INC_DIR)/ray.h \
                $(INC_DIR)/scene.h \
                $(INC_DIR)/shape.h \
                $(INC_DIR)/utils.h \
                $(INC_DIR)/hittable/base_hittable.h \
                $(INC_DIR)/hittable/bvh.h \
                $(INC_DIR)/hittable/hittable_lst.h \
                $(INC_DIR)/utils/color.h \
                $(INC_DIR)/utils/ft_math.h \
                $(INC_DIR)/utils/libft.h \
                $(INC_DIR)/utils/vector.h \
                $(GNL_DIR)/get_next_line.h

MLX_PATH	=	minilibx
MLX_LIB		=	$(MLX_PATH)/libmlx.a
INCLUDES	+=	-I$(MLX_PATH)
MLX_FLAGS	=	-L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(GNL_OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(INCLUDES) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	make -C $(MLX_PATH)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) Makefile
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/$(GNL_DIR)/%.o: $(GNL_DIR)/%.c $(HEADERS) Makefile
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM_DIR) $(OBJ_DIR)
	make clean -C $(MLX_PATH)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(MLX_LIB)

re: fclean all

.PHONY: all clean fclean re