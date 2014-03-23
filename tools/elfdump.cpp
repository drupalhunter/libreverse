#include <reverse/reverse.hpp>
#include <reverse/io/file_id.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_reader_32.hpp>

#include <boost/make_shared.hpp>
#include <boost/program_options.hpp>
#include <boost/format.hpp>

#include <iostream>

#include <reverse/trace.hpp>
#include <reverse/trace_level.hpp>
#include <reverse/trace_state.hpp>

int main ( int ac, char** av )
{
  // Declare the supported options.
  
  boost::program_options::options_description desc("Allowed options");
  desc.add_options()
		("help", "produce help message")
    ("file", boost::program_options::value<std::string>(), "file to print headers");
  
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
    
    reverse::trace_state::instance().set_trace_level ( reverse::trace_level::data );
    reverse::trace_state::instance().set_trace_area_mask ( reverse::trace_area::io );
    reverse::trace_state::instance().open_trace_file ();

    std::string filename = vm["file"].as<std::string>();

    boost::shared_ptr < reverse::io::file_id > file_obj =
      boost::make_shared < reverse::io::file_id > ( filename );

    reverse::io::input::file_readers::linux_elf::elf_reader_32 r_obj ( file_obj );

    std::cout << r_obj.to_string();

    reverse::trace_state::instance().close_trace_file();

    return 0;
}
