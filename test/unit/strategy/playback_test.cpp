/*
 * Copyright 2019 Rafael Lorandi <coolparadox@gmail.com>
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

#include <memory>
#include <forward_list>
#include <CppUTest/TestHarness.h>

#include "protocol/protocol.hpp"
#include "strategy/infinity.hpp"
#include "strategy/playback.hpp"
#include "strategy/exhaustion_error.hpp"
#include "strategy/unavailable_error.hpp"

using deepnum::clarith::protocol::Protocol;

namespace deepnum
{
namespace clarith
{
namespace strategy
{

TEST_GROUP(PlaybackTest)
{
};

TEST(PlaybackTest, DegeneratesToInfinity)
{
    Playback strategy(std::unique_ptr<std::forward_list<Protocol>>(new std::forward_list<Protocol> {}));
    CHECK_THROWS(ExhaustionError, strategy.Egest());
    CHECK_TRUE(dynamic_cast<Infinity*>(strategy.GetNewStrategy().get()));
}

TEST(PlaybackTest, DoesNotOfferPrematureStrategy)
{
    CHECK_THROWS(UnavailableError, Playback(std::unique_ptr<std::forward_list<Protocol>>(new std::forward_list<Protocol> { Protocol::kZero, })).GetNewStrategy());
}

TEST(PlaybackTest, ReplaysTwo)
{
    LONGS_EQUAL(Protocol::kTwo, Playback(std::unique_ptr<std::forward_list<Protocol>>(new std::forward_list<Protocol> { Protocol::kTwo, })).Egest());
}

TEST(PlaybackTest, ReplaysOne)
{
    LONGS_EQUAL(Protocol::kOne, Playback(std::unique_ptr<std::forward_list<Protocol>>(new std::forward_list<Protocol> { Protocol::kOne, })).Egest());
}

TEST(PlaybackTest, ReplaysZero)
{
    LONGS_EQUAL(Protocol::kZero, Playback(std::unique_ptr<std::forward_list<Protocol>>(new std::forward_list<Protocol> { Protocol::kZero, })).Egest());
}

TEST(PlaybackTest, ReplaysNegative)
{
    LONGS_EQUAL(Protocol::kNeg, Playback(std::unique_ptr<std::forward_list<Protocol>>(new std::forward_list<Protocol> { Protocol::kNeg, })).Egest());
}

TEST(PlaybackTest, ReachesEnd)
{
    Playback strategy(std::unique_ptr<std::forward_list<Protocol>>(new std::forward_list<Protocol> { Protocol::kZero, }));
    LONGS_EQUAL(Protocol::kZero, strategy.Egest());
    CHECK_THROWS(ExhaustionError, strategy.Egest());
}

}  // namespace strategy
}  // namespace clarith
}  // namespace deepnum

