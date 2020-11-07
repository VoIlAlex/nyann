cmake_minimum_required(VERSION 3.0.0)
project(nyann VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 17)

# =====
# GTest
# =====
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# ============
# Project Root
# ============
set (NYANN_ROOT nyann)
set (NYANN_SANDBOX_ROOT nyann-sandbox)
set (NYANN_TESTS_ROOT nyann-tests)

# ==========
# Subfolders
# ==========
set (NYANN ${NYANN_ROOT}/nyann)
set (NYANN_EXAMPLES ${NYANN_ROOT}/nyann-examples)
set (NYANN_PYTHON ${NYANN_ROOT}/nyann-python)

# ============
# Source Files
# ============
set (NYANN_SRCS 
${NYANN}/utils/conversion.cpp)

set (NYANN_DRAFT_SRCS
${NYANN}/drafts/io_draft.cpp)

set (NYANN_TESTS_SRCS
${NYANN_TESTS_ROOT}/test_ActivationFunction.cpp
${NYANN_TESTS_ROOT}/test_conversion.cpp
${NYANN_TESTS_ROOT}/test_dataset_operations.cpp
${NYANN_TESTS_ROOT}/test_dataset_reducers.cpp
${NYANN_TESTS_ROOT}/test_DataSet.cpp 
${NYANN_TESTS_ROOT}/test_drafts.cpp 
${NYANN_TESTS_ROOT}/test_exceptions.cpp
${NYANN_TESTS_ROOT}/test_FCLayer.cpp 
${NYANN_TESTS_ROOT}/test_goal.cpp 
${NYANN_TESTS_ROOT}/test_inbox.cpp 
${NYANN_TESTS_ROOT}/test_Index.cpp
${NYANN_TESTS_ROOT}/test_Net.cpp 
${NYANN_TESTS_ROOT}/test_Serializer.cpp
${NYANN_TESTS_ROOT}/test_Size.cpp
${NYANN_TESTS_ROOT}/test_Slice.cpp
${NYANN_TESTS_ROOT}/test_TrainDataSet_draft.cpp
${NYANN_TESTS_ROOT}/test_usage.cpp 
${NYANN_TESTS_ROOT}/test_utils_draft.cpp
${NYANN_TESTS_ROOT}/test_utils.cpp)

set (NYANN_SANDBOX_SRCS
${NYANN_SANDBOX_ROOT}/pch.cpp
${NYANN_SANDBOX_ROOT}/nyann-sandbox.cpp)

# ============
# Header Files
# ============
set (NYANN_HDRS
# ActivationFunctions
${NYANN_ROOT}/nyann/ActivationFunction/BinaryActivation.h
${NYANN_ROOT}/nyann/ActivationFunction/BipolarActivation.h
${NYANN_ROOT}/nyann/ActivationFunction/ReLUActivation.h
${NYANN_ROOT}/nyann/ActivationFunction/SigmoidActivation.h
${NYANN_ROOT}/nyann/ActivationFunction/SoftMaxActivation.h
# DataSet
${NYANN_ROOT}/nyann/DataSet/DataSetOperation.h
${NYANN_ROOT}/nyann/DataSet/DataSetReducer.h
${NYANN_ROOT}/nyann/DataSet/DataSetSerializer.h
${NYANN_ROOT}/nyann/DataSet/TrainDataSet.h
# Layer
${NYANN_ROOT}/nyann/Layer/ConvLayer1D.h
${NYANN_ROOT}/nyann/Layer/FCLayer.h
# Loss
${NYANN_ROOT}/nyann/Loss/MSELoss.h
# Optimizer
${NYANN_ROOT}/nyann/Optimizer/SGDOptimizer.h
# Utils
${NYANN_ROOT}/nyann/utils/conversion.h
${NYANN_ROOT}/nyann/utils/dataset_operations.h
${NYANN_ROOT}/nyann/utils/dataset_reducers.h
${NYANN_ROOT}/nyann/utils/exceptions.h
${NYANN_ROOT}/nyann/utils/Index.h
${NYANN_ROOT}/nyann/utils/io.h
${NYANN_ROOT}/nyann/utils/Serializer.h
${NYANN_ROOT}/nyann/utils/Size.h
${NYANN_ROOT}/nyann/utils/Slice.h
# Root
${NYANN_ROOT}/nyann/_config.h
${NYANN_ROOT}/nyann/ActivationFunction.h
${NYANN_ROOT}/nyann/dataset.h
${NYANN_ROOT}/nyann/Layer.h
${NYANN_ROOT}/nyann/Loss.h
${NYANN_ROOT}/nyann/Net.h
${NYANN_ROOT}/nyann/Optimizer.h
${NYANN_ROOT}/nyann/utils.h)

set (NYANN_SANDBOX_HDRS
${NYANN_SANDBOX_ROOT}/pch.h)

set (NYANN_HDRS_EXAMPLES
${NYANN_EXAMPLES}/labs.h)

set (NYANN_HDRS_PYTHON
${NYANN_PYTHON}/wrappers/DataSetGeneration.h
${NYANN_PYTHON}/wrappers/plot.h)

set (NYANN_DRAFT_HDRS
${NYANN}/drafts/DataSet_draft.h
${NYANN}/drafts/io_draft.h
${NYANN}/drafts/utils_draft.h
${NYANN}/drafts.h)

set (NYANN_TESTS_HDRS
${NYANN_TESTS_ROOT}/pch.h)

# =========
# Libraries
# =========
add_library(nyann
${NYANN_SRCS}
${NYANN_HDRS}
${NYANN_DRAFT_HDRS})

# ===========
# Executables
# ===========
add_executable(main 
${NYANN_SANDBOX_SRCS}
${NYANN_SANDBOX_HDRS})
target_link_libraries(main nyann)

add_executable(runTests
${NYANN_TESTS_SRCS}
${NYANN_TESTS_HDRS})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread nyann)