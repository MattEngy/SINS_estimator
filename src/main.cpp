#include "lib/vector.h"
#include "lib/basis.h"
#include <stdio.h>
#include <math.h>

using namespace Vectors;
//using namespace ;

int main()
{
	double R = 6400 * 1000,
		   dt = 0.01;
	vector g(0, 0, -9.8),//без _ в имени - координаты в L т.к. он у нас самый важный
		   U_I(0, 0, M_PI / (12 * 60 * 60));//угловая скорость земли в инерциальной СК

	vector f_raw_B, omega_raw_B;
	vector position, V;//Lambda, Phi, h
	basis L_I, B;//B- платфлома с датчиками, L - географический
/////
	////////
	vector f_raw_L = f_raw_B;
	f_raw_L.Globalize(B);

	vector omega_L = omega_raw_B;
	omega_L.Globalize(B);

	vector U = U_I;
	U.Localize(L_I);

	vector omegaL;
	// вычислить

	double hR = position.z + R;
	vector r(hR * cos(position.y) * cos(position.x),
			 hR * cos(position.y) * sin(position.x),
			 hR * sin(position.y));

	vector acc = f_raw_B - vector::CrossProd((U + omegaL), V)
						 - vector::CrossProd(U, vector::CrossProd(U, r)) + g;

	V = V + acc * dt;
	r = r + V * dt;

	B.rotate(omega_L * dt);

	return 0;
}
