#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <string>
#include <ctime>

#include "ppm.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "camera.hpp"
#include "util.hpp"

#include "Dielectric.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"

const int WIDTH = 256;
const int HEIGHT = 256;

std::mt19937_64 rng(time(NULL)); // 나중엔 시간시드/스레드별 시드
std::uniform_real_distribution<double> uni(0.0, 1.0);

const int SAMPLES_PER_PIXEL = 50;
const int DEPTH = 50;

double random_double()
{
    return uni(rng);
}

int main()
{
    image::PPM img(WIDTH, HEIGHT);

    double aspect_ratio = static_cast<double>(WIDTH) / HEIGHT;

    camera::Camera cam = camera::Camera::LookAt(
        raycore::Vec3(0, 0, 0),
        raycore::Vec3(0, 0, -1),
        raycore::Vec3(0, 1, 0),
        90.0,
        aspect_ratio,
        2.0);

    shapes::HittableList world;

    world.add(std::make_shared<shapes::Sphere>(raycore::Vec3(-1, 0, -1), 0.5, std::make_shared<materials::Dielectric>(0.2)));

    for (int r = 0; r < HEIGHT; ++r)
    {
        for (int c = 0; c < WIDTH; ++c)
        {

            raycore::Vec3 pixel_color(0, 0, 0);

            for (int s = 0; s < SAMPLES_PER_PIXEL; ++s)
            {
                double u = (c + random_double()) / (WIDTH - 1);
                double v = (r + random_double()) / (HEIGHT - 1);

                u = raycore::clamp(u, 0.0, 1.0);
                v = raycore::clamp(v, 0.0, 1.0);

                raycore::Ray ray = cam.getRay(u, v);
                pixel_color += raycore::ray_color(ray, world, DEPTH);
            }

            // 평균
            pixel_color /= SAMPLES_PER_PIXEL;

            // 감마 보정 (gamma=2.0)
            pixel_color = raycore::Vec3(sqrt(pixel_color.x),
                                        sqrt(pixel_color.y),
                                        sqrt(pixel_color.z));

            img.setPixel(c, HEIGHT - r - 1, int(255 * pixel_color.x), int(255 * pixel_color.y), int(255 * pixel_color.z));
        }
    }

    int random_integer = std::uniform_int_distribution<int>(0, 1000000)(rng);

    std::ostringstream ss;

    ss << "output_" << random_integer << ".ppm";

    std::string filename = ss.str();

    img.save(filename);

    std::cout << "Saved image to " << filename << std::endl;

    return 0;
}