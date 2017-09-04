#include "../include/Battleship.h"

#include <stdexcept>
#include <map>
#include <array>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>

#include <boost/functional/hash.hpp>

struct COStringStream
{
   template <typename T> COStringStream& operator<<(T const& t) { m_os << t; return *this; }
   operator std::string() { return m_os.str(); }
   
private:
   std::ostringstream m_os;
};

namespace Battleship
{
   CCoordinate::CCoordinate(std::string y, unsigned int x) : m_publicX(x), m_publicY(y), m_x(m_publicX - 1), m_y(std::toupper(m_publicY[0]) - 'A') {}
   CCoordinate::CCoordinate(unsigned int y, unsigned int x) : m_publicX(x + 1), m_publicY(1, y + 'A'), m_x(x), m_y(y) {}
   unsigned int CCoordinate::getX() const { return m_x; }
   unsigned int CCoordinate::getY() const { return m_y; }
   std::string CCoordinate::toString() const { return COStringStream() << m_publicY << m_publicX; }
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

   struct IField
   {
      virtual ~IField() {}
      virtual std::string toString() const = 0;
      virtual bool doHit(CCoordinate const&) = 0;
      virtual void markUsed() = 0;
   };

   struct IShipRegistration
   {
      virtual ~IShipRegistration() {}
      virtual void registerShip(IShip&) = 0;
   };

   struct IPlayground
   {
      virtual ~IPlayground() {}
      virtual IField& get(CCoordinate c) = 0;
   };

   struct CFieldBase : IField
   {
      virtual std::string toString() const { return COStringStream() << m_pre << m_main << m_post; }
      virtual void markUsed() { m_post = '.'; }
      
   protected:
      CFieldBase(std::string::value_type main) : m_pre(' '), m_main(main), m_post(' ') {}

      std::string::value_type m_pre, m_main, m_post;
   };

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

   struct CWaterField final : CFieldBase
   { 
      CWaterField() : CFieldBase('~') {} 
      virtual bool doHit(CCoordinate const&) { return false; }
   };

   struct CShipField final : CFieldBase
   { 
      CShipField(IShip& ship) : CFieldBase('#'), m_ship(ship) {}
      virtual bool doHit(CCoordinate const& c)
      {
         m_main = 'X';
         return m_ship.doHit(c);
      }

   private:
      IShip& m_ship;
   };

   struct CPlayground : IShipRegistration, IPlayground
   {
      typedef std::string KeyType;
      typedef std::vector<std::vector<std::unique_ptr<IField>>> FieldContainerType;
      
      static FieldContainerType fillWater(unsigned int width, unsigned int height)
      {
         FieldContainerType fields(height);
         for (auto& line : fields) 
         { 
            line = FieldContainerType::value_type(width);
            for (auto& element : line)
            {  element = std::make_unique<CWaterField>(); }
         }
         return fields;
      }
      
      CPlayground(CConfiguration const& configuration) : 
         m_fields(fillWater(configuration.m_width, configuration.m_height))
      {  for (auto& s: configuration.m_ships) { registerShip(*s); } }
      
      std::string toString() const 
      {
         std::ostringstream os;
         for (auto const& lines : m_fields) 
         { 
            for (auto const& element : lines) { os << element->toString(); }
            os << '\n';
         }
         return os.str();
      }
      
      virtual IField& get(CCoordinate c) override
      {  return *m_fields[c.getY()][c.getX()]; }
      
      virtual void registerShip(IShip& ship) override
      {
         ship.foreach([this, &ship](CCoordinate const& c)
         {  m_fields[c.getY()][c.getX()] = std::make_unique<CShipField>(ship); });
      }
      
   private:
      FieldContainerType m_fields;
   };
   
   CGame::CBuilder::CBuilder() : m_configuration() 
   {}
   
   CGame::CBuilder& CGame::CBuilder::placeShip(IShip::Type ship, CCoordinate a, CCoordinate b)
   {
      switch (ship)
      {
         case IShip::Type::Destroyer: m_configuration.m_ships.emplace_back(std::make_unique<CDestroyer>(a, b)); break;
         case IShip::Type::Cruiser: m_configuration.m_ships.emplace_back(std::make_unique<CCruiser>(a, b)); break;
      }
      return *this;
   }

   CGame CGame::CBuilder::create()
   {
      if (m_configuration.m_width == 0) { throw std::invalid_argument("Playground width equals 0"); }
      if (m_configuration.m_height == 0) { throw std::invalid_argument("Playground height equals 0"); }
      
      return CGame(std::move(*this));
   }

   CGame::~CGame() = default;
   CGame::CGame(CGame&&) = default;
   CGame& CGame::operator=(CGame&&) = default;

   CGame::CGame(CBuilder builder) : 
       m_configuration(std::move(builder.m_configuration))
      ,m_playground(std::make_unique<CPlayground>(m_configuration)) 
   {}
   
   bool CGame::fire(CCoordinate const& c)
   {  
      m_playground->get(c).markUsed();
      return true;
   }
   
   bool CGame::getHit(CCoordinate const& c)
   {  return m_playground->get(c).doHit(c); }

   std::string CGame::toString() const
   {  return m_playground->toString(); }
}
