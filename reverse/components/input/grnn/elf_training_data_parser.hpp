/*  Elf_Training_Data_Parser.h

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

#ifndef Elf_Training_Data_Parser_H
#define Elf_Training_Data_Parser_H

#include "XMLExpatParser.h"
#include <list>
#include <stack>
#include <boost/shared_ptr.hpp>
#include "Elf_Training_Data.h"
#include "Elf_Input_Tag_Names.h"
#include "Classifier_Types.h"

namespace libreverse {

  namespace classifier {
   
    class Elf_Training_Data_Parser : public XMLExpatParser {
    public:

      Elf_Training_Data_Parser();

      virtual ~Elf_Training_Data_Parser();

      virtual void startElement ( const std::string& element_name,
	                          const Attribute_Map_t& attributes );
  
      virtual void charData ( const std::string& element_value );

      virtual void endElement ( const std::string& element_name );

      classifier_types::Training_Set<Elf_Training_Data>::Data_List_t& get_Data ( std::string target_file );

      classifier_types::Variable_Map::map_type& get_Max_Values ( void );

    private:

      boost::uint32_t convert_String_To_UInt ( std::string );

      double convert_String_To_Double ( std::string );

      std::string get_Attribute ( std::string name,
                                  const Attribute_Map_t& attributes );

      // A Elf_Training object is created for each <FILE> tag
      // Reset at the end </FILE> tag
      classifier_types::Training_Data<Elf_Training_Data>::ptr_t m_training_data;
      
      // There is no need to reset this variable since it will
      // always be reset during normal operations.
      std::stack<std::string> m_element_list;
      
      // Constant variable
      Elf_Input_Tag_Names m_tag;
      
      // Reset at the end </DATA> tag
      classifier_types::Training_Set<Elf_Training_Data>::Data_List_t m_data;
      classifier_types::Variable_Map::map_type m_max_values;
    };

  } /* namespace classifier */
} /* namespace classifier */

#endif /* Elf_Training_Data_Parser_H */
