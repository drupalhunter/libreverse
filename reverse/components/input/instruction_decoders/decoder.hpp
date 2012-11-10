/*  Decoder.h

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

#ifndef REVERSE_COMPONENTS_INPUT_INSTRUCTION_DECODERS_DECODER_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_INSTRUCTION_DECODERS_DECODER_HPP_INCLUDED

#include <reverse/data_containers/control_flow_graph_sequence.hpp>

#include <boost/shared_ptr.hpp>

namespace reverse {
  namespace components {
    namespace input {
      namespace instruction_decoders {


	class decoder {
	public:

	  virtual ~decoder(){}

	  /* Decode the input data listed in the memory map into the desired
	     output returned in a control flow graph */
	  virtual boost::shared_ptr < data_container::control_flow_graph_sequence > execute ( std::string filename ) = 0;

	};

      } // namespace instruction_decoders
    } // namespace input
  } // namespace components
} // namespace reverse

#endif // #ifndef REVERSE_COMPONENTS_INPUT_INSTRUCTION_DECODERS_DECODER_HPP_INCLUDED
