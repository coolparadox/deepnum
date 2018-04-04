/*
 * Copyright 2018 Rafael Lorandi <coolparadox@gmail.com>
 *
 * This file is part of coolparadox-number-reducer, a library for handling
 * rational numbers in continued log format.
 * 
 * coolparadox-number-reducer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * coolparadox-number-reducer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with coolparadox-number-reducer.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef SRC_PROTOCOL_HPP_
#define SRC_PROTOCOL_HPP_

namespace coolparadox {
namespace number {
namespace reducer {

/*
 * Based from Gosper (...)
 */
enum class Protocol {

    /**
     * I was a non positive number.
     * I negativated myself; so now I am at least zero.
     */
    kNegativated,

    /*
     * I was at least zero and lesser than one.
     * I reciprocated myself; so now I am at least one.
     */
    kReciprocated,

    /*
     * I was at least one and lesser than two.
     * I subtracted one from myself; so now I am at least zero and lesser than
     * one.
     */
    kSubtracted,

    /*
     * I was at least two.
     * I halved myself; so now I am at least one.
     */
    kHalved,

    /*
     * I am positive infinity.
     * There is no more information to extract from me.
     */
    kInfinite,
}

}  // namespace reducer
}  // namespace number
}  // namespace coolparadox

#endif  // SRC_PROTOCOL_HPP_
