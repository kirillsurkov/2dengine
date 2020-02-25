#pragma once

#include <unordered_map>

#include "render.hpp"
#include "context.hpp"
#include "glfw_window.hpp"

class opengl_render_t : public render_t {
private:
	context_ptr m_context;
	std::unordered_map<std::string, image_ptr> m_images_cache;
	std::unordered_map<image_ptr, GLuint> m_images;
	GLuint m_shader_vs;
	GLuint m_shader_fs;
	GLuint m_shader_program;
	GLint m_shader_loc_mvp;
	GLint m_shader_loc_texture;

public:
	opengl_render_t(context_ptr context);
	~opengl_render_t();

	void init();
	virtual window_ptr create_window(const std::string& title) override;
	virtual image_ptr load_image(const std::string& filename) override;
	virtual void draw_image(image_ptr image, const glm::mat4& mvp) override;
	virtual void clear() override;
};
