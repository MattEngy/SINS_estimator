#include "../lib/vector.h"
#include <stdio.h>
#include "../lib/vector.cpp"

using namespace vectors;
int main()
{
	vec3<int> i(1, 0, 0),
	       j(0, 1, 0);
	vec3<int> k = i * j;
	printf("%5d %5d %5d\n", k.x, k.y, k.z);
	return 0;
}
