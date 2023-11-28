project(dynamics)

set (CMAKE_CXX_STANDARD 11)

add_executable(
	dynamics
	main.cpp	
)

target_link_libraries(dynamics sfml-graphics sfml-window sfml-system sfml-audio)
