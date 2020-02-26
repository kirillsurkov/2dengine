#pragma once

#include "engine.hpp"

class object_food_t : public game_object_t {
private:
	float m_timer;
	renderable_ptr m_sprite;

public:
	object_food_t(engine_ptr engine, int x, int y);
	~object_food_t();

	const glm::vec2& get_coords();

	virtual void update(float delta) override;
};
