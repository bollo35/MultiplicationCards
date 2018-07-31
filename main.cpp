#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "quiz_state.h"
#include <stack>

int main(int argc, char** argv) {

	// begin the SFML things!
	sf::RenderWindow window(sf::VideoMode(800, 600), "Math game!");
	std::vector<int> which_facts = {2, 3, 4};
	std::stack<std::unique_ptr<State> > state_stack;
	state_stack.push(std::make_unique<QuizState>(800, 600, which_facts));
	while ( window.isOpen() ) {

		sf::Event event;
		while ( window.pollEvent(event) ) {
			if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::KeyPressed) {
				auto& state = state_stack.top();
				state->update(event, state_stack);
			}
		}

		if (state_stack.empty()) window.close();
		else {
			window.clear();
			auto& state = state_stack.top();
			state->draw(window);
			window.display();
		}
	}
	return 0;
}
