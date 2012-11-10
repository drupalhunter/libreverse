/*  Configuration_Parser.h

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


#ifndef CONFIGURATION_PARSER_H_
#define CONFIGURATION_PARSER_H_

#include "Configuration_Tag_Names.h"
#include "Component_Types.h"
#include <string>
#include <stack>
#include "XMLExpatParser.h"

namespace libreverse { namespace infrastructure {

    class Configuration_Parser : public XMLExpatParser {
    public:

        explicit Configuration_Parser ( std::string file = "" );

        virtual ~Configuration_Parser();

        infrastructure_types::Configuration_Data::ptr_t parse_Data (void);

        virtual void startElement ( const std::string& element_name,
                                    const Attribute_Map_t& attributes );

        virtual void charData ( const std::string& element_value );

        virtual void endElement ( const std::string& element_name );

        std::string get_Configuration_File (void) const;

    private:

        std::string m_file;
        Configuration_Tag_Names m_tag;
        std::string m_host;
        std::string m_user;
        std::string m_password;

        std::stack<std::string> m_element_list;

        infrastructure_types::Configuration_Data::ptr_t m_data_ptr;
    };

} /* namespace infrastructure */
} /* namespace libreverse */

#endif /* CONFIGURATION_PARSER_H_ */
