/*  Fat_Header.cpp

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

#include "Fat_Header.h"
#include "io/Output.h"
#include "errors/IO_Exception.h"
#include "Trace.h"
#include "Reverse.h"
#include <sstream>
#include "io/Byte_Converter.h"

using namespace libreverse::api;
using namespace libreverse::trace;

namespace libreverse
{
    namespace mach_module
    {

        Fat_Header::Fat_Header()
                : m_magic ( 0 ),
                m_nfat_arch ( 0 )
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Fat_Header constructor" );
        }

        void Fat_Header::init ()
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Fat_Header::init" );
        }

        boost::uint32_t
        Fat_Header::get_size () const
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Fat_Header::get_size" );

            return static_cast<boost::uint32_t> ( 32 );
        }

        void
        Fat_Header::convert ()
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Fat_Header::convert" );

            io::Byte_Converter::convert ( m_magic );
            io::Byte_Converter::convert ( m_nfat_arch );
        }

        bool
        Fat_Header::needs_Convert ( void ) const
        {
            bool result = true;

            if ( m_magic == FAT_MAGIC )
            {
                result = false;
            }

            return result;
        }

        std::string const
        Fat_Header::to_String ( void ) const
        {
            Trace::write_Trace ( TraceArea::IO,
                                 TraceLevel::DETAIL,
                                 "Inside Fat_Header::to_String" );

            std::stringstream output;

            output << "Fat_Header" << std::endl
            << io::Output::indent ( 2 ) << boost::format ( "Magic: 0x%1$08X ( %2$d )" ) % m_magic % m_magic << std::endl
            << io::Output::indent ( 2 ) << boost::format ( "Number of Fat Architectures: 0x%1%" ) % m_nfat_arch << std::endl;

            return output.str();
        }

        bool
        Fat_Header::is_Fat_File ( void ) const
        {
            bool result = false;

            /* Exerpt from file utility 'cafebabe' file:

            # Cafe Babes unite!
            #
            # Since Java bytecode and Mach-O fat-files have the same magic number, the test
            # must be performed in the same "magic" sequence to get both right.  The long
            # at offset 4 in a mach-O fat file tells the number of architectures; the short at
            # offset 4 in a Java bytecode file is the JVM minor version and the
            # short at offset 6 is the JVM major version.  Since there are only
            # only 18 labeled Mach-O architectures at current, and the first released
            # Java class format was version 43.0, we can safely choose any number
            # between 18 and 39 to test the number of architectures against
            # (and use as a hack). Let's not use 18, because the Mach-O people
            # might add another one or two as time goes by...
            #
            */

            if ( ( ( m_magic == FAT_MAGIC ) || ( m_magic == FAT_CIGAM ) ) &&
                    ( m_nfat_arch < 30 ) )
            {
                result = true;
            }

            return result;
        }

        boost::uint32_t
        Fat_Header::get_Magic ( void ) const
        {
            return m_magic;
        }

        boost::uint32_t
        Fat_Header::get_Number_Of_Fat_Arch ( void ) const
        {
            return m_nfat_arch;
        }

    } /* namespace mach_module */
} /* namespace libreverse */
