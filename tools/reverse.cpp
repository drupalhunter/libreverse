#include <libreverse/source/Reverse.h>
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/format.hpp>

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

    libreverse::api::Reverse r_obj;
    boost::int32_t result = r_obj.execute ( vm["file"].as<std::string>(),
                                            libreverse::api::Input_Types::BINARY,
                                            libreverse::api::Output_Types::JAVA,
                                            libreverse::api::TraceLevel::DATA,
					    libreverse::api::TraceArea::GRNN );

    if ( result != libreverse::api::Results::SUCCESS )
      {
	std::cerr << "Problem with running the analysis on " << vm["file"].as<std::string>() << std::endl;
      }
    else
      {
	std::cerr << "Success processing " << vm["file"].as<std::string>() << std::endl;
      }

    return 0;
}
