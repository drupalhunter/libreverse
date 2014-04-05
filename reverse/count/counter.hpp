
/*  Counter.h

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

#ifndef COUNTER_H_
#define COUNTER_H_

#include <sys/time.h>
#include <boost/cstdint.hpp>

namespace reverse
{
  namespace count
  {

    /*!
     * \class Counter
     * \date 2008
     * \author Stephen Torri
     */
    class Counter
    {
    public:

      static inline boost::uint64_t get_CPU_Tick ()
	{
	  boost::uint64_t tick;
	  __asm__ __volatile__ ("rdtsc" : "=A"(tick) : );
	  return tick;
	}

      /**
       * Code found at http://www.devmaster.net/forums/showthread.php?t=369
       */
      static inline boost::uint64_t time_Get_Time( void ) 
      {
	//===================================================
	// Using Linux Time Functions To Determine Time
	//===================================================
	struct timeval tv;
	gettimeofday( &tv, 0 );
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
      }

      static inline boost::uint64_t get_CPU_Ticks_Per_Usec ()
	{
	  boost::int64_t timeStart, timeStop, timeBegin;
	  boost::int64_t startTick, endTick;
	  boost::int64_t overhead;

	  //===================================================
	  // Calculate CPU Tick Function Call Overhead
	  //===================================================
	  overhead = get_CPU_Tick() - get_CPU_Tick();

	  //===================================================
	  // Calculate Starting Time And Start Tick
	  //===================================================
	  timeStart = time_Get_Time();

	  while( time_Get_Time() == timeStart )
	    {
	      timeStart = time_Get_Time();
	    }

	  while(1)
	    {
	      timeStop = time_Get_Time();
	      if((timeStop - timeStart) > 1)
		{
		  startTick = get_CPU_Tick();
		  break;
		}
	    }

	  //===================================================
	  // Calculate Stop Time And End Tick
	  //===================================================
	  //timeStart = timeStop;

	  while(1)
	    {
	      timeStop = time_Get_Time();
	      if( ( timeStop - timeStart ) > 100 )
		{
		  endTick = get_CPU_Tick();
		  break;
		}
	    }

	  //===================================================
	  // Return The Processors Speed In Hertz
	  //===================================================
	  boost::int64_t elapsed_time = timeStop - timeStart;
	  boost::int64_t diff = endTick - startTick;
	  return ( diff / ( elapsed_time * 1000 ) );
	}

      static inline boost::uint64_t calculate_Elapsed_Time ( boost::uint64_t startTick,
							     boost::uint64_t stopTick,
							     boost::uint64_t ticks_per_usec )
      {
	boost::int64_t diff = stopTick - startTick;
	boost::uint64_t microseconds = diff / ticks_per_usec;
	return microseconds;
      }

    };

  } /* namespace count */
} /* namespace reverse */

#endif /* COUNTER_H_ */
