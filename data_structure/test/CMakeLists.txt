set (Boost_USE_STATIC_LIBS OFF) #enable dynamic linking

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(${Boost_INCLUDE_DIR})
include_directories(../src)

add_executable(test_data_structure test.cpp)

# Note: a target should be already defined using 'add_executable' or 'add_library' 
target_link_libraries(test_data_structure ${Boost_LIBRARIES})
