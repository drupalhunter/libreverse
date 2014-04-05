/*  Verification_Type_Tags.cpp

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

#include "Verification_Type_Tags.h"

namespace reverse { namespace java_module {

  boost::uint8_t const Verification_Type_Tags::TOP = 0;
  boost::uint8_t const Verification_Type_Tags::INTEGER = 1;
  boost::uint8_t const Verification_Type_Tags::FLOAT = 2;
  boost::uint8_t const Verification_Type_Tags::LONG = 3;
  boost::uint8_t const Verification_Type_Tags::DOUBLE = 4;
  boost::uint8_t const Verification_Type_Tags::NULL_TYPE = 5;
  boost::uint8_t const Verification_Type_Tags::UNINITIALIZED_THIS = 6;
  boost::uint8_t const Verification_Type_Tags::OBJECT = 7;
  boost::uint8_t const Verification_Type_Tags::UNINITIALIZED = 8;


} /* namespace java_module */
} /* namespace reverse */
