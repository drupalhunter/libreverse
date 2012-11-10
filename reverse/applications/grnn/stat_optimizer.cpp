#include <boost/program_options.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/format.hpp>

#include "Optimizer_Algorithm.h"
#include "Optimizer_Algorithm_Factory.h"
#include "Optimizer_Types.h"

#include "libreverse/components/input/grnn/Statistical.h"
#include "libreverse/components/input/grnn/GRNN_Data_Types.h"
#include "libreverse/components/input/grnn/IO.h"
#include "libreverse/components/input/grnn/Candidate_Solution.h"
#include "libreverse/components/input/grnn/Optimizer.h"

#ifdef LIBREVERSE_DEBUG
#include <libreverse/Reverse.h>
#include <libreverse/Trace.h>
#endif

#include <iostream>

#ifdef LIBREVERSE_DEBUG
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

using namespace libreverse::classifier;
using namespace libreverse::optimizer;

void
find_Data_Files ( const boost::filesystem::path& dirpath, std::list<std::string>& output_files )
{

    if ( exists ( dirpath ) )
    {
        boost::filesystem::directory_iterator end_itr; // default construction yields past the end

        for ( boost::filesystem::directory_iterator itr ( dirpath );
	      itr != end_itr;
	      ++itr )
        {
            if ( ! is_directory ( *itr ) )
            {
                // If file name ends with '.class'
                std::string name = itr->leaf();

                if ( name.find ( ".xml" ) != std::string::npos )
                {
                    output_files.push_back ( itr->string() );
                }
            }
        }
    }
}

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

int main ( int argc, char** argv )
{

  // Handle command line options
  std::string directory_string = "";
  std::string source_type = "";
  std::string output_string = "";

  // Options
  boost::program_options::options_description desc ( "Allowed options" );
  desc.add_options()
    ( "help", "produce help message" )
    ( "directory", boost::program_options::value<std::string>(),
      "Directory where input training data files in XML format is stored[required]" )
    ( "source_type", boost::program_options::value<std::string>(), "Type of input training data [required]" )
    ( "output", boost::program_options::value<std::string>(), "Output filename for storing final training data [required]" );

  boost::program_options::variables_map vm;

  try
    {
      boost::program_options::store ( boost::program_options::parse_command_line ( argc, argv, desc ), vm );
      boost::program_options::notify ( vm );
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


  if ( vm.count ( "help" ) )
    {
      help ( desc );
    }

  if ( vm.count ( "directory" ) )
    {
      /*
      std::cout << "Directory to be searched....: "
		<< vm["directory"].as<std::string>() << "." << std::endl;
      */
      directory_string = vm["directory"].as<std::string>();
    }
  else
    {
      help ( desc );
    }

  if ( vm.count ( "source_type" ) )
    {
      /*
      std::cout << "Input source type....: "
		<< vm["source_type"].as<std::string>() << "." << std::endl;
      */
      source_type = vm["source_type"].as<std::string>();
    }
  else
    {
      help ( desc );
    }

  if ( vm.count ( "output" ) )
    {
      /*
      std::cout << "Output file name for final training data....: "
		<< vm["output"].as<std::string>() << "." << std::endl;
      */
      output_string = vm["output"].as<std::string>();
    }
  else
    {
      help ( desc );
    }

#ifdef LIBREVERSE_DEBUG
  Trace_State::Instance().set_Trace_Level ( TraceLevel::DATA );
  Trace_State::Instance().set_Trace_Area_Mask ( TraceArea::GRNN );
  Trace_State::Instance().open_Trace_File ();
#endif /* LIBREVERSE_DEBUG */

  try
    {
      GRNN_Data_Types::Value_Type source_value = GRNN_Data_Types::get_Type ( source_type );

      if ( source_value == GRNN_Data_Types::UNKNOWN )
	{
	  std::cout << "Invalid input source type" << std::endl;
	  return 1;
	}

      // Seed the random number generator
      srand ( time ( NULL ) );

      // Get the algorithm for this file type
      libreverse::optimizer_types::Optimizer_Algorithm::ptr_t alg_ptr =
	( Optimizer_Algorithm_Factory::Instance() ).get_Algorithm<Statistical> ( source_value );

      // Process files
      std::list<std::string> data_files;
      boost::filesystem::path dir_path ( directory_string );
      find_Data_Files ( dir_path, data_files );
      
      alg_ptr->process ( data_files );
        
      // Print results
      //      std::cout << alg_ptr->print_Results() << std::endl;

      // Save data use to train GRNN to a final file. The data written
      // will only be those attributes used based on the
      // Configuration.
      //      alg_ptr->save_Data ( output_string );

    }
  catch ( std::exception& e )
    {
      std::cerr << e.what() << std::endl;
    }
#ifdef LIBREVERSE_DEBUG
  Trace_State::Instance().close_Trace_File ();
#endif /* LIBREVERSE_DEBUG */

  return 0;
}
