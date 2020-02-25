#pragma once

#include <memory>

class context_t {
private:
	int m_window_width;
	int m_window_height;

public:
	context_t();
	~context_t();

	void set_window_size(int width, int height);
	void get_window_size(int& width, int& height);
};

typedef std::shared_ptr<context_t> context_ptr;
