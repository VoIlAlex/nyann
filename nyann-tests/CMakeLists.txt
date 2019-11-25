cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests 
test_BinaryActivation.cpp
test_ConvLayer1D.cpp
test_DataSet.cpp 
test_drafts.cpp 
test_FCLayer.cpp 
test_goal.cpp 
test_inbox.cpp 
test_Net.cpp 
test_Size.cpp
test_Slice.cpp
test_usage.cpp 
test_utils.cpp
)
# add_executable(runTests test_BinaryActivation.cpp)
# add_executable(runTests test_DataSet.cpp)
# add_executable(runTests test_drafts.cpp)
# add_executable(runTests test_FCLayer.cpp)
# add_executable(runTests test_goal.cpp)
# add_executable(runTests test_inbox.cpp)
# add_executable(runTests test_Net.cpp)
# add_executable(runTests test_usage.cpp)
# add_executable(runTests test_utils.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)