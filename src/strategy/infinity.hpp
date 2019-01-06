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

#ifndef SRC_STRATEGY_INFINITY_HPP_
#define SRC_STRATEGY_INFINITY_HPP_

#include "strategy.hpp"

namespace deepnum
{
namespace clarith
{

namespace protocol
{
enum class Protocol;
}  // namespace protocol

namespace strategy
{

/**
 * Positive infinity.
 * This strategy simply represents positive infinity.
 * \see Strategy
 */
class Infinity : public Strategy
{
 public:
    protocol::Protocol Egest() override;
    std::unique_ptr<Strategy> GetNewStrategy() const override;
};

}  // namespace strategy
}  // namespace clarith
}  // namespace deepnum

#endif  // SRC_STRATEGY_INFINITY_HPP_
