/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongyoki <dongyoki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 08:21:11 by dongyoki          #+#    #+#             */
/*   Updated: 2022/12/12 08:47:46 by dongyoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "libft/libft.h"
// everything
# include <fcntl.h>
// open, close
# include <math.h>
// everything
# include "./mlx/mlx.h"
//everything
# include <stdio.h>
// perror
# include <stdlib.h>
// malloc, free, exit
# include <string.h>
// strerror
# include <unistd.h>
// read, write
# include <errno.h>

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_img
{
	void		*img;
	int			img_width;
	int			img_height;
}				t_img;

typedef struct s_map
{
	char		**map;
	size_t		height;
	size_t		width;
	size_t		collection;
	size_t		player;
	size_t		exit;
	int			start_pos[2];
	int			end_pos[2];
	t_img		img[4];
}				t_map;

typedef struct s_player
{
	t_img		img[52];
	int			pos[2];
	int			direction_state;
	int			jump_state;
	int			move_state;
	int			drop_state;
	int			down_state;
	int			life;
}				t_player;
/*
** img[] : ./assets/player/
** pos[] : start position pos[0] = x, pos[1] = y
** direction_state : right = 0, left = 1
** jump_state : groud = 0, jump = 1
** move_state : stop = 0, movef = 1
** life : die = 0, live = else
*/

typedef struct s_monster
{
	t_img		img[8];
	int			pos[2];
	int			direction_state;
}				t_monster;

/*
** direction_state : right = 0, left = 1
*/

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	t_map		*map;
	t_player	player;
	t_monster	*monster;
	size_t		monster_cnt;
	t_img		collection;
	int			end;
}				t_game;

// test.c
// int				render_next_frame(t_vars *vars);

// image.c
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);

// map
// parse_map.c
int				parse_map(t_game *game, char *map_name);
void			init_map(t_map *map);
void			clear_map(t_map **map);
// map_check.c
size_t			find_width(t_map *map);
void			start_pos(t_map *map);
int				set_map(t_map *map);
int				check_map(t_map *map);
size_t			check_arg(t_map *map);
// make_map.c
int				make_map(t_map *map, char *map_name);
int				del_linefeed(char **line);
int				re_map(t_map *map);

// init
// init_game.c
void			init_game(t_game *game, char *mapfile);
void			map_error(t_game *game);
void			init_game_utils(t_game *game);
// load_player.c
void			load_player(t_game *game);
void			init_player(t_game *game);
// load_monster.c
void			load_monster(t_game *game);
void			load_monster_img(t_game *game, t_monster *p);
size_t			count_monster(t_game *game);
void			pos_monster(t_game *game);
void			init_monster(t_game *game);
// load_map.c
void			load_map(t_game *game);
// load_collention.c
void			load_collection(t_game *game);

// error
// ft_error.c
void			ft_error(int error_no, t_game *game);

// animation
//render_frame.c
int				render_frame(t_game *game);
void			render_map(t_game *game);
void			render_collection(t_game *game);
void			render_gate(t_game *game);
// render_frame_utils.c
void			end_game(t_game *game);
void			put_move_cnt(t_game *game, int move_cnt);
// player_ani.c
void			player_ani(t_game *game);
void			player_ani_1(t_game *game, int *time, int *down, int *jump);
void			player_ani_2(t_game *game, int *time, int *down, int *jump);
// player_ani_utils.c
void			player_ani_idle(t_game *game, int time);
void			player_ani_walk(t_game *game, int time);
void			player_ani_jump(t_game *game, int time);
void			player_ani_down(t_game *game, int down);
// monster_ani.c
void			monster_ani(t_game *game);
void			monster_ani_walk(t_game *game, t_monster monster, int time);
void			monster_change_direction(t_game *game, t_monster *monster);
void			monster_move_right(t_game *game, t_monster *monster);
void			monster_move_left(t_game *game, t_monster *monster);
// eat_collection.c
void			eat_collection(t_game *game);

// hook
// key_hook.c
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				exit_mlx(int keycode, t_game *game);

// move
// player_move.c
int				player_move(t_game *game);
int				move_right(t_game *game);
int				move_left(t_game *game);
// player_jump.c
int				jump(t_game *game);
int				jump_branch(t_game *game, int *i, int x, int y);
int				jump_process(t_game *game, int i);
int				jump_process2(t_game *game, int i);
int				on_ground(t_game *game, int x, int y);
// player_drop.c
int				player_drop(t_game *game);
int				drop_branch(t_game *game, int *i, int x, int y);
int				drop_process(t_game *game, int i);
int				drop_process2(t_game *game, int i);
// player_die.c
void			player_die(t_game *game);

#endif
