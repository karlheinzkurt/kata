#pragma once

#include <iosfwd>
#include <map>
#include <vector>

struct CMinesweeper
{
   CMinesweeper(std::istream& playgroundStream);

   std::ostream& getCheatsheet(std::ostream& os) const;
   std::string getCheatsheet() const;
   
   struct CCoordinate
   {
      CCoordinate(int x, int y);
   
      int getLine() const;
   
      bool operator<(CCoordinate const& other) const;
      
      std::vector<CCoordinate> getNeighbors() const;
      
   private:
      int m_x;
      int m_y;
   };
   
   struct CField
   {
      CField();
      
      CField(char input);
           
      bool isMine() const { return m_isMine; }
      
      void operator++() { ++m_count; }
      
      std::string toString() const;
   
   private:
      bool m_isMine;
      bool m_isVisible;
      bool m_isSpace;
      char m_count; ///< Count of mines in the neighborhood
   };

private:
   std::map<CCoordinate, CField> m_fields;
};
