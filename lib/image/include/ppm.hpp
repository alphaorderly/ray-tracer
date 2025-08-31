#pragma once

#include <vector>
#include <fstream>

namespace image {
    class PPM {
        private:
            int width, height;
            std::vector<unsigned char> data;

        public:
            PPM(int w, int h) : width(w), height(h) {
                data.resize(w * h * 3);
            }

            void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);

            void save(const char* filename);
    };
}