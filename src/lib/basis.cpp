#include "basis.h"
#include "assert.h"
#include "stdio.h"

namespace Vectors {
    basis::basis() {
        i = vector(1, 0, 0);
        j = vector(0, 1, 0);
        k = vector(0, 0, 1);
    }

    basis::basis(vector i0, vector j0, vector k0) {
        i = i0;
        j = j0;
        k = k0;
    }

    basis::basis(double elems[3][3]) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
            (*this)[i][j] = elems[j][i];
            }
        }
    }

    vector &basis::operator[](char index) {
        assert(index <= 2 || index >= 0);
        switch (index) {
        case 0:
            return i;
            break;
        case 1:
            return j;
            break;
        case 2:
            return k;
            break;
        }
    }

    basis basis::operator*(basis b) {
        basis bbuf;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                bbuf[j][i] = 0;
                for (int k = 0; k < 3; ++k) {
                    bbuf[j][i] += (*this)[k][i] * b[j][k];
                }
            }
        }
        return bbuf;
    }

    basis basis::operator*(double b) {
        basis bbuf;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                bbuf[i][j] = (*this)[i][j] * b;
            }
        }
        return bbuf;
    }

    basis basis::operator+(basis b) {
        basis bbuf;
        for (int m = 0; m < 3; ++m) {
            for (int n = 0; n < 3; ++n) {
                bbuf[m][n] = (*this)[m][n] + b[m][n];
            }
        }
        return bbuf;
    }
    
    basis basis::operator-(basis b) {
        basis bbuf;
        for (int m = 0; m < 3; ++m) {
            for (int n = 0; n < 3; ++n) {
                bbuf[m][n] = (*this)[m][n] - b[m][n];
            }
        }
        return bbuf;
    }

    void basis::rotate(vector axis) {
        i.Rotate_M(axis);
        j.Rotate_M(axis);
        k.Rotate_M(axis);
    }

    void basis::transpond() {
        (*this) = basis(vector(i.x, j.x, k.x),
                        vector(j.x ,j.y, j.z),
                        vector(k.x, k.y, k.z));
    }

    char* basis::tostring() {
        char *str = new char[255];
        sprintf(str, "%s\n%s\n%s", i.tostring(),
                                   j.tostring(),
                                   k.tostring());
        return str;
    }
}
