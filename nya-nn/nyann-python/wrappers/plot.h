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
#include <vector>
#include <filesystem>
#include <fstream>

namespace nyann {
	namespace python {
		void plot(const std::vector<double>& inputs, const std::vector<double>& outputs)
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
			std::string command = "python \"nyann-python\\plot.py\"";

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

		void plot(const std::vector<double>& outputs)
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
			std::string command = "python \"nyann-python\\plot.py\"";

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
			std::filesystem::remove(std::filesystem::current_path().append(".tmp_plot").string());
		}
	} // namespace python
} // namespace nyann