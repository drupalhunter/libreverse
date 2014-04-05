
#include <boost/program_options.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/format.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#ifdef LIBREVERSE_DEBUG
#include <reverse/Reverse.h>
#include <reverse/Trace.h>
#endif

#include "Compiler_Dump_Algorithm.h"
#include "Compiler_Dump_Algorithm_Factory.h"
#include "Optimizer_Types.h"

#ifdef LIBREVERSE_DEBUG
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

using namespace reverse::classifier;
using namespace reverse::optimizer;

void help ( boost::program_options::options_description& desc )
{
      std::cout << desc << std::endl << std::endl
		<< "Support type values:" << std::endl
		<< "  java_class" << std::endl
		<< "  windows_pe" << std::endl
		<< "  linux_elf" << std::endl
		<< "  mac_mach_o" << std::endl;
      exit ( 0 );
}

int main (int ac, char** av)
{
  // Get start directory name from options.
  // IF not present start with present directory ('.')
  boost::program_options::options_description desc("Allowed options");
  desc.add_options()
    ("help", "produce help message")
    ("compiler_name", boost::program_options::value<std::string>(), "Unique string name describing the compiler")
    ("compiler_id", boost::program_options::value<int>(), "Unique numerical id describing the compiler")
    ("source_type", boost::program_options::value<std::string>(), "Type of input files [required]" )
    ("directory", boost::program_options::value<std::string>(), "Directory to start searching");

  boost::program_options::variables_map vm;

  try {
    boost::program_options::store(boost::program_options::parse_command_line(ac, av, desc), vm);
    boost::program_options::notify(vm);
  }
  catch ( boost::program_options::unknown_option& )
    {
      help ( desc );
    }
  catch ( boost::program_options::invalid_command_line_syntax& ic )
    {
      std::cout << ic.what() << std::endl;
      help ( desc );
    }

  if (vm.count("help")) {
    help ( desc );
  }

  std::string directory_string = ".";

  if (vm.count("directory"))
    {
      std::cout << "Directory to find files was set to....: "
		<< vm["directory"].as<std::string>() << "." << std::endl;
      
      directory_string = vm["directory"].as<std::string>();
    }
  else
    {
      help ( desc );
    }

  std::string compiler_name_string = "";

  if (vm.count("compiler_name"))
    {
      std::cout << "Compiler name was set to................: "
		<< vm["compiler_name"].as<std::string>() << "." << std::endl;
	  
      compiler_name_string = vm["compiler_name"].as<std::string>();
    }
  else
    {
      std::cout << "Compiler name tag must be specified. Use the flag --compiler_name <string> to set the tag" << std::endl;
      help ( desc );
    }

  boost::uint32_t compiler_id = 0;
  if ( vm.count ( "compiler_id" ) )
    {
      std::cout << "Compiler id was set to................: "
		<< vm["compiler_id"].as<int>() << "." << std::endl;
      
      compiler_id = vm["compiler_id"].as<int>();
    }
  else
    {
      std::cout << "Compiler id tag must be specified. Use the flag --compiler_id <float number> to set the tag" << std::endl;
      help ( desc );
    }

  std::string source_type = "";
  if ( vm.count ( "source_type" ) )
    {
      std::cout << "Source_type was set to................: "
		<< vm["source_type"].as<std::string>() << "." << std::endl;
      
      source_type = vm["source_type"].as<std::string>();
    }
  else
    {
      std::cout << "Source type tag must be specified. Use the flag --source_type <type> to set the tag" << std::endl;
      help ( desc );
    }

#ifdef LIBREVERSE_DEBUG
  Trace_State::Instance().set_Trace_Level ( reverse::api::TraceLevel::DATA );
  Trace_State::Instance().set_Trace_Area_Mask ( reverse::api::TraceArea::IO );
  Trace_State::Instance().open_Trace_File ();
#endif

  // open output file
  std::stringstream filename;
  filename << boost::str ( boost::format ( "test_data_%1%.xml") % compiler_name_string );

  std::ofstream xml_file ( (filename.str()).c_str() );
  xml_file << "<?xml version=\"1.0\"?>" << std::endl;
  xml_file << "<data>" << std::endl;

  GRNN_Data_Types::Value_Type source_value = GRNN_Data_Types::get_Type(source_type);

  if ( source_value == GRNN_Data_Types::UNKNOWN )
    {
      std::cout << "Invalid input source type" << std::endl;
      help ( desc );
    }

  try
    {
      // Get the algorithm for this file type
      reverse::optimizer_types::Compiler_Dump_Algorithm::ptr_t alg_ptr =
	( Compiler_Dump_Algorithm_Factory::Instance() ).get_Algorithm ( source_value );

      // Get list of target files found recursively from all directories below starting directory.
      std::vector<std::string> target_files;
      boost::filesystem::path dir_path ( directory_string );
      
      alg_ptr->find_Files ( dir_path, target_files );

      // For each file found
      for ( std::vector<std::string>::const_iterator cpos = target_files.begin();
	    cpos != target_files.end();
	    ++cpos )
	{
	  xml_file << alg_ptr->process ( compiler_id, *cpos );
	}

      // close output file
      xml_file << "</data>" << std::endl;
      xml_file.close();

#ifdef LIBREVERSE_DEBUG
      Trace_State::Instance().close_Trace_File ();
#endif
    }
  catch ( std::exception& )
    {
      std::cout << "Unsupported file type. Contact reverse developers if you believe they should support the target file type" << std::endl;
    }

  return 0;
}
