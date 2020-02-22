cmake_minimum_required(VERSION 3.0.0)
project(nyann VERSION 0.1.0)


set (CMAKE_CXX_STANDARD 17)

# ============
# Project Root
# ============
set (NYANN_ROOT nyann)

# ==========
# Subfolders
# ==========
set (NYANN ${NYANN_ROOT}/nyann)
set (NYANN_EXAMPLES ${NYANN_ROOT}/nyann-examples)
set (NYANN_PYTHON ${NYANN_ROOT}/nyann-python)


# ============
# Source Files
# ============
set(NYANN_MAIN_SRC ${NYANN_ROOT}/main.cpp)

set (NYANN_DRAFT_SRCS
${NYANN}/drafts/io_draft.cpp)

# ============
# Header Files
# ============
set (NYANN_HDRS
${NYANN}/nyann/ActivationFunction/BinaryActivation.h
${NYANN}/nyann/ActivationFunction/BipolarActivation.h
${NYANN}/nyann/ActivationFunction/ReLUActivation.h
${NYANN}/nyann/ActivationFunction/SigmoidActivation.h
${NYANN}/nyann/ActivationFunction/SoftMaxActivation.h
${NYANN}/nyann/DataSet/TrainDataSet.h
${NYANN}/nyann/Layer/ConvLayer1D.h
${NYANN}/nyann/Layer/FCLayer.h
${NYANN}/nyann/MSELoss.h
${NYANN}/nyann/SGDOptimizer.h
${NYANN}/nyann/utils/exception.h
${NYANN}/nyann/utils/Index.h
${NYANN}/nyann/utils/io.h
${NYANN}/nyann/utils/Size.h
${NYANN}/nyann/utils/Slice.h
${NYANN}/nyann/_config.h
${NYANN}/nyann/ActivationFunction.h
${NYANN}/nyann/dataset.h
${NYANN}/nyann/Layer.h
${NYANN}/nyann/Loss.h
${NYANN}/nyann/Net.h
${NYANN}/nyann/Optimizer.h
${NYANN}/nyann/utils.h)

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


# ===========
# Executables
# ===========
add_executable(main ${NYANN_MAIN_SRC})

