#ifndef UTILITY_H
#define UTILITY_H


#include <iostream>
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/trim.hpp>


namespace Utility
{

	typedef std::vector<std::string> Tokens;

	Tokens parse(std::string command);
	bool validateCommand(Tokens& command);
	std::string toLowerCase(std::string& s);
	std::string& trim(std::string& str);

}

#endif