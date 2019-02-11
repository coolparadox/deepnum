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

#ifndef SRC_STRATEGY_HOMOGRAPHY_HPP_
#define SRC_STRATEGY_HOMOGRAPHY_HPP_

#include "strategy.hpp"

namespace deepnum
{

namespace clarith
{

class Number;

namespace strategy
{

/**
 * First degree homographic transformation.
 * This strategy accepts a Number x as input and outputs a Number y where:
 *      n1 * x + n0
 * y = ------------- where n1, n0, d1, d0 are native signed integers.
 *      d1 * x + d0
 * \see Strategy
 */
class Homography : public Strategy
{
 public:

    ~Homography() = default;
    Homography(const Homography&) = delete;
    Homography& operator=(const Homography&) = delete;
    Homography(Homography&&) = delete;
    Homography& operator=(Homography&&) = delete;

    /**
     * \param x Input, or null for positive infinity.
     * \param n1 First order numerator coefficient.
     * \param n0 Independent numerator coefficient.
     * \param d1 First order denominator coefficient.
     * \param d0 Independent denominator coefficient.
     * \see Homograpy
     */
    Homography(gsl::owner<Number*> x, int n1, int n0, int d1, int d0);

    protocol::Protocol Egest() override;
    gsl::owner<Strategy*> GetNewStrategy() const override;

 private:
    Number* _x;
    int _n1, _n0, _d1, _d0;
};

}  // namespace strategy
}  // namespace clarith
}  // namespace deepnum

#endif  // SRC_STRATEGY_HOMOGRAPHY_HPP_
