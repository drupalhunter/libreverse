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


#ifndef REVERSE_INFRASTRUCTURE_CONFIGURATION_PARSER_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_CONFIGURATION_PARSER_HPP_INCLUDED

#include <reverse/infrastructure/configuration_tag_names.hpp>

#include <expatpp.h>

#include <string>
#include <stack>

namespace reverse {
  namespace infrastructure {

    class configuration_data;

    class configuration_parser : public expatpp {
    public:

      explicit configuration_parser ( std::string file = "" );
      
      virtual ~configuration_parser();

      boost::shared_ptr < infrastructure::configuration_data > parse_data (void);

      virtual void startElement ( const XML_Char* element_name,
				  const XML_Char** attributes );
      
      virtual void charData ( const std::string& element_value );

      virtual void endElement ( const std::string& element_name );

      std::string get_configuration_file (void) const;

    private:

      std::string m_file;
      configuration_tag_names m_tag;
      std::string m_host;
      std::string m_user;
      std::string m_password;
      
      std::stack<std::string> m_element_list;

      boost::shared_ptr < infrastructure::configuration_data > m_data_ptr;
    };

  } /* namespace infrastructure */
} /* namespace reverse */

#endif /* REVERSE_INFRASTRUCTURE_CONFIGURATION_PARSER_HPP_INCLUDED */
