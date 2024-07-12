#include <iostream>
#include <unistd.h>
#include <math.h>
#include <map>
#define cimg_display 0
#include "../../libs/CImg.h"
#include "../../libs/utils.h"

using namespace std;
using namespace cimg_library;


int main(int argn, char *argv[])
{
	map<int, float> logs;

	for (int i = 1; i <= 255; i++)
		logs[i] = -log((float)i / 255);
	logs[0] = logs[1];
	if (argn < 2)
		cerr << "\033[91mFailed: not enough inputs.\n\033[0m";
	while (*(++argv))
	{
		string	name(*argv);
		try
		{
			CImg<unsigned char> image(name.c_str());
		}
		catch(const std::exception& e)
		{
			cerr << "\033[91mFailed: invalid file (not a .jpg): \"" << name << "\".\n\033[0m";
			continue;
		}
		CImg<float> image(name.c_str());
		image.channel(0);

		cimg_forXY(image, x, y)
		{
			float	q = logs[image(x, y)];
			image(x, y) = q;
		}
		image.normalize(0, 255);

		if (name.find('/') != string::npos)
			name.insert(name.find('/') + 1, "lt_");
		else
			name = "lt_" + name;
		image.save(name.c_str());
		cout << name << '\n';
	}
	return 0;
}
