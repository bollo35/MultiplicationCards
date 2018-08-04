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
	std::stack<std::unique_ptr<State> > state_stack;
	state_stack.push(std::make_unique<MainMenuState>(800, 600, font, 0));
	while ( window.isOpen() ) {
		if (state_stack.empty()) window.close();

		bool state_finished = false;

		sf::Event event;
		while ( window.pollEvent(event) ) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else {
				auto& state = state_stack.top();
				state->update(event, state_stack);
				state_finished = state->done();
			}
		}

		if (state_finished) {
//			std::cerr << "----Removing a state-----\n";
			state_stack.pop();
//			std::cerr << "Stack popped!\n";
		} else {
			window.clear();
			auto& state = state_stack.top();
			state->draw(window);
//			std::cerr << "Drawing\n";
			window.display();
		}
//		std::cerr << "End of loop\n";
	}
//	std::cerr <<"Normal exit\n";
	return 0;
}
