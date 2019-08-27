project(AlexLens_tests)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
    add_link_options(-fprofile-instr-generate)
    #Uncomment in case of linker errors
    #link_libraries(clang_rt.profile-x86_64)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(--coverage)
    #Uncomment in case of linker errors
    link_libraries(gcov)
endif ()

add_executable(AlexLens_tests test_ReLU.cpp test_MaxPool2D.cpp test_Softmax.cpp)
target_link_libraries(AlexLens_tests PRIVATE AlexLens_lib catch)