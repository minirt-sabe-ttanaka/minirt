NAME		=	miniRT

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -O3
DEBUG_FLAGS =   -g -fsanitize=address

LDLIBS		=  	-lpthread

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

SRCS_RAYTRACING =	$(SRC_DIR)/raytracing/raytracing.c \
					$(SRC_DIR)/raytracing/raytracing_thread.c \
					$(SRC_DIR)/raytracing/raytracing_utils.c 

SRCS_MAT	=	$(SRC_DIR)/material/dielectric.c \
				$(SRC_DIR)/material/diffuse_light.c \
				$(SRC_DIR)/material/lambertian.c \
				$(SRC_DIR)/material/metal.c \
				$(SRC_DIR)/material/destroy.c \
				$(SRC_DIR)/material/utils.c


SRCS_HIT	=	$(SRC_DIR)/hittable/hittable_lst.c \
				$(SRC_DIR)/hittable/hittable_lst_pdf.c \
				$(SRC_DIR)/hittable/destroy.c \
				$(SRC_DIR)/hittable/bvh/bucket.c \
				$(SRC_DIR)/hittable/bvh/bvh_build_info.c \
				$(SRC_DIR)/hittable/bvh/bvh_builder.c \
				$(SRC_DIR)/hittable/bvh/bvh_interface.c \
				$(SRC_DIR)/hittable/bvh/partition.c \
				$(SRC_DIR)/hittable/bvh/sah.c \
				$(SRC_DIR)/hittable/bvh/traverse_utils.c \
				$(SRC_DIR)/hittable/shape/cylinder.c \
				$(SRC_DIR)/hittable/shape/cylinder_pdf.c \
				$(SRC_DIR)/hittable/shape/plane.c \
				$(SRC_DIR)/hittable/shape/plane_pdf.c \
				$(SRC_DIR)/hittable/shape/sphere.c \
				$(SRC_DIR)/hittable/shape/sphere_pdf.c \
				$(SRC_DIR)/hittable/shape/destroy.c \

SRCS_AABB	=	$(SRC_DIR)/AABB/aabb_utils1.c \
				$(SRC_DIR)/AABB/aabb_utils2.c 

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

SRCS_PDF	=	$(SRC_DIR)/pdf/pdf_cosine.c \
				$(SRC_DIR)/pdf/pdf_hittable.c \
				$(SRC_DIR)/pdf/pdf_mixture.c 

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
				$(SRC_DIR)/utils/vector/onb.c \

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

SRCS		=	$(SRCS_MAIN) $(SRCS_RAY) $(SRCS_RAYTRACING) $(SRCS_MAT) \
				$(SRCS_HIT) $(SRCS_AABB) $(SRCS_PARSE) $(SRCS_PDF) $(SRCS_UTILS) $(SRCS_LIBFT)

OBJS		=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

GNL_DIR		=	get_next_line
GNL_SRCS	=	$(GNL_DIR)/get_next_line.c \
				$(GNL_DIR)/get_next_line_utils.c
GNL_OBJS	=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(GNL_SRCS))

HEADERS		=	$(INC_DIR)/minirt.h \
				$(INC_DIR)/rt_struct.h \
				$(INC_DIR)/core/utils/color.h \
				$(INC_DIR)/core/utils/ft_math.h \
				$(INC_DIR)/core/utils/libft.h \
				$(INC_DIR)/core/utils/vector.h \
				$(INC_DIR)/core/ray.h \
				$(INC_DIR)/core/utils.h \
				$(INC_DIR)/engine/camera.h \
				$(INC_DIR)/engine/parse.h \
				$(INC_DIR)/engine/pdf.h \
				$(INC_DIR)/engine/plot.h \
				$(INC_DIR)/engine/raytracing.h \
				$(INC_DIR)/engine/scene.h \
				$(INC_DIR)/scene/hittable.h \
				$(INC_DIR)/scene/hittable/base_hittable.h \
				$(INC_DIR)/scene/hittable/bvh.h \
				$(INC_DIR)/scene/hittable/hittable_lst.h \
				$(INC_DIR)/scene/hittable/shape.h \
				$(INC_DIR)/scene/material.h \
				$(GNL_DIR)/get_next_line.h

MLX_PATH	=	minilibx
MLX_LIB		=	$(MLX_PATH)/libmlx.a
INCLUDES	+=	-I$(MLX_PATH)
MLX_FLAGS	=	-L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(GNL_OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS)  $(OBJS) $(GNL_OBJS) $(INCLUDES) $(MLX_FLAGS) $(LDLIBS) -o $(NAME)

debug: fclean
	make CFLAGS="$(CFLAGS) $(DEBUG_FLAGS)" LDFLAGS="$(DEBUG_FLAGS)" all

$(MLX_LIB):
	@make -C $(MLX_PATH) CC="$(CC)" \
	CFLAGS="$(CFLAGS) -DGL_SILENCE_DEPRECATION -Wno-deprecated-declarations -Wno-sign-compare -Wno-unused-parameter -Wno-error"

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

.PHONY: all clean fclean re debug