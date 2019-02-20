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

#include "number.hpp"

#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

#include "strategy/zero.hpp"
#include "strategy/strategy_mock.hpp"

using deepnum::clarith::strategy::StrategyMock;

namespace deepnum
{
namespace clarith
{

TEST_GROUP(NumberTest)
{
    void teardown()
    {
        mock().clear();
    }
};

TEST(NumberTest, DelegatesEgestionToStrategy)
{
    gsl::owner<StrategyMock*> strategy { new StrategyMock(false) };
    mock().expectOneCall("Egest").onObject(strategy);
    Number(strategy).Egest();
    mock().checkExpectations();
}

TEST(NumberTest, ReplacesStrategyOnExhaustion)
{
    gsl::owner<StrategyMock*> strategy { new StrategyMock(true) };
    mock().expectOneCall("GetNewStrategy").onObject(strategy);
    mock().ignoreOtherCalls();
    Number(strategy).Egest();
    mock().checkExpectations();
}

}  // namespace clarith
}  // namespace deepnum

