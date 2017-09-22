
#include "../include/CGame.h"
#include "../include/Utility.h"

#include <algorithm>
#include <vector>

#include <boost/functional/hash.hpp>

namespace Battleship
{
   struct IField
   {
      virtual ~IField() = default;
      virtual std::string toString() const = 0;
      virtual bool doHit(CCoordinate const&) = 0;
      virtual void markUsed() = 0;
   };

   struct IShipRegistration
   {
      virtual ~IShipRegistration() = default;
      virtual void registerShip(IShip&) = 0;
   };

   struct IPlayground
   {
      virtual ~IPlayground() = default;
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
   
   CGame::CBuilder& CGame::CBuilder::placeShip(std::unique_ptr<IShip> ship)
   {  
      m_configuration.m_ships.emplace_back(std::move(ship)); 
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
