/* Compression_Dump_Algorithm.h

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
#ifndef COMPRESSION_DUMP_ALGORITHM_H
#define COMPRESSION_DUMP_ALGORITHM_H

#include <string>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>

namespace libreverse {
  namespace optimizer {

    class Compression_Dump_Algorithm {
    public:

      virtual ~Compression_Dump_Algorithm () {};

      virtual void find_Files ( const boost::filesystem::path& dirpath,
				std::vector<std::string>& output_files ) = 0;

      virtual std::string process ( boost::uint32_t compression_id,
				    std::string filename ) = 0;

    };

  } /* namespace optimizer */
} /* namespace libreverse */

#endif /* COMPRESSION_DUMP_ALGORITHM_H */

