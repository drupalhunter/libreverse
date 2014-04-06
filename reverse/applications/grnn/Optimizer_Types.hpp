/*  Optimizer_Types.h

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

#ifndef OPTIMIZER_TYPES_H
#define OPTIMIZER_TYPES_H

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <string>
#include <map>
#include <vector>

namespace reverse {

  namespace optimizer
  {
    template <template <typename Data_Type> class Classifier_Type> class Elf_Optimizer_Algorithm;
    class Elf_Compiler_Dump_Algorithm;
    class Optimizer_Algorithm;
    template <template <typename Data_Type> class Classifier_Type> class Java_Optimizer_Algorithm;
    class Java_Compiler_Dump_Algorithm;
    class Compiler_Dump_Algorithm;
    class Compression_Dump_Algorithm;
    template <template <typename Data_Type> class Classifier_Type> class Windows_Optimizer_Algorithm;
    class Windows_Compiler_Dump_Algorithm;
    class Windows_Compression_Dump_Algorithm;
  } /* namespace optimizer */
  
  namespace optimizer_types
  {
    template <template <typename Data_Type> class Classifier_Type>
    class Elf_Optimizer_Algorithm
    {
    public:
      typedef boost::shared_ptr < optimizer::Elf_Optimizer_Algorithm<Classifier_Type> > ptr_t;
    };

    class Elf_Compiler_Dump_Algorithm
    {
    public:
      typedef boost::shared_ptr <optimizer::Elf_Compiler_Dump_Algorithm> ptr_t;
    };

    class Optimizer_Algorithm
    {
    public:
      typedef boost::shared_ptr <optimizer::Optimizer_Algorithm> ptr_t;
      typedef boost::shared_ptr <optimizer::Optimizer_Algorithm const> const_ptr_t;
    };

    template <template <typename Data_Type> class Classifier_Type>
    class Java_Optimizer_Algorithm
    {
    public:
      typedef boost::shared_ptr < optimizer::Java_Optimizer_Algorithm<Classifier_Type> > ptr_t;
    };

    class Java_Compiler_Dump_Algorithm
    {
    public:
      typedef boost::shared_ptr <optimizer::Java_Compiler_Dump_Algorithm> ptr_t;
    };

    class Compiler_Dump_Algorithm
    {
    public:
      typedef boost::shared_ptr <optimizer::Compiler_Dump_Algorithm> ptr_t;
      typedef boost::shared_ptr <optimizer::Compiler_Dump_Algorithm const> const_ptr_t;
    };

    class Compression_Dump_Algorithm
    {
    public:
      typedef boost::shared_ptr <optimizer::Compression_Dump_Algorithm> ptr_t;
      typedef boost::shared_ptr <optimizer::Compression_Dump_Algorithm const> const_ptr_t;
    };

    template <template <typename Data_Type> class Classifier_Type>
    class Windows_Optimizer_Algorithm
    {
    public:
      typedef boost::shared_ptr < optimizer::Windows_Optimizer_Algorithm<Classifier_Type> > ptr_t;
    };

    class Windows_Compiler_Dump_Algorithm
    {
    public:
      typedef boost::shared_ptr <optimizer::Windows_Compiler_Dump_Algorithm> ptr_t;
    };

    class Windows_Compression_Dump_Algorithm
    {
    public:
      typedef boost::shared_ptr <optimizer::Windows_Compression_Dump_Algorithm> ptr_t;
    };

  } /* namespace optimizer_types */
} /* namespace reverse */

#endif /* OPTIMIZER_TYPES_H */
