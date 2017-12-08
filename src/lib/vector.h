#pragma once

namespace Vectors 
{

    class vector
    {
    public:

        double x, y, z;

        vector() {};
        vector(double x0, double y0, double z0);

        double Length();
        void SetNull();
        void Normalize();
        void Rotate_M(vector Axis);
        void Rotate_D(vector Axis);
        void Globalize(class basis LocalBasis);
        void Localize(class basis newBasis);
        static double DotProd(vector a, vector b);
        static vector CrossProd(vector a, vector b);
        static double Angle(vector a, vector b);

        double &operator[](char index);
        vector operator*(double a);
        vector operator/(double a);
        vector operator+(vector a);
        vector operator-(vector a);
        void operator+=(vector a);
        void operator/=(vector a);
        vector operator*(vector a);
        char* tostring();
    };
}
