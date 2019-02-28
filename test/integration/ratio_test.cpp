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

#include <cassert>

#include "number.hpp"
#include "strategy/ratio.hpp"
#include "util.hpp"

#include <CppUTest/TestHarness.h>

#include "tracelog.h"

using deepnum::clarith::strategy::Ratio;

namespace deepnum
{
namespace clarith
{

TEST_GROUP(RatioTest)
{
};

int reference_compare(int n1, int d1, int n2, int d2)
{
    assert(n1 || d1);
    assert(n2 || d2);
    if (!d1) { n1 /= std::abs(n1); }
    if (!d2) { n2 /= std::abs(n2); }
    if (d1 < 0) { n1 *= -1; d1 *= -1; }
    if (d2 < 0) { n2 *= -1; d2 *= -1; }
    int c = d1 || d2 ? n1 * d2 - n2 * d1 : n1 - n2;
    traceloc("(" << n1 << "," << d1 << ") is " << (c > 0 ? "greater than" : (c < 0 ? "lesser than" : "equal to")) << " (" << n2 << "," << d2 << ")");
    return (c > 0) - (c < 0);
}

#define RANGE 5

TEST(RatioTest, ComparisonMatch)
{
    for (int n1 = -RANGE; n1 <= RANGE; ++n1)
    for (int d1 = -RANGE; d1 <= RANGE; !n1 && d1 == -1 ? d1 += 2 : ++d1)
    for (int n2 = -RANGE; n2 <= RANGE; ++n2)
    for (int d2 = -RANGE; d2 <= RANGE; !n2 && d2 == -1 ? d2 += 2 : ++d2)
    {
        LONGS_EQUAL(
                reference_compare(n1, d1, n2, d2),
                Util::Compare(
                        new Number(new Ratio(n1, d1)),
                        new Number(new Ratio(n2, d2))
                )
        );
    }
}

}  // namespace clarith
}  // namespace deepnum

