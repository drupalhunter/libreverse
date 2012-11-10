/*  Java_Training_Data_Parser.h

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

#ifndef Java_Training_Data_Parser_H
#define Java_Training_Data_Parser_H

#include "XMLExpatParser.h"
#include <list>
#include <stack>
#include <boost/shared_ptr.hpp>
#include "Java_Training_Data.h"
#include "Java_Input_Tag_Names.h"
#include "Classifier_Types.h"

namespace libreverse {

  namespace classifier {

    /*! \brief XML parser for Java training data */   
    class Java_Training_Data_Parser : public XMLExpatParser {
    public:

      Java_Training_Data_Parser();

      virtual ~Java_Training_Data_Parser();

      /*! \brief Parse the start element
       *
       * \param element_name XML element string
       * \param attributes Map of XML element's attributes
       */
      virtual void startElement ( const std::string& element_name,
	                          const Attribute_Map_t& attributes );
  
      /*! \brief Process the information with a XML element */
      virtual void charData ( const std::string& element_value );

      /*! \brief Process the end element
       *
       * \param element_name XML element string
       */
      virtual void endElement ( const std::string& element_name );

      /*! \brief Recover the training set from the given file
       *  \param target_file Input XML file name to be parsed
       *  \return Parsed training set
       */
      classifier_types::Training_Set<Java_Training_Data>::Data_List_t& get_Data ( std::string target_file );

      /*! \brief Get the maximum values for use in normalizing the
       *  file attributes from a Java Class file.
       */
      classifier_types::Variable_Map::map_type& get_Max_Values ( void );

    private:

      /*! \brief Convert a std::string to unsigned integer
       *
       * \param element_value string value.
       *
       * \return unsigned integer value converted from the input
       * string.
       */
      boost::uint32_t convert_String_To_UInt ( std::string element_value);

      /*! \brief Convert a std::string to double
       *
       * \param element_value string value.
       *
       * \return double value converted from the input string.
       */
      double convert_String_To_Double ( std::string element_value );

      /*! \brief return a string attribute from the attribute map.
       *
       * \param name Attribute name to be retrieved.
       * \param attributes Map of XML element's attributes
       * \return Retrieved string attribute.
       */
      std::string get_Attribute ( std::string name,
                                  const Attribute_Map_t& attributes );

      /*! \brief The list of all Java_Training object is created for each <FILE> tag. */
      classifier_types::Training_Data<Java_Training_Data>::ptr_t m_training_data;
      
      /*! \brief Marker used to keep track of where we are in the
       *  constant pool. It is reset every time a <FILE> tage is
       *  seen.
       */
      boost::uint32_t m_constant_pool_index;

      /*!
       * \brief The XML element stack.
       *
       * There is no need to reset this variable since it will always
       * be reset during normal operations.
       */
      std::stack<std::string> m_element_list;
      
      /*!
       * \brief Handle to the XML element names
       */
      Java_Input_Tag_Names m_tag;
      
      /*!
       * \brief Parse input data.
       *
       * Reset at the end </DATA> tag
       */
      classifier_types::Training_Set<Java_Training_Data>::Data_List_t m_data;

      /*!
       * \brief list of maximum values for each column of input
       *
       * Reset at the end </DATA> tag
       */
      classifier_types::Variable_Map::map_type m_max_values;
    };

  } /* namespace classifier */
} /* namespace classifier */

#endif /* Java_Training_Data_Parser_H */
