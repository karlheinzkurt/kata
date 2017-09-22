#pragma once

#include "CCoordinate.h"

#include <functional>
#include <memory>

namespace Battleship
{   
   struct IShip
   {
      enum class Type
      {
          Destroyer
         ,Cruiser
      };
      
      virtual ~IShip() = default;
      
      /** \return true only when the coordinate has NOT been hit before
       */
      virtual bool doHit(CCoordinate const&) = 0;
      
      /** \return true when all coordinates has been hit
       */
      virtual bool isSunk() const = 0;
      
      /** Execute given function for each coordinate the ship is being located on
       */
      virtual void foreach(std::function<void(CCoordinate const&)>) const = 0;
      
      /** Create a ship of desired type
       */
      static std::unique_ptr<IShip> create(IShip::Type ship, CCoordinate a, CCoordinate b);
   };
}
