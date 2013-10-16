/*  Arch_Type_Detector_WPEF32_Algorithm.h

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

#ifndef REVERSE_COMPONENTS_INPUT_ARCH_TYPE_DETECTOR_WPEF64_ALGORITHM_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_ARCH_TYPE_DETECTOR_WPEF64_ALGORITHM_HPP_INCLUDED

#include <reverse/components/input/arch_type_detector_algorithm.hpp>

#include <boost/shared_ptr.hpp>

namespace reverse {

  namespace io {
    class file_id;
  }

  namespace components {
    namespace input {

      class arch_type_detector_wpef64_algorithm : public arch_type_detector_algorithm {
      public:

	virtual ~arch_type_detector_wpef64_algorithm(){}
	
	virtual std::string run ( boost::shared_ptr < const io::file_id > file_ptr );
      };

    } // namespace input
  } /* namespace components */
} /* namespace reverse */

#endif // ifndef REVERSE_COMPONENTS_INPUT_ARCH_TYPE_DETECTOR_WPEF64_ALGORITHM_HPP_INCLUDED
