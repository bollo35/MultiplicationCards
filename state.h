#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include <iostream>

class State {
	public:
		virtual void draw(sf::RenderWindow& w) = 0;
		virtual void update(sf::Event event,std::stack<State*>& stack) = 0;
		virtual bool done() = 0;
};
