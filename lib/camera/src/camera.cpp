#include "camera.hpp"
#include <iostream>
#include "util.hpp"

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
        raycore::Vec3 rd = lensRadius * raycore::random_in_unit_disk();
        raycore::Vec3 offset = u * rd.x + v * rd.y;

        return raycore::Ray(
            origin + offset,
            lowerLeftCorner + s * horizontal + t * vertical - origin - offset);
    }
}
