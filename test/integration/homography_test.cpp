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

#include "number.hpp"
#include "strategy/homography.hpp"
#include "strategy/ratio.hpp"
#include "util.hpp"

#include <CppUTest/TestHarness.h>

#include "tracelog.h"

using deepnum::clarith::strategy::Homography;
using deepnum::clarith::strategy::Ratio;

namespace deepnum
{
namespace clarith
{

TEST_GROUP(HomographyTest)
{
};

bool result_ratio(int* nr, int* dr, int n1, int n0, int d1, int d0, int nx, int dx)
{
    traceloc(n1 << " " << n0 << " " << d1 << " " << d0 << " for " << nx << " " << dx << " ...");
    bool answer = false;
    if (!n1 && !d1)
    {
        // input is dropped
        *nr = n0;
        *dr = d0;
        goto result_ratio_check;
    }
    // if (!n1 && !n0 && !d1 && !d0)
    // {
        // goto result_ratio_undefined;
    // }
    if (!nx && !dx)
    {
        // input is undefined
        goto result_ratio_undefined;
    }
    if (!nx)
    {
        // input is zero
        if (!d0)
        {
            // pole at input
            goto result_ratio_undefined;
        }
        *nr = n0;
        *dr = d0;
        goto result_ratio_check;
    }
    if (!dx)
    {
        // input is +- infinity
        *nr = n1;
        *dr = d1;
        if (!*dr)
        {
            // there is no pole
            // sign correct output
            *nr *= d0 < 0 ? -1 : 1;
            *nr *= nx < 0 ? -1 : 1;
        }
        goto result_ratio_check;
    }
    if (dx < 0)
    {
        // sign normalize input
        nx *= -1;
        dx *= -1;
    }
    if (d1*nx+d0*dx == 0)
    {
        // there is a pole at input
        goto result_ratio_undefined;
    }
    /*
     * (n1(nx/dx)+n0)/(d1*(nx/dx)+d0)
     * = (n1nx+n0dx)/(d1nx+d0dx)
     */
    *nr = n1*nx+n0*dx;
    *dr = d1*nx+d0*dx;
result_ratio_check:
    if (!*nr && !*dr)
    {
        goto result_ratio_undefined;
    }
result_ratio_defined:
    answer = true;
result_ratio_undefined:
#if TRACE
    if (answer)
    {
        traceloc("... is " << *nr << " " << *dr);
    }
    else
    {
        traceloc(" is undefined");
    }
#endif  // TRACE
    return answer;
}

#define RANGE 3

TEST(HomographyTest, ComparisonMatch)
{
    for (int n1 = -RANGE; n1 <= RANGE; ++n1)
    for (int d1 = -RANGE; d1 <= RANGE; ++d1)
    for (int n0 = -RANGE; n0 <= RANGE; ++n0)
    for (int d0 = -RANGE; d0 <= RANGE; ++d0)
    for (int nx = -RANGE; nx <= RANGE; ++nx)
    for (int dx = -RANGE; dx <= RANGE; ++dx)
    {
        int nr, dr;
        if (!nx && !dx) { continue; }
        bool ok = result_ratio(&nr, &dr, n1, n0, d1, d0, nx, dx);
        if (!ok) { continue; }
        LONGS_EQUAL(0, Util::Compare(
                new Number(new Homography(new Number(new Ratio(nx, dx)), n1, n0, d1, d0)),
                new Number(new Ratio(nr, dr))
        ));
    }
}

}  // namespace clarith
}  // namespace deepnum

