
/*  Reverse.h

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

#ifndef REVERSE_H_
#define REVERSE_H_

#include <reverse/input_types.hpp>
#include <reverse/output_types.hpp>
#include <reverse/trace_area.hpp>
#include <reverse/trace_level.hpp>

#include <boost/cstdint.hpp>

#include <string>

/*!
 * \class Reverse
 * \date 2003
 * \author Stephen Torri
 */
namespace reverse {

    class reverse
    {

    public:

      /*!
       * \brief Default Constructor
       */
      explicit reverse();

      /*!
       * \brief Default Destructor
       */
      ~reverse();

      /*!
       * \brief Initialize the Reverse objects
       *
       * \param target_file Input binary file
       *
       * \param input_type Input type guess
       *
       * \param language_type Output type for results
       *
       * \param trace_level The maximum level of tracing. If value
       * equals None then no output will be recorded otherwise
       * output of debugging information is cumulative (e.g. warning
       * = lowest information, data = highest level recorded which
       * includes all levels from warning on up).
       *
       * \param trace_mask The trace mask is the way to control what
       * debugging information is recorded. If no value is given
       * then the default action is to debug no areas even if the
       * trace_level is set to anything other than None.
       *
       * For now the only input type we accept will be binary files. So the
       * Component graphs generated with be a pairing of binary file and
       * some output language type
       */
      boost::int32_t execute ( std::string target_file,
			       input_types::values input_type,
			       output_types::values language_type,
			       trace_level::values trace_level = trace_level::none,
			       trace_area::values trace_mask = trace_area::none );

    private:

      bool valid_types ( boost::uint32_t lower_limit,
			 boost::uint32_t upper_limit,
			 boost::uint32_t value );
    };

} /* namespace reverse */

#endif /* REVERSE_H_ */

