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

#ifndef REVERSE_COMPONENTS_INPUT_INSTRUCTION_DECODERS_JAVA_ASSEMBLY_ACTIONS_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_INSTRUCTION_DECODERS_JAVA_ASSEMBLY_ACTIONS_HPP_INCLUDED

#include <reverse/components/input/instruction_decoders/java_actions.hpp>
#include <reverse/data_containers/basic_block.hpp>

namespace reverse {
  namespace components {
    namespace input {
      namespace instruction_decoders {

	class java_assembly_actions : public java_actions {
	public:

	  java_assembly_actions();

	  virtual ~java_assembly_actions(){}

	  virtual void set_current_basic_block ( boost::shared_ptr < data_container::basic_block> );

	  virtual void handle_nop ( boost::uint32_t opcode_index );

	  virtual void handle_aconst_null ( boost::uint32_t opcode_index );

	  virtual void handle_iconst ( boost::uint32_t opcode_index, boost::int32_t constant );	      
	      
	  virtual void handle_lconst ( boost::uint32_t opcode_index, boost::int64_t constant  );
	      
	  virtual void handle_fconst ( boost::uint32_t opcode_index, float constant );
	      
	  virtual void handle_dconst ( boost::uint32_t opcode_index, double constant );
	      
	  virtual void handle_bipush ( boost::uint32_t opcode_index, boost::uint16_t imm_byte );

	  virtual void handle_sipush ( boost::uint32_t opcode_index, boost::uint16_t value );

	  virtual void handle_ldc ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_ldc2_w ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_iload ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_lload ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_fload ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_dload ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_aload ( boost::uint32_t opcode_index, boost::uint16_t index );
	      
	  virtual void handle_iaload ( boost::uint32_t opcode_index );
	      
	  virtual void handle_laload ( boost::uint32_t opcode_index );
		    
	  virtual void handle_faload ( boost::uint32_t opcode_index );
	      
	  virtual void handle_daload ( boost::uint32_t opcode_index );
    
	  virtual void handle_aaload ( boost::uint32_t opcode_index );
	      
	  virtual void handle_baload ( boost::uint32_t opcode_index );
	      
	  virtual void handle_caload ( boost::uint32_t opcode_index );
	      
	  virtual void handle_saload ( boost::uint32_t opcode_index );
	      
	  virtual void handle_istore ( boost::uint32_t opcode_index, boost::uint16_t index );
	      
	  virtual void handle_lstore ( boost::uint32_t opcode_index, boost::uint16_t index );
	      
	  virtual void handle_fstore ( boost::uint32_t opcode_index, boost::uint16_t index );
	      
	  virtual void handle_dstore ( boost::uint32_t opcode_index, boost::uint16_t index );
	      
	  virtual void handle_astore ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_iastore ( boost::uint32_t opcode_index );
	      
	  virtual void handle_lastore ( boost::uint32_t opcode_index );
	      
	  virtual void handle_fastore ( boost::uint32_t opcode_index );
	      
	  virtual void handle_dastore ( boost::uint32_t opcode_index );
	      
	  virtual void handle_aastore ( boost::uint32_t opcode_index );
	      
	  virtual void handle_bastore ( boost::uint32_t opcode_index );
	      
	  virtual void handle_castore ( boost::uint32_t opcode_index );
    
	  virtual void handle_sastore ( boost::uint32_t opcode_index );
	      
	  virtual void handle_pop ( boost::uint32_t opcode_index );
	      
	  virtual void handle_pop2 ( boost::uint32_t opcode_index );
	      
	  virtual void handle_dup ( boost::uint32_t opcode_index );
	      
	  virtual void handle_dup_x1 ( boost::uint32_t opcode_index );
	      
	  virtual void handle_dup_x2 ( boost::uint32_t opcode_index );
	      
	  virtual void handle_dup2 ( boost::uint32_t opcode_index );
	      
	  virtual void handle_dup2_x1 ( boost::uint32_t opcode_index );
	      
	  virtual void handle_dup2_x2 ( boost::uint32_t opcode_index );
	      
	  virtual void handle_swap ( boost::uint32_t opcode_index );
		    
	  virtual void handle_iadd ( boost::uint32_t opcode_index );
	      
	  virtual void handle_ladd ( boost::uint32_t opcode_index );
	      
	  virtual void handle_fadd ( boost::uint32_t opcode_index );
	      
	  virtual void handle_dadd ( boost::uint32_t opcode_index );
	      
	  virtual void handle_isub ( boost::uint32_t opcode_index );
	      
	  virtual void handle_lsub ( boost::uint32_t opcode_index );
	      
	  virtual void handle_fsub ( boost::uint32_t opcode_index );
	      
	  virtual void handle_dsub ( boost::uint32_t opcode_index );
	      
	  virtual void handle_imul ( boost::uint32_t opcode_index );
	      
	  virtual void handle_lmul ( boost::uint32_t opcode_index );
	      
	  virtual void handle_fmul ( boost::uint32_t opcode_index );
	      
	  virtual void handle_dmul ( boost::uint32_t opcode_index );
	      
	  virtual void handle_idiv ( boost::uint32_t opcode_index );
	      
	  virtual void handle_ldiv ( boost::uint32_t opcode_index );
	      
	  virtual void handle_fdiv ( boost::uint32_t opcode_index );
	      
	  virtual void handle_ddiv ( boost::uint32_t opcode_index );
		    
	  virtual void handle_irem ( boost::uint32_t opcode_index );
	      
	  virtual void handle_lrem ( boost::uint32_t opcode_index );
	      
	  virtual void handle_frem ( boost::uint32_t opcode_index );
	      
	  virtual void handle_drem ( boost::uint32_t opcode_index );
	      
	  virtual void handle_ineg ( boost::uint32_t opcode_index );
	      
	  virtual void handle_lneg ( boost::uint32_t opcode_index );
	      
	  virtual void handle_fneg ( boost::uint32_t opcode_index );
	      
	  virtual void handle_dneg ( boost::uint32_t opcode_index );
	      
	  virtual void handle_ishl ( boost::uint32_t opcode_index );
	      
	  virtual void handle_lshl ( boost::uint32_t opcode_index );
	      
	  virtual void handle_ishr ( boost::uint32_t opcode_index );
	      
	  virtual void handle_lshr ( boost::uint32_t opcode_index );
	      
	  virtual void handle_iushr ( boost::uint32_t opcode_index );
	      
	  virtual void handle_lushr ( boost::uint32_t opcode_index );
	      
	  virtual void handle_iand ( boost::uint32_t opcode_index );
	      
	  virtual void handle_land ( boost::uint32_t opcode_index );
		    
	  virtual void handle_ior ( boost::uint32_t opcode_index );
	      
	  virtual void handle_lor ( boost::uint32_t opcode_index );
	      
	  virtual void handle_ixor ( boost::uint32_t opcode_index );
	      
	  virtual void handle_lxor ( boost::uint32_t opcode_index );

	  virtual void handle_iinc ( boost::uint32_t opcode_index, boost::uint16_t index, boost::uint16_t const_value );
	      
	  virtual void handle_i2l ( boost::uint32_t opcode_index );
	      
	  virtual void handle_i2f ( boost::uint32_t opcode_index );
	      
	  virtual void handle_i2d ( boost::uint32_t opcode_index );
	      
	  virtual void handle_l2i ( boost::uint32_t opcode_index );
	      
	  virtual void handle_l2f ( boost::uint32_t opcode_index );
	      
	  virtual void handle_l2d ( boost::uint32_t opcode_index );
	      
	  virtual void handle_f2i ( boost::uint32_t opcode_index );
	      
	  virtual void handle_f2l ( boost::uint32_t opcode_index );
	      
	  virtual void handle_f2d ( boost::uint32_t opcode_index );
	      
	  virtual void handle_d2i ( boost::uint32_t opcode_index );
	      
	  virtual void handle_d2l ( boost::uint32_t opcode_index );
	      
	  virtual void handle_d2f ( boost::uint32_t opcode_index );
	      
	  virtual void handle_i2b ( boost::uint32_t opcode_index );
	      
	  virtual void handle_i2c ( boost::uint32_t opcode_index );
	      
	  virtual void handle_i2s ( boost::uint32_t opcode_index );
	      
	  virtual void handle_lcmp ( boost::uint32_t opcode_index );
	      
	  virtual void handle_fcmpl ( boost::uint32_t opcode_index );
	      
	  virtual void handle_fcmpg ( boost::uint32_t opcode_index );
	      
	  virtual void handle_dcmpl ( boost::uint32_t opcode_index );
	      
	  virtual void handle_dcmpg ( boost::uint32_t opcode_index );
	      
	  virtual void handle_ifeq ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );
	      
	  virtual void handle_ifne ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

	  virtual void handle_iflt ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

	  virtual void handle_ifge ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

	  virtual void handle_ifgt ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

	  virtual void handle_ifle ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

	  virtual void handle_if_icmpeq ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

	  virtual void handle_if_icmpne ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

	  virtual void handle_if_icmplt ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

	  virtual void handle_if_icmpge ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

	  virtual void handle_if_icmpgt ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

	  virtual void handle_if_icmple ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

	  virtual void handle_if_acmpeq ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

	  virtual void handle_if_acmpne ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

	  virtual void handle_goto ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_jsr ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_ret ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_tableswitch ( boost::uint32_t opcode_index,
					    boost::uint32_t default_value,
					    boost::uint32_t low,
					    boost::uint32_t high,
					    std::vector<boost::uint32_t> offsets );

	  virtual void handle_lookupswitch ( boost::uint32_t opcode_index,
					     boost::uint32_t default_value,
					     std::vector< std::pair<boost::uint32_t, boost::uint32_t> > npair_list );
	      
	  virtual void handle_ireturn ( boost::uint32_t opcode_index );
	      
	  virtual void handle_lreturn ( boost::uint32_t opcode_index );
	      
	  virtual void handle_freturn ( boost::uint32_t opcode_index );
	      
	  virtual void handle_dreturn ( boost::uint32_t opcode_index );
		    
	  virtual void handle_areturn ( boost::uint32_t opcode_index );
	      
	  virtual void handle_return ( boost::uint32_t opcode_index );

	  virtual void handle_getstatic ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_putstatic ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_getfield ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_putfield ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_invokevirtual ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_invokespecial ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_invokestatic ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_invokveinterface ( boost::uint32_t opcode_index,
						 boost::uint16_t index,
						 boost::uint16_t count );

	  virtual void handle_new ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_newarray ( boost::uint32_t opcode_index, boost::uint16_t atype );

	  virtual void handle_anewarray ( boost::uint32_t opcode_index, boost::uint16_t index );
	      
	  virtual void handle_arraylength ( boost::uint32_t opcode_index );
	      
	  virtual void handle_athrow ( boost::uint32_t opcode_index );

	  virtual void handle_checkcast ( boost::uint32_t opcode_index, boost::uint16_t index );

	  virtual void handle_instanceof ( boost::uint32_t opcode_index, boost::uint16_t index );
	      
	  virtual void handle_monitorenter ( boost::uint32_t opcode_index );
	      
	  virtual void handle_monitorexit ( boost::uint32_t opcode_index );
	      
	  virtual void handle_wide ( boost::uint32_t opcode_index, boost::uint16_t opcode, boost::uint16_t index );

	  virtual void handle_wide_iinc ( boost::uint32_t opcode_index, boost::uint16_t index, boost::uint16_t const_byte );

	  virtual void handle_multianewarray ( boost::uint32_t opcode_index, boost::uint16_t index, boost::uint16_t dimensions );

	  virtual void handle_ifnull ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

	  virtual void handle_ifnonnull ( boost::uint32_t opcode_index, boost::int16_t true_branch_index );

	  virtual void handle_goto_w ( boost::uint32_t ocpode_index, boost::uint32_t index );

	  virtual void handle_jsr_w ( boost::uint32_t opcode_index, boost::uint32_t offset );
	      
	  virtual void handle_breakpoint ( boost::uint32_t opcode_index );
		    
	  virtual void handle_impdep1 ( boost::uint32_t opcode_index );

	  virtual void handle_impdep2 ( boost::uint32_t opcode_index );

	private:

	  boost::shared_ptr<data_container::basic_block> m_current_block;

	};

      } // namespace instruction_decoders
    } // namespace input
  } // namespace components
} // namespace reverse

#endif // #ifndef REVERSE_COMPONENTS_INPUT_INSTRUCTION_DECODERS_JAVA_ASSEMBLY_ACTIONS_HPP_INCLUDED
