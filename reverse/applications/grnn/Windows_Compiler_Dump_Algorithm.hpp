/* Windows_Compiler_Dump_Algorithm.h

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
#ifndef WINDOWS_COMPILER_DUMP_ALGORITHM_H
#define WINDOWS_COMPILER_DUMP_ALGORITHM_H

#include "Compiler_Dump_Algorithm.h"
#include "reverse/io/input/File_Readers/Windows_PE/Reader_32.h"
#include "reverse/io/input/File_Readers/Windows_PE/Reader_64.h"

namespace reverse {
  namespace optimizer {

    class Windows_Compiler_Dump_Algorithm : public Compiler_Dump_Algorithm {
    public:

      virtual ~Windows_Compiler_Dump_Algorithm () {};

      virtual void find_Files ( const boost::filesystem::path& dirpath,
				std::vector<std::string>& output_files );

      virtual std::string process ( boost::uint32_t compiler_id,
				    std::string filename );

    private:

      std::string process_File ( boost::uint32_t compiler_id, reverse::wpef_module::Reader_32& reader32_obj );

      std::string process_File ( boost::uint32_t compiler_id, reverse::wpef_module::Reader_64& reader64_obj );

    };

  } /* namespace optimizer */
} /* namespace reverse */

#endif /* WINDOWS_COMPILER_DUMP_ALGORITHM_H */
