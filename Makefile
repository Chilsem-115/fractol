NAME = fractol

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinc -Ilib/ft_printf/inc -Ilib/minilibx

SRC_DIR = src
OBJ_DIR = obj
FT_PRINTF_DIR = lib/ft_printf
MLX_DIR = lib/minilibx

FT_PRINTF_LIB = $(FT_PRINTF_DIR)/ft_printf.a
MLX_LIB = $(MLX_DIR)/libmlx.a
LIBS = $(FT_PRINTF_LIB) $(MLX_LIB) -lX11 -lXext -lm

# Source files
SRC_FILES = compute.c events.c fractol.c init_window.c render_fractal.c color_compute.c utils.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(FT_PRINTF_LIB) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# Object compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile ft_printf
$(FT_PRINTF_LIB):
	$(MAKE) -C $(FT_PRINTF_DIR)

# Cleaning
clean:
	@rm -rf $(OBJ_DIR)
	$(MAKE) -C $(FT_PRINTF_DIR) clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
