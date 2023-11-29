project(dynamics)

set (CMAKE_CXX_STANDARD 11)

add_executable(
	dynamics
	src/main.cpp
	src/vec.cpp
	src/iter.cpp
	src/cx.cpp
	src/func.cpp
	src/color.cpp
	src/log.cpp
)

target_link_libraries(dynamics sfml-graphics sfml-window sfml-system sfml-audio)
