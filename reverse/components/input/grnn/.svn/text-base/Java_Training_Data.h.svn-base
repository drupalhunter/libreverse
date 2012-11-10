/*  Java_Training_Data.h

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

#ifndef JAVA_TRAINING_DATA_H
#define JAVA_TRAINING_DATA_H

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <string>

#include "Classifier_Types.h"
#include "Variable_Map.h"

namespace libreverse
{
  namespace classifier
  {
    class Java_Training_Data
    {
    public:

      static const boost::uint8_t ATTRIBUTE_COUNT;
      static const boost::uint8_t CLASSIFIER_TARGET;

      enum Attributes
        {
	  ATTRIBUTE_TARGET_ID = 0,
	  ATTRIBUTE_FILESIZE = 1,
	  ATTRIBUTE_THIS_INDEX = 2,
	  ATTRIBUTE_SUPER_INDEX = 3,
	  ATTRIBUTE_VERSION = 4,
	  ATTRIBUTE_CONSTANT_POOL_COUNT = 5,

	  // Constant Pool Info
	  // #1 - Constant_UTF
	  ATTRIBUTE_CONSTANT_UTF8_COUNT = 6,
	  ATTRIBUTE_CONSTANT_UTF8_RATIO = 7,

	  // #2 - Constant_RESERVED
	  ATTRIBUTE_CONSTANT_RESERVED_COUNT = 8,
	  ATTRIBUTE_CONSTANT_RESERVED_RATIO = 9,

	  // #3 - Constant_INTEGER
	  ATTRIBUTE_CONSTANT_INTEGER_COUNT = 10,
	  ATTRIBUTE_CONSTANT_INTEGER_RATIO = 11,

	  // #4 - Constant_FLOAT
	  ATTRIBUTE_CONSTANT_FLOAT_COUNT = 12,
	  ATTRIBUTE_CONSTANT_FLOAT_RATIO = 13,

	  // #5 - Constant_LONG
	  ATTRIBUTE_CONSTANT_LONG_COUNT = 14,
	  ATTRIBUTE_CONSTANT_LONG_RATIO = 15,

	  // #6 - Constant_DOUBLE
	  ATTRIBUTE_CONSTANT_DOUBLE_COUNT = 16,
	  ATTRIBUTE_CONSTANT_DOUBLE_RATIO = 17,

	  // #7 - Constant_CLASS
	  ATTRIBUTE_CONSTANT_CLASS_COUNT = 18,
	  ATTRIBUTE_CONSTANT_CLASS_RATIO = 19,

	  // #8 - Constant_STRING
	  ATTRIBUTE_CONSTANT_STRING_COUNT = 20,
	  ATTRIBUTE_CONSTANT_STRING_RATIO = 21,

	  // #9 - Constant_FIELDREF
	  ATTRIBUTE_CONSTANT_FIELDREF_COUNT = 22,
	  ATTRIBUTE_CONSTANT_FIELDREF_RATIO = 23,

	  // #10 - Constant_METHODREF
	  ATTRIBUTE_CONSTANT_METHODREF_COUNT = 24,
	  ATTRIBUTE_CONSTANT_METHODREF_RATIO = 25,

	  // #11 - Constant_INTERFACE_METHODREF
	  ATTRIBUTE_CONSTANT_INTERFACE_METHODREF_COUNT = 26,
	  ATTRIBUTE_CONSTANT_INTERFACE_METHODREF_RATIO = 27,

	  // #12 - Constant_NAME_AND_TYPE
	  ATTRIBUTE_CONSTANT_NAME_AND_TYPE_COUNT = 28,
	  ATTRIBUTE_CONSTANT_NAME_AND_TYPE_RATIO = 29,

	  ATTRIBUTE_FIELD_COUNT = 30,
	  ATTRIBUTE_METHOD_COUNT = 31
        };

      enum Constant_Pool_Tags
        {
	  // Map index
	  UTF8_TAG = 1,
	  RESERVED_TAG =2,
	  INTEGER_TAG = 3,
	  FLOAT_TAG = 4,
	  LONG_TAG = 5,
	  DOUBLE_TAG = 6,
	  CLASS_TAG = 7,
	  STRING_TAG = 8,
	  FIELDREF_TAG = 9,
	  METHODREF_TAG = 10,
	  INTERFACE_METHODREF_TAG = 11,
	  NAME_AND_TYPE_TAG = 12
        };

      friend class Java_Training_Data_Parser;

      Java_Training_Data ();

      ~Java_Training_Data();

      static std::string get_Attribute_String_List ( classifier_types::Configuration<Java_Training_Data>::ptr_t config );

      std::string to_String ( classifier_types::Configuration<Java_Training_Data>::ptr_t config ) const;

      std::string to_XML ( classifier_types::Configuration<Java_Training_Data>::ptr_t config ) const;
      
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

#endif /* JAVA_TRAINING_DATA_H */
