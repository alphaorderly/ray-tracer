#pragma once
#include <cmath>           

#include "vec3.hpp"
#include "ray.hpp"

namespace camera {
class Camera {
public:
  static Camera LookAt(
      raycore::Vec3 lookfrom,
      raycore::Vec3 lookat,
      raycore::Vec3 vup,
      double vfov_deg,
      double aspect_ratio,
      double focus_dist // ← viewport_size 대신
  ) {
      const double theta = vfov_deg * (3.141592653589793 / 180.0);
      const double h = std::tan(theta / 2.0);
      const double viewport_height = 2.0 * h * focus_dist;
      const double viewport_width  = aspect_ratio * viewport_height;

      raycore::Vec3 w = (lookfrom - lookat).normalize();
    raycore::Vec3 u = raycore::cross(vup, w).normalize();
    raycore::Vec3 v = raycore::cross(w, u);

      raycore::Vec3 origin = lookfrom;
      raycore::Vec3 horizontal = viewport_width * u;
      raycore::Vec3 vertical   = viewport_height * v;
      raycore::Vec3 lower_left = origin - horizontal/2.0 - vertical/2.0 - focus_dist * w;

      Camera cam(origin, lower_left, horizontal, vertical);
      cam.u = u; cam.v = v; cam.w = w; // DOF 대비 보관
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
