#pragma once
#include "state.h"

class EndOfReviewState : public State {
	public:
		EndOfReviewState(int width, int height, int num_correct, int num_facts, sf::Font& font);
		virtual void draw(sf::RenderWindow& w);
		virtual void update(sf::Event event, std::stack<State*>& stack);
		virtual bool done();
	private:
		int width_;
		int height_;
		int num_correct_;
		int num_facts_;
		bool done_;
		sf::Font& font_;
};
