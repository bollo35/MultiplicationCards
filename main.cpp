#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "main_menu_state.h"
#include <stack>

int main(int argc, char** argv) {
	// load font
	sf::Font font;
	if (!font.loadFromFile("Schools Out!!!.otf")) {
		std::cerr << "Unable to load 'Schools Out!!!.otf'" << std::endl;
		return 1;
	}

	// begin the SFML things!
	sf::RenderWindow window(sf::VideoMode(800, 600), "Math game!");
	std::vector<int> which_facts = {2, 3, 4};
	std::stack<State*> state_stack;
	state_stack.push(new MainMenuState(800, 600, font, 0));
	while ( window.isOpen() ) {
		if (state_stack.empty()) window.close();

		sf::Event event;
		while ( window.pollEvent(event) ) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else {
				auto& state = state_stack.top();
				state->update(event, state_stack);
			}
		}

		while (!state_stack.empty() && state_stack.top()->done()) {
			auto& ptr = state_stack.top();
			delete ptr;
			state_stack.pop();
		}

		if (!state_stack.empty()) {
			window.clear();
			auto& state = state_stack.top();
			state->draw(window);
			window.display();
		}
	}
	return 0;
}
