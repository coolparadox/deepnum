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

#ifndef SRC_STRATEGY_RATIO_HPP_
#define SRC_STRATEGY_RATIO_HPP_

#include "strategy.hpp"

namespace deepnum {
namespace clarith {

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
     * \param[in] num Numerator.
     * \param[in] den Denominator.
     * \pre At least one parameter must not be zero.
     * \throw UndefinedRatioError
     */
    Ratio(int num, int den);

    protocol::Protocol Egest() override;
    std::unique_ptr<Strategy> GetNewStrategy() const override;

 private:
    unsigned int num_;
    unsigned int den_;
    bool positive_;
};

}  // namespace strategy
}  // namespace clarith
}  // namespace deepnum

#endif  // SRC_STRATEGY_RATIO_HPP_
