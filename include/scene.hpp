#ifndef __SCENE_H_
#define __SCENE_H_
#include "include/background.hpp"
#include "include/primitive.hpp"
#include "include/ray.hpp"
#include "include/surfel.hpp"
#include "include/bvh_node.hpp"
//#include "include/lightSource.hpp"
#include <memory>

class LightSource;
class AmbientLight;

class Scene
{
	//=== Public data
public:
	//std::vector<shared_ptr<Light>> lights; // list of lights
	std::shared_ptr<Background> background; // The background object.
	std::vector<shared_ptr<LightSource>> lights = std::vector<shared_ptr<LightSource>>();
	std::shared_ptr<Primitive> aggregate;		   // The scene graph of objects, acceleration structure.
	mutable std::shared_ptr<bvh_node> accelerator; // The scene graph of objects, acceleration structure.

private:
	//=== Public interface
public:
	Scene(std::shared_ptr<Primitive> ag, std::shared_ptr<Background> bkg,
		  std::vector<shared_ptr<LightSource>> lights,
		  shared_ptr<AmbientLight> ambientLight)
		: background{bkg}, aggregate{ag}, lights{lights}, ambientLight{ambientLight}
	{ /* empty */
	}
	/// Determines the intersection info; return true if there is an intersection.
	bool intersect(const Ray &r, Surfel *isect) const
	{
		if (accelerator != nullptr)
		{
			return accelerator->intersect(r, isect);
		}
		else
		{
			return aggregate->intersect(r, isect);
		}
	};

	shared_ptr<AmbientLight> ambientLight = nullptr;
	/*! A faster version that only determines whether there is an intersection or not;
		 * it doesn't calculate the intersection info.
		 */
	bool intersect_p(const Ray &r) const
	{
		if (accelerator != nullptr)
		{
			return accelerator->intersect_p(r);
		}
		else
		{
			return aggregate->intersect_p(r);
		}
		// return aggregate->intersect_p(r);
	};
};

#endif // __SCENE_H_
