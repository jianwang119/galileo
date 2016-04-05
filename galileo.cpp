
#include <math.h>
#include <fstream>
#include <string>
using namespace std;

#include "image.h"

int main()
{
	image img;

	std::ifstream in;
	in.open("d:\\image.ppm");
	if (!in)
	{
		cerr << "ERROR -- Can't find PPM file  \'" << string("d:\\image.ppm") << "\'\n";
		exit(0);
	}
	img.read_PPM(in);
	in.close();

	std::ofstream out;
	out.open("d:\\aa.ppm");
	img.write_PPM(out);
	out.close();

    return 0;
}

