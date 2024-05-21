#include <iostream>
#include <unistd.h>
#include <math.h>
#define cimg_display 0
#include "../../libs/CImg.h"
#include "../../libs/utils.h"

using namespace std;
using namespace cimg_library;


int main(int argn, char *argv[], char *envp[])
{
	float			q;
	
	if (argn < 2)
		return (cerr << "\033[91mFailed: not enough args.\n", 0);

	while (*(++argv))
	{
		try
		{
			CImg<unsigned char> image(*argv);
		}
		catch(const std::exception& e)
		{
			cerr << "\033[91mFailed: invalid file (not a .jpg): \"" << *argv << "\".\n";
			continue;
		}
		CImg<float> image(*argv);
		image.channel(0);

		cimg_forXY(image, x, y)
		{
			q = image(x, y) ? -log(image(x, y) / 255) : -log((float)1 / 255);
			image(x, y) = q;
		}
		image.normalize(0, 255);

		string path("lt_");
		path.append(*argv);
		image.save(path.c_str());
	}
	return 0;
}
