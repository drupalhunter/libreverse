/* Java_Compiler_Dump_Algorithm.h

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
#ifndef JAVA_COMPILER_DUMP_ALGORITHM_H
#define JAVA_COMPILER_DUMP_ALGORITHM_H

#include "Compiler_Dump_Algorithm.h"

#include "libreverse/io/input/File_Readers/Java_Class/Java_Types.h"

namespace libreverse {
  namespace optimizer {

    class Java_Compiler_Dump_Algorithm : public Compiler_Dump_Algorithm {
    public:

      virtual ~Java_Compiler_Dump_Algorithm () {};

      virtual void find_Files ( const boost::filesystem::path& dirpath,
				std::vector<std::string>& output_files );

      virtual std::string process ( boost::uint32_t compiler_id,
				    std::string filename );

    private:

      void collect_Constant_Pool_Stats ( std::vector<float>& stats,
					 libreverse::java_types::Class_Header::Constant_Pool_Info_Map_t::const_iterator pool_start,
					 libreverse::java_types::Class_Header::Constant_Pool_Info_Map_t::const_iterator pool_end );

      void print_Constant_Pool_Stats ( std::stringstream& output,
				       std::vector<float>& stats,
				       float constant_pool_total );
    };

  } /* namespace optimizer */
} /* namespace libreverse */

#endif /* JAVA_COMPILER_DUMP_ALGORITHM_H */
