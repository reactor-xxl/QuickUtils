#include "FileLister.hpp"



FileLister::FileLister( const Path& path )
	: m_listDirectory{ path } {;}


std::vector<Path> FileLister::generateList() const
{
	std::vector<Path> fileListing;

	if ( !m_listDirectory.empty() )
	{
		std::filesystem::directory_iterator dit( m_listDirectory );
		for ( auto entry : dit )
		{
			auto p = entry.path();
			if ( std::filesystem::is_regular_file( p ) )
			{
				if ( m_option_fullPath )
					fileListing.push_back( p );
				else
					fileListing.push_back( p.filename() );

			}

		}
	}
	return fileListing;
}


void	FileLister::setDirectory( const Path& path )
{
	m_listDirectory = std::filesystem::absolute( path.parent_path() );
}

Path	FileLister::getDirectory() const
{
	return m_listDirectory;
}

FileLister&	FileLister::fullPath( bool b )
{
	m_option_fullPath = b;
	return *this;
}


//void	FileLister::setExtensions( const std::vector<Path>& );
