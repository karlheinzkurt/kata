#pragma once

#include <string>
#include <limits>

template < typename T, T minimum, T maximum>
struct DateElementBase
{  
   typedef DateElementBase<T, minimum, maximum> base_type;
   explicit DateElementBase(T);
   operator T() const { return m_value; }
   bool operator==(DateElementBase& other) const { return m_value == other.m_value; }
private:
   T m_value;
};

struct Years : DateElementBase<unsigned int, 1900, std::numeric_limits<unsigned int>::max()> 
{  using Years::base_type::base_type; };

struct Months : DateElementBase<unsigned int, 1, 12> 
{  using Months::base_type::base_type; };

struct Weeks : DateElementBase<unsigned int, 1, 52>
{  using Weeks::base_type::base_type; };

struct Days : DateElementBase<unsigned int, 1, 31> 
{  using Days::base_type::base_type; };

struct WeekDays : DateElementBase<unsigned int, 1,  7> 
{  using WeekDays::base_type::base_type; };

/** Determine number of days of a month
 */
Days DaysOfMonth(Years, Months);

/** Determine week day of a date
 */
WeekDays WeekDayOfMonth(Years, Months, Days = Days(1));

/** Get string representation of a month
 */
std::string PrintMonth(Years, Months);

namespace detail
{
   /** Determine number of weeks lines to print for string representation
    *  \remark Internal function
    */
   Weeks WeeksToPrintForMonth(WeekDays, Days);
}
