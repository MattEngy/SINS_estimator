#include "vector.h"
#include "math.h"
#include "basis.h"
#include "assert.h"
#include "stdio.h"

#define sqr(x) x*x

namespace Vectors {
    vector::vector(double x0, double y0, double z0) {
        x = x0; y = y0; z = z0;
    }

    double vector::Length() {
        return sqrt(x*x + y*y + z*z);
    }

    void vector::SetNull() {
        x = 0;
        y = 0;
        z = 0;
    }

    void vector::Normalize() {
        double length = Length();
        if (! ((x == 0) && (y == 0) && (z == 0))) {
            x /= length;
            y /= length;
            z /= length;
        }
    }

    void vector::Rotate_M(vector Axis) {
        double Omega = Axis.Length();
        double bx, by, bz;
        Axis.Normalize();
        bx = (cos(Omega) + (1 - cos(Omega))*sqr(Axis.x))*x + ((1 - cos(Omega))*Axis.x*Axis.y - sin(Omega)*Axis.z)*y + ((1 - cos(Omega))*Axis.x*Axis.z + sin(Omega)*Axis.y)*z;
        by = ((1 - cos(Omega))*Axis.x*Axis.y + sin(Omega)*Axis.z)*x + (cos(Omega) + (1 - cos(Omega))*sqr(Axis.y))*y + ((1 - cos(Omega))*Axis.y*Axis.z - sin(Omega)*Axis.x)*z;
        bz = ((1 - cos(Omega))*Axis.x*Axis.z - sin(Omega)*Axis.y)*x + ((1 - cos(Omega))*Axis.z*Axis.y + sin(Omega)*Axis.x)*y + (cos(Omega) + (1 - cos(Omega))*sqr(Axis.z))*z;
        x = bx;
        y = by;
        z = bz;
    }

    void vector::Rotate_D(vector Axis){ }

    void vector::Globalize(basis LocalBasis) {
        vector buffer=LocalBasis.i*x + LocalBasis.j*y + LocalBasis.k*z;
        x=buffer.x;
        y=buffer.y;
        z=buffer.z;
    }

    void vector::Localize(basis newBasis) {
        double par[4][3];
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
                float coef = par[i][j] / par[i][i];
                for (char k = i; k < 4; ++k) {
                    par[k][j] = par[k][j] - par[k][i] * coef;
                }
            }
        }
        for (char i = 2; i > 0; --i) {
            for (signed char j = i - 1; j > -1; --j) {
                double coef = par[i][j] / par[i][i];
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

    double vector::DotProd(vector a, vector b) {
        return a.x*b.x + a.y*b.y + a.z*b.z;
    }

    vector vector::CrossProd(vector a, vector b) {
        return vector(a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x);
    }

    double vector::Angle(vector a, vector b) {
        return acos(vector::DotProd(a, b) / (a.Length()*b.Length()));
    }

    double &vector::operator[](char index) {
        assert(index <= 2 || index >= 0);
        switch (index) {
            case 0: return x;
            break;
            case 1: return y;
            break;
            case 2: return z;
            break;
        }
    }

    vector vector::operator*(double a) {
        return vector(x*a, y*a, z*a);
    }

    vector vector::operator/(double a) {
        return vector(x / a, y / a, z / a);
    }

    vector vector::operator+(vector a) {
        return vector(x + a.x, y + a.y, z + a.z);
    }

    vector vector::operator-(vector a) {
        return vector(x - a.x, y - a.y, z - a.z);
    }
    
    void vector::operator+=(vector a) {
        x += a.x;
        y += a.y;
        z += a.z;
    }

    void vector::operator/=(vector a) {
        x /= a.x;
        y /= a.y;
        z /= a.z;
    }
    
    vector vector::operator*(vector a) {
        return CrossProd((*this), a);
    }

    char* vector::tostring() {
        char *str = new char[255];
        sprintf(str, "%lf  %lf  %lf", x, y, z);
        return str;
    }
}
#undef sqr
