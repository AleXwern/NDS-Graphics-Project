/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:01:06 by anystrom          #+#    #+#             */
/*   Updated: 2020/07/21 17:06:59 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"
#include "../includes/value.h"

volatile int frame = 0;
int	done = 0;
t_wolf	*cpwlf;

void	key_defaults(t_wolf *wlf)
{
	wlf->keydown = 0;
	wlf->keyleft = 0;
	wlf->keyright = 0;
	wlf->keyup = 0;
}

void	wolf_default(t_wolf *wlf)
{
	wlf->flr = 0;
	wlf->posx = 2.5;
	wlf->posy = 2.5;
	wlf->dirx = 1.0;
	wlf->diry = 0.0;
	wlf->planex = 0.0;
	wlf->planey = 0.66;
	wlf->rotsp = 0.03;
	wlf->movsp = 0.13;
	wlf->rng = 0.0;
	wlf->texbool = 1;
	wlf->sbox = WINX / 2;
	wlf->mxflr--;
	wlf->cur = 0;
	wlf->sel = -1;
	wlf->plr = 0;
	wlf->plrck = 0;
	wlf->cycle = &render;
	wlf->syssmg[0] = ft_strdup("You encountered a strong beast!");
	wlf->syssmg[1] = ft_strdup("What will you do?");
	key_defaults(wlf);
}

void	error_out(char *msg, t_wolf *wlf, int y)
{
	iprintf("\x1b[9;0HFeedback: %s",msg);
	if (!ft_strcmp(msg, WLF_ERROR))
		exit(0);
	if (!ft_strcmp(msg, FLR_ERROR))
		wlf->mxflr = wlf->flr - 49;
	exit(0);
	/*
	if (wlf->syssmg[0])
	{
		free(wlf->syssmg[0]);
		free(wlf->syssmg[1]);
	}
	if (wlf->gfx)
		destroy_gfx(wlf, -1);
	if (y > 0)
		free_layer(wlf, wlf->flr, -1, y);
	if (wlf->map)
		free_map(wlf, -1, -1);
	exit(0);*/
}

void	setup(t_wolf *wlf)
{
	int		key;

	wolf_default(wlf);
	if (wlf->map[0][(int)wlf->posy][(int)wlf->posx] != 1)
		error_out(SPW_ERROR, wlf, 0);
	while (1)
	{
		scanKeys();
		key = keysDown();
		if (key)
			key_hold(key, wlf);
		iprintf("\x1b[11;0HKeyD = %d",key);
		key = keysUp();
		if (key)
			key_release(key, wlf);
		iprintf("\x1b[12;0HKeyU = %d",key);
		iprintf("\x1b[13;0HMatrix\nPos %f %f\nDir %f %f",wlf->posx,wlf->posy,wlf->dirx,wlf->diry);
		move(wlf);
		render(wlf);
		iprintf("\x1b[10;0HFrame = %d",frame);
		done = 1;
		swiWaitForVBlank();
	}
}

void Vblank()
{
	frame++;
	done = 0;
}

int		main(int ac, char **av)
{
	t_wolf	*wlf;

	if (!(wlf = (t_wolf*)malloc(sizeof(t_wolf))))
		error_out(WLF_ERROR, wlf, 0);
	ft_bzero(wlf, sizeof(t_wolf));
	wlf->tile = 3;
	wlf->mxflr = 1;
	wlf->winb = 1;
	videoSetMode(MODE_5_2D);
	//videoSetModeSub(MODE_5_2D);
	vramSetBankA(VRAM_A_MAIN_BG);
	//vramSetBankC(VRAM_C_SUB_BG);
	wlf->bgMain = bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0,0);
	//wlf->bgSub = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0,0);
	wlf->VRAMMain = bgGetGfxPtr(wlf->bgMain);
	consoleDemoInit();
	//u16* videoMemorySub = bgGetGfxPtr(bgSub);
	cpwlf = wlf;
	irqSet(IRQ_VBLANK, Vblank);
	iprintf("\x1b[10;0HFrame = %d",frame);
	comp_map(wlf, av[3]);
	//comp_gfx(wlf, 0);
	setup(wlf);
	return (0);
}
