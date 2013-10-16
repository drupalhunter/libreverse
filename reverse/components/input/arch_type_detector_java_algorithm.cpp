/*  Arch_Type_Detector_Java_Algorithm.cpp

    Copyright (C) 2008 Stephen Torri

    This file is part of Libreverse.

    Libreverse is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published
    by the Free Software Foundation; either version 3, or (at your
    option) any later version.

    Libreverse is distributed in the hope that it woill be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see
    <http://www.gnu.org/licenses/>.
*/

#include <reverse/components/input/arch_type_detector_java_algorithm.hpp>
#include <reverse/io/input/file_readers/java_class/reader.hpp>
#include <reverse/trace.hpp>

#include <boost/make_shared.hpp>

namespace reverse {
  namespace components {
    namespace input {

      std::string
      arch_type_detector_java_algorithm::run ( boost::shared_ptr < const io::file_id > file_ptr )
      {
	trace::components_detail ( "Entering Arch_Type_Detector_Java_Algorithm::run" );

	boost::shared_ptr < reverse::io::input::file_readers::java_class::reader > file_reader_ptr
	  = boost::make_shared < reverse::io::input::file_readers::java_class::reader > ( file_ptr );

	std::string result = file_reader_ptr->get_arch_type ();

	return result;
      }

    } // namespace input
  } /* namespace components */
} /* namespace reverse */
