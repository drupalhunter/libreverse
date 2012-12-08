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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_JAVA_TRAINING_DATA_PARSER_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_JAVA_TRAINING_DATA_PARSER_HPP_INCLUDED

#include <reverse/components/input/grnn/java_training_data.hpp>
#include <reverse/components/input/grnn/java_input_tag_names.hpp>

#include <reverse/infrastructure/xmlexpatparser.hpp>

#include <boost/shared_ptr.hpp>

#include <list>
#include <stack>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	/*! \brief XML parser for Java training data */   
	class java_training_data_parser : public infrastructure::xml_expat_parser {
	public:

	  java_training_data_parser();

	  virtual ~java_training_data_parser();

	  /*! \brief Parse the start element
	   *
	   * \param element_name XML element string
	   * \param attributes Map of XML element's attributes
	   */
	  virtual void start_element ( std::string const& element_name,
				       attribute_map_t const& attributes );
  
	  /*! \brief Process the information with a XML element */
	  virtual void char_data ( std::string const& element_value );

	  /*! \brief Process the end element
	   *
	   * \param element_name XML element string
	   */
	  virtual void end_element ( std::string const& element_name );

	  /*! \brief Recover the training set from the given file
	   *  \param target_file Input XML file name to be parsed
	   *  \return Parsed training set
	   */
	  boost::shared_ptr < training_set<java_training_data> > get_data ( std::string const& target_file );

	  /*! \brief Get the maximum values for use in normalizing the
	   *  file attributes from a Java Class file.
	   */
	  variable_map::map_t& get_max_values ( void );

	private:

	  /*! \brief Convert a std::string to unsigned integer
	   *
	   * \param element_value string value.
	   *
	   * \return unsigned integer value converted from the input
	   * string.
	   */
	  boost::uint32_t convert_string_to_uint ( std::string const& element_value);

	  /*! \brief Convert a std::string to double
	   *
	   * \param element_value string value.
	   *
	   * \return double value converted from the input string.
	   */
	  double convert_string_to_double ( std::string const& element_value );

	  /*! \brief return a string attribute from the attribute map.
	   *
	   * \param name Attribute name to be retrieved.
	   * \param attributes Map of XML element's attributes
	   * \return Retrieved string attribute.
	   */
	  std::string get_attribute ( std::string const& name,
				      attribute_map_t const& attributes );

	  /*! \brief The list of all Java_Training object is created for each <FILE> tag. */
	  boost::shared_ptr < training_data<java_training_data> > m_training_data;
      
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
	  java_input_tag_names m_tag;
      
	  /*!
	   * \brief Parse input data.
	   *
	   * Reset at the end </DATA> tag
	   */
	  boost::shared_ptr < training_set<java_training_data> > m_data;

	  /*!
	   * \brief list of maximum values for each column of input
	   *
	   * Reset at the end </DATA> tag
	   */
	  variable_map::map_t m_max_values;
	};


      } // namespace grnn
    } // namespace input 
  } // namespace components
} // namespace reverse


#endif // ifndef REVERSE_COMPONENTS_INPUT_GRNN_JAVA_TRAINING_DATA_PARSER_HPP_INCLUDED
