/*  Master_Formula_Parser.h

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

#ifndef MASTER_FORMULA_PARSER_H_
#define MASTER_FORMULA_PARSER_H_

#include "Configurator.h"
#include "Master_Formula_Tag_Names.h"
#include <stack>
#include "XMLExpatParser.h"
#include "Component_Types.h"

namespace libreverse { namespace infrastructure {

    class Master_Formula_Parser : public XMLExpatParser {
    public:

        explicit Master_Formula_Parser();

        virtual ~Master_Formula_Parser(){}

        infrastructure_types::Configurator::Formula_Map_ptr_t
        get_Formula_Map ( std::string filename );

        virtual void startElement ( const std::string& element_name,
                                    const Attribute_Map_t& attributes );

        virtual void charData ( const std::string& element_value );

        virtual void endElement ( const std::string& element_name );

    private:

        static const int MATCH;

        infrastructure_types::Configurator::Formula_Map_ptr_t m_map;
        Master_Formula_Tag_Names m_tag;
        boost::uint32_t m_input_type;
        boost::uint32_t m_output_type;
        std::string m_input_formula_file;
        std::string m_analysis_formula_file;
        std::string m_output_formula_file;

        std::stack<std::string> m_element_list;
    };
} /* namespace infrastructure */
} /* namespace libreverse */

#endif /* MASTER_FORMULA_PARSER_H_ */
