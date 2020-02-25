#pragma once

#include "renderable.hpp"

class sprite_t : public renderable_t {
private:
	image_ptr m_image;
	glm::mat4 m_transform;
	glm::vec4 m_color;

public:
	sprite_t(image_ptr image);
	virtual ~sprite_t();

	virtual image_ptr get_image() override;
	virtual const glm::mat4& get_transform() override;
	virtual const glm::vec4& get_color() override;
};
