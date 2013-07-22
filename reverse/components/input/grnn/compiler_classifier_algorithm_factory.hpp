/*  Compiler_Classifier_Algorithm_Factory.h

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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_COMPILER_CLASSIFIER_ALGORITHM_FACTORY_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_COMPILER_CLASSIFIER_ALGORITHM_FACTORY_HPP_INCLUDED

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	class classifier_algorithm;

	class compiler_classifier_algorithm_factory {
	public:
	  
	  static compiler_classifier_algorithm_factory& instance()
	  {
	    static compiler_classifier_algorithm_factory fact_ref;
	    return fact_ref;
	  }

	virtual ~compiler_classifier_algorithm_factory();

	  /**
	   * \brief Create a new Classifier Algorithm
	   *
	   * \pre None
	   *
	   * \post Classifier Algorithm is not null
	   *
	   * \return Return a Component pointer to the new File Type Detector
	   */
	  boost::shared_ptr < components::input::grnn::classifier_algorithm >
	  get_classifier ( std::string type );

	private:

	  compiler_classifier_algorithm_factory ();

	  compiler_classifier_algorithm_factory ( const compiler_classifier_algorithm_factory& );
      
	  compiler_classifier_algorithm_factory& operator= ( const compiler_classifier_algorithm_factory& );
      
	};

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse

#endif // ifndef REVERSE_COMPONENTS_INPUT_GRNN_COMPILER_CLASSIFIER_ALGORITHM_FACTORY_HPP_INCLUDED
