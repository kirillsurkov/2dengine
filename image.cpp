#include "image.hpp"
#include "png_reader.hpp"

image_t::image_t(const std::string& filename) {
	png_reader_t reader(filename);
	m_width = reader.get_width();
	m_height = reader.get_height();
	m_pixels = reader.get_pixels();
}

image_t::~image_t() {
}

int image_t::get_width() {
	return m_width;
}

int image_t::get_height() {
	return m_height;
}

std::vector<char>&& image_t::get_pixels() {
	return std::move(m_pixels);
}
