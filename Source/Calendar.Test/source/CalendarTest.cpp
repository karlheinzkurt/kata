
#include "Calendar.Lib/include/Calendar.h"

#include <stdexcept>
#include <string>

#include <gtest/gtest.h>

TEST( Day, Limits )
{
   EXPECT_THROW(Days(0), std::out_of_range);
   EXPECT_NO_THROW(Days(1));
   EXPECT_NO_THROW(Days(31));
   EXPECT_THROW(Days(32), std::out_of_range);
}

TEST( Month, Limits )
{
   EXPECT_THROW(Months(0), std::out_of_range);
   EXPECT_NO_THROW(Months(1));
   EXPECT_NO_THROW(Months(12));
   EXPECT_THROW(Months(13), std::out_of_range);
}

TEST( Year, Limits )
{
   EXPECT_THROW(Years(1899), std::out_of_range);
   EXPECT_NO_THROW(Years(1900));
   EXPECT_NO_THROW(Years(std::numeric_limits<unsigned int>::max()));
}  

TEST( WeekDay, Limits )
{
   EXPECT_THROW(WeekDays(0), std::out_of_range);
   EXPECT_NO_THROW(WeekDays(1));
   EXPECT_NO_THROW(WeekDays(7));
   EXPECT_THROW(WeekDays(8), std::out_of_range);
}

TEST( DaysOfMonth, ShortMonth )
{
   for (auto y : {1900, 2012, 2013, 2014, 2015, 2016, 2200})
   {
      EXPECT_EQ(Days(30), DaysOfMonth(Years(y), Months(4)));
      EXPECT_EQ(Days(30), DaysOfMonth(Years(y), Months(6)));
      EXPECT_EQ(Days(30), DaysOfMonth(Years(y), Months(9)));
      EXPECT_EQ(Days(30), DaysOfMonth(Years(y), Months(11)));
   }
}

TEST( DaysOfMonth, LongMonth )
{
   for (auto y : {1900, 2012, 2013, 2014, 2015, 2016, 2200})
   {
      EXPECT_EQ(Days(31), DaysOfMonth(Years(y), Months(1)));
      EXPECT_EQ(Days(31), DaysOfMonth(Years(y), Months(3)));
      EXPECT_EQ(Days(31), DaysOfMonth(Years(y), Months(5)));
      EXPECT_EQ(Days(31), DaysOfMonth(Years(y), Months(7)));
      EXPECT_EQ(Days(31), DaysOfMonth(Years(y), Months(8)));
      EXPECT_EQ(Days(31), DaysOfMonth(Years(y), Months(10)));
      EXPECT_EQ(Days(31), DaysOfMonth(Years(y), Months(12)));
   }
}

TEST( DaysOfMonth, FebruarNonLeapYear )
{
   for (auto y : {1900, 2001, 2002, 2003, 2005, 2006, 2100, 2200})
   {
      EXPECT_EQ(Days(28), DaysOfMonth(Years(y), Months(2)));
   }
}

TEST( DaysOfMonth, FebruarLeapYear )
{
   for (auto y : {1904, 2000, 2004, 2008, 2012, 2016, 2400, 2800})
   {
      EXPECT_EQ(Days(29), DaysOfMonth(Years(y), Months(2)));
   }
}

TEST( WeekDayOfMonth, FebruarNonLeapYear )
{
   EXPECT_EQ(WeekDays(7), WeekDayOfMonth(Years(2014), Months(2)));
   EXPECT_EQ(WeekDays(1), WeekDayOfMonth(Years(2014), Months(2), Days(2)));
   EXPECT_EQ(WeekDays(2), WeekDayOfMonth(Years(2014), Months(2), Days(3)));
   EXPECT_EQ(WeekDays(6), WeekDayOfMonth(Years(2014), Months(2), Days(28)));
   EXPECT_EQ(WeekDays(7), WeekDayOfMonth(Years(2014), Months(3)));
}

TEST( WeekDayOfMonth, FebruarLeapYear )
{
   EXPECT_EQ(WeekDays(2), WeekDayOfMonth(Years(2016), Months(2)));
   EXPECT_EQ(WeekDays(7), WeekDayOfMonth(Years(2016), Months(2), Days(6)));
   EXPECT_EQ(WeekDays(1), WeekDayOfMonth(Years(2016), Months(2), Days(7)));
   EXPECT_EQ(WeekDays(2), WeekDayOfMonth(Years(2016), Months(2), Days(29)));
   EXPECT_EQ(WeekDays(3), WeekDayOfMonth(Years(2016), Months(3)));
}

TEST( WeekDayOfMonth, JanuarYear )
{
   EXPECT_EQ(WeekDays(5), WeekDayOfMonth(Years(2015), Months(1)));
   EXPECT_EQ(WeekDays(7), WeekDayOfMonth(Years(2015), Months(1), Days(3)));
   EXPECT_EQ(WeekDays(1), WeekDayOfMonth(Years(2015), Months(1), Days(4)));
   EXPECT_EQ(WeekDays(4), WeekDayOfMonth(Years(2015), Months(1), Days(7)));
   EXPECT_EQ(WeekDays(7), WeekDayOfMonth(Years(2015), Months(1), Days(31)));
   EXPECT_EQ(WeekDays(1), WeekDayOfMonth(Years(2015), Months(2)));
}

TEST( WeeksToPrint, Simple )
{
   using detail::WeeksToPrintForMonth;
   EXPECT_EQ(Weeks(5), WeeksToPrintForMonth(WeekDayOfMonth(Years(2016), Months(2)), DaysOfMonth(Years(2016), Months(2))));
   EXPECT_EQ(Weeks(5), WeeksToPrintForMonth(WeekDayOfMonth(Years(2027), Months(2)), DaysOfMonth(Years(2027), Months(2))));
   EXPECT_EQ(Weeks(5), WeeksToPrintForMonth(WeekDayOfMonth(Years(2048), Months(2)), DaysOfMonth(Years(2048), Months(2))));
   EXPECT_EQ(Weeks(6), WeeksToPrintForMonth(WeekDayOfMonth(Years(2015), Months(8)), DaysOfMonth(Years(2015), Months(8))));
   EXPECT_EQ(Weeks(6), WeeksToPrintForMonth(WeekDayOfMonth(Years(2026), Months(8)), DaysOfMonth(Years(2026), Months(8))));
   EXPECT_EQ(Weeks(4), WeeksToPrintForMonth(WeekDayOfMonth(Years(2015), Months(2)), DaysOfMonth(Years(2015), Months(2))));
   EXPECT_EQ(Weeks(4), WeeksToPrintForMonth(WeekDayOfMonth(Years(2026), Months(2)), DaysOfMonth(Years(2026), Months(2))));
}

TEST( PrintMonth, FebruarLeapYear )
{  
   EXPECT_EQ(std::string(
      "So Mo Di Mi Do Fr Sa\n"
      "    1  2  3  4  5  6\n"
      " 7  8  9 10 11 12 13\n"
      "14 15 16 17 18 19 20\n"
      "21 22 23 24 25 26 27\n"
      "28 29               \n"), PrintMonth(Years(2016), Months(2)));
}

TEST( PrintMonth, FebruarNonLeapYear )
{  
   EXPECT_EQ(std::string(
      "So Mo Di Mi Do Fr Sa\n"
      " 1  2  3  4  5  6  7\n"
      " 8  9 10 11 12 13 14\n"
      "15 16 17 18 19 20 21\n"
      "22 23 24 25 26 27 28\n"), PrintMonth(Years(2015), Months(2)));
}

TEST( PrintMonth, SixWeeks )
{  
   EXPECT_EQ(std::string(
      "So Mo Di Mi Do Fr Sa\n"
      "                   1\n"
      " 2  3  4  5  6  7  8\n"
      " 9 10 11 12 13 14 15\n"
      "16 17 18 19 20 21 22\n"
      "23 24 25 26 27 28 29\n"
      "30 31               \n"), PrintMonth(Years(2015), Months(8)));
}
