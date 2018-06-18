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
#include "strategy/infinity.hpp"
#include "strategy/ratio.hpp"
#include "strategy/unavailable_error.hpp"
#include "strategy/undefined_ratio_error.hpp"

using deepnum::clarith::protocol::Protocol;

namespace deepnum {
namespace clarith {
namespace strategy {

TEST_GROUP(RatioTest) {
};

TEST(RatioTest, ThrowsOnUndefinedRatio) {
    CHECK_THROWS(UndefinedRatioError, Ratio(0, 0));
}

TEST(RatioTest, DoesNotProvideNewStrategyOnNonInfiniteRatio) {
    CHECK_THROWS(UnavailableError, Ratio(0, 1).GetNewStrategy());
}

TEST(RatioTest, DegeneratesToInfinityOnInfiniteRatio) {
    Ratio ratio(1, 0);
    CHECK_THROWS(ExhaustionError, ratio.Reduce());
    CHECK_TRUE(dynamic_cast<Infinity*>(ratio.GetNewStrategy().get()));
}

TEST(RatioTest, DegeneratesToInfinityOnInfiniteRatio2) {
    Ratio ratio(std::numeric_limits<int>::max(), 0);
    CHECK_THROWS(ExhaustionError, ratio.Reduce());
    CHECK_TRUE(dynamic_cast<Infinity*>(ratio.GetNewStrategy().get()));
}

TEST(RatioTest, CanExpressAtLeastTwo) {
    LONGS_EQUAL(Protocol::kTwo, Ratio(2, 1).Reduce());
}

TEST(RatioTest, CanExpressAtLeastTwo2) {
    LONGS_EQUAL(Protocol::kTwo,
                Ratio(std::numeric_limits<int>::max(),
                      std::numeric_limits<int>::max() / 2).Reduce());
}

TEST(RatioTest, CanExpressAtLeastTwo3) {
    LONGS_EQUAL(Protocol::kTwo,
                Ratio(std::numeric_limits<int>::min(),
                      std::numeric_limits<int>::min() / 2).Reduce());
}

TEST(RatioTest, CanExpressAtLeastOne) {
    LONGS_EQUAL(Protocol::kOne, Ratio(1, 1).Reduce());
}

TEST(RatioTest, CanExpressAtLeastOne2) {
    LONGS_EQUAL(Protocol::kOne,
                Ratio(std::numeric_limits<int>::max(),
                      std::numeric_limits<int>::max()).Reduce());
}

TEST(RatioTest, CanExpressAtLeastOne3) {
    LONGS_EQUAL(Protocol::kOne,
                Ratio(std::numeric_limits<int>::min(),
                      std::numeric_limits<int>::min()).Reduce());
}

TEST(RatioTest, CanExpressAtLeastZero) {
    LONGS_EQUAL(Protocol::kZero, Ratio(0, 1).Reduce());
}

TEST(RatioTest, CanExpressAtLeastZero2) {
    LONGS_EQUAL(Protocol::kZero,
                Ratio(0, std::numeric_limits<int>::max()).Reduce());
}

TEST(RatioTest, CanExpressNegative) {
    LONGS_EQUAL(Protocol::kNeg, Ratio(-1, 1).Reduce());
}

TEST(RatioTest, CanExpressNegative2) {
    LONGS_EQUAL(Protocol::kNeg,
                Ratio(-1, std::numeric_limits<int>::max()).Reduce());
}

TEST(RatioTest, CanExpressNegative3) {
    LONGS_EQUAL(Protocol::kNeg, Ratio(1, -1).Reduce());
}

TEST(RatioTest, CanExpressNegative4) {
    LONGS_EQUAL(Protocol::kNeg,
                Ratio(1, std::numeric_limits<int>::min()).Reduce());
}

TEST(RatioTest, CanExpressNegative5) {
    LONGS_EQUAL(Protocol::kNeg,
                Ratio(std::numeric_limits<int>::max(),
                      std::numeric_limits<int>::min()).Reduce());
}

TEST(RatioTest, CanExpressNegative6) {
    LONGS_EQUAL(Protocol::kNeg,
                Ratio(std::numeric_limits<int>::min(),
                      std::numeric_limits<int>::max()).Reduce());
}

TEST(RatioTest, CanExpressNegativeInfinity) {
    LONGS_EQUAL(Protocol::kNeg, Ratio(-1, 0).Reduce());
}

TEST(RatioTest, CanExpressNegativeInfinity2) {
    LONGS_EQUAL(Protocol::kNeg,
                Ratio(std::numeric_limits<int>::min(), 0).Reduce());
}

TEST(RatioTest, CanExpressNegativeZero) {
    LONGS_EQUAL(Protocol::kNeg, Ratio(0, -1).Reduce());
}

}  // namespace strategy
}  // namespace clarith
}  // namespace deepnum

