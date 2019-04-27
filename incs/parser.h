/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:26:34 by apion             #+#    #+#             */
/*   Updated: 2019/04/27 18:04:41 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "env.h"

# define CMD_UNDEF 0x0
# define CMD_START 0x1
# define CMD_END 0x2
# define BLK_ROOM 0x4
# define BLK_TUBE 0x8

int		parser(t_env *env);
int		handle_room(char *line, t_env *env, unsigned int *cmd_flag);
int		handle_tube(char *line, t_env *env, unsigned int *cmd_flag);

int		bake_environment(t_env *env, unsigned int *cmd_flag);
int		array_room_merge_sort(t_room **array, size_t array_size);

#endif
