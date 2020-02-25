#include "sprite.hpp"

sprite_t::sprite_t(image_ptr image) :
	m_image(image),
	m_transform(1.0f),
	m_color(1.0f)
{
}

sprite_t::~sprite_t() {
}

image_ptr sprite_t::get_image() {
	return m_image;
}

const glm::mat4& sprite_t::get_transform() {
	return m_transform;
}

const glm::vec4& sprite_t::get_color() {
	return m_color;
}
