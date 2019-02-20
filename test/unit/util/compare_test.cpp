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

#include <forward_list>

#include "number.hpp"
#include "protocol/protocol.hpp"
#include "strategy/playback.hpp"
#include "util.hpp"

#include <CppUTest/TestHarness.h>

using deepnum::clarith::protocol::Protocol;
using deepnum::clarith::strategy::Playback;

namespace deepnum
{
namespace clarith
{

#define E Protocol::End
#define A Protocol::Amplify
#define U Protocol::Uncover
#define T Protocol::Turn
#define R Protocol::Reflect
#define G Protocol::Ground

#define NEG_INFINITY G,ZERO
#define NEG_THREE G,ONE_THIRD
#define NEG_TWO G,ONE_HALF
#define NEG_ONE R,ONE
#define NEG_ONE_HALF R,ONE_HALF
#define NEG_ONE_THIRD R,ONE_THIRD
#define ZERO E
#define ONE_THIRD A,U,ONE_HALF
#define ONE_HALF A,ONE
#define ONE U,ZERO
#define TWO T,ONE_HALF
#define THREE T,ONE_THIRD
#define INFINITY T,ZERO

#define NUMBER(SEQ) new Number(new Playback(new std::forward_list<Protocol> { SEQ }))
    
#define VERIFY(EXPECTED,A,B) LONGS_EQUAL(EXPECTED,Util::Compare(A,B));

gsl::owner<Number*> neg_infinity() { return NUMBER(NEG_INFINITY); }
gsl::owner<Number*> neg_three() { return NUMBER(NEG_THREE); }
gsl::owner<Number*> neg_two() { return NUMBER(NEG_TWO); }
gsl::owner<Number*> neg_one() { return NUMBER(NEG_ONE); }
gsl::owner<Number*> neg_one_half() { return NUMBER(NEG_ONE_HALF); }
gsl::owner<Number*> neg_one_third() { return NUMBER(NEG_ONE_THIRD); }
gsl::owner<Number*> zero() { return NUMBER(ZERO); }
gsl::owner<Number*> one_third() { return NUMBER(ONE_THIRD); }
gsl::owner<Number*> one_half() { return NUMBER(ONE_HALF); }
gsl::owner<Number*> one() { return NUMBER(ONE); }
gsl::owner<Number*> two() { return NUMBER(TWO); }
gsl::owner<Number*> three() { return NUMBER(THREE); }
gsl::owner<Number*> infinity() { return NUMBER(INFINITY); }

TEST_GROUP(UtilCompareTest)
{
};

TEST(UtilCompareTest, NegativeInfinity)
{
    VERIFY(0, neg_infinity(), neg_infinity())
    VERIFY(-1, neg_infinity(), neg_three())
    VERIFY(-1, neg_infinity(), neg_two())
    VERIFY(-1, neg_infinity(), neg_one())
    VERIFY(-1, neg_infinity(), neg_one_half())
    VERIFY(-1, neg_infinity(), neg_one_third())
    VERIFY(-1, neg_infinity(), zero())
    VERIFY(-1, neg_infinity(), one_third())
    VERIFY(-1, neg_infinity(), one_half())
    VERIFY(-1, neg_infinity(), one())
    VERIFY(-1, neg_infinity(), two())
    VERIFY(-1, neg_infinity(), three())
    VERIFY(-1, neg_infinity(), infinity())
}

TEST(UtilCompareTest, NegativeThree)
{
    VERIFY(1, neg_three(), neg_infinity())
    VERIFY(0, neg_three(), neg_three())
    VERIFY(-1, neg_three(), neg_two())
    VERIFY(-1, neg_three(), neg_one())
    VERIFY(-1, neg_three(), neg_one_half())
    VERIFY(-1, neg_three(), neg_one_third())
    VERIFY(-1, neg_three(), zero())
    VERIFY(-1, neg_three(), one_third())
    VERIFY(-1, neg_three(), one_half())
    VERIFY(-1, neg_three(), one())
    VERIFY(-1, neg_three(), two())
    VERIFY(-1, neg_three(), three())
    VERIFY(-1, neg_three(), infinity())
}

TEST(UtilCompareTest, NegativeTwo)
{
    VERIFY(1, neg_two(), neg_infinity())
    VERIFY(1, neg_two(), neg_three())
    VERIFY(0, neg_two(), neg_two())
    VERIFY(-1, neg_two(), neg_one())
    VERIFY(-1, neg_two(), neg_one_half())
    VERIFY(-1, neg_two(), neg_one_third())
    VERIFY(-1, neg_two(), zero())
    VERIFY(-1, neg_two(), one_third())
    VERIFY(-1, neg_two(), one_half())
    VERIFY(-1, neg_two(), one())
    VERIFY(-1, neg_two(), two())
    VERIFY(-1, neg_two(), three())
    VERIFY(-1, neg_two(), infinity())
}

TEST(UtilCompareTest, NegativeOne)
{
    VERIFY(1, neg_one(), neg_infinity())
    VERIFY(1, neg_one(), neg_three())
    VERIFY(1, neg_one(), neg_two())
    VERIFY(0, neg_one(), neg_one())
    VERIFY(-1, neg_one(), neg_one_half())
    VERIFY(-1, neg_one(), neg_one_third())
    VERIFY(-1, neg_one(), zero())
    VERIFY(-1, neg_one(), one_third())
    VERIFY(-1, neg_one(), one_half())
    VERIFY(-1, neg_one(), one())
    VERIFY(-1, neg_one(), two())
    VERIFY(-1, neg_one(), three())
    VERIFY(-1, neg_one(), infinity())
}

TEST(UtilCompareTest, NegativeOneHalf)
{
    VERIFY(1, neg_one_half(), neg_infinity())
    VERIFY(1, neg_one_half(), neg_three())
    VERIFY(1, neg_one_half(), neg_two())
    VERIFY(1, neg_one_half(), neg_one())
    VERIFY(0, neg_one_half(), neg_one_half())
    VERIFY(-1, neg_one_half(), neg_one_third())
    VERIFY(-1, neg_one_half(), zero())
    VERIFY(-1, neg_one_half(), one_third())
    VERIFY(-1, neg_one_half(), one_half())
    VERIFY(-1, neg_one_half(), one())
    VERIFY(-1, neg_one_half(), two())
    VERIFY(-1, neg_one_half(), three())
    VERIFY(-1, neg_one_half(), infinity())
}

TEST(UtilCompareTest, NegativeOneThird)
{
    VERIFY(1, neg_one_third(), neg_infinity())
    VERIFY(1, neg_one_third(), neg_three())
    VERIFY(1, neg_one_third(), neg_two())
    VERIFY(1, neg_one_third(), neg_one())
    VERIFY(1, neg_one_third(), neg_one_half())
    VERIFY(0, neg_one_third(), neg_one_third())
    VERIFY(-1, neg_one_third(), zero())
    VERIFY(-1, neg_one_third(), one_third())
    VERIFY(-1, neg_one_third(), one_half())
    VERIFY(-1, neg_one_third(), one())
    VERIFY(-1, neg_one_third(), two())
    VERIFY(-1, neg_one_third(), three())
    VERIFY(-1, neg_one_third(), infinity())
}

TEST(UtilCompareTest, Zero)
{
    VERIFY(1, zero(), neg_infinity())
    VERIFY(1, zero(), neg_three())
    VERIFY(1, zero(), neg_two())
    VERIFY(1, zero(), neg_one())
    VERIFY(1, zero(), neg_one_half())
    VERIFY(1, zero(), neg_one_third())
    VERIFY(0, zero(), zero())
    VERIFY(-1, zero(), one_third())
    VERIFY(-1, zero(), one_half())
    VERIFY(-1, zero(), one())
    VERIFY(-1, zero(), two())
    VERIFY(-1, zero(), three())
    VERIFY(-1, zero(), infinity())
}

TEST(UtilCompareTest, OneThird)
{
    VERIFY(1, one_third(), neg_infinity())
    VERIFY(1, one_third(), neg_three())
    VERIFY(1, one_third(), neg_two())
    VERIFY(1, one_third(), neg_one())
    VERIFY(1, one_third(), neg_one_half())
    VERIFY(1, one_third(), neg_one_third())
    VERIFY(1, one_third(), zero())
    VERIFY(0, one_third(), one_third())
    VERIFY(-1, one_third(), one_half())
    VERIFY(-1, one_third(), one())
    VERIFY(-1, one_third(), two())
    VERIFY(-1, one_third(), three())
    VERIFY(-1, one_third(), infinity())
}

TEST(UtilCompareTest, OneHalf)
{
    VERIFY(1, one_half(), neg_infinity())
    VERIFY(1, one_half(), neg_three())
    VERIFY(1, one_half(), neg_two())
    VERIFY(1, one_half(), neg_one())
    VERIFY(1, one_half(), neg_one_half())
    VERIFY(1, one_half(), neg_one_third())
    VERIFY(1, one_half(), zero())
    VERIFY(1, one_half(), one_third())
    VERIFY(0, one_half(), one_half())
    VERIFY(-1, one_half(), one())
    VERIFY(-1, one_half(), two())
    VERIFY(-1, one_half(), three())
    VERIFY(-1, one_half(), infinity())
}

TEST(UtilCompareTest, One)
{
    VERIFY(1, one(), neg_infinity())
    VERIFY(1, one(), neg_three())
    VERIFY(1, one(), neg_two())
    VERIFY(1, one(), neg_one())
    VERIFY(1, one(), neg_one_half())
    VERIFY(1, one(), neg_one_third())
    VERIFY(1, one(), zero())
    VERIFY(1, one(), one_third())
    VERIFY(1, one(), one_half())
    VERIFY(0, one(), one())
    VERIFY(-1, one(), two())
    VERIFY(-1, one(), three())
    VERIFY(-1, one(), infinity())
}

TEST(UtilCompareTest, Two)
{
    VERIFY(1, two(), neg_infinity())
    VERIFY(1, two(), neg_three())
    VERIFY(1, two(), neg_two())
    VERIFY(1, two(), neg_one())
    VERIFY(1, two(), neg_one_half())
    VERIFY(1, two(), neg_one_third())
    VERIFY(1, two(), zero())
    VERIFY(1, two(), one_third())
    VERIFY(1, two(), one_half())
    VERIFY(1, two(), one())
    VERIFY(0, two(), two())
    VERIFY(-1, two(), three())
    VERIFY(-1, two(), infinity())
}

TEST(UtilCompareTest, Three)
{
    VERIFY(1, three(), neg_infinity())
    VERIFY(1, three(), neg_three())
    VERIFY(1, three(), neg_two())
    VERIFY(1, three(), neg_one())
    VERIFY(1, three(), neg_one_half())
    VERIFY(1, three(), neg_one_third())
    VERIFY(1, three(), zero())
    VERIFY(1, three(), one_third())
    VERIFY(1, three(), one_half())
    VERIFY(1, three(), one())
    VERIFY(1, three(), two())
    VERIFY(0, three(), three())
    VERIFY(-1, three(), infinity())
}

TEST(UtilCompareTest, Infinity)
{
    VERIFY(1, infinity(), neg_infinity())
    VERIFY(1, infinity(), neg_three())
    VERIFY(1, infinity(), neg_two())
    VERIFY(1, infinity(), neg_one())
    VERIFY(1, infinity(), neg_one_half())
    VERIFY(1, infinity(), neg_one_third())
    VERIFY(1, infinity(), zero())
    VERIFY(1, infinity(), one_third())
    VERIFY(1, infinity(), one_half())
    VERIFY(1, infinity(), one())
    VERIFY(1, infinity(), two())
    VERIFY(1, infinity(), three())
    VERIFY(0, infinity(), infinity())
}

}  // namespace clarith
}  // namespace deepnum

