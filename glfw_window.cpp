#include "glfw_window.hpp"

glfw_window_t::glfw_window_t(context_ptr context, const std::string& title) :
	m_context(context)
{
	int width;
	int height;
	m_context->get_window_size(width, height);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!m_window) {
		throw std::runtime_error("glfwCreateWindow failed");
	}
}

glfw_window_t::~glfw_window_t() {
	glfwDestroyWindow(m_window);
}

void glfw_window_t::set_current() {
	glfwMakeContextCurrent(m_window);
}

void glfw_window_t::swap_buffers() {
	glfwSwapBuffers(m_window);
}

void glfw_window_t::poll_events() {
	glfwPollEvents();
}

bool glfw_window_t::is_alive() {
	return !glfwWindowShouldClose(m_window);
}
