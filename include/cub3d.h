/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:05:23 by sdemaude          #+#    #+#             */
/*   Updated: 2024/06/14 15:22:25 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/********************************** INCLUDE ***********************************/

# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "../lib/libft/libft.h"
# include "../lib/libft/gnl/get_next_line.h"
# include "../lib/minilibx/mlx42.h"

/********************************** DEFINE ************************************/

# define SCREEN_WIDTH 320
# define SCREEN_HEIGHT 200
# define MINI_SQ_SIZE 16
# define CB_SIZE 64
# define OFFSET 0.1

//**ERROR**MESSSAGES**
# define ERR_NOT_CUB "The program needs a .cub file as parameter\n"
# define ERR_OPEN "Could not open, check permissions or if is a directory\n"
# define ERR_NO_COMMA "The RGB values need to be separated by commas\n"
# define ERR_NOT_RGB "Invalid RGB value (min : 0, max : 255)\n"
# define ERR_LINE "Incorrect line, must start by F, C, NO, SO, WE, or EA \
(map should be last in file)\n"
# define ERR_MISS "Missing parameters for the map creation\n"
# define ERR_TEX "Texture could not be loaded\n"
# define ERR_MULT "Parameter has already been initialized\n"
# define ERR_NO_MAP "No map in file\n"
# define ERR_INV_CHAR "Invalid character in map (not 1, 0, N, S, W, E or \
space)\n"
# define ERR_PLAYER "Multiple player position\n"
# define ERR_NOT_CLOSE "The map is not closed\n"

/********************************** STRUCT ************************************/

typedef struct s_dir
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;
	bool			set;

}	t_dir;

typedef struct s_alt
{
	int			rgb;
	mlx_image_t	*img;
	bool		set;
}	t_alt;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_point_reel
{
	double	x;
	double	y;
}	t_point_reel;

typedef struct s_player
{
	bool			set;
	t_point			pos_init; // coordonnees initiales dans le tableau
	t_point_reel	pos; // coordonnees reelles en pixels
	char			dir; // N, S, W, E
	double			move_speed;
	double			theta;
	double			rotate_speed;
}	t_player;

typedef struct s_mini
{
	mlx_image_t	*f;
	mlx_image_t	*w;
	mlx_image_t	*p;
}	t_mini;

typedef struct s_map
{
	char		**map;
	t_point		size;
	t_player	player;
	t_mini		mini;
}	t_map;

typedef struct s_param
{
	t_dir	no;
	t_dir	so;
	t_dir	we;
	t_dir	ea;
	t_alt	f;
	t_alt	c;
}	t_param;

typedef struct s_raycasting
{
	double			theta;
	t_point_reel	hor_inter;
	t_point_reel	ver_inter;
	double			len_inter;
}	t_raycasting;

typedef struct s_game
{
	mlx_t			*mlx;
	t_param			param;
	t_map			map;
	t_raycasting	ray;
}	t_game;

/********************************* FUNCTION ***********************************/

//UTILS
bool	ft_isspace(char c);
bool	err_msg(char *str);
bool	ft_strtoi(const char *nptr, int *value);
void	free_tab(char **tab);

//PARSING
bool	parse_file(char *filename, t_game *game);

//PARSING_UTILS
bool	correct_char(char c);
bool	player_pos(t_map *map, char c, int x, int y);

//PARSE_PARAM
bool	parse_param(int fd, t_game *game);

//COLORS
bool	parse_color(char id, char *line, t_param *param);

//TEXTURE
bool	parse_texture(char id, char *line, t_param *param);

//PARSE_MAP
bool	parse_map(int fd, t_game *game);

//DISPLAY_MINI_MAP
void	set_mini_color(t_game *game, int color_f, int color_w, int color_p);
int		get_rgb(int r, int g, int b);
void	set_img(t_game *game);
void	display_mini_map_background(t_game *game);
// bool	display_mini_map(t_game *game);

//DISPLAY_MAP
bool	display_map(t_game *game);

//START_GAME
void	set_start_angle(t_game *game);
void	key_control(void *param);
void	start_game(t_game *game);

//MOVE
void	move_up(t_game *game);
void	move_down(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);

//ROTATE
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);

#endif
