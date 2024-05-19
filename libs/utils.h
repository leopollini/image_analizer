#include <iostream>

#define HEIGHT_MAP_FOLDER "height_maps/"

float	get_float(char *s)
{
	float	res;
	try
	{
		res = (float)255 * std::stof(s) / 100 - 1;
	}
	catch(const std::exception& e)
	{
		std::cerr << "\033[91mFailed: invalid threshold (not a float).\n";
		exit(0);
	}
	return (res);
}
