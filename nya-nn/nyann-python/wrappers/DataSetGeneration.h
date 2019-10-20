#include "..//..//nyann/dataset.h"

#include <string>
#include <fstream>

namespace nyann {
	namespace python {

		template <typename _DT>
		TrainDataSet<_DT> generate_linear_dataset(int size, int input_size, double deviation)
		{
			TrainDataSet<double> dataset;
			std::string command = "python \"nyann-python\\generate_dataset.py\" ";

			// convert all to
			// string arguments
			// for the python script
			std::vector<std::string> args;

			args.push_back("-s");
			args.push_back(std::to_string(size));

			args.push_back("-d");
			args.push_back(std::to_string(deviation));

			args.push_back("-o");
			args.push_back("tmp");

			args.push_back("-i");
			args.push_back(std::to_string(input_size));

			args.push_back("-l");


			// insert the arguments
			// into the command
			for (auto& arg : args)
				command += " " + arg;

			system(command.c_str());

			// parse dataset
			std::ifstream dataset_file("tmp");
			std::string line_csv;

			DataRow<double> input;
			DataRow<double> output;

			for (int i = 0; dataset_file >> line_csv; i++)
			{
				if (i % 2 == 0)
				{
					if (!input.empty() && !output.empty())
					{
						dataset.push_back({ input, output });
						input.clear();
						output.clear();
					}

					double value;
					std::string str_value;

					for (auto ch : line_csv)
					{
						if (ch == ',')
						{
							value = atof(str_value.c_str());
							input.push_back(value);
							str_value.clear();
						}
						else
						{
							str_value += ch;
						}
					}
					if (!str_value.empty())
					{
						value = atof(str_value.c_str());
						input.push_back(value);
						str_value.clear();
					}
				}
				else
				{
					double value;
					std::string str_value;

					for (auto ch : line_csv)
					{
						if (ch == ',')
						{
							value = atof(str_value.c_str());
							output.push_back(value);
							str_value.clear();
						}
						else
						{
							str_value += ch;
						}
					}
					if (!str_value.empty())
					{
						value = atof(str_value.c_str());
						output.push_back(value);
						str_value.clear();
					}
				}
			}
			if (!input.empty() && !output.empty())
			{
				dataset.push_back({ input, output });
			}

			// remove temporary file
			std::filesystem::remove("tmp");
			return dataset;
		}
	} // namespace python
} // namespace nyann