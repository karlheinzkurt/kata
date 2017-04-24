#include "../include/Minesweeper.h"

#include <iostream>
#include <sstream>

CMinesweeper::CMinesweeper(std::istream& playgroundStream)
{
   std::string line;
   for (size_t h(0); std::getline(playgroundStream, line); ++h)
   {
      line += '\n'; ///< Newline has been cut off, so we have to append it again
      for (size_t w(0); w < line.size(); ++w)
      {  m_fields.emplace(std::make_pair(CCoordinate(w, h), createField(line[w]))); }
   }
   
   for (auto& centerField : m_fields)
   {
      for (auto const& neighbor : centerField.first.getNeighbors())
      {  
         auto neighborField(m_fields.find(neighbor));
         if (neighborField != m_fields.end())
         {  if (neighborField->second->isMine()) centerField.second->incrementCount(); }
      }
   }
}

std::string CMinesweeper::getCheatsheet() const
{
   std::ostringstream os;
   getCheatsheet(os);
   return os.str();
}

std::ostream& CMinesweeper::getCheatsheet(std::ostream& os) const
{  
   for (auto const& pair : m_fields) { os << pair.second->toString(); }
   return os;
}

CMinesweeper::CCoordinate::CCoordinate(int x, int y) : m_x(x), m_y(y)
{}

std::vector<CMinesweeper::CCoordinate> CMinesweeper::CCoordinate::getNeighbors() const
{  
   return std::vector<CMinesweeper::CCoordinate>( 
      {{m_x-1,m_y-1},{m_x-1,m_y},{m_x-1,m_y+1}
      ,{m_x  ,m_y-1}            ,{m_x  ,m_y+1}
      ,{m_x+1,m_y-1},{m_x+1,m_y},{m_x+1,m_y+1}});
}

bool CMinesweeper::CCoordinate::operator<(CCoordinate const& other) const
{  
   /** Order of x and y is important here, 1st x, 2nd y. */
   return std::tie(m_y, m_x) < std::tie(other.m_y, other.m_x); 
}

struct AFieldBase : CMinesweeper::IField
{
   AFieldBase(char ch) : m_char(ch) {}
   
   virtual bool isMine() const { return false; }
   
   virtual void incrementCount() {}
            
   virtual std::string toString() const { return std::string() + m_char; }
   
protected:
   char m_char;
};

struct CMineField : AFieldBase
{
   using AFieldBase::AFieldBase;
   
   virtual bool isMine() const { return true; }
};

struct CNormalField : AFieldBase
{
   CNormalField() : AFieldBase(0), m_count(0) {}
   
   virtual void incrementCount() { ++m_count; }
           
   virtual std::string toString() const override { return std::to_string(m_count); }
   
private:
   size_t m_count;
};

struct CIgnoredField : AFieldBase { using AFieldBase::AFieldBase; };

std::unique_ptr<CMinesweeper::IField> CMinesweeper::createField(char ch)
{
   switch (ch)
   {
      case '*':  return std::make_unique<CMineField>(ch);      break;
      case '.':  return std::make_unique<CNormalField>();      break;
      case ' ':
      case '\n': return std::make_unique<CIgnoredField>(ch);   break;
      default: break;
   }
   throw std::invalid_argument(std::string("Unsupported field character found: ") + ch);
}
