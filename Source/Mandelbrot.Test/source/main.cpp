
#include <gtest/gtest.h>

#include "Mandelbrot.Lib/include/Mandelbrot.h"

#include <iostream>

int main( int argc, char** argv )
{
   ::testing::InitGoogleTest( &argc, argv );
   auto const r(RUN_ALL_TESTS());
   
   CMandelbrot m(100);
   std::cout << m.print(minmax({-2, 1}), minmax({-1, 1}), minmax({0.05, 0.05})) << '\n';
   
   return r;
}
