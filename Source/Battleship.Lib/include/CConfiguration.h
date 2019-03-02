#pragma once

#include "IShip.h"

#include <memory>
#include <list>

namespace Battleship
{   
   struct CConfiguration ///< POD for internal configuration
   {
      CConfiguration() = default;
      CConfiguration(CConfiguration&) = delete;
      CConfiguration(CConfiguration&&) = default;
      CConfiguration& operator=(CConfiguration&) = delete;
      CConfiguration& operator=(CConfiguration&&) = default;
      
      unsigned int m_width, m_height;
      std::list<std::unique_ptr<IShip>> m_ships;
   };
}
