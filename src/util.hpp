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

#ifndef SRC_UTIL_HPP_
#define SRC_UTIL_HPP_

#include <gsl/gsl>

namespace deepnum
{
namespace clarith
{

class Number;

/**
 * Useful functions.
 */
class Util
{
 public:

    /**
     * Compare two numbers.
     *
     * \param[in] n1 First number.
     * \param[in] n2 Second number.
     * \param[in] pedantic Distinguish between negative and positive zero.
     * \pre n1 not null.
     * \pre n2 not null.
     * \return -1 if n1 is lesser than n2,
     *         +1 if n1 is greater than n2,
     *         0 otherwise.
     */
    static int Compare(gsl::owner<Number*> n1,
                       gsl::owner<Number*> n2,
                       bool pedantic = false);

 private:
    Util();
};

}  // namespace clarith
}  // namespace deepnum

#endif  // SRC_UTIL_HPP_
