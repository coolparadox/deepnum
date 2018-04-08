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
 * Protocol tells what are the atoms of the number reducing protocol.
 * The set of reducing atoms is an adaptation from Bill Gosper's continued log
 * idea (see README).
 *
 * Before any atom is known, a number is deemed to be completely unknown
 * (i.e., it lies somewhere between negative infinity and positive infinity).
 *
 * The atom sequence of any given number is supposed to form a coherent list
 * where each atom subdivide the previously known range of the number, and
 * causes a change of this range as a side effect. Moreover, the math must
 * converge in reducing the information of the number more and more until there
 * is no information left to be extracted.
 *
 * The above constraints can be boiled down to the following protocol
 * invariants:
 * 1. An Inf-type atom is final.
 * 2. A not Inf-type atom is not final.
 * 3. A Neg-type atom may happen zero or one time as the first atom.
 * 4. A Zero-type atom may happen zero or one time before any occurrence of
 *    other Pos-type atoms.
 * 5. An Inf-type atom cannot follow a Two-type atom.
 *
 * Samples:
 * 0 = PosZero, PosInf.
 * 0.5 = PosZero, PosTwo, PosOne, PosInf.
 * -3.14 = NegTwo, PosOne, PosOne, PosOne, PosTwo, PosOne, PosOne, PosOne,
 *         PosTwo, PosTwo, PosOne, PosOne, PosOne, PosOne, PosTwo, PosOne,
 *         PosInf.
 */
enum class Protocol {

    /**
     * I am positive infinity.
     */
    kPosInf,

    /**
     * I was at least two; I halved myself.
     */
    kPosTwo,

    /**
     * I was at least one and lesser than two; I subtracted one from myself and
     * then reciprocated myself.
     */
    kPosOne,

    /**
     * I was at least zero and lesser than one; I reciprocated myself.
     */
    kPosZero,

    /**
     * I was greater than minus one and lesser than zero; I negated myself and
     * then reciprocated myself.
     */
    kNegZero,

    /**
     * I was greater than minus two and not greater than minus one; I negated
     * myself, subtracted one from myself and reciprocated myself.
     */
    kNegOne,

    /**
     * I was not greater than minus two; I negated myself and then halved
     * myself.
     */
    kNegTwo,

    /**
     * I am negative infinity.
     */
    kNegInf,
};

}  // namespace reducer
}  // namespace number
}  // namespace coolparadox

#endif  // SRC_PROTOCOL_HPP_
