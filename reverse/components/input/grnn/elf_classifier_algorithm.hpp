/*  Elf_Classifier_Algorithm.h

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

#ifndef REVERSE_COMPONENTS_INPUT_GRNN_ELF_CLASSIFIER_ALGORITHM_HPP_INCLUDED
#define REVERSE_COMPONENTS_INPUT_GRNN_ELF_CLASSIFIER_ALGORITHM_HPP_INCLUDED

#include "Classifier_Algorithm.h"
#include <string>
#include "meta/Meta_Object.h"

namespace reverse {
  namespace components {
    namespace input {
      namespace grnn {

	class elf_classifier_algorithm : public classifier_algorithm {
	public:

	  virtual ~elf_classifier_algorithm(){}

	  virtual boost::shared_ptr < meta::meta_object > execute ( std::string const& filename );

	private:

	  std::string get_compiler_name ( double value );

	  meta::meta_object::ptr_t process_file ( libreverse::elf_module::elf_reader_32 const& reader32_obj ) const;

	  meta::meta_object::ptr_t process_file ( libreverse::elf_module::elf_reader_64 const& reader64_obj ) const;

	  enum values {
	    gcc_4_1 = 0,
	    pgcc = 1,
	    intel = 2
	  };

	};

      } // namespace grnn
    } // namespace input
  } // namespace components
} // namespace reverse


#endif // ifndef REVERSE_COMPONENTS_INPUT_GRNN_ELF_CLASSIFIER_ALGORITHM_HPP_INCLUDED
