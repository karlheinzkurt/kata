
#include "../include/Minesweeper.h"

#include <iostream>
#include <sstream>
#include <algorithm>

CMinesweeper::CMinesweeper(std::istream& playgroundStream)
{
   std::string line;
   for (size_t h(0); std::getline(playgroundStream, line); ++h)
   {
      for (size_t w(0); w < line.size(); ++w)
      {  m_fields.insert(std::make_pair(CCoordinate(w, h), CField(line[w]))); }
   }
   
   for (auto& field : m_fields) 
   {
      for (auto const& neighbor : field.first.getNeighbors())
      {  
         if (m_fields.find(neighbor) == m_fields.end())
         {  continue; }
         
         if (m_fields[neighbor].isMine())
         {  ++field.second; }
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
   int previousLine(0);
   for (auto const& pair : m_fields) 
   {  
      int currentLine(pair.first.getLine());
      if (previousLine < currentLine)
      {  
         os << '\n'; 
         previousLine = currentLine;
      }
      os << pair.second.toString(); 
   }
   os << '\n';
   return os;
}

CMinesweeper::CCoordinate::CCoordinate(int x, int y) : m_x(x), m_y(y) 
{}

int CMinesweeper::CCoordinate::getLine() const
{  return m_y; }

std::vector<CMinesweeper::CCoordinate> CMinesweeper::CCoordinate::getNeighbors() const
{  
   return std::vector<CMinesweeper::CCoordinate>( 
   {   {m_x-1,m_y-1},{m_x-1,m_y},{m_x-1,m_y+1}
      ,{m_x  ,m_y-1}            ,{m_x  ,m_y+1}
      ,{m_x+1,m_y-1},{m_x+1,m_y},{m_x+1,m_y+1}});
}

bool CMinesweeper::CCoordinate::operator<(CCoordinate const& other) const
{  
   /** Order of x and y is important here to get 
       a proper oder of the fields.
    */
   return std::tie(m_y, m_x) < std::tie(other.m_y, other.m_x); 
}

CMinesweeper::CField::CField() : m_isMine(false), m_isVisible(false), m_isSpace(false), m_count(0)
{}

CMinesweeper::CField::CField(char input) : m_isMine(input == '*'), m_isVisible(true), m_isSpace(input == ' '), m_count(0)
{}

std::string CMinesweeper::CField::toString() const
{  
   if (!m_isVisible) 
   {  return std::string(); }
   else
   if (m_isMine)
   {  return std::string("*"); }
   else
   if (m_isSpace)
   {  return std::string(" "); }
   
   return std::to_string(m_count); 
}
