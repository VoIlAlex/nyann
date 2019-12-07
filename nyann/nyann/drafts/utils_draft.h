
#include "DataSet_draft.h"

namespace nyann {
    
    template<typename _DT>
    DataSet_draft<_DT> abs(const DataSet_draft<_DT>& dataset) 
    {
        DataSet_draft<_DT> new_dataset(dataset);
        for(auto it = new_dataset.begin(); it != new_dataset.end(); it++)
            it->set_value(abs(it->value()));
        return new_dataset;
    }

} // namespace nyann
