#include "../include/Mandelbrot.h"

#include <iostream>
#include <sstream>
#include <complex>

CMandelbrot::CMandelbrot(int iterations) : m_iterations(iterations) {}

bool CMandelbrot::isInSet(complex c)
{
   return isInSet(complex(0,0), c, m_iterations);
}

bool CMandelbrot::isInSet(complex z, complex c, int iteration)
{
   auto const result = std::pow(z, 2) + c;

   if (iteration >= m_iterations)
   {
      return (std::abs(result.real()) <= 1 && std::abs(result.imag()) <= 1);
   }
   
   return isInSet(result, c, ++iteration);
}

std::string CMandelbrot::print(minmax mx, minmax my, minmax step)
{
   std::ostringstream result;
   for (double y = my[0]; y < my[1]; y += step[0])
   {
      std::ostringstream os;
      for (double x = mx[0]; x < mx[1]; x += step[1])
      {
         os << (isInSet(complex(0,0), complex(x,y), 0) ? '.' : ' ');
      }
      result << os.str() << "\n";
   }
   return result.str();
}
