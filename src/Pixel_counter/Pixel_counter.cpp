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
	int		count = -1;

	(void)envp;
	if (argn < 2)
		return (cerr << "\033[91mFailed: Needs threshold.\n", 0);

	try
	{
		twf = stof(*(++argv)) * 255;
	}
	catch(const std::exception& e)
	{
		return (cerr << "\033[91mFailed: Invalid threshold.\n", 0);
	}
	
	if (argn < 3)
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
			cerr << "\033[91mFailed: invalid file (not a .jpg): \"" << name << "\".\n";
			continue;
		}
		CImg<unsigned char> image(name.c_str());

		count = 0;
		image.channel(0);
		cimg_forXY(image, x, y)
		{
			if (((int)image(x, y) + 1) * 100 >= twf)
				count++;
		}
		printf("%.1f", (float)count * 100 / (image.height() * image.width()));
		if (*argv)
			printf(", ");
	}
	printf("\n");
	return 0;
}
