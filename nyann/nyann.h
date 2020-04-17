#pragma once


// include all the headers of 
// nyann library

#include "nyann/_config.h"

#ifdef DRAFT_DATASET_2_0_0_ALPHA_TEST

#include "nyann/drafts/DataSet_draft.h"
#include "nyann/drafts/TrainDataSet_draft.h"
//#include "nyann/DataSet.h"
#include "nyann/Layer.h"
#include "nyann/Loss.h"
#include "nyann/Optimizer.h"
#include "nyann/Net.h"
#include "nyann/utils.h"
#include "nyann/ActivationFunction.h"


// python integration

#include "nyann-python/wrappers/DataSetGeneration.h"
#include "nyann-python/wrappers/plot.h"

#elif defined (DRAFT_DATASET_2_0_0_PRERELEASE)

#include "nyann/DataSet.h"
#include "nyann/Layer.h"
#include "nyann/Loss.h"
#include "nyann/Optimizer.h"
#include "nyann/Net.h"
#include "nyann/utils.h"
#include "nyann/ActivationFunction.h"


// python integration

#include "nyann-python/wrappers/DataSetGeneration.h"
#include "nyann-python/wrappers/plot.h"


#else

#include "nyann/DataSet.h"
#include "nyann/Layer.h"
#include "nyann/Loss.h"
#include "nyann/Optimizer.h"
#include "nyann/Net.h"
#include "nyann/utils.h"
#include "nyann/ActivationFunction.h"


// python integration

#include "nyann-python/wrappers/DataSetGeneration.h"
#include "nyann-python/wrappers/plot.h"


#endif