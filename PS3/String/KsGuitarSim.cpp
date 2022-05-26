/*
* Copyright James Yakura 2020
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "StringSound.h"
#include <map>
#include <math.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Guitar Sounds");

	//Load key identities
	std::string keys = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' ";

	int duration_secs = 10;

	//Initialize vector of string sounds
	std::map<char, sf::Sound> mapping;
	for (int i = 0; i < keys.size(); i++)
	{
		StringSound thisString(440 * pow(2, (i - 24) / 12));
		thisString.pluck();
		sf::Sound thisSound;
		sf::SoundBuffer thisSoundBuffer;
		std::vector<sf::Int16> samples;
		for (int i = 0; i < duration_secs * StringSound::SAMPLES_PER_SEC*10; i++)
		{
			samples.push_back(thisString.sample());
			thisString.tic();
		}
		thisSoundBuffer.loadFromSamples(samples.data(), samples.size(), 1, StringSound::SAMPLES_PER_SEC);
		thisSound.setBuffer(thisSoundBuffer);
		mapping[keys.at(i)] = thisSound;
	}

	while (window.isOpen())
	{
		//Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Check for window close
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			//Check for key typed
			if (event.type == sf::Event::TextEntered)
			{
				sf::String text = event.text.unicode;
				char key = text[0];
				//Search map for key
				std::map<char, sf::Sound>::iterator it = mapping.find(key);
				if(it!=mapping.end())
				{
					it->second.play();
				}
			}

		}
	}
}