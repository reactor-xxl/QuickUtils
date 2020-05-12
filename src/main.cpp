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
#include <string>
#include <filesystem>


struct Settings
{
	int s{ 42 };
};

void help()
{
	static const std::string	helpString{ "help" };
	std::cout << helpString << std::endl;
}

Settings	read_args( int argc, char *argv[] )
{
	for ( auto i = 0; i < argc; ++i )
	{
		std::cout << std::fixed << std::setw( 3 ) << std::right << i << " : \"" << argv[i] << "\"\n";
	}

	return Settings{};
}




int	main( int argc, char *argv[] )
{
	Settings	settings = read_args( argc, argv );

	std::filesystem::path	workingDirectory;
	std::filesystem::path	listingDirectory;
	std::filesystem::path	outputFilepath;


	workingDirectory.assign( argv[0] );

	listingDirectory = workingDirectory = workingDirectory.parent_path();

	auto it = listingDirectory.end();

	--it;

	std::string		directoryShortname;

	directoryShortname = it->generic_string();

	std::string	filename{ "List of " };
	filename += directoryShortname;
	filename += "'s files.txt";


	outputFilepath = listingDirectory / filename;

	std::cout << "workingDirectory: " << workingDirectory << std::endl;
	std::cout << "listingDirectory: " << listingDirectory << std::endl;
	std::cout << "directoryShortname: " << directoryShortname << std::endl;
	std::cout << "outputFilepath: " << outputFilepath << std::endl;

	std::cin.get();
	return 0;
}


