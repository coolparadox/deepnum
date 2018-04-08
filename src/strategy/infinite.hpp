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

#ifndef SRC_STRATEGY_INFINITE_HPP_
#define SRC_STRATEGY_INFINITE_HPP_

#include "strategy/strategy.hpp"

namespace coolparadox {
namespace number {
namespace reducer {
namespace strategy {

/**
 * Infinite is a strategy that repeatedly tells the same Inf-type atom.
 * \see Protocol
 */
class Infinite : public Strategy {
 public:
    /**
     * \param positive If true, PosInf is returned from reducing; otherwise
     *                 NegInf is returned.
     */
    explicit Infinite(bool positive);

    bool Reduce(Protocol* atom) override;
    std::unique_ptr<Strategy> GetNewStrategy() override;

 private:
    bool positive_ = true;
};

}  // namespace strategy
}  // namespace reducer
}  // namespace number
}  // namespace coolparadox

#endif  // SRC_STRATEGY_INFINITE_HPP_
