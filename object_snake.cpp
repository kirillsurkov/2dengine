#include <cmath>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/color_space.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "object_snake.hpp"
#include "animated_sprite.hpp"

object_snake_t::corner_sprite_t::corner_sprite_t(image_ptr image) :
	sprite_t(image)
{
}

object_snake_t::object_snake_t(engine_ptr engine, float speed, int x, int y) :
	m_engine(engine),
	m_speed(speed),
	m_timer(0.0f),
	m_color_counter(0),
	m_grow(false),
	m_direction(direction::none),
	m_prev_direction(direction::none)
{
	auto sprite = create_head(x, y, 0.0f);
	sprite->set_color(get_piece_color());
	m_renderables.push_back(sprite);
}

object_snake_t::~object_snake_t() {
}

renderable_ptr object_snake_t::create_head(int x, int y, float rotation) {
	auto sprite = std::make_shared<animated_sprite_t>();
	sprite->add_image(m_engine->load_image("snake_head_1.png"));
	sprite->add_image(m_engine->load_image("snake_head_2.png"));
	sprite->add_image(m_engine->load_image("snake_head_3.png"));
	sprite->add_image(m_engine->load_image("snake_head_4.png"));
	sprite->set_coords(x, y);
	sprite->set_rotation(rotation);
	return sprite;
}

renderable_ptr object_snake_t::create_body(int x, int y, float rotation) {
	auto sprite = std::make_shared<sprite_t>(m_engine->load_image("snake_body.png"));
	sprite->set_coords(x, y);
	sprite->set_rotation(rotation);
	return sprite;
}

renderable_ptr object_snake_t::create_corner(int x, int y, float rotation) {
	auto sprite = std::make_shared<corner_sprite_t>(m_engine->load_image("snake_corner.png"));
	sprite->set_coords(x, y);
	sprite->set_rotation(rotation);
	return sprite;
}

renderable_ptr object_snake_t::create_tail(int x, int y, float rotation) {
	auto sprite = std::make_shared<sprite_t>(m_engine->load_image("snake_tail.png"));
	sprite->set_coords(x, y);
	sprite->set_rotation(rotation);
	return sprite;
}

void object_snake_t::get_new_transform(int& x, int& y, float& rotation) {
	switch (m_direction) {
	case direction::left: {
		rotation = M_PI_2;
		x--;
		break;
	}
	case direction::right: {
		rotation = -M_PI_2;
		x++;
		break;
	}
	case direction::up: {
		rotation = 0;
		y++;
		break;
	}
	case direction::down: {
		rotation = M_PI;
		y--;
		break;
	}
	}
}

float object_snake_t::get_corner_rotation() {
	float corner_rotation = 0.0f;
	switch (m_prev_direction) {
	case direction::up: {
		corner_rotation = (m_direction == direction::right) ? 0 : -M_PI_2;
		break;
	}
	case direction::down: {
		corner_rotation = (m_direction == direction::right) ? M_PI_2 : M_PI;
		break;
	}
	case direction::left: {
		corner_rotation = (m_direction == direction::up) ? M_PI_2 : 0;
		break;
	}
	case direction::right: {
		corner_rotation = (m_direction == direction::up) ? M_PI : -M_PI_2;
		break;
	}
	}
	return corner_rotation;
}

glm::vec4 object_snake_t::get_piece_color() {
	glm::vec4 color = glm::vec4(glm::rgbColor(glm::vec3(m_color_counter, 1.0f, 1.0f)), 1.0f);
	m_color_counter = (m_color_counter + 30) % 360;
	return color;
}

const glm::vec2& object_snake_t::get_head_coords() {
	return m_renderables.front()->get_coords();
}

void object_snake_t::grow() {
	m_grow = true;
	m_speed *= 0.99f;
}

void object_snake_t::update(float delta) {
	for (const auto& input : m_engine->get_inputs()) {
		switch (input) {
		case window_t::key::left: {
			if (m_prev_direction != direction::right) {
				m_direction = direction::left;
			}
			break;
		}
		case window_t::key::right: {
			if (m_prev_direction != direction::left) {
				m_direction = direction::right;
			}
			break;
		}
		case window_t::key::up: {
			if (m_prev_direction != direction::down) {
				m_direction = direction::up;
			}
			break;
		}
		case window_t::key::down: {
			if (m_prev_direction != direction::up) {
				m_direction = direction::down;
			}
			break;
		}
		}
	}

	m_timer += delta;
	if (m_timer >= m_speed) {
		m_timer -= m_speed;

		auto old_head = m_renderables.front();

		if (!m_grow) {
			m_renderables.pop_back();
		}

		float new_head_rotation = 0.0f;
		glm::ivec2 new_head_coords = old_head->get_coords();
		get_new_transform(new_head_coords.x, new_head_coords.y, new_head_rotation);

		if (m_renderables.size() >= 1) {
			const auto& piece = m_renderables.back();
			float tail_rotation = piece->get_rotation();
			auto tail_coords = piece->get_coords();
			glm::vec4 tail_color = piece->get_color();
			m_renderables.pop_back();
			if (m_renderables.size() > 0) {
				glm::vec2 dpos = glm::normalize(m_renderables.back()->get_coords() - tail_coords);
				tail_rotation = std::atan2(dpos.y, dpos.x) - M_PI_2;
			} else {
				tail_rotation = new_head_rotation;
			}
			auto sprite = create_tail(tail_coords.x, tail_coords.y, tail_rotation);
			sprite->set_color(tail_color);
			m_renderables.push_back(sprite);
		}

		if (m_renderables.size() >= 2) {
			float old_head_rotation = old_head->get_rotation();
			auto old_head_coords = old_head->get_coords();
			glm::vec4 old_head_color = old_head->get_color();
			m_renderables.pop_front();
			renderable_ptr sprite;
			if (m_prev_direction == m_direction) {
				sprite = create_body(old_head_coords.x, old_head_coords.y, old_head_rotation);
			} else {
				sprite = create_corner(old_head_coords.x, old_head_coords.y, get_corner_rotation());
			}
			sprite->set_color(old_head_color);
			m_renderables.push_front(sprite);
		}

		auto sprite = create_head(new_head_coords.x, new_head_coords.y, new_head_rotation);
		sprite->set_color(get_piece_color());
		m_renderables.push_front(sprite);

		m_prev_direction = m_direction;
		m_grow = false;
	}
}
