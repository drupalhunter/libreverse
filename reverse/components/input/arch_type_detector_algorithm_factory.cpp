/*  Arch_Type_Detector_Algorithm_Factory.cpp

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

#include <reverse/components/input/arch_type_detector_algorithm_factory.hpp>
#include <reverse/components/input/arch_type_detector_elf32_algorithm.hpp>
#include <reverse/components/input/arch_type_detector_elf64_algorithm.hpp>
#include <reverse/components/input/arch_type_detector_java_algorithm.hpp>
#include <reverse/components/input/arch_type_detector_wpef32_algorithm.hpp>
#include <reverse/components/input/arch_type_detector_wpef64_algorithm.hpp>
#include <reverse/errors/cpu_exception.hpp>
#include <reverse/io/input/file_readers/linux_elf/elf_meta_info.hpp>
#include <reverse/io/input/file_readers/java_class/java_meta_info.hpp>
#include <reverse/io/input/file_readers/windows_pe/pe_meta_info.hpp>

#include <reverse/trace.hpp>

#include <boost/make_shared.hpp>

#include <string>

namespace reverse {
  namespace component {
    namespace input {

      boost::shared_ptr < arch_type_detector_algorithm >
      arch_type_detector_algorithm_factory::get_algorithm ( std::string file_type )
      {
	trace::components_detail ("Entering arch_type_detector_algorithm_factory::get_algorithm" );

	if ( file_type.compare ( io::input::file_readers::linux_elf::elf_meta_info::FILE_TYPE_32BIT ) == 0 )
	  {
	    return boost::make_shared < arch_type_detector_elf32_algorithm > ();
	  }
	else if ( file_type.compare ( io::input::file_readers::linux_elf::elf_meta_info::FILE_TYPE_64BIT ) == 0 )
	  {
	    return boost::make_shared < arch_type_detector_elf64_algorithm > ();
	  }
	else if ( file_type.compare ( java_module::java_meta_info::file_type ) == 0 )
	  {
	    return boost::make_shared < arch_type_detector_java_algorithm > ();
	  }
	else if ( file_type.compare ( wpef_module::pe_meta_info::pe_file_type_32bit ) == 0 )
	  {
	    return boost::make_shared < arch_type_detector_wpef32_algorithm > ();
	  }
	else if ( file_type.compare ( wpef_module::pe_meta_info::pe_file_type_64bit ) == 0 )
	  {
	    return boost::make_shared < arch_type_detector_wpef64_algorithm> ();
	  }
	else
	  {
	    throw errors::cpu_exception ( errors::cpu_exception::unsupported_architecture );
	  }

	trace::components_detail ("Exiting arch_type_detector_algorithm_factory::get_algorithm" );
      }

    }  // namespace input
  }  // namespace component
} // namespace reverse

