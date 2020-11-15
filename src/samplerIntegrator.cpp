#include "include/integrator.hpp"

// Enter the ray tracing main loop; this is the default render() method.
// Notice that the FlatIntegrator does not need to override this method.
// It relies on the version provided by the base class (SamplerIntegrator).
void SamplerIntegrator::render(const Scene &scene)
{
    // Always call the preprocess() before doing any rendering.
    // This might be just an empty method, or not, depending on the integrator's needs.
    preprocess(scene);

    // This might just be a tile (part) of an image, rendered in parallel.
    int xres = camera->film->getWidth();
    int yres = camera->film->getHeight();
    std::cout << "camera width: " << xres << std::endl;
    std::cout << "camera height: " << yres << std::endl;
    for (int y = 0; y < yres; y++)
    {
        for (int x = 0; x < xres; x++)
        {
            double j = double(yres - 1 - y) / double(yres);
            double i = double(xres - 1 - x) / double(xres);
            // Get the background color in case we hit nothing.
            //            Point2 screen_coord{ double(x)/double(xres), double(y)/double(yres) };
            Ray ray = camera->generate_ray(x, y); // Generate the ray from (x,y)
            if (x == xres - 1 && y == yres - 1)
            {
                int x = 0;
            }
            Color24 L_background = scene.background->getColor(i, j, ray);
            // Determine the ray for the current camera type.
            // Determine the incoming light.
            // std::cout << "x and y: " << x << " " << y << std::endl;
            // std::cout << "ray direction: " << ray.direction() << std::endl;
            Color24 L = Li(ray, scene, L_background);
            if (x == 0 && y == 0)
            {
                int z = 0;
            }
            // Add color (radiance) to the image.
            camera->film->setPoint(x, y, L); // Set color of pixel (x,y) to L.
        }
    }
    // Send image color buffer to the output file.
    camera->film->writeToFile();
}
void SamplerIntegrator::preprocess(const Scene &scene)
{
    // stub
}
