#ifndef CUB3D_H
#define CUB3D_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include <stdbool.h>
# include <stdarg.h>
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

# define TILE_SIZE 32

# define FOV_FACTOR 0.66

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define RESET "\033[0m"

# define BUFFER			1024
# define SCREEN_WIDTH	800
# define SCREEN_HEIGHT	600
# define MOVE_SPEED		0.1
# define ROTATE_SPEED	0.05

# define NORTH	0
# define SOUTH	1
# define WEST	2
# define EAST	3
# define FLOOR	0
# define CEILING	1

typedef struct s_cub_elements
{
	char	*no;// Path to NO texture
	char	*so;// Path to SO texture
	char	*we;// Path to WE texture
	char	*ea;// Path to EA texture
	char	*f;	// Floor color string
	char	*c;	// Ceiling color string
	char	**map; // Map grid (NULL if not set)
	int	 map_started;
}				t_cub_elements;

/* 🎨 Colors */
typedef struct s_color
{
	char	*color_str;	// color string
	char	*texture;
	int		r;
	int		g;
	int		b;
	int		mode; //1:color   2:texture
}			t_color;

/* 📌 Textures */
typedef struct s_texture
{
	char	*path;
	void	*img;	   // Pointer to MiniLibX image
	char	*addr;	  // Image data address
	int	 	width;	  // Image width
	int	 	height;	 // Image height
	int	 	bpp;		// Bits per pixel
	int	 	line_len;   // Bytes per line
	int	 	endian;	 // Endian format
}			t_texture;

/* 🚶 Player */
typedef struct s_player
{
	char 	*ini_dir;
	double	x;		  // Player's X position
	double	y;		  // Player's Y position
	double	dir_x;	  // Direction vector X
	double	dir_y;	  // Direction vector Y
	double	plane_x;	// Camera plane X (for FOV)
	double	plane_y;	// Camera plane Y (for FOV)
	int		move_x;
	int		move_y;
	int		moved;
	int		rotate;
} t_player;

typedef struct	s_ray 
{
	double	dirx; //ray direction
	double	diry;
	int		mapx;	//current map cell
	int		mapy;
	double	side_distx; //distance to next side
	double	side_disty;
	double	deltadistx; //distance between sides
	double	deltadisty;
	double	walldist; //distance to wall
	int		stepx;	//step direction
	int		stepy;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
}				t_ray;
/* 🎮 Game Structure */

typedef struct s_game
{
	int	 	bpp;		// Bits per pixel
	int	 	line_len;   // Bytes per line
	int	 	endian;	 // Endian format
	char			**map;			  // 2D array for the map
	int				width;			   // Map width
	int				height;	
	int				last_mouse_x;
	int				key;
	int				map_size;		  // Map height
	void			*mlx;				// MiniLibX connection
	void			*win;				// Window pointer
	void			*img;				
	void			*addr;
	t_player		player;			  // Player data
	t_texture	  	textures[4];		 // Textures: [0]NO, [1]SO, [2]EA, [3]WE
	t_color			color[2];		 // Floor RGB color
	t_ray		ray;
}				t_game;

int		validate_file(const char *filename);
int		pars_file(const char *filename, t_game *game, char** argv);
int		validate_cub_elements(t_game *game);
int		is_valid_texture_path(char *path);
int		validate_colors(t_color *color);
int		is_valid_color_texture(t_color *color);
int		is_map_closed_and_accessible(t_game *game, char **map, \
			int height, int width);
void	free_two_dim(char **arr);
int		two_dim_len(char **arr);
void	cal_map_dim(t_game **game);
int		free_game(t_game *game);
void	print_error(const char *format, ...);
void	create_window(t_game *game);
void	init_game(t_game *game);
int		press_key(int keycode, t_game *game);
int		close_window(t_game *game);
void	move_player(int keycode, t_game *game);
void	cast_rays(t_game *game);
int		render(t_game *game);
void	init_win(t_game *game);
int		case_one(t_game *game, char **map, int y);
int		case_two(t_game *game, char **map, int y);
int		case_three(t_game *game, char **map, int x);
int		case_four(t_game *game, char **map, int x);
int		case_five(t_game *game, char **map, int x);
int		first_pos_row(char *line);
int		last_pos_row(char *line);
int		first_pos_col(char **map, int col);
int		last_pos_col(char **map, int col, int height);
void	init_mlx_ray(t_ray *ray, t_game *game, int x);
void	print_struct(t_game *game);
void	calculate_wall_height(t_ray *ray, t_game *game);
void	perform_dda(t_ray *ray, t_game *game);
void	calculate_step(t_ray *ray, t_game *game);
void	load_player(t_game *game);
void	set_dir(t_game *game);
void	init_mlx_texture(t_game *game, int index, char *path);
int		select_texture(t_ray *ray);


#endif
