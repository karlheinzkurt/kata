#include "../include/Calendar.h"

#include <boost/algorithm/string/join.hpp>

#include <stdexcept>
#include <sstream>
#include <ctime>
#include <set>
#include <array>
#include <iomanip>
#include <vector>
#include <cmath>

template < typename T, T min, T max>
DateElementBase<T, min, max>::DateElementBase(T value) : m_value(value)
{
   if (value > max)
   {  
      std::ostringstream os;
      os << "Given value " << value << " exceeds maximum value " << max;
      throw std::out_of_range(os.str()); 
   }
   if (value < min)
   {
      std::ostringstream os;
      os << "Given value " << value << " undercuts minimum value " << max;
      throw std::out_of_range(os.str()); 
   }
}

template class DateElementBase<unsigned int, 1, 31>;
template class DateElementBase<unsigned int, 1,  7>;
template class DateElementBase<unsigned int, 1, 12>;
template class DateElementBase<unsigned int, 1900, std::numeric_limits<unsigned int>::max()>;

static std::set<unsigned int> const shortMonth({4, 6, 9, 11});

Days DaysOfMonth(Years year, Months month)
{  
   if (month == 2) 
   {
      bool const isLeapYear((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
      return isLeapYear ? Days(29) : Days(28);
   }
   return shortMonth.count(month) > 0 ? Days(30) : Days(31);
}

WeekDays WeekDayOfMonth(Years years, Months months, Days days /*= Days(1)*/)
{
   std::tm t = {};
   t.tm_year = years - 1900;
   t.tm_mon = months - 1;
   t.tm_mday = days;
   t.tm_hour = 12;
   if (-1 == mktime(&t))
   {  
      std::ostringstream os;
      os << "Determination of week day failed for year " << years << " month " << months << " day " << days;
      throw std::domain_error(os.str()); 
   }
   return WeekDays(1 + t.tm_wday);
}

std::string PrintMonth(Years years, Months months)
{
   auto const firstDay(WeekDayOfMonth(years, months, Days(1)));
   auto const daysOfMonth(DaysOfMonth(years, months));
   auto const lastDay(firstDay + daysOfMonth - 1);
   auto const weeks(detail::WeeksToPrintForMonth(firstDay, daysOfMonth));
   std::vector<std::array<std::string, 7>> month(weeks, std::array<std::string, 7>());
   
   size_t count(1);
   size_t dayOfMonth(1);
   for (auto& week : month)
   {
      for (auto& day : week)
      {
         if (count < firstDay || count > lastDay)
         {  day = "  "; }
         else
         {       
            std::ostringstream os;
            os << std::setw(2) << dayOfMonth++;
            day = os.str();
         }
         ++count;
      }
   }
   
   std::ostringstream os;
   os << "So Mo Di Mi Do Fr Sa\n";
   for (auto& week : month)
   {  os << boost::algorithm::join(week, " ") << '\n'; }
   return os.str();
}

namespace detail
{
   Weeks WeeksToPrintForMonth(WeekDays weekDays, Days daysOfMonth)
   {  return Weeks(std::ceil((static_cast<double>(weekDays) + static_cast<double>(daysOfMonth) - 1.)/7.)); }
}
