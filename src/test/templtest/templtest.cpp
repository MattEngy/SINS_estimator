#include <stdio.h>
using namespace std;

template <typename T>
class c_t {
public:
	c_t(T val);
	T a;
	T getval() {
		return a;
	}

	void equalize(c_t c);
};

#define __TPL template<typename T>

__TPL
c_t<T>::c_t(T val) {
	a = val;
}

template <typename T>
void c_t<T>::equalize(c_t c) {
    a = c.a;
}

typedef c_t<double> cd_t;
typedef c_t<int> ci_t;

int main()
{
	double d = 4.68;
	cd_t c1(d);
	cd_t c2(0);
	c2.equalize(c1);
	printf("%d\n", c2.getval());
	return 0;
}
