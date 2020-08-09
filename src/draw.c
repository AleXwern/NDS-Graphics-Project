/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:38:13 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/21 17:09:33 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"
#include "../includes/value.h"

void	draw_sky(t_wolf *wlf, int scan)
{
	int		i;

	if (scan >= WINX)
		scan -= WINX;
	i = 0;
	while (i < wlf->start)
	{
		wlf->VRAMMain[WINX * i + wlf->x] = ARGB16(1, 4, 14, 31);
		i++;
	}
}

void	draw_stripe(t_wolf *wlf)
{
	while (wlf->start <= wlf->end)
	{
		wlf->VRAMMain[WINX * wlf->start + wlf->x] = wlf->testcolor;
		wlf->start++;
	}
}

void	wall_stripe(t_wolf *wlf)
{
	//wlf->testcolor = 0x22a800;
	draw_sky(wlf, wlf->sbox + wlf->x);
	draw_stripe(wlf);
	draw_floor(wlf, wlf->start);
}
