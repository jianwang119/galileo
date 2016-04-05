#ifndef _IMAGE_H
#define _IMAGE_H

#include "global_define.h"
#include "rgb.h"

class image
{
public:
	image()
	{
		w = h = 0;
	}

	image(int _w, int _h)
	{
		w = _w;
		h = _h;
		data = new rgb*[w];
		for (int i = 0; i < w; i++)
		{
			data[i] = new rgb[h];
		}
	}

	image(int _w, int _h, const rgb& c)
	{
		w = _w;
		h = _h;
		data = new rgb*[w];
		for (int i = 0; i < w; i++)
		{
			data[i] = new rgb[h];
			for (int j = 0; j < h; j++)
				data[i][j] = c;
		}
	}

	~image()
	{
		if (data != 0)
		{
			for (int i = 0; i < w; i++)
				delete[] data[i];
			delete[] data;
		}
	}

	void set_pixel(int x, int y, const rgb& c)
	{
		data[x][y] = c;
	}

	void set_pixel_safty(int x, int y, const rgb& c)
	{
		if (x >= 0 && x < w && y >= 0 && y < h)
		{
			data[x][y] = c;
		}
	}

	const rgb& get_pixel(int x, int y) const
	{
		x = clamp(x, 0, w - 1);
		y = clamp(y, 0, h - 1);
		return data[x][y];
	}

	int width() const
	{
		return w;
	}

	int height() const
	{
		return h;
	}

	void read_PPM(std::istream& s);

	void write_PPM(std::ostream& s) const;

private:
	rgb** data;
	int w;
	int h;
};

#endif
