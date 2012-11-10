/*  Windows_Training_Data_Parser.h

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

#ifndef Windows_Training_Data_Parser_H
#define Windows_Training_Data_Parser_H

#include "XMLExpatParser.h"
#include "Windows_Input_Tag_Names.h"
#include "Windows_Training_Data.h"
#include "Classifier_Types.h"
#include "Training_Data.h"

#include <list>
#include <string>
#include <stack>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

#ifdef LIBREVERSE_DEBUG
#include "Reverse.h"
#include "Trace.h"

using namespace libreverse::api;
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse {

  namespace classifier {

    class Windows_Training_Data_Parser : public XMLExpatParser {
    public:

      Windows_Training_Data_Parser();

      virtual ~Windows_Training_Data_Parser();

      virtual void startElement ( const std::string& element_name,
	                          const Attribute_Map_t& attributes );
  
      virtual void charData ( const std::string& element_value );

      virtual void endElement ( const std::string& element_name );

      classifier_types::Training_Set<Windows_Training_Data>::Data_List_t get_Data ( std::string target_file );

    private:

      boost::uint32_t convert_String_To_UInt ( std::string );

      float convert_String_To_Float ( std::string );

      std::string get_Attribute ( std::string name,
                                  const Attribute_Map_t& attributes );

      template < typename Tag_Value_Type, typename Attribute_Type, typename Element_Type >
      void process_Value ( Tag_Value_Type tag_value, Attribute_Type attrib_value, Element_Type element_value )
      {
	  Trace::write_Trace ( TraceArea::GRNN_PARSER,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "Processing %s% tag" ) % tag_value ) );

	  m_training_data->set_Attribute ( attrib_value,
					   convert_String_To_Float ( element_value ) );
      }

      // A Windows_Training object is created for each <FILE> tag
      // Reset at the end </FILE> tag
      classifier_types::Training_Data<Windows_Training_Data>::ptr_t m_training_data;
      
      // There is no need to reset this variable since it will
      // always be reset during normal operations.
      std::stack<std::string> m_element_list;
      
      // Constant variable
      Windows_Input_Tag_Names m_tag;
      
      // Reset at the end </DATA> tag
      classifier_types::Training_Set<Windows_Training_Data>::Data_List_t m_data;
    };

  } /* namespace classifier */
} /* namespace classifier */

#endif /* Windows_Training_Data_Parser_H */
