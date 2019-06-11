/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:34:00 by jkettani          #+#    #+#             */
/*   Updated: 2019/06/11 10:41:00 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

# include "env.h"

/*
** Option flags
*/

# define OP_ERR 0x1
# define OP_DEBUG 0x2

typedef struct s_option	t_option;
struct					s_option
{
	char			c;
	unsigned int	flag;

};

int						get_options(int ac, char **av, t_env *env);

#endif
