unsigned int Rgb(unsigned int color)
{
	unsigned int red;

	red = color >> 16 & 0xFF;
	return (red);
}

unsigned int rGb(unsigned int color)
{
	unsigned int green;

	green = color >> 8 & 0xFF;
	return (green);
}

unsigned int rgB(unsigned int color)
{
	unsigned int blue;

	blue = color & 0xFF;
	return (blue);
}

void		img_add_px6(t_win *mlx, unsigned int color, int x, int y)
{

	if (x < X_WIN && y < Y_WIN && x >= 0 && y >= 0)
	{
		mlx->addr6[(y * mlx->sizeline6 + x * mlx->bpp6 / 8)] = color;
		mlx->addr6[(y * mlx->sizeline6 + x * mlx->bpp6 / 8) + 1] = color >> 8;
		mlx->addr6[(y * mlx->sizeline6 + x * mlx->bpp6 / 8) + 2] = color >> 16;
	}
}

void kernel(t_win *mlx)
{
	unsigned int	colorR;
	unsigned int	colorG;
	unsigned int	colorB;
	unsigned int	colorF;
	int				x;
	int				y;
	t_filtre		*filtre;

	x = 1;
	y = 1;
	filtre = (t_filtre*)malloc(sizeof(*filtre));
	matrix(filtre);
	while (y < Y_WIN)
	{
		while (x < X_WIN)
		{
			colorR = Rgb(ligne1(mlx, x, (y - 1), filtre)) + Rgb(ligne2(mlx, x, y, filtre)) + Rgb(ligne3(mlx, x, (y + 1), filtre));
			colorG = rGb(ligne1(mlx, x, (y - 1), filtre)) + rGb(ligne2(mlx, x, y, filtre)) + rGb(ligne3(mlx, x, (y + 1), filtre));
			colorB = rgB(ligne1(mlx, x, (y - 1), filtre)) + rgB(ligne2(mlx, x, y, filtre)) + rgB(ligne3(mlx, x, (y + 1), filtre));
			colorF = colorB;
			colorF += colorG * 256;
			colorF += colorR * 256 * 256;
			img_add_px6(mlx, colorF, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}
