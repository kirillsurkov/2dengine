#include "game_object.hpp"

game_object_t::game_object_t() {
}

game_object_t::~game_object_t() {
}

const std::list<renderable_ptr>& game_object_t::get_renderables() {
	return m_renderables;
}
