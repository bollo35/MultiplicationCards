#pragma once
#include "state.h"

class MainMenuState : public State {
	public:
		MainMenuState(int width, int height, sf::Font& font, int selected=0);
		virtual void draw(sf::RenderWindow& w);
		virtual void update(sf::Event, std::stack< std::unique_ptr<State> >& stack);
		virtual bool done();
		~MainMenuState();
	private:
		int selected_;
		int width_;
		int height_;
		bool done_;
		sf::Font& font_;
		sf::Color color_selected_;
		sf::Color color_unselected_;
};
