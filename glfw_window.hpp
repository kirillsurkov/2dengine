#pragma once

#include <GLFW/glfw3.h>

#include "window.hpp"

class glfw_window_t : public window_t {
private:
	GLFWwindow* m_window;
	std::function<void(key)> m_key_callback;

public:
	glfw_window_t(int width, int height, const std::string& title);
	~glfw_window_t();

	virtual void get_size(int& width, int& height) override;
	virtual void set_key_callback(const std::function<void(key)>& callback) override;
	virtual void set_current() override;
	virtual void swap_buffers() override;
	virtual void poll_events() override;
	virtual bool is_alive() override;
};
