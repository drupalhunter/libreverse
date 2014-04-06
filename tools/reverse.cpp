#include <reverse/reverse.hpp>
#include <reverse/results.hpp>

#include <boost/program_options.hpp>
#include <boost/format.hpp>

#include <iostream>

int main ( int ac, char** av )
{
	// Declare the supported options.

  boost::program_options::options_description desc("Allowed options");
  desc.add_options()
    ("help", "produce help message")
    ("file", boost::program_options::value<std::string>(), "file to reverse");
  
  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::parse_command_line(ac, av, desc), vm);
  boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    if (vm.count("file")) {
        std::cout << "File to analyze was set to "
                  << vm["file"].as<std::string>() << "." << std::endl;
    }
      else {
        std::cout << "File to analyze was not set." << std::endl;
        return 0;
    }

    reverse::reverse r_obj;
    boost::int32_t result = r_obj.execute ( vm["file"].as<std::string>(),
                                            reverse::input_types::binary,
                                            reverse::output_types::java,
                                            reverse::trace_level::data,
					    reverse::trace_area::grnn );

    if ( result != reverse::results::success )
      {
	std::cerr << "Problem with running the analysis on " << vm["file"].as<std::string>() << std::endl;
      }
    else
      {
	std::cerr << "Success processing " << vm["file"].as<std::string>() << std::endl;
      }

    return 0;
}
