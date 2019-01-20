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
#include "strategy/exhaustion_error.hpp"
#include "strategy/infinity.hpp"
#include "strategy/ratio.hpp"
#include "strategy/unavailable_error.hpp"
#include "strategy/undefined_ratio_error.hpp"

#include <CppUTest/TestHarness.h>

using deepnum::clarith::protocol::Protocol;

namespace deepnum
{
namespace clarith
{
namespace strategy
{

class TestableRatio : public Ratio
{
 public:
    TestableRatio(int num, int den) : Ratio(num, den) {}
    TestableRatio(unsigned int num, unsigned int den, bool positive)
            : Ratio(num, den, positive) {}
    unsigned int GetNum() { return num_; }
    unsigned int GetDen() { return den_; }
    bool GetPositive() { return positive_; }
};

TEST_GROUP(RatioTest)
{
};

TEST(RatioTest, ParsesSignedParameters1)
{
    TestableRatio ratio(-1, -1);
    LONGS_EQUAL(1, ratio.GetNum());
    LONGS_EQUAL(1, ratio.GetDen());
    CHECK_TRUE(ratio.GetPositive());
}

TEST(RatioTest, ParsesSignedParameters2)
{
    TestableRatio ratio(-1, 1);
    LONGS_EQUAL(1, ratio.GetNum());
    LONGS_EQUAL(1, ratio.GetDen());
    CHECK_FALSE(ratio.GetPositive());
}

TEST(RatioTest, ParsesSignedParameters3)
{
    TestableRatio ratio(1, -1);
    LONGS_EQUAL(1, ratio.GetNum());
    LONGS_EQUAL(1, ratio.GetDen());
    CHECK_FALSE(ratio.GetPositive());
}

TEST(RatioTest, ParsesSignedParameters4)
{
    TestableRatio ratio(1, 1);
    LONGS_EQUAL(1, ratio.GetNum());
    LONGS_EQUAL(1, ratio.GetDen());
    CHECK_TRUE(ratio.GetPositive());
}

TEST(RatioTest, ParsesSignedParameters5)
{
    TestableRatio ratio(std::numeric_limits<int>::lowest(),
                        std::numeric_limits<int>::lowest());
    LONGS_EQUAL(static_cast<unsigned int>(
            std::abs(std::numeric_limits<int>::lowest() + 1)) + 1,
            ratio.GetNum());
    LONGS_EQUAL(static_cast<unsigned int>(
            std::abs(std::numeric_limits<int>::lowest() + 1)) + 1,
            ratio.GetDen());
    CHECK_TRUE(ratio.GetPositive());
}

TEST(RatioTest, ParsesSignedParameters6)
{
    TestableRatio ratio(std::numeric_limits<int>::lowest(),
                        std::numeric_limits<int>::max());
    LONGS_EQUAL(static_cast<unsigned int>(
            std::abs(std::numeric_limits<int>::lowest() + 1)) + 1,
            ratio.GetNum());
    LONGS_EQUAL(std::numeric_limits<int>::max(), ratio.GetDen());
    CHECK_FALSE(ratio.GetPositive());
}

TEST(RatioTest, ParsesSignedParameters7)
{
    TestableRatio ratio(std::numeric_limits<int>::max(),
                        std::numeric_limits<int>::lowest());
    LONGS_EQUAL(std::numeric_limits<int>::max(), ratio.GetNum());
    LONGS_EQUAL(static_cast<unsigned int>(
            std::abs(std::numeric_limits<int>::lowest() + 1)) + 1,
            ratio.GetDen());
    CHECK_FALSE(ratio.GetPositive());
}

TEST(RatioTest, ParsesSignedParameters8)
{
    TestableRatio ratio(std::numeric_limits<int>::max(),
                        std::numeric_limits<int>::max());
    LONGS_EQUAL(std::numeric_limits<int>::max(), ratio.GetNum());
    LONGS_EQUAL(std::numeric_limits<int>::max(), ratio.GetDen());
    CHECK_TRUE(ratio.GetPositive());
}

TEST(RatioTest, ThrowsOnUndefinedRatio)
{
    CHECK_THROWS(UndefinedRatioError, TestableRatio(0, 0, true));
}

TEST(RatioTest, DoesNotProvideNewStrategyOnNonInfiniteRatio)
{
    CHECK_THROWS(UnavailableError, TestableRatio(0, 1, true).GetNewStrategy());
}

TEST(RatioTest, DegeneratesToInfinityOnInfiniteRatio1)
{
    TestableRatio s1(1, 0, true);
    CHECK_THROWS(ExhaustionError, s1.Egest());
    Strategy* s2 = s1.GetNewStrategy();
    CHECK_TRUE(dynamic_cast<Infinity*>(s2));
    delete s2;
}

TEST(RatioTest, DegeneratesToInfinityOnInfiniteRatio2)
{
    TestableRatio s1(std::numeric_limits<unsigned int>::max(), 0, true);
    CHECK_THROWS(ExhaustionError, s1.Egest());
    Strategy* s2 = s1.GetNewStrategy();
    CHECK_TRUE(dynamic_cast<Infinity*>(s2));
    delete s2;
}

TEST(RatioTest, CanExpressAtLeastTwo1)
{
    LONGS_EQUAL(Protocol::kTwo, TestableRatio(2, 1, true).Egest());
}

TEST(RatioTest, CanExpressAtLeastTwo2)
{
    LONGS_EQUAL(Protocol::kTwo,
                TestableRatio(std::numeric_limits<unsigned int>::max(),
                      std::numeric_limits<unsigned int>::max() / 2,
                      true).Egest());
}

TEST(RatioTest, CanExpressAtLeastOne1)
{
    LONGS_EQUAL(Protocol::kOne, TestableRatio(1, 1, true).Egest());
}

TEST(RatioTest, CanExpressAtLeastOne2)
{
    LONGS_EQUAL(Protocol::kOne,
                TestableRatio(std::numeric_limits<unsigned int>::max(),
                      std::numeric_limits<unsigned int>::max(),
                      true).Egest());
}

TEST(RatioTest, CanExpressAtLeastZero)
{
    LONGS_EQUAL(Protocol::kZero, TestableRatio(0, 1, true).Egest());
}

TEST(RatioTest, CanExpressAtLeastZero2)
{
    LONGS_EQUAL(Protocol::kZero,
                TestableRatio(0, std::numeric_limits<unsigned int>::max(),
                      true).Egest());
}

TEST(RatioTest, CanExpressNegative)
{
    LONGS_EQUAL(Protocol::kNeg, TestableRatio(1, 1, false).Egest());
}

TEST(RatioTest, CanExpressNegativeInfinity1)
{
    LONGS_EQUAL(Protocol::kNeg, TestableRatio(1, 0, false).Egest());
}

TEST(RatioTest, CanExpressNegativeInfinity2)
{
    LONGS_EQUAL(Protocol::kNeg, TestableRatio(
            std::numeric_limits<unsigned int>::max(), 0, false) .Egest());
}

TEST(RatioTest, CanExpressNegativeZero)
{
    LONGS_EQUAL(Protocol::kNeg, TestableRatio(0, 1, false).Egest());
}

}  // namespace strategy
}  // namespace clarith
}  // namespace deepnum

