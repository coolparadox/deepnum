/*
 * Copyright 2018 Rafael Lorandi <coolparadox@gmail.com>
 *
 * This file is part of dn-clarith, a library for performing arithmetic
 * in continued logarithm representation.
 * 
 * dn-clarith is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * dn-clarith is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with dn-clarith.  If not, see <http://www.gnu.org/licenses/>
 */

#include "protocol/protocol.hpp"
#include "strategy/strategy_mock.hpp"
#include "strategy/exhaustion_error.hpp"
#include "strategy/unavailable_error.hpp"

#include <CppUTestExt/MockSupport.h>

using deepnum::clarith::protocol::Protocol;

namespace deepnum
{
namespace clarith
{
namespace strategy
{

StrategyMock::StrategyMock(bool exhausted)
        : exhausted_ (exhausted)
{
}

Protocol StrategyMock::Egest()
{
    mock().actualCall("Egest").onObject(this);
    if (exhausted_)
    {
        throw ExhaustionError();
    }
    return Protocol::End;
}

gsl::owner<Strategy*> StrategyMock::GetNewStrategy() const
{
    mock().actualCall("GetNewStrategy").onObject(this);
    if (!exhausted_)
    {
        throw UnavailableError();
    }
    return gsl::owner<StrategyMock*>(new StrategyMock);
}

}  // namespace strategy
}  // namespace clarith
}  // namespace deepnum

