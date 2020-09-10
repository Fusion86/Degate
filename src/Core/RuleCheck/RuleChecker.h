/**
 * This file is part of the IC reverse engineering tool Degate.
 *
 * Copyright 2008, 2009, 2010 by Martin Schobert
 * Copyright 2019-2020 Dorian Bachelot
 *
 * Degate is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * Degate is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with degate. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __RULECHECKER_H__
#define __RULECHECKER_H__

#include "Core/RuleCheck/RCBase.h"
#include "Core/RuleCheck/ERCOpenPorts.h"
#include "Core/RuleCheck/ERCNet.h"

namespace degate
{
	class RuleChecker : public RCBase
	{
	private:

		std::list<RCBase_shptr> checks;

	public:

		RuleChecker() : RCBase("rc-all", "A collection of all RCs.", RC_UNDEFINED)
		{
			checks.push_back(RCBase_shptr(new ERCOpenPorts()));
			checks.push_back(RCBase_shptr(new ERCNet()));
		}

		void run(LogicModel_shptr lmodel)
		{
			debug(TM, "run RC");

			clear_rc_violations();

			BOOST_FOREACH(RCBase_shptr check, checks)
			{
				std::cout << "RC: " << check->get_rc_class_name() << std::endl;
				check->run(lmodel);
				BOOST_FOREACH(RCViolation_shptr violation, check->get_rc_violations())
				{
					add_rc_violation(violation);
				}
			}

			debug(TM, "found %d rc violations.", get_rc_violations().size());
		}
	};
}

#endif
