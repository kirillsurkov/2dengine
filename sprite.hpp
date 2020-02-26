#pragma once

#include "renderable.hpp"

class sprite_t : public renderable_t {
private:
	image_ptr m_image;
	float m_rotation;
	glm::vec2 m_coords;
	glm::vec4 m_color;

public:
	sprite_t(image_ptr image);
	virtual ~sprite_t();

	virtual void set_rotation(float rotation) override;
	virtual void set_coords(float x, float y) override;
	virtual void set_color(const glm::vec4& color) override;
	virtual image_ptr get_image() override;
	virtual float get_rotation() override;
	virtual const glm::vec2& get_coords() override;
	virtual const glm::vec4& get_color() override;
};
