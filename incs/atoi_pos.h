/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_pos.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:00:06 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/25 13:12:43 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOI_POS_H
# define ATOI_POS_H

# define ATOI_NBR_IN_STR 1
# define ATOI_NBR_AND_SPACES_ONLY 0

int			atoi_pos(char *str, int *n, unsigned int context);

#endif
