#pragma once

#include <memory>

class window_t {
public:
	virtual void set_current() = 0;
	virtual void swap_buffers() = 0;
	virtual void poll_events() = 0;
	virtual bool is_alive() = 0;
};

typedef std::shared_ptr<window_t> window_ptr;
