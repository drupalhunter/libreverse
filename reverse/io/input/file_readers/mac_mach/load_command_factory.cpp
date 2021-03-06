/*  Load_Command_Factory.cpp

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

#include "Load_Command_Factory.h"
#include "Load_Command_Constants.h"
#include "Segment_Command.h"
#include "Symtab_Command.h"
#include "Thread_Command.h"
#include "Fvmlib_Command.h"
#include "Dylib_Command.h"
#include "Dysymtab_Command.h"
#include "Skipped_Command.h"
#include "Ident_Command.h"
#include "Dylinker_Command.h"
#include "Prebound_Dylib_Command.h"
#include "Routines_Command.h"
#include "Routines_Command_64.h"
#include "Sub_Client_Command.h"
#include "Sub_Framework_Command.h"
#include "Sub_Library_Command.h"
#include "Sub_Umbrella_Command.h"
#include "errors/Internal_Exception.h"
#include "CPU_Type.h"
#include "CPU_State_T.h"
#include "CPU_X86_32.h"
#include "CPU_X86_64.h"
#include "CPU_PPC_32.h"
#include "CPU_PPC_64.h"
#include "UUID_Command.h"
#include "Twolevel_Hints_Command.h"
#include "Segment_Command_64.h"
#include "Section.h"
#include "Trace.h"
#include "Reverse.h"
#include "io/Preconditions.h"
#include "io/Byte_Converter.h"

using namespace reverse::trace;
using namespace reverse::api;

namespace reverse
{
    namespace mach_module
    {
        mach_types::Load_Command::ptr_t
        Load_Command_Factory::create ( Mach_File& m_file,
                                       boost::uint32_t cputype,
                                       bool need_convert )
        {
            boost::uint32_t command_id = 0;
            m_file.read ( &command_id );
            boost::uint32_t command_size = 0;
            m_file.read ( &command_size );

            if ( need_convert )
            {
                io::Byte_Converter::convert ( command_id );
                io::Byte_Converter::convert ( command_size );
            }

            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DATA,
                                 boost::str ( boost::format ( "Load Command:  %1% (%2% bytes)" ) % command_id % command_size ) );

            switch ( command_id )
            {
                case Load_Command_Constants::LC_SEGMENT:
                {
                    mach_types::Segment_Command::ptr_t obj_ptr ( new Segment_Command ( command_id, command_size ) );
                    m_file.read_Segment_Command ( obj_ptr );
                    obj_ptr->convert ( need_convert );

                    for ( boost::uint32_t index = 0;
                            index < obj_ptr->get_Section_Count();
                            ++index )
                    {
                        mach_types::Section::ptr_t sec_ptr ( new Section() );
                        m_file.read_Section ( sec_ptr );
                        sec_ptr->convert ( need_convert );
                        obj_ptr->push_back ( sec_ptr );
                    }

                    return obj_ptr;
                }
                case Load_Command_Constants::LC_SYMTAB:
                {
                    mach_types::Symtab_Command::ptr_t obj_ptr ( new Symtab_Command ( command_id, command_size ) );
                    m_file.read_Symtab_Command ( obj_ptr );
                    obj_ptr->convert ( need_convert );
                    return obj_ptr;
                }
                case Load_Command_Constants::LC_THREAD:
                case Load_Command_Constants::LC_UNIXTHREAD:
                {
                    mach_types::Thread_Command::ptr_t obj_ptr ( new Thread_Command ( command_id, command_size ) );
                    m_file.read_Thread_Command ( obj_ptr );
                    Load_Command_Factory::create_CPU_Thread_State ( m_file, obj_ptr, cputype );
                    obj_ptr->convert ( need_convert );
                    return obj_ptr;
                }
                case Load_Command_Constants::LC_IDENT:
                {
                    mach_types::Ident_Command::ptr_t obj_ptr ( new Ident_Command ( command_id, command_size ) );
                    m_file.read_Ident_Command ( obj_ptr );
                    obj_ptr->convert ( need_convert );
                    return obj_ptr;
                }
                case Load_Command_Constants::LC_DYSYMTAB:
                {
                    mach_types::Dysymtab_Command::ptr_t obj_ptr ( new Dysymtab_Command ( command_id, command_size ) );
                    m_file.read_Dysymtab_Command ( obj_ptr );
                    obj_ptr->convert ( need_convert );
                    return obj_ptr;
                }
                case Load_Command_Constants::LC_LOAD_WEAK_DYLIB:
                case Load_Command_Constants::LC_ID_DYLIB:
                case Load_Command_Constants::LC_LOAD_DYLIB:
                {
                    mach_types::Dylib_Command::ptr_t obj_ptr ( new Dylib_Command ( command_id, command_size ) );
                    m_file.read_Dylib_Command ( obj_ptr, need_convert );
                    obj_ptr->convert ( need_convert );
                    return obj_ptr;
                }
                case Load_Command_Constants::LC_ID_DYLINKER:
                case Load_Command_Constants::LC_LOAD_DYLINKER:
                {
                    mach_types::Dylinker_Command::ptr_t obj_ptr ( new Dylinker_Command ( command_id, command_size ) );
                    m_file.read_Dylinker_Command ( obj_ptr, need_convert );
                    return obj_ptr;
                }
                case Load_Command_Constants::LC_PREBOUND_DYLIB:
                {
                    mach_types::Prebound_Dylib_Command::ptr_t obj_ptr ( new Prebound_Dylib_Command ( command_id, command_size ) );
                    m_file.read_Prebound_Dylib_Command ( obj_ptr, need_convert );
                    obj_ptr->convert ( need_convert );
                    return obj_ptr;
                }
                case Load_Command_Constants::LC_ROUTINES:
                {
                    mach_types::Routines_Command::ptr_t obj_ptr ( new Routines_Command ( command_id, command_size ) );
                    m_file.read_Routines_Command ( obj_ptr );
                    obj_ptr->convert ( need_convert );
                    return obj_ptr;
                }
                case Load_Command_Constants::LC_SUB_FRAMEWORK:
                {
                    mach_types::Sub_Framework_Command::ptr_t obj_ptr ( new Sub_Framework_Command ( command_id, command_size ) );
                    m_file.read_Sub_Framework_Command ( obj_ptr, need_convert );
                    return obj_ptr;
                }
                case Load_Command_Constants::LC_SUB_UMBRELLA:
                {
                    mach_types::Sub_Umbrella_Command::ptr_t obj_ptr ( new Sub_Umbrella_Command ( command_id, command_size ) );
                    m_file.read_Sub_Umbrella_Command ( obj_ptr, need_convert );
                    return obj_ptr;
                }
                case Load_Command_Constants::LC_SUB_CLIENT:
                {
                    mach_types::Sub_Client_Command::ptr_t obj_ptr ( new Sub_Client_Command ( command_id, command_size ) );
                    m_file.read_Sub_Client_Command ( obj_ptr, need_convert );
                    return obj_ptr;
                }
                case Load_Command_Constants::LC_SUB_LIBRARY:
                {
                    mach_types::Sub_Library_Command::ptr_t obj_ptr ( new Sub_Library_Command ( command_id, command_size ) );
                    m_file.read_Sub_Library_Command ( obj_ptr, need_convert );
                    return obj_ptr;
                }
                case Load_Command_Constants::LC_TWOLEVEL_HINTS:
                {
                    mach_types::Twolevel_Hints_Command::ptr_t obj_ptr ( new Twolevel_Hints_Command ( command_id, command_size ) );
                    m_file.read_Twolevel_Hints_Command ( obj_ptr );
                    obj_ptr->convert ( need_convert );
                    return obj_ptr;
                }
                case Load_Command_Constants::LC_SEGMENT_64:
                {
                    mach_types::Segment_Command_64::ptr_t obj_ptr ( new Segment_Command_64 ( command_id, command_size ) );
                    m_file.read_Segment_Command_64 ( obj_ptr );
                    obj_ptr->convert ( need_convert );
                    return obj_ptr;
                }
                case Load_Command_Constants::LC_ROUTINES_64:
                {
                    mach_types::Routines_Command_64::ptr_t obj_ptr ( new Routines_Command_64 ( command_id, command_size ) );
                    m_file.read_Routines_Command_64 ( obj_ptr );
                    obj_ptr->convert ( need_convert );
                    return obj_ptr;
                }
                case Load_Command_Constants::LC_UUID:
                {
                    mach_types::UUID_Command::ptr_t obj_ptr ( new UUID_Command ( command_id, command_size ) );
                    m_file.read_UUID_Command ( obj_ptr );
                    obj_ptr->convert ( need_convert );
                    return obj_ptr;
                }
                case Load_Command_Constants::LC_PREBIND_CKSUM:
                case Load_Command_Constants::LC_LOADFVMLIB:
                case Load_Command_Constants::LC_IDFVMLIB:
                case Load_Command_Constants::LC_FVMFILE:
                case Load_Command_Constants::LC_PREPAGE:
                case Load_Command_Constants::LC_SYMSEG:
                default:
                {
                    // Unsupported, skip load command
                    mach_types::Skipped_Command::ptr_t obj_ptr ( new Skipped_Command ( command_id, command_size ) );
                    m_file.read_Skipped_Command ( obj_ptr );
                    obj_ptr->convert ( need_convert );
                    return obj_ptr;
                }
            }
        }

        void
        Load_Command_Factory::create_CPU_Thread_State ( Mach_File& m_file,
                mach_types::Thread_Command::ptr_t thread_ptr,
                boost::uint32_t cputype )
        {
            io::Preconditions::is_set ( thread_ptr );

            switch ( cputype )
            {
                case CPU_Type::CPU_TYPE_X86:
                {
                    mach_types::CPU_State<CPU_X86_32>::ptr_t state_ptr ( new CPU_State<CPU_X86_32>() );
                    m_file.read_CPU_State ( state_ptr );
                    thread_ptr->add_CPU_State ( state_ptr );
                    break;
                }
                case CPU_Type::CPU_TYPE_X86_64:
                {
                    mach_types::CPU_State<CPU_X86_64>::ptr_t state_ptr ( new CPU_State<CPU_X86_64>() );
                    m_file.read_CPU_State ( state_ptr );
                    thread_ptr->add_CPU_State ( state_ptr );
                    break;
                }
                case CPU_Type::CPU_TYPE_POWERPC:
                {
                    mach_types::CPU_State<CPU_PPC_32>::ptr_t state_ptr ( new CPU_State<CPU_PPC_32>() );
                    m_file.read_CPU_State ( state_ptr );
                    thread_ptr->add_CPU_State ( state_ptr );
                    break;
                }
                case CPU_Type::CPU_TYPE_POWERPC64:
                {
                    mach_types::CPU_State<CPU_PPC_64>::ptr_t state_ptr ( new CPU_State<CPU_PPC_64>() );
                    m_file.read_CPU_State ( state_ptr );
                    thread_ptr->add_CPU_State ( state_ptr );
                    break;
                }
                default:
                {
                    // Unsupported
                }
            }
        }
    } /* namespace mach_module */
} /* namespace reverse */

