# ---- NAME ---- #

NAME = cub3D

FT = ./libft/libft.a
FTCC = -L./libft -lft

CC = cc
CFLAGS= -Wall -Wextra -Werror -g3
# CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
# CFLAGS = -g3 -fsanitize=address
AR = ar
ARFLAG = ruc
RM = rm -f

object_dir = ./objects
src_dir = ./src
bonus_src_dir = ./bonus_src

# ---- escape ---- #

DELINE = \033[K
CURSUP = \033[A

RESET = \033[0m
RESTINT = \033[22m

BOLD = \033[1m

MAGENTA = \033[35m
GREEN = \033[32m
RED = \033[31m

# ---- Mandatory ---- #

sources1 :=

sources1 += src/map_parse/map_parse.c
sources1 += src/map_parse/map_parse_utils.c
sources1 += src/map_parse/load_av.c
sources1 += src/map_parse/load_av_asset.c
sources1 += src/map_parse/load_wall_utils.c
sources1 += src/map_parse/make_map.c
sources1 += src/map_parse/check_map.c
sources1 += src/map_parse/check_map_utils.c
sources1 += src/map_parse/get_next_line_cub3D.c
sources1 += src/map_parse/make_map_img.c
sources1 += src/map_parse/put_pixel.c

sources1 += src/game_control/doors.c
sources1 += src/game_control/game_control.c
sources1 += src/game_control/key_press.c

sources1 += src/render/ray_calc.c
sources1 += src/render/ray_cast.c
sources1 += src/render/ray_utils.c
sources1 += src/render/render_doors.c

sources1 += src/error/ft_error.c

sources1 += src/minimap/draw_minimap.c
sources1 += src/minimap/draw_minimap_door.c
sources1 += src/minimap/pixel_utils.c

sources1 += src/main.c

# ---- Bonus ---- #

sources2 :=

sources2 += src_bonus/map_parse/map_parse.c
sources2 += src_bonus/map_parse/map_parse_utils.c
sources2 += src_bonus/map_parse/load_av.c
sources2 += src_bonus/map_parse/load_av_asset.c
sources2 += src_bonus/map_parse/load_wall_utils.c
sources2 += src_bonus/map_parse/make_map.c
sources2 += src_bonus/map_parse/check_map.c
sources2 += src_bonus/map_parse/check_map_utils.c
sources2 += src_bonus/map_parse/get_next_line_cub3D.c
sources2 += src_bonus/map_parse/make_map_img.c
sources2 += src_bonus/map_parse/put_pixel.c

sources2 += src_bonus/game_control/doors.c
sources2 += src_bonus/game_control/game_control.c
sources2 += src_bonus/game_control/key_press.c

sources2 += src_bonus/render/gun.c
sources2 += src_bonus/render/ray_calc.c
sources2 += src_bonus/render/ray_cast.c
sources2 += src_bonus/render/ray_utils.c
sources2 += src_bonus/render/render_doors.c

sources2 += src_bonus/error/ft_error.c

sources2 += src_bonus/minimap/draw_minimap.c
sources2 += src_bonus/minimap/draw_minimap_door.c
sources2 += src_bonus/minimap/pixel_utils.c

sources2 += src_bonus/main.c

# ---- Elements ---- #

objects1 = $(sources1:.c=.o)
objects2 = $(sources2:.c=.o)
all_objects = $(objects1) $(objects2)
all_sources = $(sources1) $(sources2)

define objects_goal
$(addprefix $(object_dir)/, $(call $(if $(filter bonus, $(MAKECMDGOALS)), objects2, objects1)))
endef

define react
$(if $(filter bonus, $(MAKECMDGOALS)), bonus, all)
endef

# ---- Command ---- #

.PHONY : clean fclean re all bonus

all : $(NAME)

$(NAME) : $(objects_goal) $(FT) mlx/libmlx.a
	@$(CC) $(CFLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $@ $(objects_goal) $(FTCC)
	@echo "$(DELINE) $(MAGENTA)$@ $(RESET) is compiled $(GREEN)$(BOLD) OK ✅ $(RESET)"

bonus : $(NAME)

$(object_dir)/%.o : %.c
	@mkdir -p $(object_dir)
	@mkdir -p $(object_dir)/$(dir $^)
	@$(CC) $(CFLAGS) -Imlx -Iinclude -c $^ -o $@
	@echo " $(MAGENTA)$(NAME) $(RESET)objects file compiling... $(DELINE)$(GREEN) $^ $(RESET)$(CURSUP)"

$(FT) :
	@make -C ./libft all

mlx/libmlx.a :
	@make -C ./mlx all

clean :
	@$(RM) $(all_objects)
	@rm -rf $(object_dir)
	@make -C ./libft clean
	@make -C ./mlx clean
	@echo "$(RED) Delete$(BOLD) objects $(RESTINT)file $(RESET)"

fclean :
	@$(RM) $(NAME)
	@$(RM) $(all_objects)
	@rm -rf $(object_dir)
	@make -C ./libft fclean
	@make -C ./mlx clean
	@echo "$(RED) Delete$(BOLD) $(NAME) $(RESTINT)file $(RESET)"

re :
	@make fclean
	@make $(react)
