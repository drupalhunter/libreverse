/*  Java_Decoder.cpp

    Copyright (C) 2008 Stephen Torri

    This file is part of Libreverse.

    Libreverse is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published
    by the Free Software Foundation; either version 3, or (at your
    option) any later version.

    Libreverse is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see
    <http://www.gnu.org/licenses/>.
*/

#include <reverse/components/input/instruction_decoders/java_decoder.hpp>
#include <reverse/components/input/instruction_decoders/java_actions.hpp>
#include <reverse/components/input/instruction_decoders/java_opcodes.hpp>

#include <reverse/data_containers/basic_block.hpp>
#include <reverse/data_containers/control_flow_graph.hpp>
#include <reverse/data_containers/control_flow_graph_sequence.hpp>
#include <reverse/data_containers/instruction.hpp>
#include <reverse/io/input/file_readers/java_class/attribute_tags.hpp>
#include <reverse/io/input/file_readers/java_class/code_attribute.hpp>
#include <reverse/io/input/file_readers/java_class/class_header.hpp>
#include <reverse/io/input/file_readers/java_class/method_info.hpp>
#include <reverse/io/input/file_readers/java_class/reader.hpp>
#include <reverse/io/input/file_readers/reader_factory.hpp>
#include <reverse/io/file_id.hpp>
#include <reverse/preconditions.hpp>

#include <boost/format.hpp>
#include <boost/smart_ptr/make_shared.hpp>

#include <sstream>

#ifdef LIBREVERSE_DEBUG
#include <reverse/trace.hpp>
#endif /* LIBREVERSE_DEBUG */

namespace reverse {
  namespace components {
    namespace input {
      namespace instruction_decoders {

	java_decoder::java_decoder ( boost::shared_ptr < java_actions > action_ptr )
	  : m_actions ( action_ptr ),
	    m_graph_list ( new data_container::control_flow_graph_sequence() )
	{
#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Inside Java_Decoder constructor" );
#endif /* LIBREVERSE_DEBUG */
	}

	boost::shared_ptr < data_container::control_flow_graph_sequence>
	java_decoder::execute ( std::string filename )
	{
#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( trace_area::INSTRUCTION_DECODER,
			       trace_level::DETAIL,
			       "Entering Java_Decode::execute" );
#endif /* LIBREVERSE_DEBUG */

	  preconditions::is_set ( m_actions );

	  boost::shared_ptr < io::file_id > file_obj = boost::make_shared < io::file_id > ( filename );

	  io::input::file_readers::java_class::reader reader_obj ( file_obj );

	  reader_obj.read_headers();

	  boost::shared_ptr < const io::input::file_readers::java_class::class_header > class_hdr = reader_obj.get_header();

	  boost::uint32_t method_count = 0;

	  // Get list of Code sections
	  for ( io::input::file_readers::java_class::class_header::method_info_map_t::const_iterator cpos = class_hdr->get_method_begin();
		cpos != class_hdr->get_method_end();
		++cpos )
	    {
	      boost::shared_ptr < const io::input::file_readers::java_class::method_info > method_ptr = (*cpos).second;

#ifdef LIBREVERSE_DEBUG
	      trace::write_trace ( trace_area::instruction_decoder,
				   trace_level::detail,
				   boost::str ( boost::format ( "Java_Decode::execute - reading Method #%1%" )
						% method_ptr->get_name_string() ) );

	      trace::write_trace ( trace_area::instruction_decoder,
				   trace_level::detail,
				   boost::str ( boost::format ( "Java_Decode::execute - Attribute count %1%" )
						% method_ptr->get_attributes_count() ) );

#endif /* LIBREVERSE_DEBUG */

	      // FOR EACH Code section
	      for ( io::input::file_readers::java_class::class_header::attribute_info_map_t::const_iterator attrib_pos = method_ptr->attribute_begin();
		    attrib_pos != method_ptr->attribute_end();
		    ++attrib_pos )
		{

		  boost::shared_ptr < io::input::file_readers::java_class::attribute_info > attrib_ptr = (*attrib_pos).second;

#ifdef LIBREVERSE_DEBUG
		  trace::write_trace ( trace_area::instruction_decoder,
				       trace_level::detail,
				       "Entering Java_Decode::execute - reading Attribute" );

		  trace::write_trace ( trace_area::instruction_decoder,
				       trace_level::data,
				       attrib_ptr->to_string() );

#endif /* LIBREVERSE_DEBUG */

		  if ( attrib_ptr->is_type ( io::input::file_readers::java_class::attribute_tags::code ) )
		    {

		      /*---------------------------*/
		      /*         SETUP             */
		      /*---------------------------*/
		      m_todo_list.clear();
		      m_processed_list.clear();
		      m_current_graph.reset ( new data_container::control_flow_graph( method_ptr->get_name_string() ) );

		      /*---------------------------*/
		      /*         PROCESS           */
		      /*---------------------------*/
		      // Get Code_List_t from Code Section
		      boost::shared_ptr < io::input::file_readers::java_class::code_attribute > code_ptr =
			boost::dynamic_pointer_cast< io::input::file_readers::java_class::code_attribute> ( attrib_ptr );
		
		      // Parse Opcode from Code_List_t
		      this->process_code_attribute ( code_ptr, method_ptr );

		      // Save Control Flow Graph
		      m_graph_list->add_control_flow_graph ( m_current_graph );
		    }
		}

	      // Increment to next count
	      ++method_count;

	    }

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Exiting Java_Decode::execute" );
#endif /* LIBREVERSE_DEBUG */

	  return m_graph_list;
	}

	void
	java_decoder::process_code_attribute ( boost::shared_ptr < reverse::io::input::file_readers::java_class::code_attribute > code_ptr,
					       boost::shared_ptr < const reverse::io::input::file_readers::java_class::method_info > method_ptr )
	{
#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Entering Java_Decode::process_Code_Attribute" );
#endif /* LIBREVERSE_DEBUG */

	  // Create Basic Block (0)
	  boost::uint32_t id = 0;
	  boost::shared_ptr < data_container::basic_block > bb_ptr = 
	    boost::make_shared < data_container::basic_block > ( id,
								 data_container::instruction::java_assembly );

	  bb_ptr->add_comment ( boost::str ( boost::format ( "method: %1%" ) % method_ptr->get_name_string() ) );

	  // Put 0 on todo list;
	  m_todo_list.push_back ( id );

	  // Add Basic Block (0) to graph
	  m_current_graph->add_basic_block ( bb_ptr );

	  // While m_todo_list is not empty
	  while ( ! m_todo_list.empty() )
	    {
	      //   Read next entry from todo list
	      boost::uint32_t next_entry = m_todo_list.front();

	      //   Put next entry in processed list
	      basic_block_list_t::iterator result = std::find ( m_processed_list.begin(),
								m_processed_list.end(),
								next_entry );
	      if ( result == m_processed_list.end() )
		{
		  m_processed_list.push_back ( next_entry );
		}

	      //   call process_todo_list
	      this->process_todo_list ( code_ptr );
	    }

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Exiting Java_Decode::process_Code_Attribute" );
#endif /* LIBREVERSE_DEBUG */

	}

	void
	java_decoder::process_todo_list ( boost::shared_ptr < io::input::file_readers::java_class::code_attribute > code_ptr )
	{

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Enterng java_decode::process_todo_list" );

	  std::stringstream output_todo_list;
	  std::stringstream output_processed_list;
	  boost::uint32_t list_size = m_todo_list.size();
	  boost::uint32_t end_of_list_position = list_size - 1;
	  boost::uint32_t index = 0;

	  // Collect all the entries in the todo list
	  for ( java_decoder::basic_block_list_t::const_iterator cpos = m_todo_list.begin();
		cpos != m_todo_list.end();
		++cpos )
	    {
	      output_todo_list << (*cpos);

	      if ( index < end_of_list_position )
		{
		  output_todo_list << " ";
		}

	      ++index;
	    }

	  // Collect all the entries in the processed list
	  index = 0;
	  list_size = m_processed_list.size();
	  end_of_list_position = list_size - 1;
	  for ( java_decoder::basic_block_list_t::const_iterator cpos = m_processed_list.begin();
		cpos != m_processed_list.end();
		++cpos )
	    {
	      output_processed_list << (*cpos);

	      if ( index < end_of_list_position )
		{
		  output_processed_list << " ";
		}

	      ++index;
	    }

	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::data,
			       boost::str ( boost::format ("todo list: %1%" ) % output_todo_list.str() ) );
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::data,
			       boost::str ( boost::format ("processed list: %1%" ) % output_processed_list.str() ) );

#endif /* LIBREVERSE_DEBUG */


	  // Pop first entry from todo list
	  boost::uint32_t next_entry = m_todo_list.front();
	  bool continue_working = true;

	  m_todo_list.pop_front();


#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::data,
			       boost::str ( boost::format ( "Processing basic block: %1%" ) % next_entry ) );
#endif /* LIBREVERSE_DEBUG */

      
	  // Retrieve Basic Block(next_entry) from graph
	  data_container::control_flow_graph::vertex_t node = m_current_graph->get_vertex ( next_entry );
	  boost::shared_ptr < data_container::basic_block > current_bb_ptr =  m_current_graph->get_basic_block ( node );

	  // Set Current Block = Basic Block (next_entry)
	  m_actions->set_current_basic_block ( current_bb_ptr );

	  while ( continue_working )
	    {
	      // Get instruction at entry
	      boost::uint8_t instruction = code_ptr->get_code ( next_entry );

	      // Process instruction
	      switch ( instruction )
		{
		case java_opcodes::nop:
		case java_opcodes::aconst_null:
		case java_opcodes::iconst_m1:
		case java_opcodes::iconst_0:
		case java_opcodes::iconst_1:
		case java_opcodes::iconst_2:
		case java_opcodes::iconst_3:
		case java_opcodes::iconst_4:
		case java_opcodes::iconst_5:
		case java_opcodes::lconst_0:
		case java_opcodes::lconst_1:
		case java_opcodes::fconst_0:
		case java_opcodes::fconst_1:
		case java_opcodes::fconst_2:
		case java_opcodes::dconst_0:
		case java_opcodes::dconst_1:
		case java_opcodes::bipush:
		case java_opcodes::sipush:
		case java_opcodes::ldc:
		case java_opcodes::ldc_w:
		case java_opcodes::ldc2_w:
		case java_opcodes::iload:
		case java_opcodes::lload:
		case java_opcodes::fload:
		case java_opcodes::dload:
		case java_opcodes::aload:
		case java_opcodes::iload_0:
		case java_opcodes::iload_1:
		case java_opcodes::iload_2:
		case java_opcodes::iload_3:
		case java_opcodes::lload_0:
		case java_opcodes::lload_1:
		case java_opcodes::lload_2:
		case java_opcodes::lload_3:
		case java_opcodes::fload_0:
		case java_opcodes::fload_1:
		case java_opcodes::fload_2:
		case java_opcodes::fload_3:
		case java_opcodes::dload_0:
		case java_opcodes::dload_1:
		case java_opcodes::dload_2:
		case java_opcodes::dload_3:
		case java_opcodes::aload_0:
		case java_opcodes::aload_1:
		case java_opcodes::aload_2:
		case java_opcodes::aload_3:
		case java_opcodes::iaload:
		case java_opcodes::laload:
		case java_opcodes::faload:
		case java_opcodes::daload:
		case java_opcodes::aaload:
		case java_opcodes::baload:
		case java_opcodes::caload:
		case java_opcodes::saload:
		case java_opcodes::istore:
		case java_opcodes::lstore:
		case java_opcodes::fstore:
		case java_opcodes::dstore:
		case java_opcodes::astore:
		case java_opcodes::istore_0:
		case java_opcodes::istore_1:
		case java_opcodes::istore_2:
		case java_opcodes::istore_3:
		case java_opcodes::lstore_0:
		case java_opcodes::lstore_1:
		case java_opcodes::lstore_2:
		case java_opcodes::lstore_3:
		case java_opcodes::fstore_0:
		case java_opcodes::fstore_1:
		case java_opcodes::fstore_2:
		case java_opcodes::fstore_3:
		case java_opcodes::dstore_0:
		case java_opcodes::dstore_1:
		case java_opcodes::dstore_2:
		case java_opcodes::dstore_3:
		case java_opcodes::astore_0:
		case java_opcodes::astore_1:
		case java_opcodes::astore_2:
		case java_opcodes::astore_3:
		case java_opcodes::iastore:
		case java_opcodes::lastore:
		case java_opcodes::fastore:
		case java_opcodes::dastore:
		case java_opcodes::aastore:
		case java_opcodes::bastore:
		case java_opcodes::castore:
		case java_opcodes::sastore:
		case java_opcodes::pop:
		case java_opcodes::pop2:
		case java_opcodes::dup:
		case java_opcodes::dup_x1:
		case java_opcodes::dup_x2:
		case java_opcodes::dup2:
		case java_opcodes::dup2_x1:
		case java_opcodes::dup2_x2:
		case java_opcodes::swap:
		case java_opcodes::iadd:
		case java_opcodes::ladd:
		case java_opcodes::fadd:
		case java_opcodes::dadd:
		case java_opcodes::isub:
		case java_opcodes::lsub:
		case java_opcodes::fsub:
		case java_opcodes::dsub:
		case java_opcodes::imul:
		case java_opcodes::lmul:
		case java_opcodes::fmul:
		case java_opcodes::dmul:
		case java_opcodes::idiv:
		case java_opcodes::ldiv:
		case java_opcodes::fdiv:
		case java_opcodes::ddiv:  
		case java_opcodes::irem:
		case java_opcodes::lrem:
		case java_opcodes::frem:
		case java_opcodes::drem:
		case java_opcodes::ineg:
		case java_opcodes::lneg:
		case java_opcodes::fneg:
		case java_opcodes::dneg:
		case java_opcodes::ishl:
		case java_opcodes::lshl:
		case java_opcodes::ishr:
		case java_opcodes::lshr:
		case java_opcodes::iushr:
		case java_opcodes::lushr:
		case java_opcodes::iand:
		case java_opcodes::land:	  
		case java_opcodes::ior:
		case java_opcodes::lor:
		case java_opcodes::ixor:
		case java_opcodes::lxor:
		case java_opcodes::iinc:
		case java_opcodes::i2l:
		case java_opcodes::i2f:
		case java_opcodes::i2d:
		case java_opcodes::l2i:
		case java_opcodes::l2f:
		case java_opcodes::l2d:
		case java_opcodes::f2i:
		case java_opcodes::f2l:
		case java_opcodes::f2d:
		case java_opcodes::d2i:
		case java_opcodes::d2l:	  
		case java_opcodes::d2f:
		case java_opcodes::i2b:
		case java_opcodes::i2c:
		case java_opcodes::i2s:
		case java_opcodes::lcmp:
		case java_opcodes::fcmpl:
		case java_opcodes::fcmpg:
		case java_opcodes::dcmpl:
		case java_opcodes::dcmpg:
		case java_opcodes::ret:
		case java_opcodes::tableswitch:
		case java_opcodes::loopupswitch:
		case java_opcodes::getstatic:
		case java_opcodes::putstatic:
		case java_opcodes::getfield:
		case java_opcodes::putfield:
		case java_opcodes::invokevirtual:
		case java_opcodes::invokespecial:
		case java_opcodes::invokestatic:
		case java_opcodes::invokveinterface:
		case java_opcodes::opcode_new:
		case java_opcodes::newarray:
		case java_opcodes::anewarray:
		case java_opcodes::arraylength:
		case java_opcodes::athrow:
		case java_opcodes::checkcast:
		case java_opcodes::instanceof:
		case java_opcodes::monitorenter:
		case java_opcodes::monitorexit:
		case java_opcodes::wide:
		case java_opcodes::multianewarray:
		case java_opcodes::breakpoint:
		case java_opcodes::impdep1:
		case java_opcodes::impdep2:
		  {
		    process_single_opcodes ( next_entry, code_ptr );

		    // Get next instruction index
		    //++next_entry;

		    // if next instruction index is in processed list OR we are past the end of the stream
		    basic_block_list_t::iterator processed_result = std::find ( m_processed_list.begin(),
										m_processed_list.end(),
										next_entry );
		    if ( processed_result != m_processed_list.end() )
		      {
			m_current_graph->add_edge ( current_bb_ptr->get_id(), *processed_result );
			continue_working = false;
		      }
		    else if ( next_entry == code_ptr->get_code_length() )
		      {
			continue_working = false;
		      }

		    break;
		  }
		case java_opcodes::ireturn:
		case java_opcodes::lreturn:
		case java_opcodes::freturn:
		case java_opcodes::dreturn:
		case java_opcodes::areturn:
		case java_opcodes::opcode_return:
		  {
		    process_single_opcodes ( next_entry, code_ptr );
		    continue_working = false;
		    break;
		  }
		case java_opcodes::ifeq:
		case java_opcodes::ifne:
		case java_opcodes::iflt:
		case java_opcodes::ifge:
		case java_opcodes::ifgt:
		case java_opcodes::ifle:
		case java_opcodes::if_icmpeq:
		case java_opcodes::if_icmpne:
		case java_opcodes::if_icmplt:
		case java_opcodes::if_icmpge:
		case java_opcodes::if_icmpgt:
		case java_opcodes::if_icmple:
		case java_opcodes::if_acmpeq:
		case java_opcodes::if_acmpne:
		case java_opcodes::ifnull:
		case java_opcodes::ifnonnull:
		  {
		    process_double_branch_opcodes ( next_entry, code_ptr, current_bb_ptr );
		    continue_working = false;
		    break;
		  }
		case java_opcodes::opcode_goto:
		case java_opcodes::jsr:
		  {
		    process_16bit_single_branch_opcodes ( next_entry, code_ptr, current_bb_ptr );
		    continue_working = false;
		    break;
		  }

		case java_opcodes::goto_w:
		case java_opcodes::jsr_w:
		  {
		    process_32bit_single_branch_opcodes ( next_entry, code_ptr, current_bb_ptr );
		    continue_working = false;
		    break;
		  }
		case java_opcodes::xxxunusedxxx:
		default:
		  {
		    continue_working = false;
		    break;
		  }
		}
	    }

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Exiting Java_Decode::process_Todo_List" );
#endif /* LIBREVERSE_DEBUG */
	}
  
	void
	java_decoder::process_single_opcodes ( boost::uint32_t& opcode_index,
					       boost::shared_ptr < const io::input::file_readers::java_class::code_attribute > code_ptr )
	{
#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Entering Java_Decode::process_Single_Opcodes" );

	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::data,
			       boost::str ( boost::format ( "Opcode index: %1%" ) % opcode_index ) );
#endif /* LIBREVERSE_DEBUG */

	  // Get instruction at entry
	  boost::uint8_t instruction = code_ptr->get_code ( opcode_index );

	  io::input::file_readers::java_class::code_attribute::code_list_t::const_iterator read_head =
	    code_ptr->get_code_iterator ( opcode_index );

	  // Process instruction
	  switch ( instruction )
	    {
	    case java_opcodes::nop:
	      {
		m_actions->handle_nop ( opcode_index );
		break;
	      }
	    case java_opcodes::aconst_null:
	      {
		m_actions->handle_aconst_null ( opcode_index );
		break;
	      }
	    case java_opcodes::iconst_m1:
	      {
		m_actions->handle_iconst ( opcode_index, -1 );
		break;
	      }
	    case java_opcodes::iconst_0:
	      {
		m_actions->handle_iconst ( opcode_index, 0 );
		break;
	      }
	    case java_opcodes::iconst_1:
	      {
		m_actions->handle_iconst ( opcode_index, 1 );
		break;
	      }
	    case java_opcodes::iconst_2:
	      {
		m_actions->handle_iconst ( opcode_index, 2 );
		break;
	      }
	    case java_opcodes::iconst_3:
	      {
		m_actions->handle_iconst ( opcode_index, 3 );
		break;
	      }
	    case java_opcodes::iconst_4:
	      {
		m_actions->handle_iconst ( opcode_index, 4 );
		break;
	      }
	    case java_opcodes::iconst_5:
	      {
		m_actions->handle_iconst ( opcode_index, 5 );
		break;
	      }
	    case java_opcodes::lconst_0:
	      {
		m_actions->handle_lconst ( opcode_index, 0 );
		break;
	      }
	    case java_opcodes::lconst_1:
	      {
		m_actions->handle_lconst ( opcode_index, 1 );
		break;
	      }
	    case java_opcodes::fconst_0:
	      {
		m_actions->handle_fconst ( opcode_index, 0.0 );
		break;
	      }
	    case java_opcodes::fconst_1:
	      {
		m_actions->handle_fconst ( opcode_index, 1.0 );
		break;
	      }
	    case java_opcodes::fconst_2:
	      {
		m_actions->handle_fconst ( opcode_index, 2.0 );
		break;
	      }
	    case java_opcodes::dconst_0:
	      {
		m_actions->handle_dconst ( opcode_index, 0.0 );
		break;
	      }
	    case java_opcodes::dconst_1:
	      {
		m_actions->handle_dconst ( opcode_index, 1.0 );
		break;
	      }
	    case java_opcodes::bipush:
	      {
		boost::uint8_t imm_byte = this->read_8bit_value ( read_head, code_ptr->get_code_end() );
		m_actions->handle_bipush ( opcode_index, imm_byte );
		break;
	      }
	    case java_opcodes::sipush:
	      {
		boost::uint16_t value = this->read_16bit_value ( read_head, code_ptr->get_code_end() );
		m_actions->handle_sipush ( opcode_index, value );
		break;
	      }
	    case java_opcodes::ldc:
	      {
		// read index
		boost::uint8_t index = this->read_8bit_value ( read_head, code_ptr->get_code_end() );
		m_actions->handle_ldc ( opcode_index, index );
		break;
	      }
	    case java_opcodes::ldc_w:
	      {
		boost::uint16_t index = this->read_16bit_value ( read_head, code_ptr->get_code_end() );
		m_actions->handle_ldc ( opcode_index, index );
		break;
	      }
	    case java_opcodes::ldc2_w:
	      {
		boost::uint16_t index = this->read_16bit_value ( read_head, code_ptr->get_code_end() );
		m_actions->handle_ldc2_w ( opcode_index, index );
		break;
	      }
	    case java_opcodes::iload:
	      {
		// read index
		boost::uint8_t index = this->read_8bit_value ( read_head, code_ptr->get_code_end() );
		m_actions->handle_iload ( opcode_index, index );
		break;
	      }
	    case java_opcodes::lload:
	      {
		// read index
		boost::uint8_t index = this->read_8bit_value ( read_head, code_ptr->get_code_end() );
		m_actions->handle_lload ( opcode_index, index );
		break;
	      }
	    case java_opcodes::fload:
	      {
		// read index
		boost::uint8_t index = this->read_8bit_value ( read_head, code_ptr->get_code_end() );
		m_actions->handle_fload ( opcode_index, index );
		break;
	      }
	    case java_opcodes::dload:
	      {
		// read index
		boost::uint8_t index = this->read_8bit_value ( read_head, code_ptr->get_code_end() );
		m_actions->handle_dload ( opcode_index, index );
		break;
	      }
	    case java_opcodes::aload:
	      {
		// read index
		boost::uint8_t index = this->read_8bit_value ( read_head, code_ptr->get_code_end() );
		m_actions->handle_aload ( opcode_index, index );
		break;
	      }
	    case java_opcodes::iload_0:
	      {
		m_actions->handle_iload ( opcode_index, 0 );
		break;
	      }
	    case java_opcodes::iload_1:
	      {
		m_actions->handle_iload ( opcode_index, 1 );
		break;
	      }
	    case java_opcodes::iload_2:
	      {
		m_actions->handle_iload ( opcode_index, 2 );
		break;
	      }
	    case java_opcodes::iload_3:
	      {
		m_actions->handle_iload ( opcode_index, 3 );
		break;
	      }
	    case java_opcodes::lload_0:
	      {
		m_actions->handle_lload ( opcode_index, 0 );
		break;
	      }
	    case java_opcodes::lload_1:
	      {
		m_actions->handle_lload ( opcode_index, 1 );
		break;
	      }

	    case java_opcodes::lload_2:
	      {
		m_actions->handle_lload ( opcode_index, 2 );
		break;
	      }
	    case java_opcodes::lload_3:
	      {
		m_actions->handle_lload ( opcode_index, 3 );
		break;
	      }
	    case java_opcodes::fload_0:
	      {
		m_actions->handle_fload ( opcode_index, 0 );
		break;
	      }
	    case java_opcodes::fload_1:
	      {
		m_actions->handle_fload ( opcode_index, 1 );
		break;
	      }
	    case java_opcodes::fload_2:
	      {
		m_actions->handle_fload ( opcode_index, 2 );
		break;
	      }
	    case java_opcodes::fload_3:
	      {
		m_actions->handle_fload ( opcode_index, 3 );
		break;
	      }
	    case java_opcodes::dload_0:
	      {
		m_actions->handle_dload ( opcode_index, 0 );
		break;
	      }
	    case java_opcodes::dload_1:
	      {
		m_actions->handle_dload ( opcode_index, 1 );
		break;
	      }
	    case java_opcodes::dload_2:
	      {
		m_actions->handle_dload ( opcode_index, 2 );
		break;
	      }
	    case java_opcodes::dload_3:
	      {
		m_actions->handle_dload ( opcode_index, 3 );
		break;
	      }
	    case java_opcodes::aload_0:
	      {
		m_actions->handle_aload ( opcode_index, 0 );
		break;
	      }
	    case java_opcodes::aload_1:
	      {
		m_actions->handle_aload ( opcode_index, 1 );
		break;
	      }
	    case java_opcodes::aload_2:
	      {
		m_actions->handle_aload ( opcode_index, 2 );
		break;
	      }
	    case java_opcodes::aload_3:
	      {
		m_actions->handle_aload ( opcode_index, 3 );
		break;
	      }
	    case java_opcodes::iaload:
	      {
		m_actions->handle_iaload ( opcode_index );
		break;
	      }
	    case java_opcodes::laload:
	      {
		m_actions->handle_laload ( opcode_index );
		break;
	      }

	    case java_opcodes::faload:
	      {
		m_actions->handle_faload ( opcode_index );
		break;
	      }
	    case java_opcodes::daload:
	      {
		m_actions->handle_daload ( opcode_index );
		break;
	      }
	    case java_opcodes::aaload:
	      {
		m_actions->handle_aaload ( opcode_index );
		break;
	      }
	    case java_opcodes::baload:
	      {
		m_actions->handle_baload ( opcode_index );
		break;
	      }
	    case java_opcodes::caload:
	      {
		m_actions->handle_caload ( opcode_index );
		break;
	      }
	    case java_opcodes::saload:
	      {
		m_actions->handle_saload ( opcode_index );
		break;
	      }
	    case java_opcodes::istore:
	      {
		// read index
		boost::uint8_t index = this->read_8bit_value ( read_head, code_ptr->get_code_end() );
		m_actions->handle_istore ( opcode_index, index );
		break;
	      }
	    case java_opcodes::lstore:
	      {
		// read index
		boost::uint8_t index = this->read_8bit_value ( read_head, code_ptr->get_code_end() );
		m_actions->handle_lstore ( opcode_index, index );
		break;
	      }
	    case java_opcodes::fstore:
	      {
		// read index
		boost::uint8_t index = this->read_8bit_value ( read_head, code_ptr->get_code_end() );
		m_actions->handle_fstore ( opcode_index, index );
		break;
	      }
	    case java_opcodes::dstore:
	      {
		// read index
		boost::uint8_t index = this->read_8bit_value ( read_head, code_ptr->get_code_end() );
		m_actions->handle_dstore ( opcode_index, index );
		break;
	      }
	    case java_opcodes::astore:
	      {
		// read index
		boost::uint8_t index = this->read_8bit_value ( read_head, code_ptr->get_code_end() );
		m_actions->handle_astore ( opcode_index, index );
		break;
	      }
	    case java_opcodes::istore_0:
	      {
		m_actions->handle_istore ( opcode_index, 0 );
		break;
	      }
	    case java_opcodes::istore_1:
	      {
		m_actions->handle_istore ( opcode_index, 1 );
		break;
	      }
	    case java_opcodes::istore_2:
	      {
		m_actions->handle_istore ( opcode_index, 2 );
		break;
	      }
	    case java_opcodes::istore_3:
	      {
		m_actions->handle_istore ( opcode_index, 3 );
		break;
	      }
	    case java_opcodes::lstore_0:
	      {
		m_actions->handle_lstore ( opcode_index, 0 );
		break;
	      }
	    case java_opcodes::lstore_1:
	      {
		m_actions->handle_lstore ( opcode_index, 1 );
		break;
	      }
	    case java_opcodes::lstore_2:
	      {
		m_actions->handle_lstore ( opcode_index, 2 );
		break;
	      }
	    case java_opcodes::lstore_3:
	      {
		m_actions->handle_lstore ( opcode_index, 3 );
		break;
	      }
	    case java_opcodes::fstore_0:
	      {
		m_actions->handle_fstore ( opcode_index, 0 );
		break;
	      }
	    case java_opcodes::fstore_1:
	      {
		m_actions->handle_fstore ( opcode_index, 1 );
		break;
	      }
	    case java_opcodes::fstore_2:
	      {
		m_actions->handle_fstore ( opcode_index, 2 );
		break;
	      }
	    case java_opcodes::fstore_3:
	      {
		m_actions->handle_fstore ( opcode_index, 3 );
		break;
	      }
	    case java_opcodes::dstore_0:
	      {
		m_actions->handle_dstore ( opcode_index, 0 );
		break;
	      }
	    case java_opcodes::dstore_1:
	      {
		m_actions->handle_dstore ( opcode_index, 1 );
		break;
	      }
	    case java_opcodes::dstore_2:
	      {
		m_actions->handle_dstore ( opcode_index, 2 );
		break;
	      }
	    case java_opcodes::dstore_3:
	      {
		m_actions->handle_dstore ( opcode_index, 3 );
		break;
	      }
	    case java_opcodes::astore_0:
	      {
		m_actions->handle_astore ( opcode_index, 0 );
		break;
	      }
	    case java_opcodes::astore_1:
	      {
		m_actions->handle_astore ( opcode_index, 1 );
		break;
	      }
	    case java_opcodes::astore_2:
	      {
		m_actions->handle_astore ( opcode_index, 2 );
		break;
	      }
	    case java_opcodes::astore_3:
	      {
		m_actions->handle_astore ( opcode_index, 3 );
		break;
	      }
	    case java_opcodes::iastore:
	      {
		m_actions->handle_iastore ( opcode_index );
		break;
	      }
	    case java_opcodes::lastore:
	      {
		m_actions->handle_lastore ( opcode_index );
		break;
	      }
	    case java_opcodes::fastore:
	      {
		m_actions->handle_fastore ( opcode_index );
		break;
	      }
	    case java_opcodes::dastore:
	      {
		m_actions->handle_dastore ( opcode_index );
		break;
	      }
	    case java_opcodes::aastore:
	      {
		m_actions->handle_aastore ( opcode_index );
		break;
	      }
	    case java_opcodes::bastore:
	      {
		m_actions->handle_bastore ( opcode_index );
		break;
	      }
	    case java_opcodes::castore:
	      {
		m_actions->handle_castore ( opcode_index );
		break;
	      }
	    case java_opcodes::sastore:
	      {
		m_actions->handle_sastore ( opcode_index );
		break;
	      }
	    case java_opcodes::pop:
	      {
		m_actions->handle_pop ( opcode_index );
		break;
	      }
	    case java_opcodes::pop2:
	      {
		m_actions->handle_pop2 ( opcode_index );
		break;
	      }
	    case java_opcodes::dup:
	      {
		m_actions->handle_dup ( opcode_index );
		break;
	      }
	    case java_opcodes::dup_x1:
	      {
		m_actions->handle_dup_x1 ( opcode_index );
		break;
	      }
	    case java_opcodes::dup_x2:
	      {
		m_actions->handle_dup_x2 ( opcode_index );
		break;
	      }
	    case java_opcodes::dup2:
	      {
		m_actions->handle_dup2 ( opcode_index );
		break;
	      }
	    case java_opcodes::dup2_x1:
	      {
		m_actions->handle_dup2_x1 ( opcode_index );
		break;
	      }
	    case java_opcodes::dup2_x2:
	      {
		m_actions->handle_dup2_x2 ( opcode_index );
		break;
	      }
	    case java_opcodes::swap:
	      {
		m_actions->handle_swap ( opcode_index );
		break;
	      }
	    case java_opcodes::iadd:
	      {
		m_actions->handle_iadd ( opcode_index );
		break;
	      }
	    case java_opcodes::ladd:
	      {
		m_actions->handle_ladd ( opcode_index );
		break;
	      }
	    case java_opcodes::fadd:
	      {
		m_actions->handle_fadd ( opcode_index );
		break;
	      }
	    case java_opcodes::dadd:
	      {
		m_actions->handle_dadd ( opcode_index );
		break;
	      }
	    case java_opcodes::isub:
	      {
		m_actions->handle_isub ( opcode_index );
		break;
	      }
	    case java_opcodes::lsub:
	      {
		m_actions->handle_lsub ( opcode_index );
		break;
	      }
	    case java_opcodes::fsub:
	      {
		m_actions->handle_fsub ( opcode_index );
		break;
	      }
	    case java_opcodes::dsub:
	      {
		m_actions->handle_dsub ( opcode_index );
		break;
	      }
	    case java_opcodes::imul:
	      {
		m_actions->handle_imul ( opcode_index );
		break;
	      }
	    case java_opcodes::lmul:
	      {
		m_actions->handle_lmul ( opcode_index );
		break;
	      }
	    case java_opcodes::fmul:
	      {
		m_actions->handle_fmul ( opcode_index );
		break;
	      }
	    case java_opcodes::dmul:
	      {
		m_actions->handle_dmul ( opcode_index );
		break;
	      }
	    case java_opcodes::idiv:
	      {
		m_actions->handle_idiv ( opcode_index );
		break;
	      }
	    case java_opcodes::ldiv:
	      {
		m_actions->handle_ldiv ( opcode_index );
		break;
	      }
	    case java_opcodes::fdiv:
	      {
		m_actions->handle_fdiv ( opcode_index );
		break;
	      }
	    case java_opcodes::ddiv:
	      {
		m_actions->handle_ddiv ( opcode_index );
		break;
	      }

	    case java_opcodes::irem:
	      {
		m_actions->handle_irem ( opcode_index );
		break;
	      }
	    case java_opcodes::lrem:
	      {
		m_actions->handle_lrem ( opcode_index );
		break;
	      }
	    case java_opcodes::frem:
	      {
		m_actions->handle_frem ( opcode_index );
		break;
	      }
	    case java_opcodes::drem:
	      {
		m_actions->handle_drem ( opcode_index );
		break;
	      }
	    case java_opcodes::ineg:
	      {
		m_actions->handle_ineg ( opcode_index );
		break;
	      }
	    case java_opcodes::lneg:
	      {
		m_actions->handle_lneg ( opcode_index );
		break;
	      }
	    case java_opcodes::fneg:
	      {
		m_actions->handle_fneg ( opcode_index );
		break;
	      }
	    case java_opcodes::dneg:
	      {
		m_actions->handle_dneg ( opcode_index );
		break;
	      }
	    case java_opcodes::ishl:
	      {
		m_actions->handle_ishl ( opcode_index );
		break;
	      }
	    case java_opcodes::lshl:
	      {
		m_actions->handle_lshl ( opcode_index );
		break;
	      }
	    case java_opcodes::ishr:
	      {
		m_actions->handle_ishr ( opcode_index );
		break;
	      }
	    case java_opcodes::lshr:
	      {
		m_actions->handle_lshr ( opcode_index );
		break;
	      }
	    case java_opcodes::iushr:
	      {
		m_actions->handle_iushr ( opcode_index );
		break;
	      }
	    case java_opcodes::lushr:
	      {
		m_actions->handle_lushr ( opcode_index );
		break;
	      }
	    case java_opcodes::iand:
	      {
		m_actions->handle_iand ( opcode_index );
		break;
	      }
	    case java_opcodes::land:
	      {
		m_actions->handle_land ( opcode_index );
		break;
	      }
	    case java_opcodes::ior:
	      {
		m_actions->handle_ior ( opcode_index );
		break;
	      }
	    case java_opcodes::lor:
	      {
		m_actions->handle_lor ( opcode_index );
		break;
	      }
	    case java_opcodes::ixor:
	      {
		m_actions->handle_ixor ( opcode_index );
		break;
	      }
	    case java_opcodes::lxor:
	      {
		m_actions->handle_lxor ( opcode_index );
		break;
	      }
	    case java_opcodes::iinc:
	      {
		// index unsigned byte
		boost::uint8_t index = this->read_8bit_value ( read_head, code_ptr->get_code_end() );

		// signed byte
		boost::int8_t const_value = this->read_8bit_value ( read_head, code_ptr->get_code_end() );

		m_actions->handle_iinc ( opcode_index, index, const_value );
		break;
	      }
	    case java_opcodes::i2l:
	      {
		m_actions->handle_i2l ( opcode_index );
		break;
	      }
	    case java_opcodes::i2f:
	      {
		m_actions->handle_i2f ( opcode_index );
		break;
	      }
	    case java_opcodes::i2d:
	      {
		m_actions->handle_i2d ( opcode_index );
		break;
	      }
	    case java_opcodes::l2i:
	      {
		m_actions->handle_l2i ( opcode_index );
		break;
	      }
	    case java_opcodes::l2f:
	      {
		m_actions->handle_l2f ( opcode_index );
		break;
	      }
	    case java_opcodes::l2d:
	      {
		m_actions->handle_l2d ( opcode_index );
		break;
	      }
	    case java_opcodes::f2i:
	      {
		m_actions->handle_f2i ( opcode_index );
		break;
	      }
	    case java_opcodes::f2l:
	      {
		m_actions->handle_f2l ( opcode_index );
		break;
	      }
	    case java_opcodes::f2d:
	      {
		m_actions->handle_f2d ( opcode_index );
		break;
	      }
	    case java_opcodes::d2i:
	      {
		m_actions->handle_d2i ( opcode_index );
		break;
	      }
	    case java_opcodes::d2l:
	      {
		m_actions->handle_d2l ( opcode_index );
		break;
	      }
	    case java_opcodes::d2f:
	      {
		m_actions->handle_d2f ( opcode_index );
		break;
	      }
	    case java_opcodes::i2b:
	      {
		m_actions->handle_i2b ( opcode_index );
		break;
	      }
	    case java_opcodes::i2c:
	      {
		m_actions->handle_i2c ( opcode_index );
		break;
	      }
	    case java_opcodes::i2s:
	      {
		m_actions->handle_i2s ( opcode_index );
		break;
	      }
	    case java_opcodes::lcmp:
	      {
		m_actions->handle_lcmp ( opcode_index );
		break;
	      }
	    case java_opcodes::fcmpl:
	      {
		m_actions->handle_fcmpl ( opcode_index );
		break;
	      }
	    case java_opcodes::fcmpg:
	      {
		m_actions->handle_fcmpg ( opcode_index );
		break;
	      }
	    case java_opcodes::dcmpl:
	      {
		m_actions->handle_dcmpl ( opcode_index );
		break;
	      }
	    case java_opcodes::dcmpg:
	      {
		m_actions->handle_dcmpg ( opcode_index );
		break;
	      }
	    case java_opcodes::ret:
	      {
		boost::uint8_t index = this->read_8bit_value ( read_head, code_ptr->get_code_end() );

		m_actions->handle_ret ( opcode_index, index );
		break;
	      }
	    case java_opcodes::tableswitch:
	      {
		while ( ( read_head - code_ptr->get_code_begin() ) % 4 != 0 )
		  {
		    // skip padding bytes
		    ++read_head;
		  }

		boost::uint32_t default_value = this->read_32bit_value ( read_head, code_ptr->get_code_end() );

		boost::uint32_t low = this->read_32bit_value ( read_head, code_ptr->get_code_end() );

		boost::uint32_t high = this->read_32bit_value ( read_head, code_ptr->get_code_end() );

		boost::uint32_t offset_count = high - low + 1;

		std::vector<boost::uint32_t> offsets;

		for ( boost::uint32_t i = 0; i < offset_count; ++i )
		  {
		    boost::uint32_t offset_value = this->read_32bit_value ( read_head, code_ptr->get_code_end() );

		    offsets.push_back ( offset_value );
		  }

		m_actions->handle_tableswitch ( opcode_index, default_value, low, high, offsets );
		break;
	      }
	    case java_opcodes::loopupswitch:
	      {
		while ( ( read_head - code_ptr->get_code_begin() ) % 4 != 0 )
		  {
		    // skip padding bytes
		    ++read_head;
		  }

		boost::uint32_t default_value = this->read_32bit_value ( read_head, code_ptr->get_code_end() );

		boost::uint32_t npairs = this->read_32bit_value ( read_head, code_ptr->get_code_end() );

		std::vector< std::pair<boost::uint32_t, boost::uint32_t> > npair_list;

		for ( boost::uint32_t i = 0; i < npairs; ++i )
		  {
		    boost::uint32_t match = this->read_32bit_value ( read_head, code_ptr->get_code_end() );
		    boost::uint32_t offset = this->read_32bit_value ( read_head, code_ptr->get_code_end() );

		    npair_list.push_back ( std::make_pair ( match, offset ) );
		  }

		m_actions->handle_lookupswitch ( opcode_index, default_value, npair_list );
		break;
	      }
	    case java_opcodes::ireturn:
	      {
		m_actions->handle_ireturn ( opcode_index );
		break;
	      }
	    case java_opcodes::lreturn:
	      {
		m_actions->handle_lreturn ( opcode_index );
		break;
	      }
	    case java_opcodes::freturn:
	      {
		m_actions->handle_freturn ( opcode_index );
		break;
	      }
	    case java_opcodes::dreturn:
	      {
		m_actions->handle_dreturn ( opcode_index );
		break;
	      }

	    case java_opcodes::areturn:
	      {
		m_actions->handle_areturn ( opcode_index );
		break;
	      }
	    case java_opcodes::opcode_return:
	      {
		m_actions->handle_return ( opcode_index );
		break;
	      }
	    case java_opcodes::getstatic:
	      {
		boost::uint16_t index = this->read_16bit_value ( read_head, code_ptr->get_code_end() );

		m_actions->handle_getstatic ( opcode_index, index );

		break;
	      }
	    case java_opcodes::putstatic:
	      {
		boost::uint16_t index = this->read_16bit_value ( read_head, code_ptr->get_code_end() );

		m_actions->handle_putstatic ( opcode_index, index );

		break;
	      }
	    case java_opcodes::getfield:
	      {
		boost::uint16_t index = this->read_16bit_value ( read_head, code_ptr->get_code_end() );

		m_actions->handle_getfield ( opcode_index, index );

		break;
	      }
	    case java_opcodes::putfield:
	      {
		boost::uint16_t index = this->read_16bit_value ( read_head, code_ptr->get_code_end() );

		m_actions->handle_putfield ( opcode_index, index );

		break;
	      }
	    case java_opcodes::invokevirtual:
	      {
		boost::uint16_t index = this->read_16bit_value ( read_head, code_ptr->get_code_end() );

		m_actions->handle_invokevirtual ( opcode_index, index );

		break;
	      }
	    case java_opcodes::invokespecial:
	      {
		boost::uint16_t index = this->read_16bit_value ( read_head, code_ptr->get_code_end() );

		m_actions->handle_invokespecial ( opcode_index, index );

		break;
	      }
	    case java_opcodes::invokestatic:
	      {
		boost::uint16_t index = this->read_16bit_value ( read_head, code_ptr->get_code_end() );

		m_actions->handle_invokestatic ( opcode_index, index );

		break;
	      }
	    case java_opcodes::invokveinterface:
	      {
		boost::uint16_t index = this->read_16bit_value ( read_head, code_ptr->get_code_end() );

		boost::uint8_t count = this->read_8bit_value ( read_head, code_ptr->get_code_end() );

		// skipping the next byte. should always be zero.
		this->read_8bit_value ( read_head, code_ptr->get_code_end() );

		m_actions->handle_invokveinterface ( opcode_index, index, count );

		break;
	      }
	    case java_opcodes::opcode_new:
	      {
		boost::uint16_t index = this->read_16bit_value ( read_head, code_ptr->get_code_end() );

		m_actions->handle_new ( opcode_index, index );

		break;
	      }
	    case java_opcodes::newarray:
	      {
		boost::uint8_t atype = this->read_8bit_value ( read_head, code_ptr->get_code_end() );

		m_actions->handle_newarray ( opcode_index, atype );

		break;
	      }
	    case java_opcodes::anewarray:
	      {
		boost::uint16_t index = this->read_16bit_value ( read_head, code_ptr->get_code_end() );

		m_actions->handle_anewarray ( opcode_index, index );

		break;
	      }
	    case java_opcodes::arraylength:
	      {
		m_actions->handle_arraylength ( opcode_index );

		break;
	      }
	    case java_opcodes::athrow:
	      {
		m_actions->handle_athrow ( opcode_index );
		break;
	      }

	    case java_opcodes::checkcast:
	      {
		boost::uint16_t index = this->read_16bit_value ( read_head, code_ptr->get_code_end() );

		m_actions->handle_checkcast ( opcode_index, index );

		break;
	      }
	    case java_opcodes::instanceof:
	      {
		boost::uint16_t index = this->read_16bit_value ( read_head, code_ptr->get_code_end() );

		m_actions->handle_instanceof ( opcode_index, index );

		break;
	      }
	    case java_opcodes::monitorenter:
	      {
		m_actions->handle_monitorenter ( opcode_index );

		break;
	      }
	    case java_opcodes::monitorexit:
	      {
		m_actions->handle_monitorexit ( opcode_index );

		break;
	      }
	    case java_opcodes::wide:
	      {
		boost::uint8_t opcode = this->read_8bit_value ( read_head, code_ptr->get_code_end() );

		switch ( opcode )
		  {
		  case java_opcodes::iload:
		  case java_opcodes::fload:
		  case java_opcodes::aload:
		  case java_opcodes::lload:
		  case java_opcodes::dload:
		  case java_opcodes::istore:
		  case java_opcodes::fstore:
		  case java_opcodes::astore:
		  case java_opcodes::lstore:
		  case java_opcodes::dstore:
		  case java_opcodes::opcode_return:
		    {
		      boost::uint16_t index = this->read_16bit_value ( read_head, code_ptr->get_code_end() );

		      m_actions->handle_wide ( opcode_index, opcode, index );
		    }
		  case java_opcodes::iinc:
		    {
		      boost::uint16_t index = this->read_16bit_value ( read_head, code_ptr->get_code_end() );

		      boost::uint16_t const_byte = this->read_16bit_value ( read_head, code_ptr->get_code_end() );

		      m_actions->handle_wide_iinc ( opcode_index, index, const_byte );
		    }
		  default:
		    {
		      // error
		    }
		  }

		break;
	      }
	    case java_opcodes::multianewarray:
	      {
		boost::uint16_t index = this->read_16bit_value ( read_head, code_ptr->get_code_end() );
	      
		boost::uint8_t dimensions = this->read_8bit_value ( read_head, code_ptr->get_code_end() );

		m_actions->handle_multianewarray ( opcode_index, index, dimensions );

		break;
	      }
	    case java_opcodes::breakpoint:
	      {
		m_actions->handle_breakpoint ( opcode_index );
		break;
	      }

	    case java_opcodes::impdep1:
	      {
		m_actions->handle_impdep1 ( opcode_index );
		break;
	      }
	    case java_opcodes::impdep2:
	      {
		m_actions->handle_impdep2 ( opcode_index );
		break;
	      }
	    case java_opcodes::xxxunusedxxx:
	    default:
	      break;
	    }

	  // set the opcode_index to address of the next instruction
	  opcode_index = ( read_head - code_ptr->get_code_begin() + 1);

#ifdef libreverse_debug
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "exiting java_decode::parse_single_opcodes" );
#endif /* libreverse_debug */
	}

	void
	java_decoder::process_16bit_single_branch_opcodes ( boost::uint32_t& opcode_index,
							    boost::shared_ptr < const io::input::file_readers::java_class::code_attribute > code_ptr,
							    boost::shared_ptr < const data_container::basic_block > current_bb_ptr )
	{

#ifdef libreverse_debug
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "entering java_decode::parse_16bit_single_branch_opcodes" );

	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::data,
			       boost::str ( boost::format ( "opcode index: %1%" ) % opcode_index ) );
#endif /* libreverse_debug */


	  boost::uint8_t instruction = code_ptr->get_code ( opcode_index );

	  io::input::file_readers::java_class::code_attribute::code_list_t::const_iterator read_head =
	    code_ptr->get_code_iterator ( opcode_index );

	  // calculate true index
	  boost::int16_t dest_index = this->read_16bit_value ( read_head, code_ptr->get_code_end() )
	    + opcode_index;

#ifdef libreverse_debug
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::data,
			       boost::str ( boost::format ( "dest index: %1%" ) % dest_index ) );
#endif /* libreverse_debug */
    
	  // if true index is not in processed and todo list then add true index to todo list
	  basic_block_list_t::iterator processed_result = std::find ( m_processed_list.begin(),
								      m_processed_list.end(),
								      dest_index );
	  basic_block_list_t::iterator todo_result = std::find ( m_todo_list.begin(),
								 m_todo_list.end(),
								 dest_index );

	  if ( ( processed_result == m_processed_list.end() ) &&
	       ( todo_result == m_todo_list.end() ) )
	    {
	      // add dest index to todo list
	      m_todo_list.push_back ( dest_index );

	      // add basic block (true index) to graph
	      boost::shared_ptr < data_container::basic_block > dest_bb_ptr =
		boost::make_shared < data_container::basic_block > ( dest_index,
								     data_container::instruction::java_assembly );


#ifdef libreverse_debug
	      trace::write_trace ( trace_area::instruction_decoder,
				   trace_level::data,
				   "cfg before add" );

	      trace::write_trace ( trace_area::instruction_decoder,
				   trace_level::data,
				   boost::str ( boost::format ( "%1%" ) % m_current_graph->to_string() ) );

#endif /* libreverse_debug */


	      m_current_graph->add_basic_block ( dest_bb_ptr );


#ifdef libreverse_debug
	      trace::write_trace ( trace_area::instruction_decoder,
				   trace_level::data,
				   "cfg after add" );

	      trace::write_trace ( trace_area::instruction_decoder,
				   trace_level::data,
				   boost::str ( boost::format ( "%1%" ) % m_current_graph->to_string() ) );

#endif /* libreverse_debug */

	    }

	  //     add edge from basic block(entry) -> basic block(true index)
	  m_current_graph->add_edge ( current_bb_ptr->get_id(), dest_index );

	  switch ( instruction )
	    {
	    case java_opcodes::opcode_goto:
	      {
		m_actions->handle_goto ( opcode_index, dest_index );
		break;
	      }
	    case java_opcodes::jsr:
	      {
		m_actions->handle_jsr ( opcode_index, dest_index );
		break;
	      }
	    }

	  opcode_index = read_head - code_ptr->get_code_begin() + 1;

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Exiting Java_Decode::parse_16Bit_Single_Branch_Opcodes" );
#endif /* LIBREVERSE_DEBUG */

	}

	void
	java_decoder::process_32bit_single_branch_opcodes ( boost::uint32_t& opcode_index,
							    boost::shared_ptr < const reverse::io::input::file_readers::java_class::code_attribute > code_ptr,
							    boost::shared_ptr < const reverse::data_container::basic_block > current_bb_ptr )
	{
#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Entering Java_Decode::parse_32Bit_Single_Branch_Opcodes" );

	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::data,
			       boost::str ( boost::format ( "Opcode index: %1%" ) % opcode_index ) );
#endif /* LIBREVERSE_DEBUG */

	  boost::uint8_t instruction = code_ptr->get_code ( opcode_index );

	  io::input::file_readers::java_class::code_attribute::code_list_t::const_iterator read_head =
	    code_ptr->get_code_iterator ( opcode_index );

	  // calculate dest index
	  boost::int32_t dest_index = this->read_32bit_value ( read_head, code_ptr->get_code_end() ) + opcode_index;
    
#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::data,
			       boost::str ( boost::format ( "Dest index: %1%" ) % dest_index ) );
#endif /* LIBREVERSE_DEBUG */

	  // If true index is not in processed and todo list then add true index to todo list
	  basic_block_list_t::iterator processed_result = std::find ( m_processed_list.begin(),
								      m_processed_list.end(),
								      dest_index );
	  basic_block_list_t::iterator todo_result = std::find ( m_todo_list.begin(),
								 m_todo_list.end(),
								 dest_index );

	  if ( ( processed_result == m_processed_list.end() ) &&
	       ( todo_result == m_todo_list.end() ) )
	    {
	      // Add dest index to todo list
	      m_todo_list.push_back ( dest_index );

	      // Add Basic Block (true index) to graph
	      boost::shared_ptr < data_container::basic_block> dest_bb_ptr =
		boost::make_shared < data_container::basic_block > ( dest_index,
								     data_container::instruction::java_assembly );
	      m_current_graph->add_basic_block ( dest_bb_ptr );

	    }

	  //     Add edge from Basic Block(entry) -> Basic Block(true index)
	  m_current_graph->add_edge ( current_bb_ptr->get_id(), dest_index );

	  switch (instruction)
	    {
	    case java_opcodes::goto_w:
	      {
		m_actions->handle_goto_w ( opcode_index, dest_index );
		break;
	      }
	    case java_opcodes::jsr_w:
	      {
		m_actions->handle_jsr_w ( opcode_index, dest_index );
		break;
	      }
	    }

	  opcode_index = read_head - code_ptr->get_code_begin() + 1;

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Exiting Java_Decode::parse_32Bit_Single_Branch_Opcodes" );
#endif /* LIBREVERSE_DEBUG */
	}

	void
	java_decoder::process_double_branch_opcodes ( boost::uint32_t& opcode_index,
						      boost::shared_ptr < const reverse::io::input::file_readers::java_class::code_attribute > code_ptr,
						      boost::shared_ptr < const reverse::data_container::basic_block > current_bb_ptr )
	{
#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Entering Java_Decode::parse_Double_Branch_Opcodes" );

	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::data,
			       boost::str ( boost::format ( "Opcode index: %1%" ) % opcode_index ) );
#endif /* LIBREVERSE_DEBUG */

	  boost::uint8_t instruction = code_ptr->get_code ( opcode_index );
	  
	  io::input::file_readers::java_class::code_attribute::code_list_t::const_iterator read_head = code_ptr->get_code_iterator ( opcode_index );

	  // Calculate true index
	  boost::uint16_t true_index = this->read_16bit_value ( read_head, code_ptr->get_code_end() )
	    + opcode_index;

	  // Calculate false index. This just happens to be the present location of the read head plus one
	  boost::uint16_t false_index = ( read_head - code_ptr->get_code_begin() + 1);

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::data,
			       boost::str ( boost::format ( "True index: %1%" ) % true_index ) );

	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::data,
			       boost::str ( boost::format ( "False index: %1%" ) % false_index ) );
#endif /* LIBREVERSE_DEBUG */
    
	  // If true index is not in processed and todo list then add true index to todo list
	  basic_block_list_t::iterator processed_result = std::find ( m_processed_list.begin(),
								      m_processed_list.end(),
								      true_index );
	  basic_block_list_t::iterator todo_result = std::find ( m_todo_list.begin(),
								 m_todo_list.end(),
								 true_index );

	  if ( ( processed_result == m_processed_list.end() ) &&
	       ( todo_result == m_todo_list.end() ) )
	    {
	      // Add true index to todo list
	      m_todo_list.push_back ( true_index );

	      // Add Basic Block (true index) to graph
	      boost::shared_ptr < data_container::basic_block > true_bb_ptr =
		boost::make_shared < data_container::basic_block > ( true_index,
								     data_container::instruction::java_assembly );
	      m_current_graph->add_basic_block ( true_bb_ptr );

	    }

	  // Id of the current basic bock

	  //     Add edge from Basic Block(entry) -> Basic Block(true index)
	  m_current_graph->add_edge ( current_bb_ptr->get_id(), true_index );

	  // If false index is not in processed and todo list then add false index to todo list
	  processed_result = std::find ( m_processed_list.begin(),
					 m_processed_list.end(),
					 false_index );
	  todo_result = std::find ( m_todo_list.begin(),
				    m_todo_list.end(),
				    false_index );

	  if ( ( processed_result == m_processed_list.end() ) &&
	       ( todo_result == m_todo_list.end() ) )
	    {
	      // Add false index to todo list
	      m_todo_list.push_back ( false_index );

	      // Add Basic Block (false index) to graph
	      boost::shared_ptr < data_container::basic_block > false_bb_ptr =
		boost::make_shared < data_container::basic_block > ( false_index,
								     data_container::instruction::java_assembly );
	      m_current_graph->add_basic_block ( false_bb_ptr );

	    }

	  // Add edge from Basic Block(entry) -> Basic Block(false index)
	  m_current_graph->add_edge ( current_bb_ptr->get_id(), false_index );

	  //     break;
	  switch ( instruction )
	    {
	    case java_opcodes::ifeq:
	      {
		m_actions->handle_ifeq ( opcode_index, true_index );
		break;
	      }
	    case java_opcodes::ifne:
	      {
		m_actions->handle_ifne ( opcode_index, true_index );
		break;
	      }
	    case java_opcodes::iflt:
	      {
		m_actions->handle_iflt ( opcode_index, true_index );
		break;
	      }
	    case java_opcodes::ifge:
	      {
		m_actions->handle_ifge ( opcode_index, true_index );
		break;
	      }
	    case java_opcodes::ifgt:
	      {
		m_actions->handle_ifgt ( opcode_index, true_index );
		break;
	      }
	    case java_opcodes::ifle:
	      {
		m_actions->handle_ifle ( opcode_index, true_index );
		break;
	      }
	    case java_opcodes::if_icmpeq:
	      {
		m_actions->handle_if_icmpeq ( opcode_index, true_index );
		break;
	      }
	    case java_opcodes::if_icmpne:
	      {
		m_actions->handle_if_icmpne ( opcode_index, true_index );
		break;
	      }
	    case java_opcodes::if_icmplt:
	      {
		m_actions->handle_if_icmplt ( opcode_index, true_index );
		break;
	      }
	    case java_opcodes::if_icmpge:
	      {
		m_actions->handle_if_icmpge ( opcode_index, true_index );
		break;
	      }
	    case java_opcodes::if_icmpgt:
	      {
		m_actions->handle_if_icmpgt ( opcode_index, true_index );
		break;
	      }
	    case java_opcodes::if_icmple:
	      {
		m_actions->handle_if_icmple ( opcode_index, true_index );
		break;
	      }
	    case java_opcodes::if_acmpeq:
	      {
		m_actions->handle_if_acmpeq ( opcode_index, true_index );
		break;
	      }
	    case java_opcodes::if_acmpne:
	      {
		m_actions->handle_if_acmpne ( opcode_index, true_index );
		break;
	      }
	    case java_opcodes::ifnull:
	      {
		m_actions->handle_ifnull ( opcode_index, true_index );
		break;
	      }
	    case java_opcodes::ifnonnull:
	      {
		m_actions->handle_ifnonnull ( opcode_index, true_index );
		break;
	      }
	    }

	  // The next instruction after an 'if' statement is the beginning
	  // of its false segment
	  opcode_index = false_index;

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Exiting Java_Decode::parse_Double_Branch_Opcodes" );
#endif /* LIBREVERSE_DEBUG */

	}

	boost::uint8_t
	java_decoder::read_8bit_value ( io::input::file_readers::java_class::code_attribute::code_list_t::const_iterator read_head,
					io::input::file_readers::java_class::code_attribute::code_list_t::const_iterator end )
	{
#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Entering Java_Decode::read_8bit_Value" );
#endif /* LIBREVERSE_DEBUG */

	  boost::uint8_t byte = 0;

	  if ( read_head != end )
	    {
	      // Read next two immediate bytes
	      ++read_head;
	    }

	  if ( read_head != end )
	    {
	      byte = (*read_head);
	    }

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Exiting Java_Decode::read_8bit_Value" );
#endif /* LIBREVERSE_DEBUG */

	  return byte;
	}
  
	boost::uint16_t
	java_decoder::read_16bit_value ( io::input::file_readers::java_class::code_attribute::code_list_t::const_iterator read_head,
					 io::input::file_readers::java_class::code_attribute::code_list_t::const_iterator end )
	{
#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Entering Java_Decode::read_16bit_Value" );
#endif /* LIBREVERSE_DEBUG */

	  boost::uint8_t imm_byte1 = this->read_8bit_value ( read_head, end );
	  boost::uint8_t imm_byte2 = this->read_8bit_value ( read_head, end );

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::data,
			       boost::str ( boost::format ( "Exiting Java_Decode::read_16bit_Value - imm_byte1 = %1$X" )
					    % static_cast<boost::uint16_t>(imm_byte1) ) );

	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::data,
			       boost::str ( boost::format ( "Exiting Java_Decode::read_16bit_Value - imm_byte1 << 8 = %1$X" )
					    % static_cast<boost::uint16_t>(imm_byte1 << 8) ) );

	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::data,
			       boost::str ( boost::format ( "Exiting Java_Decode::read_16bit_Value - imm_byte2 = %1$X" )
					    % static_cast<boost::uint16_t>(imm_byte2) ) );
#endif /* LIBREVERSE_DEBUG */


	  boost::uint16_t result = ( imm_byte1 << 8 ) | imm_byte2;

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Exiting Java_Decode::read_16bit_Value" );
#endif /* LIBREVERSE_DEBUG */

	  return result;
	}

	boost::uint32_t
	java_decoder::read_32bit_value ( io::input::file_readers::java_class::code_attribute::code_list_t::const_iterator read_head,
					 io::input::file_readers::java_class::code_attribute::code_list_t::const_iterator end )
	{
#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Entering Java_Decode::read_32bit_Value" );
#endif /* LIBREVERSE_DEBUG */

	  boost::uint8_t imm_byte1 = this->read_8bit_value ( read_head, end );
	  boost::uint8_t imm_byte2 = this->read_8bit_value ( read_head, end );
	  boost::uint8_t imm_byte3 = this->read_8bit_value ( read_head, end );
	  boost::uint8_t imm_byte4 = this->read_8bit_value ( read_head, end );

	  boost::uint32_t result = ( imm_byte1 << 24 ) | ( imm_byte2 << 16 ) | ( imm_byte3 << 8 ) | imm_byte4;

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Exiting Java_Decode::read_32bit_Value" );
#endif /* LIBREVERSE_DEBUG */

	  return result;
	}

      } // namespace instruction_decoders
    } // namespace input
  } // namespace components
} // namespace reverse

  
  
  
