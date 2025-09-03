#include "ppm.hpp"

#include <iostream>
#include <filesystem>


namespace image
{
    void PPM::setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            return; // Out of bounds
        }
        int index = (y * width + x) * 3;
        data[index] = r;
        data[index + 1] = g;
        data[index + 2] = b;
    }

    void PPM::save(const std::string& filename) {
        std::ofstream ofs(filename, std::ios::binary);

        if (!ofs) {
            std::cerr << "PPM::save: failed to open '" << filename << "' for writing.\n"
                      << "  cwd: " << std::filesystem::current_path() << std::endl;
            return;
        }

        ofs << "P6\n" << width << " " << height << "\n255\n";
        ofs.write(reinterpret_cast<char*>(data.data()), data.size());

        std::cout << "PPM::save: saved '" << filename << "' (" << width << "x" << height << ")\n";

        ofs.close();
    }
}
