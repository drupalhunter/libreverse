/*  CPU_PPC_32.cpp

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

#include "CPU_PPC_32.h"

namespace libreverse
{
    namespace mach_module
    {
        std::string
        CPU_PPC_32::get_Register_Name ( boost::uint32_t index )
        {
            if ( index > VRSAVE )
            {
                throw errors::IO_Exception ( errors::IO_Exception::INVALID_INDEX );
            }

            std::string name = "";

            switch ( index )
            {
                case SRR0: name = "SRR0"; break;
                case SRR1: name = "SRR1"; break;
                case R0: name = "R0"; break;
                case R1: name = "R1"; break;
                case R2: name = "R2"; break;
                case R3: name = "R3"; break;
                case R4: name = "R4"; break;
                case R5: name = "R5"; break;
                case R6: name = "R6"; break;
                case R7: name = "R7"; break;
                case R8: name = "R8"; break;
                case R9: name = "R9"; break;
                case R10: name = "R10"; break;
                case R11: name = "R11"; break;
                case R12: name = "R12"; break;
                case R13: name = "R13"; break;
                case R14: name = "R14"; break;
                case R15: name = "R15"; break;
                case R16: name = "R16"; break;
                case R17: name = "R17"; break;
                case R18: name = "R18"; break;
                case R19: name = "R19"; break;
                case R20: name = "R20"; break;
                case R21: name = "R21"; break;
                case R22: name = "R22"; break;
                case R23: name = "R23"; break;
                case R24: name = "R24"; break;
                case R25: name = "R25"; break;
                case R26: name = "R26"; break;
                case R27: name = "R27"; break;
                case R28: name = "R28"; break;
                case R29: name = "R29"; break;
                case R30: name = "R30"; break;
                case R31: name = "R31"; break;
                case CR: name = "CR"; break;
                case XER: name = "XER"; break;
                case LR: name = "LR"; break;
                case CTR: name = "CTR"; break;
                case MQ: name = "MQ"; break;
                case VRSAVE: name = "VRSAVE"; break;
            }

            return name;
        }
    }
}
