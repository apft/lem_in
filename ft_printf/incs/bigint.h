/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 12:48:57 by apion             #+#    #+#             */
/*   Updated: 2019/03/18 13:42:31 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_H
# define BIGINT_H

# define BIGINT_N_BLOCKS 520
# define BIGINT_SIZE_BLOCK 32

# define BIGINT_MASK_BLOCK 0xffffffff
# define BIGINT_OVERFLOW 0xf
# define BIGINT_UNDERFLOW 0xf0

typedef struct	s_bigint
{
	unsigned int	length;
	unsigned int	blocks[BIGINT_N_BLOCKS + 1];
}				t_bigint;

int				bigint_is_null(t_bigint *a);
int				bigint_is_overflow(t_bigint *a);
int				bigint_is_underflow(t_bigint *a);
void			print_bigint(t_bigint *value);
void			bigint_init_null(t_bigint *a);
void			bigint_init_int(t_bigint *a, unsigned int n);
long			bigint_cmp(t_bigint *a, t_bigint *b);
void			bigint_copy(t_bigint *dst, t_bigint *src);
void			bigint_add(t_bigint *r, t_bigint *a, t_bigint *b);
void			bigint_add_int(t_bigint *result, t_bigint *a, unsigned int n);
void			bigint_sub(t_bigint *r, t_bigint *a, t_bigint *b);
void			bigint_sub_int(t_bigint *result, t_bigint *a, unsigned int n);
void			bigint_shift_left(t_bigint *r, t_bigint *a, unsigned int shift);
void			bigint_shift_left_self(t_bigint *a, unsigned int shift);
void			bigint_mult_int(t_bigint *result, t_bigint *a, unsigned int n);
void			bigint_mult_by_basis(t_bigint *res, t_bigint *a, t_bigint *b);
void			bigint_mult(t_bigint *result, t_bigint *a, t_bigint *b);

#endif
