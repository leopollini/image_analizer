#include <iostream>
#include <unistd.h>
#include <math.h>
#include <sys/stat.h>
#define cimg_display 0
#include "../../libs/CImg.h"
#include "../../libs/utils.h"

using namespace std;
using namespace cimg_library;


int main(int argn, char *argv[])
{
	int firstn = 300;
	int	k = 2, p = 30;

	if (argn < 2)
		cerr << "\033[91mFailed: not enough inputs.\n\033[0m";
	while (*(++argv))
	{
		string	name(*argv);
		int x0, y0, x1, y1;
		try
		{
			CImg<unsigned char> image(*argv);
		}
		catch(const std::exception& e)
		{
			cerr << "\033[91mFailed: invalid file (not a .jpg): \"" << name << "\".\n\033[0m";
			continue;
		}
		CImg<float> image(*argv);
		image.channel(0);

		long	t = 0;
		cimg_for1(firstn, i)
		{
			cimg_forY(image, y)
			{
				t += image(i, y);
			}
		}
		t *= p;
		t /= firstn;
		float usefulol = t * k / image.height();
		// std::cout << "@@" << usefulol << "\n";
		
		cimg_forY(image, y)
		{
			int val = 0;
			cimg_forX(image, x)
			{
				if (x % p == 0)
				{
					if (val > usefulol)
					{
						y0 = y;
						val = 0;
						break ;
					}
					else
						val = 0;
				}
				val += image(x, y);
			}
			if (!val)
				break ;
		}
		cimg_forY(image, y)
		{
			int val = 0;
			cimg_forX(image, x)
			{
				if (x % p == 0)
				{
					if (val > usefulol)
					{
						y1 = image.height() - y - 1;
						val = 0;
						break ;
					}
					else
						val = 0;
				}
				val += image(x, image.height() - y - 1);
			}
			if (!val)
				break ;
		}
		cimg_forX(image, x)
		{
			int val = 0;
			cimg_forY(image, y)
			{
				if (y % p == 0)
				{
					if (val > usefulol)
					{
						x0 = x;
						val = 0;
						break ;
					}
					else
						val = 0;
				}
				val += image(x, y);
			}
			if (!val)
				break ;
		}
		cimg_forX(image, x)
		{
			int val = 0;
			cimg_forY(image, y)
			{
				if (y % p == 0)
				{
					if (val > usefulol)
					{
						x1 = image.width() - x - 1;
						val = 0;
						break ;
					}
					else
						val = 0;
				}
				val += image(image.width() - x - 1, y);
			}
			if (!val)
				break ;
		}
		// // correct size (more like square)
		// int del = (y1 - x1 - y0 + x0) / 4;
		// y1 -= del;
		// y0 += del;
		// x1 += del;
		// x0 -= del;
		if (y0 >= y1 || x0 >= x1)
		{
			cerr << "\033[91mFailed: Crop failed\".\n\033[0m";
			continue;
		}

		CImg<unsigned char> cropd(y1 - y0, x1 - x0);
		cimg_forXY(cropd, x, y)
		{
			cropd(x, y) = image(x1 - x - 1, y1 - y - 1);
		}

		if (name.find('/') != string::npos)
			name.insert(name.find('/') + 1, "ct_");
		else
			name = "ct_" + name;
		cropd.save(name.c_str());
		std::cout << name << '\n';
	}
	return 0;
}
