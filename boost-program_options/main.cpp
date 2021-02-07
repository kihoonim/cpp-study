#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>


boost::program_options::variables_map parse_config(std::string config_path)
{
	boost::program_options::options_description config("Config");
	config.add_options()
		("in_memory,h", boost::program_options::value<bool>(), "In Memory Mode");

	boost::program_options::variables_map config_vm;
	std::ifstream config_file(config_path);
	boost::program_options::store(boost::program_options::parse_config_file<char>(config_file, config, true), config_vm);
	boost::program_options::notify(config_vm);

	return config_vm;
}


int main(int argc, char* argv[])
{

}