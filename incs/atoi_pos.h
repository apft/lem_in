/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_pos.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:00:06 by jkettani          #+#    #+#             */
/*   Updated: 2019/05/07 13:17:29 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOI_POS_H
# define ATOI_POS_H

# define ATOI_NBR_IN_STR 			0x1
# define ATOI_NBR_AND_SPACES_ONLY 	0x2

int			atoi_pos(char *str, int *n, unsigned int context);

#endif
