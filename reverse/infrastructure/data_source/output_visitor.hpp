/*  Output_Visitor.h

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

#ifndef OUTPUT_VISITOR_H
#define OUTPUT_VISITOR_H

#include "Data_Source_Base.h"
#include <boost/variant/static_visitor.hpp>
#include <string>

namespace libreverse {
namespace infrastructure {

  class Output_Visitor : public boost::static_visitor<std::string>
  {
  public:

    std::string operator() ( Data_Object& value ) const;

  };

} /* namespace infrastructure */
} /* namespace libreverse */

#endif /* OUTPUT_VISITOR_H */

