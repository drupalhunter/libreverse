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

#ifndef GRNN_DATA_PARSER_H_
#define GRNN_DATA_PARSER_H_

#include "GRNN_Data_Tag_Names.h"
#include "Component_Types.h"

#include "components/input/grnn/Classifier_Types.h"

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <vector>
#include <stack>
#include "XMLExpatParser.h"


namespace libreverse { namespace infrastructure {

    class GRNN_Data_Parser : public XMLExpatParser {
    public:

        GRNN_Data_Parser();

        virtual ~GRNN_Data_Parser(){}

	classifier_types::GRNN_Data_Map::ptr_t get_Data_Map ( std::string filename );

        virtual void startElement ( const std::string& element_name,
                                    const Attribute_Map_t& attributes );

        virtual void charData ( const std::string& element_value );

        virtual void endElement ( const std::string& element_name );

    private:

        static const int MATCH;

        classifier_types::GRNN_Data_Map::ptr_t m_data_map;
        GRNN_Data_Tag_Names m_tag;

	std::string m_type;
	double m_sigma;
        std::string m_file;

        std::stack<std::string> m_element_list;
    };
} /* namespace infrastructure */
} /* namespace libreverse */

#endif /* GRNN_DATA_PARSER_H_ */
