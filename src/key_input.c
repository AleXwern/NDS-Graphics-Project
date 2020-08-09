/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:07:30 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/21 16:02:24 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/value.h"
#include "../includes/wolf.h"

int				key_hold(int key, t_wolf *wlf)
{
	if (key == KEY_START)
		error_out(FINE, wlf, 0);
	if (key == KEY_LEFT)
		wlf->keyleft = 1;
	if (key == KEY_RIGHT)
		wlf->keyright = 1;
	if (key == KEY_UP)
		wlf->keyup = 1;
	if (key == KEY_DOWN)
		wlf->keydown = 1;
	return (0);
}

int				key_release(int key, t_wolf *wlf)
{
	//if (key == KEY_T)
	//	wlf->texbool = (wlf->texbool * wlf->texbool) - 1;
	if (key == KEY_A)
		interact(wlf);
	if (key == KEY_LEFT)
		wlf->keyleft = 0;
	if (key == KEY_RIGHT)
		wlf->keyright = 0;
	if (key == KEY_UP)
		wlf->keyup = 0;
	if (key == KEY_DOWN)
		wlf->keydown = 0;
	return (0);
}

int				x_press(t_wolf *wlf)
{
	error_out(FINE, wlf, 0);
	return (0);
}

int				move(t_wolf *wlf)
{
	if (wlf->flrchange > 0)
		wlf->flrchange--;
	if (wlf->keydown || wlf->keyup)
	{
		move_fb(wlf);
		wlf->rng += (wlf->posx + wlf->posy) * 10;
		if (wlf->rng < 0)
			wlf->rng = 35565;
		else if (wlf->rng > 35565)
			wlf->rng = 0;
	}
	if (wlf->keyleft || wlf->keyright)
		move_lr(wlf);
	wlf->cycle(wlf);
	return (0);
}
