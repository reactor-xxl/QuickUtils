#pragma once

#include <vector>
#include "main.hpp"



class FileLister
{
public:
	std::vector<Path> generateList();

	void	setDirectory(const Path&);
	Path	getDirectory() const;
	void	setExtensions( const std::vector<Path>& );


/*
directory
file listing settings
returns a vector of path

in path
out path
options

*/

	Path	m_listDirectory;

};


