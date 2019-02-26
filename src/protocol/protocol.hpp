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

#ifndef SRC_PROTOCOL_PROTOCOL_HPP_
#define SRC_PROTOCOL_PROTOCOL_HPP_

#include <config.h>

#if TRACE
#include <iostream>
#endif  // TRACE

namespace deepnum
{
namespace clarith
{
namespace protocol
{

/**
 * Continued logarithm messages.
 * The set of messages is a modified version of Bill Gosper's continued log idea.
 *
 * Before a number egests any message, it is deemed to be completely unknown
 * (i.e., it lies somewhere between negative infinity and positive infinity).
 *
 * Messages produced by reducing any given number are supposed to form a
 * coherent sequence where each message uncovers a new level of knowledge about
 * where the number lies in its formerly known range,
 * and then causes a change of this range as a side effect.
 * Each egested message decreases the number's "information pool",
 * until there is no more information to be know about the number
 * (i.e, it is zero).
 *
 * The above constraints can be boiled down
 * to the following protocol invariants:
 *   -# Message '0' is final.
 *   -# Any message other than '0' is not final.
 *   -# '/', '-' or '-/' can only happen as the first message.
 *   -# '0' cannot follow '2'.
 *
 * Samples of reducing some numbers using this protocol:
 *   - _0_ = '0'
 *   - _0.5_ = '210'
 *   - _-3.14_ = '-/21112111221111210'
 *
 */
enum class Protocol
{

    /**
     * '0'.
     * Number is zero.
     */
    End,

    /**
     * '2'.
     * Number was greater than zero but no greater than one half,
     * and was doubled.
     */
    Amplify,

    /**
     * '1'.
     * Number was greater than one half but no greater than one,
     * was reciprocated
     * and then had one subtracted from itself.
     */
    Uncover,

    /**
     * '/'.
     * Number was greater than one
     * and was reciprocated.
     */
    Turn,

    /**
     * '-'.
     * Number was lesser than zero but no lesser than minus one,
     * and was negated.
     */
    Reflect,

    /**
     * '-/'.
     * Number was lesser than minus one,
     * was negated
     * and then was reciprocated.
     */
    Ground,

};

#if TRACE
std::ostream& operator<<(std::ostream& os, const Protocol& message);
#endif  // TRACE

}  // namespace protocol
}  // namespace clarith
}  // namespace deepnum

#endif  // SRC_PROTOCOL_PROTOCOL_HPP_
