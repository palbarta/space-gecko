#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <unordered_map>

class DebugConfig;
class Scene;
class SceneObject;

class Debug
{
public:
	Debug(const Scene& scene);
	void update(float dt);
	const std::list<sf::Drawable*>& objects() const { return objects_; }

private:
	void addBoundingBoxes();
	void updateBoundingBox(const SceneObject& scene_object);

private:
	const Scene& scene_;
	const DebugConfig& cfg_;
	std::unordered_map<const SceneObject*, sf::VertexArray> scene_object_bounding_boxes_;
	std::list<sf::Drawable*> objects_;
};