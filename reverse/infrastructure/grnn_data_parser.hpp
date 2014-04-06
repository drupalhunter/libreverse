/*  GRNN_Data_Parser.h

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

#ifndef REVERSE_INFRASTRUCTURE_GRNN_DATA_PARSER_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_GRNN_DATA_PARSER_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

namespace reverse {
  
	namespace components {
	  namespace input {
	    namespace grnn {
	      class grnn_data_map;
	    } // namespace grnn
	  } // namespace input
	} // namespace components
  
        namespace infrastructure {

                class grnn_data_parser {
                        public:

                                grnn_data_parser();

                                virtual ~grnn_data_parser() {}

                                boost::shared_ptr < components::input::grnn::grnn_data_map > get_data_map ( std::string filename );

                        private:

                                boost::shared_ptr < components::input::grnn::grnn_data_map > m_data_map;
                };
        } /* namespace infrastructure */
} /* namespace reverse */

#endif /* REVERSE_INFRASTRUCTURE_GRNN_DATA_PARSER_HPP_INCLUDED */
