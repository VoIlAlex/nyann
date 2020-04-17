#include "io_draft.h"

namespace nyann {
#ifdef DRAFT_DATASET_2_0_0_ALPHA_TEST
	std::ostream& operator<<(std::ostream& stream, const DataSet_draft<double>::NestedDataSet& dataset)
	{
		try
		{
			stream << dataset.value_const();
		}
		catch (ConversionError & e)
		{
			stream << "[";
			for (auto it = dataset.begin(); it != dataset.end(); it++)
			{
				if (it != dataset.begin())
					stream << ", ";
				stream << *it;
			}
			stream << "]";
		}
		return stream;
	}

	std::ostream& operator<<(std::ostream& stream, const DataSet_draft<float>::NestedDataSet& dataset)
	{
		try
		{
			stream << dataset.value_const();
		}
		catch (ConversionError & e)
		{
			stream << "[";
			for (auto it = dataset.begin(); it != dataset.end(); it++)
			{
				if (it != dataset.begin())
					stream << ", ";
				stream << *it;
			}
			stream << "]";
		}
		return stream;
	}
#endif
} // namespace nyann