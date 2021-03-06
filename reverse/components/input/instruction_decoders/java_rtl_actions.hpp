/*  Java_Assembly_Actions.h

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

#ifndef JAVA_ASSEMBLY_ACTIONS_H
#define JAVA_ASSEMBLY_ACTIONS_H

#include "reverse/data_containers/Data_Types.h"
#include "Java_Actions.h"

namespace reverse { namespace decoder {

    class Java_Assembly_Actions : public Java_Actions {
    public:

      Java_Assembly_Actions();

      virtual ~Java_Assembly_Actions(){}

      virtual void set_Current_Basic_Block ( data_types::Basic_Block::ptr_t );

      virtual void handle_NOP ( boost::uint32_t opcode_index );

      virtual void handle_ACONST_NULL ( boost::uint32_t opcode_index );

      virtual void handle_ICONST ( boost::uint32_t opcode_index, boost::int32_t constant );	      
	      
      virtual void handle_LCONST ( boost::uint32_t opcode_index, boost::int64_t constant  );
	      
      virtual void handle_FCONST ( boost::uint32_t opcode_index, float constant );
	      
      virtual void handle_DCONST ( boost::uint32_t opcode_index, double constant );
	      
      virtual void handle_BIPUSH ( boost::uint32_t opcode_index, boost::uint16_t imm_byte );

      virtual void handle_SIPUSH ( boost::uint32_t opcode_index, boost::uint16_t value );

      virtual void handle_LDC ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_LDC2_W ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_ILOAD ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_LLOAD ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_FLOAD ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_DLOAD ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_ALOAD ( boost::uint32_t opcode_index, boost::uint16_t index );
	      
      virtual void handle_IALOAD ( boost::uint32_t opcode_index );
	      
      virtual void handle_LALOAD ( boost::uint32_t opcode_index );
		    
      virtual void handle_FALOAD ( boost::uint32_t opcode_index );
	      
      virtual void handle_DALOAD ( boost::uint32_t opcode_index );
    
      virtual void handle_AALOAD ( boost::uint32_t opcode_index );
	      
      virtual void handle_BALOAD ( boost::uint32_t opcode_index );
	      
      virtual void handle_CALOAD ( boost::uint32_t opcode_index );
	      
      virtual void handle_SALOAD ( boost::uint32_t opcode_index );
	      
      virtual void handle_ISTORE ( boost::uint32_t opcode_index, boost::uint16_t index );
	      
      virtual void handle_LSTORE ( boost::uint32_t opcode_index, boost::uint16_t index );
	      
      virtual void handle_FSTORE ( boost::uint32_t opcode_index, boost::uint16_t index );
	      
      virtual void handle_DSTORE ( boost::uint32_t opcode_index, boost::uint16_t index );
	      
      virtual void handle_ASTORE ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_IASTORE ( boost::uint32_t opcode_index );
	      
      virtual void handle_LASTORE ( boost::uint32_t opcode_index );
	      
      virtual void handle_FASTORE ( boost::uint32_t opcode_index );
	      
      virtual void handle_DASTORE ( boost::uint32_t opcode_index );
	      
      virtual void handle_AASTORE ( boost::uint32_t opcode_index );
	      
      virtual void handle_BASTORE ( boost::uint32_t opcode_index );
	      
      virtual void handle_CASTORE ( boost::uint32_t opcode_index );
    
      virtual void handle_SASTORE ( boost::uint32_t opcode_index );
	      
      virtual void handle_POP ( boost::uint32_t opcode_index );
	      
      virtual void handle_POP2 ( boost::uint32_t opcode_index );
	      
      virtual void handle_DUP ( boost::uint32_t opcode_index );
	      
      virtual void handle_DUP_X1 ( boost::uint32_t opcode_index );
	      
      virtual void handle_DUP_X2 ( boost::uint32_t opcode_index );
	      
      virtual void handle_DUP2 ( boost::uint32_t opcode_index );
	      
      virtual void handle_DUP2_X1 ( boost::uint32_t opcode_index );
	      
      virtual void handle_DUP2_X2 ( boost::uint32_t opcode_index );
	      
      virtual void handle_SWAP ( boost::uint32_t opcode_index );
		    
      virtual void handle_IADD ( boost::uint32_t opcode_index );
	      
      virtual void handle_LADD ( boost::uint32_t opcode_index );
	      
      virtual void handle_FADD ( boost::uint32_t opcode_index );
	      
      virtual void handle_DADD ( boost::uint32_t opcode_index );
	      
      virtual void handle_ISUB ( boost::uint32_t opcode_index );
	      
      virtual void handle_LSUB ( boost::uint32_t opcode_index );
	      
      virtual void handle_FSUB ( boost::uint32_t opcode_index );
	      
      virtual void handle_DSUB ( boost::uint32_t opcode_index );
	      
      virtual void handle_IMUL ( boost::uint32_t opcode_index );
	      
      virtual void handle_LMUL ( boost::uint32_t opcode_index );
	      
      virtual void handle_FMUL ( boost::uint32_t opcode_index );
	      
      virtual void handle_DMUL ( boost::uint32_t opcode_index );
	      
      virtual void handle_IDIV ( boost::uint32_t opcode_index );
	      
      virtual void handle_LDIV ( boost::uint32_t opcode_index );
	      
      virtual void handle_FDIV ( boost::uint32_t opcode_index );
	      
      virtual void handle_DDIV ( boost::uint32_t opcode_index );
		    
      virtual void handle_IREM ( boost::uint32_t opcode_index );
	      
      virtual void handle_LREM ( boost::uint32_t opcode_index );
	      
      virtual void handle_FREM ( boost::uint32_t opcode_index );
	      
      virtual void handle_DREM ( boost::uint32_t opcode_index );
	      
      virtual void handle_INEG ( boost::uint32_t opcode_index );
	      
      virtual void handle_LNEG ( boost::uint32_t opcode_index );
	      
      virtual void handle_FNEG ( boost::uint32_t opcode_index );
	      
      virtual void handle_DNEG ( boost::uint32_t opcode_index );
	      
      virtual void handle_ISHL ( boost::uint32_t opcode_index );
	      
      virtual void handle_LSHL ( boost::uint32_t opcode_index );
	      
      virtual void handle_ISHR ( boost::uint32_t opcode_index );
	      
      virtual void handle_LSHR ( boost::uint32_t opcode_index );
	      
      virtual void handle_IUSHR ( boost::uint32_t opcode_index );
	      
      virtual void handle_LUSHR ( boost::uint32_t opcode_index );
	      
      virtual void handle_IAND ( boost::uint32_t opcode_index );
	      
      virtual void handle_LAND ( boost::uint32_t opcode_index );
		    
      virtual void handle_IOR ( boost::uint32_t opcode_index );
	      
      virtual void handle_LOR ( boost::uint32_t opcode_index );
	      
      virtual void handle_IXOR ( boost::uint32_t opcode_index );
	      
      virtual void handle_LXOR ( boost::uint32_t opcode_index );

      virtual void handle_IINC ( boost::uint32_t opcode_index, boost::uint16_t index, boost::uint16_t const_value );
	      
      virtual void handle_I2L ( boost::uint32_t opcode_index );
	      
      virtual void handle_I2F ( boost::uint32_t opcode_index );
	      
      virtual void handle_I2D ( boost::uint32_t opcode_index );
	      
      virtual void handle_L2I ( boost::uint32_t opcode_index );
	      
      virtual void handle_L2F ( boost::uint32_t opcode_index );
	      
      virtual void handle_L2D ( boost::uint32_t opcode_index );
	      
      virtual void handle_F2I ( boost::uint32_t opcode_index );
	      
      virtual void handle_F2L ( boost::uint32_t opcode_index );
	      
      virtual void handle_F2D ( boost::uint32_t opcode_index );
	      
      virtual void handle_D2I ( boost::uint32_t opcode_index );
	      
      virtual void handle_D2L ( boost::uint32_t opcode_index );
	      
      virtual void handle_D2F ( boost::uint32_t opcode_index );
	      
      virtual void handle_I2B ( boost::uint32_t opcode_index );
	      
      virtual void handle_I2C ( boost::uint32_t opcode_index );
	      
      virtual void handle_I2S ( boost::uint32_t opcode_index );
	      
      virtual void handle_LCMP ( boost::uint32_t opcode_index );
	      
      virtual void handle_FCMPL ( boost::uint32_t opcode_index );
	      
      virtual void handle_FCMPG ( boost::uint32_t opcode_index );
	      
      virtual void handle_DCMPL ( boost::uint32_t opcode_index );
	      
      virtual void handle_DCMPG ( boost::uint32_t opcode_index );
	      
      virtual void handle_IFEQ ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );
	      
      virtual void handle_IFNE ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

      virtual void handle_IFLT ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

      virtual void handle_IFGE ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

      virtual void handle_IFGT ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

      virtual void handle_IFLE ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

      virtual void handle_IF_ICMPEQ ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

      virtual void handle_IF_ICMPNE ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

      virtual void handle_IF_ICMPLT ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

      virtual void handle_IF_ICMPGE ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

      virtual void handle_IF_ICMPGT ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

      virtual void handle_IF_ICMPLE ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

      virtual void handle_IF_ACMPEQ ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

      virtual void handle_IF_ACMPNE ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

      virtual void handle_GOTO ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_JSR ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_RET ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_TABLESWITCH ( boost::uint32_t opcode_index,
					boost::uint32_t default_value,
					boost::uint32_t low,
					boost::uint32_t high,
					std::vector<boost::uint32_t> offsets );

      virtual void handle_LOOKUPSWITCH ( boost::uint32_t opcode_index,
					 boost::uint32_t default_value,
					 std::vector< std::pair<boost::uint32_t, boost::uint32_t> > npair_list );
	      
      virtual void handle_IRETURN ( boost::uint32_t opcode_index );
	      
      virtual void handle_LRETURN ( boost::uint32_t opcode_index );
	      
      virtual void handle_FRETURN ( boost::uint32_t opcode_index );
	      
      virtual void handle_DRETURN ( boost::uint32_t opcode_index );
		    
      virtual void handle_ARETURN ( boost::uint32_t opcode_index );
	      
      virtual void handle_RETURN ( boost::uint32_t opcode_index );

      virtual void handle_GETSTATIC ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_PUTSTATIC ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_GETFIELD ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_PUTFIELD ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_INVOKEVIRTUAL ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_INVOKESPECIAL ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_INVOKESTATIC ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_INVOKVEINTERFACE ( boost::uint32_t opcode_index,
					     boost::uint16_t index,
					     boost::uint16_t count );

      virtual void handle_NEW ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_NEWARRAY ( boost::uint32_t opcode_index, boost::uint16_t atype );

      virtual void handle_ANEWARRAY ( boost::uint32_t opcode_index, boost::uint16_t index );
	      
      virtual void handle_ARRAYLENGTH ( boost::uint32_t opcode_index );
	      
      virtual void handle_ATHROW ( boost::uint32_t opcode_index );

      virtual void handle_CHECKCAST ( boost::uint32_t opcode_index, boost::uint16_t index );

      virtual void handle_INSTANCEOF ( boost::uint32_t opcode_index, boost::uint16_t index );
	      
      virtual void handle_MONITORENTER ( boost::uint32_t opcode_index );
	      
      virtual void handle_MONITOREXIT ( boost::uint32_t opcode_index );
	      
      virtual void handle_WIDE ( boost::uint32_t opcode_index, boost::uint16_t opcode, boost::uint16_t index );

      virtual void handle_WIDE_IINC ( boost::uint32_t opcode_index, boost::uint16_t index, boost::uint16_t const_byte );

      virtual void handle_MULTIANEWARRAY ( boost::uint32_t opcode_index, boost::uint16_t index, boost::uint16_t dimensions );

      virtual void handle_IFNULL ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

      virtual void handle_IFNONNULL ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

      virtual void handle_GOTO_W ( boost::uint32_t ocpode_index, boost::uint32_t index );

      virtual void handle_JSR_W ( boost::uint32_t opcode_index, boost::uint32_t offset );
	      
      virtual void handle_BREAKPOINT ( boost::uint32_t opcode_index );
		    
      virtual void handle_IMPDEP1 ( boost::uint32_t opcode_index );

      virtual void handle_IMPDEP2 ( boost::uint32_t opcode_index );

    private:

      data_types::Basic_Block::ptr_t m_current_block;

    };

  } /* namespace decoder */
} /* namespace reverse */

#endif /* JAVA_ASSEMBLY_ACTIONS_H */
