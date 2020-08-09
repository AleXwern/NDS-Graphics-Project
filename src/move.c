/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:01:53 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/21 17:06:08 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/value.h"
#include "../includes/wolf.h"

void	move_l(t_wolf *wlf, double olddirx, double oldplanex)
{
	double	sangle = -0.02999550;
	double	cangle = 0.99955003;

	if (wlf->keyleft)
	{
		olddirx = wlf->dirx;
		wlf->dirx = wlf->dirx * cangle - wlf->diry * sangle;
		wlf->diry = olddirx * sangle + wlf->diry * cangle;
		oldplanex = wlf->planex;
		wlf->planex = wlf->planex * cangle - wlf->planey * sangle;
		wlf->planey = oldplanex * sangle + wlf->planey * cangle;
		wlf->sbox += WINX / 64;
	}
}

int		move_lr(t_wolf *wlf)
{
	double	olddirx;
	double	oldplanex;
	double	sangle = 0.02999550;
	double	cangle = 0.99955003;

	if (wlf->keyright)
	{
		olddirx = wlf->dirx;
		wlf->dirx = wlf->dirx * cangle - wlf->diry * sangle;
		wlf->diry = olddirx * sangle + wlf->diry * cangle;
		oldplanex = wlf->planex;
		wlf->planex = wlf->planex * cangle - wlf->planey * sangle;
		wlf->planey = oldplanex * sangle + wlf->planey * cangle;
		wlf->sbox += WINX / 64;
	}
	move_l(wlf, olddirx, oldplanex);
	if (wlf->sbox < 0)
		wlf->sbox += WINX;
	if (wlf->sbox > WINX)
		wlf->sbox -= WINX;
	return (0);
}

int		move_fb(t_wolf *wlf)
{
	if (wlf->keyup)
	{
		if (wlf->map[wlf->flr][(int)(wlf->posy + wlf->diry
				* wlf->movsp)][(int)wlf->posx] <= 1)
			wlf->posy += wlf->diry * wlf->movsp;
		if (wlf->map[wlf->flr][(int)wlf->posy][(int)(wlf->posx
				+ wlf->dirx * wlf->movsp)] <= 1)
			wlf->posx += wlf->dirx * wlf->movsp;
	}
	if (wlf->keydown)
	{
		if (wlf->map[wlf->flr][(int)(wlf->posy - wlf->diry
				* wlf->movsp)][(int)wlf->posx] <= 1)
			wlf->posy -= wlf->diry * wlf->movsp;
		if (wlf->map[wlf->flr][(int)wlf->posy][(int)(wlf->posx
				- wlf->dirx * wlf->movsp)] <= 1)
			wlf->posx -= wlf->dirx * wlf->movsp;
	}
	wlf->aggro += (int)wlf->rng % 7;
	return (0);
}
