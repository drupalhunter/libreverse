/*  CPU_State_T.cpp

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

#include "CPU_State_T.h"
#include "libreverse/errors/IO_Exception.h"
#include <boost/format.hpp>
#include <sstream>
#include "libreverse/io/Byte_Converter.h"

namespace libreverse
{
    namespace mach_module
    {

        template <typename Register_Type>
        typename Register_Type::data_type
        CPU_State<Register_Type>::read_Register ( boost::uint32_t index )
        {
            typename Map_t::const_iterator cpos = m_data.find ( index );
            if ( cpos == m_data.end() )
            {
                throw errors::IO_Exception ( errors::IO_Exception::INVALID_INDEX );
            }

            return ( *cpos ).second;
        }

        template <typename Register_Type>
        void
        CPU_State<Register_Type>::set_Register ( boost::uint32_t index, typename Register_Type::data_type value )
        {
            typename Map_t::const_iterator cpos = m_data.find ( index );
            if ( index >= Register_Type::MAX_COUNT )
            {
                throw errors::IO_Exception ( errors::IO_Exception::INVALID_INDEX );
            }

            m_data[index] = value;
        }

        template <typename Register_Type>
        std::string
        CPU_State<Register_Type>::get_Register_Name ( boost::uint32_t index )
        {
            if ( index >= Register_Type::MAX_COUNT )
            {
                throw errors::IO_Exception ( errors::IO_Exception::INVALID_INDEX );
            }

            return Register_Type::get_Register_Name ( index );
        }

        template <typename Register_Type>
        std::string
        CPU_State<Register_Type>::to_String ()
        {
            std::stringstream output;

            for ( boost::uint32_t index = 0;
                    index < Register_Type::MAX_COUNT;
                    ++index )
            {
                output << boost::format ( "%1$s = %2$X" ) % this->get_Register_Name ( index )
                % this->read_Register ( index ) << std::endl;
            }

            return output.str();
        }

        template <typename Register_Type>
        void
        CPU_State<Register_Type>::convert ( bool need_convert )
        {
            if ( need_convert )
            {
                std::for_each ( m_data.begin(), m_data.end(), convert_entry );
            }
        }

        template <typename Register_Type>
        void
        CPU_State<Register_Type>::convert_entry ( typename Map_t::value_type & val )
        {
            io::Byte_Converter::convert ( val.second );
        }
    }
}


