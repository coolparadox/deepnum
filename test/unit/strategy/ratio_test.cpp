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

#include "protocol/protocol.hpp"
#include "strategy/exhaustion_error.hpp"
#include "strategy/ratio.hpp"
#include "strategy/unavailable_error.hpp"

using coolparadox::number::reducer::protocol::Protocol;

namespace coolparadox {
namespace number {
namespace reducer {
namespace strategy {

TEST_GROUP(RatioTest) {
};

/*

TEST(RatioTest, DoesNotProvideNewStrategy) {
    CHECK_THROWS(UnavailableError, Ratio(0, 1).GetNewStrategy());
}

TEST(RatioTest, DegeneratesToInfinite) {
    std::unique_ptr<Strategy> strategy(new Ratio(1, 0));
    CHECK_THROWS(ExhaustionError, strategy->Reduce());
    strategy = strategy->GetNewStrategy();
    LONGS_EQUAL(Protocol::kEnd, strategy->Reduce());
}

*/

}  // namespace strategy
}  // namespace reducer
}  // namespace number
}  // namespace coolparadox

