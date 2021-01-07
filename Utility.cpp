#include "Utility.h"


namespace Utility
{
	Tokens parse(std::string command)
	{
		//						Parse the request
		//				---------- Command type ----------
		//	put [name] [value] [timestamp] - put the new value to our storage
		//	get [name] - get the value from our storage by the name
		std::vector<std::string> tokens;
		
		try
		{
			boost::trim_right(command);
			boost::split(tokens, command, boost::is_any_of(" "));
		}
		catch (std::exception& ec)
		{}

		return tokens;
	}

	bool validateCommand(Tokens& command)
	{
		if (command.at(0) == "put" && command.size() == 4)
		{
			return true;
		}
		else if (command.at(0) == "get" && command.size() == 2)
		{
			return true;
		}
		return false;
	}

	std::string toLowerCase(std::string& s)
	{
		std::string result = "";
		for (auto& c : s)
		{
			result += std::tolower(c);
		}

		return result;
	}

	std::string& trim(std::string& str) {
		size_t endpos = str.find_last_not_of("\r\n");
		if (endpos != std::string::npos) {
			str.substr(0, endpos + 1).swap(str);
		}
		return str;
	}

}
