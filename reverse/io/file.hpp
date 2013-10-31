/*  File.h

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

#ifndef REVERSE_IO_FILE_HPP_INCLUDED
#define REVERSE_IO_FILE_HPP_INCLUDED

#include <reverse/preconditions.hpp>
#include <reverse/data_containers/memory_map.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>

#include <unicode/ucnv.h>

#include <iostream>

namespace reverse {
  namespace io {

    class file_id;

    /*!
     * \class File
     * \brief Basic file class. All specific file classes inherit from this.
     * \date 2003
     * \author Stephen Torri
     */
    class file
    {

    public:


      /*!
       * \brief Basic Constructor
       * \param filename File_ID representing the target file
       * \param path String representating the location of the target file
       * \exception FileNameException The given file name is empty
       * \exception PathNameException The given path name is empty
       */
      file ( boost::shared_ptr < const file_id >& filename );

      /*!
       * \brief Basic Constructor
       * \param file_img_ptr Memory Map containing the contents of the target file
       * \param filename File_ID representing the target file
       * \exception FileNameException The given file name is empty
       * \exception PathNameException The given path name is empty
       */
      file ( boost::shared_ptr < data_containers::memory_map>& file_img_ptr,
	     boost::shared_ptr < const file_id >& filename );


      /*!
       * \brief Default destructor
       */
      ~file ();


      /*!
       * \brief Return a reference to the File_ID
       *
       * \return Pointer to the File_ID object associated with the target file.
       */
      boost::shared_ptr < const file_id> get_id() const;

      /*!
       * \brief Initialize this class and read in file image
       */
      bool init ( void );

      /*!
       * \brief Move to the provided offset in the target file
       *
       * \param offset Unsigned integer value representing the desired offset
       *
       * \test Check to see if the Offset_Type is unsigned
       */
      template <typename Offset_Type>
      void seek ( Offset_Type offset )
      {

#ifdef LIBREVERSE_DEBUG
	trace::write_trace ( trace_area::io,
			     trace_level::detail,
			     "Entering File::seek" );
#endif /* LIBREVERSE_DEBUG */

	reverse::preconditions::is_set ( m_file_img );

	m_file_img->index_seek ( offset );


#ifdef LIBREVERSE_DEBUG
	trace::write_trace ( trace_area::io,
			     trace_level::detail,
			     "Exiting File::seek" );
#endif /* LIBREVERSE_DEBUG */

      }

      /*!
       * \brief Read a value from the present location in the target file
       *
       * \param value Pointer to where data read from the target file will be stored
       */
      template <typename value_type>
      void read ( value_type* value )
      {

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( trace_area::IO,
			     trace_level::DETAIL,
			     "Entering File::read (Value_Type)" );

	Trace::write_Trace ( trace_area::IO,
			     trace_level::DATA,
			     boost::str ( boost::format ( "(0x%1$X) Entering File::reading %2$d bit value" )
					  % m_file_img->get_Present_Position_Address()
					  % sizeof ( Value_Type ) ) );
#endif /* LIBREVERSE_DEBUG */

	reverse::preconditions::is_set ( m_file_img );

	m_file_img->read ( reinterpret_cast<boost::uint8_t*> ( value ),
			   sizeof ( value_type ) );


#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( trace_area::IO,
			     trace_level::DETAIL,
			     "Exiting File::read (Value_Type)" );
#endif /* LIBREVERSE_DEBUG */

      }

      /*!
       * \brief Read a value from the present location in the target file
       *
       * \param offset Unsigned integer value representing the desired offset
       * \param value Pointer to where data read from the target file will be stored
       */
      template < typename value_type, typename offset_type >
      void read ( value_type* value, offset_type offset )
      {

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( trace_area::IO,
			     trace_level::DETAIL,
			     "Entering File::read (Value_Type, Offset_Type)" );
#endif /* LIBREVERSE_DEBUG */


	this->seek ( offset );
	this->read ( value );


#ifdef LIBREVERSE_DEBUG
	trace::write_trace ( trace_area::io,
			     trace_level::detail,
			     "Exiting File::read (Value_Type, Offset_Type)" );
#endif /* LIBREVERSE_DEBUG */

      }

      /*!
       * \brief Read a value from the present location in the target file
       *
       * \param value Pointer to where data read from the target file will be stored
       * \param offset Unsigned integer value representing the desired offset
       * \param len Number of times the Value_Type will be read from the target file
       */
      template < typename value_type,
		 typename offset_type,
		 typename length_type >
      void read ( value_type* value,
		  offset_type offset,
		  length_type len )
      {

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( trace_area::IO,
			     trace_level::DETAIL,
			     "Entering File::read (Value_Type, Offset_Type, Length_Type)" );
#endif /* LIBREVERSE_DEBUG */

	reverse::preconditions::is_set ( m_file_img );

	this->seek ( offset );

	m_file_img->read ( static_cast<boost::uint8_t*> ( value ), len );

#ifdef LIBREVERSE_DEBUG
	trace::write_trace ( trace_area::io,
			     trace_level::detail,
			     "Exiting File::read (Value_Type, Offset_Type, Length_Type)" );
#endif /* LIBREVERSE_DEBUG */

      }

      reverse::data_containers::memory_map::const_iterator begin ( void ) const;

      reverse::data_containers::memory_map::const_iterator end ( void ) const;

      boost::shared_ptr < reverse::data_containers::memory_map> get_map_ptr ( void ) const;

      boost::uint32_t size ( void ) const;

      std::string read_utf8_string ( boost::uint32_t length );

      std::string read_utf16_string ( boost::uint32_t length );

      std::vector<UChar> read_8bit_java_unicode_string ( boost::uint32_t length );

      std::string read_string ( boost::uint32_t length );

      std::string read_null_terminated_string ( void );

    protected:

      /* ---- VARIABLES ---- */

      /*! \brief File identification */
      boost::shared_ptr < const file_id > m_file_id;

      /*! \brief File image */
      boost::shared_ptr < reverse::data_containers::memory_map > m_file_img;

    private:

      /*!
       * \brief Reads the binary image from file
       */
      void read_image ();

      UErrorCode m_error;

      UConverter* m_conv;
    };

  } // namespace io
} // namespace reverse

#endif // #ifndef REVERSE_IO_FILE_HPP_INCLUDED
