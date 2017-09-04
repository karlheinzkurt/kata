#pragma once

#include <string>
#include <memory>
#include <list>

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

   struct IShip
   {
      enum class Type
      {
          Destroyer
         ,Cruiser
      };
      
      virtual ~IShip() {}
      
      /** \return true only when the coordinate has NOT been hit before
       */
      virtual bool doHit(CCoordinate const&) = 0;
      
      /** \return true when all coordinates has been hit
       */
      virtual bool isSunk() const = 0;
      
      /** Execute given function for each coordinate the ship is being located on
       */
      virtual void foreach(std::function<void(CCoordinate const&)>) const = 0;
   };

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
         CBuilder& placeShip(IShip::Type ship, CCoordinate a, CCoordinate b);
         
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
