/*  Fat_Reader.cpp

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

#include "Fat_Reader.h"
#include "Fat_Arch.h"
#include "Fat_Header.h"
#include "Mach_File.h"
#include "Trace.h"
#include "Mach_Reader_32.h"
#include "Mach_Reader_64.h"
#include <sstream>
#include "data_containers/Memory_Map.h"

/*
#include "io/File_ID.h"
#include "io/File.h"
#include "data_containers/Memory_Map.h"
#include <sstream>
#include <list>
*/
using namespace libreverse::api;
using namespace libreverse::trace;

namespace libreverse
{
    namespace mach_module
    {

        Fat_Reader::Fat_Reader ( io_types::File_ID::ptr_t target_file )
                : m_file ( new Mach_File ( target_file ) ),
                m_need_convert ( false )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Fat_Reader (File_ID,bool,bool) constructor" );

            // Read Mach Header
            this->read_Fat_Header();
        }

        Fat_Reader::Fat_Reader ( data_types::Memory_Map::ptr_t mem_ptr,
                                 io_types::File_ID::ptr_t target_file )
                : m_file ( new Mach_File ( mem_ptr, target_file ) ),
                m_need_convert ( false ),
                m_header ( new Fat_Header() )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Fat_Reader (File_ID,bool,bool) constructor" );

            // Read Mach Header
            this->read_Fat_Header();
        }

        Fat_Reader::~Fat_Reader ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Fat_Reader destructor" );
        }


        void Fat_Reader::read_Fat_Header ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Fat_Reader::read_Fat_Header" );

            if ( ! m_file->init() )
            {
                std::cout << "Error initializing file. Checking standard output for error message."
                << std::endl;
                return;
            }

            if ( !m_header )
            {
                mach_types::Fat_Header::ptr_t new_fat_hdr_ptr ( new Fat_Header() );

                m_file->read_Fat_Header ( new_fat_hdr_ptr );

                // Fat Header is always stored in big endian order. So we must convert.
                if ( new_fat_hdr_ptr->needs_Convert() )
                {
                    new_fat_hdr_ptr->convert ();
                    m_need_convert = true;
                }

                m_header = new_fat_hdr_ptr;
            }

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Fat_Reader::read_Fat_Header" );
        }


        bool
        Fat_Reader::support_File_Type ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Fat_Reader::support_File_Type" );

            bool support_file = false;

            if ( ! m_file->init() )
            {
                std::cout << "Error initializing file. Checking standard output for error message."
                << std::endl;
                return false;
            }

            if ( ! m_header )
            {
                read_Fat_Header();
            }

            if ( m_header->is_Fat_File() )
            {
                support_file = true;
            }

            return support_file;
        }


        std::string
        Fat_Reader::get_File_Type ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Fat_Reader::get_File_Type" );

            return "java:class";
        }


        std::string
        Fat_Reader::get_Arch_Type ( void ) const
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Fat_Reader::get_Arch_Type" );

            return "java:bytecode";
        }


        data_types::Memory_Map::ptr_t
        Fat_Reader::get_Memory_Map ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Fat_Reader::get_Memory_Map" );

            this->read_Headers();

            return data_types::Memory_Map::ptr_t();
        }


        std::string
        Fat_Reader::to_String ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Fat_Reader::to_String" );

            this->read_Headers ();

            std::stringstream output;

            output << m_header->to_String();

            for ( std::vector<mach_types::Mach_Reader_32::ptr_t>::const_iterator cpos = m_32bit_files.begin();
                    cpos != m_32bit_files.end();
                    ++cpos )
            {
                output << ( *cpos )->to_String() << std::endl;
            }


            for ( std::vector<mach_types::Mach_Reader_64::ptr_t>::const_iterator cpos = m_64bit_files.begin();
                    cpos != m_64bit_files.end();
                    ++cpos )
            {
                output << ( *cpos )->to_String() << std::endl;
            }

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Fat_Reader::to_String" );

            return output.str();
        }


        io_types::Text_Data::data_type
        Fat_Reader::get_Text_Strings ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Fat_Reader::get_Text_String" );

            io_types::Text_Data::data_type output;

            this->read_Headers ();

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Fat_Reader::get_Text_String" );

            return output;
        }


        io_types::Text_Data::data_type
        Fat_Reader::get_UTF16_Strings ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Fat_Reader::get_UTF16_String" );

            io_types::Text_Data::data_type output;

            this->read_Headers ();

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Fat_Reader::get_UTF16_String" );

            return output;
        }


        std::string
        Fat_Reader::get_Section_String ( std::string name ) const
        {
            return name;
        }

        void
        Fat_Reader::read_Headers ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Fat_Reader::read_Headers" );

            this->read_Fat_Header();
            this->create_Mach_Readers();
        }


        mach_types::Fat_Header::ptr_t
        Fat_Reader::get_Header ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Fat_Reader::get_Header" );

            return m_header;
        }

        void
        Fat_Reader::create_Mach_Readers ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Fat_Reader::create_Mach_Readers" );

            if ( m_32bit_files.empty() && m_64bit_files.empty() )
            {

                std::vector<mach_types::Fat_Arch::ptr_t> fat_arch_list;

                // FOR ALL Fat_Arch objects
                for ( boost::uint32_t i = 0;
                        i < m_header->get_Number_Of_Fat_Arch();
                        ++i )
                {
                    // Create Fat_Arch object
                    mach_types::Fat_Arch::ptr_t new_fat_arch_ptr ( new Fat_Arch() );

                    // Read Fat_Arch object
                    m_file->read_Fat_Arch ( new_fat_arch_ptr, m_need_convert );

                    // Fat_Arch is always stored in big endian order. So we must convert.
                    if ( m_need_convert )
                    {
                        new_fat_arch_ptr->convert ();
                    }

                    std::cout << new_fat_arch_ptr->to_String() << std::endl;

                    fat_arch_list.push_back ( new_fat_arch_ptr );
                }

                for ( std::vector<mach_types::Fat_Arch::ptr_t>::const_iterator cpos = fat_arch_list.begin();
                        cpos != fat_arch_list.end();
                        ++cpos )
                {
                    m_file->address_Seek ( ( *cpos )->get_Offset() );

                    // Create copy of memory
                    data_types::Memory_Map::ptr_t mach_file_map_ptr ( new data_container::Memory_Map ( ( *cpos )->get_Header_Size(),
                            ( *cpos )->get_Offset() ) );

                    m_file->copy ( mach_file_map_ptr, ( *cpos )->get_Header_Size() );

                    if ( ( *cpos )->is_64bit() )
                    {
                        // Create 64-bit Mach Reader
                        mach_types::Mach_Reader_64::ptr_t new_mach_64_ptr ( new Mach_Reader_64 ( mach_file_map_ptr,
                                m_file->get_ID() ) );

                        new_mach_64_ptr->read_Headers();

                        m_64bit_files.push_back ( new_mach_64_ptr );
                    }
                    else
                    {
                        // Create 32-bit Mach Header
                        mach_types::Mach_Reader_32::ptr_t new_mach_32_ptr ( new Mach_Reader_32 ( mach_file_map_ptr,
                                m_file->get_ID() ) );

                        new_mach_32_ptr->read_Headers();

                        m_32bit_files.push_back ( new_mach_32_ptr );
                    }
                }
            }

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Fat_Reader::create_Mach_Readers" );

        }

    } /* namespace mach_module */
} /* namespace libreverse */
