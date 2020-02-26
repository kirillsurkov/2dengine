#pragma once

#include "engine.hpp"
#include "sprite.hpp"

class object_snake_t : public game_object_t {
private:
	enum class direction {
		none,
		left,
		right,
		up,
		down
	};

	class corner_sprite_t : public sprite_t {
	public:
		corner_sprite_t(image_ptr image);
	};

	engine_ptr m_engine;
	float m_speed;
	float m_timer;
	int m_color_counter;
	bool m_grow;
	direction m_direction;
	direction m_prev_direction;

	renderable_ptr create_head(int x, int y, float rotation);
	renderable_ptr create_body(int x, int y, float rotation);
	renderable_ptr create_corner(int x, int y, float rotation);
	renderable_ptr create_tail(int x, int y, float rotation);

	void get_new_transform(int& x, int& y, float& rotation);
	float get_corner_rotation();
	glm::vec4 get_piece_color();

public:
	object_snake_t(engine_ptr engine, float speed, int x, int y);
	~object_snake_t();

	const glm::vec2& get_head_coords();

	void grow();

	virtual void update(float delta) override;
};
