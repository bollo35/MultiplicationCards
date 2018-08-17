#include "quiz_state.h"
#include "end_of_review_state.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <sstream>

QuizState::QuizState(int width, int height, std::vector<int> which_facts, sf::Font& font) : 
  width_{width},
  height_{height},
  index_{0},
  current_fact_{0},
  num_correct_{0},
  input_{0, 0, 0},
  done_{false},
  font_{font} {
	for (auto table : which_facts) {
		for (int i = 1; i < 10; ++i) {
			auto fact = MultiplicationFact(table, i);
			facts_.push_back(fact);
		}
	}

	// shuffle the facts
	std::srand( unsigned (std::time(0)) );
	std::random_shuffle(facts_.begin(), facts_.end());

	// load resources
	if (!right_answer_.loadFromFile("celebration-short.ogg")) {
		throw std::runtime_error("Unable to open 'celebration-short.ogg'");
	}

	if (!wrong_answer_.loadFromFile("sadcry5.ogg")) {
		throw std::runtime_error("Unable to open 'sadcry5.ogg'");
	}
}

void QuizState::draw(sf::RenderWindow& w) {
	std::stringstream ss(std::stringstream::in | std::stringstream::out);
	ss << (current_fact_+1) << " of " << facts_.size();
	sf::Text progress;
	progress.setString(ss.str());
	progress.setCharacterSize(40);
	progress.setFont(font_);
	progress.setPosition(0, 0);

	auto color = sf::Color(255, 102, 178);
	sf::Text input_string;
	input_string.setString(std::string(input_));
	input_string.setCharacterSize(80);
	input_string.setFillColor(color);
	input_string.setFont(font_);
	auto input_rect = input_string.getLocalBounds();
	input_string.setPosition( width_ / 2 - input_rect.width / 2,
	                          height_ / 2 + input_rect.height); // kind of a guess...

	w.draw(input_string);
	w.draw(progress);
	facts_[current_fact_].draw(w, font_);
}

void QuizState::update(sf::Event event, std::stack<State*>& stack) {
	// make sure we don't do anything if we're done
	if (done_) return;
	bool answer_given = false;
	if (event.type == sf::Event::KeyPressed) {
		switch(event.key.code) {
			case sf::Keyboard::Key::Num0:
			case sf::Keyboard::Key::Numpad0:
				if ( index_ < 2 ) {
					input_[index_++] = '0';
				}
				break;
			case sf::Keyboard::Key::Num1:
			case sf::Keyboard::Key::Numpad1:
				if ( index_ < 2 ) {
					input_[index_++] = '1';
				}
				break;
			case sf::Keyboard::Key::Num2:
			case sf::Keyboard::Key::Numpad2:
				if ( index_ < 2 ) {
					input_[index_++] = '2';
				}
				break;
			case sf::Keyboard::Key::Num3:
			case sf::Keyboard::Key::Numpad3:
				if ( index_ < 2 ) {
					input_[index_++] = '3';
				}
				break;
			case sf::Keyboard::Key::Num4:
			case sf::Keyboard::Key::Numpad4:
				if ( index_ < 2 ) {
					input_[index_++] = '4';
				}
				break;
			case sf::Keyboard::Key::Num5:
			case sf::Keyboard::Key::Numpad5:
				if ( index_ < 2 ) {
					input_[index_++] = '5';
				}
				break;
			case sf::Keyboard::Key::Num6:
			case sf::Keyboard::Key::Numpad6:
				if ( index_ < 2 ) {
					input_[index_++] = '6';
				}
				break;
			case sf::Keyboard::Key::Num7:
			case sf::Keyboard::Key::Numpad7:
				if ( index_ < 2 ) {
					input_[index_++] = '7';
				}
				break;
			case sf::Keyboard::Key::Num8:
			case sf::Keyboard::Key::Numpad8:
				if ( index_ < 2 ) {
					input_[index_++] = '8';
				}
				break;
			case sf::Keyboard::Key::Num9:
			case sf::Keyboard::Key::Numpad9:
				if ( index_ < 2 ) {
					input_[index_++] = '9';
				}
				break;
			case sf::Keyboard::Key::BackSpace:
				if ( index_ > 0 ) {
					input_[--index_] = 0;
				}
				break;
			case sf::Keyboard::Key::Return:
				answer_given = index_ > 0;
				break;
			case sf::Keyboard::Key::Escape:
				done_ = true;
				return;
				break;
		}
	}

	if (answer_given) {
		auto input_answer = atoi(input_);
		auto is_correct = facts_[current_fact_].check_answer(input_answer);
		sf::Sound sound;
		if (is_correct) {
			if (!facts_[current_fact_].is_flipped())
				++num_correct_;
			sound.setBuffer(right_answer_);
			sound.play();
			while (sound.getStatus() == sf::SoundSource::Playing)
				;
			current_fact_++;
			if (current_fact_ == facts_.size()) {
				// TODO: transition to EndOfReview
				done_ = true;
				stack.push( new EndOfReviewState(width_, height_, num_correct_, facts_.size(), font_) );
			}
		} else {
			sound.setBuffer(wrong_answer_);
			sound.play();
			while (sound.getStatus() == sf::SoundSource::Playing)
				;
			facts_[current_fact_].flip();
		}
		index_ = 0;
		input_[0] = 0;
		input_[1] = 0;
	}
}

bool QuizState::done() {
	return done_;
}
