#pragma once

#include <iosfwd>
#include <string>
#include <complex>
#include <array>
#include <vector>

typedef std::complex<double> complex;
typedef std::array<double, 2> minmax;

struct CMandelbrot
{
   CMandelbrot(int iterations);
   
   bool isInSet(complex c);

   std::string print(minmax mx, minmax my, minmax step);

private:
   bool isInSet(complex z, complex c, int iteration);

   int const m_iterations;
};