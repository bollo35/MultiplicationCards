#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class MultiplicationFact {
	public:
		MultiplicationFact(int op1, int op2, int times_correct=0, int times_incorrect=0, int response_time=60);
		void flip();
		void update_response_time(int response_time);
		bool check_answer(int answer);
		void draw(sf::RenderWindow& w, const sf::Font& font);
	private:
		int op1;
		int op2;
		int times_correct;
		int times_incorrect;
		int response_time;
		bool flipped;
		std::string fact_string;
};
