
#include "../include/ChristmasTree.h"

#include <iostream>

bool IsInside( unsigned int wide, unsigned int line, unsigned int column )
{   
   unsigned int const center( wide / 2 );
   return ( column > ( center - line - 1 ) && column < ( center + line + 1 ) );  
}

void PrintChristmasTree( std::ostream& os, unsigned int height )
{
   unsigned int const wide( height + ( height - 1 ) + 2 );
   for ( unsigned int line( 0 ); line < height; ++line )
   {
      for ( unsigned int column( 0 ); column < wide; ++column )
      {
         os << ( IsInside( wide, line, column ) ? '*' : ' ' );
      }
      os << '\n';
   }
}

void PrintChristmasTree( unsigned int height )
{  PrintChristmasTree( std::cout, height ); }
