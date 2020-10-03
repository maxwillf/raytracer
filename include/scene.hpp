#ifndef __SCENE_H_
#define __SCENE_H_
#include "include/background.hpp"
#include "include/primitive.hpp"
#include "include/ray.hpp"
#include "include/surfel.hpp"
#include <memory>

class Scene {
	//=== Public data
    public:
	    //std::vector<shared_ptr<Light>> lights; // list of lights
	    std::shared_ptr< Background > background; // The background object.
	private:
		std::shared_ptr<Primitive> aggregate; // The scene graph of objects, acceleration structure.

        //=== Public interface
	public:
		Scene( std::shared_ptr<Primitive> ag, std::shared_ptr< Background > bkg)
			: background{bkg}, aggregate{ag}
		{/* empty */}
		/// Determines the intersection info; return true if there is an intersection.
		bool intersect( const Ray& r, Surfel *isect ) const{
			return aggregate->intersect(r,isect);
		};
		/*! A faster version that only determines whether there is an intersection or not;
		 * it doesn't calculate the intersection info.
		 */
		bool intersect_p( const Ray& r ) const {
			return aggregate->intersect_p(r);
		};
};



#endif // __SCENE_H_
