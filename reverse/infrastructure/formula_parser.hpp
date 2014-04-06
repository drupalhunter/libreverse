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

#include <json_spirit/json_spirit.h>

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <boost/graph/graph_concepts.hpp>


namespace reverse {
  namespace infrastructure {

   class component;
   class component_graph;
    
    class formula_parser {
    public:

        formula_parser();

        virtual ~formula_parser(){}

	boost::shared_ptr < infrastructure::component_graph > get_graph ( std::string filename,
									  std::string directory );

    private:

        void read_components ( json_spirit::Object const& obj );

	boost::shared_ptr < infrastructure::component > get_component ( json_spirit::Object::const_iterator cpos );

	boost::shared_ptr < infrastructure::component_graph > m_graph;
	
	int m_id;
	std::string m_name;
	std::string m_file;

    };

  } /* namespace infrastructure */
} /* namespace reverse */

#endif /* REVERSE_INFRASTRUCTURE_FORMULA_PARSER_HPP_INCLUDED */
