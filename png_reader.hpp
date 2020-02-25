#pragma once

#include <png.h>

#include "image_reader.hpp"

class png_reader_t : public image_reader_t {
private:
	struct libpng_context_t {
		png_structp png_ptr;
		png_infop info_ptr;

		libpng_context_t();
		~libpng_context_t();
	};

	libpng_context_t m_libpng;
	int m_width;
	int m_height;
	int m_channels;
	std::vector<char> m_pixels;

public:
	png_reader_t(const std::string& filename);
	virtual ~png_reader_t();

	virtual int get_width() override;
	virtual int get_height() override;
	virtual int get_channels() override;
	virtual std::vector<char>&& get_pixels() override;
};
