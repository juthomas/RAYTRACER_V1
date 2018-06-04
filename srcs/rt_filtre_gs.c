void		img_add_px4(t_win *mlx, unsigned int color, int x, int y)
{

	if (x < X_WIN && y < Y_WIN && x >= 0 && y >= 0)
	{
		mlx->addr4[(y * mlx->sizeline4 + x * mlx->bpp4 / 8)] = color;
		mlx->addr4[(y * mlx->sizeline4 + x * mlx->bpp4 / 8) + 1] = color;
		mlx->addr4[(y * mlx->sizeline4 + x * mlx->bpp4 / 8) + 2] = color;
	}
}

void grayscale(t_win *mlx)
{
	unsigned int	color;
	int				x2;
	int				y2;

	x2 = 0;
	y2 = 0;
	color = 0;
    while (y2 < Y_WIN)
    {
        while (x2 < X_WIN)
        {
            color = 0;
            color = ((unsigned char)mlx->addr3[(y2 * mlx->sizeline3 + x2 * mlx->bpp3 / 8)] +
                ((unsigned char)mlx->addr3[(y2 * mlx->sizeline3 + x2 * mlx->bpp3 / 8) + 1]) +
                    ((unsigned char)mlx->addr3[(y2 * mlx->sizeline3 + x2 * mlx->bpp3 / 8) + 2])) / 3;
        img_add_px4(mlx, color, x2, y2);
            x2++;
        }
        x2 = 0;
        y2++;
    }
}
