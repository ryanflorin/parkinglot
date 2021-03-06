//File:         Logger.cpp
//Description: 	Provides logging to the application

#include "Logger.hpp"

std::ostream * Logger::trace = &std::cout;
std::ostream * Logger::debug = &std::cout;
std::ostream * Logger::info = &std::cout;
std::ostream * Logger::standard = &std::cout;

std::ostream * Logger::throwaway = NULL;

void Logger::Initialize()
{
	int logLevel = _configuration.LogLevel;
	if (logLevel == 0)
	{
		ShowAll();
	}
	else if (logLevel == 1)
	{
		ShowDebug();
	}
	else if (logLevel == 2)
	{
		ShowInfo();
	}
	else if (logLevel == 3)
	{
		ShowStandard();
	}
	else
	{
		ShowNone();
	}

}

//Show all logging messages
void Logger::ShowAll()
{

}

//Show only Standard or higher messages
void Logger::ShowStandard()
{
	throwaway = new std::ostream(NULL);
    info = throwaway;
	debug = throwaway;
	trace = throwaway;
}


//Show only Info or higher messages
void Logger::ShowInfo()
{
	throwaway = new std::ostream(NULL);
	debug = throwaway;
	trace = throwaway;
}

//Show only Debug or higher messages
void Logger::ShowDebug()
{
	throwaway = new std::ostream(NULL);
	trace = throwaway;
}

//Show no messages
void Logger::ShowNone()
{
	throwaway = new std::ostream(NULL);
    info = throwaway;
	debug = throwaway;
	trace = throwaway;

}


