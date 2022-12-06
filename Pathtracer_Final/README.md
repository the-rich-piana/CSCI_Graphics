--- CSCI 4229 Giuliano Costa Final Project Checkpoint 11/29 ---

Interactive Pathtracer 

# Build Instructions : #

This project uses the CMake VScode extension. But can be build with the command line CMake tools.
My local machine is Linux, such that I'm not sure how to build on Windows/Mac. But as long as you have the CMake extension installed in VScode, you can simply right click CMakeLists.txt > Configure All Projects > Build All Projects. Otherwise, run the below from terminal.

Using command line in the Pathtracer_Final directory run:

1. cmake -B build

2. cmake --build build

3. cd build/

4. Once built, run the pathtracer in the build folder, (takes me ~30 seconds):

./Pathtracer

5. Wait for the image to be generated / open the generated image in the build folder, "Render.jpg".
Sample images can be found in the /images folder.

Description:

After weeks of trying different methods; I have settled on a vanilla C++ implentation of a raytracer.
Though it is not interactive, has no GUI, and simply writes an image/window, my goal is to get everything into an OpenGL context. This project uses inspiration from Peter Shirley's "Ray Tracing in One Weekend"
https://raytracing.github.io/books/RayTracingInOneWeekend.html 

This is a barebones implementation of Raytracing, the only third party library I've used is stb_image (and SDL for the window), which is great and lets me save png/jpeg/bmp images. I tried a number of GLEW, GLSL, ThreeJS, and GLFW type projects, but there is a HUGE diversity in compute libraries, Vulkan, Intel Embree, CUDA, OpenRT, etc... All of which are very complex. Every single OpenGL method I tried was a mess of dependencies, outdated libraries, linking problems, incompatible drivers, and confusion. It is borderline insanity. The repositories that did work were far too complicated to reproduce in a simplistic fashion.

Since this does not use any sort of GLSL compute fragment shader it is by nature CPU bound. And thus relatively slow. Nonetheless, it is much easier to comprehend. Which is why I assume Shirley has opted to teach this in the simplest way possible. 

My goal is to get this into an OpenGL context somehow and integrate GLSL. As well as compute the normals and ray intersects on meshes other than spheres. For more complicated objects that aren't spheres, I might need to implement a BVH (Bounding Volume Hierarchy), which is very complex. If I have enough time I'll look at creating some different light sources (environment, point, area, etc...).

