#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>

class State {
	public:
		virtual void draw(sf::RenderWindow& w) = 0;
		virtual void update(sf::Event event,std::stack<std::unique_ptr<State> >& stack) = 0;
};
