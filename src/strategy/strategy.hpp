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

#ifndef SRC_STRATEGY_STRATEGY_HPP_
#define SRC_STRATEGY_STRATEGY_HPP_

#include <memory>

namespace deepnum {
namespace clarith {

namespace protocol {
enum class Protocol;
}  // namespace protocol

namespace strategy {

/**
 * Represents an approach for reducing numbers to Protocol message sequences.
 * \see Protocol
 */
class Strategy {
 public:
    virtual ~Strategy() = default;

    /**
     * Extracts next Protocol message.
     * Takes out the next Protocol message from the underlying number,
     * which loses this information as a side effect.
     * \return Extracted Protocol message.
     * \throw ExhaustionError
     * \see GetNewStrategy
     */
    virtual protocol::Protocol Reduce() = 0;

    /**
     * New strategy in case of exhaustion.
     * Offers another strategy that can resume the reduction process
     * in case the current strategy ceases working.
     * \return New strategy where Reduce() works.
     * \throw UnavailableError
     * \see Reduce
     */
    virtual std::unique_ptr<Strategy> GetNewStrategy() const = 0;
};

}  // namespace strategy
}  // namespace clarith
}  // namespace deepnum

#endif  // SRC_STRATEGY_STRATEGY_HPP_
