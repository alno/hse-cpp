#include <iostream>

void swap(int * a, int i, int j) {
	int v = a[i];
	a[i] = a[j];
	a[j] = v;
}

int partition(int * a, int l, int r, int v) {
	int av = a[v];
	swap(a, v, r-1);

	int m = l;
	for (int i = l; i < r - 1; ++ i) {
		if (a[i] < av) {
			swap(a, i, m);
			m ++;
		}
	}
	swap(a, r - 1, m);
	return m;
}

void qsort(int * a, int l ,int r) {
	while (r > l + 1) {
		int v = partition(a,l,r,(l+r)/2);

		if ( r-v+1 > v-l ) {
			qsort(a, l, v);
			l = v + 1;
		} else {
			qsort(a, v+1, r);
			r = v;
		}
	}
}

int main(int argc, char* argv[])
{
	int a[10] = {2,6,1,3,4,9,8,0,7,5};

	qsort(a, 0, 10);

	for (int i = 0; i < 10; ++ i)
		std::cout << a[i] << " ";

	std::cout << std::endl;

	return 0;
}
