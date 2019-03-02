
#include "../include/IShip.h"
#include "../include/Utility.h"

#include <stdexcept>
#include <map>
#include <algorithm>

namespace Battleship
{
   struct CShipBase : IShip
   { 
      typedef std::map<CCoordinate, unsigned int> CoordinateMapType;
      
      virtual bool doHit(CCoordinate const& c) override
      { 
         auto item(m_coordinates.find(c));
         if (item == m_coordinates.end())
         {  return false; }
         
         ++(item->second);
         return true;
      }
      
      virtual bool isSunk() const override
      { 
         for (auto const& t : m_coordinates)
         {  if (t.second == 0) { return false; } }
         return true;
      }
            
      virtual void foreach(std::function<void(CCoordinate const&)> f) const override
      {  std::for_each(m_coordinates.begin(), m_coordinates.end(), [f](auto const& t){ f(std::get<0>(t)); }); }

   protected:  
      CShipBase(CCoordinate a, CCoordinate b, unsigned int hitCount) : m_hitCount(hitCount), m_coordinates()
      {
         if (!(a.getX() == b.getX() || a.getY() == b.getY()))
         {  throw std::invalid_argument("Diagonal ship coordinates not allowed"); }
         
         {
            auto const l(std::minmax({a.getX(), b.getX()}));
            for (unsigned int x(l.first); x <= l.second; ++x)
            {  m_coordinates.emplace(CoordinateMapType::value_type(CCoordinate(a.getY(), x), 0)); }
         }
         {
            auto const l(std::minmax({a.getY(), b.getY()}));
            for (unsigned int y(l.first); y <= l.second; ++y)
            {  m_coordinates.emplace(CoordinateMapType::value_type(CCoordinate(y, a.getX()), 0)); }
         }
         
         if (m_coordinates.size() != m_hitCount)
         {  throw std::invalid_argument(COStringStream() << "Mismatch of given size " << m_hitCount << " and coordinate distance " << m_coordinates.size()); }
      }

      unsigned int const m_hitCount;
      CoordinateMapType m_coordinates;
   };

   struct CDestroyer final : CShipBase { CDestroyer(CCoordinate a, CCoordinate b) : CShipBase(a, b, 5) {} };

   struct CCruiser final : CShipBase { CCruiser(CCoordinate a, CCoordinate b) : CShipBase(a, b, 3) {} };
   
   std::unique_ptr<IShip> IShip::create(IShip::Type ship, CCoordinate a, CCoordinate b)
   {
      switch (ship)
      {
         case IShip::Type::Destroyer:  return std::make_unique<CDestroyer>(a, b); break;
         case IShip::Type::Cruiser:    return std::make_unique<CCruiser>(a, b); break;
      }
      throw std::invalid_argument("Unsupported ship type");
   }
}
