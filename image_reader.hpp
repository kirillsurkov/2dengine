#pragma once

#include <vector>

class image_reader_t {
public:
	virtual int get_width() = 0;
	virtual int get_height() = 0;
	virtual int get_channels() = 0;
	virtual std::vector<char>&& get_pixels() = 0;
};
