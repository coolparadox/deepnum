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

#ifndef SRC_REDUCER_HPP_
#define SRC_REDUCER_HPP_

#include <memory>

namespace coolparadox {
namespace number {
namespace reducer {

namespace protocol {
enum class Protocol;
}  // namespace protocol

namespace strategy {
class Strategy;
}  // namespace strategy

/**
 * Plays a reducing strategy.
 * Strategies eventually get exhausted and provide another strategy for
 * resuming the reduction process. Reducer automates strategy switching,
 * providing a more straightforward interface for number reduction.
 * \see strategy::Strategy
 */
class Reducer {
 public:
    /**
     * Constructs a strategy player.
     * \param[in] strategy The strategy to be played.
     */
    explicit Reducer(std::unique_ptr<strategy::Strategy> strategy);

    /**
     * Retrieves next Protocol message from underlying strategy.
     * \return Extracted Protocol message.
     * \see Protocol
     */
    protocol::Protocol Reduce();

 private:
    std::unique_ptr<strategy::Strategy> strategy_;
};

}  // namespace reducer
}  // namespace number
}  // namespace coolparadox

#endif  // SRC_REDUCER_HPP_
