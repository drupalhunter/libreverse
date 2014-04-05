/*  Mach_Reader_32.cpp

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

#include "Mach_Meta_Info.h"
#include "Mach_Reader_32.h"
#include "Mach_Header_32.h"
#include "Load_Command_Factory.h"
#include "Load_Command.h"

#include "Trace.h"
#include "Reverse.h"
#include "io/Byte_Converter.h"

#include <boost/format.hpp>
#include <sstream>

using namespace reverse::trace;
using namespace reverse::api;

namespace reverse
{
    namespace mach_module
    {

        Mach_Reader_32::Mach_Reader_32 ( io_types::File_ID::const_ptr_t target_file )
                : m_header ( new Mach_Header_32 () ),
                m_file ( target_file ),
                m_convert ( false )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Mach_Reader_32 (File_ID,bool,bool) constructor" );
        }


        Mach_Reader_32::Mach_Reader_32 ( data_types::memory_map::ptr_t mem_ptr,
                                         io_types::File_ID::const_ptr_t target_file )
                : m_header ( new Mach_Header_32() ),
                m_file ( mem_ptr, target_file ),
                m_convert ( false )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Mach_Reader_32 (File_ID,bool,bool) constructor" );
        }


        Mach_Reader_32::~Mach_Reader_32 ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Mach_Reader_32 destructor" );
        }


        bool
        Mach_Reader_32::support_File_Type ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_Reader_32::support_File_Type" );

            bool support_file = false;

            if ( m_header->is_Mach_File() )
            {
                support_file = true;
            }

            return support_file;
        }


        std::string
        Mach_Reader_32::get_File_Type ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Mach_Reader_32::get_File_Type" );

            return Mach_Meta_Info::FILE_TYPE;
        }


        std::string
        Mach_Reader_32::get_Arch_Type ( void ) const
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Mach_Reader_32::get_Arch_Type" );

            return "java:bytecode";
        }


        data_types::memory_map::ptr_t
        Mach_Reader_32::get_memory_map ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Mach_Reader_32::get_memory_map" );

            return data_types::memory_map::ptr_t();
        }


        std::string
        Mach_Reader_32::to_String ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_Reader_32::to_String" );

            std::stringstream output;

            output << m_header->to_String() << std::endl;

            output << "---- Load_Commands ----" << std::endl;
            for ( Command_List_t::const_iterator cpos = m_commands.begin();
                    cpos != m_commands.end();
                    ++cpos )
            {
                output << ( *cpos )->to_String() << std::endl;
            }

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_Reader_32::to_String" );

            return output.str();
        }


        io_types::Text_Data::data_type
        Mach_Reader_32::get_Text_Strings ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_Reader_32::get_Text_String" );

            io_types::Text_Data::data_type output;

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_Reader_32::get_Text_String" );

            return output;
        }


        io_types::Text_Data::data_type
        Mach_Reader_32::get_UTF16_Strings ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_Reader_32::get_UTF16_String" );

            io_types::Text_Data::data_type output;

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_Reader_32::get_UTF16_String" );

            return output;
        }


        std::string
        Mach_Reader_32::get_Section_String ( std::string name ) const
        {
            return name;
        }

        void
        Mach_Reader_32::read_Headers ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Mach_Reader_32::read_Headers" );

            this->read_Mach_Header();
            this->read_Load_Commands();
        }

        void
        Mach_Reader_32::read_Mach_Header ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_Reader_32::read_Mach_Header" );

            mach_types::Mach_Header_32::ptr_t header ( new Mach_Header_32() );

            m_file.read_Mach_Header ( header );

            if ( header->needs_Convert () )
            {
                header->convert();
                m_convert = true;
            }

            m_header = header;

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_Reader_32::read_Mach_Header" );
        }

        void
        Mach_Reader_32::read_Load_Commands ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_Reader_32::read_Load_Commands" );

            for ( boost::uint32_t counter = 0;
                    counter < m_header->get_Load_Command_Count();
                    ++counter )
            {
                // Call factory to create correct command
                mach_types::Load_Command::ptr_t cmd_ptr = Load_Command_Factory::create ( m_file,
                        m_header->get_Cputype(),
                        m_convert );

                // Store command in List
                m_commands.push_back ( cmd_ptr );
            }

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_Reader_32::read_Load_Commands" );
        }

        mach_types::Mach_Header_32::ptr_t
        Mach_Reader_32::get_Header ( void )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Mach_Reader_32::get_Header" );

            return m_header;
        }

    } /* namespace mach_module */
} /* namespace reverse */
