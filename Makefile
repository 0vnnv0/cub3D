NAME = cub3d

BONUS = cub3d_bonus

SRC = src/main/main.c \
src/main/init.c \
src/raycast/keys.c \
src/raycast/keys_utils.c \
src/raycast/draw.c \
src/raycast/draw_utils.c \
src/main/exit.c \
src/raycast/dda.c \
src/raycast/ray.c \
src/parsing/parser.c \
src/parsing/helpers.c \
src/parsing/textures.c \
src/parsing/parse_map.c \
src/parsing/validate_map.c \
src/parsing/colors.c \
src/parsing/free.c \
src/parsing/parse_config.c \
src/parsing/player.c

SRC_BONUS = src/main/main_bonus.c \
src/main/init_bonus.c \
src/raycast/keys_bonus.c \
src/raycast/keys_utils_bonus.c \
src/raycast/draw_bonus.c \
src/raycast/draw_utils_bonus.c \
src/main/exit_bonus.c \
src/raycast/dda_bonus.c \
src/raycast/ray_bonus.c \
src/parsing/parser_bonus.c \
src/parsing/helpers_bonus.c \
src/parsing/textures_bonus.c \
src/parsing/parse_map_bonus.c \
src/parsing/validate_map_bonus.c \
src/parsing/colors_bonus.c \
src/parsing/free_bonus.c \
src/parsing/parse_config_bonus.c \
src/parsing/player_bonus.c \
src/parsing/minimap_bonus.c

CC = cc
CFLAGS = -Wall -Werror -Wextra

OBJDIR = objs
OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))
OBJDIRS = $(sort $(dir $(OBJS)))

OBJDIR_BONUS = objs_bonus
OBJS_BONUS = $(patsubst %.c, $(OBJDIR_BONUS)/%.o, $(SRC_BONUS))
OBJDIRS_BONUS = $(sort $(dir $(OBJS_BONUS)))

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR)

MLX_DIR = ./mlx
MLX = $(MLX_DIR)/libmlx.a
MLXFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
INCLUDES += -I$(MLX_DIR)

GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(LIBFT) $(MLX) $(NAME)

bonus: $(LIBFT) $(MLX) $(BONUS)

$(LIBFT):
	@echo "$(YELLOW) Building libft...$(RESET)"
	@$(MAKE) --silent --no-print-directory -C $(LIBFT_DIR)

$(MLX):
	@echo "$(YELLOW) Building MiniLibX...$(RESET)"
	@$(MAKE) --silent --no-print-directory -C $(MLX_DIR)

$(OBJDIRS):
	@mkdir -p $@

$(OBJDIR)/%.o: %.c | $(OBJDIRS)
	@echo "$(YELLOW) Compiling $< ... $(RESET)"
	@$(CC) $(CFLAGS) -I/usr/include -Imlx -O3 -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(MLXFLAGS)
	@echo "$(GREEN) Executable $(NAME) created.$(RESET)"

$(OBJDIRS_BONUS):
	@mkdir -p $@

$(OBJDIR_BONUS)/%.o: %.c | $(OBJDIRS_BONUS)
	@echo "$(YELLOW) Compiling $< ... $(RESET)"
	@$(CC) $(CFLAGS) -I/usr/include -Imlx -O3 -c $< -o $@

$(BONUS): $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(BONUS) $(LIBFT) $(MLXFLAGS)
	@echo "$(GREEN) Executable $(BONUS) created.$(RESET)"

clean:
	@$(MAKE) --no-print-directory clean -C $(LIBFT_DIR)
	@$(MAKE) -C $(MLX_DIR)
	@echo "$(GREEN)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)

fclean: clean
	@$(MAKE) --no-print-directory fclean -C $(LIBFT_DIR)
	@$(MAKE) -C $(MLX_DIR)
	@echo "$(GREEN)Removing executable ... $(RESET)"
	@rm -rf $(NAME)

bonus_clean:
	@$(MAKE) --no-print-directory clean -C $(LIBFT_DIR)
	@$(MAKE) -C $(MLX_DIR)
	@echo "$(GREEN)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR_BONUS)

bonus_fclean: bonus_clean
	@$(MAKE) --no-print-directory fclean -C $(LIBFT_DIR)
	@$(MAKE) -C $(MLX_DIR)
	@echo "$(GREEN)Removing executable ... $(RESET)"
	@rm -rf $(BONUS)

re: fclean all

bonus_re: bonus_fclean bonus

.PHONY: all clean fclean re
