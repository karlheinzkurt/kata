
#include "Minesweeper.Lib/include/Minesweeper.h"

#include <gtest/gtest.h>

TEST( Minesweeper, Empty )
{
   std::stringstream s;
   CMinesweeper m(s);
   EXPECT_EQ("", m.getCheatsheet());
}

TEST( Minesweeper, OneMine )
{
   std::stringstream s("*\n");
   CMinesweeper m(s);
   EXPECT_EQ("*\n", m.getCheatsheet());
}

TEST( Minesweeper, OneField )
{
   std::stringstream s(".\n");
   CMinesweeper m(s);
   EXPECT_EQ("0\n", m.getCheatsheet());
}

TEST( Minesweeper, 1 )
{
   std::stringstream s( "...\n"
                        ".*.\n"
                        "...\n");
   CMinesweeper m(s);
   EXPECT_EQ(  "111\n"
               "1*1\n"
               "111\n", m.getCheatsheet());
}

TEST( Minesweeper, 2 )
{
   std::stringstream s( ".....\n"
                        ".**.\n"
                        "...\n");
   CMinesweeper m(s);
   EXPECT_EQ(  "12210\n"
               "1**1\n"
               "122\n", m.getCheatsheet());
}

TEST( Minesweeper, 3 )
{
   std::stringstream s( "......\n"
                        " .**. \n"
                        "  ..  \n");
   CMinesweeper m(s);
   EXPECT_EQ(  "012210\n"
               " 1**1 \n"
               "  22  \n", m.getCheatsheet());
}

TEST( Minesweeper, 4 )
{
   std::stringstream s( " ***** \n"
                        "  *.*  \n"
                        "  ***  \n");
   CMinesweeper m(s);
   EXPECT_EQ(  " ***** \n"
               "  *8*  \n"
               "  ***  \n", m.getCheatsheet());
}

TEST( Minesweeper, 5 )
{
   std::stringstream s( "**..*..\n"
                        ".***.**\n"
                        "*..*..*\n"
                        ".*.**.*\n"
                        "..*****\n");
   CMinesweeper m(s);
   EXPECT_EQ(  "**43*32\n"
               "4***4**\n"
               "*46*55*\n"
               "2*5**6*\n"
               "12*****\n", m.getCheatsheet());
}

TEST( Minesweeper, 6 )
{
   std::stringstream s( "*...*\n"
                        " *.*   \n"
                        "  *\n"
                        " *.*   \n"
                        "*...*\n");
   CMinesweeper m(s);
   EXPECT_EQ(  "*222*\n"
               " *3*   \n"
               "  *\n"
               " *3*   \n"
               "*222*\n", m.getCheatsheet());
}
