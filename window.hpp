#pragma once

#include <memory>
#include <functional>

class window_t {
public:
	enum class key {
		esc,
		left,
		right,
		up,
		down
	};

	virtual void get_size(int& width, int& height) = 0;
	virtual void set_key_callback(const std::function<void(key)>& callback) = 0;
	virtual void set_current() = 0;
	virtual void swap_buffers() = 0;
	virtual void poll_events() = 0;
	virtual bool is_alive() = 0;
};

typedef std::shared_ptr<window_t> window_ptr;
