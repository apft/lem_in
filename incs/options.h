/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:34:00 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/07 16:04:03 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

# include "env.h"

# define OP_ERR 0x1
# define OP_DEBUG 0x2

int		get_options(int ac, char **av, t_env *env);

#endif
