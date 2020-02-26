#include <chrono>

#include "engine.hpp"
#include "opengl_render.hpp"
#include "glfw_window.hpp"

engine_t::engine_t(int width, int height, const std::string& title) {
	m_render = std::make_shared<opengl_render_t>(width, height);

	m_window = m_render->create_window(title);
	m_window->set_current();
	m_window->set_key_callback([this](window_t::key key) {
		m_inputs.push_back(key);
	});

	m_render->init();

	m_scene = std::make_shared<scene_t>(m_render);
}

engine_t::~engine_t() {
}

scene_ptr engine_t::get_scene() {
	return m_scene;
}

image_ptr engine_t::load_image(const std::string& filename) {
	if (m_images_cache.find(filename) == m_images_cache.end()) {
		m_images_cache[filename] = m_render->load_image(filename);
	}
	return m_images_cache[filename];
}

const std::list<window_t::key>& engine_t::get_inputs() {
	return m_inputs;
}

void engine_t::main_loop(const std::function<bool(float)>& callback) {
	auto last_time = std::chrono::system_clock::now();
	while (m_window->is_alive()) {
		auto current_time = std::chrono::system_clock::now();
		float delta = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_time).count() / 1000.0f;
		last_time = current_time;

		m_scene->update(delta);

		int width;
		int height;
		m_window->get_size(width, height);
		glm::mat4 ortho(glm::ortho(-0.5f * width, 0.5f * width, -0.5f * height, 0.5f * height));

		m_render->clear();
		m_scene->draw(ortho);

		if (!callback(delta)) {
			break;
		}

		m_inputs.clear();

		m_window->swap_buffers();
		m_window->poll_events();
	}
}
