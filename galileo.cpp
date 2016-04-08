
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
	image img(500, 500);

	sphere _sphere(vector3(250, 250, -1000), 150, nullptr);
	triangle _triangle(vector3(300, 600, -800), vector3(0, 100, -1000),
		vector3(450, 20, -1000), nullptr);
	surface_list sl;
	sl.add(&_sphere);
	sl.add(&_triangle);

	vector3 o;
	vector3 d(0, 0, -1);
	ray r(o, d);
	surface_hit_record hit_record;

	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			o.set_x((FLOAT)i); o.set_y((FLOAT)j);
			r.set_origin(o);

			if (sl.hit(r, 0.01f, 2000.0f, 0, hit_record))
			{
				if (hit_record.instance_id == _sphere.id())
				{
					img.set_pixel(i, j, rgb(1, 0, 0));
				}
				else if (hit_record.instance_id == _triangle.id())
				{
					img.set_pixel(i, j, rgb(0, 0, 1));
				}
			}
			else
			{
				img.set_pixel(i, j, rgb(0, 1, 0));
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

