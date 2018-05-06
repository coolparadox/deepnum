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

/**
 * Protocol tells what are the messages of the number reducing protocol.
 * The set of reducing messages is taken from Bill Gosper's continued log idea
 * (see README).
 *
 * Before any message is known, a number is deemed to be completely unknown
 * (i.e., it lies somewhere between negative infinity and positive infinity).
 *
 * The message sequence of any given number is supposed to form a coherent list
 * where each message subdivide the previously known range of the number, and
 * causes a change of this range as a side effect. Moreover, the math must
 * converge in gradually decreasing the "information pool" of the number until
 * there is no information left to be extracted.
 *
 * The above constraints can be boiled down to the following protocol
 * invariants:
 * 1. '$' is final.
 * 2. Any message other than '$' is not final.
 * 3. '-' may optionally happen only once as the first message.
 * 4. '0' may optionally happen only once before any occurrence of other
 *    messages besides '-'.
 * 5. '$' cannot follow '2'.
 *
 * Samples:
 * 0: 0$
 * 0.5: 021$
 * -3.14: -2111211122111121$
 */
enum class Protocol {

    /**
     * ('$') I am positive infinity.
     */
    kEnd,

    /**
     * ('2') I was at least two; I halved myself.
     */
    kTwo,

    /**
     * ('1') I was at least one and lesser than two; I subtracted one from
     * myself and then reciprocated myself.
     */
    kOne,

    /**
     * ('0') I was at least zero and lesser than one; I reciprocated myself.
     */
    kZero,

    /**
     * ('-') I was lesser than zero; I negated myself.
     */
    kNeg,
};

}  // namespace reducer
}  // namespace number
}  // namespace coolparadox

#endif  // SRC_PROTOCOL_HPP_
