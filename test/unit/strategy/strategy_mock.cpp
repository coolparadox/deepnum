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

#include <CppUTestExt/MockSupport.h>

#include "strategy/strategy_mock.hpp"
#include "strategy/exhaustion_error.hpp"
#include "strategy/unavailable_error.hpp"

namespace coolparadox {
namespace number {
namespace reducer {
namespace strategy {

StrategyMock::StrategyMock(bool exhausted)
        : exhausted_ (exhausted) {
}

Protocol StrategyMock::Reduce() {
    mock().actualCall("Reduce").onObject(this);
    if (exhausted_) {
        throw ExhaustionError();
    }
}

std::unique_ptr<Strategy> StrategyMock::GetNewStrategy() const {
    mock().actualCall("GetNewStrategy").onObject(this);
    if (!exhausted_) {
        throw UnavailableError();
    }
    return std::make_unique<StrategyMock>();
}

}  // namespace strategy
}  // namespace reducer
}  // namespace number
}  // namespace coolparadox

