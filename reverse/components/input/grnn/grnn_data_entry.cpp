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

#include "GRNN_Data_Entry.h"

#include "Reverse.h"
#include "io/Preconditions.h"

using namespace libreverse::api;

#ifdef LIBREVERSE_DEBUG
#include "Trace.h"
using namespace libreverse::trace;
#endif /* LIBREVERSE_DEBUG */

namespace libreverse
{
  namespace classifier
  {

    GRNN_Data_Entry::GRNN_Data_Entry ( double sigma, std::string file )
      : m_sigma ( sigma ),
	m_file ( file )
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside GRNN_Data_Entry constructor" );
#endif /* LIBREVERSE_DEBUG */


      io::Preconditions::not_equal ( m_sigma, static_cast<double>(0.0) );
      io::Preconditions::not_empty ( m_file );
    }

    double
    GRNN_Data_Entry::get_Sigma ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside GRNN_Data_Entry::get_Sigma" );
#endif /* LIBREVERSE_DEBUG */


      io::Preconditions::not_equal ( m_sigma, static_cast<double>(0.0) );

      return m_sigma;
    }

    std::string
    GRNN_Data_Entry::get_Filename ( void ) const
    {

#ifdef LIBREVERSE_DEBUG
      Trace::write_Trace ( TraceArea::GRNN_DATA,
			   TraceLevel::DETAIL,
			   "Inside GRNN_Data_Entry::get_Filename" );
#endif /* LIBREVERSE_DEBUG */


      io::Preconditions::not_empty ( m_file );

      return m_file;
    }

  } /* namespace classifier */

} /* namespace libreverse */
