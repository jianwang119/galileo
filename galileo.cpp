
#include <math.h>
#include <fstream>
#include <string>
using namespace std;

#include "sphere.h"
#include "triangle.h"
#include "ray.h"
#include "image.h"
#include "surface_list.h"
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
			o.set_x((t_float)i); o.set_y((t_float)j);
			r.set_origin(o);

			if (sl.hit(r, 0.01f, 2000.0f, 0, hit_record))
			{
				if (hit_record.instance_id == _sphere.id())
				{
					img.set_pixel(i, j, c_rgb(1, 0, 0));
				}
				else if (hit_record.instance_id == _triangle.id())
				{
					img.set_pixel(i, j, c_rgb(0, 0, 1));
				}
			}
			else
			{
				img.set_pixel(i, j, c_rgb(0, 1, 0));
			}
		}
	}

	std::ofstream out;
	out.open("d:\\test_single_sample_ray_tracer.ppm");
	img.write_PPM(out);
	out.close();
}

int main()
{
	test_single_sample_ray_tracer();
    return 0;
}

