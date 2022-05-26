/*
* Copyright 2020 James Yakura
*/
#include <stdio.h>
#include <cstdio>
#include <string>
#include <iostream>
#include "boost/date_time.hpp"
#include <boost/regex.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

using boost::gregorian::date;
using boost::posix_time::ptime;
using boost::posix_time::time_duration;
using boost::gregorian::date_period;
using boost::gregorian::date_duration;
using boost::gregorian::from_simple_string;



boost::regex regex_1 = boost::regex("\\(log\\.c\\.166\\) server started");
boost::regex regex_2 = boost::regex("oejs\\.AbstractConnector:Started SelectChannelConnector@0\\.0\\.0\\.0:9080");
boost::regex date_regex = boost::regex("^(\\d+-\\d+-\\d+)");
boost::regex time_regex = boost::regex("(\\d+:\\d+:\\d+(?:\\.\\d+))");
boost::regex end_regex = boost::regex("^$");

boost::gregorian::date getDate(std::string text)
{
	boost::smatch matches;
	boost::regex_search(text, matches, date_regex);
	std::string textDate = matches[0];
	return boost::gregorian::date(from_simple_string(textDate));
}

ptime getTime(std::string text)
{
	boost::smatch matches;
	regex_search(text, matches, date_regex);
	std::string textTime = matches[0];
	return ptime(from_simple_string(textTime));
}

int main()
{

	bool testing = false;
	date startDate;
	ptime startTime;

	bool running = true;

	//Program loop:
	while (running)
	{
		std::string input;
		std::getline(std::cin, input);
		//	Read until reaching either regex1 or regex2, or end of file.
		if (regex_match(input, end_regex))
		{
			running = false;
			if (testing)
			{
				std::cout << "Failed" << std::endl;
			}
		}
		else if (regex_search(input, regex_1))
		{
			startDate = getDate(input);
			startTime = getTime(input);
			if (testing)
			{
				std::cout << "Failed" << std::endl;
			}
			std::cout << "Begin startup at " << startDate.year() << "-" << startDate.month() << "-" << startDate.day() << "-" << startTime << " | ";
			testing = true;
		}
		else if (regex_search(input,regex_2))
		{
			date endDate = getDate(input);
			ptime endTime = getTime(input);
			date_period datePer = date_period(endDate, startDate);
			date_duration dateDur = datePer.length();
			time_duration timeDur = endTime - startTime;
			std::cout << "Succeeded in " << dateDur.days() << ":" << timeDur.hours() << ":" << timeDur.minutes() << ":" << timeDur.seconds() << std::endl;
			testing = false;
		}
	}
}
