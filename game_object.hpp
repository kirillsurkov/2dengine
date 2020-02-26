#pragma once

#include <list>
#include <glm/gtc/matrix_transform.hpp>

#include "renderable.hpp"

class game_object_t {
protected:
	std::list<renderable_ptr> m_renderables;

public:
	game_object_t();
	~game_object_t();

	const std::list<renderable_ptr>& get_renderables();

	virtual void update(float delta) {}
};

typedef std::shared_ptr<game_object_t> game_object_ptr;
