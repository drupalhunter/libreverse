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

#include <reverse/infrastructure/grnn_data_tag_names.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>

#include <expatpp.h>

#include <vector>
#include <stack>



namespace libreverse { namespace infrastructure {

    class GRNN_Data_Parser : public expatpp {
    public:

        grnn_data_parser();

      virtual ~grnn_data_parser(){}
      
      boost::shared_ptr < components::input::grnn::grnn_data_map > get_data_map ( std::string filename );

      virtual void startElement ( const std::string& element_name,
				  const Attribute_Map_t& attributes );

      virtual void charData ( const std::string& element_value );
      
      virtual void endElement ( const std::string& element_name );

    private:

      static const int MATCH;
      
      boost::shared_ptr < components::input::grnn::grnn_data_map > m_data_map;
      grnn_data_tag_names m_tag;

      std::string m_type;
      double m_sigma;
      std::string m_file;
      
        std::stack<std::string> m_element_list;
    };
  } /* namespace infrastructure */
} /* namespace reverse */

#endif /* REVERSE_INFRASTRUCTURE_GRNN_DATA_PARSER_HPP_INCLUDED */
