#pragma once

#include "IShip.h"
#include "CCoordinate.h"

#include <string>
#include <memory>

namespace Battleship
{   
   struct CPlayground;
   struct CConfiguration;

   struct CGame
   {        
      struct CBuilder ///< Public builder to create a configured game instance
      {
         CBuilder();
         ~CBuilder();
         CBuilder(CBuilder const&) = delete;
         CBuilder(CBuilder&&);
         CBuilder& operator=(CBuilder const&) = delete;
         CBuilder& operator=(CBuilder&&);
         
         CGame create();
         
         CBuilder& useWidth(unsigned int w);
         CBuilder& useHeight(unsigned int h);
         CBuilder& placeShip(std::unique_ptr<IShip> ship);
         
      private:
         friend CGame; ///< Smells but to get the configuration without public member 
         std::unique_ptr<CConfiguration> m_configuration;
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
    
      std::unique_ptr<CConfiguration> m_configuration;
      std::unique_ptr<CPlayground> m_playground;
   };
}
