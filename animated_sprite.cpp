#include "animated_sprite.hpp"

animated_sprite_t::animated_sprite_t() :
	m_timer(0.0f),
	m_animation_speed(0.1f),
	m_current_image(0),
	m_rotation(0.0f),
	m_coords(0.0f),
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

void animated_sprite_t::set_rotation(float rotation) {
	m_rotation = rotation;
}

void animated_sprite_t::set_coords(float x, float y) {
	m_coords.x = x;
	m_coords.y = y;
}

void animated_sprite_t::set_color(const glm::vec4& color) {
	m_color = color;
}

image_ptr animated_sprite_t::get_image() {
	if (m_images.size() == 0) {
		return nullptr;
	}
	return m_images[m_current_image];
}

float animated_sprite_t::get_rotation() {
	return m_rotation;
}

const glm::vec2& animated_sprite_t::get_coords() {
	return m_coords;
}

const glm::vec4& animated_sprite_t::get_color() {
	return m_color;
}

void animated_sprite_t::update(float delta) {
	m_timer += delta;
	if (m_timer >= m_animation_speed) {
		m_timer = 0;
		m_current_image = (m_current_image + 1) % m_images.size();
	}
}
