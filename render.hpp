#pragma once

#include <glm/mat4x4.hpp>

#include "window.hpp"
#include "image.hpp"

class render_t {
public:
	virtual window_ptr create_window(const std::string& title) = 0;
	virtual image_ptr load_image(const std::string& filename) = 0;
	virtual void draw_image(image_ptr image, const glm::mat4& mvp) = 0;
	virtual void clear() = 0;
};

typedef std::shared_ptr<render_t> render_ptr;
