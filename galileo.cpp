
#include <math.h>
#include <fstream>
#include <string>
using namespace std;

#include "sphere.h"
#include "triangle.h"
#include "ray.h"
#include "image.h"
#include "surface_list.h"
#include "sample2.h"
using namespace galileo;

void test_single_sample_ray_tracer()
{
	c_image img(500, 500);

	c_sphere _sphere(c_vector3(250, 250, -1000), 150, nullptr);
	c_triangle _triangle(c_vector3(300, 600, -800), c_vector3(0, 100, -1000),
		c_vector3(450, 20, -1000), nullptr);
	c_surface_list sl;
	sl.add(&_sphere);
	sl.add(&_triangle);

	c_vector3 o;
	c_vector3 d(0, 0, -1);
	c_ray r(o, d);
	c_surface_hit_record hit_record;

	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			c_rgb clr(0, 1, 0);

			o.set_x((t_float)i); o.set_y((t_float)j);
			r.set_origin(o);

			if (sl.hit(r, 0.01f, 2000.0f, 0, hit_record))
			{
				if (hit_record.instance_id == _sphere.id())
				{
					clr = c_rgb(1, 0, 0);
				}
				else if (hit_record.instance_id == _triangle.id())
				{
					clr = c_rgb(0, 0, 1);
				}
			}

			img.set_pixel(i, j, clr);
		}
	}

	std::ofstream out;
	out.open("d:\\test_single_sample_ray_tracer.ppm");
	img.write_PPM(out);
	out.close();
}

void test_multi_sample_ray_tracer(int mx, int my)
{
	c_image img(500, 500);

	c_sphere _sphere(c_vector3(250, 250, -1000), 150, nullptr);
	c_triangle _triangle(c_vector3(300, 600, -800), c_vector3(0, 100, -1000),
		c_vector3(450, 20, -1000), nullptr);
	c_surface_list sl;
	sl.add(&_sphere);
	sl.add(&_triangle);

	c_vector3 o;
	c_vector3 d(0, 0, -1);
	c_ray r(o, d);
	c_surface_hit_record hit_record;

	c_jitter_sample2 jitter(mx, my);
	c_vector2* a = new c_vector2[mx * my];
	jitter.generate(a);

	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			c_rgb clr(0, 0, 0);

			for (int m = 0; m < mx; m++)
			{
				for (int n = 0; n < my; n++)
				{
					c_vector2 v = a[m * 2 + n];
					o.set_x((t_float)i + v.x()); o.set_y((t_float)j + v.y());
					r.set_origin(o);

					if (sl.hit(r, 0.01f, 2000.0f, 0, hit_record))
					{
						if (hit_record.instance_id == _sphere.id())
						{
							clr += c_rgb(1, 0, 0);
						}
						else if (hit_record.instance_id == _triangle.id())
						{
							clr += c_rgb(0, 0, 1);
						}
					}
					else
					{
						clr += c_rgb(0, 1, 0);
					}
				}
			}
			clr /= (t_float)(mx * my);

			img.set_pixel(i, j, clr);
		}
	}

	delete[] a;

	std::ofstream out;
	char buf[256];
	sprintf_s(buf, "d:\\test_multi_sample_ray_tracer_%d_%d.ppm", mx, my);
	out.open(buf);
	img.write_PPM(out);
	out.close();
}

int main()
{
	//test_single_sample_ray_tracer();
	test_multi_sample_ray_tracer(4,4);
    return 0;
}

