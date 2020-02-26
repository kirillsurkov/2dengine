#include "glfw_window.hpp"

glfw_window_t::glfw_window_t(int width, int height, const std::string& title) :
	m_key_callback(nullptr)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!m_window) {
		throw std::runtime_error("glfwCreateWindow failed");
	}
	glfwSetWindowUserPointer(m_window, this);
	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int, int action, int) {
		auto self = static_cast<glfw_window_t*>(glfwGetWindowUserPointer(window));
		if (!self->m_key_callback || action != GLFW_PRESS) {
			return;
		}
		switch (key) {
		case GLFW_KEY_ESCAPE: {
			self->m_key_callback(key::esc);
			break;
		}
		case GLFW_KEY_LEFT: {
			self->m_key_callback(key::left);
			break;
		}
		case GLFW_KEY_RIGHT: {
			self->m_key_callback(key::right);
			break;
		}
		case GLFW_KEY_UP: {
			self->m_key_callback(key::up);
			break;
		}
		case GLFW_KEY_DOWN: {
			self->m_key_callback(key::down);
			break;
		}
		}
	});
}

glfw_window_t::~glfw_window_t() {
	glfwDestroyWindow(m_window);
}

void glfw_window_t::get_size(int& width, int& height) {
	glfwGetWindowSize(m_window, &width, &height);
}

void glfw_window_t::set_key_callback(const std::function<void(key)>& callback) {
	m_key_callback = callback;
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
