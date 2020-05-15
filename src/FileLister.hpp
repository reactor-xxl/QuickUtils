#pragma once

#include <vector>
#include "main.hpp"



class FileLister
{
public:
	FileLister( const Path& path = std::filesystem::current_path() );
	std::vector<Path> generateList() const;
	void	setDirectory(const Path&);
	Path	getDirectory() const;
	void	setExtensions( const std::vector<Path>& );

	FileLister&	fullPath(bool);

protected:
	Path	m_listDirectory{};
	bool	m_option_fullPath{ false };
};


