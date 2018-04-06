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
 * Number reducing atoms.
 * Adapted from Bill Gosper's continued log idea (see README).
 *
 * Before any atom is known, a number is deemed to be completely unknown
 * (i.e., ranges from negative infinity to positive infinity). The atom sequence
 * of any given number is supposed to form a coherent list where the new value
 * or range of an atom is within the resulting range left by applying the
 * modifications of the previous atom. For instance, a PosTwo may follow a
 * PosZero, but the reverse is invalid.
 *
 * The above constraint can be boiled down to the following protocol invariants:
 * 1. An Inf-type atom is final, and all other types are not final.
 * 2. A Neg-type atom may optionally happen only once as the first atom.
 * 3. A Zero-type atom may optionally happen only once before any occurrence of
 *    other Pos-type atoms.
 * 4. PosInf cannot follow Two-type atoms.
 *
 * Examples:
 * 0 = PosZero, PosInf.
 * 0.5 = PosZero, PosTwo, PosOne, PosInf.
 * -3.14 = NegTwo, PosOne, PosOne, PosOne, PosTwo, PosOne, PosOne, PosOne,
 *         PosTwo, PosTwo, PosOne, PosOne, PosOne, PosOne, PosTwo, PosOne,
 *         PosInf.
 */
enum class Protocol {

    /*
     * I am positive infinity.
     */
    kPosInf,

    /*
     * I was at least two; I halved myself.
     */
    kPosTwo,

    /*
     * I was at least one and lesser than two; I subtracted one from myself and
     * then reciprocated myself.
     */
    kPosOne,

    /*
     * I was at least zero and lesser than one; I reciprocated myself.
     */
    kPosZero,

    /* I was greater than minus one and lesser than zero; I negated myself and
     * then reciprocated myself.
     */
    kNegZero,

    /*
     * I was greater than minus two and not greater than minus one; I negated
     * myself, subtracted one from myself and reciprocated myself.
     */
    kNegOne,

    /*
     * I was not greater than minus two; I negated myself and then halved
     * myself.
     */
    kNegTwo,

    /*
     * I am negative infinity.
     */
    kNegInf,
}

}  // namespace reducer
}  // namespace number
}  // namespace coolparadox

#endif  // SRC_PROTOCOL_HPP_
