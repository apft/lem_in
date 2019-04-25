/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:26:34 by apion             #+#    #+#             */
/*   Updated: 2019/04/25 15:28:13 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "env.h"

int		parser(t_env *env);
int		handle_room_or_tube(char *line, t_env *env, unsigned int *cmd_flag);
int		handle_room(char *line, t_env *env, unsigned int *cmd_flag);
int		handle_tube(char *line, t_env *env, unsigned int *cmd_flag);

#endif
