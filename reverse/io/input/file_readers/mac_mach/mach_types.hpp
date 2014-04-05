/*  Mach_Types.h

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

#ifndef MACH_TYPES_H_
#define MACH_TYPES_H_

#include <boost/shared_ptr.hpp>
#include <vector>
#include <map>
#include <boost/cstdint.hpp>

namespace reverse
{

    namespace mach_module
    {
        template <typename Register_Type> class CPU_State;
        class CPU_Thread_State;
        class Dylib;
        class Dylib_Command;
        class Dylinker_Command;
        class Dysymtab_Command;
        class Fat_Arch;
        class Fat_Header;
        class Fvmfile_Command;
        class Fvmlib;
        class Fvmlib_Command;
        template <boost::uint32_t bitsize> class Header;
        class Ident_Command;
        class LC_Str;
        class Load_Command;
        class Mach_File;
        class Mach_Header_32;
        class Mach_Header_64;
        class Mach_Reader_32;
        class Mach_Reader_64;
        class Prebound_Dylib_Command;
        template <boost::uint32_t bitsize> class Reader;
        class Routines_Command;
        class Routines_Command_64;
        class Skipped_Command;
        class Section;
        class Segment_Command;
        class Segment_Command_64;
        class Sub_Framework_Command;
        class Sub_Umbrella_Command;
        class Sub_Client_Command;
        class Sub_Library_Command;
        class Symtab_Command;
        class Thread_Command;
        class Twolevel_Hints_Command;
        class UUID_Command;
    }

    namespace mach_types
    {

        template <typename Register_Type>
        class CPU_State
        {
            public:
                typedef boost::shared_ptr < mach_module::CPU_State<Register_Type> > ptr_t;
        };

        class CPU_Thread_State
        {
            public:
                typedef boost::shared_ptr < mach_module::CPU_Thread_State > ptr_t;
        };

        class Dylib
        {
            public:
                typedef boost::shared_ptr < mach_module::Dylib > ptr_t;
        };

        class Dylib_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Dylib_Command > ptr_t;
        };

        class Dylinker_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Dylinker_Command > ptr_t;
        };

        class Dysymtab_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Dysymtab_Command > ptr_t;
        };

        class Fat_Arch
        {
            public:
                typedef boost::shared_ptr < mach_module::Fat_Arch > ptr_t;
        };

        class Fat_Header
        {
            public:
                typedef boost::shared_ptr < mach_module::Fat_Header > ptr_t;
        };

        class Fvmfile_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Fvmfile_Command > ptr_t;
        };

        class Fvmlib_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Fvmlib_Command > ptr_t;
        };

        class Fvmlib
        {
            public:
                typedef boost::shared_ptr < mach_module::Fvmlib > ptr_t;
        };

        class Ident_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Ident_Command > ptr_t;
        };

        class LC_Str
        {
            public:
                typedef boost::shared_ptr < mach_module::LC_Str > ptr_t;
        };

        template <boost::uint32_t bitsize>
        class Reader
        {
            public:
                typedef boost::shared_ptr < mach_module::Reader<bitsize> > ptr_t;
        };

        template <boost::uint32_t bitsize>
        class Header
        {
            public:
                typedef boost::shared_ptr < mach_module::Header<bitsize> > ptr_t;
        };

        class Mach_File
        {
            public:
                typedef boost::shared_ptr < mach_module::Mach_File > ptr_t;
        };

        class Mach_Header_32
        {
            public:
                typedef boost::shared_ptr < mach_module::Mach_Header_32 > ptr_t;
        };

        class Mach_Header_64
        {
            public:
                typedef boost::shared_ptr < mach_module::Mach_Header_64 > ptr_t;
        };

        class Load_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Load_Command > ptr_t;
                typedef std::vector<ptr_t> List_t;
        };

        class Prebound_Dylib_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Prebound_Dylib_Command > ptr_t;
        };

        class Section
        {
            public:
                typedef boost::shared_ptr < mach_module::Section > ptr_t;
        };

        class UUID_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::UUID_Command > ptr_t;
        };

        class Mach_Reader_32
        {
            public:
                typedef boost::shared_ptr < mach_module::Mach_Reader_32 > ptr_t;
        };

        class Mach_Reader_64
        {
            public:
                typedef boost::shared_ptr < mach_module::Mach_Reader_64 > ptr_t;
        };

        class Routines_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Routines_Command > ptr_t;
        };

        class Routines_Command_64
        {
            public:
                typedef boost::shared_ptr < mach_module::Routines_Command_64 > ptr_t;
        };

        class Segment_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Segment_Command > ptr_t;
        };

        class Segment_Command_64
        {
            public:
                typedef boost::shared_ptr < mach_module::Segment_Command_64 > ptr_t;
        };

        class Skipped_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Skipped_Command > ptr_t;
        };

        class Sub_Framework_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Sub_Framework_Command > ptr_t;
        };

        class Sub_Umbrella_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Sub_Umbrella_Command > ptr_t;
        };

        class Sub_Client_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Sub_Client_Command > ptr_t;
        };

        class Sub_Library_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Sub_Library_Command > ptr_t;
        };

        class Symtab_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Symtab_Command > ptr_t;
        };

        class Thread_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Thread_Command > ptr_t;
        };

        
        class Twolevel_Hints_Command
        {
            public:
                typedef boost::shared_ptr < mach_module::Twolevel_Hints_Command > ptr_t;
        };
    }

} /* namespace reverse */

#endif /* MACH_TYPES_H_ */

