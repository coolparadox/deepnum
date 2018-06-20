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

#ifndef SRC_NUMBER_HPP_
#define SRC_NUMBER_HPP_

#include <memory>

namespace deepnum {
namespace clarith {

namespace protocol {
enum class Protocol;
}  // namespace protocol

namespace strategy {
class Strategy;
}  // namespace strategy

/**
 * Rational number in continued logarithm representation.
 */
class Number {
 public:
    /**
     * A Number is defined by means of a strategy (that may combine other
     * numbers).
     * \param[in] strategy Defining strategy.
     */
    explicit Number(std::unique_ptr<strategy::Strategy> strategy);

    /**
     * Extract Number information.
     * Takes out the next piece of information from the Number instance, which
     * looses this information as a side effect.
     * \return Next continued logarithm protocol message.
     */
    protocol::Protocol Egest();

 private:
    std::unique_ptr<strategy::Strategy> strategy_;
};

}  // namespace clarith
}  // namespace deepnum

#endif  // SRC_NUMBER_HPP_
