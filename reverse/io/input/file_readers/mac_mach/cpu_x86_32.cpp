/*  CPU_X86_32.cpp

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

#include "CPU_X86_32.h"
#include "errors/IO_Exception.h"

namespace libreverse
{
    namespace mach_module
    {

        string CPU_X86_32::get_Register_Name ( uint32_t index )
        {
            // Bouml preserved body begin 0001F437
            if ( index > GS )
            {
                throw errors::IO_Exception ( errors::IO_Exception::INVALID_INDEX );
            }

            std::string name = "";

            switch ( index )
            {
                case EAX: name = "EAX"; break;
                case EBX: name = "EBX"; break;
                case ECX: name = "ECX"; break;
                case EDX: name = "EDX"; break;
                case EDI: name = "EDI"; break;
                case ESI: name = "ESI"; break;
                case EBP: name = "EBP"; break;
                case ESP: name = "ESP"; break;
                case SS: name = "SS"; break;
                case EFLAGS: name = "EFLAGS"; break;
                case EIP: name = "EIP"; break;
                case DS: name = "DS"; break;
                case ES: name = "ES"; break;
                case FS: name = "FS"; break;
                case GS: name = "GS"; break;
            }

            return name;
            // Bouml preserved body end 0001F437
        }

    } /* namespace mach_module */
} /* namespace libreverse */
