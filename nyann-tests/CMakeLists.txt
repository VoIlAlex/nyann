cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library

set (NYANN_TESTS_SRCS
test_ActivationFunction.cpp
test_conversion.cpp
test_dataset_operations.cpp
test_dataset_reducers.cpp
test_DataSet.cpp 
test_drafts.cpp 
test_exceptions.cpp
test_FCLayer.cpp 
test_goal.cpp 
test_inbox.cpp 
test_Index.cpp
test_Net.cpp 
test_Serializer.cpp
test_Size.cpp
test_Slice.cpp
test_TrainDataSet_draft.cpp
test_usage.cpp 
test_utils_draft.cpp
test_utils.cpp)



add_executable(runTests 
${NYANN_TESTS_SRCS}
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