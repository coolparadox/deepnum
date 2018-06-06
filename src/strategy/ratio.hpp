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

#ifndef SRC_STRATEGY_RATIO_HPP_
#define SRC_STRATEGY_RATIO_HPP_

#include "strategy.hpp"

namespace coolparadox {
namespace number {
namespace reducer {

namespace protocol {
enum class Protocol;
}  // namespace protocol

namespace strategy {

/**
 * Integer ratio.
 * This strategy can reduce ratios of integer numbers.
 * \see Strategy
 */
class Ratio : public Strategy {
 public:
    /**
     * Ratio strategy constructor.
     * Construct a strategy for reducing a ratio of integer numbers.
     * \param[in] n Numerator.
     * \param[in] d Denominator.
     */
    Ratio(int n, int d);

    protocol::Protocol Reduce() override;
    std::unique_ptr<Strategy> GetNewStrategy() const override;
};

}  // namespace strategy
}  // namespace reducer
}  // namespace number
}  // namespace coolparadox

#endif  // SRC_STRATEGY_RATIO_HPP_
