#pragma once

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "image.hpp"

class renderable_t {
public:
	virtual void set_rotation(float rotation) = 0;
	virtual void set_coords(float x, float y) = 0;
	virtual void set_color(const glm::vec4& color) = 0;
	virtual image_ptr get_image() = 0;
	virtual float get_rotation() = 0;
	virtual const glm::vec2& get_coords() = 0;
	virtual const glm::vec4& get_color() = 0;
	virtual void update(float delta) {}
};

typedef std::shared_ptr<renderable_t> renderable_ptr;
