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
 * Strategy is an approach for reducing numbers to atoms.
 * \see Protocol
 */
class Strategy {
 public:
    /**
     * Reduce extracts an atom.
     * \param atom Placeholder for the extracted atom.
     * \return If extraction was successful. On false, client must acquire
     *         another strategy through GetNewStrategy and use the new acquired
     *         strategy for resuming the reduction.
     * \see GetNewStrategy
     * TODO(coolparadox): check how ISO C++ suggests declaring an output parameter.
     */
    virtual bool Reduce(Protocol* atom) = 0;

    /**
     * GetNewStrategy offers a strategy that knows how to resume reduction when
     * this strategy halts in doing so.
     * \see Reduce
     */
    virtual std::unique_ptr<Strategy> GetNewStrategy() = 0;
};

}  // namespace strategy
}  // namespace reducer
}  // namespace number
}  // namespace coolparadox

#endif  // SRC_STRATEGY_STRATEGY_HPP_
