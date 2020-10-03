#include "include/integrator.hpp"

// Enter the ray tracing main loop; this is the default render() method.
// Notice that the FlatIntegrator does not need to override this method.
// It relies on the version provided by the base class (SamplerIntegrator).
void SamplerIntegrator::render(const Scene& scene) {
    // Always call the preprocess() before doing any rendering.
    // This might be just an empty method, or not, depending on the integrator's needs.
    preprocess(scene);

    // This might just be a tile (part) of an image, rendered in parallel.
    int xres = camera->film->getWidth();
    int yres = camera->film->getHeight();
    for ( int y = 0 ; y < yres ; y++ ) {
        for( int x = 0 ; x < xres ; x++ ) {
            // Get the background color in case we hit nothing.
            Color24 L_background{0,0,0};
            Point2 screen_coord{ float(x)/float(xres), float(y)/float(yres) };
            Ray ray = camera->generate_ray(x,y); // Generate the ray from (x,y)
            L_background = scene.background->getColor(x,y,ray);
            // Determine the ray for the current camera type.
            // Determine the incoming light.
            Color24 L =  Li( ray, scene, L_background );
            // Add color (radiance) to the image.
            //camera->film->add_sample( Point2( x, y ), L ); // Set color of pixel (x,y) to L.
        }
    }
// Send image color buffer to the output file.
    //    camera->film->writeToFile( image );
}
void SamplerIntegrator::preprocess(const Scene &scene){
    // stub
}
