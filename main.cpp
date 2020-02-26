#include <iostream>

#include "engine.hpp"
#include "object_snake.hpp"
#include "object_food.hpp"

int main() {
	try {
		auto engine = std::make_shared<engine_t>(800, 600, "Game");

		auto scene = engine->get_scene();
		scene->set_scale(32);

		auto snake = scene->add_object(std::make_shared<object_snake_t>(engine, 0.5f, 0, -1));
		auto food = scene->add_object(std::make_shared<object_food_t>(engine, 0, 0));

		try {
			engine->main_loop([&snake, &food, &scene, &engine](float delta) {
				for (const auto& input : engine->get_inputs()) {
					if (input == window_t::key::esc) {
						return false;
					}
				}
				const auto& snake_coords = snake->get_head_coords();
				const auto& food_coords = food->get_coords();
				if (snake_coords.x == food_coords.x && snake_coords.y == food_coords.y) {
					scene->remove_object(food);
					snake->grow();
					food = scene->add_object(std::make_shared<object_food_t>(engine, std::rand() % 10 - 5, std::rand() % 10 - 5));
				}
				return true;
			});
		} catch (const std::exception& e) {
			std::cout << "Exception in loop: " << e.what() << std::endl;
		}
	} catch (const std::exception& e) {
		std::cout << "Exception in init: " << e.what() << std::endl;
	}
	return 0;
}
