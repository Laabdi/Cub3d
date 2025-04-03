/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:44:41 by iouhssei          #+#    #+#             */
/*   Updated: 2025/04/02 06:58:38 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
#define CUBE3D_H

#include "../libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <math.h>
// #include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

//----------------------------==----------//
//-----------MACROS-------====------------//
//--------------==------------------------//

// colors

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define ORANGE "\033[0;36m"
#define RESET "\033[0m"

// keys

#define ESC 65307
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100
#define UP 126
#define DOWN 125
#define PI 3.14159265359
#define M_PI_2 1.57079632679489661923
#define LEFT_KEY 65361
#define RIGHT_KEY 65363
#define S_RES 800
#define FOV PI / 3

// Struct (raycaster)
typedef struct s_garbage_node
{
	void *ptr;
	struct s_garbage_node *next;
} t_garbage_node;

typedef struct s_garbage_collector
{
	t_garbage_node *head;
} t_garbage_collector;

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

typedef struct s_cube
{
	void *mlx;
	void *mlx_window;
	t_garbage_collector *gc;
	t_data *data;
	int map[10][10];
	int p_x;
	int p_y;
	double angle;
} t_cube;

// FUNCTIONS :

//----INITIALIZATION-==---------------//
//------------------=--==-------------//
//----PARSING------------==-----------//
//----PARSING------------==-----------//
typedef struct s_rgb
{
	int r;
	int g;
	int b;
	char *rgb_in_hex;
} t_rgb;

typedef struct s_map
{
	char **map;
	char *se;
	char *no;
	char *we;
	char *ea;
	char *floor_color;
	char *celling_color;
	int is_valid;
	int map_height;
	int map_width;
	double start_angle;
	int x;
	int y;
	t_rgb f_rgb;
	t_rgb c_rgb;
} t_map;

void print_2d(char **s);
void free_map_textures(t_map *map);
void free_map_struct(t_map *map);
int handle_errors(int err_code);

/* parse.c */
int check_file_name(char *s);
int check_texture(t_map *map);
size_t ft_strlenewline(char *s);
int check_virgul(char *av);
char *get_file_in_char(char *av);
int empty_map(t_map *map);

/* parse_helpers1.c */
void free_all_lines(char **lines);
void alloc_clean_lines(char **all_line,
					   char ***clean_line, int count);
char **count_and_alloc_lines(char **all_line,
							 int *count);
char **split_file(char *s);
void *free_clean_lines(char **clean_line, int j);

/* parse_helpers2.c */
char *parse_line(char *s, char *to_trim);
void free_rgb_arrays(char **floor_rgb,
					 char **celling_rgb);
void fill_rgb(t_map *map);
int is_valid_rgb(int r, int g, int b);
int check_rgbs(t_map *map);

/* parse_helpers3.c */
void parse_texture(t_map *map, char *line,
				   char *identifier, char **dest);
void fill_struct_helper(t_map *map, char **file);
void fill_struct(t_map *map, char *av);
void initiliase_struct(t_map *map, char *av);

/* parse_map1.c */
int check_map_line(char *s);
void count_map_lines(char **all_file, int *lines,
					 int *map_started);
void fill_map_array(t_map *map, char **all_file,
					int lines);
void get_map_into2darray(t_map *map, char *av);
int count_double_char(char **s);
/*parse_helpers.c*/

void count_w_h(t_map *map);
void get_x_y(t_map *map);
void check_direction(t_map *map);

/* parse_map2.c */
int check_borders(char *s);
int check_top_and_bottom(char *s);
int check_line_endings(char **map, int i,
					   int current_len, int prev_len);
int check_map_steps(t_map *map);
int check_surroundings(t_map *map, int i, int j,
					   int size);

/* parse_map3.c */
int check_map_content(t_map *map, int size);
int check_map(t_map *map);
int count_till_newline(char *s);
int get_bigger_mapline(char **s);
int get_line_of_biggervalue(char **s);
int check_map_content(t_map *map, int size);
//-------------------------===--------//

//--------------------------------------//
//----RAY-CASTER------------------------//
//--------------------------------------//
//----DRAWING---------------------------//

void print_error(char *str);
void init_mlx(t_cube *cube, t_data *data);
t_garbage_collector *init_garbage_collector(void);
void add_garbage(t_garbage_collector *gc, void *ptr);
void *free_all(t_garbage_collector *gc);
void *tracked_malloc(t_garbage_collector *gc,
					 size_t size);
void my_mlx_pixel_put(t_data *data, int x, int y,
					  int color);
int handle_keypress(int keycode, t_cube *cube,
					t_map *map);
void cast_away(t_cube *cube);
void draw_line(t_cube *cube, int x1, int y1,
			   double angle, int length, int color);
void draw_mini_map(t_cube *cube);
void cast_away_minirays(t_cube *cube);
#endif
