
#include "Mandelbrot.Lib/include/Mandelbrot.h"

#include <gtest/gtest.h>

TEST(Mandelbrot, SomeSet)
{
   CMandelbrot m(100);
   EXPECT_EQ(m.print(minmax({-0.6, 0.4}), minmax({0.5, 0.65}), minmax({0.1, 0.1})),
   " .........\n"
   " . .....  \n");
}

TEST(Mandelbrot, IsInSet)
{
   CMandelbrot m(100);
   EXPECT_TRUE(m.isInSet(complex(-1,0)));
}

TEST(Mandelbrot, IsNotInSet)
{
   CMandelbrot m(100);
   EXPECT_FALSE(m.isInSet(complex(-1,-1)));
}
