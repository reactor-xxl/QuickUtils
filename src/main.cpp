/*****************************************************************************
							   MIT License

Copyright (c) 2020	Jonathon Rogers

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

#include <My\utils.hpp>

#include "Settings.hpp"

//using Path = std::filesystem::path;

#include <ctime>
namespace Windows {
#include <Windows.h>
};


Windows::FILETIME   time_t_to_win_filetime( const std::time_t& t );

std::time_t  win_filetime_to_time_t( const Windows::FILETIME& ft );

std::tm window_time_to_C_time_tm( const Windows::SYSTEMTIME& winSysTime );



void help()
{
	static const std::string	helpString{ "help" };
	std::cout << helpString << std::endl;
}

#include <chrono>

Windows::FILETIME	time_time_t_to_win_file_time( const std::time_t& t );
std::time_t			time_win_file_time_to_time_t( const Windows::FILETIME& );


	template <typename T>
	std::string to_binary( const T& rawValue )
	{
		std::string	str;

		unsigned char *pc = reinterpret_cast<unsigned char *>(&rawValue);

		uintmax_t value = static_cast<uintmax_t>(rawValue);

		size_t numBits = 8 * sizeof( rawValue );

		str.reserve( numBits );

		for ( size_t i = 0; i < numBits; ++i )
		{
			size_t y = 1 << (numBits - i - 1);
			if ( value & y )
			{
				str.push_back( '1' );
			} else
			{
				str.push_back( '0' );
			}
		}

		return str;
	}


Windows::FILETIME	time_time_t_to_win_file_time( const std::time_t& t )
{
	/* t is seconds, windows time is 100ns ticks, so
	millis->micros->nanos / 100
	1000L * 1000L * 1000L / 100L */
	uint64_t windowsTicks = t * 1000L * 1000L * 1000L / 100L;

	/*
	Windows Epoch is in 1601 or some goddamn thing.  I don't know.
	offset is 116444736000000000L	
	*/
	windowsTicks += 116444736000000000L;

	Windows::FILETIME ft;
	
    ft.dwLowDateTime  = 0xFFFFFFFF & (windowsTicks >> 0);
    ft.dwHighDateTime = 0xFFFFFFFF & (windowsTicks >> 32);

	std::cout << to_binary( ft ) << std::endl;


	return ft;
}



std::time_t			time_win_file_time_to_time_t( const Windows::FILETIME& ft )
{
	uint64_t	highPart = ft.dwHighDateTime;
	highPart <<= 32;

	uint64_t	windowsTicks = highPart & ft.dwLowDateTime;

	// correct for offset:
	windowsTicks -= 116444736000000000L;

	std::cout << to_binary( ft ) << std::endl;

	//correct for duration:
	windowsTicks /= (1000L * 1000L * 1000L / 100L);

	std::time_t t = windowsTicks;

	return t;

}


int	main( int argc, char *argv[] )
{
//Windows::FILETIME		time_time_t_to_win_file_time( const std::time_t& t );
//std::time_t			time_win_file_time_to_time_t( const Windows::FILETIME& );

	std::time_t current_time = std::time(nullptr);

	auto wft = time_time_t_to_win_file_time( current_time );

	std::time_t conversion_time = time_win_file_time_to_time_t( wft );

	std::cout << "original time_t :  " << current_time << std::endl;
	std::cout << "converted time_t : " << conversion_time << std::endl;


	std::cin.get();
	return 0;
}

int crap( int argc, char *argv[] )
{
	Settings settings;
	std::ostringstream ofileListString;

	settings.processArgs( argc, argv );

	Path outPath = settings.getOutputFilePath();

	if ( !std::filesystem::exists( outPath ) || settings.allowOverwrite() )
	{
		auto listDirIt = std::filesystem::directory_iterator( settings.getListingDirectory() );
		auto i = 0;
		for ( auto& dirEntry : listDirIt )
		{
			if ( dirEntry.is_regular_file() )
			{
				ofileListString << dirEntry.path().filename().generic_string() << '\n';
			}
			++i;
		}

		std::ofstream	outfile( outPath );
		outfile << ofileListString.str();
		outfile.close();

		std::cout << "Wrote " << i << " filenames to " << outPath << std::endl;
	} else
	{
		std::cout << "Cannot generate file listing : the file "
			<< outPath.generic_string() << " already exists, and overwriting is not allowed." << std::endl;
	}


	std::cin.get();
	return 0;
}



std::tm window_time_to_C_time_tm( const Windows::SYSTEMTIME& winSysTime )
{
	std::tm		c_time;

	c_time.tm_sec = winSysTime.wSecond;
	c_time.tm_min = winSysTime.wMinute;
	c_time.tm_hour = winSysTime.wHour;
	c_time.tm_mday = winSysTime.wDay;
	c_time.tm_mon = winSysTime.wMonth - 1;
	c_time.tm_year = winSysTime.wYear - 1900; /* 1900 is zero year */
	c_time.tm_wday = winSysTime.wDayOfWeek;
	/* c_time.tm_yday		= (ignored) */
	/* c_time.tm_isdst		= (ignored) */

	auto tt = std::mktime ( &c_time );
	// debug:
	std::cout << std::asctime ( &c_time ) << std::endl;
	c_time = *std::localtime( &tt );
	std::cout << std::asctime ( &c_time ) << std::endl;


	return c_time;

}

