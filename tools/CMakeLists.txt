cmake_minimum_required(VERSION 2.8)
project(reverse_tools)

set ( REVERSE_SOURCES
    reverse.cpp )

include_directories ( ${CMAKE_SOURCE_DIR} ${Boost_INCLUDE_DIRS} )

add_executable ( reverse ${REVERSE_SOURCES} reverse ${ADDITIONAL_LIBS} )
target_link_libraries ( reverse libreverse ${Boost_LIBRARIES} )

add_executable ( elfdump elfdump.cpp ${ADDITIONAL_LIBS} )
target_link_libraries ( elfdump libreverse ${Boost_LIBRARIES} )

#pedump_SOURCES = pedump.cpp
#pedump_CPPFLAGS = -I$(XTRA_INCLUDE)/usr/local/include
#pedump_LDFLAGS = -L$(XTRA_INCLUDE)/usr/local/lib -lreverse -lboost_program_options -lboost_date_time

#memory_map_SOURCES = memory_map.cpp
#memory_map_CPPFLAGS = -I$(XTRA_INCLUDE)/usr/local/include
#memory_map_LDFLAGS = -L$(XTRA_INCLUDE)/usr/local/lib -lreverse -lboost_program_options -lboost_date_time

#elfdump_SOURCES = elfdump.cpp
#elfdump_CPPFLAGS = -I$(XTRA_INCLUDE)/usr/local/include
#elfdump_LDFLAGS = -L$(XTRA_INCLUDE)/usr/local/lib -lreverse -lboost_program_options -lboost_date_time

#class_dump_SOURCES = class_dump.cpp
#class_dump_CPPFLAGS = -I$(XTRA_INCLUDE)/usr/local/include
#class_dump_LDFLAGS = -L$(XTRA_INCLUDE)/usr/local/lib -lreverse -lboost_program_options -lboost_date_time

#strings_SOURCES = strings.cpp
#strings_CPPFLAGS = -I$(XTRA_INCLUDE)/usr/local/include
#strings_LDFLAGS = -L$(XTRA_INCLUDE)/usr/local/lib -lreverse -lboost_program_options -lboost_date_time

#machdump_SOURCES = machdump.cpp
#machdump_CPPFLAGS = -I$(XTRA_INCLUDE)/usr/local/include
#machdump_LDFLAGS = -L$(XTRA_INCLUDE)/usr/local/lib -lreverse -lboost_program_options -lboost_date_time

#fatdump_SOURCES = fatdump.cpp
#fatdump_CPPFLAGS = -I$(XTRA_INCLUDE)/usr/local/include
#fatdump_LDFLAGS = -L$(XTRA_INCLUDE)/usr/local/lib -lreverse -lboost_program_options -lboost_date_time


