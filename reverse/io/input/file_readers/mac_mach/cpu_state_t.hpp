/*  CPU_State_T.h

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

//
// C++ Interface: CPU_State
//
// Description:
//
//
// Author: Stephen Torri,,, <storri@torri.org>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef CPU_STATE_H
#define CPU_STATE_H


#include "CPU_Thread_State.h"
#include "io/Byte_Converter.h"

#include <map>
#include <string>

namespace reverse
{
  namespace mach_module
  {
    template <typename Register_Type>
      class CPU_State : public CPU_Thread_State
      {
      public:

	/*!
	 * \brief Return the value stored in the target register
	 *
	 * \param index Unsigned integer denoting the target register
	 *
	 * \exception IO_Exception(INVALID_INDEX) Thrown when index value is outside the acceptable range.
	 *
	 * \return Value stored in register
	 */
	typename Register_Type::data_type read_Register ( boost::uint32_t index )
	{
	  typename Map_t::const_iterator cpos = m_data.find ( index );
	  if ( cpos == m_data.end() )
            {
	      throw errors::IO_Exception ( errors::IO_Exception::INVALID_INDEX );
            }

	  return ( *cpos ).second;
        }

	/*!
	 * \brief Store the value in the target register
	 *
	 * \param index Unsigned integer denoting the target register
	 * \param value Value to be stored at register position
	 *
	 * \exception IO_Exception(INVALID_INDEX) Thrown when index value is outside the acceptable range.
	 */
	void set_Register ( boost::uint32_t index, typename Register_Type::data_type value )
	{
	  typename Map_t::const_iterator cpos = m_data.find ( index );
	  if ( index >= Register_Type::MAX_COUNT )
            {
	      throw errors::IO_Exception ( errors::IO_Exception::INVALID_INDEX );
            }

	  m_data[index] = value;
        }

	/*!
	 * \brief Return the register name for the given index
	 *
	 * \param index Unsigned integer index for the target register
	 *
	 * \exception IO_Exception(INVALID_INDEX) Exception thrown for invalid index.
	 *
	 * \return Register string name
	 */
	std::string get_Register_Name ( boost::uint32_t index )
	  {
            if ( index >= Register_Type::MAX_COUNT )
	      {
                throw errors::IO_Exception ( errors::IO_Exception::INVALID_INDEX );
	      }

            return Register_Type::get_Register_Name ( index );
	  }

	/*!
	 * \brief Return a formatted string representation of the CPU state
	 *
	 * \return Formatted output string of CPU state
	 */
	virtual std::string to_String ()
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

	/*!
	 * \brief Convert the byte order of register values
	 *
	 * \param need_convert TRUE it is necessary to convert the byte_order otherwise nothing is done
	 */
	virtual void convert ( bool need_convert )
	{
	  if ( need_convert )
            {
	      std::for_each ( m_data.begin(), m_data.end(), convert_entry );
            }
        }

      private:

	typedef std::map<boost::uint32_t, typename Register_Type::data_type> Map_t;
	Map_t m_data;

	/*!
	 * \brief Functor that is applied to each value in the CPU state to convert the byte order
	 *
	 * \param obj Value stored in target register
	 */
	static void convert_entry ( typename Map_t::value_type & obj )
	{
	  io::Byte_Converter::convert ( obj.second );
        }
      };
  }
}

#endif /* CPU_THREAD_STATE */
