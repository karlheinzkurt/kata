#pragma once

#include <string>

namespace Battleship
{   
   struct CCoordinate
   {
      struct X {};
      struct Y {};
      
      CCoordinate(std::string y, unsigned int x);
      CCoordinate(unsigned int y, unsigned int x);
      
      unsigned int getX() const;
      unsigned int getY() const;
      std::string toString() const;
      
   private:
      unsigned int m_publicX;
      std::string  m_publicY;
      unsigned int m_x, m_y;
   };
   
   bool operator<(CCoordinate const& a, CCoordinate const& b);
   bool operator==(CCoordinate const& a, CCoordinate const& b);
}
