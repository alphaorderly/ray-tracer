#include "ppm.hpp"

#include <iostream>
#include <filesystem>

namespace image
{
    /**
     * 픽셀 (x, y) 위치에 RGB 색상을 설정
     * (0,0)은 이미지의 좌상단 모서리
     * @param x 픽셀의 x 좌표
     * @param y 픽셀의 y 좌표
     * @param r 빨간색 성분 (0-255)
     * @param g 초록색 성분 (0-255)
     * @param b 파란색 성분 (0-255)
     */
    void PPM::setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b)
    {
        if (x < 0 || x >= width || y < 0 || y >= height)
        {
            return; // Out of bounds
        }
        int index = (y * width + x) * 3;
        data[index] = r;
        data[index + 1] = g;
        data[index + 2] = b;
    }

    /**
     * PPM 파일로 이미지 저장
     * @param filename 저장할 파일 이름
     */
    void PPM::save(const std::string &filename)
    {
        std::ofstream ofs(filename, std::ios::binary);

        // 파일 열기 실패 시 에러 로그 작성
        if (!ofs)
        {
            std::ofstream err("error.log", std::ios::app);
            err << "PPM::save: failed to open '" << filename << "' for writing\n";
            err.close();
            return;
        }

        ofs << "P6\n"
            << width << " " << height << "\n255\n";
        ofs.write(reinterpret_cast<char *>(data.data()), data.size());

        std::cout << "PPM::save: saved '" << filename << "' (" << width << "x" << height << ")\n";

        ofs.close();
    }
}
