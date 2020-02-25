#include "context.hpp"

context_t::context_t() :
	m_window_width(0),
	m_window_height(0)
{
}

context_t::~context_t() {
}

void context_t::set_window_size(int width, int height) {
	m_window_width = width;
	m_window_height = height;
}

void context_t::get_window_size(int& width, int& height) {
	width = m_window_width;
	height = m_window_height;
}
