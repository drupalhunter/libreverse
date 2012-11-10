/*  Data_Source_Base.h

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

#ifndef REVERSE_INFRASTRUCTURE_DATA_SOURCE_DATA_SOURCE_BASE_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_DATA_SOURCE_DATA_SOURCE_BASE_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

namespace reverse {
  namespace infrastructure {
    namespace data_source {

      class data_object;

      class data_source_base {
      public:

        virtual ~data_source_base(){}

        /**
         *
         */
	virtual boost::shared_ptr < const infrastructure::data_source::data_object > get () const = 0;

	/**
	 *
	 * @param data
	 */
	virtual void put ( boost::shared_ptr < infrastructure::data_source::data_object >& data) = 0;

        /**
         * \brief debug data structure by dumping contents to standard out.
         */
        virtual std::string to_string (void) const = 0;

        /**
         * \brief provide a deep copy of the object implementing data_source_base
         */
        virtual boost::shared_ptr < infrastructure::data_source::data_object > get_deep_copy ( void ) = 0;
      };

    } // namespace data_source
  } // namespace infrastructure
} // namespace reverse

#endif // #ifndef REVERSE_INFRASTRUCTURE_DATA_SOURCE_DATA_SOURCE_BASE_HPP_INCLUDED

