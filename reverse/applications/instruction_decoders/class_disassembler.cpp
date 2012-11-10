#include <boost/program_options.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/format.hpp>
#include <string>
#include <iostream>
#include <fstream>

#include "libreverse/data_containers/Data_Types.h"
#include "libreverse/data_containers/Control_Flow_Graph_Sequence.h"
#include "libreverse/data_containers/visitor/Control_Flow_Graph_Graphviz_Visitor.h"
#include "libreverse/components/input/instruction_decoders/Decoder_Types.h"
#include "libreverse/components/input/instruction_decoders/Java_Assembly_Actions.h"
#include "libreverse/components/input/instruction_decoders/Java_Decoder.h"

#ifdef LIBREVERSE_DEBUG
#include <libreverse/Reverse.h>
#include <libreverse/Trace.h>
using namespace libreverse::api;
using namespace libreverse::trace;
#endif

using namespace libreverse;

void help ( boost::program_options::options_description& desc )
{
  std::cout << "class_disassembler <file>" << std::endl
	    << desc << std::endl;
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
    ( "help", "produce help message" );

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

  std::string target = argv[argc-1];

#ifdef LIBREVERSE_DEBUG
  Trace_State::Instance().set_Trace_Level ( TraceLevel::DATA );
  Trace_State::Instance().set_Trace_Area_Mask ( TraceArea::INSTRUCTION_DECODER | TraceArea::DATA_CONTAINERS );
  Trace_State::Instance().open_Trace_File ();
#endif /* LIBREVERSE_DEBUG */

  decoder_types::Java_Actions::ptr_t actions_ptr ( new decoder::Java_Assembly_Actions() );
  decoder::Java_Decoder decoder_ref ( actions_ptr );
  data_types::Control_Flow_Graph_Sequence::ptr_t cfg_ptr = decoder_ref.execute ( target );

  for ( data_types::Control_Flow_Graph_Sequence::Sequence_t::iterator pos = cfg_ptr->begin();
	pos != cfg_ptr->end();
	++pos )
    {
      std::stringstream output;
      std::string name = (*pos)->get_Name() + ".dot";
      std::ofstream file ( name.c_str() );
      visitor::Control_Flow_Graph_Graphviz_Visitor graphviz_ref;
      graphviz_ref.visit ( **pos, output );
      file << output.str() << std::endl;
      file.close();
    }

#ifdef LIBREVERSE_DEBUG
  Trace_State::Instance().close_Trace_File ();
#endif /* LIBREVERSE_DEBUG */

  return 0;
}
