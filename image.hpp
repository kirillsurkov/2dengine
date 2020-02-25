#pragma once

#include <memory>
#include <vector>

class image_t {
protected:
	int m_width;
	int m_height;
	std::vector<char> m_pixels;

public:
	image_t(const std::string& filename);
	~image_t();

	int get_width();
	int get_height();
	std::vector<char>&& get_pixels();
};

typedef std::shared_ptr<image_t> image_ptr;
