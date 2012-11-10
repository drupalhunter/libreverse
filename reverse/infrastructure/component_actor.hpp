/*  Component_Actor.h

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

/* Component Actor interface

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
#ifndef REVERSE_INFRASTRUCTURE_COMPONENT_ACTOR_HPP_INCLUDED
#define REVERSE_INFRASTRUCTURE_COMPONENT_ACTOR_HPP_INCLUDED

namespace reverse {
  namespace infrastructure {

    // inherited by all component objects (e.g. file type detector)
    class component_actor {
    public:

        virtual ~component_actor(){}

        // performs the specific action
        //
        // \param data_ptr used to grab information to start its work. the
        // end results are placed in it for retrieval later.
        virtual void process ( void ) = 0;

    };

  } // namespace infrastructure
} // namespace reverse

#endif // #ifndef REVERSE_INFRASTRUCTURE_COMPONENT_ACTOR_HPP_INCLUDED
