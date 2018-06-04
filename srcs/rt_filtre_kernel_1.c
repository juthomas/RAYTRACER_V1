void matrix(t_filtre *filtre)
{
	filtre->matrix[0][0] = 1;
	filtre->matrix[0][1] = 1;
	filtre->matrix[0][2] = 1;
	filtre->matrix[1][0] = 1;
	filtre->matrix[1][1] = 1;
	filtre->matrix[1][2] = 1;
	filtre->matrix[2][0] = 1;
	filtre->matrix[2][1] = 1;
	filtre->matrix[2][2] = 1;
	filtre->div = 9;
}

unsigned int ligne1(t_win *mlx, int x, int y, t_filtre *filtre)
{
	unsigned int	colorR;
	unsigned int	colorG;
	unsigned int	colorB;
	unsigned int	total;

	colorR = (((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x - 1) * mlx->bpp3 / 8) + 2] * filtre->matrix[0][0])  +
				((unsigned char)mlx->addr3[(y * mlx->sizeline3 + x * mlx->bpp3 / 8) + 2] * filtre->matrix[0][1]) +
					((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x + 1) * mlx->bpp3 / 8) + 2] * filtre->matrix[0][2])) / filtre->div;
	colorG = (((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x - 1) * mlx->bpp3 / 8) + 1] * filtre->matrix[0][0]) +
				((unsigned char)mlx->addr3[(y * mlx->sizeline3 + x * mlx->bpp3 / 8) + 1] * filtre->matrix[0][1]) +
					((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x + 1) * mlx->bpp3 / 8) + 1] * filtre->matrix[0][2])) / filtre->div;
	colorB = (((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x - 1) * mlx->bpp3 / 8)] * filtre->matrix[0][0]) +
				((unsigned char)mlx->addr3[(y * mlx->sizeline3 + x * mlx->bpp3 / 8)] * filtre->matrix[0][1]) +
					((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x + 1) * mlx->bpp3 / 8)] * filtre->matrix[0][2])) / filtre->div;
	total = colorB;
	total += colorG * 256;
	total += colorR * 256 * 256;
	return(total);
}

unsigned int ligne2(t_win *mlx, int x, int y, t_filtre *filtre)
{
	unsigned int	colorR;
	unsigned int	colorG;
	unsigned int	colorB;
	unsigned int	total;

	colorR = (((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x - 1) * mlx->bpp3 / 8) + 2] * filtre->matrix[1][0]) +
				((unsigned char)mlx->addr3[(y * mlx->sizeline3 + x * mlx->bpp3 / 8) + 2] * filtre->matrix[1][1]) +
					((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x + 1) * mlx->bpp3 / 8) + 2] * filtre->matrix[1][2])) / filtre->div;
	colorG = (((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x - 1) * mlx->bpp3 / 8) + 1] * filtre->matrix[1][0]) +
				((unsigned char)mlx->addr3[(y * mlx->sizeline3 + x * mlx->bpp3 / 8) + 1] * filtre->matrix[1][1]) +
					((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x + 1) * mlx->bpp3 / 8) + 1] * filtre->matrix[1][2])) / filtre->div;
	colorB = (((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x - 1) * mlx->bpp3 / 8)] * filtre->matrix[1][0]) +
				((unsigned char)mlx->addr3[(y * mlx->sizeline3 + x * mlx->bpp3 / 8)] * filtre->matrix[1][1]) +
					((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x + 1) * mlx->bpp3 / 8)] * filtre->matrix[1][2])) / filtre->div;
	total = colorB;
	total += colorG * 256;
	total += colorR * 256 * 256;
	return(total);
}

unsigned int ligne3(t_win *mlx, int x, int y, t_filtre *filtre)
{
	unsigned int	colorR;
	unsigned int	colorG;
	unsigned int	colorB;
	unsigned int	total;

	colorR = (((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x - 1) * mlx->bpp3 / 8) + 2] * filtre->matrix[2][0]) +
				((unsigned char)mlx->addr3[(y * mlx->sizeline3 + x * mlx->bpp3 / 8) + 2] * filtre->matrix[2][1]) +
					((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x + 1) * mlx->bpp3 / 8) + 2] * filtre->matrix[2][2])) / filtre->div;
	colorG = (((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x - 1) * mlx->bpp3 / 8) + 1] * filtre->matrix[2][0]) +
				((unsigned char)mlx->addr3[(y * mlx->sizeline3 + x * mlx->bpp3 / 8) + 1] * filtre->matrix[2][1]) +
					((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x + 1) * mlx->bpp3 / 8) + 1] * filtre->matrix[2][2])) / filtre->div;
	colorB = (((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x - 1) * mlx->bpp3 / 8)] * filtre->matrix[2][0]) +
				((unsigned char)mlx->addr3[(y * mlx->sizeline3 + x * mlx->bpp3 / 8)] * filtre->matrix[2][1]) +
					((unsigned char)mlx->addr3[(y * mlx->sizeline3 + (x + 1) * mlx->bpp3 / 8)] * filtre->matrix[2][2])) / filtre->div;
	total = colorB;
	total += colorG * 256;
	total += colorR * 256 * 256;
	return(total);
}
