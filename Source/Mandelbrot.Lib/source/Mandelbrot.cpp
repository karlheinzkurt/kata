#include "../include/Mandelbrot.h"

#include <sstream>
#include <complex>

CMandelbrot::CMandelbrot(int iterations, double bailoutRadius) 
   : m_iterations(iterations) 
   , m_bailoutRadius(bailoutRadius)
{}

bool CMandelbrot::isInside(complex c)
{
   return getIterations(c) >= m_iterations;
}

int CMandelbrot::getIterations(complex c)
{
   auto iteration = 0;
   auto z = complex(0,0) + c;
   while (1)
   {
      if (std::abs(z) > m_bailoutRadius || iteration >= m_iterations)
      {  
         break;
      }
      ++iteration;
      z = std::pow(z, 2) + c;
   }
   return iteration;
}

std::string CMandelbrot::toString(minmax mx, minmax my, minmax step)
{
   std::ostringstream result;
   for (double y = my[0]; y <= my[1]; y += step[1])
   {
      std::ostringstream os;
      for (double x = mx[0]; x <= mx[1]; x += step[0])
      {
         os << (isInside(complex(x,y)) ? '.' : ' ');
      }
      result << os.str() << "\n";
   }
   return result.str();
}
