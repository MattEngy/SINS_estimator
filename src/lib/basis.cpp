#include "basis.h"

namespace vectors
{
	basis::basis()
	{
		i = vector(1, 0, 0);
		j = vector(0, 1, 0);
		k = vector(0, 0, 1);
	}

	basis::basis(vector i0, vector j0, vector k0)
	{
		i = i0;
		j = j0;
		k = k0;
	}

	vector & basis::operator[](char index)
	{
		switch (index)
		{
		case 1:
			return i;
			break;
		case 2:
			return j;
			break;
		case 3:
			return k;
			break;
		}
	}

}
