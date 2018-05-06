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

#ifndef SRC_STRATEGY_STRATEGY_HPP_
#define SRC_STRATEGY_STRATEGY_HPP_

#include <memory>

namespace coolparadox {
namespace number {
namespace reducer {
enum class Protocol;

namespace strategy {

/**
 * Strategy is an approach for reducing numbers to Protocol message sequences.
 * \see Protocol
 */
class Strategy {
 public:
    /**
     * Reduce takes out the next Procol message from the underlying number,
     * which loses this information as a side effect.
     * \return If extraction was successful. On false, caller must ignore the
     *         returned message and acquire another strategy through
     *         GetNewStrategy. The new acquired strategy can then be used to
     *         resume the reduction.
     * \return Extracted message (valid only on successful extraction).
     * \see GetNewStrategy
     */
    virtual std::tuple<bool, Protocol> Reduce() = 0;

    /**
     * GetNewStrategy offers another strategy that knows how to resume reduction
     * when this strategy ceases working.
     * This method should be called after Reduce fails.
     * \see Reduce
     */
    virtual std::unique_ptr<Strategy> GetNewStrategy() = 0;
};

}  // namespace strategy
}  // namespace reducer
}  // namespace number
}  // namespace coolparadox

#endif  // SRC_STRATEGY_STRATEGY_HPP_
