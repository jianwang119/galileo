#include <string>

#include "image.h"

void image::read_PPM(std::istream& s)
{
	std::string file_type, garbage;
	rgb pix_col;

	s >> file_type >> w >> h >> garbage;

	data = new rgb*[w];
	for (int i = 0; i < w; i++)
		data[i] = new rgb[h];

	if (file_type == "P3")
	{
		int red, green, blue;
		for (int i = h - 1; i >= 0; i--)
		{
			for (int j = 0; j < w; j++)
			{
				s >> red >> green >> blue;
				pix_col[0] = ((FLOAT(red) + 0.5f) / 256.0f) *
					((FLOAT(red) + 0.5f) / 256.0f);
				pix_col[1] = ((FLOAT(green) + 0.5f) / 256.0f) *
					((FLOAT(green) + 0.5f) / 256.0f);
				pix_col[2] = ((FLOAT(blue) + 0.5f) / 256.0f) *
					((FLOAT(blue) + 0.5f) / 256.0f);
				data[j][i] = pix_col;
			}
		}
	}
	else
	{
		char red, green, blue;
		s.get(red); // get rid of newline
		for (int i = h - 1; i >= 0; i--)
		{
			for (int j = 0; j < w; j++)
			{
				s.get(red);
				s.get(green);
				s.get(blue);

				pix_col[0] = ((FLOAT(red) + 0.5f) / 256.0f) *
					((FLOAT(red) + 0.5f) / 256.0f);
				pix_col[1] = ((FLOAT(green) + 0.5f) / 256.0f) *
					((FLOAT(green) + 0.5f) / 256.0f);
				pix_col[2] = ((FLOAT(blue) + 0.5f) / 256.0f) *
					((FLOAT(blue) + 0.5f) / 256.0f);

				data[j][i] = pix_col;
			}
		}
	}
}

void image::write_PPM(std::ostream& s) const
{
	s << "P6\n" << w << " " << h << "\n255\n";

	unsigned int i;
	for (int y = h - 1; y >= 0; y--)
	{
		for (int x = 0; x < w; x++)
		{
			FLOAT gamma = 1.0f / 2.2f;
			data[x][y] = rgb(pow(data[x][y].r(), gamma),
				pow(data[x][y].g(), gamma),
				pow(data[x][y].b(), gamma));
			i = (U32)(256.0 * data[x][y].r());
			if (i > 255) i = 255;
			s.put((U8)i);
			i = (U32)(256.0 * data[x][y].g());
			if (i > 255) i = 255;
			s.put((U8)i);
			i = (U32)(256.0 * data[x][y].b());
			if (i > 255) i = 255;
			s.put((U8)i);
		}
	}
}