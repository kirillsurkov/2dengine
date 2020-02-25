#pragma once

#include <GLFW/glfw3.h>

#include "window.hpp"
#include "context.hpp"

class glfw_window_t : public window_t {
private:
	context_ptr m_context;
	GLFWwindow* m_window;

public:
	glfw_window_t(context_ptr context, const std::string& title);
	~glfw_window_t();

	virtual void set_current() override;
	virtual void swap_buffers() override;
	virtual void poll_events() override;
	virtual bool is_alive() override;
};
