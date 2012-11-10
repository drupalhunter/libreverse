/*  Elf_Training_Data.h

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

#ifndef ELF_TRAINING_DATA_H
#define ELF_TRAINING_DATA_H

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <string>

#include "Classifier_Types.h"
#include "Variable_Map.h"

namespace libreverse
{
  namespace classifier
  {
    class Elf_Training_Data
    {
    public:

      static const boost::uint8_t ATTRIBUTE_COUNT;
      static const boost::uint8_t CLASSIFIER_TARGET;

      enum Attributes
        {
	  ATTRIBUTE_TARGET_ID = 0,
	  ATTRIBUTE_FILESIZE = 1,
	  ATTRIBUTE_ENTRY_POINT_ADDRESS = 2,
	  ATTRIBUTE_SECTION_HEADERS_START = 3,
	  ATTRIBUTE_PROGRAM_HEADER_COUNT = 4,
	  ATTRIBUTE_SECTION_HEADER_COUNT = 5,
	  ATTRIBUTE_SECTION_HEADER_STRING_TABLE_INDEX = 6,
	  ATTRIBUTE_TEXT_SECTION_SIZE = 7
        };

      friend class Elf_Training_Data_Parser;

      Elf_Training_Data ();

      ~Elf_Training_Data();

      static std::string get_Attribute_String_List ( classifier_types::Configuration<Elf_Training_Data>::ptr_t config );

      std::string to_String ( classifier_types::Configuration<Elf_Training_Data>::ptr_t config ) const;

      std::string to_XML ( classifier_types::Configuration<Elf_Training_Data>::ptr_t config ) const;
      
      classifier_types::Variable_Map::map_type::const_iterator begin ( void ) const;
      classifier_types::Variable_Map::map_type::iterator begin ( void );

      classifier_types::Variable_Map::map_type::const_iterator end ( void ) const;
      classifier_types::Variable_Map::map_type::iterator end ( void );

      void set_Attribute ( boost::uint32_t index, double value );

      double get_Attribute ( boost::uint32_t index );

      bool empty ( void ) const;

    private:

      classifier::Variable_Map m_data;
    };

  } /* namespace classifier */
} /* namespace libreverse */

#endif /* ELF_TRAINING_DATA_H */
