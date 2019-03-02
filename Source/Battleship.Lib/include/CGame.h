#pragma once

#include "IShip.h"
#include "CCoordinate.h"

#include <string>
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
   
   struct CPlayground;

   struct CGame
   {        
      struct CBuilder ///< Public builder to create a configured game instance
      {
         CBuilder();
         CGame create();
         
         CBuilder& useWidth(unsigned int w) { m_configuration.m_width = w; return *this; }
         CBuilder& useHeight(unsigned int h) { m_configuration.m_height = h; return *this; }
         CBuilder& placeShip(std::unique_ptr<IShip> ship);
         
      private:
         friend CGame; ///< Smells but to get the configuration without public member 
         CConfiguration m_configuration;
      };
      
      CGame() = delete;
      ~CGame();
      CGame(CGame&) = delete;
      CGame(CGame&&);
      CGame& operator=(CGame&) = delete;
      CGame& operator=(CGame&&);
      
      bool fire(CCoordinate const&);
      bool getHit(CCoordinate const&);
      
      std::string toString() const;
      
   private:
      CGame(CBuilder);
    
      CConfiguration m_configuration;
      std::unique_ptr<CPlayground> m_playground;
   };
}
