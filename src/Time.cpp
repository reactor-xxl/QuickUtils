#include <ctime>
namespace Windows {
#include <Windows.h>
};
#include <iostream> /* DEBUG */


std::tm window_time_to_C_time_tm( const Windows::SYSTEMTIME& winSysTime )
{
	std::tm		c_time;

c_time.tm_sec		= winSysTime.wSecond;
c_time.tm_min		= winSysTime.wMinute;
c_time.tm_hour		= winSysTime.wHour;
c_time.tm_mday		= winSysTime.wDay;
c_time.tm_mon		= winSysTime.wMonth - 1;
c_time.tm_year		= winSysTime.wYear - 1900; /* 1900 is zero year */
c_time.tm_wday		= winSysTime.wDayOfWeek;
/* c_time.tm_yday		= (ignored) */
/* c_time.tm_isdst		= (ignored) */

auto tt = std::mktime (&c_time);
// debug:
std::cout << std::asctime ( &c_time ) << std::endl;
c_time = *std::localtime( &tt );
std::cout << std::asctime ( &c_time ) << std::endl;


return c_time;

}



