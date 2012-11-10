/*  Reader_Factory.cpp

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

#include <reverse/io/input/File_Readers/Reader_Factory.h>
#include "io/input/File_Readers/Elf/Elf_Reader_32.h"
#include "io/input/File_Readers/Elf/Elf_Reader_64.h"
#include "io/input/File_Readers/Windows_PE/Reader_32.h"
#include "io/input/File_Readers/Windows_PE/Reader_64.h"
#include "io/input/File_Readers/Java_Class/Reader.h"
#include "io/input/File_Readers/Mach/Mach_Reader_32.h"
#include "io/input/File_Readers/Mach/Mach_Reader_64.h"
#include "io/input/File_Readers/Mach/Fat_Reader.h"
#include "io/File_ID.h"
#include "File_Reader.h"
#include "errors/API_Exception.h"

namespace reverse {
  namespace io {
    namespace input {
      namespace File_Readers {

        Reader_Factory&
        Reader_Factory::Instance ( void )
        {
	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DETAIL,
			       "Inside Reader_Factory::Instance()" );
	  
            static Reader_Factory fact_obj;
            return fact_obj;
        }

        Reader_Factory::Reader_Pair_t
        Reader_Factory::create_Elf_Reader ( boost::shared_ptr < const File_ID >& target_file )
        {
	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DETAIL,
			       "Inside Reader_Factory::create_Elf_Reader()" );

	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "target file: %1%" ) % target_file->get_Full_Name() ) );


            // try 32-bit
            elf_module::Elf_Reader_32::ptr_t tmp32_ptr ( new elf_module::Elf_Reader_32 ( target_file ) );

            if ( tmp32_ptr->support_File_Type () )
            {
                return std::make_pair ( tmp32_ptr, true );
            }
            else
            {
                return std::make_pair ( tmp32_ptr, false );
            }
        }

        Reader_Factory::Reader_Pair_t
        Reader_Factory::create_WPEF_Reader ( boost::shared_ptr < const File_ID >& target_file )
        {
	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DETAIL,
			       "Inside Reader_Factory::create_WPEF_Reader()" );

	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "target file: %1%" ) % target_file->get_Full_Name() ) );

            wpef_module::Reader_32::ptr_t tmp_ptr ( new wpef_module::Reader_32 ( target_file ) );

            if ( tmp_ptr->support_File_Type () )
            {
                return std::make_pair ( tmp_ptr, true );
            }

            // Try 64-bit PE Reader
            wpef_module::Reader_64::ptr_t tmp2_ptr ( new wpef_module::Reader_64 ( target_file ) );

            if ( tmp2_ptr->support_File_Type () )
            {
                return std::make_pair ( tmp2_ptr, true );
            }
            else
            {
                wpef_module::Reader_32::ptr_t null_ptr;
                return std::make_pair ( null_ptr, false );
            }
        }

        Reader_Factory::Reader_Pair_t
        Reader_Factory::create_Java_Reader ( boost::shared_ptr < const File_ID >& target_file )
        {
	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DETAIL,
			       "Inside Reader_Factory::create_Java_Reader()" );

	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "target file: %1%" ) % target_file->get_Full_Name() ) );

            java_module::Reader::ptr_t tmp_ptr ( new java_module::Reader ( target_file ) );

            if ( tmp_ptr->support_File_Type () )
            {
                return std::make_pair ( tmp_ptr, true );
            }
            else
            {
                return std::make_pair ( tmp_ptr, false );
            }
        }

        Reader_Factory::Reader_Pair_t
        Reader_Factory::create_Mach_Reader ( boost::shared_ptr < const File_ID >& target_file )
        {
	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DETAIL,
			       "Inside Reader_Factory::create_Mach_Reader()" );

	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "target file: %1%" ) % target_file->get_Full_Name() ) );

            mach_module::Mach_Reader_32::ptr_t tmp_ptr ( new mach_module::Mach_Reader_32 ( target_file ) );

            if ( tmp_ptr->support_File_Type () )
            {
                return std::make_pair ( tmp_ptr, true );
            }

            // Try 64-bit Mach Reader
            mach_module::Mach_Reader_64::ptr_t tmp2_ptr ( new mach_module::Mach_Reader_64 ( target_file ) );

            if ( tmp2_ptr->support_File_Type () )
            {
                return std::make_pair ( tmp2_ptr, true );
            }
            else
            {
                mach_module::Mach_Reader_32::ptr_t null_ptr;
                return std::make_pair ( null_ptr, false );
            }
        }

        Reader_Factory::Reader_Pair_t
        Reader_Factory::create_Mach_Fat_Reader ( boost::shared_ptr < const File_ID >& target_file )
        {
	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DETAIL,
			       "Inside Reader_Factory::create_Mach_Fat_Reader()" );

	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "target file: %1%" ) % target_file->get_Full_Name() ) );

            mach_module::Fat_Reader::ptr_t tmp_ptr ( new mach_module::Fat_Reader ( target_file ) );

            if ( tmp_ptr->support_File_Type () )
            {
                return std::make_pair ( tmp_ptr, true );
            }
            else
            {
                return std::make_pair ( tmp_ptr, false );
            }
        }


        io_types::File_Reader::ptr_t
        Reader_Factory::create_File_Reader ( std::string filename )
        {
            bool found = false;

	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DETAIL,
			       "Inside Reader_Factory::create_File_Reader()" );

	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DATA,
			       boost::str ( boost::format ( "target file: %1%" ) % filename ) );

            Reader_Factory::Reader_Pair_t reader_pair;

            // Search for existing reader
            Reader_Map_t::iterator pos = m_reader_map.find ( filename );

            if ( pos == m_reader_map.end() )
            {
                // Going through each type find a reader that supports the file
                // and return it.
	      boost::shared_ptr < const File_ID > target_ptr = make_shared<File_ID> ( filename );

                reader_pair = this->create_Elf_Reader ( target_ptr );
                if ( reader_pair.second )
                {
                    return reader_pair.first;
                }

                // If no match, check WPEF reader
                reader_pair = this->create_WPEF_Reader ( target_ptr );
                if ( reader_pair.second )
                {
                    return reader_pair.first;
                }

                // If no match, check JAVA reader
                reader_pair = this->create_Java_Reader ( target_ptr );
                if ( reader_pair.second )
                {
                    return reader_pair.first;
                }

                // If no match, check MACH reader
                reader_pair = this->create_Mach_Reader ( target_ptr );
                if ( reader_pair.second )
                {
                    return reader_pair.first;
                }

                // If no match, check MACH Fat reader
                reader_pair = this->create_Mach_Fat_Reader ( target_ptr );
                if ( reader_pair.second )
                {
                    return reader_pair.first;
                }

                if ( ! found )
		  {
		    Trace::write_Trace ( TraceArea::IO,
					 TraceLevel::ERROR,
					 boost::str ( boost::format ( "Unsupported file type: %s" ) % filename ) );

		    Trace::write_Trace ( TraceArea::IO,
					 TraceLevel::ERROR,
					 boost::str ( boost::format ( "Exception throw in %s at line %d" )
						      % __FILE__
						      % __LINE__ ) );

                    // Exception: Unsupported filetype
                    // throw file type not supported.
                    throw errors::File_Reader_Exception ( errors::File_Reader_Exception::UNSUPPORTED_FILE_TYPE );
                }
                else
                {
                    if ( ( m_reader_map.insert ( std::make_pair ( filename, reader_pair.first ) ) ).second == false )
                    {
		    Trace::write_Trace ( TraceArea::IO,
					 TraceLevel::ERROR,
					 boost::str ( boost::format ( "Found a duplicate reader for %s" ) % filename ) );

		    Trace::write_Trace ( TraceArea::IO,
					 TraceLevel::ERROR,
					 boost::str ( boost::format ( "Exception throw in %s at line %d" )
						      % __FILE__
						      % __LINE__ ) );

                        throw errors::API_Exception ( errors::API_Exception::INTERNAL_LIBRARY_ERROR );
                    }
                }
            }
            else
            {
                reader_pair.first = ( *pos ).second;
            }

            return reader_pair.first;
        }

        void Reader_Factory::clear_Reader ( std::string filename )
        {
	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::DETAIL,
			       "Inside Reader_Factory::clear_Reader(string)" );

	  Trace::write_Trace ( TraceArea::IO,
			       TraceLevel::ERROR,
			       boost::str ( boost::format ( "Erasing entry for file: %s" ) % filename ) );

            m_reader_map.erase ( filename );
        }

      } // namespace File_Readers
    } // namespace input
  } // namespace io
} // namespace reverse
