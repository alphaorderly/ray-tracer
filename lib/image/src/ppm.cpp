#include "ppm.hpp"

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

    void PPM::save(const char* filename) {
        std::ofstream ofs(filename, std::ios::binary);

        ofs << "P6\n" << width << " " << height << "\n255\n";
        ofs.write(reinterpret_cast<char*>(data.data()), data.size());
        ofs.close();
    }
}
