#include "Battleship.Lib/include/CGame.h"

#include <stdexcept>
#include <iostream>

#include <gtest/gtest.h>

TEST( Battleship, ConfigurationErrors )
{   
   EXPECT_THROW(Battleship::CGame::CBuilder().useWidth(0).create(), std::invalid_argument);
   EXPECT_THROW(Battleship::CGame::CBuilder().useHeight(0).create(), std::invalid_argument);
}

TEST( Battleship, Complex )
{   
   auto game(Battleship::CGame::CBuilder()
      .useWidth(10).useHeight(10)
      .placeShip(Battleship::IShip::create(Battleship::IShip::Type::Destroyer, Battleship::CCoordinate("B", 2), Battleship::CCoordinate("B", 6)))
      .placeShip(Battleship::IShip::create(Battleship::IShip::Type::Cruiser, Battleship::CCoordinate("C", 7), Battleship::CCoordinate("E", 7)))
      .placeShip(Battleship::IShip::create(Battleship::IShip::Type::Cruiser, Battleship::CCoordinate("I", 3), Battleship::CCoordinate("G", 3)))
      .create());
      
   game.fire(Battleship::CCoordinate("D", 5));
   EXPECT_FALSE(game.getHit(Battleship::CCoordinate("A", 1)));
   EXPECT_TRUE(game.getHit(Battleship::CCoordinate("B", 3)));
   
   EXPECT_EQ(R"2end(
 ~  ~  ~  ~  ~  ~  ~  ~  ~  ~ 
 ~  #  X  #  #  #  ~  ~  ~  ~ 
 ~  ~  ~  ~  ~  ~  #  ~  ~  ~ 
 ~  ~  ~  ~  ~. ~  #  ~  ~  ~ 
 ~  ~  ~  ~  ~  ~  #  ~  ~  ~ 
 ~  ~  ~  ~  ~  ~  ~  ~  ~  ~ 
 ~  ~  #  ~  ~  ~  ~  ~  ~  ~ 
 ~  ~  #  ~  ~  ~  ~  ~  ~  ~ 
 ~  ~  #  ~  ~  ~  ~  ~  ~  ~ 
 ~  ~  ~  ~  ~  ~  ~  ~  ~  ~ 
)2end", "\n" + game.toString());
}
