#pragma once

#include <initializer_list>
#include <vector>

#include "utils/exceptions.h"
#include "utils/Size.h"

namespace nyann {
	template<typename _DT>
	class DataRow : public std::vector<_DT>
	{
	public:
		using std::vector<_DT>::vector;
		DataRow(const std::vector<_DT>& obj)
			: std::vector<_DT>(obj)
		{}
	};


	template<typename _DT>
	class DataSet : public std::vector<DataRow<_DT>>
	{
	public:
		DataSet() {}
		DataSet(std::initializer_list<DataRow<_DT>> il)
			: std::vector<DataRow<_DT>>(il)
		{}

		DataSet(int size, const std::allocator<_DT>& allocator = std::allocator<_DT>())
			: std::vector<DataRow<_DT>>(size, allocator)
		{}
		DataSet(const DataSet<_DT>& dataset)
			: std::vector<DataRow<_DT>>(dataset)
		{}

		// For now only two dimensional
		DataSet(nyann::Size size)
		{
			if (size == Size() || size[0] == 0)
				return;

			for (int i = 0; i < size[0]; i++)
			{
				if (size.size() == 1)
					this->push_back({});
				else
					this->push_back(DataRow<_DT>(size[1]));
			}
		}
		static DataSet<_DT> zeros_like(const DataSet<_DT>& dataset)
		{
			nyann::Size size_of_dataset;
			size_of_dataset.push_back(dataset.size());
			if (dataset.size() >= 1)
				size_of_dataset.push_back(dataset[0].size());

			return DataSet<_DT>(size_of_dataset);
		}
		static DataSet<_DT> ones_like(const DataSet<_DT>& dataset)
		{
			DataSet<_DT> result = DataSet<_DT>::zeros_like(dataset);
			for (int i = 0; i < result.get_size()[0]; i++)
				for (int j = 0; j < result.get_size()[1]; j++)
					result[i][j] = 1;
			return result;
		}
		static _DT abs_difference(const DataSet<_DT>& left, const DataSet<_DT>& right)
		{
			_DT difference = _DT();
			DataSet<_DT> diff_dataset = abs(left - right);
			for (int i = 0; i < diff_dataset.size(); i++)
				for (int j = 0; j < diff_dataset[0].size(); j++)
					difference += diff_dataset[i][j];
			return difference;
		}
		Size get_size() const
		{
			Size s;
			s.push_back(this->size());
			if (this->size() >= 1)
				s.push_back(this->operator[](0).size());
			return s;
		}
		Size shape() const
		{
			return get_size();
		}
	};

	template<typename _DT>
	DataRow<_DT> abs(const DataRow<_DT>& datarow)
	{
		DataRow<_DT> result = datarow;
		for (int i = 0; i < result.size(); i++)
			result[i] = result[i] > 0 ? result[i] : -result[i];
		return result;
	}


	template<typename _DT>
	DataSet<_DT> abs(const DataSet<_DT>& dataset)
	{
		DataSet<_DT> result;
		for (auto& row : dataset)
			result.push_back(abs(row));
		return result;
	}
	////////////////////////////
	// Operators overloadings //
	////////////////////////////
	template<typename _DT>
	DataRow<_DT> operator+(const DataRow<_DT>& left, const DataRow<_DT>& right)
	{
		if (left.size() != right.size())
			throw DifferentSizeError();

		DataRow<_DT> result(left.size());
		for (int i = 0; i < right.size(); i++)
			result[i] = left[i] + right[i];
		return result;
	}

	template<typename _DT>
	DataRow<_DT> operator-(const DataRow<_DT>& left, const DataRow<_DT>& right)
	{
		if (left.size() != right.size())
			throw DifferentSizeError(""); // TODO: exception message

		DataRow<_DT> result(left.size());
		for (int i = 0; i < result.size(); i++)
			result[i] = left[i] - right[i];
		return result;
	}

	template<typename _DT>
	DataRow<_DT> operator-(const DataRow<_DT>& obj)
	{
		DataRow<_DT> result(obj);

		for (int i = 0; i < obj.size(); i++)
			result[i] = -result[i];

		return result;
	}

	// used in evaluation of results
	/*template<typename _DT>
	double abs_difference(const DataSet<_DT>& left, const DataSet<_DT>& right)
	{
		if (left.size() != right.size())
			throw DifferentSizeError();

		double error = 0;
		for (int i = 0; i < left.size(); i++)
			for (int j = 0; j < left.front().size(); j++)
				error += left[i][j] - right[i][j];
		return error;
	}*/


	template<typename _DT>
	DataSet<_DT> operator-(const DataSet<_DT>& left, const DataSet<_DT>& right)
	{
		if (left.size() != right.size())
			throw DifferentSizeError(""); // TODO: exception message

		DataSet<_DT> result = DataSet<_DT>::zeros_like(left);

		for (int i = 0; i < left.get_size()[0]; i++)
			for (int j = 0; j < left.get_size()[1]; j++)
				result[i][j] = left[i][j] - right[i][j];

		return result;
	}

} // namespace nyann


// include subclasses of DataSet
#include "DataSet/TrainDataSet.h"