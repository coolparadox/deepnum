/*
 * Copyright 2018 Rafael Lorandi <coolparadox@gmail.com>
 *
 * This file is part of coolparadox-number-reducer, a library for handling
 * rational numbers in continued log format.
 * 
 * coolparadox-number-reducer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * coolparadox-number-reducer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with coolparadox-number-reducer.  If not, see <http://www.gnu.org/licenses/>
 */

#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

#include "reducer.hpp"
#include "strategy/strategy_mock.hpp"

using coolparadox::number::reducer::strategy::StrategyMock;

namespace coolparadox {
namespace number {
namespace reducer {

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

}  // namespace reducer
}  // namespace number
}  // namespace coolparadox

