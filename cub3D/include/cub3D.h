/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejikim <heejikim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:23:04 by dongyoki          #+#    #+#             */
/*   Updated: 2023/02/07 16:34:19 by heejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <math.h>
// everything
# include <fcntl.h>
// open, close
# include <unistd.h>
// read, write
# include <stdio.h>
// printf, perror
# include <stdlib.h>
// malloc, free, exit
# include <string.h>
// strerror
# include <errno.h>

# define MALLOC_ERR 100
# define MAP_ERR 101
# define FILE_ERR 102
# define NOFILE_ERR 103
# define MLX_ERR 104

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.02
# define DOOR_SPEED 0.05

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_F 3
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define VERTICAL 0
# define HORIZONTAL 1

typedef struct s_map_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_map_img;

typedef struct s_img
{
	void			*img;
	char			*img_ptr;
	int				img_width;
	int				img_height;
	int				bit_per_pixel;
	int				size_line;
	int				endian;
}					t_img;

typedef struct s_floor
{
	int				r;
	int				g;
	int				b;
	int				color;
}					t_floor;

typedef struct s_door
{
	int				x;
	int				y;
	int				dir;
	double			open_speed;
	double			open_state;
	struct s_door	*next;
}					t_door;

typedef struct s_map
{
	char			**map;
	t_door			*doors;
	t_img			wall[4];
	t_img			door_img;
	t_floor			floor[2];
	char			dir;
	t_map_img		map_img;
}					t_map;

typedef struct s_pos
{
	double			x;
	double			y;
	double			z;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			dx;
	double			dy;
	double			rotate;
}					t_pos;

typedef struct s_ray
{
	int				x;
	double			cam_x;
	double			ray_x;
	double			ray_y;
	int				map_x;
	int				map_y;
	double			delta_x;
	double			delta_y;
	double			dist_x;
	double			dist_y;
	int				step_x;
	int				step_y;
	int				wall_side;
}					t_ray;

typedef struct s_draw_info
{
	int				line_height;
	int				wall_start;
	int				wall_end;
	int				wall_width;
	double			wall_x;
	double			wall_y;
	double			step;
}					t_draw_info;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	t_map			map;
	t_pos			pos;
	int				keydown;
	t_map_img		minimap;
}					t_game;

// get_next_line_cub3D.c
char				*gnl_cub(int fd);

// map_parse.c
void				map_parse(t_game *game, int ac, char **av);
void				minimap_init(t_game *game);
int					get_fd(int ac, char **av);
void				check_path(char *str);

// make_map_img.c
void				make_map_img(t_game *game);
void				get_wh(char **map, int *w, int *h);
void				make_clean(t_map_img *map_img, int w, int h);

// put_pixel.c
void				put_pixel_to_map(t_map_img *map_img, char **map);
void				put_blk(t_map_img *map_img, int y, int x);
void				put_back(t_map_img *map_img, int y, int x);
void				put_h(t_map_img *map_img, int y, int x);
void				put_v(t_map_img *map_img, int y, int x);

// load_av.c
void				load_av(t_game *game, int fd);
t_img				load_img(t_game *game, char *path);
t_floor				load_color(char **color);

// load_av_asset.c
void				check_seq(t_game *game, char *line, int ck[6]);
int					check_direction(t_game *game, char *line, int ck[6]);
int					check_floor(t_game *game, char *line, int ck[6]);

// load_wall_utils.c
void				free_color(char **color);
void				trim_color(char **color);
int					find_index_cub(char *s);

// map_parse_utils.c
int					is_empty_str(char *s);
int					is_three(char **color);
int					str_digit(char **color);
int					atoi_cub(char *s);

// make_map.c
void				make_map(t_game *game, int fd);
void				put_map(t_game *game, char *line);
void				remove_empty(t_game *game);

// check_map.c
void				check_map(t_game *game);
void				set_pos(t_game *game, char pos, int x, int y);

// check_map_utils.c
int					ft_is_whitespace(char c);
void				is_open(char **map, int x, int y);
int					check_char(char **map, int x, int y, int *player);

// doors.c
t_door				*get_door(t_game *game, int x, int y);
t_door				*get_door_by_ray(t_game *game, t_ray *ray);
void				update_doors(t_game *game);
void				proc_door(t_game *game, int x, int y);
void				key_f(t_game *game);

// game_control.c
int					key_release(int key, void *game_ptr);
int					is_empty(t_game *game, int x, int y);
int					game_loop(void *game_ptr);

// key_press.c
void				key_w(t_game *game);
void				key_s(t_game *game);
void				key_a(t_game *game);
void				key_d(t_game *game);
int					key_press(int key, void *game_ptr);

// ray_calc.c
void				calc_dist(t_game *game, t_ray *ray);
t_ray				init_ray(t_game *game, int x);
void				find_wall(t_game *game, t_ray *ray);
void				calc_line_info(t_game *game, t_ray *ray, t_draw_info *info,
						double wall_dist);
t_draw_info			calc_draw_info(t_game *game, t_ray *ray);

// ray_cast.c
void				ray_draw(t_game *game, t_ray *ray, t_draw_info *info,
						t_img *img);
void				ray_cast(t_game *game);

// ray_utils.c
int					get_color(t_img *img, int col, int row);
void				set_color(t_img *img, int col, int row, int color);
double				ft_absd(double n);
t_img				create_img(t_game *game);
int					ft_dir(double d);

// render_doors.c
int					get_door_color(t_game *game, t_ray *ray, double wall_x,
						double wall_y);
void				draw_door(t_game *game, t_ray *ray, t_draw_info *info,
						t_img *img);
t_door				*draw_if_door(t_game *game, t_ray *ray, t_img *img);
void				draw_doors(t_game *game, t_ray *ray, t_img *img);

// ft_error.c
int					exit_game(t_game *game);
void				_error(int err);

// draw_minimap.c
void				draw_minimap(t_game *game);
void				put_pixel(t_map_img *map, t_map_img *mini, double x,
						double y);
void				put_player(t_map_img *mini);
void				put_dir(t_game *game);

// draw_minimap_door.c
void				change_door(t_map *map);
void				change_map_door_v(t_map_img *map, int y, int x);
void				change_map_door_h(t_map_img *map, int y, int x);

// pixel_utils.c
void				pixel_put(t_map_img *mini, int x, int y, int color);
int					pixel_get(t_map_img *mini, int x, int y);

#endif
