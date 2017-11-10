#pragma once
#include "vector.h"

namespace Vectors
{
	class basis
	{
	public:

		vector i, j, k;

		basis();
		basis(vector i0, vector j0, vector k0);

		vector &operator[](char index);
		void rotate(vector axis);
	};
}
