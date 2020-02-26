#include "sprite.hpp"

sprite_t::sprite_t(image_ptr image) :
	m_image(image),
	m_rotation(0.0f),
	m_coords(0.0f),
	m_color(1.0f)
{
}

sprite_t::~sprite_t() {
}

void sprite_t::set_rotation(float rotation) {
	m_rotation = rotation;
}

void sprite_t::set_coords(float x, float y) {
	m_coords.x = x;
	m_coords.y = y;
}

void sprite_t::set_color(const glm::vec4& color) {
	m_color = color;
}

image_ptr sprite_t::get_image() {
	return m_image;
}

float sprite_t::get_rotation() {
	return m_rotation;
}

const glm::vec2& sprite_t::get_coords() {
	return m_coords;
}

const glm::vec4& sprite_t::get_color() {
	return m_color;
}
