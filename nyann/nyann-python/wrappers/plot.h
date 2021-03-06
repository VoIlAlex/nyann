/*
	Format of exchange file:

	OUT [IN_OUT]
	N
	[input_1 ]output_1
	[input_2 ]output_2
	...
	[input_N ]output_N
*/

#pragma once

// For all the framework configurations
#include "../../nyann/_config.h"

#include <vector>
#include <filesystem>
#include <fstream>

namespace nyann {
	namespace python {

		template<typename _DT=double>
		void plot(const std::vector<_DT>& inputs, const std::vector<_DT>& outputs)
		{
			// Write to the exchange file
			size_t size = std::min(inputs.size(), outputs.size());
			std::ofstream exchange_file(".tmp_plot");
			exchange_file << "IN_OUT" << std::endl;
			exchange_file << size << std::endl;
			for (int i = 0; i < size; i++)
				exchange_file << inputs[i] << ' ' << outputs[i] << std::endl;
			exchange_file.close();

			// Compose the command
#ifdef PYTHON_3
			std::string command = "python3 \"nyann-python/plot.py\"";
#elif defined(PYTHON_3_VSCODE_MANUAL_MAKE)
			std::string command = "python3 \"nyann/nyann-python/plot.py\"";
#else
			std::string command = "python \"nyann-python\\plot.py\"";
#endif
			// convert all to
			// string arguments
			// for the python script
			std::vector<std::string> args;

			args.push_back("-i");
			args.push_back(".tmp_plot");


			// insert the arguments
			// into the command
			for (auto& arg : args)
				command += arg + " ";

			// Run python script
			system(command.c_str());

			// Delete temp file
			std::filesystem::remove(std::filesystem::current_path().append(".tmp_plot").string());
		}

		template<typename _DT=double>
		void plot(const std::vector<_DT>& outputs)
		{
			// Write to the exchange file
			size_t size = outputs.size();
			std::ofstream exchange_file(".tmp_plot");
			exchange_file << "OUT" << std::endl;
			exchange_file << size << std::endl;
			for (int i = 0; i < size; i++)
				exchange_file << outputs[i] << std::endl;
			exchange_file.close();

			// Compose the command
#ifdef PYTHON_3
			std::string command = "python3 \"nyann-python/plot.py\"";
#elif defined(PYTHON_3_VSCODE_MANUAL_MAKE)
			std::string command = "python3 \"nyann/nyann-python/plot.py\"";
#else
			std::string command = "python \"nyann-python\\plot.py\"";
#endif
			// convert all to
			// string arguments
			// for the python script
			std::vector<std::string> args;

			args.push_back("-i");
			args.push_back(".tmp_plot");


			// insert the arguments
			// into the command
			for (auto& arg : args)
				command += " " + arg;

			// Run python script
			system(command.c_str());

			// Delete temp file
			// TODO: delete this file, please
			// std::string temp_file_path = ".tmp_plot";
			// if (std::filesystem::exists(temp_file_path))
			// 	std::filesystem::remove(temp_file_path);
		}
	} // namespace python
} // namespace nyann
