#pragma once

#include <iosfwd>
#include <string>
#include <map>
#include <vector>
#include <memory>

struct CMinesweeper
{
   CMinesweeper(std::istream& playgroundStream);

   std::ostream& getCheatsheet(std::ostream& os) const;
   
   std::string getCheatsheet() const;
   
   struct CCoordinate
   {
      CCoordinate(int x, int y);
   
      bool operator<(CCoordinate const& other) const;
      
      std::vector<CCoordinate> getNeighbors() const;
      
   private:
      int m_x;
      int m_y;
   };
   
   struct IField
   {  
      virtual ~IField() = default;
      
      virtual bool isMine() const = 0;
   
      virtual void incrementCount() = 0;
            
      virtual std::string toString() const = 0;
   };

   static std::unique_ptr<IField> createField(char ch);
   
private:   
   std::map<CCoordinate, std::unique_ptr<IField>> m_fields;
};
