#include "camera.hpp"
#include <iostream>

namespace camera
{
    /**
     * 원점으로부터 수평으로 s 만큼, 수직으로 t 만큼 떨어진 지점으로 향하는 광선을 반환
     * @param s 수평 방향으로의 이동 거리 (0 ~ 1)
     * @param t 수직 방향으로의 이동 거리 (0 ~ 1)
     */
    raycore::Ray Camera::getRay(double s, double t) const
    {

        // s와 t의 유효성을 검사 ( 0.0 ~ 1.0 인지 )
        if (s < 0.0 || s > 1.0 || t < 0.0 || t > 1.0)
        {
            std::cerr << "Error: s and t should be in the range [0, 1]. Got s=" << s << ", t=" << t << std::endl;
            throw std::out_of_range("s and t must be in [0, 1]");
        }

        return raycore::Ray(
            origin,
            lowerLeftCorner + s * horizontal + t * vertical - origin);
    }
}
