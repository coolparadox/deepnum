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

#include "exhaustion_error.hpp"
#include "zero.hpp"
#include "protocol/protocol.hpp"
#include "unavailable_error.hpp"
#include "undefined_ratio_error.hpp"

#include "ratio.hpp"

#include "tracelog.h"

using deepnum::clarith::protocol::Protocol;

namespace deepnum
{
namespace clarith
{
namespace strategy
{

Ratio::~Ratio()
{
    tracelog("");
}

Ratio::Ratio(int num, int den)
        : Ratio(num >= 0 ? num : -num, den >= 0 ? den : -den,
                (num >= 0 && den >= 0) || (num < 0 && den < 0))
{
    tracelog(num << " " << den);
}

Ratio::Ratio(unsigned int num, unsigned int den, bool positive)
        : num_(num),
          den_(den),
          positive_(positive)
{
    tracelog(num << " " << den << " " << positive);
    if (num_ == 0 && den_ == 0)
    {
        throw UndefinedRatioError();
    }
}

Protocol Ratio::Egest()
{
    tracelog(num_ << " " << den_ << " " << positive_);
    if (num_ == 0)
    {
        throw ExhaustionError();
    }
    if (!positive_)
    {
        positive_ = true;
        if (num_ > den_)
        {
            std::swap(num_, den_);
            return Protocol::Ground;
        }
        else
        {
            return Protocol::Reflect;
        }
    }
    if (num_ > den_)
    {
        std::swap(num_, den_);
        return Protocol::Turn;
    }
    if (num_ > den_ / 2)
    {
        std::swap(num_, den_);
        num_ -= den_;
        return Protocol::Uncover;
    }
    if (den_ % 2 == 0)
    {
        den_ /= 2;
    }
    else
    {
        num_ *= 2;
    }
    return Protocol::Amplify;
}

gsl::owner<Strategy*> Ratio::GetNewStrategy() const
{
    if (num_ != 0)
    {
        throw UnavailableError();
    }
    return new Zero();
}

}  // namespace strategy
}  // namespace clarith
}  // namespace deepnum
