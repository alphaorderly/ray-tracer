#include "camera.hpp"
#include <iostream>

namespace camera
{
    /**
     * 카메라 뷰포트의 lower left corner 에서 (s, t) 위치로 향하는 광선을 생성
     * s와 t는 뷰포트 내부에서의 상대적인 위치를 나타냄 (0,0이 lower left corner, 1,1이 upper right corner)
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
