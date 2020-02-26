#pragma once

#include <unordered_map>
#include <functional>

#include "render.hpp"
#include "window.hpp"
#include "scene.hpp"

class engine_t {
private:
	render_ptr m_render;
	window_ptr m_window;
	scene_ptr m_scene;
	std::unordered_map<std::string, image_ptr> m_images_cache;
	std::list<window_t::key> m_inputs;

public:
	engine_t(int width, int height, const std::string& title);
	~engine_t();

	scene_ptr get_scene();
	image_ptr load_image(const std::string& filename);

	const std::list<window_t::key>& get_inputs();

	void main_loop(const std::function<bool(float)>& callback);
};

typedef std::shared_ptr<engine_t> engine_ptr;
