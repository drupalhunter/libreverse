/*  Java_Assembly_Actions.cpp

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

#include <reverse/components/input/instruction_decoders/java_assembly_actions.hpp>
#include <reverse/components/input/instruction_decoders/java_opcodes.hpp>
#include <reverse/preconditions.hpp>
#include <reverse/data_containers/control_flow_graph.hpp>
#include <reverse/data_containers/java_assembly_instruction.hpp>

#include <boost/format.hpp>
#include <boost/smart_ptr/make_shared.hpp>

#include <sstream>

#ifdef LIBREVERSE_DEBUG
#include <reverse/Trace.h>
using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse {
  namespace components {
    namespace input {
      namespace instruction_decoders {


	java_assembly_actions::java_assembly_actions ()
	{
#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Inside Java_Assembly_Actions constructor" );
#endif /* LIBREVERSE_DEBUG */
	}

	void
	java_assembly_actions::set_current_basic_block ( boost::shared_ptr < data_container::basic_block> bb_ptr )
	{
#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Entering Java_Assembly_Actions::set_Current_Basic_Block" );
#endif /* LIBREVERSE_DEBUG */

	  preconditions::is_set ( bb_ptr );

	  m_current_block = bb_ptr;

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Exiting Java_Assembly_Actions::set_Current_Basic_Block" );
#endif /* LIBREVERSE_DEBUG */
	}

	void
	java_assembly_actions::handle_nop ( boost::uint32_t opcode_index )
	{
#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Entering Java_Assembly_Actions::handle_NOP" );
#endif /* LIBREVERSE_DEBUG */

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared<data_container::java_assembly_instruction> ( opcode_index, "nop" );

	  m_current_block->add_line ( temp_ptr );

#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Exting Java_Assembly_Actions::handle_NOP" );
#endif /* LIBREVERSE_DEBUG */
	}

	void
	java_assembly_actions::handle_aconst_null ( boost::uint32_t opcode_index )
	{
#ifdef LIBREVERSE_DEBUG
	  trace::write_trace ( trace_area::instruction_decoder,
			       trace_level::detail,
			       "Entering Java_Assembly_Actions::handle_ACONST_NULL" );
#endif /* LIBREVERSE_DEBUG */

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared <data_container::java_assembly_instruction> ( opcode_index, "aconst_null" );

	  m_current_block->add_line ( temp_ptr );

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( trace_area::INSTRUCTION_DECODER,
			       trace_level::DETAIL,
			       "Exiting Java_Assembly_Actions::handle_ACONST_NULL" );
#endif /* LIBREVERSE_DEBUG */

	}

	void
	java_assembly_actions::handle_iconst ( boost::uint32_t opcode_index, boost::int32_t constant )
	{

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr;

	  switch ( constant )
	    {
	    case -1:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "iconst_m1" );
	      break;
	    case 0:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "iconst_0" );
	      break;
	    case 1:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "iconst_1" );
	      break;
	    case 2:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "iconst_2" );
	      break;
	    case 3:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "iconst_3" );
	      break;
	    case 4:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "iconst_4" );
	      break;
	    case 5:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "iconst_5" );
	      break;
	    }

	  m_current_block->add_line ( temp_ptr );
	}	      
	      
	void
	java_assembly_actions::handle_lconst ( boost::uint32_t opcode_index, boost::int64_t constant  )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr;

	  switch ( constant )
	    {
	    case 0:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lconst_0" );
	      break;
	    case 1:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lconst_1" );
	      break;
	    }

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_fconst ( boost::uint32_t opcode_index, float constant )
	{

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr;

	  if ( constant == 0.0 )
	    {
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "fconst_0" );
	    }
	  else if ( constant == 1.0 )
	    {
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "fconst_1" );
	    }
	  else if ( constant == 2.0 )
	    {
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "fconst_2" );
	    }

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_dconst ( boost::uint32_t opcode_index, double constant )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr;

	  if ( constant == 0.0)
	    {
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dconst_0" );
	    }
	  else if ( constant == 1.0 )
	    {
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dconst_1" );
	    }

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_bipush ( boost::uint32_t opcode_index, boost::uint16_t imm_byte )
	{
	  std::string line = boost::str ( boost::format ( "bipush %1%" ) % imm_byte );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_sipush ( boost::uint32_t opcode_index, boost::uint16_t value )
	{
	  std::string line = boost::str ( boost::format ( "sipush %1%" ) % value );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}
  
	void
	java_assembly_actions::handle_ldc ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "ldc #%1%" ) % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_ldc2_w ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "ldc2_w #%1%" ) % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_iload ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr;

	  switch ( index )
	    {
	    case 0:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "iload_0" );
	      break;
	    case 1:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "iload_1" );
	      break;
	    case 2:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "iload_2" );
	      break;
	    case 3:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "iload_3" );
	      break;
	    default:
	      std::string line = boost::str ( boost::format ( "iload #%1%" ) % index );
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	    }
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_lload ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr;

	  switch ( index )
	    {
	    case 0:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lload_0" );
	      break;
	    case 1:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lload_1" );
	      break;
	    case 2:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lload_2" );
	      break;
	    case 3:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lload_3" );
	      break;
	    default:
	      std::string line = boost::str ( boost::format ( "lload #%1%" ) % index );
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	    }
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_fload ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr;

	  switch ( index )
	    {
	    case 0:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "fload_0" );
	      break;
	    case 1:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "fload_1" );
	      break;
	    case 2:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "fload_2" );
	      break;
	    case 3:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "fload_3" );
	      break;
	    default:
	      std::string line = boost::str ( boost::format ( "fload #%1%" ) % index );
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	    }

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_dload ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr;

	  switch ( index )
	    {
	    case 0:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dload_0" );
	      break;
	    case 1:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dload_1" );
	      break;
	    case 2:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dload_2" );
	      break;
	    case 3:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dload_3" );
	      break;
	    default:
	      std::string line = boost::str ( boost::format ( "dload #%1%" ) % index );
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	    }

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_aload ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr;

	  switch ( index )
	    {
	    case 0:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "aload_0" );
	      break;
	    case 1:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "aload_1" );
	      break;
	    case 2:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "aload_2" );
	      break;
	    case 3:
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "aload_3" );
	      break;
	    default:
	      std::string line = boost::str ( boost::format ( "aload #%1%" ) % index );
	      temp_ptr = boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	    }

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_iaload ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr = 
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "iaload" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_laload ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "laload" );
	  m_current_block->add_line ( temp_ptr );
	}
		    
	void
	java_assembly_actions::handle_faload ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "faload" );
	  m_current_block->add_line ( temp_ptr );
	}
  
	void
	java_assembly_actions::handle_daload ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "daload" );
	  m_current_block->add_line ( temp_ptr );
	}
    
	void
	java_assembly_actions::handle_aaload ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "aaload" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_baload ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "baload" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_caload ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "caload" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_saload ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "saload" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_istore ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "istore #%1%" ) % index );
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_lstore ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "lstore #%1%" ) % index );
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_fstore ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "fstore #%1%" ) % index );
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_dstore ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "dstore #%1%" ) % index );
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_astore ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "astore #%1%" ) % index );
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_iastore ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "iastore" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_lastore ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lastore" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_fastore ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "fastore" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_dastore ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dastore" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_aastore ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "aastore" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_bastore ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "bastore" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_castore ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "castore" );
	  m_current_block->add_line ( temp_ptr );
	}
    
	void
	java_assembly_actions::handle_sastore ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "sastore" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_pop ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "pop" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_pop2 ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "pop2" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_dup ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dup" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_dup_x1 ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dup_x1" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_dup_x2 ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dup_x2" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_dup2 ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dup2" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_dup2_x1 ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dup2_x1" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_dup2_x2 ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dup2_x2" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_swap ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "swap" );
	  m_current_block->add_line ( temp_ptr );
	}
		    
	void
	java_assembly_actions::handle_iadd ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "iadd" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_ladd ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "ladd" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_fadd ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "fadd" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_dadd ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dadd" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_isub ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "isub" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_lsub ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lsub" );
	  m_current_block->add_line ( temp_ptr );
	}
  
	void
	java_assembly_actions::handle_fsub ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "fsub" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_dsub ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dsub" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_imul ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "imul" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_lmul ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lmul" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_fmul ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "fmul" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_dmul ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dmul" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_idiv ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "idiv" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_ldiv ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "ldiv" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_fdiv ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "fdiv" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_ddiv ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "ddiv" );
	  m_current_block->add_line ( temp_ptr );
	}
		    
	void
	java_assembly_actions::handle_irem ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "irem" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_lrem ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lrem" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_frem ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "frem" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_drem ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "drem" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_ineg ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "ineg" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_lneg ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lneg" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_fneg ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "fneg" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_dneg ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dneg" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_ishl ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "ishl" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_lshl ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lshl" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_ishr ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "ishr" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_lshr ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lshr" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_iushr ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "iushr" );
	  m_current_block->add_line ( temp_ptr );
	}
  
	void
	java_assembly_actions::handle_lushr ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lushr" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_iand ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "iand" );
	  m_current_block->add_line ( temp_ptr );
	}
  
	void
	java_assembly_actions::handle_land ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "land" );
	  m_current_block->add_line ( temp_ptr );
	}
		    
	void
	java_assembly_actions::handle_ior ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "ior" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_lor ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lor" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_ixor ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "ixor" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_lxor ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lxor" );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_iinc ( boost::uint32_t opcode_index, boost::uint16_t index, boost::uint16_t const_value )
	{
	  std::string line = boost::str ( boost::format ( "iinc #%1% %2%" )
					  % index
					  % const_value );
      
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_i2l ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "i2l" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_i2f ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "i2f" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_i2d ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "i2d" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_l2i ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "l2i" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_l2f ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "l2f" );

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_l2d ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "l2d" );

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_f2i ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "f2i" );

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_f2l ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "f2l" );

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_f2d ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "f2d" );

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_d2i ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "d2i" );

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_d2l ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "d2l" );

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_d2f ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "d2f" );

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_i2b ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "i2b" );

	  m_current_block->add_line ( temp_ptr );
	}
  
	void
	java_assembly_actions::handle_i2c ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "i2c" );

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_i2s ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "i2s" );

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_lcmp ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lcmp" );

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_fcmpl ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "fcmpl" );

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_fcmpg ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "fcmpg" );

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_dcmpl ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dcmpl" );

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_dcmpg ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dcmpg" );

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_ifeq ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
	{
	  std::string line = boost::str ( boost::format ( "ifeq #%1%" ) % true_branch_index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_ifne ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
	{
	  std::string line = boost::str ( boost::format ( "ifne #%1%" )
					  % true_branch_index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_iflt ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
	{
	  std::string line = boost::str ( boost::format ( "iflt #%1%" )
					  % true_branch_index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_ifge ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
	{
	  std::string line = boost::str ( boost::format ( "ifge #%1%" )
					  % true_branch_index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_ifgt ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
	{
	  std::string line = boost::str ( boost::format ( "ifgt #%1%" )
					  % true_branch_index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_ifle ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
	{
	  std::string line = boost::str ( boost::format ( "ifle #%1%" )
					  % true_branch_index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_if_icmpeq ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
	{
	  std::string line = boost::str ( boost::format ( "if_icmpeq #%1%" )
					  % true_branch_index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_if_icmpne ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
	{
	  std::string line = boost::str ( boost::format ( "if_icmpne #%1%" )
					  % true_branch_index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_if_icmplt ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
	{
	  std::string line = boost::str ( boost::format ( "if_icmplt #%1%" )
					  % true_branch_index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_if_icmpge ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
	{
	  std::string line = boost::str ( boost::format ( "if_icmpge #%1%" )
					  % true_branch_index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_if_icmpgt ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
	{
	  std::string line = boost::str ( boost::format ( "if_icmpgt #%1%" )
					  % true_branch_index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_if_icmple ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
	{
	  std::string line = boost::str ( boost::format ( "if_icmple #%1%" )
					  % true_branch_index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_if_acmpeq ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
	{
	  std::string line = boost::str ( boost::format ( "if_acmpeq #%1%" )
					  % true_branch_index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}
  
	void
	java_assembly_actions::handle_if_acmpne ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
	{
	  std::string line = boost::str ( boost::format ( "if_acmpne #%1%" )
					  % true_branch_index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_goto ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "goto #%1%" ) % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_jsr ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "jsr #%1%" )
					  % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_ret ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "ret #%1%" )
					  % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}
  
	void
	java_assembly_actions::handle_tableswitch ( boost::uint32_t opcode_index,
						    boost::uint32_t default_value,
						    boost::uint32_t low,
						    boost::uint32_t high,
						    std::vector<boost::uint32_t> offsets )
	{
	  std::stringstream output;
	  output << boost::str ( boost::format ( "tableswitch #%1% to %2%: default=%3%" )
				 % low
				 % high
				 % default_value ) << std::endl;

	  for ( std::vector<boost::uint32_t>::const_iterator pos = offsets.begin();
		pos != offsets.end();
		++pos )
	    {
	      output << boost::format ( "%|1$' '15d|: %|2$d|")
		% ( pos - offsets.begin() )
		% *pos
		     << std::endl;
	    }

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, output.str() );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_lookupswitch ( boost::uint32_t opcode_index,
						     boost::uint32_t default_value,
						     std::vector< std::pair<boost::uint32_t, boost::uint32_t> > npair_list )
	{
	  std::stringstream output;
	  output << "lookupswitch" << std::endl;
	  output << boost::str ( boost::format ( "default = %1%" ) % default_value ) << std::endl;
	  output << boost::str ( boost::format ( "pairs count = %1%" ) % npair_list.size() ) << std::endl;

	  for ( std::vector< std::pair<boost::uint32_t, boost::uint32_t> >::const_iterator pos = npair_list.begin();
		pos != npair_list.end();
		++pos )
	    {
	      output << boost::format ( "key = %1%, offset = #%2%")
		% (*pos).first
		% (*pos).second
		     << std::endl;
	    }

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, output.str() );

	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_ireturn ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "ireturn" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_lreturn ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "lreturn" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_freturn ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "freturn" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_dreturn ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "dreturn" );
	  m_current_block->add_line ( temp_ptr );
	}
		    
	void
	java_assembly_actions::handle_areturn ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "areturn" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_return ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "return" );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_getstatic ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "getstatic #%1%" )
					  % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_putstatic ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "putstatic #%1%" )
					  % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_getfield ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "getfield #%1%" ) % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );

	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_putfield ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "putfield #%1%" )
					  % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_invokevirtual ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "invokevirtual #%1%" )
					  % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_invokespecial ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "invokespecial #%1%" )
					  % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_invokestatic ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "invokestatic #%1%" )
					  % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_invokveinterface ( boost::uint32_t opcode_index,
							 boost::uint16_t index,
							 boost::uint16_t )
	{
	  std::string line = boost::str ( boost::format ( "invokeinterface #%1%" )
					  % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_new ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "new #%1%" )
					  % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_newarray ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "newarray #%1%" )
					  % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_anewarray ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "anewarray #%1%" )
					  % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_arraylength ( boost::uint32_t opcode_index )
	{
	  std::string line = boost::str ( boost::format ( "arraylength #%1%" )
					  % opcode_index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_athrow ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "athrow" );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_checkcast ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "checkcast #%1%" )
					  % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_instanceof ( boost::uint32_t opcode_index, boost::uint16_t index )
	{
	  std::string line = boost::str ( boost::format ( "instanceof #%1%" )
					  % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}
  
	void
	java_assembly_actions::handle_monitorenter ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "monitorenter" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_monitorexit ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "monitorexit" );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_wide ( boost::uint32_t opcode_index, boost::uint16_t opcode, boost::uint16_t index )
	{
	  std::stringstream output;

	  output << "wide ";

	  switch ( opcode )
	    {
	    case java_opcodes::iload: output << "iload"; break;
	    case java_opcodes::fload: output << "fload"; break;
	    case java_opcodes::aload: output << "aload"; break;
	    case java_opcodes::lload: output << "lload"; break;
	    case java_opcodes::dload: output << "dload"; break;
	    case java_opcodes::istore: output << "istore"; break;
	    case java_opcodes::fstore: output << "fstore"; break;
	    case java_opcodes::astore: output << "astore"; break;
	    case java_opcodes::lstore: output << "istore"; break;
	    case java_opcodes::dstore: output << "dstore"; break;
	    case java_opcodes::opcode_return: output << "return"; break;
	    }

	  output << boost::str ( boost::format (" %1%") % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, output.str() );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_wide_iinc ( boost::uint32_t opcode_index, boost::uint16_t index, boost::uint16_t const_byte )
	{
	  std::string line = boost::str ( boost::format ( "wide iinc #%2% %3%" )
					  % opcode_index
					  % index
					  % const_byte );
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_multianewarray ( boost::uint32_t opcode_index, boost::uint16_t index, boost::uint16_t dimensions )
	{
	  std::string line = boost::str ( boost::format ( "mutlinewarray #%1%, %2%" )
					  % index
					  % dimensions );
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_ifnull ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
	{
	  std::string line = boost::str ( boost::format ( "ifnull #%1%" )
					  % true_branch_index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_ifnonnull ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
	{
	  std::string line = boost::str ( boost::format ( "ifnonnull #%1%" )
					  % true_branch_index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_goto_w ( boost::uint32_t opcode_index, boost::uint32_t index )
	{
	  std::string line = boost::str ( boost::format ( "gotow #%1%" ) % index );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_jsr_w ( boost::uint32_t opcode_index, boost::uint32_t offset )
	{
	  std::string line = boost::str ( boost::format ( "jsr_w #%1%" )
					  % offset );

	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, line );
	  m_current_block->add_line ( temp_ptr );
	}
	      
	void
	java_assembly_actions::handle_breakpoint ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "breakpoint" );
	  m_current_block->add_line ( temp_ptr );
	}
  
	void
	java_assembly_actions::handle_impdep1 ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "impdep1" );
	  m_current_block->add_line ( temp_ptr );
	}

	void
	java_assembly_actions::handle_impdep2 ( boost::uint32_t opcode_index )
	{
	  boost::shared_ptr < data_container::java_assembly_instruction > temp_ptr =
	    boost::make_shared < data_container::java_assembly_instruction > ( opcode_index, "impdep2" );
	  m_current_block->add_line ( temp_ptr );
	}




      } // namespace instruction_decoders
    } // namespace input
  } // namespace components
} // namespace reverse
