#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>

#include <boost/noncopyable.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>


//To use this logger you need inherit from this class
//There are three levels:
//	DEBUG - Debug lines
//	INFO  - Info lines
//	Error - Error lines

class LoggerDecorator : boost::noncopyable
{
public:
	LoggerDecorator()
	{
		boost::filesystem::path logFolder = "Log";
		boost::filesystem::create_directory(logFolder);

		m_logFile.open("Log/Log.txt");
	}

	~LoggerDecorator()
	{
		m_logFile.close();
	}

	void logInfo(std::string& message)
	{
		std::string logMessage = "INFO: " __FILE__ + std::string(__FUNCTION__) + boost::lexical_cast<std::string>(__LINE__) + ": " + message + "\n";
		m_logFile << logMessage;
	}

	void logDebug(std::string& message)
	{
		std::string logMessage = "DEBUG: " __FILE__ + std::string(__FUNCTION__) + boost::lexical_cast<std::string>(__LINE__) + ": " + message + "\n";
		m_logFile << logMessage;
	}

	void logError(std::string& message)
	{
		std::string logMessage = "ERROR: " __FILE__ + std::string(__FUNCTION__) + boost::lexical_cast<std::string>(__LINE__) + ": " + message + "\n";
		m_logFile << logMessage;
	}

private:
	std::ofstream m_logFile;

};

#endif