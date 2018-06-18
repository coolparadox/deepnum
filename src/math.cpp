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

#include "math.hpp"

#include <cstdlib>
#include <limits>

namespace deepnum {
namespace clarith {

unsigned int Math::Absolute(int value) {
    static constexpr int lowest_int { std::numeric_limits<int>::lowest() };
    if (value == lowest_int)
        return static_cast<unsigned int>(abs(lowest_int + 1)) + 1;
    return abs(value);
}

}  // namespace clarith
}  // namespace deepnum
