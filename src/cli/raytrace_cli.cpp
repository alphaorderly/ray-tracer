#include <iostream>
#include <limits>

#include "ppm.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "camera.hpp"

#include "hittable_list.hpp"
#include "hit_record.hpp"
#include "sphere.hpp"

const int WIDTH = 256;
const int HEIGHT = 256;

int main() {
    image::PPM img(WIDTH, HEIGHT);

    double aspect_ratio = static_cast<double>(WIDTH) / HEIGHT;

    double focal_length = 1.0;

    camera::Camera cam = camera::Camera::LookAt(
        raycore::vec3(0, 0, 0),
        raycore::vec3(0, 0, -1), 
        raycore::vec3(0, 1, 0),
        90.0,
        aspect_ratio,
        2.0
    );

    hit::hittable_list world;

    world.add(std::make_shared<hit::Sphere>(raycore::vec3(0, 0, -2), 0.5));
    world.add(std::make_shared<hit::Sphere>(raycore::vec3(0, -1, -1), 1));

    for (int r = 0; r < HEIGHT; ++r) {
        for (int c = 0; c < WIDTH; ++c) {
            double u = static_cast<double>(c) / (WIDTH - 1);
            double v = static_cast<double>(r) / (HEIGHT - 1);

            hit::hit_record rec;

            raycore::ray ray = cam.getRay(u, v);

            bool isHit = world.hit(ray, 0.001, std::numeric_limits<double>::infinity(), rec);

            if(isHit) {
                auto n = rec.normal;
                auto col = 0.5 * raycore::vec3(n.x + 1.0, n.y + 1.0, n.z + 1.0);
                img.setPixel(c, HEIGHT - r - 1,
                            int(255.999*col.x), int(255.999*col.y), int(255.999*col.z));
            } else {
                raycore::vec3 color = raycore::sky_color(ray);

                int ir = static_cast<int>(255.999 * color.x);
                int ig = static_cast<int>(255.999 * color.y);
                int ib = static_cast<int>(255.999 * color.z);

                img.setPixel(c, HEIGHT - r - 1, ir, ig, ib);
            }

        }
    }

    img.save("output.ppm");

    return 0;
}