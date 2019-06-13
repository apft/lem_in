/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 16:48:58 by apion             #+#    #+#             */
/*   Updated: 2019/04/28 16:24:14 by pion             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "utils.h"
#include "effect.h"
#include "handlers.h"

t_effect		g_effect[] =
{
	{"reset", RESET},
	{"eoc", RESET},
	{"nc", RESET},
	{"", RESET},

	{"b", BOLD},
	{"bold", BOLD},
	{"dim", DIM},
	{"italic", ITALIC},
	{"u", UNDERLINE},
	{"underline", UNDERLINE},
	{"reverse", REVERSE_VIDEO},
	{"crossed", CROSSED},
	{"strike", CROSSED},

	{"\\b", BOLD_OFF},
	{"/b", BOLD_OFF},
	{"reset_bold", BOLD_OFF},
	{"clear_bold", BOLD_OFF},
	{"end_bold", BOLD_OFF},
	{"reset_dim", DIM_OFF},
	{"clear_dim", DIM_OFF},
	{"end_dim", DIM_OFF},
	{"reset_italic", ITALIC_OFF},
	{"clear_italic", ITALIC_OFF},
	{"end_italic", ITALIC_OFF},
	{"\\u", UNDERLINE_OFF},
	{"/u", UNDERLINE_OFF},
	{"reset_underline", UNDERLINE_OFF},
	{"clear_underline", UNDERLINE_OFF},
	{"end_underline", UNDERLINE_OFF},
	{"reset_reverse", REVERSE_OFF},
	{"clear_reverse", REVERSE_OFF},
	{"end_reverse", REVERSE_OFF},
	{"reset_crossed", CROSSED_OFF},
	{"clear_crossed", CROSSED_OFF},
	{"end_crossed", CROSSED_OFF},

	{"\\fg", DEFAULT_FG},
	{"/fg", DEFAULT_FG},
	{"no_fg", DEFAULT_FG},
	{"\\bg", DEFAULT_BG},
	{"/bg", DEFAULT_BG},
	{"no_bg", DEFAULT_BG},

	{"black", BLACK},
	{"black_fg", BLACK},
	{"red", RED},
	{"red_fg", RED},
	{"green", GREEN},
	{"green_fg", GREEN},
	{"yellow", YELLOW},
	{"yellow_fg", YELLOW},
	{"blue", BLUE},
	{"blue_fg", BLUE},
	{"magenta", MAGENTA},
	{"magenta_fg", MAGENTA},
	{"cyan", CYAN},
	{"cyan_fg", CYAN},
	{"white", WHITE},
	{"white_fg", WHITE},
	{"light_black", LIGHT_BLACK},
	{"light_black_fg", LIGHT_BLACK},
	{"light_red", LIGHT_RED},
	{"light_red_fg", LIGHT_RED},
	{"light_green", LIGHT_GREEN},
	{"light_green_fg", LIGHT_GREEN},
	{"light_yellow", LIGHT_YELLOW},
	{"light_yellow_fg", LIGHT_YELLOW},
	{"light_blue", LIGHT_BLUE},
	{"light_blue_fg", LIGHT_BLUE},
	{"light_magenta", LIGHT_MAGENTA},
	{"light_magenta_fg", LIGHT_MAGENTA},
	{"light_cyan", LIGHT_CYAN},
	{"light_cyan_fg", LIGHT_CYAN},
	{"light_white", LIGHT_WHITE},
	{"light_white_fg", LIGHT_WHITE},

	{"black_bg", BLACK_BG},
	{"red_bg", RED_BG},
	{"green_bg", GREEN_BG},
	{"yellow_bg", YELLOW_BG},
	{"blue_bg", BLUE_BG},
	{"magenta_bg", MAGENTA_BG},
	{"cyan_bg", CYAN_BG},
	{"white_bg", WHITE_BG},
	{"light_black_bg", LIGHT_BLACK_BG},
	{"light_red_bg", LIGHT_RED_BG},
	{"light_green_bg", LIGHT_GREEN_BG},
	{"light_yellow_bg", LIGHT_YELLOW_BG},
	{"light_blue_bg", LIGHT_BLUE_BG},
	{"light_magenta_bg", LIGHT_MAGENTA_BG},
	{"light_cyan_bg", LIGHT_CYAN_BG},
	{"light_white_bg", LIGHT_WHITE_BG}
};

static int	effect_match(const char **effect, char *expected)
{
	int		i;

	i = 1;
	if (!effect || !*effect || !expected)
		return (0);
	while (**effect && *(*effect + i) != '}' && *expected
			&& *(*effect + i) == *expected++)
		++i;
	if (*(*effect + i) == '}' && !*expected)
	{
		*effect += i;
		return (1);
	}
	return (0);
}

int			apply_effect(const char **effect, t_specs *specs, char *str)
{
	int		size;
	int		i;

	specs->type ^= STRING;
	size = sizeof(g_effect) / sizeof(t_effect);
	i = 0;
	while (i < size)
	{
		if (effect_match(effect, g_effect[i].effect))
			return (handle_str_conv(g_effect[i].sgr, specs, str));
		++i;
	}
	specs->type ^= STRING | CHAR;
	return (handle_char_conv('{', specs, str));
}

int			clear_screen(va_list ap, t_specs *specs, char *str)
{
	(void)ap;
	return (handle_str_conv(CLEAR_SCREEN, specs, str));
}
