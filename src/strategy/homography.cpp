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

#include "homography.hpp"

#include "protocol/protocol.hpp"
#include "strategy/unavailable_error.hpp"

using deepnum::clarith::protocol::Protocol;

namespace deepnum
{

namespace clarith
{

namespace strategy
{

Homography::Homography(gsl::owner<Number*> x, int n1, int n0, int d1, int d0)
{
    // FIXME: implement me
}

protocol::Protocol Homography::Egest()
{
    // FIXME: implement me
    return Protocol::kEnd;
}

gsl::owner<Strategy*> Homography::GetNewStrategy() const
{
    // FIXME: implement me
    throw UnavailableError();
}

}  // namespace strategy
}  // namespace clarith
}  // namespace deepnum

