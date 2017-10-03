#include "stdafx.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <ctime>

inline const double M_PI() { return 3.141592653589793238462643383279502884; }

inline double f(double val)
{
	return sin(val);
}

static int F(int n)
{
	int f, f1 = 1, f2 = 1, m = 0;
	while (m < n - 1)
	{
		f = f1 + f2;
		f1 = f2;
		f2 = f;
		++m;
	}
	return f1;
}

static void Dih(double x_left, double x_right, double eps)
{
	int count = 0;
	auto xm = (x_left + x_right) / 2;
	auto l = x_right - x_left;
	//Console.WriteLine(xm);
	//Console.WriteLine(L);


	auto x1 = x_left + l / 4;
	auto x2 = x_right - l / 4;
	//Console.WriteLine(x1);
	//Console.WriteLine(x2);
	//Console.WriteLine(sin(xm));
	while (l >= eps)
	{
		count++;


		if (sin(x1) < sin(xm))
		{
			x_right = xm;
			xm = x1;
		}
		else
		{
			if (sin(x2) < sin(xm))
			{
				x_left = xm;
				xm = x2;
			}
			if (sin(x2) > sin(xm))
			{
				x_left = x1;
				x_right = x2;
			}
		}
		l = x_right - x_left;
		x1 = x_left + l / 4;
		x2 = x_right - l / 4;
		//Console.WriteLine(x1);
		//Console.WriteLine(x2);
		//Console.WriteLine(xm);
		//Console.WriteLine(L);
	}
	std::cout << std::endl << "x = " << xm << " F(x) = " << sin(xm) << " Количество итераций: " << count << std::endl;

	//Console.ReadLine();
}
static void Fib(double a, double b, double eps)
{
	double x1, x2, _x, xf1, xf2;
	int k = 0;
	int N = 0;
	double fn1 = 1, fn2 = 1, fn, f = (b - a) / eps;

	while (fn1 < f)
	{
		fn = fn1 + fn2;
		fn1 = fn2;
		fn2 = fn;
		++N;
	}
	int ix = N & 1;
	auto bix = ix == 1;
	x1 = a + (double)F(N - 2) / F(N) * (b - a) - (bix ? -1 : 1) * eps / F(N);
	x2 = a + (double)F(N - 1) / F(N) * (b - a) + (bix ? -1 : 1) * eps / F(N);
	xf1 = sin(x1);
	xf2 = sin(x2);
	while (!(fabs(b - a) <= eps))
	{
		++k;
		if (xf1 >= xf2)
		{
			ix = (N - k) & 1;
			bix = ix == 1;
			a = x1;
			x1 = x2;
			xf1 = xf2;
			x2 = a + (double)F(N - k - 1) / F(N - k) * (b - a) + (bix ? -1 : 1) * eps / F(N - k);
			xf2 = sin(x2);
		}
		else
		{
			ix = (N - k) & 1;
			bix = ix == 1;
			b = x2;
			x2 = x1;
			xf2 = xf1;
			x1 = a + (double)F(N - k - 2) / F(N - k) * (b - a) - (bix ? -1 : 1) * eps / F(N - k);
			xf1 = sin(x1);
		}
	}

	_x = (a + b) / 2;
	std::cout << std::endl << "x = " << _x << " F(x) = " << sin(_x) << " Количество итераций: " << k << std::endl;
}


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	const double epsilon = 0.01;
	auto a = -M_PI() / 2;
	auto b = M_PI() / 2;
	Dih(a, b, epsilon);
	auto first = clock();
	Fib(a, b, epsilon);
	auto second = clock();
	std::cout << second - first;
	//Console.WriteLine(second - first);
	return 0;
}
