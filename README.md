# raycore
Minimal C++ Ray Tracing Engine

## Goals
- Educational purpose, not performance
- Clean modular CMake build
- CLI toggles for rendering options
- Progressive feature milestones

## Milestones
- [X] Background gradient [ 2025 08 31 ]
- [ ] Sphere intersection
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
