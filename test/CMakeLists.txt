project(AlexLens_tests)

add_executable(AlexLens_tests testmain.cpp)
target_link_libraries(AlexLens_tests PRIVATE AlexLens_lib catch)