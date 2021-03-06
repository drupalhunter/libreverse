/*  Mach_File.cpp

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

#include "Mach_File.h"

#include "Mach_Header_32.h"
#include "Mach_Header_64.h"
#include "Fat_Header.h"
#include "Fat_Arch.h"
#include "Segment_Command.h"
#include "Segment_Command_64.h"
#include "Symtab_Command.h"
#include "Thread_Command.h"
#include "Fvmfile_Command.h"
#include "Fvmlib_Command.h"
#include "Fvmlib.h"
#include "Ident_Command.h"
#include "Skipped_Command.h"
#include "Dysymtab_Command.h"
#include "Dylib_Command.h"
#include "Dylib.h"
#include "Dylinker_Command.h"
#include "Skipped_Command.h"
#include "Prebound_Dylib_Command.h"
#include "LC_Str.h"
#include "CPU_State_T.h"
#include "Routines_Command.h"
#include "Routines_Command_64.h"
#include "Sub_Framework_Command.h"
#include "Sub_Umbrella_Command.h"
#include "Sub_Client_Command.h"
#include "Sub_Library_Command.h"
#include "Twolevel_Hints_Command.h"
#include "UUID_Command.h"
#include "Trace.h"
#include "Reverse.h"
#include "Section.h"

using namespace reverse::trace;
using namespace reverse::api;

namespace reverse
{
    namespace mach_module
    {

        Mach_File::Mach_File ( io_types::File_ID::const_ptr_t filename )
                : m_file ( filename )
        {}

        Mach_File::Mach_File ( data_types::memory_map::ptr_t file_img_ptr,
                               io_types::File_ID::const_ptr_t filename )
                : m_file ( file_img_ptr, filename )
        {}

        bool Mach_File::init ( void )
        {
            return m_file.init();
        }

        boost::uint32_t Mach_File::get_File_Size ( void ) const
        {
            return m_file.size();
        }

        void
        Mach_File::read_Mach_Header ( mach_types::Mach_Header_32::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Mach_Header ( 32-bit )" );

            io::Preconditions::is_set ( obj );

            m_file.read ( & ( obj->m_magic ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Magic: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_magic ) );

            m_file.read ( & ( obj->m_cputype ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) CPU type: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_cputype ) );

            m_file.read ( & ( obj->m_cpusubtype ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) CPU subtype: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_cpusubtype ) );

            m_file.read ( & ( obj->m_filetype ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Filetype: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_filetype ) );

            m_file.read ( & ( obj->m_ncmds ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Number of commands: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_ncmds ) );

            m_file.read ( & ( obj->m_sizeofcmds ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Size of commands: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_sizeofcmds ) );

            m_file.read ( & ( obj->m_flags ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Flags: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_flags ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Mach_Header ( 32-bit )" );
        }

        void
        Mach_File::read_Mach_Header ( mach_types::Mach_Header_64::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Mach_Header ( 64-bit )" );

            io::Preconditions::is_set ( obj );

            m_file.read ( & ( obj->m_magic ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Magic: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_magic ) );

            m_file.read ( & ( obj->m_cputype ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) CPU type: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_cputype ) );

            m_file.read ( & ( obj->m_cpusubtype ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) CPU subtype: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_cpusubtype ) );

            m_file.read ( & ( obj->m_filetype ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Filetype: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_filetype ) );

            m_file.read ( & ( obj->m_ncmds ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Number of commands: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_ncmds ) );

            m_file.read ( & ( obj->m_sizeofcmds ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Size of commands: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_sizeofcmds ) );

            m_file.read ( & ( obj->m_flags ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Flags: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_flags ) );

            m_file.read ( & ( obj->m_reserved ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Reserved: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_reserved ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Mach_Header ( 64-bit )" );
        }

        void
        Mach_File::read_Fat_Header ( mach_types::Fat_Header::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Fat_Header" );

            m_file.read ( & ( obj->m_magic ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Magic: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % io::Byte_Converter::check_Convert ( obj->m_magic, obj->needs_Convert() ) ) );

            m_file.read ( & ( obj->m_nfat_arch ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Number of Fat Arch fields: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % io::Byte_Converter::check_Convert ( obj->m_nfat_arch, obj->needs_Convert() ) ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Fat_Header" );
        }

        void
        Mach_File::read_Fat_Arch ( mach_types::Fat_Arch::ptr_t obj, bool needs_convert )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Fat_Arch" );

            io::Preconditions::is_set ( obj );

            m_file.read ( & ( obj->m_cputype ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) CPU type: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % io::Byte_Converter::check_Convert ( obj->m_cputype, needs_convert ) ) );

            m_file.read ( & ( obj->m_cpu_subtype ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) CPU subtype: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % io::Byte_Converter::check_Convert ( obj->m_cpu_subtype, needs_convert ) ) );

            m_file.read ( & ( obj->m_offset ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Offset: 0x%2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % io::Byte_Converter::check_Convert ( obj->m_offset, needs_convert ) ) );

            m_file.read ( & ( obj->m_size ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Size: %2$d" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % io::Byte_Converter::check_Convert ( obj->m_size, needs_convert ) ) );

            m_file.read ( & ( obj->m_align ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Aligment: 0x%2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % io::Byte_Converter::check_Convert ( obj->m_align, needs_convert ) ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Fat_Arch" );
        }

        void
        Mach_File::read_Segment_Command ( mach_types::Segment_Command::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Segment_Command" );

            io::Preconditions::is_set ( obj );
            obj->m_segname = m_file.read_String ( Load_Command::MAX_NAME_SIZE );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Segment name: %2$s" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_segname ) );

            m_file.read ( & ( obj->m_vmaddr ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Virtual memory address: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_vmaddr ) );

            m_file.read ( & ( obj->m_vmsize ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Virtual memory size: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_vmsize ) );

            m_file.read ( & ( obj->m_fileoff ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) File offset: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_fileoff ) );

            m_file.read ( & ( obj->m_filesize ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) File size: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_filesize ) );

            m_file.read ( & ( obj->m_maxprot ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Max protection: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_maxprot ) );

            m_file.read ( & ( obj->m_initprot ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Init protection: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_initprot ) );

            m_file.read ( & ( obj->m_nsects ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Number of sections: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_nsects ) );

            m_file.read ( & ( obj->m_flags ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Flags: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_flags ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Segment_Command" );
        }

        void
        Mach_File::read_Section ( mach_types::Section::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Section" );

            io::Preconditions::is_set ( obj );

            obj->m_sectname = m_file.read_String ( Load_Command::MAX_NAME_SIZE );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Section name: %2$s" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_sectname ) );

            obj->m_segname = m_file.read_String ( Load_Command::MAX_NAME_SIZE );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Segment name: %2$s" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_segname ) );

            m_file.read ( & ( obj->m_addr ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Address: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_addr ) );

            m_file.read ( & ( obj->m_size ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Size: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_size ) );

            m_file.read ( & ( obj->m_offset ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Offset: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_offset ) );

            m_file.read ( & ( obj->m_align ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Alignment: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_align ) );

            m_file.read ( & ( obj->m_reloff ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Relocation Offset: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_reloff ) );

            m_file.read ( & ( obj->m_nreloc ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Number of relocation: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_nreloc ) );

            m_file.read ( & ( obj->m_flags ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Flags: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_flags ) );

            m_file.read ( & ( obj->m_reserved1 ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Reserved1: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_reserved1 ) );

            m_file.read ( & ( obj->m_reserved2 ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Reserved2: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_reserved2 ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Section" );
        }

        void
        Mach_File::read_Symtab_Command ( mach_types::Symtab_Command::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Symtab_Command" );

            io::Preconditions::is_set ( obj );

            m_file.read ( & ( obj->m_symoff ) );
            m_file.read ( & ( obj->m_nsyms ) );
            m_file.read ( & ( obj->m_stroff ) );
            m_file.read ( & ( obj->m_strsize ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Symtab_Command" );
        }

        void
        Mach_File::read_Thread_Command ( mach_types::Thread_Command::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Thread_Command" );

            io::Preconditions::is_set ( obj );

            m_file.read ( & ( obj->m_flavor ) );
            m_file.read ( & ( obj->m_count ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Thread_Command" );
        }
        void
        Mach_File::read_Fvmlib_Command ( mach_types::Fvmlib_Command::ptr_t obj, bool need_convert )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Fvmlib_Command" );

            io::Preconditions::is_set ( obj );

            // Mark present location
            boost::uint32_t command_start_address = this->get_Present_Position_Value() - ( sizeof ( boost::uint32_t ) * 2 );

            mach_types::Fvmlib::ptr_t lib_ptr ( new Fvmlib () );
            this->read_LC_Str ( lib_ptr->m_name, command_start_address, need_convert );
            m_file.read ( & ( lib_ptr->m_minor_version ) );
            obj->m_fvmlib = lib_ptr;

            // Set to the next command
            this->index_Seek ( command_start_address + obj->m_cmdsize );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Fvmlib_Command" );
        }

        void
        Mach_File::read_LC_Str ( mach_types::LC_Str::ptr_t obj,
                                 boost::uint32_t command_start_address,
                                 bool need_convert )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_LC_Str" );

            io::Preconditions::is_set ( obj );

            m_file.read ( & ( obj->m_offset ) );

            if ( need_convert )
            {
                io::Byte_Converter::convert ( obj->m_offset );
            }

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "(0x%1$X) Offset: %2$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address()
                                              % obj->m_offset ) );

            // Save present position
            boost::uint32_t next_command_address = this->get_Present_Position_Value();

            this->index_Seek ( command_start_address + obj->m_offset );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "Starting reading LC_Str at 0x%1$X" )
                                              % m_file.get_Map_Ptr()->get_Previous_Position_Address() ) );

            obj->m_text = m_file.read_Null_Terminated_String ();

            this->index_Seek ( next_command_address );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_LC_Str" );
        }

        void
        Mach_File::read_Ident_Command ( mach_types::Ident_Command::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Ident_Command" );

            io::Preconditions::is_set ( obj );

            /* When we can find out what are the fields of this command we can fully implement it */
            this->index_Seek ( this->get_Present_Position_Value() + obj->m_cmdsize - ( sizeof ( boost::uint32_t ) * 2 ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Ident_Command" );
        }

        void
        Mach_File::read_Fvmfile_Command ( mach_types::Fvmfile_Command::ptr_t obj, bool need_convert )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Fvmfile_Command" );

            io::Preconditions::is_set ( obj );

            // Mark present location
            boost::uint32_t command_start_address = this->get_Present_Position_Value() - ( sizeof ( boost::uint32_t ) * 2 );

            this->read_LC_Str ( obj->m_name, command_start_address, need_convert );
            m_file.read ( & ( obj->m_header_addr ) );

            // Set to the next command
            this->index_Seek ( command_start_address + obj->m_cmdsize );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Fvmfile_Command" );
        }

        void
        Mach_File::read_Skipped_Command ( mach_types::Skipped_Command::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Skipped_Command" );

            io::Preconditions::is_set ( obj );

            // Mark present location
            boost::uint32_t command_start_address = this->get_Present_Position_Value() - ( sizeof ( boost::uint32_t ) * 2 );

            // Set to the next command
            this->index_Seek ( command_start_address + obj->m_cmdsize );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Skipped_Command" );
        }

        // Read Dysymtab_Command from file
        void
        Mach_File::read_Dysymtab_Command ( mach_types::Dysymtab_Command::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Dysymtab_Command" );

            io::Preconditions::is_set ( obj );

            m_file.read ( & ( obj->m_ilocalsym ) );
            m_file.read ( & ( obj->m_nlocalsym ) );
            m_file.read ( & ( obj->m_iextdefsym ) );
            m_file.read ( & ( obj->m_nextdefsym ) );
            m_file.read ( & ( obj->m_iundefsym ) );
            m_file.read ( & ( obj->m_nundefsym ) );
            m_file.read ( & ( obj->m_tocoff ) );
            m_file.read ( & ( obj->m_ntoc ) );
            m_file.read ( & ( obj->m_modtaboff ) );
            m_file.read ( & ( obj->m_nmodtab ) );
            m_file.read ( & ( obj->m_extrefsymoff ) );
            m_file.read ( & ( obj->m_nextrefsyms ) );
            m_file.read ( & ( obj->m_indirectsymoff ) );
            m_file.read ( & ( obj->m_nindirectsyms ) );
            m_file.read ( & ( obj->m_extreloff ) );
            m_file.read ( & ( obj->m_nextrel ) );
            m_file.read ( & ( obj->m_localref ) );
            m_file.read ( & ( obj->m_nlocrel ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Dysymtab_Command" );
        }

        // Read Dylib_Command from file
        void
        Mach_File::read_Dylib_Command ( mach_types::Dylib_Command::ptr_t obj, bool need_convert )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Dylib_Command" );

            io::Preconditions::is_set ( obj );

            // Mark present location
            boost::uint32_t command_start_address = this->get_Present_Position_Value() - ( sizeof ( boost::uint32_t ) * 2 );

            mach_types::Dylib::ptr_t lib_ptr ( new Dylib () );
            this->read_LC_Str ( lib_ptr->m_name, command_start_address, need_convert );

            m_file.read ( & ( lib_ptr->m_timestamp ) );
            m_file.read ( & ( lib_ptr->m_current_version ) );
            m_file.read ( & ( lib_ptr->m_compatibility_version ) );

            obj->m_dylib = lib_ptr;

            // Set to the next command
            this->index_Seek ( command_start_address + obj->m_cmdsize );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Dylib_Command" );
        }

        void
        Mach_File::index_Seek ( boost::uint32_t offset )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::index_Seek" );

            // - Init source to where data will be read.
            data_types::memory_map::ptr_t src_map_ptr = m_file.get_Map_Ptr();

            src_map_ptr->index_Seek ( offset );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::index_Seek" );
        }

        api::Results::Values
        Mach_File::address_Seek ( boost::uint32_t address )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::address_Seek" );

            // - Init source to where data will be read.
            data_types::memory_map::ptr_t src_map_ptr = m_file.get_Map_Ptr();

            if ( src_map_ptr->address_Seek ( address ) != data_types::memory_map::SUCCESS )
            {
                return api::Results::INVALID_INDEX;
            }

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::address_Seek" );

            return api::Results::SUCCESS;
        }

        void
        Mach_File::copy ( data_types::memory_map::ptr_t dest_ptr,
                          boost::uint32_t length )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::copy" );

            io::Preconditions::is_set ( dest_ptr );
            io::Preconditions::not_equal ( length, static_cast<boost::uint32_t>(0) );

            data_types::memory_map::ptr_t src_map_ptr = m_file.get_Map_Ptr();

            dest_ptr->copy ( src_map_ptr, length );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::copy" );
        }

        io_types::File_ID::const_ptr_t
        Mach_File::get_ID ( void ) const
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Mach_File::get_ID" );

            return m_file.get_ID();
        }

        boost::uint32_t
        Mach_File::get_Present_Position_Value ( void ) const
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Mach_File::get_Present_Position_Value" );

            data_types::memory_map::ptr_t src_map_ptr = m_file.get_Map_Ptr();

            return src_map_ptr->get_Present_Position_Value ();
        }

        // Read x86 32-bit CPU state from file
        void
        Mach_File::read_CPU_State ( mach_types::CPU_State<CPU_X86_32>::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_CPU_State ( x86 32-bit )" );

            io::Preconditions::is_set ( obj );

            CPU_X86_32::data_type register_value = 0;

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_32::EAX, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_32::EBX, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_32::ECX, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_32::EDX, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_32::EDI, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_32::ESI, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_32::EBP, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_32::ESP, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_32::SS, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_32::EFLAGS, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_32::EIP, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_32::DS, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_32::ES, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_32::FS, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_32::GS, register_value );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_CPU_State ( x86 32-bit )" );
        }

        // Read x86 64-bit CPU state from file
        void
        Mach_File::read_CPU_State ( mach_types::CPU_State<CPU_X86_64>::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_CPU_State ( x86 64-bit )" );

            io::Preconditions::is_set ( obj );

            CPU_X86_64::data_type register_value = 0;

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::RAX, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::RBX, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::RCX, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::RDX, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::RDI, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::RSI, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::RBP, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::RSP, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::R8, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::R9, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::R10, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::R11, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::R12, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::R13, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::R14, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::R15, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::RIP, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::RFLAGS, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::CS, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::FS, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_X86_64::GS, register_value );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_CPU_State ( x86 64-bit )" );
        }

        // Read PPC 32-bit CPU state from file
        void
        Mach_File::read_CPU_State ( mach_types::CPU_State<CPU_PPC_32>::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_CPU_State ( PPC 32-bit )" );

            io::Preconditions::is_set ( obj );

            CPU_PPC_32::data_type register_value = 0;

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::SRR0, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::SRR1, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R0, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R1, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R2, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R3, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R4, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R5, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R6, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R7, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R8, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R9, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R10, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R11, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R12, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R13, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R14, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R15, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R16, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R17, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R18, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R19, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R20, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R21, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R22, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R23, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R24, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R25, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R26, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R27, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R28, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R29, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R30, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::R31, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::CR, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::XER, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::LR, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::CTR, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::MQ, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_32::VRSAVE, register_value );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_CPU_State ( PPC 32-bit )" );
        }

        // Read PPC 64-bit CPU state from file
        void
        Mach_File::read_CPU_State ( mach_types::CPU_State<CPU_PPC_64>::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_CPU_State ( PPC 64-bit )" );

            io::Preconditions::is_set ( obj );

            CPU_PPC_64::data_type register_value = 0;

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::SRR0, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::SRR1, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R0, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R1, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R2, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R3, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R4, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R5, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R6, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R7, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R8, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R9, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R10, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R11, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R12, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R13, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R14, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R15, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R16, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R17, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R18, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R19, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R20, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R21, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R22, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R23, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R24, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R25, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R26, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R27, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R28, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R29, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R30, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::R31, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::CR, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::XER, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::LR, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::CTR, register_value );

            m_file.read ( &register_value );
            obj->set_Register ( CPU_PPC_64::VRSAVE, register_value );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_CPU_State ( PPC 64-bit )" );
        }

        // Read Dylinker_Command from file
        void
        Mach_File::read_Dylinker_Command ( mach_types::Dylinker_Command::ptr_t obj, bool need_convert )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Dylinker_Command" );

            io::Preconditions::is_set ( obj );

            // Mark present location
            boost::uint32_t command_start_address = this->get_Present_Position_Value() - ( sizeof ( boost::uint32_t ) * 2 );

            this->read_LC_Str ( obj->m_name, command_start_address, need_convert );

            // Set to the next command
            this->index_Seek ( command_start_address + obj->m_cmdsize );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Dylinker_Command" );
        }

        // Read Prebound_Dylib_Command from file
        void
        Mach_File::read_Prebound_Dylib_Command ( mach_types::Prebound_Dylib_Command::ptr_t obj, bool need_convert )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Prebound_Dylib_Command" );

            io::Preconditions::is_set ( obj );

            // Mark present location
            boost::uint32_t command_start_address = this->get_Present_Position_Value() - ( sizeof ( boost::uint32_t ) * 2 );

            this->read_LC_Str ( obj->m_name, command_start_address, need_convert );
            m_file.read ( & ( obj->m_nmodules ) );
            this->read_LC_Str ( obj->m_linked_modules, command_start_address, need_convert );

            // Set to the next command
            this->index_Seek ( command_start_address + obj->m_cmdsize );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Prebound_Dylib_Command" );
        }

        // Read Routine_Command from file
        void
        Mach_File::read_Routines_Command ( mach_types::Routines_Command::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Routines_Command" );

            io::Preconditions::is_set ( obj );

            m_file.read ( & ( obj->m_init_address ) );
            m_file.read ( & ( obj->m_init_module ) );
            m_file.read ( & ( obj->m_reserved1 ) );
            m_file.read ( & ( obj->m_reserved2 ) );
            m_file.read ( & ( obj->m_reserved3 ) );
            m_file.read ( & ( obj->m_reserved4 ) );
            m_file.read ( & ( obj->m_reserved5 ) );
            m_file.read ( & ( obj->m_reserved6 ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Routines_Command" );
        }

        // Read Routine_Command_64 from file
        void
        Mach_File::read_Routines_Command_64 ( mach_types::Routines_Command_64::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Routines_Command_64" );

            io::Preconditions::is_set ( obj );

            m_file.read ( & ( obj->m_init_address ) );
            m_file.read ( & ( obj->m_init_module ) );
            m_file.read ( & ( obj->m_reserved1 ) );
            m_file.read ( & ( obj->m_reserved2 ) );
            m_file.read ( & ( obj->m_reserved3 ) );
            m_file.read ( & ( obj->m_reserved4 ) );
            m_file.read ( & ( obj->m_reserved5 ) );
            m_file.read ( & ( obj->m_reserved6 ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Routines_Command_64" );
        }

        // Read Sub_Framework_Command from file
        void
        Mach_File::read_Sub_Framework_Command ( mach_types::Sub_Framework_Command::ptr_t obj, bool need_convert )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Sub_Framework_Command" );

            io::Preconditions::is_set ( obj );

            // Mark present location
            boost::uint32_t command_start_address = this->get_Present_Position_Value() - ( sizeof ( boost::uint32_t ) * 2 );

            this->read_LC_Str ( obj->m_umbrella, command_start_address, need_convert );

            // Set to the next command
            this->index_Seek ( command_start_address + obj->m_cmdsize );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Sub_Framework_Command" );
        }

        // Read Sub_Umbrella_Command from file
        void
        Mach_File::read_Sub_Umbrella_Command ( mach_types::Sub_Umbrella_Command::ptr_t obj, bool need_convert )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Sub_Umbrella_Command" );

            io::Preconditions::is_set ( obj );

            // Mark present location
            boost::uint32_t command_start_address = this->get_Present_Position_Value() - ( sizeof ( boost::uint32_t ) * 2 );

            this->read_LC_Str ( obj->m_sub_umbrella, command_start_address, need_convert );

            // Set to the next command
            this->index_Seek ( command_start_address + obj->m_cmdsize );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Sub_Umbrella_Command" );
        }

        void
        Mach_File::read_Sub_Client_Command ( mach_types::Sub_Client_Command::ptr_t obj, bool need_convert )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Sub_Client_Command" );

            io::Preconditions::is_set ( obj );

            // Mark present location
            boost::uint32_t command_start_address = this->get_Present_Position_Value() - ( sizeof ( boost::uint32_t ) * 2 );

            this->read_LC_Str ( obj->m_client, command_start_address, need_convert );

            // Set to the next command
            this->index_Seek ( command_start_address + obj->m_cmdsize );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Sub_Client_Command" );
        }

        void
        Mach_File::read_Sub_Library_Command ( mach_types::Sub_Library_Command::ptr_t obj, bool need_convert )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Sub_Library_Command" );

            io::Preconditions::is_set ( obj );

            // Mark present location
            boost::uint32_t command_start_address = this->get_Present_Position_Value() - ( sizeof ( boost::uint32_t ) * 2 );

            this->read_LC_Str ( obj->m_sub_library, command_start_address, need_convert );

            // Set to the next command
            this->index_Seek ( command_start_address + obj->m_cmdsize );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Sub_Library_Command" );
        }

        void
        Mach_File::read_Twolevel_Hints_Command ( mach_types::Twolevel_Hints_Command::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Twolevel_Hints_Command" );

            io::Preconditions::is_set ( obj );

            m_file.read ( & ( obj->m_offset ) );
            m_file.read ( & ( obj->m_nhints ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Twolevel_Hints_Command" );
        }

        void
        Mach_File::read_Segment_Command_64 ( mach_types::Segment_Command_64::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_Segment_Command_64" );

            io::Preconditions::is_set ( obj );

            m_file.read ( & ( obj->m_vmaddr ) );
            m_file.read ( & ( obj->m_vmsize ) );
            m_file.read ( & ( obj->m_fileoff ) );
            m_file.read ( & ( obj->m_filesize ) );
            m_file.read ( & ( obj->m_maxprot ) );
            m_file.read ( & ( obj->m_initprot ) );
            m_file.read ( & ( obj->m_nsects ) );
            m_file.read ( & ( obj->m_flags ) );

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_Segment_Command_64" );
        }

        void
        Mach_File::read_UUID_Command ( mach_types::UUID_Command::ptr_t obj )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Entering Mach_File::read_UUID_Command" );

            io::Preconditions::is_set ( obj );

            boost::uint8_t byte = 0;

            for ( boost::uint32_t index = 0;
                    index < UUID_Command::MAX_SIZE;
                    ++index )
            {
                m_file.read ( &byte );

                obj->m_uuid.push_back ( byte );
            }

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Exiting Mach_File::read_UUID_Command" );
        }
    } /* namespace mach_module */
} /* namespace reverse */
