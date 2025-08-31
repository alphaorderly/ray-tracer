#include <iostream>

#include "ppm.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"

const int WIDTH = 256;
const int HEIGHT = 256;

int main() {
    image::PPM img(WIDTH, HEIGHT);

    double aspect_ratio = static_cast<double>(WIDTH) / HEIGHT;

    double viewport_width = 2.0;
    double viewport_height = viewport_width / aspect_ratio;

    double focal_length = 1.0;

    raycore::vec3 origin(0, 0, 0);

    raycore::vec3 lower_left = origin - raycore::vec3(viewport_width / 2, viewport_height / 2, focal_length);
    raycore::vec3 horizontal(viewport_width, 0, 0);
    raycore::vec3 vertical(0, viewport_height, 0);

    for (int r = 0; r < HEIGHT; ++r) {
        for (int c = 0; c < WIDTH; ++c) {
            double u = static_cast<double>(c) / (WIDTH - 1);
            double v = static_cast<double>(r) / (HEIGHT - 1);

            raycore::vec3 ray_origin = origin;
            raycore::vec3 ray_direction = lower_left + horizontal * u + vertical * v - origin;
            raycore::ray ray(ray_origin, ray_direction);

            raycore::vec3 color = raycore::sky_color(ray.direction);

            auto clamp01 = [](double x){ return x < 0 ? 0 : (x > 1 ? 1 : x); };
            int ir = static_cast<int>(255.999 * clamp01(color.x));
            int ig = static_cast<int>(255.999 * clamp01(color.y));
            int ib = static_cast<int>(255.999 * clamp01(color.z));


            img.setPixel(c, HEIGHT - r - 1, ir, ig, ib);
        }
    }

    img.save("output.ppm");

    return 0;
}