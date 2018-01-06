#include "debug.h"

#include "config.h"
#include "scene.h"
#include "scene_object.h"

Debug::Debug(const Scene& scene)
	: scene_(scene)
	, cfg_(Config::getInstance().debug_)
{
	/*sf::Text debug_message;
	debug_message.setFont(font);
	debug_message.setCharacterSize(30);
	debug_message.setFillColor(sf::Color::White);
	
	
	debug_message.setPosition(space_ship.shape().getPosition());
	std::stringstream ss;
	auto&& x = space_ship.shape().getPosition().x - map.midPoint().x;
	auto&& y = space_ship.shape().getPosition().y - map.midPoint().y;
	ss << std::setprecision(3) << "x:" << x << ", y:" << y << ", rad:" << space_ship.inwardAngleRadian() << ", deg:" << space_ship.inwardAngleDegree();
	debug_message.setString(ss.str());*/
}

void 
Debug::update(float dt)
{
	objects_.clear();
	if (cfg_.draw_bounding_boxes_)
		addBoundingBoxes();
}


void
Debug::addBoundingBoxes()
{
	for (auto&& scene_object : scene_.objects()) {
		if (scene_object_bounding_boxes_.find(scene_object) == scene_object_bounding_boxes_.end()) {
			scene_object_bounding_boxes_[scene_object] = sf::VertexArray(sf::LineStrip, scene_object->box2dShape().m_count);
		}
		updateBoundingBox(*scene_object);
		objects_.push_back(&scene_object_bounding_boxes_[scene_object]);
	}
}

void
Debug::updateBoundingBox(const SceneObject& scene_object)
{
	auto&& bounding_box = scene_object_bounding_boxes_[&scene_object];
	auto&& b2_transform = scene_object.box2dTransform();
	auto&& b2_shape = scene_object.box2dShape();
	bounding_box.resize(b2_shape.m_count + 1);
	for (int vertex_idx = 0; vertex_idx < b2_shape.m_count; ++vertex_idx) {
		auto&& vertex = b2_shape.m_vertices[vertex_idx];
		auto&& transformed_vertex = b2Mul(b2_transform, vertex);
		(bounding_box)[vertex_idx].position = sf::Vector2f(transformed_vertex.x, transformed_vertex.y);
	}
	bounding_box[b2_shape.m_count] = bounding_box[0];
}