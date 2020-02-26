#include <fstream>


#include "png_reader.hpp"


png_reader_t::libpng_context_t::libpng_context_t() :
	png_ptr(nullptr),
	info_ptr(nullptr)
{
}

png_reader_t::libpng_context_t::~libpng_context_t() {
	png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
}

png_reader_t::png_reader_t(const std::string& filename) :
	m_libpng()
{
	std::ifstream input(filename);
	if (!input) {
		throw std::runtime_error("Unable to locate file '" + filename + "'");
	}

	unsigned char header[8];
	input.read(reinterpret_cast<char*>(header), 8);
	if (png_sig_cmp(header, 0, 8) != 0) {
		throw std::runtime_error("Invalid png file '" + filename + "'");
	}

	m_libpng.png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (!m_libpng.png_ptr) {
		throw std::runtime_error("png_create_read_struct failed");
	}

	m_libpng.info_ptr = png_create_info_struct(m_libpng.png_ptr);
	if (!m_libpng.info_ptr) {
		throw std::runtime_error("png_create_info_struct failed");
	}

	if (setjmp(png_jmpbuf(m_libpng.png_ptr)) != 0) {
		throw std::runtime_error("Error while reading file '" + filename + "'");
	}

	png_set_read_fn(m_libpng.png_ptr, &input, [](png_structp png_ptr, png_bytep data, png_size_t length) {
		static_cast<std::ifstream*>(png_get_io_ptr(png_ptr))->read(reinterpret_cast<char*>(data), length);
	});

	png_set_sig_bytes(m_libpng.png_ptr, 8);
	png_read_info(m_libpng.png_ptr, m_libpng.info_ptr);

	switch (png_get_color_type(m_libpng.png_ptr, m_libpng.info_ptr)) {
	case PNG_COLOR_TYPE_RGB_ALPHA: {
		m_channels = 4;
		break;
	}
	default: {
		throw std::runtime_error("Unsupported format for PNG file '" + filename + "'");
	}
	}

	m_width = png_get_image_width(m_libpng.png_ptr, m_libpng.info_ptr);
	m_height = png_get_image_height(m_libpng.png_ptr, m_libpng.info_ptr);

	int row_size = m_width * m_channels;

	std::vector<png_byte*> row_pointers;
	for (int y = 0; y < m_height; y++) {
		row_pointers.push_back(new png_byte[row_size]);
	}

	if (setjmp(png_jmpbuf(m_libpng.png_ptr)) != 0) {
		for (png_byte* row : row_pointers) {
			delete[] row;
		}
		throw std::runtime_error("Error while reading file '" + filename + "'");
	}

	png_read_image(m_libpng.png_ptr, row_pointers.data());
	for (auto it = row_pointers.rbegin(); it != row_pointers.rend(); it++) {
		auto row = *it;
		for (int x = 0; x < m_width; x++) {
			float alpha = row[x * m_channels + 3] / 255.0f;
			row[x * m_channels + 0] *= alpha;
			row[x * m_channels + 1] *= alpha;
			row[x * m_channels + 2] *= alpha;
		}
		std::copy(row, row + row_size, std::back_inserter(m_pixels));
		delete[] row;
	}
}

png_reader_t::~png_reader_t() {
}

int png_reader_t::get_width() {
	return m_width;
}

int png_reader_t::get_height() {
	return m_height;
}

int png_reader_t::get_channels() {
	return m_channels;
}

std::vector<char>&& png_reader_t::get_pixels() {
	return std::move(m_pixels);
}
