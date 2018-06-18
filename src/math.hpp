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

#ifndef SRC_MATH_HPP_
#define SRC_MATH_HPP_

namespace deepnum {
namespace clarith {

/**
 * General support math functions.
 */
class Math {
 public:
    /**
     * Absolute value of a signed integer.
     * This does the right thing even in case the input is the lowest value of
     * a two's complement representation.
     * \param[in] value Any signed integer number.
     * \return Non negative value with same magnitude as input.
     */
    static unsigned int Absolute(int value);
};

}  // namespace clarith
}  // namespace deepnum

#endif  // SRC_MATH_HPP_
