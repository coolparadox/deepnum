/*
 * Copyright 2019 Rafael Lorandi <coolparadox@gmail.com>
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

// #include <memory>
#include <forward_list>
#include <CppUTest/TestHarness.h>

#include "number.hpp"
#include "protocol/protocol.hpp"
// #include "protocol/violation_error.hpp"
// #include "strategy/strategy.hpp"
// #include "strategy/infinity.hpp"
#include "strategy/playback.hpp"
// #include "strategy/exhaustion_error.hpp"
// #include "strategy/unavailable_error.hpp"
#include "util.hpp"

using deepnum::clarith::protocol::Protocol;
// using deepnum::clarith::protocol::ViolationError;
// using deepnum::clarith::strategy::Strategy;
using deepnum::clarith::strategy::Playback;

namespace deepnum
{
namespace clarith
{

#define KE Protocol::kEnd
#define K2 Protocol::kTwo
#define K1 Protocol::kOne
#define K0 Protocol::kZero
#define KN Protocol::kNeg

#define NEG_INF KN,INF
#define NEG_THREE KN,THREE
#define NEG_TWO KN,TWO
#define NEG_ONE KN,ONE
#define NEG_ONE_HALF KN,ONE_HALF
#define NEG_ONE_THIRD KN,ONE_THIRD
#define NEG_ZERO KN,ZERO
#define ZERO K0,INF
#define ONE_THIRD K0,THREE
#define ONE_HALF K0,TWO
#define ONE K1,INF
#define TWO K2,ONE
#define THREE K2,K1,TWO
#define INF KE

#define NUMBER(SEQ) std::make_unique<Number>(std::make_unique<Playback>(std::unique_ptr<std::forward_list<Protocol>>(new std::forward_list<Protocol> { SEQ })))

#define VERIFY(EXPECTED,A,B) LONGS_EQUAL(EXPECTED, Util::Compare(A,B,true));

TEST_GROUP(UtilCompareTest)
{
};

TEST(UtilCompareTest, NegativeInfinity)
{
    VERIFY(0, NUMBER(NEG_INF), NUMBER(NEG_INF))
    VERIFY(-1, NUMBER(NEG_INF), NUMBER(NEG_THREE))
    VERIFY(-1, NUMBER(NEG_INF), NUMBER(NEG_TWO))
    VERIFY(-1, NUMBER(NEG_INF), NUMBER(NEG_ONE))
    VERIFY(-1, NUMBER(NEG_INF), NUMBER(NEG_ONE_HALF))
    VERIFY(-1, NUMBER(NEG_INF), NUMBER(NEG_ONE_THIRD))
    VERIFY(-1, NUMBER(NEG_INF), NUMBER(NEG_ZERO))
    VERIFY(-1, NUMBER(NEG_INF), NUMBER(ZERO))
    VERIFY(-1, NUMBER(NEG_INF), NUMBER(ONE_THIRD))
    VERIFY(-1, NUMBER(NEG_INF), NUMBER(ONE_HALF))
    VERIFY(-1, NUMBER(NEG_INF), NUMBER(ONE))
    VERIFY(-1, NUMBER(NEG_INF), NUMBER(TWO))
    VERIFY(-1, NUMBER(NEG_INF), NUMBER(THREE))
    VERIFY(-1, NUMBER(NEG_INF), NUMBER(INF))
}

TEST(UtilCompareTest, NegativeThree)
{
    VERIFY(1, NUMBER(NEG_THREE), NUMBER(NEG_INF))
    VERIFY(0, NUMBER(NEG_THREE), NUMBER(NEG_THREE))
    VERIFY(-1, NUMBER(NEG_THREE), NUMBER(NEG_TWO))
    VERIFY(-1, NUMBER(NEG_THREE), NUMBER(NEG_ONE))
    VERIFY(-1, NUMBER(NEG_THREE), NUMBER(NEG_ONE_HALF))
    VERIFY(-1, NUMBER(NEG_THREE), NUMBER(NEG_ONE_THIRD))
    VERIFY(-1, NUMBER(NEG_THREE), NUMBER(NEG_ZERO))
    VERIFY(-1, NUMBER(NEG_THREE), NUMBER(ZERO))
    VERIFY(-1, NUMBER(NEG_THREE), NUMBER(ONE_THIRD))
    VERIFY(-1, NUMBER(NEG_THREE), NUMBER(ONE_HALF))
    VERIFY(-1, NUMBER(NEG_THREE), NUMBER(ONE))
    VERIFY(-1, NUMBER(NEG_THREE), NUMBER(TWO))
    VERIFY(-1, NUMBER(NEG_THREE), NUMBER(THREE))
    VERIFY(-1, NUMBER(NEG_THREE), NUMBER(INF))
}

TEST(UtilCompareTest, NegativeTwo)
{
    VERIFY(1, NUMBER(NEG_TWO), NUMBER(NEG_INF))
    VERIFY(1, NUMBER(NEG_TWO), NUMBER(NEG_THREE))
    VERIFY(0, NUMBER(NEG_TWO), NUMBER(NEG_TWO))
    VERIFY(-1, NUMBER(NEG_TWO), NUMBER(NEG_ONE))
    VERIFY(-1, NUMBER(NEG_TWO), NUMBER(NEG_ONE_HALF))
    VERIFY(-1, NUMBER(NEG_TWO), NUMBER(NEG_ONE_THIRD))
    VERIFY(-1, NUMBER(NEG_TWO), NUMBER(NEG_ZERO))
    VERIFY(-1, NUMBER(NEG_TWO), NUMBER(ZERO))
    VERIFY(-1, NUMBER(NEG_TWO), NUMBER(ONE_THIRD))
    VERIFY(-1, NUMBER(NEG_TWO), NUMBER(ONE_HALF))
    VERIFY(-1, NUMBER(NEG_TWO), NUMBER(ONE))
    VERIFY(-1, NUMBER(NEG_TWO), NUMBER(TWO))
    VERIFY(-1, NUMBER(NEG_TWO), NUMBER(THREE))
    VERIFY(-1, NUMBER(NEG_TWO), NUMBER(INF))
}

TEST(UtilCompareTest, NegativeOne)
{
    VERIFY(1, NUMBER(NEG_ONE), NUMBER(NEG_INF))
    VERIFY(1, NUMBER(NEG_ONE), NUMBER(NEG_THREE))
    VERIFY(1, NUMBER(NEG_ONE), NUMBER(NEG_TWO))
    VERIFY(0, NUMBER(NEG_ONE), NUMBER(NEG_ONE))
    VERIFY(-1, NUMBER(NEG_ONE), NUMBER(NEG_ONE_HALF))
    VERIFY(-1, NUMBER(NEG_ONE), NUMBER(NEG_ONE_THIRD))
    VERIFY(-1, NUMBER(NEG_ONE), NUMBER(NEG_ZERO))
    VERIFY(-1, NUMBER(NEG_ONE), NUMBER(ZERO))
    VERIFY(-1, NUMBER(NEG_ONE), NUMBER(ONE_THIRD))
    VERIFY(-1, NUMBER(NEG_ONE), NUMBER(ONE_HALF))
    VERIFY(-1, NUMBER(NEG_ONE), NUMBER(ONE))
    VERIFY(-1, NUMBER(NEG_ONE), NUMBER(TWO))
    VERIFY(-1, NUMBER(NEG_ONE), NUMBER(THREE))
    VERIFY(-1, NUMBER(NEG_ONE), NUMBER(INF))
}

TEST(UtilCompareTest, NegativeOneHalf)
{
    VERIFY(1, NUMBER(NEG_ONE_HALF), NUMBER(NEG_INF))
    VERIFY(1, NUMBER(NEG_ONE_HALF), NUMBER(NEG_THREE))
    VERIFY(1, NUMBER(NEG_ONE_HALF), NUMBER(NEG_TWO))
    VERIFY(1, NUMBER(NEG_ONE_HALF), NUMBER(NEG_ONE))
    VERIFY(0, NUMBER(NEG_ONE_HALF), NUMBER(NEG_ONE_HALF))
    VERIFY(-1, NUMBER(NEG_ONE_HALF), NUMBER(NEG_ONE_THIRD))
    VERIFY(-1, NUMBER(NEG_ONE_HALF), NUMBER(NEG_ZERO))
    VERIFY(-1, NUMBER(NEG_ONE_HALF), NUMBER(ZERO))
    VERIFY(-1, NUMBER(NEG_ONE_HALF), NUMBER(ONE_THIRD))
    VERIFY(-1, NUMBER(NEG_ONE_HALF), NUMBER(ONE_HALF))
    VERIFY(-1, NUMBER(NEG_ONE_HALF), NUMBER(ONE))
    VERIFY(-1, NUMBER(NEG_ONE_HALF), NUMBER(TWO))
    VERIFY(-1, NUMBER(NEG_ONE_HALF), NUMBER(THREE))
    VERIFY(-1, NUMBER(NEG_ONE_HALF), NUMBER(INF))
}

TEST(UtilCompareTest, NegativeOneThird)
{
    VERIFY(1, NUMBER(NEG_ONE_THIRD), NUMBER(NEG_INF))
    VERIFY(1, NUMBER(NEG_ONE_THIRD), NUMBER(NEG_THREE))
    VERIFY(1, NUMBER(NEG_ONE_THIRD), NUMBER(NEG_TWO))
    VERIFY(1, NUMBER(NEG_ONE_THIRD), NUMBER(NEG_ONE))
    VERIFY(1, NUMBER(NEG_ONE_THIRD), NUMBER(NEG_ONE_HALF))
    VERIFY(0, NUMBER(NEG_ONE_THIRD), NUMBER(NEG_ONE_THIRD))
    VERIFY(-1, NUMBER(NEG_ONE_THIRD), NUMBER(NEG_ZERO))
    VERIFY(-1, NUMBER(NEG_ONE_THIRD), NUMBER(ZERO))
    VERIFY(-1, NUMBER(NEG_ONE_THIRD), NUMBER(ONE_THIRD))
    VERIFY(-1, NUMBER(NEG_ONE_THIRD), NUMBER(ONE_HALF))
    VERIFY(-1, NUMBER(NEG_ONE_THIRD), NUMBER(ONE))
    VERIFY(-1, NUMBER(NEG_ONE_THIRD), NUMBER(TWO))
    VERIFY(-1, NUMBER(NEG_ONE_THIRD), NUMBER(THREE))
    VERIFY(-1, NUMBER(NEG_ONE_THIRD), NUMBER(INF))
}

TEST(UtilCompareTest, NegativeZero)
{
    VERIFY(1, NUMBER(NEG_ZERO), NUMBER(NEG_INF))
    VERIFY(1, NUMBER(NEG_ZERO), NUMBER(NEG_THREE))
    VERIFY(1, NUMBER(NEG_ZERO), NUMBER(NEG_TWO))
    VERIFY(1, NUMBER(NEG_ZERO), NUMBER(NEG_ONE))
    VERIFY(1, NUMBER(NEG_ZERO), NUMBER(NEG_ONE_HALF))
    VERIFY(1, NUMBER(NEG_ZERO), NUMBER(NEG_ONE_THIRD))
    VERIFY(0, NUMBER(NEG_ZERO), NUMBER(NEG_ZERO))
    VERIFY(-1, NUMBER(NEG_ZERO), NUMBER(ZERO))
    VERIFY(-1, NUMBER(NEG_ZERO), NUMBER(ONE_THIRD))
    VERIFY(-1, NUMBER(NEG_ZERO), NUMBER(ONE_HALF))
    VERIFY(-1, NUMBER(NEG_ZERO), NUMBER(ONE))
    VERIFY(-1, NUMBER(NEG_ZERO), NUMBER(TWO))
    VERIFY(-1, NUMBER(NEG_ZERO), NUMBER(THREE))
    VERIFY(-1, NUMBER(NEG_ZERO), NUMBER(INF))
}

TEST(UtilCompareTest, Zero)
{
    VERIFY(1, NUMBER(ZERO), NUMBER(NEG_INF))
    VERIFY(1, NUMBER(ZERO), NUMBER(NEG_THREE))
    VERIFY(1, NUMBER(ZERO), NUMBER(NEG_TWO))
    VERIFY(1, NUMBER(ZERO), NUMBER(NEG_ONE))
    VERIFY(1, NUMBER(ZERO), NUMBER(NEG_ONE_HALF))
    VERIFY(1, NUMBER(ZERO), NUMBER(NEG_ONE_THIRD))
    VERIFY(1, NUMBER(ZERO), NUMBER(NEG_ZERO))
    VERIFY(0, NUMBER(ZERO), NUMBER(ZERO))
    VERIFY(-1, NUMBER(ZERO), NUMBER(ONE_THIRD))
    VERIFY(-1, NUMBER(ZERO), NUMBER(ONE_HALF))
    VERIFY(-1, NUMBER(ZERO), NUMBER(ONE))
    VERIFY(-1, NUMBER(ZERO), NUMBER(TWO))
    VERIFY(-1, NUMBER(ZERO), NUMBER(THREE))
    VERIFY(-1, NUMBER(ZERO), NUMBER(INF))
}

TEST(UtilCompareTest, OneThird)
{
    VERIFY(1, NUMBER(ONE_THIRD), NUMBER(NEG_INF))
    VERIFY(1, NUMBER(ONE_THIRD), NUMBER(NEG_THREE))
    VERIFY(1, NUMBER(ONE_THIRD), NUMBER(NEG_TWO))
    VERIFY(1, NUMBER(ONE_THIRD), NUMBER(NEG_ONE))
    VERIFY(1, NUMBER(ONE_THIRD), NUMBER(NEG_ONE_HALF))
    VERIFY(1, NUMBER(ONE_THIRD), NUMBER(NEG_ONE_THIRD))
    VERIFY(1, NUMBER(ONE_THIRD), NUMBER(NEG_ZERO))
    VERIFY(1, NUMBER(ONE_THIRD), NUMBER(ZERO))
    VERIFY(0, NUMBER(ONE_THIRD), NUMBER(ONE_THIRD))
    VERIFY(-1, NUMBER(ONE_THIRD), NUMBER(ONE_HALF))
    VERIFY(-1, NUMBER(ONE_THIRD), NUMBER(ONE))
    VERIFY(-1, NUMBER(ONE_THIRD), NUMBER(TWO))
    VERIFY(-1, NUMBER(ONE_THIRD), NUMBER(THREE))
    VERIFY(-1, NUMBER(ONE_THIRD), NUMBER(INF))
}

TEST(UtilCompareTest, OneHalf)
{
    VERIFY(1, NUMBER(ONE_HALF), NUMBER(NEG_INF))
    VERIFY(1, NUMBER(ONE_HALF), NUMBER(NEG_THREE))
    VERIFY(1, NUMBER(ONE_HALF), NUMBER(NEG_TWO))
    VERIFY(1, NUMBER(ONE_HALF), NUMBER(NEG_ONE))
    VERIFY(1, NUMBER(ONE_HALF), NUMBER(NEG_ONE_HALF))
    VERIFY(1, NUMBER(ONE_HALF), NUMBER(NEG_ONE_THIRD))
    VERIFY(1, NUMBER(ONE_HALF), NUMBER(NEG_ZERO))
    VERIFY(1, NUMBER(ONE_HALF), NUMBER(ZERO))
    VERIFY(1, NUMBER(ONE_HALF), NUMBER(ONE_THIRD))
    VERIFY(0, NUMBER(ONE_HALF), NUMBER(ONE_HALF))
    VERIFY(-1, NUMBER(ONE_HALF), NUMBER(ONE))
    VERIFY(-1, NUMBER(ONE_HALF), NUMBER(TWO))
    VERIFY(-1, NUMBER(ONE_HALF), NUMBER(THREE))
    VERIFY(-1, NUMBER(ONE_HALF), NUMBER(INF))
}

TEST(UtilCompareTest, One)
{
    VERIFY(1, NUMBER(ONE), NUMBER(NEG_INF))
    VERIFY(1, NUMBER(ONE), NUMBER(NEG_THREE))
    VERIFY(1, NUMBER(ONE), NUMBER(NEG_TWO))
    VERIFY(1, NUMBER(ONE), NUMBER(NEG_ONE))
    VERIFY(1, NUMBER(ONE), NUMBER(NEG_ONE_HALF))
    VERIFY(1, NUMBER(ONE), NUMBER(NEG_ONE_THIRD))
    VERIFY(1, NUMBER(ONE), NUMBER(NEG_ZERO))
    VERIFY(1, NUMBER(ONE), NUMBER(ZERO))
    VERIFY(1, NUMBER(ONE), NUMBER(ONE_THIRD))
    VERIFY(1, NUMBER(ONE), NUMBER(ONE_HALF))
    VERIFY(0, NUMBER(ONE), NUMBER(ONE))
    VERIFY(-1, NUMBER(ONE), NUMBER(TWO))
    VERIFY(-1, NUMBER(ONE), NUMBER(THREE))
    VERIFY(-1, NUMBER(ONE), NUMBER(INF))
}

TEST(UtilCompareTest, Two)
{
    VERIFY(1, NUMBER(TWO), NUMBER(NEG_INF))
    VERIFY(1, NUMBER(TWO), NUMBER(NEG_THREE))
    VERIFY(1, NUMBER(TWO), NUMBER(NEG_TWO))
    VERIFY(1, NUMBER(TWO), NUMBER(NEG_ONE))
    VERIFY(1, NUMBER(TWO), NUMBER(NEG_ONE_HALF))
    VERIFY(1, NUMBER(TWO), NUMBER(NEG_ONE_THIRD))
    VERIFY(1, NUMBER(TWO), NUMBER(NEG_ZERO))
    VERIFY(1, NUMBER(TWO), NUMBER(ZERO))
    VERIFY(1, NUMBER(TWO), NUMBER(ONE_THIRD))
    VERIFY(1, NUMBER(TWO), NUMBER(ONE_HALF))
    VERIFY(1, NUMBER(TWO), NUMBER(ONE))
    VERIFY(0, NUMBER(TWO), NUMBER(TWO))
    VERIFY(-1, NUMBER(TWO), NUMBER(THREE))
    VERIFY(-1, NUMBER(TWO), NUMBER(INF))
}

TEST(UtilCompareTest, Three)
{
    VERIFY(1, NUMBER(THREE), NUMBER(NEG_INF))
    VERIFY(1, NUMBER(THREE), NUMBER(NEG_THREE))
    VERIFY(1, NUMBER(THREE), NUMBER(NEG_TWO))
    VERIFY(1, NUMBER(THREE), NUMBER(NEG_ONE))
    VERIFY(1, NUMBER(THREE), NUMBER(NEG_ONE_HALF))
    VERIFY(1, NUMBER(THREE), NUMBER(NEG_ONE_THIRD))
    VERIFY(1, NUMBER(THREE), NUMBER(NEG_ZERO))
    VERIFY(1, NUMBER(THREE), NUMBER(ZERO))
    VERIFY(1, NUMBER(THREE), NUMBER(ONE_THIRD))
    VERIFY(1, NUMBER(THREE), NUMBER(ONE_HALF))
    VERIFY(1, NUMBER(THREE), NUMBER(ONE))
    VERIFY(1, NUMBER(THREE), NUMBER(TWO))
    VERIFY(0, NUMBER(THREE), NUMBER(THREE))
    VERIFY(-1, NUMBER(THREE), NUMBER(INF))
}

TEST(UtilCompareTest, Infinity)
{
    VERIFY(1, NUMBER(INF), NUMBER(NEG_INF))
    VERIFY(1, NUMBER(INF), NUMBER(NEG_THREE))
    VERIFY(1, NUMBER(INF), NUMBER(NEG_TWO))
    VERIFY(1, NUMBER(INF), NUMBER(NEG_ONE))
    VERIFY(1, NUMBER(INF), NUMBER(NEG_ONE_HALF))
    VERIFY(1, NUMBER(INF), NUMBER(NEG_ONE_THIRD))
    VERIFY(1, NUMBER(INF), NUMBER(NEG_ZERO))
    VERIFY(1, NUMBER(INF), NUMBER(ZERO))
    VERIFY(1, NUMBER(INF), NUMBER(ONE_THIRD))
    VERIFY(1, NUMBER(INF), NUMBER(ONE_HALF))
    VERIFY(1, NUMBER(INF), NUMBER(ONE))
    VERIFY(1, NUMBER(INF), NUMBER(TWO))
    VERIFY(1, NUMBER(INF), NUMBER(THREE))
    VERIFY(0, NUMBER(INF), NUMBER(INF))
}

TEST(UtilCompareTest, NonPedanticZeroComparison)
{
    LONGS_EQUAL(0, Util::Compare(NUMBER(NEG_ZERO), NUMBER(ZERO)));
    LONGS_EQUAL(0, Util::Compare(NUMBER(ZERO), NUMBER(NEG_ZERO)));
}

}  // namespace clarith
}  // namespace deepnum

