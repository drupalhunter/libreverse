/*  Classifier_Algorithm.h

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
#ifndef REVERSE_COMPONENTS_INPUT_GRNN_CLASSIFIER_ALGORITHM_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_CLASSIFIER_ALGORITHM_HPP_INCLUDED

#include <boost/shared_ptr.hpp>

#include <string>

namespace reverse {

  namespace meta {
    class meta_object;
  } // namespace meta

  namespace components {
    namespace input {
      namespace grnn {

	class classifier_algorithm {
	public:

	  virtual ~classifier_algorithm(){}

	  virtual boost::shared_ptr < meta::meta_object > execute ( std::string const& filename ) = 0;

	};

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse

#endif // ifndef REVERSE_COMPONENTS_INPUT_GRNN_CLASSIFIER_ALGORITHM_HPP_INCLUDED

