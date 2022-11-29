cmake_minimum_required ( VERSION 3.1.0 )

project ( RTWeekend
  VERSION 3.0.0
  LANGUAGES CXX
)

# Set to c++11
set ( CMAKE_CXX_STANDARD 11 )

# Utilities
set ( COMMON_ALL
  utils/utilities.h
  utils/ray.h
  utils/vec3.h
  utils/camera.h
  utils/stb_image.h
  utils/stb_image_write.h
)

set ( SOURCE_PATHTRACER
  ${COMMON_ALL}
  src/hittable.h
  src/hittable_list.h
  src/material.h
  src/sphere.h
  src/main.cc
)

# Executables
add_executable(Pathtracer     ${SOURCE_PATHTRACER})

include_directories(utils/)
