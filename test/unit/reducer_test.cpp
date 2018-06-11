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

#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

#include "reducer.hpp"
#include "strategy/strategy_mock.hpp"

using deepnum::clarith::strategy::StrategyMock;

namespace deepnum {
namespace clarith {

TEST_GROUP(ReducerTest) {
    void teardown() {
        mock().clear();
    }
};

TEST(ReducerTest, ReducesStrategy) {
    StrategyMock* strategy { new StrategyMock(false) };
    mock().expectOneCall("Reduce").onObject(strategy);
    Reducer(std::unique_ptr<StrategyMock>(strategy)).Reduce();
    mock().checkExpectations();
}

TEST(ReducerTest, ReplacesStrategyOnExhaustion) {
    StrategyMock* strategy { new StrategyMock(true) };
    mock().expectOneCall("GetNewStrategy").onObject(strategy);
    mock().ignoreOtherCalls();
    Reducer(std::unique_ptr<StrategyMock>(strategy)).Reduce();
    mock().checkExpectations();
}

}  // namespace clarith
}  // namespace deepnum

