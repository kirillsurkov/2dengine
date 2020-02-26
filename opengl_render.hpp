#pragma once

#include <unordered_map>

#include "render.hpp"
#include "glfw_window.hpp"

class opengl_render_t : public render_t {
private:
	int m_width;
	int m_height;
	std::unordered_map<image_ptr, GLuint> m_images;
	GLuint m_shader_vs;
	GLuint m_shader_fs;
	GLuint m_shader_program;
	GLint m_shader_loc_mvp;
	GLint m_shader_loc_texture;
	GLint m_shader_loc_color;

public:
	opengl_render_t(int width, int height);
	~opengl_render_t();

	virtual void init() override;
	virtual window_ptr create_window(const std::string& title) override;
	virtual image_ptr load_image(const std::string& filename) override;
	virtual void draw_image(image_ptr image, const glm::vec4& color, const glm::mat4& mvp) override;
	virtual void clear() override;
};
