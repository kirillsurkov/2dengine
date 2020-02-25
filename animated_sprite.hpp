#pragma once

#include <vector>

#include "renderable.hpp"

class animated_sprite_t : public renderable_t {
private:
	float m_timer;
	float m_animation_speed;
	int m_current_image;
	std::vector<image_ptr> m_images;
	glm::mat4 m_transform;
	glm::vec4 m_color;

public:
	animated_sprite_t();
	virtual ~animated_sprite_t();

	void set_animation_speed(float speed);
	void add_image(image_ptr image);

	virtual image_ptr get_image() override;
	virtual const glm::mat4& get_transform() override;
	virtual const glm::vec4& get_color() override;
	virtual void update(float delta) override;
};
