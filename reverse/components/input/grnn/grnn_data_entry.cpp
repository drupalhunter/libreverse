/*  GRNN_Data_Entry.cpp

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

#include <reverse/preconditions.hpp>
#include <reverse/components/input/grnn/grnn_data_entry.hpp>

#ifdef LIBREVERSE_DEBUG
#include <reverse/trace.hpp>
using namespace reverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	grnn_data_entry::grnn_data_entry ( double sigma, std::string file )
	  : m_sigma ( sigma ),
	    m_file ( file )
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_DATA,
			       TraceLevel::DETAIL,
			       "Inside GRNN_Data_Entry constructor" );
#endif /* LIBREVERSE_DEBUG */


	  preconditions::not_equal ( m_sigma, static_cast<double>(0.0) );
	  preconditions::not_empty ( m_file );
	}

	double
	grnn_data_entry::get_sigma ( void ) const
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_DATA,
			       TraceLevel::DETAIL,
			       "Inside GRNN_Data_Entry::get_Sigma" );
#endif /* LIBREVERSE_DEBUG */


	  preconditions::not_equal ( m_sigma, static_cast<double>(0.0) );

	  return m_sigma;
	}

	std::string
	grnn_data_entry::get_filename ( void ) const
	{

#ifdef LIBREVERSE_DEBUG
	  Trace::write_Trace ( TraceArea::GRNN_DATA,
			       TraceLevel::DETAIL,
			       "Inside GRNN_Data_Entry::get_filename" );
#endif /* LIBREVERSE_DEBUG */


	  preconditions::not_empty ( m_file );

	  return m_file;
	}

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse

