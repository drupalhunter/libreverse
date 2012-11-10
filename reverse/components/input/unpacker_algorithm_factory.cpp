/*  Unpacker_Algorithm_Factory.cpp

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

#include "Unpacker_Algorithm_Factory.h"
#include "Unpacker_Java_Algorithm.h"
#include "Unpacker_X86_Algorithm.h"
#include "errors/CPU_Exception.h"
#include <string>

namespace libreverse { namespace component {

    Unpacker_Algorithm::ptr_t
    Unpacker_Algorithm_Factory::get_Algorithm ( std::string name )
    {
        if ( name.compare ( "intel:i386" ) == 0 )
            {
                return Unpacker_Algorithm::ptr_t ( new Unpacker_X86_Algorithm() );
            }
        else if ( name.compare ( "java:bytecode" ) == 0 )
            {
                return Unpacker_Algorithm::ptr_t ( new Unpacker_Java_Algorithm() );
            }
        else
            {
                throw errors::CPU_Exception
                    ( errors::CPU_Exception::UNSUPPORTED_ARCHITECTURE );
            }
    }

} /* namespace component */
} /* namespace libreverse */

