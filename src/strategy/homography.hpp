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
 * This strategy accepts a Number \f$x\f$ as input and outputs
 * \f$y=\frac{n_1 x + n_0}{d_1 x + d_0}\f$ where
 * \f$n_1\f$, \f$n_0\f$, \f$d_1\f$ and \f$d_0\f$ are machine native signed integers.
 * \see Strategy
 */
class Homography : public Strategy
{
 public:

    Homography(const Homography&) = delete;
    Homography& operator=(const Homography&) = delete;
    Homography(Homography&&) = delete;
    Homography& operator=(Homography&&) = delete;

    ~Homography();

    /**
     * \param x Input.
     * \param n1 First order numerator coefficient.
     * \param n0 Independent numerator coefficient.
     * \param d1 First order denominator coefficient.
     * \param d0 Independent denominator coefficient.
     * \pre x not null.
     * \see strategy::Homography
     * \throws UndefinedRatioError
     */
    Homography(gsl::owner<Number*> x, int n1, int n0, int d1, int d0);

    protocol::Protocol Egest() override;
    gsl::owner<Strategy*> GetNewStrategy() const override;

 private:

    static protocol::Protocol CanEgest(int min_n, int min_d, int max_n, int max_d);
    static bool IsBetweenZeroAndOne(int n, int d);
    static void MinMax(int* min_n, int* min_d, int* max_n, int* max_d, int n, int d);
    protocol::Protocol Egest(protocol::Protocol output);
    static int Compare(int n1, int d1, int n2, int d2);
    void Ingest();

    Number* _x;
    int _n1, _n0, _d1, _d0;
    bool _primed;
    bool _exhausted;
    bool _has_pole;
};

}  // namespace strategy
}  // namespace clarith
}  // namespace deepnum

#endif  // SRC_STRATEGY_HOMOGRAPHY_HPP_
