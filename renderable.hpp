#pragma once

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "image.hpp"

class renderable_t {
public:
	virtual image_ptr get_image() = 0;
	virtual const glm::mat4& get_transform() = 0;
	virtual const glm::vec4& get_color() = 0;
	virtual void update(float delta) {}
};
