
#include "../include/CCoordinate.h"
#include "../include/Utility.h"

#include <tuple>

namespace Battleship
{
   CCoordinate::CCoordinate(std::string y, unsigned int x) : m_publicX(x), m_publicY(y), m_x(m_publicX - 1), m_y(std::toupper(m_publicY[0]) - 'A') 
   {}
   
   CCoordinate::CCoordinate(unsigned int y, unsigned int x) : m_publicX(x + 1), m_publicY(1, y + 'A'), m_x(x), m_y(y) 
   {}
   
   unsigned int CCoordinate::getX() const 
   {  return m_x; }
   
   unsigned int CCoordinate::getY() const 
   {  return m_y; }
   
   std::string CCoordinate::toString() const 
   {  return COStringStream() << m_publicY << m_publicX; }
   
   bool operator<(CCoordinate const& a, CCoordinate const& b)
   {  
      auto ax(a.getX()); auto ay(a.getY());
      auto bx(b.getX()); auto by(b.getY());
      return std::tie(ax, ay) < std::tie(bx, by); 
   }
   
   bool operator==(CCoordinate const& a, CCoordinate const& b)
   {  
      auto ax(a.getX()); auto ay(a.getY());
      auto bx(b.getX()); auto by(b.getY());
      return std::tie(ax, ay) == std::tie(bx, by); 
   }
}
