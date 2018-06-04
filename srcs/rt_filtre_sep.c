void		img_add_px5(t_win *mlx, int x, int y, unsigned int tr, unsigned int tg, unsigned int tb)
{
	unsigned int	oui;

	oui = 255;
	if (x < X_WIN && y < Y_WIN && x >= 0 && y >= 0)
	{
		if (tb > 255)
			mlx->addr5[(y * mlx->sizeline5 + x * mlx->bpp5 / 8)] = oui;
		else
			mlx->addr5[(y * mlx->sizeline5 + x * mlx->bpp5 / 8)] = tb;

		if (tg > 255)
			mlx->addr5[(y * mlx->sizeline5 + x * mlx->bpp5 / 8) + 1] = oui;
		else
			mlx->addr5[(y * mlx->sizeline5 + x * mlx->bpp5 / 8) + 1] = tg;

		if (tr > 255)
			mlx->addr5[(y * mlx->sizeline5 + x * mlx->bpp5 / 8) + 2] = oui;
		else
			mlx->addr5[(y * mlx->sizeline5 + x * mlx->bpp5 / 8) + 2] = tr;
	}
}



void sepia(t_win *mlx)
{
	int				x2;
	int				y2;
	unsigned int	tr;
	unsigned int	tg;
	unsigned int	tb;

	x2 = 0;
	y2 = 0;
	tr = 0;
	tg = 0;
	tb = 0;
    while (y2 < Y_WIN)
    {
        while (x2 < X_WIN)
        {
            //		r  = img_get_px(mlx, x)
            tr = 0.189 * (unsigned char)mlx->addr3[(y2 * mlx->sizeline3 + x2 * mlx->bpp3 / 8)] +
                0.769 * (unsigned char)mlx->addr3[(y2 * mlx->sizeline3 + x2 * mlx->bpp3 / 8) + 1] +
                    0.393 * (unsigned char)mlx->addr3[(y2 * mlx->sizeline3 + x2 * mlx->bpp3 / 8) + 2];
			tg = 0.168 * (unsigned char)mlx->addr3[(y2 * mlx->sizeline3 + x2 * mlx->bpp3 / 8)] +
                0.686 * (unsigned char)mlx->addr3[(y2 * mlx->sizeline3 + x2 * mlx->bpp3 / 8) + 1] +
                    0.349 * (unsigned char)mlx->addr3[(y2 * mlx->sizeline3 + x2 * mlx->bpp3 / 8) + 2];
			tb = 0.131 * (unsigned char)mlx->addr3[(y2 * mlx->sizeline3 + x2 * mlx->bpp3 / 8)] +
                0.534 * (unsigned char)mlx->addr3[(y2 * mlx->sizeline3 + x2 * mlx->bpp3 / 8) + 1] +
                    0.272 * (unsigned char)mlx->addr3[(y2 * mlx->sizeline3 + x2 * mlx->bpp3 / 8) + 2];
        img_add_px5(mlx, x2, y2, tr, tg, tb);
            x2++;
        }
        x2 = 0;
        y2++;
    }
}
