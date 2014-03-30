/*  Formula_Parser.h

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

#ifndef REVERSE_INFRASTRUCTURE_FORMULA_PARSER_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_FORMULA_PARSER_HPP_INCLUDED

#include <reverse/infrastructure/formula_tag_names.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>

#include <vector>
#include <stack>

#include "expatpp.h"


namespace reverse {
  namespace infrastructure {

    class formula_parser : public expatpp {
    public:

        formula_parser();

        virtual ~formula_parser(){}

        infrastructure_types::Component_Graph::ptr_t get_Graph ( std::string filename,
                                                                 std::string directory );

        virtual void startElement ( const std::string& element_name,
                                    const Attribute_Map_t& attributes );

        virtual void charData ( const std::string& element_value );

        virtual void endElement ( const std::string& element_name );

    private:

        static const int MATCH;

        infrastructure_types::Component::ptr_t get_Component ( boost::uint32_t id,
                                                               std::string name );

        void construct_Component ();

        void print_Component_List (void) const;

      boost::shared_ptr < infrastructure_types::component_graph > m_graph;
      formula_tag_names m_tag;
      std::vector<int> m_predecessor_list;
      int m_id;
      std::string m_name;
      std::string m_file;

      std::stack<std::string> m_element_list;
    };

  } /* namespace infrastructure */
} /* namespace reverse */

#endif /* REVERSE_INFRASTRUCTURE_FORMULA_PARSER_HPP_INCLUDED */
