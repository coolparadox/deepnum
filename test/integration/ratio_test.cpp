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

#include <CppUTest/TestHarness.h>

#include "number.hpp"
#include "strategy/ratio.hpp"
#include "util.hpp"

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
    if (d1 < 0) { n1 *= -1; d1 *= -1; }
    if (d2 < 0) { n2 *= -1; d2 *= -1; }
    int c = n1 * d2 - n2 * d1;
    return (c > 0) - (c < 0);
}

#define RANGE 25

TEST(RatioTest, ComparisonMatch)
{
    for (int n1 = -RANGE; n1 != RANGE; ++n1)
    for (int d1 = -RANGE; d1 != RANGE; ++d1)
    for (int n2 = -RANGE; n2 != RANGE; ++n2)
    for (int d2 = -RANGE; d2 != RANGE; ++d2)
    {
        if (d1 == 0 || d2 == 0) { continue; }
        int c1 = reference_compare(n1, d1, n2, d2);
        int c2 = Util::Compare(std::make_unique<Number>(std::make_unique<Ratio>(n1, d1)), std::make_unique<Number>(std::make_unique<Ratio>(n2, d2)));
        LONGS_EQUAL(c1, c2);
    }
}

}  // namespace clarith
}  // namespace deepnum

