/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fonction.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthomas <juthomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 08:04:02 by juthomas          #+#    #+#             */
/*   Updated: 2018/04/08 08:25:31 by juthomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_FONCTION_H
# define RT_FONCTION_H
# include "./rt.h"


int		exit_error(int error);
int		rt_parser_no_space(char *str, int i);
int		rt_parser_balise_name(char *str, int i, int *state);
int		rt_parser_go_next_number(char *str, int i);
int		rt_parser_stock_vec(char *str, t_vec *vec, int *nb, int dec);
int		rt_parser_is_correct(char *str, char *ac, int len);
int		rt_parser_stock_color_norm(int *tmp, t_vec *vec, unsigned int color, char *str);
int		rt_parser_stock_color(char *str, t_vec *vec, int *nb, int dec);
int		rt_parser_go_next_number_2(char *str, int i);
int		rt_parser_stock_number(char *str, float *nu, int *nb, int dec);
int		stock_triangle(t_triangle *triangle, char *str, int *nb);
int		stock_cycon(t_cycon *cycon, char *str, int *nb);
int		stock_plan(t_plan *plan, char *str, int *nb);
int		stock_disque(t_disque *disque, char *str, int *nb);
int		stock_spher(t_spher *spher, char *str, int *nb);
int		stock_lpsher(t_lspher *spher, char *str, int *nb);
int		stock_camera(t_cam *cam, char *str, int *nb);
int		stock_lproj_norm(t_lproj *proj, char *str, int *nb);
int		stock_lproj(t_lproj *proj, char *str, int *nb);
void	rt_parser_objtype_lspher_setup(t_lspher *spher);
void	rt_parser_objtype_camera_setup(t_cam *cam);
void	rt_parser_objtype_lproj_setup(t_lproj *proj);
char	rt_parser_objtype_lspher(char *str, void **addr, char type);
void	rt_parser_objtype_camera(char *str, t_cam *cam, char type);
char	rt_parser_objtype_lproj(char *str, void **addr, char type);
void	rt_parser_objtype_spher_setup(t_spher *spher);
void	rt_parser_objtype_triangle_setup(t_triangle *triangle);
void	rt_parser_objtype_cycon_setup(t_cycon *cycon);
void	rt_parser_objtype_disque_setup(t_disque *disque);
void	rt_parser_objtype_plan_setup(t_plan *plan);
void	rt_parser_objtype_triangle_norm(t_triangle *triangle);
char	rt_parser_objtype_triangle(char *str, void **addr, char type);
char	rt_parser_objtype_cycon(char *str, void **addr, char type);
char	rt_parser_objtype_plan(char *str, void **addr, char type);
char	rt_parser_objtype_disque(char *str, void **addr, char type);
char	rt_parser_objtype_spher(char *str, void **addr, char type);
char	rt_parser_objtype(char *str);
char	rt_parser_camera(char *str);
t_type	*rt_parser_objtype_done(char *str, char type);
t_type	*rt_parser_lobjtype_done(char *str, char type);
t_cam	*rt_parser_camera_done(char *str, char type);
int		rt_parser_state(char *str, int state, int i);
void	ft_lstdellast(t_list **list);
t_list	*ft_lstnew2(void *content, size_t content_size, int *vo);
void	rt_parser_stock_win(char *str, t_win *win);
void	rt_parser_main_setup(int argc, char **argv, t_parser *parser, t_win *win);
t_list	*rt_parser_main_end(t_parser *parser, t_list *list, t_win *win);
void	rt_parser_main_while(t_parser *parser, t_cam **cam, t_list *list, t_win *win);
t_list	*rt_parser_main(int argc, char **argv, t_cam **cam, t_win *win);



#endif















