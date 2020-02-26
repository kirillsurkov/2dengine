#include "scene.hpp"

scene_t::scene_t(render_ptr render) :
	m_render(render),
	m_scale(1.0f)
{
}

scene_t::~scene_t() {
}

void scene_t::set_scale(float scale) {
	m_scale = scale;
}

void scene_t::remove_object(game_object_ptr object) {
	m_objects.remove(object);
}

game_object_ptr scene_t::get_control_object() {
	return m_control_object;
}

void scene_t::update(float delta) {
	for (auto object : m_objects) {
		object->update(delta);
		for (auto renderable : object->get_renderables()) {
			renderable->update(delta);
		}
	}
}

void scene_t::draw(const glm::mat4& projection) {
	for (auto object : m_objects) {
		for (auto renderable : object->get_renderables()) {
			auto transform = glm::rotate(glm::translate(glm::mat4(1.0f), m_scale * glm::vec3(renderable->get_coords(), 0.0f)), renderable->get_rotation(), glm::vec3(0.0f, 0.0f, 1.0f));
			m_render->draw_image(renderable->get_image(), renderable->get_color(), projection * transform);
		}
	}
}
