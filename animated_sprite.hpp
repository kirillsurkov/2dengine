#pragma once

#include <vector>

#include "renderable.hpp"

class animated_sprite_t : public renderable_t {
private:
	float m_timer;
	float m_animation_speed;
	int m_current_image;
	std::vector<image_ptr> m_images;
	float m_rotation;
	glm::vec2 m_coords;
	glm::vec4 m_color;

public:
	animated_sprite_t();
	virtual ~animated_sprite_t();

	void set_animation_speed(float speed);
	void add_image(image_ptr image);

	virtual void set_rotation(float rotation) override;
	virtual void set_coords(float x, float y) override;
	virtual void set_color(const glm::vec4& color) override;
	virtual image_ptr get_image() override;
	virtual float get_rotation() override;
	virtual const glm::vec2& get_coords() override;
	virtual const glm::vec4& get_color() override;
	virtual void update(float delta) override;
};
