#include <iostream>
#include <GL/glew.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include "opengl_render.hpp"

opengl_render_t::opengl_render_t(context_ptr context) :
	m_context(context)
{
	if (!glfwInit()) {
		throw std::runtime_error("glfwInit failed");
	}
}

opengl_render_t::~opengl_render_t() {
	glDeleteShader(m_shader_vs);
	glDeleteShader(m_shader_fs);
	glDeleteProgram(m_shader_program);
	glfwTerminate();
}

void opengl_render_t::init() {
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("glewInit failed");
	}

	int width;
	int height;
	m_context->get_window_size(width, height);
	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	const char* vs_src = 
		"#version 130\n\
		precision highp float;\n\
		uniform mat4 u_mvp;\n\
		out vec2 v_uv;\n\
		void main() {\n\
			vec2 pos = vec2(0.0);\n\
			switch (gl_VertexID) {\n\
				case 0: pos = vec2(1.0, -1.0); break;\n\
				case 1: pos = vec2(1.0, 1.0); break;\n\
				case 2: pos = vec2(-1.0, -1.0); break;\n\
				case 3: pos = vec2(-1.0, 1.0); break;\n\
			}\n\
			v_uv = (pos + 1.0) / 2.0;\n\
			gl_Position = u_mvp * vec4(pos, 0.0, 1.0);\n\
		}";

	const char* fs_src = 
		"#version 130\n\
		precision highp float;\n\
		uniform sampler2D u_texture;\n\
		in vec2 v_uv;\n\
		out vec4 outColor;\n\
		void main() {\n\
			outColor = texture2D(u_texture, v_uv);\n\
		}";

	char buf[512];
	int len;

	m_shader_vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_shader_vs, 1, &vs_src, nullptr);
	glCompileShader(m_shader_vs);
	glGetShaderInfoLog(m_shader_vs, 512, &len, buf);
	std::cout << std::string(buf, len) << std::endl;

	m_shader_fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_shader_fs, 1, &fs_src, nullptr);
	glCompileShader(m_shader_fs);
	glGetShaderInfoLog(m_shader_fs, 512, &len, buf);
	std::cout << std::string(buf, len) << std::endl;

	m_shader_program = glCreateProgram();
	glAttachShader(m_shader_program, m_shader_vs);
	glAttachShader(m_shader_program, m_shader_fs);
	glLinkProgram(m_shader_program);

	glUseProgram(m_shader_program);

	m_shader_loc_mvp = glGetUniformLocation(m_shader_program, "u_mvp");
	m_shader_loc_texture = glGetUniformLocation(m_shader_program, "u_texture");
}

window_ptr opengl_render_t::create_window(const std::string& title) {
	return std::make_shared<glfw_window_t>(m_context, title);
}

image_ptr opengl_render_t::load_image(const std::string& filename) {
	if (m_images_cache.find(filename) == m_images_cache.end()) {
		auto image = std::make_shared<image_t>("res/" + filename);
		std::vector<char> pixels(image->get_pixels());
		GLuint id;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->get_width(), image->get_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		m_images_cache[filename] = image;
		m_images[image] = id;
	}
	return m_images_cache[filename];
}

void opengl_render_t::draw_image(image_ptr image, const glm::mat4& mvp) {
	glBindTexture(GL_TEXTURE_2D, m_images[image]);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(m_shader_loc_texture, 0);
	glUniformMatrix4fv(m_shader_loc_mvp, 1, GL_FALSE, &glm::scale(mvp, glm::vec3(0.5f * image->get_width(), 0.5f * image->get_height(), 1.0f))[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void opengl_render_t::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}
