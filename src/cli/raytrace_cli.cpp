#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <string>
#include <ctime>
#include <thread>
#include <chrono>

#include "ppm.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "camera.hpp"
#include "util.hpp"

#include "HittableList.hpp"
#include "Sphere.hpp"
#include "Lambertian.hpp"
#include "Dielectric.hpp"
#include "Metal.hpp"
#include "Emmisive.hpp"
#include "checker.hpp"
#include "solid_color.hpp"

const int WIDTH = 256;
const int HEIGHT = 256;

std::mt19937_64 rng(time(NULL)); // 나중엔 시간시드/스레드별 시드
std::uniform_real_distribution<double> uni(0.0, 1.0);

const int SAMPLES_PER_PIXEL = 50;
const int DEPTH = 50;

static void render_multi_thread(image::PPM &img,
                                const camera::Camera &cam,
                                const shapes::HittableList &world);

// Compute the color of a single pixel by sampling multiple rays and applying gamma correction.
static raycore::Vec3 compute_pixel_color(int row, int col,
                                         const camera::Camera &cam,
                                         const shapes::HittableList &world)
{
    raycore::Vec3 pixel_color(0, 0, 0);
    for (int s = 0; s < SAMPLES_PER_PIXEL; ++s)
    {
        double u = (col + raycore::random_double()) / (WIDTH - 1);
        double v = (row + raycore::random_double()) / (HEIGHT - 1);

        u = raycore::clamp(u, 0.0, 1.0);
        v = raycore::clamp(v, 0.0, 1.0);

        raycore::Ray ray = cam.getRay(u, v);
        pixel_color += raycore::ray_color(ray, world, DEPTH);
    }

    // Average samples
    pixel_color /= SAMPLES_PER_PIXEL;

    // Gamma correction (gamma = 2.0)
    pixel_color = raycore::Vec3(std::sqrt(pixel_color.x),
                                std::sqrt(pixel_color.y),
                                std::sqrt(pixel_color.z));

    return pixel_color;
}

void random_scene(shapes::HittableList &world)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            double choose_mat = raycore::random_double();
            raycore::Vec3 center(i + 0.9 * raycore::random_double(), 0.2, j + 0.9 * raycore::random_double());

            if ((center - raycore::Vec3(4, 0.2, 0)).length() > 0.9)
            {
                if (choose_mat < 0.8)
                {
                    // diffuse
                    raycore::Vec3 albedo = raycore::Vec3::random() * raycore::Vec3::random();
                    world.add(std::make_shared<shapes::Sphere>(center, 0.2, std::make_shared<materials::Lambertian>(albedo)));
                }
                else if (choose_mat < 0.95)
                {
                    // metal
                    raycore::Vec3 albedo = raycore::Vec3::random(0.5, 1);
                    double fuzz = raycore::random_double(0, 0.5);
                    world.add(std::make_shared<shapes::Sphere>(center, 0.2, std::make_shared<materials::Metal>(albedo, fuzz)));
                }
                else if (choose_mat < 0.98)
                {
                    // glass
                    world.add(std::make_shared<shapes::Sphere>(center, 0.2, std::make_shared<materials::Dielectric>(1.5)));
                }
                else
                {
                    // emissive (bright light-ish sphere)
                    raycore::Vec3 emitColor = raycore::Vec3::random(2.0, 4.0); // brighter range
                    world.add(std::make_shared<shapes::Sphere>(center, 0.2, std::make_shared<materials::Emmisive>(emitColor)));
                }
            }
        }
    }
}

void remove_ppms_in_cwd()
{
    std::filesystem::path cwd = std::filesystem::current_path();
    for (const auto &entry : std::filesystem::directory_iterator(cwd))
    {
        if (entry.path().extension() == ".ppm")
        {
            std::filesystem::remove(entry.path());
        }
    }
}

double random_double()
{
    return uni(rng);
}

static void render_multi_thread(image::PPM &img,
                                const camera::Camera &cam,
                                const shapes::HittableList &world)
{
    const unsigned int max_threads = std::max(1u, std::thread::hardware_concurrency());
    const int rows_per_thread = HEIGHT / max_threads;

    std::vector<std::thread> threads;
    threads.reserve(max_threads);

    for (unsigned int t = 0; t < max_threads; ++t)
    {
        int start_row = t * rows_per_thread;
        int end_row = (t == max_threads - 1) ? HEIGHT : static_cast<int>((t + 1) * rows_per_thread);

        threads.emplace_back([start_row, end_row, &img, &cam, &world]()
                             {
            for (int r = start_row; r < end_row; ++r)
            {
                for (int c = 0; c < WIDTH; ++c)
                {
                    raycore::Vec3 pixel_color = compute_pixel_color(r, c, cam, world);
                    img.setPixel(c, HEIGHT - r - 1,
                                 static_cast<unsigned char>(255.999 * raycore::clamp(pixel_color.x, 0.0, 0.999)),
                                 static_cast<unsigned char>(255.999 * raycore::clamp(pixel_color.y, 0.0, 0.999)),
                                 static_cast<unsigned char>(255.999 * raycore::clamp(pixel_color.z, 0.0, 0.999)));
                }
            } });
    }

    for (auto &th : threads)
    {
        if (th.joinable())
            th.join();
    }
}

int main()
{
    double aspect_ratio = static_cast<double>(WIDTH) / HEIGHT;

    camera::Camera cam = camera::Camera::LookAt(
        raycore::Vec3(0, 0, 3),
        raycore::Vec3(0, 0, -1),
        raycore::Vec3(0, 1, 0),
        90.0,
        aspect_ratio,
        0.0, 2.0);

    shapes::HittableList world;
    {
        auto even = std::make_shared<texture::SolidColor>(raycore::Vec3(0.8, 0.8, 0.8));
        auto odd = std::make_shared<texture::SolidColor>(raycore::Vec3(0.2, 0.3, 0.2));
        auto checker = std::make_shared<texture::Checker>(even, odd);
        world.add(std::make_shared<shapes::Sphere>(raycore::Vec3(0, -100.5, -1), 100, std::make_shared<materials::Lambertian>(checker)));
    }
    random_scene(world);

    remove_ppms_in_cwd();

    image::PPM img(WIDTH, HEIGHT);
    auto start_time = std::chrono::steady_clock::now();
    render_multi_thread(img, cam, world);
    auto end_time = std::chrono::steady_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    int rand_val = std::uniform_int_distribution<int>(0, 1000000)(rng);
    std::ostringstream ss;
    ss << "multi_" << rand_val << ".ppm";
    img.save(ss.str());
    std::cout << "Multi-thread render time: " << dur << " ms => " << ss.str() << std::endl;
    return 0;
}