#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/color_space.hpp>

#include "object_food.hpp"
#include "animated_sprite.hpp"

object_food_t::object_food_t(engine_ptr engine, int x, int y) :
	m_timer(0.0f)
{
	auto sprite = std::make_shared<animated_sprite_t>();
	sprite->add_image(engine->load_image("food_1.png"));
	sprite->add_image(engine->load_image("food_2.png"));
	sprite->add_image(engine->load_image("food_3.png"));
	sprite->set_coords(x, y);
	m_renderables.push_back(sprite);
	m_sprite = sprite;
}

object_food_t::~object_food_t() {
}

const glm::vec2& object_food_t::get_coords() {
	return m_sprite->get_coords();
}

void object_food_t::update(float delta) {
	m_timer += delta * 2.0f;
	if (m_timer >= 1.0f) {
		m_timer -= 1.0f;
	}
	auto color = glm::rgbColor(glm::vec3(m_timer * 360.0f, 1.0f, 1.0f));
	m_sprite->set_color(glm::vec4(color, 1.0f));
}
