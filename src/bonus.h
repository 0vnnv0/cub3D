/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:55:23 by anschmit          #+#    #+#             */
/*   Updated: 2025/07/15 13:32:02 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include <X11/X.h>
# include <X11/keysym.h>

# define TILE_SIZE 32
# define RED    "\033[0;31m"
# define RESET  "\033[0m"
# define WIN_WIDTH 840
# define WIN_HEIGHT 640
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_RIGHT 65363
# define KEY_LEFT 65361
# define ESC 65307
# define SPACE 32

typedef enum e_dir
{
	NO,
	SO,
	WE,
	EA,
	DO,
	DC,
}	t_dir;

typedef enum e_move
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
}	t_move;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*path;
}	t_texture;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			config_count;
	int			header_done;
	int			map_started;
	char		player_dir;
	char		player_x;
	char		player_y;
	int			player_count;
	void		*mlx;
	void		*win;
	int			floor[3];
	int			ceiling[3];
	int			f_set;
	int			c_set;
	t_texture	textures[6];
}	t_map;

typedef struct s_dvec
{
	double	x;
	double	y;
}	t_dvec;

typedef struct s_ivec
{
	int	x;
	int	y;
}	t_ivec;

typedef struct s_screen
{
	int	w;
	int	h;
}	t_screen;

typedef struct s_frame
{
	time_t		time;
	time_t		oldtime;
	double		frametime;
	double		movespeed;
	double		rotspeed;
}	t_frame;

typedef struct s_controls
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		l_arrow;
	int		r_arrow;
	int		esc;
	int		cursor;
}	t_controls;

typedef struct s_pro
{
	void		*mlx;
	void		*win;
	t_screen	screen;
	t_ivec		pos;
	char		dir;
	char		**map;
	t_map		*parser;
	t_controls	key;
}	t_pro;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_graphics
{
	int			num;
	double		wallx;
	t_ivec		tex;
	double		pos;
	double		step;
	t_screen	size;
	int			color;
	int			bytes;
	char		*pxl;
}	t_graphics;

typedef struct s_raycast
{
	t_frame		frame;
	t_dvec		pos;
	t_dvec		dir;
	t_dvec		plane;
	double		camerax;
	t_dvec		raydir;
	t_dvec		sidedist;
	t_dvec		deltadist;
	t_ivec		square;
	t_ivec		step;
	double		perpwalldist;
	int			hit;
	int			side;
	int			lheight;
	int			start;
	int			end;
	t_graphics	tex;
	t_img		buffer;
	t_pro		*game;
}	t_raycast;

/***	MAIN		***/
int		exit_loop(t_pro *game);
int		exit_game(t_pro *game, t_raycast *data, t_map *map);
void	free_splits(char **splits);

/***	RAYCASTING	***/
void	init_raycast(t_raycast *data);
int		start_raycast(t_raycast *data);
void	get_raydir(t_raycast *data, int x);
void	pix_put_img(t_raycast *data, int x, int y, int color);
void	init_starting_point(t_raycast *data);
void	get_deltadist(t_raycast *data);
void	get_sidedist_step(t_raycast *data);
void	perform_dda(t_raycast *data);
void	put_line(t_raycast *data, int x);
void	render_background(t_raycast *data);
void	create_img_buffer(t_raycast *data);
void	render_line(t_raycast *data, int x);
void	get_tex_x(t_raycast *data);
int		rgb_to_int(int *c);

/***	CONTROLS	***/
int		apply_key(t_raycast *data);
void	set_hooks(t_raycast *data);
void	set_speed(t_raycast *data);
int		set_action(int key, t_raycast *data);
int		unset_action(int key, t_raycast *data);
time_t	get_time(void);
time_t	get_current_time(time_t start);
void	rotate(t_raycast *data, double rot);
int		check_path(t_raycast *data, char opt, t_dvec dir);
void	move(t_raycast *data, t_move key, t_dvec dir);

/***	PARSING		***/

//map
int		check_map_name(char *mapname);
int		parse_file(t_map *map, char *filename);
int		process_config_line(t_map *map, char *line);
void	save_player(t_map *map, char position, int i, int j);
void	draw_minimap(t_raycast *data);
void	handle_map_line(t_map *map, char *line);
int		validate_map(t_map *map);
void	check_width(t_map *map, char *line);
void	normalize_map_width(t_map *map);
int		check_map_name(char *mapname);
void	free_map(t_map *map);
int		exit_with_error(t_map *map, char *line, const char *msg);
int		ft_isspace(char c);
int		parse_file(t_map *map, char *filename);
char	*trim_leading_whitespace(char *str);
char	*trim_whitespace(char *str);
int		is_skippable(char *line);
int		ft_isnumber(char *s);
int		check_map2(t_map *map, int i, int j);
int		is_cell_enclosed(t_map *map, int y, int x);
int		check_neighbour(t_map *map, int y, int x, char player);

// inititilisation
void	initialise_game(t_map *map);
void	init_map(t_map *map);
void	init_textures(t_texture *textures);

//colors
int		store_color(t_map *map, int *texture, char *line);
int		process_color(char **colors, int *texture, t_map *map);
void	set_color_flag(t_map *map, int *color);
int		duplicate_color(t_map *map, int *color);
int		check_following_char(t_map *map, char *line);
void	cleanup_colors(char **colors);

//textures
void	load_all_textures(t_map *map, t_pro *game);
int		store_texture_path(t_map *map, t_texture *texture, char *line);
char	*correct_path(char *str);
void	free_img(t_map *map);

//only for testing:
void	render_test(t_map *map);
void	get_map(t_pro *game, char *file);
void	print_data(t_raycast *data);

#endif
