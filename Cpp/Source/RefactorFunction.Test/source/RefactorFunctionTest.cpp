
#include "RefactorFunction.Lib/include/Sophisticated.h"

#include <gtest/gtest.h>

TEST( First, Refactor )
{
    CalcIni(23, false);
    EXPECT_EQ(5, Calc(false));
}

TEST( Second, Refactor )
{
    EXPECT_EQ(23, Calc(true));
}

TEST( Third, Refactor )
{
    CalcIni(23, true);
    EXPECT_EQ(3, Calc(true));
    EXPECT_EQ(3, Calc(false));
}
