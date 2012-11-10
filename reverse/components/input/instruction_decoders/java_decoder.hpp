/*  Java_Decoder.h

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

#ifndef JAVA_DECODER_H
#define JAVA_DECODER_H

#include <reverse/components/input/instruction_decoders/decoder.hpp>
#include <reverse/io/input/file_readers/java_class/code_attribute.hpp>

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>

#include <list>
#include <stack>
#include <string>

namespace reverse {
  namespace data_container {

    class basic_block;
    class control_flow_graph_sequence;

  } // namespace data_container
} // namespace reverse

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace java_class {

	  class method_info;

	} // namespace java
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

namespace reverse {
  namespace components {
    namespace input {
      namespace instruction_decoders {

	class java_actions;

	class java_decoder : public decoder {
	public:

	  java_decoder ( boost::shared_ptr < java_actions > m_actions );

	  /* Decode the input data listed in the memory map into the desired
	     output returned in a control flow graph */
	  
	  virtual boost::shared_ptr < data_container::control_flow_graph_sequence> execute ( std::string filename );

	private:

	  void process_code_attribute ( boost::shared_ptr < reverse::io::input::file_readers::java_class::code_attribute > code_ptr,
					boost::shared_ptr < const reverse::io::input::file_readers::java_class::method_info > method_ptr );

	  void process_todo_list ( boost::shared_ptr < reverse::io::input::file_readers::java_class::code_attribute > code_ptr );

	  void process_single_opcodes ( boost::uint32_t& opcode_index,
					boost::shared_ptr < const reverse::io::input::file_readers::java_class::code_attribute > code_ptr );

	  void process_16bit_single_branch_opcodes ( boost::uint32_t& opcode_index,
						     boost::shared_ptr < const reverse::io::input::file_readers::java_class::code_attribute > code_ptr,
						     boost::shared_ptr < const reverse::data_container::basic_block > current_bb_ptr );

	  void process_32bit_single_branch_opcodes ( boost::uint32_t& opcode_index,
						     boost::shared_ptr < const reverse::io::input::file_readers::java_class::code_attribute > code_ptr,
						     boost::shared_ptr < const reverse::data_container::basic_block > current_bb_ptr );

	  void process_double_branch_opcodes ( boost::uint32_t& opcode_index,
					       boost::shared_ptr < const reverse::io::input::file_readers::java_class::code_attribute > code_ptr,
					       boost::shared_ptr < const reverse::data_container::basic_block > current_bb_ptr );

	  boost::uint8_t read_8bit_value ( reverse::io::input::file_readers::java_class::code_attribute::code_list_t::const_iterator pos,
					   reverse::io::input::file_readers::java_class::code_attribute::code_list_t::const_iterator end );

	  boost::uint16_t read_16bit_value ( reverse::io::input::file_readers::java_class::code_attribute::code_list_t::const_iterator pos,
					     reverse::io::input::file_readers::java_class::code_attribute::code_list_t::const_iterator end );
	
	  boost::uint32_t read_32bit_value ( reverse::io::input::file_readers::java_class::code_attribute::code_list_t::const_iterator pos,
					     reverse::io::input::file_readers::java_class::code_attribute::code_list_t::const_iterator end );

	  boost::shared_ptr < java_actions > m_actions;

	  boost::shared_ptr < data_container::control_flow_graph > m_current_graph;

	  boost::shared_ptr < data_container::control_flow_graph_sequence > m_graph_list;

	  typedef std::list<boost::uint32_t> basic_block_list_t;
	  basic_block_list_t m_todo_list;

	  basic_block_list_t m_processed_list;

	  reverse::io::input::file_readers::java_class::code_attribute::code_list_t::const_iterator m_read_head;
	};
    
      } // namespace instruction_decoders
    } // namespace input
  } // namespace components
} // namespace reverse


#endif /* JAVA_DECODER_H */
