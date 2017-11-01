#include "vector.h"
#include "math.h"
#include "basis.h"
#define sqr(x) x*x

namespace vectors { 
    template <typename T>
	T vec3<T>::len() {
		return sqrt(x * x + y * y + z * z);
	}

    template <typename T>
	void vec3<T>::setNull() {
		x = 0;
		y = 0;
		z = 0;
	}

    template <typename T>
	void vec3<T>::normalize() {
		T length = len();
		if (! ((x == 0) && (y == 0) && (z == 0)))
		{
			x /= length;
			y /= length;
			z /= length;
		}
	}

    template <typename T>
	void vec3<T>::Rotate_M(vec3 Axis) {
		T Omega = Axis.Length();
		T bx, by, bz;
		Axis.Normalize();
		bx = (cos(Omega) + (1 - cos(Omega))*sqr(Axis.x))*x + ((1 - cos(Omega))*Axis.x*Axis.y - sin(Omega)*Axis.z)*y + ((1 - cos(Omega))*Axis.x*Axis.z + sin(Omega)*Axis.y)*z;
		by = ((1 - cos(Omega))*Axis.x*Axis.y + sin(Omega)*Axis.z)*x + (cos(Omega) + (1 - cos(Omega))*sqr(Axis.y))*y + ((1 - cos(Omega))*Axis.y*Axis.z - sin(Omega)*Axis.x)*z;
		bz = ((1 - cos(Omega))*Axis.x*Axis.z - sin(Omega)*Axis.y)*x + ((1 - cos(Omega))*Axis.z*Axis.y + sin(Omega)*Axis.x)*y + (cos(Omega) + (1 - cos(Omega))*sqr(Axis.z))*z;
		x = bx;
		y = by;
		z = bz;
	}

    template <typename T>
	void vec3<T>::Rotate_D(vec3 axis) { }

    template <class T>
	void vec3<T>::globalize(basis LocalBasis) {
		vec3 buffer = LocalBasis.i * x + LocalBasis.j * y + LocalBasis.k * z;
		x = buffer.x;
		y = buffer.y;
		z = buffer.z;
	}
    
    template <class T>
	void vec3<T>::localize(basis newBasis) {
		T par[4][3];
		par[0][0] = newBasis.i.x;
		par[0][1] = newBasis.i.y;
		par[0][2] = newBasis.i.z;

		par[1][0] = newBasis.j.x;
		par[1][1] = newBasis.j.y;
		par[1][2] = newBasis.j.z;

		par[2][0] = newBasis.k.x;
		par[2][1] = newBasis.k.y;
		par[2][2] = newBasis.k.z;

		par[3][0] = x;
		par[3][1] = y;
		par[3][2] = z;
		for (char i = 0; i < 2; ++i) {
			for (char j = i + 1; j < 3; ++j) {
				T coef = par[i][j] / par[i][i];
				for (char k = i; k < 4; ++k) {
					par[k][j] = par[k][j] - par[k][i] * coef;
				}
			}
		}
		for (char i = 2; i > 0; --i) {
			for (signed char j = i - 1; j > -1; --j) {
				T coef = par[i][j] / par[i][i];
				for (char k = 0; k < 4; ++k) {
					par[k][j] -= par[k][i] * coef;
				}
			}
		}
		for (char i = 0; i < 3; ++i) {
			par[3][i] /= par[i][i];
		}
		x = par[3][0];
		y = par[3][1];
		z = par[3][2];
	}

    template <typename T>
	T vec3<T>::dotProd(vec3 a, vec3 b) {
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}

    template <class T>
	vec3<T> vec3<T>::crossProd(vec3 a, vec3 b) {
		return vec3(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
	}

    template <class T>
	T vec3<T>::angle(vec3 a, vec3 b) {
		return acos(dotProd(a, b) / (a.length()*b.length()));
	}

    template <class T>
	T &vec3<T>::operator[](char index) {
		switch (index) {
			case 1: return x;
			break;
			case 2: return y;
			break;
			case 3: return z;
			break;
		}
	}

    template <class T>
	vec3<T> vec3<T>::operator*(T a) {
		return vec3(x*a, y*a, z*a);
	}

    template <class T>
	vec3<T> vec3<T>::operator/(T a) {
		return vec3(x / a, y / a, z / a);
	}

    template <class T>
	vec3<T> vec3<T>::operator+(vec3 a) {
		return vec3(x + a.x, y + a.y, z + a.z);
	}

    template <class T>
	vec3<T> vec3<T>::operator-(vec3 a) {
		return vec3(x - a.x, y - a.y, z - a.z);
	}
}

#undef sqr
