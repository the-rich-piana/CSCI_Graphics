cmake_minimum_required ( VERSION 3.1.0 )

project ( RTWeekend
  VERSION 3.0.0
  LANGUAGES CXX
)

# Set to c++11
set ( CMAKE_CXX_STANDARD 11 )

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


# Utilities
set ( COMMON_ALL
utils/utilities.h
utils/ray.h
utils/vec3.h
utils/camera.h
utils/stb_image.h
utils/stb_image_write.h
utils/sdltemplate.h
#utils/glm/include/glm.hpp
)



set ( SOURCE_PATHTRACER
${COMMON_ALL}
src/hittable.h
src/hittable_list.h
src/material.h
src/sphere.h
src/quad.h
src/main.cpp
src/shaders/frag_shader.glsl
src/shaders/vert_shader.glsl
)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(GLFW REQUIRED glfw3)

find_package (glm REQUIRED )


#find_package(GLM)


include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} )

#target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

# Executables
add_executable(Pathtracer     ${SOURCE_PATHTRACER})

target_link_libraries(Pathtracer ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES})

include_directories(utils/)
