/*  InternalData.h

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

#ifndef INTERNAL_DATA_H
#define INTERNAL_DATA_H

//
// C++ Interface: InternalData
//
// Description:
//
//
// Author: Stephen Torri <storri@torri.org>, (C) 2005
//
// Copyright: See COPYING file that comes with this distribution
//
#include <map>
#include <boost/shared_ptr.hpp>

#include "CPU.h"
#include "Rule.h"
#include "Table.h"
#include "Token.h"

namespace parserGen
{
	class InternalData {
	private:
		typedef std::map < std::string, boost::shared_ptr<Table> > TableMap;
		typedef std::map < std::string, boost::shared_ptr<Token> > TokenMap;
		typedef std::map < std::string, boost::shared_ptr<Rule> > RuleMap;

		boost::shared_ptr<CPU> m_cpu;
		TableMap m_tableMap;
		TokenMap m_tokenMap;
		RuleMap m_ruleMap;

	public:
		void setCPU (boost::shared_ptr<CPU> cpu);
		void addTable (boost::shared_ptr<Table> table);	
		void addToken (boost::shared_ptr<Token> token);	
		void addRule (boost::shared_ptr<Rule> rule);
	};
}

#endif
