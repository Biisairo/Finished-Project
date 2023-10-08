# ---- NAME ---- #

NAME = so_long

FT = ./libft/libft.a
FTCC = -L./libft -lft

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAG = ruc
RM = rm -f

object_dir = ./objects

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

sources1 += main.c

sources1 += ./map/parse_map.c
sources1 += ./map/make_map.c
sources1 += ./map/map_check.c

sources1 += ./init/load_player.c
sources1 += ./init/load_monster.c
sources1 += ./init/load_map.c
sources1 += ./init/init_game.c
sources1 += ./init/load_collection.c

sources1 += ./error/ft_error.c

sources1 += ./animation/render_frame.c
sources1 += ./animation/render_frame_utils.c
sources1 += ./animation/player_ani.c
sources1 += ./animation/player_ani_utils.c
sources1 += ./animation/eat_collection.c
sources1 += ./animation/monster_ani.c

sources1 += ./hook/key_hook.c

sources1 += ./move/player_move.c
sources1 += ./move/player_jump.c
sources1 += ./move/player_drop.c
sources1 += ./move/player_die.c

sources1 += ./etc/image.c
sources1 += ./etc/color.c

# ---- Bonus ---- #

sources2 :=

sources2 +=

# ---- Elements ---- #

all_sources = $(sources1) $(sources2)

objects1 = $(sources1:.c=.o)
objects2 = $(sources2:.c=.o)
all_objects = $(objects1) $(objects2)

define objects_goal
$(addprefix $(object_dir)/, $(call $(if $(filter bonus, $(MAKECMDGOALS)), all_objects, objects1)))
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
	@$(CC) $(CFLAGS) -Imlx -c $^ -o $@
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

fclean : clean
	@$(RM) $(NAME)
	@$(RM) checker
	@make -C ./libft fclean
	@make -C ./mlx clean
	@echo "$(RED) Delete$(BOLD) $(NAME) $(RESTINT)file $(RESET)"

re : fclean
	@make $(react)
