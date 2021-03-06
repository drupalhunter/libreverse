/*  CPU_Type.cpp

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

#include "CPU_Type.h"
#include "errors/Internal_Exception.h"
#include "Trace.h"
#include "Reverse.h"
#include <boost/format.hpp>

using namespace reverse::api;
using namespace reverse::trace;

namespace reverse
{
    namespace mach_module
    {
        std::string
        CPU_Type::get_String_Name ( boost::uint32_t cputype )
        {
            std::string name = "CPU Type: ";

            switch ( cputype )
            {
                case CPU_TYPE_VAX:
                case CPU_Type::CPU_TYPE_MC680x0:
                case CPU_Type::CPU_TYPE_X86:
                    name = "x86 (32-bit)";
                    break;
                case CPU_Type::CPU_TYPE_X86_64:
                    name = "x86 (64-bit)";
                    break;
                case CPU_Type::CPU_TYPE_MIPS:
                    name= "MIPS";
                    break;
                case CPU_Type::CPU_TYPE_MC98000:
                    name = "MC98000";
                    break;
                case CPU_Type::CPU_TYPE_HPPA:
                    name = "HPPA";
                    break;
                case CPU_Type::CPU_TYPE_ARM:
                    name = "ARM";
                    break;
                case CPU_Type::CPU_TYPE_MC88000:
                    name= "MC88000";
                    break;
                case CPU_Type::CPU_TYPE_SPARC:
                    name = "Sparc";
                    break;
                case CPU_Type::CPU_TYPE_I860:
                    name = "I860";
                    break;
                case CPU_Type::CPU_TYPE_ALPHA:
                    name = "Alpha";
                    break;
                case CPU_Type::CPU_TYPE_POWERPC:
                    name = "PowerPC (32-bit)";
                    break;
                case CPU_Type::CPU_TYPE_POWERPC64:
                    name = "PowerPC (64-bit)";
                    break;
                default:
                    Trace::write_Trace ( TraceArea::IO,
                                         TraceLevel::DATA,
                                         boost::str ( boost::format ( "Invalid Index = %1%" ) % cputype ) );

                    throw errors::Internal_Exception ( errors::Internal_Exception::INVALID_VALUE );
            }

            return name;
        }

    } /* namespace mach_module */
} /* namespace reverse */
