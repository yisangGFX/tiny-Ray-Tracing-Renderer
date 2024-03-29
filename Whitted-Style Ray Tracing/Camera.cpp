#include "Camera.h"
Camera::Camera(Point3 lookfrom, Point3 lookat, Vec3 up, float fov0, float scale, float aperture, float focusDis, float _time0, float _time1)
{
    auto theta = degrees_to_radians(fov0);
    auto h = tan(theta / 2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = scale * viewport_height;
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(up, w));
    v = cross(w, u);

    origin = lookfrom;
    horizontal = focusDis * viewport_width * u;
    vertical = focusDis * viewport_height * v;
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - focusDis * w;

    lens_radius = aperture / 2;
    time0 = _time0;
    time1 = _time1;
}
Ray Camera::getRay(float s,float t) const
{
    Vec3 rd = lens_radius * random_in_unit_disk();
    Vec3 offset = rd.x * u + rd.y * v;

    return Ray(
        origin + offset,
        lower_left_corner + s * horizontal + t * vertical - origin - offset,randomFloat(time0,time1));
}

