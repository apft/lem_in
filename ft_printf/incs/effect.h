/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 16:57:23 by apion             #+#    #+#             */
/*   Updated: 2019/03/26 11:29:06 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EFFECT_H
# define EFFECT_H

# define CURSOR_ON_TOP		"\x1b[;H"
# define CLEAR_SCREEN		"\x1b[2J" CURSOR_ON_TOP

# define RESET				"\x1b[0m"

# define BOLD				"\x1b[1m"
# define DIM 				"\x1b[2m"
# define ITALIC       		"\x1b[3m"
# define UNDERLINE    		"\x1b[4m"
# define REVERSE_VIDEO		"\x1b[7m"
# define CROSSED			"\x1b[9m"

# define BOLD_OFF			"\x1b[22m"
# define DIM_OFF			"\x1b[22m"
# define ITALIC_OFF			"\x1b[23m"
# define UNDERLINE_OFF		"\x1b[24m"
# define REVERSE_OFF		"\x1b[27m"
# define CROSSED_OFF		"\x1b[29m"

# define BLACK 				"\x1b[30m"
# define RED   				"\x1b[31m"
# define GREEN 				"\x1b[32m"
# define YELLOW 			"\x1b[33m"
# define BLUE   			"\x1b[34m"
# define MAGENTA			"\x1b[35m"
# define CYAN 				"\x1b[36m"
# define WHITE				"\x1b[37m"

# define DEFAULT_FG			"\x1b[39m"

# define BLACK_BG			"\x1b[40m"
# define RED_BG				"\x1b[41m"
# define GREEN_BG			"\x1b[42m"
# define YELLOW_BG			"\x1b[43m"
# define BLUE_BG			"\x1b[44m"
# define MAGENTA_BG			"\x1b[45m"
# define CYAN_BG			"\x1b[46m"
# define WHITE_BG			"\x1b[47m"

# define DEFAULT_BG			"\x1b[49m"

# define LIGHT_BLACK		"\x1b[90m"
# define LIGHT_RED			"\x1b[91m"
# define LIGHT_GREEN		"\x1b[92m"
# define LIGHT_YELLOW		"\x1b[93m"
# define LIGHT_BLUE			"\x1b[94m"
# define LIGHT_MAGENTA		"\x1b[95m"
# define LIGHT_CYAN			"\x1b[96m"
# define LIGHT_WHITE		"\x1b[97m"

# define LIGHT_BLACK_BG		"\x1b[100m"
# define LIGHT_RED_BG		"\x1b[101m"
# define LIGHT_GREEN_BG		"\x1b[102m"
# define LIGHT_YELLOW_BG	"\x1b[103m"
# define LIGHT_BLUE_BG		"\x1b[104m"
# define LIGHT_MAGENTA_BG	"\x1b[105m"
# define LIGHT_CYAN_BG		"\x1b[106m"
# define LIGHT_WHITE_BG		"\x1b[107m"

typedef struct	s_effect
{
	char	*effect;
	char	*sgr;
}				t_effect;

#endif
