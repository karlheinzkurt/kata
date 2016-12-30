
#include "ChristmasTree.Lib/include/ChristmasTree.h"

#include <gtest/gtest.h>

std::string const tree1(
" * \n" );
std::string const tree2(
"  *  \n"
" *** \n" );
std::string const tree3(
"   *   \n"
"  ***  \n"
" ***** \n" );
std::string const tree4(
"    *    \n"
"   ***   \n"
"  *****  \n"
" ******* \n" );

TEST( ChristmasTree, Height1 )
{
   std::ostringstream os;
   PrintChristmasTree( os, 1 );
   EXPECT_EQ( tree1, os.str() );
}

TEST( ChristmasTree, Height2 )
{
   std::ostringstream os;
   PrintChristmasTree( os, 2 );
   EXPECT_EQ( tree2, os.str() );
}

TEST( ChristmasTree, Height3 )
{
   std::ostringstream os;
   PrintChristmasTree( os, 3 );
   EXPECT_EQ( tree3, os.str() );
}

TEST( ChristmasTree, Height4 )
{
   std::ostringstream os;
   PrintChristmasTree( os, 4 );
   EXPECT_EQ( tree4, os.str() );
}
