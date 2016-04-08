#ifndef _IMAGE_H
#define _IMAGE_H

#include "global_define.h"
#include "rgb.h"

namespace galileo
{
	class c_image
	{
	public:
		c_image()
		{
			w = h = 0;
		}

		c_image(int _w, int _h)
		{
			w = _w;
			h = _h;
			data = new c_rgb*[w];
			for (int i = 0; i < w; i++)
			{
				data[i] = new c_rgb[h];
			}
		}

		c_image(int _w, int _h, const c_rgb& c)
		{
			w = _w;
			h = _h;
			data = new c_rgb*[w];
			for (int i = 0; i < w; i++)
			{
				data[i] = new c_rgb[h];
				for (int j = 0; j < h; j++)
					data[i][j] = c;
			}
		}

		~c_image()
		{
			if (data != 0)
			{
				for (int i = 0; i < w; i++)
					delete[] data[i];
				delete[] data;
			}
		}

		void set_pixel(int x, int y, const c_rgb& c)
		{
			data[x][y] = c;
		}

		void set_pixel_safty(int x, int y, const c_rgb& c)
		{
			if (x >= 0 && x < w && y >= 0 && y < h)
			{
				data[x][y] = c;
			}
		}

		const c_rgb& get_pixel(int x, int y) const
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
		c_rgb** data;
		int w;
		int h;
	};
}

#endif
