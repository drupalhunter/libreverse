/*  CPU_X86_64.cpp

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

#include "CPU_X86_64.h"

namespace reverse
{
    namespace mach_module
    {
        std::string
        CPU_X86_64::get_Register_Name ( boost::uint32_t index )
        {
            if ( index > GS )
            {
                throw errors::IO_Exception ( errors::IO_Exception::INVALID_INDEX );
            }

            std::string name = "";

            switch ( index )
            {
                case RAX: name = "RAX"; break;
                case RBX: name = "RBX"; break;
                case RCX: name = "RCX"; break;
                case RDX: name = "RDX"; break;
                case RDI: name = "RDI"; break;
                case RSI: name = "RSI"; break;
                case RBP: name = "RBP"; break;
                case RSP: name = "RSP"; break;
                case R8: name = "R8"; break;
                case R9: name = "R9"; break;
                case R10: name = "R10"; break;
                case R11: name = "R11"; break;
                case R12: name = "R12"; break;
                case R13: name = "R13"; break;
                case R14: name = "R14"; break;
                case R15: name = "R15"; break;
                case RIP: name = "RIP"; break;
                case RFLAGS: name = "RFLAGS"; break;
                case CS: name = "CS"; break;
                case FS: name = "FS"; break;
                case GS: name = "GS"; break;
            }

            return name;
        }
    }
}

