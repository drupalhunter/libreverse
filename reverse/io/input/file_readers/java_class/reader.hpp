/*  Reader.h

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

#ifndef REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_READER_HPP_INCLUDED
#define REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_READER_HPP_INCLUDED

#include <reverse/io/input/file_readers/file_reader.hpp>

#include <boost/shared_ptr.hpp>

namespace reverse {

  namespace data_container {
    class memory_map;
  } // namespace data_container

  namespace io {

    class file_id;

    namespace input {
      namespace file_readers {
	namespace java_class {

	  class header;

	  /*!
	   * \class Reader
	   * \date 2003
	   * \author Stephen Torri
	   */
	  class reader : public io::file_reader {
	  public:

	    /*!
	     * \brief Default Constructor
	     * \param target_file The file to be used for decompiling
	     */
	    reader ( boost::shared_ptr < const file_id > target_file );

	    /*!
	     * \brief Default Destructor
	     */
	    virtual ~reader();

	    virtual bool support_file_type ( void );

	    virtual void read_headers ( void );

	    virtual boost::shared_ptr < data_container::memory_map > get_memory_map ( void );

	    /*!
	     * \brief Print out the entire file contents
	     */
	    virtual std::string to_string (void);

	    /*!
	     * \brief Get human readable strings
	     */
	    virtual std::vector < std::string > get_text_strings (void);
	    
	    /*!
	     * \brief Get UTF-16 strings
	     */
	    virtual std::vector < std::string > get_utf16_strings (void);

	    virtual std::string get_section_string ( std::string name ) const;

	    boost::shared_ptr < java_class::class_header > get_header (void);

	    /*!
	     * \brief Return the File Type of the target file
	     */
	    virtual std::string get_file_type (void);

	    /*
	     * !\brief Return the Architecture Type of the target file
	     */
	    std::string get_arch_type (void) const;

	  private:

	    /*---------------
	     *   Variables
	     *---------------*/
	    /*! \brief JAVA File handle */
	    boost::shared_ptr < java_class::class_file > m_file;

	    boost::shared_ptr < java_class::header > m_hdr_ptr;

	  public:

	    /*---------------
	     *   Functions
	     *---------------*/

	    /*!
	     * \brief Get the JAVA Header from the file
	     */
	    void read_class_header (void);

	  };

	} // namespace java_class
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

#endif // #ifndef REVERSE_IO_INPUT_FILE_READERS_JAVA_CLASS_READER_HPP_INCLUDED
