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

#include "Java_Assembly_Actions.h"
#include "Java_Opcodes.h"

#include "reverse/io/Preconditions.h"
#include "reverse/data_containers/Basic_Block.h"
#include "reverse/data_containers/Control_Flow_Graph.h"
#include "reverse/data_containers/Java_Assembly_Instruction.h"

#include <boost/format.hpp>
#include <sstream>

#ifdef LIBREVERSE_DEBUG
#include "reverse/Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

using namespace reverse::data_container;

namespace reverse { namespace decoder {

    Java_Assembly_Actions::Java_Assembly_Actions ()
    {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INSTRUCTION_DECODER,
                             TraceLevel::DETAIL,
                             "Inside Java_Assembly_Actions constructor" );
#endif /* LIBREVERSE_DEBUG */
    }

    void
    Java_Assembly_Actions::set_Current_Basic_Block ( data_types::Basic_Block::ptr_t bb_ptr )
    {
#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INSTRUCTION_DECODER,
                             TraceLevel::DETAIL,
                             "Entering Java_Assembly_Actions::set_Current_Basic_Block" );
#endif /* LIBREVERSE_DEBUG */

	io::Preconditions::is_set ( bb_ptr );

	m_current_block = bb_ptr;

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INSTRUCTION_DECODER,
                             TraceLevel::DETAIL,
                             "Exiting Java_Assembly_Actions::set_Current_Basic_Block" );
#endif /* LIBREVERSE_DEBUG */
    }

    void
    Java_Assembly_Actions::handle_NOP ( boost::uint32_t opcode_index )
    {
#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::INSTRUCTION_DECODER,
			   TraceLevel::DETAIL,
			   "Entering Java_Assembly_Actions::handle_NOP" );
#endif /* LIBREVERSE_DEBUG */

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr ( new data_container::Java_Assembly_Instruction ( opcode_index, "nop" ) );
      m_current_block->add_Line ( temp_ptr );

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::INSTRUCTION_DECODER,
                             TraceLevel::DETAIL,
                             "Exting Java_Assembly_Actions::handle_NOP" );
#endif /* LIBREVERSE_DEBUG */
    }

    void
    Java_Assembly_Actions::handle_ACONST_NULL ( boost::uint32_t opcode_index )
    {
#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::INSTRUCTION_DECODER,
			   TraceLevel::DETAIL,
			   "Entering Java_Assembly_Actions::handle_ACONST_NULL" );
#endif /* LIBREVERSE_DEBUG */

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr
	( new data_container::Java_Assembly_Instruction ( opcode_index, "aconst_null" ) );
      m_current_block->add_Line ( temp_ptr );

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::INSTRUCTION_DECODER,
			   TraceLevel::DETAIL,
			   "Exiting Java_Assembly_Actions::handle_ACONST_NULL" );
#endif /* LIBREVERSE_DEBUG */

    }

    void
    Java_Assembly_Actions::handle_ICONST ( boost::uint32_t opcode_index, boost::int32_t constant )
    {

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr;

      switch ( constant )
	{
	case -1:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new data_container::Java_Assembly_Instruction ( opcode_index, "iconst_m1" ) );
	  break;
	case 0:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new data_container::Java_Assembly_Instruction ( opcode_index, "iconst_0" ) );
	  break;
	case 1:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "iconst_1" ) );
	  break;
	case 2:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "iconst_2" ) );
	  break;
	case 3:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "iconst_3" ) );
	  break;
	case 4:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "iconst_4" ) );
	  break;
	case 5:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "iconst_5" ) );
	  break;
	}

      m_current_block->add_Line ( temp_ptr );
    }	      
	      
    void
    Java_Assembly_Actions::handle_LCONST ( boost::uint32_t opcode_index, boost::int64_t constant  )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr;

      switch ( constant )
	{
	case 0:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lconst_0" ) );
	  break;
	case 1:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lconst_1" ) );
	  break;
	}

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_FCONST ( boost::uint32_t opcode_index, float constant )
    {

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr;

      if ( constant == 0.0 )
	{
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "fconst_0" ) );
	}
      else if ( constant == 1.0 )
	{
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "fconst_1" ) );
	}
      else if ( constant == 2.0 )
	{
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "fconst_2" ) );
	}

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DCONST ( boost::uint32_t opcode_index, double constant )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr;

      if ( constant == 0.0)
	{
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dconst_0" ) );
	}
      else if ( constant == 1.0 )
	{
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dconst_1" ) );
	}

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_BIPUSH ( boost::uint32_t opcode_index, boost::uint16_t imm_byte )
    {
      std::string line = boost::str ( boost::format ( "bipush %1%" ) % imm_byte );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_SIPUSH ( boost::uint32_t opcode_index, boost::uint16_t value )
    {
      std::string line = boost::str ( boost::format ( "sipush %1%" ) % value );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }
  
    void
    Java_Assembly_Actions::handle_LDC ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "ldc #%1%" ) % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_LDC2_W ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "ldc2_w #%1%" ) % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_ILOAD ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr;

      switch ( index )
	{
	case 0:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "iload_0" ) );
	  break;
	case 1:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "iload_1" ) );
	  break;
	case 2:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "iload_2" ) );
	  break;
	case 3:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "iload_3" ) );
	  break;
	default:
	  std::string line = boost::str ( boost::format ( "iload #%1%" ) % index );
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
	}
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_LLOAD ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr;

      switch ( index )
	{
	case 0:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lload_0" ) );
	  break;
	case 1:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lload_1" ) );
	  break;
	case 2:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lload_2" ) );
	  break;
	case 3:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lload_3" ) );
	  break;
	default:
	  std::string line = boost::str ( boost::format ( "lload #%1%" ) % index );
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
	}
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_FLOAD ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr;

      switch ( index )
	{
	case 0:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "fload_0" ) );
	  break;
	case 1:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "fload_1" ) );
	  break;
	case 2:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "fload_2" ) );
	  break;
	case 3:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "fload_3" ) );
	  break;
	default:
	  std::string line = boost::str ( boost::format ( "fload #%1%" ) % index );
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
	}

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_DLOAD ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr;

      switch ( index )
	{
	case 0:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dload_0" ) );
	  break;
	case 1:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dload_1" ) );
	  break;
	case 2:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dload_2" ) );
	  break;
	case 3:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dload_3" ) );
	  break;
	default:
	  std::string line = boost::str ( boost::format ( "dload #%1%" ) % index );
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
	}

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_ALOAD ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr;

      switch ( index )
	{
	case 0:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "aload_0" ) );
	  break;
	case 1:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "aload_1" ) );
	  break;
	case 2:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "aload_2" ) );
	  break;
	case 3:
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "aload_3" ) );
	  break;
	default:
	  std::string line = boost::str ( boost::format ( "aload #%1%" ) % index );
	  temp_ptr = data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
	}

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_IALOAD ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr ( new Java_Assembly_Instruction ( opcode_index, "iaload" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_LALOAD ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr ( new Java_Assembly_Instruction ( opcode_index, "laload" ) );
      m_current_block->add_Line ( temp_ptr );
    }
		    
    void
    Java_Assembly_Actions::handle_FALOAD ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr ( new Java_Assembly_Instruction ( opcode_index, "faload" ) );
      m_current_block->add_Line ( temp_ptr );
    }
  
    void
    Java_Assembly_Actions::handle_DALOAD ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr ( new Java_Assembly_Instruction ( opcode_index, "daload" ) );
      m_current_block->add_Line ( temp_ptr );
    }
    
    void
    Java_Assembly_Actions::handle_AALOAD ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr ( new Java_Assembly_Instruction ( opcode_index, "aaload" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_BALOAD ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr ( new Java_Assembly_Instruction ( opcode_index, "baload" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_CALOAD ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr ( new Java_Assembly_Instruction ( opcode_index, "caload" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_SALOAD ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr ( new Java_Assembly_Instruction ( opcode_index, "saload" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_ISTORE ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "istore #%1%" ) % index );
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_LSTORE ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "lstore #%1%" ) % index );
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_FSTORE ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "fstore #%1%" ) % index );
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DSTORE ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "dstore #%1%" ) % index );
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_ASTORE ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "astore #%1%" ) % index );
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_IASTORE ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "iastore" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_LASTORE ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lastore" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_FASTORE ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "fastore" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DASTORE ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dastore" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_AASTORE ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "aastore" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_BASTORE ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "bastore" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_CASTORE ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "castore" ) );
      m_current_block->add_Line ( temp_ptr );
    }
    
    void
    Java_Assembly_Actions::handle_SASTORE ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "sastore" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_POP ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "pop" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_POP2 ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "pop2" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DUP ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dup" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DUP_X1 ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dup_x1" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DUP_X2 ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dup_x2" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DUP2 ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dup2" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DUP2_X1 ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dup2_x1" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DUP2_X2 ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dup2_x2" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_SWAP ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "swap" ) );
      m_current_block->add_Line ( temp_ptr );
    }
		    
    void
    Java_Assembly_Actions::handle_IADD ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "iadd" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_LADD ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "ladd" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_FADD ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "fadd" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DADD ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dadd" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_ISUB ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "isub" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_LSUB ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lsub" ) );
      m_current_block->add_Line ( temp_ptr );
    }
  
    void
    Java_Assembly_Actions::handle_FSUB ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "fsub" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DSUB ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dsub" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_IMUL ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "imul" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_LMUL ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lmul" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_FMUL ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "fmul" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DMUL ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dmul" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_IDIV ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "idiv" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_LDIV ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "ldiv" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_FDIV ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "fdiv" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DDIV ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "ddiv" ) );
      m_current_block->add_Line ( temp_ptr );
    }
		    
    void
    Java_Assembly_Actions::handle_IREM ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "irem" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_LREM ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lrem" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_FREM ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "frem" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DREM ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "drem" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_INEG ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "ineg" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_LNEG ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lneg" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_FNEG ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "fneg" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DNEG ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dneg" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_ISHL ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "ishl" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_LSHL ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lshl" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_ISHR ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "ishr" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_LSHR ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lshr" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_IUSHR ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "iushr" ) );
      m_current_block->add_Line ( temp_ptr );
    }
  
    void
    Java_Assembly_Actions::handle_LUSHR ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lushr" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_IAND ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "iand" ) );
      m_current_block->add_Line ( temp_ptr );
    }
  
    void
    Java_Assembly_Actions::handle_LAND ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "land" ) );
      m_current_block->add_Line ( temp_ptr );
    }
		    
    void
    Java_Assembly_Actions::handle_IOR ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "ior" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_LOR ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lor" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_IXOR ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "ixor" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_LXOR ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lxor" ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_IINC ( boost::uint32_t opcode_index, boost::uint16_t index, boost::uint16_t const_value )
    {
      std::string line = boost::str ( boost::format ( "iinc #%1% %2%" )
				      % index
				      % const_value );
      
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_I2L ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "i2l" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_I2F ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "i2f" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_I2D ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "i2d" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_L2I ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "l2i" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_L2F ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "l2f" ) );

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_L2D ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "l2d" ) );

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_F2I ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "f2i" ) );

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_F2L ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "f2l" ) );

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_F2D ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "f2d" ) );

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_D2I ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "d2i" ) );

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_D2L ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "d2l" ) );

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_D2F ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "d2f" ) );

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_I2B ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "i2b" ) );

      m_current_block->add_Line ( temp_ptr );
    }
  
    void
    Java_Assembly_Actions::handle_I2C ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "i2c" ) );

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_I2S ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "i2s" ) );

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_LCMP ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lcmp" ) );

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_FCMPL ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "fcmpl" ) );

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_FCMPG ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "fcmpg" ) );

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DCMPL ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dcmpl" ) );

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DCMPG ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dcmpg" ) );

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_IFEQ ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
    {
      std::string line = boost::str ( boost::format ( "ifeq #%1%" ) % true_branch_index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_IFNE ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
    {
      std::string line = boost::str ( boost::format ( "ifne #%1%" )
				      % true_branch_index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_IFLT ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
    {
      std::string line = boost::str ( boost::format ( "iflt #%1%" )
				      % true_branch_index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_IFGE ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
    {
      std::string line = boost::str ( boost::format ( "ifge #%1%" )
				      % true_branch_index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_IFGT ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
    {
      std::string line = boost::str ( boost::format ( "ifgt #%1%" )
				      % true_branch_index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_IFLE ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
    {
      std::string line = boost::str ( boost::format ( "ifle #%1%" )
				      % true_branch_index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_IF_ICMPEQ ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
    {
      std::string line = boost::str ( boost::format ( "if_icmpeq #%1%" )
				      % true_branch_index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_IF_ICMPNE ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
    {
      std::string line = boost::str ( boost::format ( "if_icmpne #%1%" )
				      % true_branch_index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_IF_ICMPLT ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
    {
      std::string line = boost::str ( boost::format ( "if_icmplt #%1%" )
				      % true_branch_index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_IF_ICMPGE ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
    {
      std::string line = boost::str ( boost::format ( "if_icmpge #%1%" )
				      % true_branch_index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_IF_ICMPGT ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
    {
      std::string line = boost::str ( boost::format ( "if_icmpgt #%1%" )
				      % true_branch_index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_IF_ICMPLE ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
    {
      std::string line = boost::str ( boost::format ( "if_icmple #%1%" )
				      % true_branch_index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_IF_ACMPEQ ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
    {
      std::string line = boost::str ( boost::format ( "if_acmpeq #%1%" )
				      % true_branch_index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }
  
    void
    Java_Assembly_Actions::handle_IF_ACMPNE ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
    {
      std::string line = boost::str ( boost::format ( "if_acmpne #%1%" )
				      % true_branch_index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_GOTO ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "goto #%1%" ) % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_JSR ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "jsr #%1%" )
				      % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_RET ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "ret #%1%" )
				      % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }
  
    void
    Java_Assembly_Actions::handle_TABLESWITCH ( boost::uint32_t opcode_index,
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

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, output.str() ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_LOOKUPSWITCH ( boost::uint32_t opcode_index,
						 boost::uint32_t default_value,
						 std::vector< std::pair<boost::uint32_t, boost::uint32_t> > npair_list )
    {
      std::stringstream output;
      output << "lookupswitch" << std::endl;
      output << boost::str ( boost::format ( "Default = %1%" ) % default_value ) << std::endl;
      output << boost::str ( boost::format ( "Pairs Count = %1%" ) % npair_list.size() ) << std::endl;

      for ( std::vector< std::pair<boost::uint32_t, boost::uint32_t> >::const_iterator pos = npair_list.begin();
	    pos != npair_list.end();
	    ++pos )
	{
	  output << boost::format ( "Key = %1%, Offset = #%2%")
	    % (*pos).first
	    % (*pos).second
		 << std::endl;
	}

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, output.str() ) );

      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_IRETURN ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "ireturn" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_LRETURN ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "lreturn" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_FRETURN ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "freturn" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_DRETURN ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "dreturn" ) );
      m_current_block->add_Line ( temp_ptr );
    }
		    
    void
    Java_Assembly_Actions::handle_ARETURN ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "areturn" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_RETURN ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "return" ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_GETSTATIC ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "getstatic #%1%" )
				      % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_PUTSTATIC ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "putstatic #%1%" )
				      % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_GETFIELD ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "getfield #%1%" ) % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );

      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_PUTFIELD ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "putfield #%1%" )
				      % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_INVOKEVIRTUAL ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "invokevirtual #%1%" )
				      % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_INVOKESPECIAL ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "invokespecial #%1%" )
				      % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_INVOKESTATIC ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "invokestatic #%1%" )
				      % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_INVOKVEINTERFACE ( boost::uint32_t opcode_index,
						     boost::uint16_t index,
						     boost::uint16_t )
    {
      std::string line = boost::str ( boost::format ( "invokeinterface #%1%" )
				      % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_NEW ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "new #%1%" )
				      % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_NEWARRAY ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "newarray #%1%" )
				      % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_ANEWARRAY ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "anewarray #%1%" )
				      % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_ARRAYLENGTH ( boost::uint32_t opcode_index )
    {
      std::string line = boost::str ( boost::format ( "arraylength #%1%" )
				      % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_ATHROW ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "athrow" ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_CHECKCAST ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "checkcast #%1%" )
				      % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_INSTANCEOF ( boost::uint32_t opcode_index, boost::uint16_t index )
    {
      std::string line = boost::str ( boost::format ( "instanceof #%1%" )
				      % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }
  
    void
    Java_Assembly_Actions::handle_MONITORENTER ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "monitorenter" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_MONITOREXIT ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "monitorexit" ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_WIDE ( boost::uint32_t opcode_index, boost::uint16_t opcode, boost::uint16_t index )
    {
      std::stringstream output;

      output << "wide ";

      switch ( opcode )
	{
	case Java_Opcodes::ILOAD: output << "iload"; break;
	case Java_Opcodes::FLOAD: output << "fload"; break;
	case Java_Opcodes::ALOAD: output << "aload"; break;
	case Java_Opcodes::LLOAD: output << "lload"; break;
	case Java_Opcodes::DLOAD: output << "dload"; break;
	case Java_Opcodes::ISTORE: output << "istore"; break;
	case Java_Opcodes::FSTORE: output << "fstore"; break;
	case Java_Opcodes::ASTORE: output << "astore"; break;
	case Java_Opcodes::LSTORE: output << "istore"; break;
	case Java_Opcodes::DSTORE: output << "dstore"; break;
	case Java_Opcodes::RETURN: output << "return"; break;
	}

      output << boost::str ( boost::format (" %1%") % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, output.str() ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_WIDE_IINC ( boost::uint32_t opcode_index, boost::uint16_t index, boost::uint16_t const_byte )
    {
      std::string line = boost::str ( boost::format ( "wide iinc #%2% %3%" )
				      % opcode_index
				      % index
				      % const_byte );
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_MULTIANEWARRAY ( boost::uint32_t opcode_index, boost::uint16_t index, boost::uint16_t dimensions )
    {
      std::string line = boost::str ( boost::format ( "mutlinewarray #%1%, %2%" )
				      % index
				      % dimensions );
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_IFNULL ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
    {
      std::string line = boost::str ( boost::format ( "ifnull #%1%" )
				      % true_branch_index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_IFNONNULL ( boost::uint32_t opcode_index, boost::int16_t true_branch_index )
    {
      std::string line = boost::str ( boost::format ( "ifnonnull #%1%" )
				      % true_branch_index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_GOTO_W ( boost::uint32_t opcode_index, boost::uint32_t index )
    {
      std::string line = boost::str ( boost::format ( "gotow #%1%" ) % index );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_JSR_W ( boost::uint32_t opcode_index, boost::uint32_t offset )
    {
      std::string line = boost::str ( boost::format ( "jsr_w #%1%" )
				      % offset );

      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, line ) );
      m_current_block->add_Line ( temp_ptr );
    }
	      
    void
    Java_Assembly_Actions::handle_BREAKPOINT ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "breakpoint" ) );
      m_current_block->add_Line ( temp_ptr );
    }
  
    void
    Java_Assembly_Actions::handle_IMPDEP1 ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "impdep1" ) );
      m_current_block->add_Line ( temp_ptr );
    }

    void
    Java_Assembly_Actions::handle_IMPDEP2 ( boost::uint32_t opcode_index )
    {
      data_types::Java_Assembly_Instruction::ptr_t temp_ptr =
	data_types::Java_Assembly_Instruction::ptr_t ( new Java_Assembly_Instruction ( opcode_index, "impdep2" ) );
      m_current_block->add_Line ( temp_ptr );
    }

  } /* namespace decoder */
} /* namespace reverse */
