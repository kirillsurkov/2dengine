#pragma once

#include <list>

#include "render.hpp"
#include "game_object.hpp"

class scene_t {
private:
	render_ptr m_render;
	std::list<game_object_ptr> m_objects;
	game_object_ptr m_control_object;
	float m_scale;

public:
	scene_t(render_ptr render);
	~scene_t();

	void set_scale(float scale);

	template<class T> T add_object(T object, bool control = false) {
		m_objects.push_back(object);
		if (control) {
			m_control_object = object;
		}
		return object;
	}
	void remove_object(game_object_ptr object);

	game_object_ptr get_control_object();

	void update(float delta);
	void draw(const glm::mat4& projection);
};

typedef std::shared_ptr<scene_t> scene_ptr;
