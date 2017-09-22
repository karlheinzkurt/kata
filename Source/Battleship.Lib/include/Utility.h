#pragma once

#include <sstream>

namespace Battleship
{
   struct COStringStream
   {
      template <typename T> COStringStream& operator<<(T const& t) { m_os << t; return *this; }
      operator std::string() { return m_os.str(); }
      
   private:
      std::ostringstream m_os;
   };
}
