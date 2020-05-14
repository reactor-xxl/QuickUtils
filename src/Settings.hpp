#pragma once
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

// #include <string>
#include <filesystem>

using Path = std::filesystem::path;

#include <My\utils.hpp>
std::string		Utility::directory_name( Path path );

class Settings
{
public:
	enum class eOutputFormat{ Basic, JSON };

	Settings() = default;
	Settings( const Settings& ) = default;
	Settings& operator=( const Settings& ) = default;

	~Settings() = default;


	void	processArgs( int argc, char *argv[] );

	Path	getListingDirectory() const;
	Path	getOutputFilePath() const;

	eOutputFormat	getFormat() const;
	bool		allowOverwrite() const;

private:
	void	setDefaults( const char *argv_0 );
	void	buildOutfilePath();

	Path	m_workingDirectory{};
	Path	m_listingDirectory{};
	Path	m_outputFilepath{};

	eOutputFormat	m_format{ eOutputFormat::Basic };

	bool	m_allowOverwrite{ false };

};
