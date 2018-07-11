#include "fact.h"
#include <sstream>
#include <assert.h>

MultiplicationFact::MultiplicationFact(int op1, int op2, int times_correct, int times_incorrect, int response_time) : op1(op1), op2(op2),
  times_correct(times_correct),
  times_incorrect(times_incorrect),
  response_time(response_time),
  flipped(false) {
	assert(op1 > -1 && op1 < 10);
	assert(op2 > -1 && op2 < 10);
	std::stringstream ss(std::stringstream::in | std::stringstream::out);
	ss << op1 << " x " << op2;
	fact_string = ss.str();
}

void MultiplicationFact::flip() {
	if (!flipped) flipped = true;
}

void MultiplicationFact::update_response_time(int response_time) {
	this->response_time = response_time;
}

bool MultiplicationFact::check_answer(int answer) {
	auto is_correct = op1*op2 == answer;
	// adjust time limit for next time
	if (is_correct) {
	} else {
	}
	return is_correct;
}

void MultiplicationFact::draw(sf::RenderWindow& w, const sf::Font& font) {
	// we will want to use this to scale our drawing
	// eventually. Maybe?
	auto size = w.getSize(); 
	if (flipped) {
		std::stringstream ss (std::stringstream::in | std::stringstream::out);
		ss << fact_string << " means we have " << op1 << " group" << (op1 > 1 ? "s": "") << " of " << op2 <<" things";
		sf::Text explanation;
		explanation.setFont(font);
		explanation.setString(ss.str());
		explanation.setCharacterSize(40);
		explanation.setFillColor(sf::Color::Red);
		explanation.setPosition(0,0);
		w.draw(explanation);

		auto position = explanation.getGlobalBounds();

		if (op1 != 0 && op2 != 0) {
			std::string group;
			for (int i = 0; i < op1; ++i) {
				group += ".  ";
			}

			explanation.setString(group);
			explanation.setCharacterSize(80);
			auto dimensions = explanation.getLocalBounds();
			auto group_height = dimensions.height;
			auto group_x = size.x / 2 - dimensions.width / 2;
			auto group_y = position.height + group_height / 2;
			for (int i = 0; i < op2; ++i) {
				explanation.setPosition(group_x, group_y);
				w.draw(explanation);
				group_y += group_height;
			}
			position = explanation.getGlobalBounds();
		}
		explanation.setCharacterSize(50);
		explanation.setString("Guess again!");
		auto dimensions = explanation.getLocalBounds();
		explanation.setPosition(size.x / 2 - dimensions.width / 2, position.top + position.height /*+ group_y*/);
		w.draw(explanation);
	} else {
		// display the multiplication fact, and update the timer
		sf::Text text;
		text.setFont(font);
		text.setString(fact_string);
		text.setCharacterSize(80);
		text.setFillColor(sf::Color::Red);
		auto rect = text.getLocalBounds();
		text.setPosition(size.x / 2 - rect.width/2, size.y/2 - rect.height/2);
		w.draw(text);
	}
}
