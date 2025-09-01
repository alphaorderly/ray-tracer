# raycore

Minimal C++ Ray Tracing Engine

## Goals

- Educational purpose, not performance
- Clean modular CMake build
- CLI toggles for rendering options
- Progressive feature milestones

## Milestones

- [x] Background gradient [ 2025 08 31 ]
- [x] Sphere intersection
- [ ] Anti-aliasing
- [ ] Diffuse/Metal/Dielectric
- [ ] CLI options
- [ ] Multi-threaded rendering

---

### Note:

#### 2025-08-31

- implement ray.hpp
  - origin, dir included
- implement vec3.hpp
  - basic vector operations
- implement color.hpp
  - write_color function
- implement main.cpp
  - image dimensions
  - ray generation
  - color calculation

#### 2025-09-01

- implement sphere.hpp
  - Sphere class
  - hit function
- implement hittable_list.hpp
  - HittableList class
  - hit function
- implement hit_record.hpp
  - HitRecord class
