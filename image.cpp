#include <string>

#include "image.h"

void galileo::c_image::read_PPM(std::istream& s)
{
	std::string file_type, garbage;
	c_rgb pix_col;

	s >> file_type >> w >> h >> garbage;

	data = new c_rgb*[w];
	for (int i = 0; i < w; i++)
		data[i] = new c_rgb[h];

	if (file_type == "P3")
	{
		int red, green, blue;
		for (int i = h - 1; i >= 0; i--)
		{
			for (int j = 0; j < w; j++)
			{
				s >> red >> green >> blue;
				pix_col.set_u8((t_u8)red, (t_u8)green, (t_u8)blue);
				data[j][i] = pix_col.gamma(2.2f);
			}
		}
	}
}

void galileo::c_image::write_PPM(std::ostream& s) const
{
	s << "P3\n" << w << " " << h << "\n255\n";

	for (int y = h - 1; y >= 0; y--)
	{
		for (int x = 0; x < w; x++)
		{
			data[x][y] = data[x][y].gamma(1.0f/2.2f);
			s << (int)data[x][y].r_u8() << " " << (int)data[x][y].g_u8() 
				<< " " << (int)data[x][y].b_u8() << " ";
		}
	}
}