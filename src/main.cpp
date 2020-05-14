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


void help()
{
	static const std::string	helpString{ "help" };
	std::cout << helpString << std::endl;
}




int	main( int argc, char *argv[] )
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
	}
	else
	{
		std::cout << "Cannot generate file listing : the file "
			<< outPath.generic_string() << " already exists, and overwriting is not allowed." << std::endl;
	}


	std::cin.get();
	return 0;
}







