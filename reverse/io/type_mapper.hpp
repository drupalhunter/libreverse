/*  Type_Mapper.h

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

#ifndef TYPE_MAPPER_H_
#define TYPE_MAPPER_H_

#include <boost/cstdint.hpp>

namespace libreverse {

/*! \brief Type Mapper type */
template <boost::uint32_t size> struct Type_Mapper;

/*! \brief 32-bit Type Mapper */
template <>
struct Type_Mapper<32> {

  /*! \brief 32-bit type */
    typedef boost::uint32_t arch_t;
};

/*! \brief 64-bit Type Mapper */
template <>
struct Type_Mapper<64> {

  /*! \brief 64-bit type */
    typedef boost::uint64_t arch_t;
};

} /* namespace libreverse */
#endif /* TYPE_MAPPER_H_ */
