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

#include <forward_list>

#include "protocol/protocol.hpp"
#include "protocol/violation_error.hpp"
#include "strategy/zero.hpp"
#include "strategy/playback.hpp"
#include "strategy/exhaustion_error.hpp"
#include "strategy/unavailable_error.hpp"

#include <CppUTest/TestHarness.h>

using deepnum::clarith::protocol::Protocol;
using deepnum::clarith::protocol::ViolationError;

namespace deepnum
{
namespace clarith
{
namespace strategy
{

TEST_GROUP(PlaybackTest)
{
};

TEST(PlaybackTest, ReachesZero)
{
    Playback s1(gsl::owner<std::forward_list<Protocol>*>(new std::forward_list<Protocol> {}));
    CHECK_THROWS(ExhaustionError, s1.Egest());
    Strategy* s2 = s1.GetNewStrategy();
    CHECK_TRUE(dynamic_cast<Zero*>(s2));
    delete s2;
}

TEST(PlaybackTest, DoesNotOfferPrematureStrategy)
{
    CHECK_THROWS(UnavailableError, Playback(gsl::owner<std::forward_list<Protocol>*>(new std::forward_list<Protocol> { Protocol::Uncover })).GetNewStrategy());
}

TEST(PlaybackTest, ReplaysEnd)
{
    LONGS_EQUAL(Protocol::End, Playback(gsl::owner<std::forward_list<Protocol>*>(new std::forward_list<Protocol> { Protocol::End })).Egest());
}

TEST(PlaybackTest, ReplaysAmplify)
{
    LONGS_EQUAL(Protocol::Amplify, Playback(gsl::owner<std::forward_list<Protocol>*>(new std::forward_list<Protocol> { Protocol::Amplify })).Egest());
}

TEST(PlaybackTest, ReplaysUncover)
{
    LONGS_EQUAL(Protocol::Uncover, Playback(gsl::owner<std::forward_list<Protocol>*>(new std::forward_list<Protocol> { Protocol::Uncover })).Egest());
}

TEST(PlaybackTest, ReplaysTurn)
{
    LONGS_EQUAL(Protocol::Turn, Playback(gsl::owner<std::forward_list<Protocol>*>(new std::forward_list<Protocol> { Protocol::Turn })).Egest());
}

TEST(PlaybackTest, ReplaysReflect)
{
    LONGS_EQUAL(Protocol::Reflect, Playback(gsl::owner<std::forward_list<Protocol>*>(new std::forward_list<Protocol> { Protocol::Reflect })).Egest());
}

TEST(PlaybackTest, ReplaysGround)
{
    LONGS_EQUAL(Protocol::Ground, Playback(gsl::owner<std::forward_list<Protocol>*>(new std::forward_list<Protocol> { Protocol::Ground })).Egest());
}

TEST(PlaybackTest, ThrowsOnNonFinalEnd)
{
    {
        Playback strategy(gsl::owner<std::forward_list<Protocol>*>(new std::forward_list<Protocol> { Protocol::End, Protocol::Uncover }));
        LONGS_EQUAL(Protocol::End, strategy.Egest());
        CHECK_THROWS(ViolationError, strategy.Egest());
    }
}

TEST(PlaybackTest, ThrowsOnFinalAmplify)
{
    {
        Playback strategy(gsl::owner<std::forward_list<Protocol>*>(new std::forward_list<Protocol> { Protocol::Amplify }));
        LONGS_EQUAL(Protocol::Amplify, strategy.Egest());
        CHECK_THROWS(ViolationError, strategy.Egest());
    }
}

TEST(PlaybackTest, ThrowsOnNonInitialTurn)
{
    {
        Playback strategy(gsl::owner<std::forward_list<Protocol>*>(new std::forward_list<Protocol> { Protocol::Uncover, Protocol::Turn }));
        LONGS_EQUAL(Protocol::Uncover, strategy.Egest());
        CHECK_THROWS(ViolationError, strategy.Egest());
    }
}

TEST(PlaybackTest, ThrowsOnNonInitialReflect)
{
    {
        Playback strategy(gsl::owner<std::forward_list<Protocol>*>(new std::forward_list<Protocol> { Protocol::Uncover, Protocol::Reflect }));
        LONGS_EQUAL(Protocol::Uncover, strategy.Egest());
        CHECK_THROWS(ViolationError, strategy.Egest());
    }
}

TEST(PlaybackTest, ThrowsOnNonInitialGround)
{
    {
        Playback strategy(gsl::owner<std::forward_list<Protocol>*>(new std::forward_list<Protocol> { Protocol::Uncover, Protocol::Ground }));
        LONGS_EQUAL(Protocol::Uncover, strategy.Egest());
        CHECK_THROWS(ViolationError, strategy.Egest());
    }
}

}  // namespace strategy
}  // namespace clarith
}  // namespace deepnum

