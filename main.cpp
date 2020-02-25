#include <chrono>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "context.hpp"
#include "glfw_window.hpp"
#include "opengl_render.hpp"
#include "sprite.hpp"
#include "animated_sprite.hpp"

int main() {
	try {
		auto context = std::make_shared<context_t>();
		context->set_window_size(800, 600);

		opengl_render_t render(context);

		auto window = render.create_window("Game");
		window->set_current();

		render.init();

		sprite_t sprite1(render.load_image("food_1.png"));

		animated_sprite_t sprite2;
		sprite2.set_animation_speed(0.08f);
		sprite2.add_image(render.load_image("food_1.png"));
		sprite2.add_image(render.load_image("food_2.png"));
		sprite2.add_image(render.load_image("food_3.png"));

		try {
			auto last_time = std::chrono::system_clock::now();
			while (window->is_alive()) {
				auto current_time = std::chrono::system_clock::now();
				float delta = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_time).count() / 1000.0f;
				last_time = current_time;

				sprite1.update(delta);
				sprite2.update(delta);

				int width;
				int height;
				context->get_window_size(width, height);
				glm::mat4 ortho(glm::ortho(-0.5f * width, 0.5f * width, -0.5f * height, 0.5f * height));

				render.clear();
				render.draw_image(sprite1.get_image(), ortho * sprite1.get_transform());
				render.draw_image(sprite2.get_image(), glm::translate(ortho * sprite2.get_transform(), glm::vec3(32.0f, 0.0f, 0.0f)));

				window->swap_buffers();
				window->poll_events();
			}
		} catch (const std::exception& e) {
			std::cout << "Exception in loop: " << e.what() << std::endl;
		}
	} catch (const std::exception& e) {
		std::cout << "Exception in init: " << e.what() << std::endl;
	}
	return 0;
}
