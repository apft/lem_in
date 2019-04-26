/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:09:34 by apion             #+#    #+#             */
/*   Updated: 2019/04/26 10:18:52 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "error.h"
#include "ft_printf.h"

#define OPTION_ERROR	1

static void	custom_print_error(char *error_msg)
{
	ft_dprintf(STDERR_FILENO, "ERROR");
	if (OPTION_ERROR)
		ft_dprintf(STDERR_FILENO, ": %s", error_msg);
	ft_dprintf(STDERR_FILENO, "\n");
}

static char	*custom_strerror(int error)
{
	(void)error;
	return ("your error message here");
}

void		print_error(int error)
{
	char	*error_msg;

	if (error > 0)
		error_msg = strerror(error);
	else
		error_msg = custom_strerror(error);
	custom_print_error(error_msg);
}
