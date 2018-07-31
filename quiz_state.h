#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include "state.h"
#include "fact.h"

class QuizState : public State {
	public:
		QuizState(int width, int height, std::vector<int> which_facts);
		virtual void draw(sf::RenderWindow& w);
		virtual void update(sf::Event event,std::stack<std::unique_ptr<State> >& stack);
	private:
		std::vector<MultiplicationFact> facts_;
		int width_;
		int height_;
		int index_;
		int current_fact_;
		char input_[3];
		sf::Font font_;
		sf::SoundBuffer right_answer_;
		sf::SoundBuffer wrong_answer_;
};