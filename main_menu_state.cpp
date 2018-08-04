#include "main_menu_state.h"
#include "quiz_state.h"
#include <cstdlib>
#include <iostream>

MainMenuState::MainMenuState(int width, int height, sf::Font& font, int selected) :
  font_(font),
  selected_{selected},
  done_{false},
  width_(width),
  height_(height) {
	// metallic gold!
	color_selected_.r = 212;
	color_selected_.g = 175;
	color_selected_.b = 55;
	// grey
	color_unselected_.r = 224;
	color_unselected_.g = 224;
	color_unselected_.b = 224;
}

void MainMenuState::draw(sf::RenderWindow& w) {
	// divide the visible space into 3 rows, 3 columns
	// and draw numbers to be selected...
	auto window_size = w.getSize();
	auto width = width_ / 3;
	auto height = height_ / 3;

	sf::Text number;
	number.setCharacterSize(80);
	number.setFont(font_);
	char num_str[2] = {0, 0};
	for (int x = 0; x < 3; ++x) {
		for (int y = 0; y < 3; ++y) {
			auto num = 3*x + y + 1;
			sprintf(num_str, "%d", num);
			number.setString(num_str);
			auto rect = number.getLocalBounds();
			auto num_width = rect.width;
			auto num_height = rect.height;

			number.setPosition( x * width + (width - num_width) / 2, y * height + (height - num_height) / 2 );
			auto mask = 1 << (num - 1);
			auto active = (selected_ & mask) == mask;
			if (active) {
				number.setFillColor(color_selected_);
			} else {
				number.setFillColor(color_unselected_);
			}
			w.draw(number);
		}
	}
}

void MainMenuState::update(sf::Event event, std::stack< std::unique_ptr<State> >& stack) {
	if (event.type == sf::Event::MouseButtonPressed && 
		event.mouseButton.button == sf::Mouse::Button::Left) {
		auto width = width_ / 3;
		auto height = height_ / 3;
		auto x = event.mouseButton.x / width;
		auto y = event.mouseButton.y / height;
		auto num = 3 * x + y + 1;
		selected_ ^= 1 << (num - 1);
	} else if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
		case sf::Keyboard::Key::Return: {
	       
			std::vector<int> which_facts;
			auto selected = selected_;
			for (int i = 0; i < 9; ++i) {
				if(selected & 1)
					which_facts.push_back(i+1);
				selected >>= 1;
			}
			stack.push( std::make_unique<QuizState>(width_, height_, which_facts, font_) );
		}
			break;
		case sf::Keyboard::Key::Escape:
			done_ = true;
			break;
		}
	}
}

bool MainMenuState::done() {
	return done_;
}

MainMenuState::~MainMenuState() { std::cerr << "Destructor called!" << std::endl; }
