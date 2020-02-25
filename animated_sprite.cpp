#include "animated_sprite.hpp"

animated_sprite_t::animated_sprite_t() :
	m_timer(0.0f),
	m_animation_speed(0.1f),
	m_current_image(0),
	m_transform(1.0f),
	m_color(1.0f)
{
}

animated_sprite_t::~animated_sprite_t() {
}

void animated_sprite_t::set_animation_speed(float speed) {
	m_animation_speed = speed;
}

void animated_sprite_t::add_image(image_ptr image) {
	m_images.push_back(image);
}

image_ptr animated_sprite_t::get_image() {
	if (m_images.size() == 0) {
		return nullptr;
	}
	return m_images[m_current_image];
}

const glm::mat4& animated_sprite_t::get_transform() {
	return m_transform;
}

const glm::vec4& animated_sprite_t::get_color() {
	return m_color;
}

void animated_sprite_t::update(float delta) {
	m_timer += delta;
	if (m_timer >= m_animation_speed) {
		m_timer -= m_animation_speed;
		m_current_image = (m_current_image + 1) % m_images.size();
	}
}
