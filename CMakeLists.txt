cmake_minimum_required(VERSION 3.17)
project(bomberman)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(Irrlicht_DIR "${CMAKE_MODULE_PATH}/Irrlicht")
set(SFMLAudio_DIR "${CMAKE_MODULE_PATH}/SFMLAudio")

find_package(Irrlicht REQUIRED)

include_directories("${CMAKE_CURRENT_LIST_DIR}/include")
include_directories(${Irrlicht_INCLUDE_DIRS})
FILE(GLOB sources "src/*.cpp")
FILE(GLOB includes "include/*.hpp")

if(NOT WIN32)
message("Linux")
    find_package(OpenGL REQUIRED)
    find_package(SFML 2.5 COMPONENTS audio REQUIRED)
    include_directories (${SFML_INCLUDE_DIR})
else()
    find_package(SFMLAudio REQUIRED)
    include_directories (${SFMLAudio_INCLUDE_DIRS})
endif()

# include_directories(
#         "/usr/include/irrlicht"
#         ${PROJECT_SOURCE_DIR}/include
# )

add_executable(${PROJECT_NAME} ${sources} ${includes})

if(WIN32)
    file(COPY "${Irrlicht_DIR}/Irrlicht.dll" DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "${SFMLAudio_DIR}/sfml-audio-d-2.dll" DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "${SFMLAudio_DIR}/sfml-system-d-2.dll" DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "${SFMLAudio_DIR}/openal32.dll" DESTINATION ${CMAKE_BINARY_DIR})
    target_link_libraries(bomberman ${OPENGL_LIBRARIES} ${Irrlicht_LIBRARIES} ${SFMLAudio_LIBRARIES})
else()
    target_link_libraries(bomberman ${OPENGL_LIBRARIES} ${Irrlicht_LIBRARIES} sfml-audio)
endif()
# target_link_libraries(${PROJECT_NAME} ${Irrlicht_LIBRARIES})
# target_link_libraries(${PROJECT_NAME} -lsfml-audio)


# set(DLL_IRRLICHT ${Irrlicht_DIR}/Irrlicht.dll)
# file(GLOB DLL_FILES ${DLL_IRRLICHT})
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${DLL_IRRLICHT} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
# install(FILES ${DLL_FILES} DESTINATION bin)
