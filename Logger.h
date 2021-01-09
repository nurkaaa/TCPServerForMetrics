#include <fstream>

#include <boost/lexical_cast.hpp>


#define LOG(formatString, level, ...) log("log.txt", formatString, LOG_LEVELS::LOG_INFO, __FILE__, __FUNCTION__, __LINE__)

#define LOG_INFO(formatString)  LOG(formatString, LOG_LEVELS::LOG_INFO)
#define LOG_DEBUG(formatString) LOG(formatString, LOG_LEVELS::LOG_DEBUG)
#define LOG_ERROR(formatString) LOG(formatString, LOG_LEVELS::LOG_ERROR)


enum LOG_LEVELS
{
	LOG_DEBUG = 0,
	LOG_INFO = 1,
	LOG_ERROR = 2
};

void log(std::string filename, std::string message, const LOG_LEVELS logLevel, std::string file, std::string function, int line)
{
	std::ofstream logFile;
	logFile.open(filename, std::ofstream::out | std::ofstream::app);

	std::string toLog = "";

	switch (logLevel)
	{
		case 0:
			toLog += "DEBUG: ";
			break;
		case 1:
			toLog += "INFO: ";
			break;
		case 2:
			toLog += "ERROR: ";
			break;
	}

	toLog += file + " " + function + " LINE: " + boost::lexical_cast<std::string>(line) + ": " + message;
	logFile << toLog;
	logFile.close();
}
