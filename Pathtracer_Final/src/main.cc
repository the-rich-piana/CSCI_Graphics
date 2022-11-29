#include "utilities.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#include <iostream>


color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);

    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}



//* Create a world containing spheres and a ground plain *//
hittable_list sphere_scene() {
    hittable_list world;

    //Create Ground
    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    //Create cool spheres
    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(4, 1, 2.4), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(.9, 0.9, 0.9));
    world.add(make_shared<sphere>(point3(3, 1.5, 0), 1.5, material2));

    auto material3 = make_shared<metal>(color(0.8, 0.55, 0.1), 0.0);
    world.add(make_shared<sphere>(point3(1, 1, -3), 1.0, material3));

    auto material4 = make_shared<lambertian>(color(1, 0.01, 0.01));
    world.add(make_shared<sphere>(point3(7, 0.5, 0), 0.5, material4));    

    return world;
}

int main() {

    // Image

    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 960;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 20;
    const int max_depth = 50;

    // World
    auto world = sphere_scene();

    //Make our camera
    point3 lookfrom(20, 5, 0);
    point3 lookat(0,0,0);
    vec3 vup(0,1,0);
    auto dist_to_focus = 15.0;
    auto aperture = 0.0;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    //Begin render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    std::cerr << "\rRendering with " << samples_per_pixel << " sample(s) per pixel\n";

    int channels_num = 3;
    //Image data
    unsigned char data[image_width * image_height * channels_num];
    int index = 0;

    //MAIN RENDER LOOP
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rPixels remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            
            color pixel_color(0,0,0);

            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            
            //std::cerr << pixel_color.e[0] ;
            color norm_pixel(0,0,0);
            norm_pixel = write_color(std::cout, pixel_color, samples_per_pixel);
            
            //save pixels in our data
            data[index++] = int(norm_pixel.e[0]); //ir;
            data[index++] = int(norm_pixel.e[1]); //ig;
            data[index++] = int(norm_pixel.e[2]); //ib;            
        }
    }
    //WRITE TO PNG
    stbi_write_jpg("render.png", image_width, image_height, channels_num, data, 100);

    std::cerr << "\n Render finished.\n";
}

