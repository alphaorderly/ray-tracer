#pragma once
#include <cmath>

#include "vec3.hpp"
#include "ray.hpp"

namespace camera
{
  /**
   * 오른손 좌표계 (Right-handed coordinate system) 를 사용하는 카메라 클래스
   */
  class Camera
  {
  public:
    /**
     * @brief lookfrom 에서 lookat 으로 향하면서, 윗쪽을 향하는 벡터는 vup인 카메라를 생성하는 정적 메서드
     *
     * @param lookfrom 카메라 위치
     * @param lookat 카메라가 바라보는 위치
     * @param vup 카메라의 윗쪽 방향
     * @param vfov_deg 수직 시야각 (degree 단위) ( lookfrom 에서 lookat으로 향하는 벡터에 대해 얼마나 넓은 각도를 볼 수 있는지, 즉 시야각 )
     * @param aspect_ratio 화면의 가로/세로 비율
     * @param focus_dist 초점 거리 (lookfrom과 lookat 사이의 거리)
     */
    static Camera LookAt(
        raycore::Vec3 lookfrom,
        raycore::Vec3 lookat,
        raycore::Vec3 vup,
        double vfov_deg,
        double aspect_ratio,
        double focus_dist)
    {
      /**
       * 1. vfov_deg 를 tan 연산에 사용하기 위해 radian 으로 변환한다.
       * 2. theta의 각도는 삼각형 2개를 겹쳐놓은 모양에 해당하기에, 2로 나눈다.
       * 3. viewport 의 높이를 계산한다 ( viewport_height = 2.0 * h * focus_dist ) >> 여기서 h * focus_dist 를 하면 삼각형의 절반의 높이 값을 알수 있기에 2를 곱한다.
       * 4. viewport 의 너비를 계산한다 ( viewport_width = aspect_ratio * viewport_height ) >> 즉 이 부분은 따로 추가 계산이 아닌 aspect_ratio를 곱해주는 것 뿐이다.
       */
      const double theta = vfov_deg * (3.141592653589793 / 180.0);
      const double h = std::tan(theta / 2.0);
      const double viewport_height = 2.0 * h * focus_dist;
      const double viewport_width = aspect_ratio * viewport_height;

      /**
       * w : 카메라가 바라보는 방향벡터의 반대방향 ( lookfrom - lookat )
       * u : 카메라의 오른쪽 방향에 해당하는 벡터 ( vup 와 w 의 외적 )
       * v : 카메라의 위쪽 방향에 해당하는 벡터 ( w 와 u 의 외적 )
       */
      raycore::Vec3 w = (lookfrom - lookat).normalize();
      raycore::Vec3 u = raycore::cross(vup, w).normalize();
      raycore::Vec3 v = raycore::cross(w, u).normalize();

      /**
       * 정보 저장
       * horizontal : 카메라의 수평 방향 벡터 [ 크기 포함 ]
       * vertical : 카메라의 수직 방향 벡터 [ 크기 포함 ]
       * lower_left : 카메라의 좌하단 모서리 위치
       */
      raycore::Vec3 origin = lookfrom;
      raycore::Vec3 horizontal = viewport_width * u;
      raycore::Vec3 vertical = viewport_height * v;
      raycore::Vec3 lower_left = origin - horizontal / 2.0 - vertical / 2.0 - focus_dist * w;

      Camera cam(origin, lower_left, horizontal, vertical);
      cam.u = u;
      cam.v = v;
      cam.w = w;
      return cam;
    }

    Camera(raycore::Vec3 origin,
           raycore::Vec3 lowerLeftCorner,
           raycore::Vec3 horizontal,
           raycore::Vec3 vertical)
        : origin(origin), lowerLeftCorner(lowerLeftCorner),
          horizontal(horizontal), vertical(vertical) {}

    raycore::Ray getRay(double s, double t) const;

  private:
    raycore::Vec3 origin, lowerLeftCorner, horizontal, vertical;
    raycore::Vec3 u, v, w; // ← 나중에 DOF에서 사용
  };
} // namespace camera
