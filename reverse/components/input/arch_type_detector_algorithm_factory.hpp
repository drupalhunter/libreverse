/*  Arch_Type_Detector_Algorithm_Factory.h

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

#ifndef REVERSE_COMPONENTS_INPUT_ARCH_TYPE_DETECTOR_ALGORITHM_FACTORY_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_ARCH_TYPE_DETECTOR_ALGORITHM_FACTORY_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

namespace reverse {
  namespace component {
    namespace input {

      class arch_type_detector_algorithm_factory {
      public:

        // pointer type
        typedef boost::shared_ptr<arch_type_detector_algorithm_factory> ptr_t;

        static arch_type_detector_algorithm_factory& instance()
        {
	  static arch_type_detector_algorithm_factory fact_ref;
	  return fact_ref;
        }

	boost::shared_ptr < arch_type_detector_algorithm > get_algorithm ( std::string file_type );

      private:

	arch_type_detector_algorithm_factory (){}

	arch_type_detector_algorithm_factory ( const arch_type_detector_algorithm_factory& );
      
	arch_type_detector_algorithm_factory& operator = ( const arch_type_detector_algorithm_factory& );
      
	~arch_type_detector_algorithm_factory (){}
      };

    } /* namespace input */
  } /* namespace component */
} /* namespace reverse */

#endif // ifndef REVERSE_COMPONENTS_INPUT_ARCH_TYPE_DETECTOR_ALGORITHM_FACTORY_HPP_INCLUDED
