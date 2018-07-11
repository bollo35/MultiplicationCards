#include <algorithm>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include "fact.h"


int main(int argc, char** argv) {

	// Load resources
	sf::Font font;
	if (!font.loadFromFile("Schools Out!!!.otf")) {
		std::cerr << "Unable to open 'Schools Out!!!.otf'" << std::endl;
		return 1;
	} 
	
	sf::SoundBuffer celebration;
	if (!celebration.loadFromFile("celebration-short.ogg")) {
		std::cerr << "Unable to open 'celebration.ogg'" << std::endl;
		return 1;
	}

	sf::SoundBuffer sadcry;
	if (!sadcry.loadFromFile("sadcry5.ogg")) {
		std::cerr << "Unable to open 'sadcry5.ogg'" << std::endl;
		return 1;
	}
	
	// populate multiplication facts
	std::vector<MultiplicationFact> facts;
	for (int i = 1; i < 10; ++i) {
		for (int j = 1; j < 10; ++j) {
			auto mfact = MultiplicationFact{i, j};
			facts.push_back(mfact);
		}
	}
	// apparently random_shuffle uses rand...but doesn't initialize it
	std::srand( unsigned (std::time(0)) );
	// shuffle the facts
	std::random_shuffle(facts.begin(), facts.end());
	auto fact_index = 0;
	auto& mfact = facts[fact_index];

	// begin the SFML things!
	sf::RenderWindow window(sf::VideoMode(800, 600), "Math game!");
	sf::Text input_string;
	input_string.setFont(font);
	input_string.setCharacterSize(80);
	input_string.setFillColor(sf::Color::Red);
	char input[3] = {0, 0, 0};
	int index = 0;
	bool answer_given = false;
	while ( window.isOpen() ) {
		sf::Event event;
		while ( window.pollEvent(event) ) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::KeyPressed) {
				switch(event.key.code) {
					case sf::Keyboard::Key::Num0:
					case sf::Keyboard::Key::Numpad0:
						if ( index < 2 ) {
							input[index++] = '0';
						}
						break;
					case sf::Keyboard::Key::Num1:
					case sf::Keyboard::Key::Numpad1:
						if ( index < 2 ) {
							input[index++] = '1';
						}
						break;
					case sf::Keyboard::Key::Num2:
					case sf::Keyboard::Key::Numpad2:
						if ( index < 2 ) {
							input[index++] = '2';
						}
						break;
					case sf::Keyboard::Key::Num3:
					case sf::Keyboard::Key::Numpad3:
						if ( index < 2 ) {
							input[index++] = '3';
						}
						break;
					case sf::Keyboard::Key::Num4:
					case sf::Keyboard::Key::Numpad4:
						if ( index < 2 ) {
							input[index++] = '4';
						}
						break;
					case sf::Keyboard::Key::Num5:
					case sf::Keyboard::Key::Numpad5:
						if ( index < 2 ) {
							input[index++] = '5';
						}
						break;
					case sf::Keyboard::Key::Num6:
					case sf::Keyboard::Key::Numpad6:
						if ( index < 2 ) {
							input[index++] = '6';
						}
						break;
					case sf::Keyboard::Key::Num7:
					case sf::Keyboard::Key::Numpad7:
						if ( index < 2 ) {
							input[index++] = '7';
						}
						break;
					case sf::Keyboard::Key::Num8:
					case sf::Keyboard::Key::Numpad8:
						if ( index < 2 ) {
							input[index++] = '8';
						}
						break;
					case sf::Keyboard::Key::Num9:
					case sf::Keyboard::Key::Numpad9:
						if ( index < 2 ) {
							input[index++] = '9';
						}
						break;
					case sf::Keyboard::Key::BackSpace:
						if ( index > 0 ) {
							input[--index] = 0;
						}
						break;
					case sf::Keyboard::Key::Return:
						answer_given = index > 0;
						break;
					case sf::Keyboard::Key::Escape:
						window.close();
						break;
				}
			}
		}

		auto me_ans = std::string(input);
		input_string.setString(me_ans);
		if (answer_given) {
			auto input_answer = atoi(input);
			auto is_correct = mfact.check_answer(input_answer);
			// if it's correct, celebrate and give a new problem
			sf::Sound sound;
			if (is_correct) {
				sound.setBuffer(celebration);
				sound.play();
				sf::Clock clock;
				while (clock.getElapsedTime().asSeconds() != 3)
					;
				// we can move on to the next fact
				fact_index++;
				if (fact_index == facts.size()) {
					window.close();
				}
				mfact = facts[fact_index];
			} else {
				sound.setBuffer(sadcry);
				sound.play();
				sf::Clock clock;
				while (clock.getElapsedTime().asSeconds() != 3)
					;
				mfact.flip();
			}

			// reset state
			answer_given = false;
			index = 0;
			input[0] = 0;
			input[1] = 0;
		} else {
			// Display countdown timer
		}

		window.clear();
		mfact.draw(window, font);

		auto rect = input_string.getLocalBounds();
		auto window_size = window.getSize();
		input_string.setPosition(window_size.x / 2 - rect.width /2, 400);
		window.draw(input_string);
		window.display();
	}

	return 0;
}

/*
std::vector<MathFact> create_facts() {
	std::vector<MathFact> facts(100);
	for(int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			MathFact mf { i, j, i*j };
			facts.push_back(mf);
		}
	}

	return facts;
}
*/
