/*  Compiler_Classifier_Algorithm_Factory.cpp

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

#include <reverse/components/input/grnn/classifier_algorithm.hpp>
#include <reverse/components/input/grnn/compiler_classifier_algorithm_factory.hpp>
#include <reverse/components/input/grnn/java_classifier_algorithm.hpp>
#include <reverse/errors/internal_exception.hpp>
#include <reverse/io/input/file_readers/java_class/java_meta_info.hpp>
#include <reverse/trace.hpp>

#include <boost/format.hpp>
#include <boost/smart_ptr/make_shared.hpp>

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {


	boost::shared_ptr < components::input::grnn::classifier_algorithm >
	compiler_classifier_algorithm_factory::get_classifier ( std::string type )
	{
	  trace::components_detail ( "Inside Compiler_Classifier_Algorithm_Factory::get_classifier" );

	  if ( type.compare ( io::input::file_readers::java_class::java_meta_info::file_type ) == 0 )
	    {
	      return boost::make_shared < components::input::grnn::java_classifier_algorithm>();
	    }
	  else
	    {
	      throw errors::internal_exception ( errors::internal_exception::unsupported_feature );
	    }
	}

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse

