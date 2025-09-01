#pragma once
#include <cmath>            // std::tan
#include "vec3.hpp"
#include "ray.hpp"

namespace camera {
class Camera {
public:
  static Camera LookAt(
      raycore::vec3 lookfrom,
      raycore::vec3 lookat,
      raycore::vec3 vup,
      double vfov_deg,
      double aspect_ratio,
      double focus_dist // ← viewport_size 대신
  ) {
      const double theta = vfov_deg * (3.141592653589793 / 180.0);
      const double h = std::tan(theta / 2.0);
      const double viewport_height = 2.0 * h * focus_dist;
      const double viewport_width  = aspect_ratio * viewport_height;

      raycore::vec3 w = (lookfrom - lookat).normalize();
      raycore::vec3 u = cross(vup, w).normalize();
      raycore::vec3 v = cross(w, u);

      raycore::vec3 origin = lookfrom;
      raycore::vec3 horizontal = viewport_width * u;
      raycore::vec3 vertical   = viewport_height * v;
      raycore::vec3 lower_left = origin - horizontal/2.0 - vertical/2.0 - focus_dist * w;

      Camera cam(origin, lower_left, horizontal, vertical);
      cam.u = u; cam.v = v; cam.w = w; // DOF 대비 보관
      return cam;
  }

  Camera(raycore::vec3 origin,
         raycore::vec3 lowerLeftCorner,
         raycore::vec3 horizontal,
         raycore::vec3 vertical)
    : origin(origin), lowerLeftCorner(lowerLeftCorner),
      horizontal(horizontal), vertical(vertical) {}

  raycore::ray getRay(double s, double t) const;

private:
  raycore::vec3 origin, lowerLeftCorner, horizontal, vertical;
  raycore::vec3 u, v, w; // ← 나중에 DOF에서 사용
};
} // namespace camera
