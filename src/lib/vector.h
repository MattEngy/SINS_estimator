#pragma once

namespace vectors 
{
	template <class T>
	class vec3
	{
	public:

		T x, y, z;

		vec3() { }

		vec3(T x0, T y0, T z0) {
            x = x0; y = y0; z = z0;
        }

		T len();

		void setNull();

		void normalize();

		void Rotate_M(vec3 axis);

		void Rotate_D(vec3 Axis);

		void globalize(class basis localBasis);

		void localize(class basis newBasis);

		static T dotProd(vec3 a, vec3 b);

		static vec3<T> crossProd(vec3 a, vec3 b);

		static T angle(vec3 a, vec3 b);

		T &operator[](char index);

		vec3<T> operator*(T a);

		vec3<T> operator/(T a);

		vec3<T> operator+(vec3 a);

		vec3<T> operator-(vec3 a);

		vec3<T> operator*(vec3 a) {
            return crossProd(*this, a);
        }
	};
    
    typedef vec3<double> vector;
}
