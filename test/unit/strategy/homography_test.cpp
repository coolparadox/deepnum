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

#include "strategy/homography.hpp"

#include <CppUTest/TestHarness.h>

#include "number.hpp"
#include "protocol/protocol.hpp"
#include "strategy/zero.hpp"
#include "strategy/ratio.hpp"
#include "strategy/unavailable_error.hpp"
#include "strategy/exhaustion_error.hpp"
#include "strategy/undefined_ratio_error.hpp"
#include "util.hpp"

using deepnum::clarith::protocol::Protocol;
using deepnum::clarith::Number;

namespace deepnum
{
namespace clarith
{
namespace strategy
{

#define NEG_INFINITY new Number(new Ratio(-1, 0))
#define NEG_TWO new Number(new Ratio(-2, 1))
#define NEG_ONE new Number(new Ratio(-1, 1))
#define ZERO new Number(new Zero())
#define ONE_HALF new Number(new Ratio(1, 2))
#define ONE new Number(new Ratio(1, 1))
#define TWO new Number(new Ratio(2, 1))
#define THREE new Number(new Ratio(3, 1))
#define FOUR new Number(new Ratio(4, 1))
#define INFINITY new Number(new Ratio(1, 0))

#define UNITY1(x) Homography(x, 1, 0, 0, 1)
#define UNITY2(x) Homography(x, -1, 0, 0, -1)
// #define UNITY3(x) Homography(x, std::numeric_limits<int>::max(), 0, 0, std::numeric_limits<int>::max())
// #define UNITY4(x) Homography(x, std::numeric_limits<int>::lowest(), 0, 0, std::numeric_limits<int>::lowest())

TEST_GROUP(HomographyTest)
{
};

TEST(HomographyTest, ForbidsUndefinedHomography)
{
    CHECK_THROWS(UndefinedRatioError, Homography(ONE, 0, 0, 0, 0));
}

TEST(HomographyTest, DoesNotProvideNewStrategyWhenNotExhausted)
{
    CHECK_THROWS(UnavailableError, UNITY1(new Number(new Ratio(0, 1))).GetNewStrategy());
}

TEST(HomographyTest, DegeneratesToRatioOnEndOfInput)
{
    Homography s1 = UNITY1(ZERO);
    CHECK_THROWS(ExhaustionError, s1.Egest());
    Strategy* s2 = s1.GetNewStrategy();
    CHECK_TRUE(dynamic_cast<Ratio*>(s2));
    delete s2;
}

TEST(HomographyTest, DegeneratesToRatioOnDiscardedInput)
{
    Homography s1(TWO, 0, 1, 0, 1);
    CHECK_THROWS(ExhaustionError, s1.Egest());
    Strategy* s2 = s1.GetNewStrategy();
    CHECK_TRUE(dynamic_cast<Ratio*>(s2));
    delete s2;
}

TEST(HomographyTest, XByXIsOneAtOne)
{
    LONGS_EQUAL(0, Util::Compare(ONE, new Number(new Homography(ONE, 1, 0, 1, 0))));
    LONGS_EQUAL(0, Util::Compare(ONE, new Number(new Homography(ONE, -1, 0, -1, 0))));
}

TEST(HomographyTest, XByXIsUndefinedAtZero)
{

    {
        Number* z = ZERO;
        Number* h = new Number(new Homography(ZERO, 1, 0, 1, 0));
        CHECK_THROWS(UndefinedRatioError, Util::Compare(z, h));
        delete z;
        delete h;
    }
    
    {
        Number* z = ZERO;
        Number* h = new Number(new Homography(ZERO, -1, 0, -1, 0));
        CHECK_THROWS(UndefinedRatioError, Util::Compare(z, h));
        delete z;
        delete h;
    }
}

TEST(HomographyTest, XByZeroIsUndefinedAtZero)
{

    {
        Number* z = ZERO;
        Number* h = new Number(new Homography(ZERO, 1, 0, 0, 0));
        CHECK_THROWS(UndefinedRatioError, Util::Compare(z, h));
        delete z;
        delete h;
    }

    {
        Number* z = ZERO;
        Number* h = new Number(new Homography(ZERO, -1, 0, 0, 0));
        CHECK_THROWS(UndefinedRatioError, Util::Compare(z, h));
        delete z;
        delete h;
    }

}

TEST(HomographyTest, ZeroByXIsUndefinedAtZero)
{

    {
        Number* z = ZERO;
        Number* h = new Number(new Homography(ZERO, 0, 0, 1, 0));
        CHECK_THROWS(UndefinedRatioError, Util::Compare(z, h));
        delete z;
        delete h;
    }
    
    {
        Number* z = ZERO;
        Number* h = new Number(new Homography(ZERO, 0, 0, -1, 0));
        CHECK_THROWS(UndefinedRatioError, Util::Compare(z, h));
        delete z;
        delete h;
    }

}

TEST(HomographyTest, XByZeroIsInfinityAtOne)
{
    LONGS_EQUAL(0, Util::Compare(INFINITY, new Number(new Homography(ONE, 1, 0, 0, 0))));
}

TEST(HomographyTest, MinusXByZeroIsMinusInfinityAtOne)
{
    LONGS_EQUAL(0, Util::Compare(NEG_INFINITY, new Number(new Homography(ONE, -1, 0, 0, 0))));
}

TEST(HomographyTest, XByZeroIsMinusInfinityAtMinusOne)
{
    LONGS_EQUAL(0, Util::Compare(NEG_INFINITY, new Number(new Homography(NEG_ONE, 1, 0, 0, 0))));
}

TEST(HomographyTest, MinusXByZeroIsInfinityAtMinusOne)
{
    LONGS_EQUAL(0, Util::Compare(INFINITY, new Number(new Homography(NEG_ONE, -1, 0, 0, 0))));
}

TEST(HomographyTest, OneByXIsUndefinedAtZero)
{
    // lim(1/x) when x approaches 0 differs according to approaching side

    {
        Number* z = INFINITY;
        Number* h = new Number(new Homography(ZERO, 0, 1, 1, 0));
        CHECK_THROWS(UndefinedRatioError, Util::Compare(z, h));
        delete z;
        delete h;
    }
    
    {
        Number* z = INFINITY;
        Number* h = new Number(new Homography(ZERO, 0, -1, -1, 0));
        CHECK_THROWS(UndefinedRatioError, Util::Compare(z, h));
        delete z;
        delete h;
    }

}

TEST(HomographyTest, XIsZeroAtZero)
{
    LONGS_EQUAL(0, Util::Compare(ZERO, new Number(new UNITY1(ZERO))));
    LONGS_EQUAL(0, Util::Compare(ZERO, new Number(new UNITY2(ZERO))));
    // LONGS_EQUAL(0, Util::Compare(ZERO, new Number(new UNITY3(ZERO))));
    // LONGS_EQUAL(0, Util::Compare(ZERO, new Number(new UNITY4(ZERO))));
}

TEST(HomographyTest, XIsOneHalfAtOneHalf)
{
    LONGS_EQUAL(0, Util::Compare(ONE_HALF, new Number(new UNITY1(ONE_HALF))));
    LONGS_EQUAL(0, Util::Compare(ONE_HALF, new Number(new UNITY2(ONE_HALF))));
    // LONGS_EQUAL(0, Util::Compare(ONE_HALF, new Number(new UNITY3(ONE_HALF))));
    // LONGS_EQUAL(0, Util::Compare(ONE_HALF, new Number(new UNITY4(ONE_HALF))));
}

TEST(HomographyTest, XIsOneAtOne)
{
    LONGS_EQUAL(0, Util::Compare(ONE, new Number(new UNITY1(ONE))));
    LONGS_EQUAL(0, Util::Compare(ONE, new Number(new UNITY2(ONE))));
    // LONGS_EQUAL(0, Util::Compare(ONE, new Number(new UNITY3(ONE))));
    // LONGS_EQUAL(0, Util::Compare(ONE, new Number(new UNITY4(ONE))));
}

TEST(HomographyTest, XIsTwoAtTwo)
{
    LONGS_EQUAL(0, Util::Compare(TWO, new Number(new UNITY1(TWO))));
    LONGS_EQUAL(0, Util::Compare(TWO, new Number(new UNITY2(TWO))));
    // LONGS_EQUAL(0, Util::Compare(TWO, new Number(new UNITY3(TWO))));
    // LONGS_EQUAL(0, Util::Compare(TWO, new Number(new UNITY4(TWO))));
}

TEST(HomographyTest, XIsMinusOneAtMinusOne)
{
    LONGS_EQUAL(0, Util::Compare(NEG_ONE, new Number(new UNITY1(NEG_ONE))));
    LONGS_EQUAL(0, Util::Compare(NEG_ONE, new Number(new UNITY2(NEG_ONE))));
    // LONGS_EQUAL(0, Util::Compare(NEG_ONE, new Number(new UNITY3(NEG_ONE))));
    // LONGS_EQUAL(0, Util::Compare(NEG_ONE, new Number(new UNITY4(NEG_ONE))));
}

TEST(HomographyTest, XIsMinusTwoAtMinusTwo)
{
    LONGS_EQUAL(0, Util::Compare(NEG_TWO, new Number(new UNITY1(NEG_TWO))));
    LONGS_EQUAL(0, Util::Compare(NEG_TWO, new Number(new UNITY2(NEG_TWO))));
    // LONGS_EQUAL(0, Util::Compare(NEG_TWO, new Number(new UNITY3(NEG_TWO))));
    // LONGS_EQUAL(0, Util::Compare(NEG_TWO, new Number(new UNITY4(NEG_TWO))));
}

TEST(HomographyTest, XDoubledIsFourAtTwo)
{
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(TWO, 2, 0, 0, 1)), FOUR));
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(TWO, -2, 0, 0, -1)), FOUR));
}

TEST(HomographyTest, XHalvedIsOneAtTwo)
{
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(TWO, 1, 0, 0, 2)), ONE));
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(TWO, -1, 0, 0, -2)), ONE));
}

TEST(HomographyTest, XPlusOneIsThreeAtTwo)
{
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(TWO, 1, 1, 0, 1)), THREE));
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(TWO, -1, -1, 0, -1)), THREE));
}

TEST(HomographyTest, XMinusOneIsOneAtTwo)
{
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(TWO, 1, -1, 0, 1)), ONE));
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(TWO, -1, 1, 0, -1)), ONE));
}

TEST(HomographyTest, XReciprocatedIsOneHalfAtTwo)
{
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(TWO, 0, 1, 1, 0)), ONE_HALF));
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(TWO, 0, -1, -1, 0)), ONE_HALF));
}

TEST(HomographyTest, XNegatedIsMinusTwoAtTwo)
{
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(TWO, -1, 0, 0, 1)), NEG_TWO));
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(TWO, 1, 0, 0, -1)), NEG_TWO));
}

TEST(HomographyTest, XPlusOneIsInfinityAtInfinity)
{
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(INFINITY, 1, 1, 0, 1)), INFINITY));
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(INFINITY, -1, -1, 0, -1)), INFINITY));
}

TEST(HomographyTest, XPlusOneIsMinusInfinityAtMinusInfinity)
{
     LONGS_EQUAL(0, Util::Compare(new Number(new Homography(NEG_INFINITY, 1, 1, 0, 1)), NEG_INFINITY));
     LONGS_EQUAL(0, Util::Compare(new Number(new Homography(NEG_INFINITY, -1, -1, 0, -1)), NEG_INFINITY));
}

TEST(HomographyTest, XPlusOneReciprocatedIsZeroAtMinusInfinity)
{
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(NEG_INFINITY, 0, 1, 1, 1)), ZERO));
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(NEG_INFINITY, 0, -1, -1, -1)), ZERO));
}

TEST(HomographyTest, XPlusOneReciprocatedIsZeroAtInfinity)
{
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(INFINITY, 0, 1, 1, 1)), ZERO));
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(INFINITY, 0, -1, -1, -1)), ZERO));
}

TEST(HomographyTest, XPlusOneReciprocatedIsUndefinedAtMinusOne)
{

    {
        Number* z = ZERO;
        Number* h = new Number(new Homography(NEG_ONE, 0, 1, 1, 1));
        CHECK_THROWS(UndefinedRatioError, Util::Compare(z, h));
        delete z;
        delete h;
    }
    
    {
        Number* z = ZERO;
        Number* h = new Number(new Homography(NEG_ONE, 0, -1, -1, -1));
        CHECK_THROWS(UndefinedRatioError, Util::Compare(z, h));
        delete z;
        delete h;
    }

}

TEST(HomographyTest, XPlusOneOverXPlusOneIsOneAtMinusInfinity)
{
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(NEG_INFINITY, 1, 1, 1, 1)), ONE));
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(NEG_INFINITY, -1, -1, -1, -1)), ONE));
}

TEST(HomographyTest, XPlusOneOverXPlusOneIsOneAtInfinity)
{
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(INFINITY, 1, 1, 1, 1)), ONE));
    LONGS_EQUAL(0, Util::Compare(new Number(new Homography(INFINITY, -1, -1, -1, -1)), ONE));
}

}  // namespace strategy
}  // namespace clarith
}  // namespace deepnum

