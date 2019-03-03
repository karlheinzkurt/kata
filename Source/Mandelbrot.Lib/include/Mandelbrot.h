#pragma once

#include <string>
#include <complex>
#include <array>
#include <vector>

typedef std::complex<double> complex;
typedef std::array<double, 2> minmax;

struct CMandelbrot
{
   CMandelbrot(int iterations, double bailoutRadius);
   
   bool isInside(complex c);
   
   int getIterations(complex c);

   std::string toString(minmax mx, minmax my, minmax step);

private:
   int const m_iterations;
   double const m_bailoutRadius;
};