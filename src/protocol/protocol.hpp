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

namespace deepnum
{
namespace clarith
{
namespace protocol
{

/**
 * Continued logarithm messages.
 * The set of messages is taken from Bill Gosper's continued log idea.
 *
 * Before any message is known, a number is deemed to be completely unknown
 * (i.e., it lies somewhere between negative infinity and positive infinity).
 *
 * Messages produced by reducing any given number are supposed to form a
 * coherent sequence where each message uncovers a new level of knowledge about
 * where the number lies in its formerly known range,
 * and then causes a change of this range as a side effect
 * of simple arithmetic transformations in the number.
 * Moreover, the math must converge in gradually decreasing the
 * "information pool" of the number
 * until there is no information left to be extracted.
 *
 * The above constraints can be boiled down
 * to the following protocol invariants:
 *   -# '$' is final.
 *   -# Any message other than '$' is not final.
 *   -# '-' may optionally happen only once as the first message.
 *   -# '0' may optionally happen only once before any occurrence of other
 *      messages besides '-'.
 *   -# '$' cannot follow '2'.
 *
 * Samples of reducing some numbers using this protocol:
 *   - _0_ = '0$'
 *   - _0.5_ = '021$'
 *   - _-3.14_ = '-2111211122111121$'
 */
enum class Protocol
{

    /**
     * '$'.
     * Number is positive infinity.
     */
    kEnd,

    /**
     * '2'.
     * Number was at least two and was halved.
     */
    kTwo,

    /**
     * '1'.
     * Number was at least one but lesser than two,
     * had one subtracted from itself and then was reciprocated.
     */
    kOne,

    /**
     * '0'.
     * Number was at least zero but lesser than one,
     * and was reciprocated.
     */
    kZero,

    /**
     * '-'.
     * Number was lesser than zero and was negated.
     */
    kNeg,
};

}  // namespace protocol
}  // namespace clarith
}  // namespace deepnum

#endif  // SRC_PROTOCOL_PROTOCOL_HPP_
