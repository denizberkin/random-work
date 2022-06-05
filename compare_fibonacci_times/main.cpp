#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;
#define ull unsigned long long

ull fib_fast(int, ull []);
ull fib_normal(int);
ull normal(int, int);
ull fast(int, int, ull[]);

int main() {
	ull x[1000] = { NULL };

	steady_clock::time_point begin;
	steady_clock::time_point end;
	
	begin = steady_clock::now();
	fib_normal(35);
	end = steady_clock::now();
	cout << "normal time passed: " << duration_cast<nanoseconds>(end-begin).count()/1000000.0 << endl;
	
	begin = steady_clock::now();
	fib_fast(500, x);
	end = steady_clock::now();
	
	cout << "fast time passed: " << duration_cast<nanoseconds>(end-begin).count()/1000000.0 << endl;
	
	
	
	return 0;
}


ull fib_normal(int n) {
	if (n <= 2)return 1;
	else return fib_normal(n - 1) + fib_normal(n - 2);
}

ull normal(int m, int n) {
	if (m == 1 || n == 1)	return 1;
	else return normal(m-1,n) + normal(m, n-1);
}

ull fast(int m, int n, ull a[]) {
	static int nn = n;
	if (a[(m-1)*nn + n] != 0)	return a[(m - 1) * nn + n];
	else if (m == 1 || n == 1) return 1;
	else {
		a[(m - 1) * nn + n] = fast(m - 1, n, a) + fast(m, n - 1, a);
		return a[(m - 1) * nn + n];
	}
}


ull fib_fast(int n, ull fib[]){
	if (*(fib+n) != 0)	return fib[n];
	else if (n <= 2)	return 1;
	else {
		fib[n] = fib_fast(n - 2, fib) + fib_fast(n - 1, fib);
		return fib[n];
	}
}