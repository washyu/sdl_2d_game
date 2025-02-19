cmake_minimum_required(VERSION 3.10)
project(game1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set source files
file(GLOB SOURCES src/*.cpp src/player/*.cpp src/sprite/*.cpp src/utils/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

# Add include directories
include_directories(include include/player include/sprite include/utils)

# Add SDL2 paths for Scoop installation (Windows only)
if(WIN32)
    set(SDL2_DIR "$ENV{USERPROFILE}/scoop/apps/sdl2/current")
    set(SDL2_IMAGE_DIR "$ENV{USERPROFILE}/scoop/apps/sdl2-image/current")
    include_directories("${SDL2_DIR}/include/SDL2" "${SDL2_IMAGE_DIR}/include/SDL2_image")
    link_directories("${SDL2_DIR}/lib" "${SDL2_IMAGE_DIR}/lib")
endif()

# Link SDL2 libraries based on the platform
if(WIN32)
    target_link_libraries(${PROJECT_NAME}
        "${SDL2_DIR}/lib/SDL2.lib"
        "${SDL2_DIR}/lib/SDL2main.lib"
        "${SDL2_IMAGE_DIR}/lib/SDL2_image.lib"
    )
else()
    target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_image)
endif()

# Install required system libraries
include(InstallRequiredSystemLibraries)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Copy assets using post-build command
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMENT "Copying assets directory to output folder"
)

# Copy SDL2 DLLs to build directory (for Windows)
if(WIN32)
    file(GLOB SDL2_DLLS
        "${SDL2_DIR}/lib/SDL2.dll"
        "${SDL2_IMAGE_DIR}/lib/SDL2_image.dll"
        "${SDL2_IMAGE_DIR}/lib/optional/libpng16-16.dll"
    )
    
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL2_DLLS}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
