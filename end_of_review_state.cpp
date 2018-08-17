#include "end_of_review_state.h"
#include <sstream>

EndOfReviewState::EndOfReviewState(int width, int height, int num_correct, int num_facts, sf::Font& font) :
  width_{width},
  height_{height},
  num_correct_{num_correct},
  num_facts_{num_facts},
  done_{false},
  font_(font) {}

void EndOfReviewState::draw(sf::RenderWindow& w) {
	// compose the string to draw
	sf::Text results;
	results.setCharacterSize(40);
	results.setFont(font_);
	// determine percentage correct
	auto score = (double) num_correct_ / (double) num_facts_;
	std::stringstream ss(std::stringstream::in | std::stringstream::out);
	ss << "You got " << num_correct_ << " of " << num_facts_ << " correct" << ((score > 0.79) ? "!" : ".") << "\n";
	if (score > 0.89) {
		ss << "GREAT JOB!";
	} else if (score > 0.69) {
		ss << "Not bad!";
	} else {
		ss << "You need to study more.";
	}
	results.setString(ss.str());

	// center the string
	auto size = results.getLocalBounds();
	// we're just going to assume that the string doesn't exceed
	// the screen's dimensions
	auto x = (width_ - size.width) / 2;
	auto y = (height_ - size.height) / 2;
	results.setPosition(x, y);
	w.draw(results);
}

void EndOfReviewState::update(sf::Event event, std::stack<State*>& stack) {
	if (event.type == sf::Event::KeyPressed &&
	    event.key.code == sf::Keyboard::Key::Return) {
		done_ = true;
	}
}

bool EndOfReviewState::done() {
	return done_;
}
