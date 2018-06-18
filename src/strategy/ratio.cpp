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

#include "ratio.hpp"

#include "exhaustion_error.hpp"
#include "infinity.hpp"
#include "math.hpp"
#include "protocol/protocol.hpp"
#include "unavailable_error.hpp"
#include "undefined_ratio_error.hpp"

using deepnum::clarith::protocol::Protocol;

namespace deepnum {
namespace clarith {
namespace strategy {

Ratio::Ratio(int num, int den) {
    if (num == 0 && den == 0)
        throw UndefinedRatioError();
    positive_ = (num >= 0 && den >= 0) || (num < 0 && den < 0);
    num_ = Math::Absolute(num);
    den_ = Math::Absolute(den);
}

Protocol Ratio::Reduce() {
    if (!positive_) {
        positive_ = true;
        return Protocol::kNeg;
    }
    if (den_ == 0)
        throw ExhaustionError();
    if (num_ / 2 >= den_) {
        if (num_ % 2)
            den_ *= 2;
        else
            num_ /= 2;
        return Protocol::kTwo;
    }
    if (num_ >= den_) {
        num_ -= den_;
        std::swap(num_, den_);
        return Protocol::kOne;
    }
    std::swap(num_, den_);
    return Protocol::kZero;
}

std::unique_ptr<Strategy> Ratio::GetNewStrategy() const {
    if (den_ != 0)
        throw UnavailableError();
    return std::make_unique<Infinity>();
}

}  // namespace strategy
}  // namespace clarith
}  // namespace deepnum
