#include "Settings.hpp"
#include <sstream>

/*
	void	processArgs( int argc, char *argv[] );
*/

void	Settings::setDefaults(const char *argv_0)
{
	m_workingDirectory.assign( argv_0 );
	m_workingDirectory = m_workingDirectory.parent_path();
	m_listingDirectory = m_workingDirectory;
	m_allowOverwrite = false;
	m_outputFilepath.clear();

}

void	Settings::buildOutfilePath()
{
	auto tempStr = Utility::directory_name(m_listingDirectory);
	std::string outFilename = "list of " + tempStr + "'s files.txt";

	m_outputFilepath = m_listingDirectory / outFilename;
}


void	Settings::processArgs( int argc, char *argv[] )
{
	setDefaults( argv[0] );

	if ( argc > 1 )
	{
		// argv[1] is either the directory to list (and the output file is tucked into it)
		// or it's the output file path itself.

		std::string tempStr{ argv[1] };

		if ( tempStr.length() )
		{
			Path	inputDirOrOutputFile{ tempStr };

			if ( inputDirOrOutputFile.has_filename() )/* output file, then */
			{
				m_outputFilepath = inputDirOrOutputFile;
			}
			else /* directory */
			{
				m_listingDirectory = inputDirOrOutputFile;
				/* requires rebuild of outfile path */
			}
		}
		// argv[2] is the output file path itself, if provided
		if ( argc > 2 )
		{
			m_outputFilepath.assign( argv[2] );
		}

	}
		
	if ( m_outputFilepath.empty() )
		buildOutfilePath();
}




Path	Settings::getListingDirectory() const
{
	return m_listingDirectory;
}

Path	Settings::getOutputFilePath() const
{
	return m_outputFilepath;
}

Settings::eOutputFormat	Settings::getFormat() const
{
	return m_format;
}

bool		Settings::allowOverwrite() const
{
	return m_allowOverwrite;
}

