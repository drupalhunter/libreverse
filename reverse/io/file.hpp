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

#include <reverse/Preconditions.h>
#include <reverse/data_containers/Memory_Map.h>

#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>

#include <unicode/ucnv.h>

#include <iostream>

namespace reverse {
  namespace io {

    class File_ID;

    /*!
     * \class File
     * \brief Basic file class. All specific file classes inherit from this.
     * \date 2003
     * \author Stephen Torri
     */
    class File
    {

    public:


      /*!
       * \brief Basic Constructor
       * \param filename File_ID representing the target file
       * \param path String representating the location of the target file
       * \exception FileNameException The given file name is empty
       * \exception PathNameException The given path name is empty
       */
      File ( boost::shared_ptr < const File_ID >& filename );

      /*!
       * \brief Basic Constructor
       * \param file_img_ptr Memory Map containing the contents of the target file
       * \param filename File_ID representing the target file
       * \exception FileNameException The given file name is empty
       * \exception PathNameException The given path name is empty
       */
      File ( boost::shared_ptr < data_container::Memory_Map>& file_img_ptr,
	     boost::shared_ptr < const File_ID >& filename );


      /*!
       * \brief Default destructor
       */
      ~File ();


      /*!
       * \brief Return a reference to the File_ID
       *
       * \return Pointer to the File_ID object associated with the target file.
       */
      boost::shared_ptr < const File_ID> get_ID() const;

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
	Trace::write_Trace ( TraceArea::IO,
			     trace_level::DETAIL,
			     "Entering File::seek" );
#endif /* LIBREVERSE_DEBUG */

	reverse::Preconditions::is_set ( m_file_img );

	m_file_img->index_Seek ( offset );


#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( TraceArea::IO,
			     trace_level::DETAIL,
			     "Exiting File::seek" );
#endif /* LIBREVERSE_DEBUG */

      }

      /*!
       * \brief Read a value from the present location in the target file
       *
       * \param value Pointer to where data read from the target file will be stored
       */
      template <typename Value_Type>
      void read ( Value_Type* value )
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

	reverse::Preconditions::is_set ( m_file_img );

	m_file_img->read ( reinterpret_cast<boost::uint8_t*> ( value ),
			   sizeof ( Value_Type ) );


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
      template < typename Value_Type, typename Offset_Type >
      void read ( Value_Type* value, Offset_Type offset )
      {

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( trace_area::IO,
			     trace_level::DETAIL,
			     "Entering File::read (Value_Type, Offset_Type)" );
#endif /* LIBREVERSE_DEBUG */


	this->seek ( offset );
	this->read ( value );


#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( trace_area::IO,
			     trace_level::DETAIL,
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
      template < typename Value_Type,
		 typename Offset_Type,
		 typename Length_Type >
      void read ( Value_Type* value,
		  Offset_Type offset,
		  Length_Type len )
      {

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( trace_area::IO,
			     trace_level::DETAIL,
			     "Entering File::read (Value_Type, Offset_Type, Length_Type)" );
#endif /* LIBREVERSE_DEBUG */

	reverse::Preconditions::is_set ( m_file_img );

	this->seek ( offset );

	m_file_img->read ( static_cast<boost::uint8_t*> ( value ), len );

#ifdef LIBREVERSE_DEBUG
	Trace::write_Trace ( trace_area::IO,
			     trace_level::DETAIL,
			     "Exiting File::read (Value_Type, Offset_Type, Length_Type)" );
#endif /* LIBREVERSE_DEBUG */

      }

      reverse::data_container::Memory_Map::const_iterator begin ( void ) const;

      reverse::data_container::Memory_Map::const_iterator end ( void ) const;

      boost::shared_ptr < const reverse::data_container::Memory_Map> get_Map_Ptr ( void ) const;

      boost::uint32_t size ( void ) const;

      std::string read_UTF8_String ( boost::uint32_t length );

      std::string read_UTF16_String ( boost::uint32_t length );

      std::vector<UChar> read_8bit_Java_Unicode_String ( boost::uint32_t length );

      std::string read_String ( boost::uint32_t length );

      std::string read_Null_Terminated_String ( void );

    protected:

      /* ---- VARIABLES ---- */

      /*! \brief File identification */
      boost::shared_ptr < const File_ID> m_file_id;

      /*! \brief File image */
      boost::shared_ptr < reverse::data_container::Memory_Map > m_file_img;

    private:

      /*!
       * \brief Reads the binary image from file
       */
      void read_Image ();

      UErrorCode m_error;

      UConverter* m_conv;
    };

    } // namespace io
} // namespace reverse

#endif // #ifndef REVERSE_IO_FILE_HPP_INCLUDED
