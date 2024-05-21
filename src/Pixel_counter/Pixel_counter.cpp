#include <iostream>
#include <unistd.h>
#define cimg_display 0
#include "../../libs/CImg.h"
#include "../../libs/utils.h"

using namespace std;
using namespace cimg_library;

int main(int argn, char *argv[], char *envp[])
{
	float	twf;
	int		count;

	if (argn < 3)
		return (cerr << "\033[91mFailed: not enough args.\n", 0);
	twf = get_float(*++argv) * 255;

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
		CImg<unsigned char> image(*argv);

		count = 0;
		image.channel(0);
		cimg_forXY(image, x, y)
		{
			if (((int)image(x, y) + 1) * 100 >= twf)
				count++;
		}
		printf("%.1f", (float)count * 100 / (image.height() * image.width()));
		cout << (*(argv + 1) ? ',' : '\n');
	}
	return 0;
}
