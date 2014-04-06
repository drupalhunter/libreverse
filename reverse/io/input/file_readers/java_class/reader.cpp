/*  Reader.cpp

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

/*
  Code for most of this file was obtained from the GNU Binutils
  readelf.c file. Below is the copyright for the original code. The
  original code was used as a inspiration on how to design an Elf
  file reader. I give full credit of this excellent set of code to
  the original developers. Thanks for the hard work.

  Copyright 1998, 1999, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

  Originally developed by Eric Youngdale <eric@andante.jic.com>
  Modifications by Nick Clifton <nickc@redhat.com>

  This file is part of GNU Binutils.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
*/

#include "Reader.h"
#include "Header.h"
#include "Class_File.h"
#include "Class_Header.h"
#include "Java_Meta_Info.h"

#include "io/File_ID.h"
#include "io/File.h"
#include "data_containers/memory_map.h"

#include <sstream>
#include <list>

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace reverse::api;
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse {
  namespace io {
    namespace input {
      namespace file_readers {
	namespace java_class {

    Reader::Reader ( io_types::File_ID::const_ptr_t target_file )
        : m_file ( new Class_File ( target_file ) ),
	  m_hdr_ptr ( new Header() )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Reader (File_ID) constructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    Reader::~Reader (void)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Reader destructor" );
#endif /* LIBREVERSE_DEBUG */

    }

    void Reader::read_Class_Header (void)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Reader::read_Class_Header" );
#endif /* LIBREVERSE_DEBUG */


        m_file->init();

        java_types::Class_Header::ptr_t class_hdr_ptr = m_hdr_ptr->get_Class_Header();

        if ( class_hdr_ptr.get() == 0 )
            {
                java_types::Class_Header::ptr_t new_class_hdr_ptr ( new Class_Header() );

                m_file->read_Class_Header ( new_class_hdr_ptr );


#ifdef LIBREVERSE_DEBUG
                Trace::write_Trace ( TraceArea::IO,
                                     TraceLevel::DATA,
                                     boost::str ( boost::format ( "Java Reader - read_Class_Header:\n%1%" ) % new_class_hdr_ptr->to_String() ) );
#endif /* LIBREVERSE_DEBUG */


                m_hdr_ptr->set_Class_Header ( new_class_hdr_ptr );
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Reader::read_Class_Header" );
#endif /* LIBREVERSE_DEBUG */

    }

    bool
    Reader::support_File_Type ( void )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Reader::support_File_Type" );
#endif /* LIBREVERSE_DEBUG */


        bool java_support = false;

        java_types::Class_Header::ptr_t class_hdr_ptr = m_hdr_ptr->get_Class_Header();

        if ( class_hdr_ptr.get() == 0 )
            {
                read_Class_Header ();

                class_hdr_ptr = m_hdr_ptr->get_Class_Header();
            }

        if ( class_hdr_ptr->is_Java_File() )
            {
                java_support = true;
            }


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Reader::support_File_Type" );
#endif /* LIBREVERSE_DEBUG */


        return java_support;
    }

    std::string
    Reader::get_Section_String ( std::string name ) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Reader::get_Section_String" );
#endif /* LIBREVERSE_DEBUG */


        return name;
    }

    std::string
    Reader::get_File_Type (void)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Reader::get_File_Type" );
#endif /* LIBREVERSE_DEBUG */

        return Java_Meta_Info::FILE_TYPE;
    }

    std::string
    Reader::get_Arch_Type (void) const
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Reader::get_Arch_Type" );
#endif /* LIBREVERSE_DEBUG */


    	return "java:bytecode";
    }

    data_types::memory_map::ptr_t
    Reader::get_memory_map ( void )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Reader::get_memory_map" );
#endif /* LIBREVERSE_DEBUG */


        return (m_file->get_File()).get_Map_Ptr();
    }

    std::string
    Reader::to_String (void)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Reader::to_String" );
#endif /* LIBREVERSE_DEBUG */


        this->read_Class_Header ();

        std::string output = m_hdr_ptr->to_String();


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Reader::to_String" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }

    io_types::Text_Data::data_type
    Reader::get_Text_Strings ( void )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Reader::get_Text_String" );
#endif /* LIBREVERSE_DEBUG */


        io_types::Text_Data::data_type output;

        this->read_Class_Header ();

        // Do work here to read human readable strings
        java_types::Class_Header::ptr_t header_ptr = m_hdr_ptr->get_Class_Header();

        output = header_ptr->get_Text_Strings();


#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Reader::get_Text_String" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }

    io_types::Text_Data::data_type
    Reader::get_UTF16_Strings ( void )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Entering Reader::get_UTF16_String" );
#endif /* LIBREVERSE_DEBUG */


        io_types::Text_Data::data_type output;

        // NOTE: Java stores its strings in a SUN UTF-8 format not the
        // specification UTF-8. I do not think we need to process the
        // class file looking for UTF-16 strings.

        // Do work here to read human readable strings

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Exiting Reader::get_UTF16_String" );
#endif /* LIBREVERSE_DEBUG */


        return output;
    }

    void
    Reader::read_Headers ( void )
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Reader::read_Headers" );
#endif /* LIBREVERSE_DEBUG */


        this->read_Class_Header();
    }

    java_types::Class_Header::ptr_t
    Reader::get_Header (void)
    {

#ifdef LIBREVERSE_DEBUG
        Trace::write_Trace ( TraceArea::IO,
                             TraceLevel::DETAIL,
                             "Inside Reader::get_Header" );
#endif /* LIBREVERSE_DEBUG */


        return m_hdr_ptr->get_Class_Header();
    }

	} // namespace java_class
      } // namespace file_readers
    } // namespace input
  } // namespace io
} // namespace reverse

