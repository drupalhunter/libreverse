/*  PE_Debug_Directory.cpp

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

#include "PE_Debug_Directory.h"
#include <iostream>
#include <iomanip>
#include "io/Byte_Converter.h"
#include <sstream>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace libreverse
{
    namespace wpef_module
    {

        PE_Debug_Directory::PE_Debug_Directory()
                : m_characteristics ( 0 ),
                m_time_date_stamp ( 0 ),
                m_major_version ( 0 ),
                m_minor_version ( 0 ),
                m_type ( 0 ),
                m_size_of_data ( 0 ),
                m_address_of_raw_data ( 0 ),
                m_pointer_to_raw_data ( 0 )
        {}

        boost::uint32_t
        PE_Debug_Directory::get_size ( void ) const
        {
            return static_cast<boost::uint32_t> ( 32 );
        }

        std::string
        PE_Debug_Directory::to_String ( void )
        {
            std::stringstream output_str;

            output_str << "PE Debug Directory:" << std::endl;

            output_str << boost::format ( "  Characteristics:             %1X" ) %
            m_characteristics
            << std::endl;

            boost::posix_time::ptime epoch
            ( boost::gregorian::date ( 1970, 1, 1 ) );
            boost::posix_time::seconds s_time ( m_time_date_stamp );
            boost::posix_time::ptime creation_date = epoch + s_time;

            output_str << boost::format ( "  Time & Date:              %1%" ) %
            boost::posix_time::to_simple_string ( creation_date )
            << std::endl;

            output_str << boost::format ( "  Version:                  %1%.%2%" ) %
            m_major_version %
            boost::io::group ( std::setfill ( '0' ),
                               std::setw ( 2 ),
                               m_minor_version )
            << std::endl;

            output_str << boost::format ( "  Type:                     %1s" ) %
            Debug_Types::get_Type_Name ( m_type )
            << std::endl;

            output_str << boost::format ( "  Size of data:             %1X" ) %
            m_size_of_data
            << std::endl;

            output_str << boost::format ( "  Address of Raw Data:      %1X" ) %
            m_address_of_raw_data
            << std::endl;

            output_str << boost::format ( "  Pointers to Raw Data:     %1X" ) %
            m_pointer_to_raw_data
            << std::endl;

            return output_str.str();

        }

        void
        PE_Debug_Directory::convert ()
        {
            io::Byte_Converter::convert ( m_characteristics );
            io::Byte_Converter::convert ( m_time_date_stamp );
            io::Byte_Converter::convert ( m_major_version );
            io::Byte_Converter::convert ( m_minor_version );
            io::Byte_Converter::convert ( m_type );
            io::Byte_Converter::convert ( m_size_of_data );
            io::Byte_Converter::convert ( m_address_of_raw_data );
            io::Byte_Converter::convert ( m_pointer_to_raw_data );
        }

    } /* namespace wpef_module */
} /* namespace libreverse */

