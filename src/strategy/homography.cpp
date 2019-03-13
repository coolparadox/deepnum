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

#include <cassert>
#include <cmath>
#include <stdexcept>

#include "number.hpp"
#include "protocol/protocol.hpp"
#include "strategy/zero.hpp"
#include "strategy/exhaustion_error.hpp"
#include "strategy/ratio.hpp"
#include "strategy/unavailable_error.hpp"
#include "strategy/undefined_ratio_error.hpp"
#include "util.hpp"

#include "homography.hpp"

#include "tracelog.h"

using deepnum::clarith::protocol::Protocol;

namespace deepnum
{

namespace clarith
{

namespace strategy
{

Homography::Homography(Number* x, int n1, int n0, int d1, int d0)
        : _x(x), _n1(n1), _n0(n0), _d1(d1), _d0(d0),
        _primed(false),
        _exhausted(false),
        _has_pole(d1)
{
    tracelog(x << " " << _n1 << " " << _n0 << " " << _d1 << " " << _d0);
    if (!n1 && !n0 && !d1 && !d0)
    {
        delete _x;
        throw UndefinedRatioError();
    }
    if (!_n1 && !_d1)
    {
        // input is dropped
        _exhausted = true;
        return;
    }
}

Homography::~Homography()
{
    tracelog("");
    delete _x;
}

protocol::Protocol Homography::Egest()
{
    if (_exhausted)
    {
        throw ExhaustionError();
    }
    if (!_primed)
    {
        _primed = true;
        // Input is completely unknown; make it lie between 0 and 1.
        Ingest();
    }

    Protocol output;
    do
    {

        int min_n, min_d, max_n, max_d;
        DetectOutputRange(&min_n, &min_d, &max_n, &max_d);
        tracelog("output range min " << min_n << " " << min_d << " max " << max_n << " " << max_d);
        if (min_n == max_n && min_d == max_d)
        {
            tracelog("output range is a point");
            _exhausted = true;
            throw ExhaustionError();
        }
        output = CanEgest(min_n, min_d, max_n, max_d);
        if (output == Protocol::End)
        {
            tracelog("need more input");
            Ingest();
        }

    } while (output == Protocol::End);
    return Egest(output);

}

void Homography::DetectOutputRange(int* min_n, int* min_d, int* max_n, int* max_d)
{

    if (_n0 || _d0)
    {
        *min_n = *max_n = _n0;
        *min_d = *max_d = _d0;
        tracelog("output at 0 is " << _n0 << " " << _d0);
    }
    else
    {
        tracelog("output at 0 is undefined");
        *min_n = -1;
        *max_n = 1;
        *min_d = *max_d = 0;
    }

    int n, d;
    assert(!__builtin_add_overflow(_n1, _n0, &n));
    assert(!__builtin_add_overflow(_d1, _d0, &d));
    // int n = _n1 + _n0;
    // int d = _d1 + _d0;
    if (n || d)
    {
        tracelog("output at 1 is " << n << " " << d);
        MinMax(min_n, min_d, max_n, max_d, n, d);
    }
    else
    {
        tracelog("output at 1 is undefined");
        *min_n = -1;
        *max_n = 1;
        *min_d = *max_d = 0;
    }

    if (IsBetweenZeroAndOne(-_n0, _n1)) {
        tracelog("has a zero between 0 and 1");
        MinMax(min_n, min_d, max_n, max_d, 0, 1);
    }

    if (IsBetweenZeroAndOne(-_d0, _d1))
    {
        tracelog("has a pole between 0 and 1");
        *min_n = -1;
        *min_d = 0;
        *max_n = 1;
        *max_d = 0;
    }

}

void Homography::MinMax(int* min_n, int* min_d, int* max_n, int* max_d, int n, int d)
{
    if (Compare(n, d, *min_n, *min_d) < 0)
    {
        *min_n = n;
        *min_d = d;
    }
    if (Compare(n, d, *max_n, *max_d) > 0)
    {
        *max_n = n;
        *max_d = d;
    }
}

bool Homography::IsBetweenZeroAndOne(int n, int d)
{
    if (!n && !d) {
        return false;
    }
    if (d < 0) {
        n *= -1;
        d *= -1;
    }
    return n >= 0 && n <= d;
}

Protocol Homography::CanEgest(int min_n, int min_d, int max_n, int max_d)
{
    assert(min_n || max_n);
    if (Compare(max_n, max_d, -1, 1) < 0) { return Protocol::Ground; }
    if (Compare(min_n, min_d, 1, 1) > 0) { return Protocol::Turn; }
    if (Compare(max_n, max_d, 0, 1) < 0 && Compare(min_n, min_d, -1, 1) >= 0) { return Protocol::Reflect; }
    if (Compare(min_n, min_d, 1, 2) > 0 && Compare(max_n, max_d, 1, 1) <= 0) { return Protocol::Uncover; }
    if (Compare(min_n, min_d, 0, 1) > 0 && Compare(max_n, max_d, 1, 2) <= 0) { return Protocol::Amplify; }
    return Protocol::End;
}

Protocol Homography::Egest(Protocol output)
{
    switch (output)
    {
        case Protocol::Amplify:
            /*
             * 2(n1x+n0)/(d1x+d0)
             * = ((2n1)x+(2n0))/(d1x+d0)
             * = (n1x+n0)/((d1/2)x+(d0/2))
             */
            if (_d1 % 2 || _d0 % 2)
            {
                assert(!__builtin_mul_overflow(_n1, 2, &_n1));
                assert(!__builtin_mul_overflow(_n0, 2, &_n0));
            }
            else
            {
                _d1 /= 2;
                _d0 /= 2;
            }
            break;
        case Protocol:: Uncover:
            /*
             * 1/((n1x+n0)/(d1x+d0))-1
             * = (d1x+d0)/(n1x+n0)-1
             * = (d1x+d0)/(n1x+n0)-(n1x+n0)/(n1x+n0)
             * = ((d1-n1)x+(d0-n0))/(n1x+n0)
             */
            assert(!__builtin_sub_overflow(_d1, _n1, &_d1));
            assert(!__builtin_sub_overflow(_d0, _n0, &_d0));
            std::swap(_n1, _d1);
            std::swap(_n0, _d0);
            break;
        case Protocol:: Turn:
            /*
             * 1/((n1x+n0)/(d1x+d0))
             * = (d1x+d0)/(n1x+n0)
             */
            std::swap(_n1, _d1);
            std::swap(_n0, _d0);
            break;
        case Protocol:: Reflect:
            /*
             * -((n1x+n0)/(d1x+d0))
             * = ((-n1)x+(-n0))/(d1x+d0)
             */
            assert(!__builtin_mul_overflow(_n1, -1, &_n1));
            assert(!__builtin_mul_overflow(_n0, -1, &_n0));
            break;
        case Protocol:: Ground:
            /*
             * 1/(-(n1x+n0)/(d1x+d0))
             * = -(d1x+d0)/(n1x+n0)
             * = ((-d1)x+(-d0))/(n1x+n0)
             */
            assert(!__builtin_mul_overflow(_d1, -1, &_d1));
            assert(!__builtin_mul_overflow(_d0, -1, &_d0));
            std::swap(_n1, _d1);
            std::swap(_n0, _d0);
            break;
        default:
            throw std::logic_error("unhandled protocol message");
    }
    tracelog("egesting " << output << ", new state " << _n1 << " " << _n0 << " " << _d1 << " " << _d0);
    return output;
}

Strategy* Homography::GetNewStrategy() const
{
    if (!_exhausted)
    {
        throw UnavailableError();
    }
    return new Ratio(_n0, _d0);
}

int Homography::Compare(int n1, int d1, int n2, int d2)
{
    assert(n1 || d1);
    assert(n2 || d2);
    int n1_ = n1;
    int d1_ = d1;
    int n2_ = n2;
    int d2_ = d2;
    if (!d1_)
    {
        n1_ = n1_ > 0 ? 1 : -1;
    }
    else if (d1_ < 0)
    {
        if (__builtin_mul_overflow(n1_, -1, &n1_))
        {
            goto compare_fallback;
        }
        if (__builtin_mul_overflow(d1_, -1, &d1_))
        {
            goto compare_fallback;
        }
    }
    if (!d2_)
    {
        n2_ = n2_ > 0 ? 1 : -1;
    }
    else if (d2_ < 0)
    {
        if (__builtin_mul_overflow(n2_, -1, &n2_))
        {
            goto compare_fallback;
        }
        if (__builtin_mul_overflow(d2_, -1, &d2_))
        {
            goto compare_fallback;
        }
    }
    int c;
    if (d1_ || d2_)
    {
        int t1, t2;
        if (__builtin_mul_overflow(n1_, d2_, &t1))
        {
            goto compare_fallback;
        }
        if (__builtin_mul_overflow(n2_, d1_, &t2))
        {
            goto compare_fallback;
        }
        if (__builtin_sub_overflow(t1, t2, &c))
        {
            goto compare_fallback;
        }
    }
    else
    {
        if (__builtin_sub_overflow(n1_, n2_, &c))
        {
            goto compare_fallback;
        }
    }
    return (c > 0) - (c < 0);
compare_fallback:
    traceloc("integer overflow; fallbacking to Ratio comparison");
    return Util::Compare(new Number(new Ratio(n1, d1)), new Number(new Ratio(n2, d2)));
}

void Homography::Ingest()
{
    tracelog("querying " << _x);
    Protocol input = _x->Egest();
    switch (input)
    {
        case Protocol::End:
            tracelog("end of input");
            if (!_d0)
            {
                tracelog("pole at 0");
                if (_has_pole)
                {
                    tracelog("and pole is primal");
                    throw UndefinedRatioError();
                }
                if (_d1 < 0)
                {
                    assert(!__builtin_mul_overflow(_n0, -1, &_n0));
                }
            }
            _exhausted = true;
            throw ExhaustionError();
        case Protocol::Amplify:
            /*
             * x2 = 2x1 => x1 = x2/2
             *
             * (n1x1+n0)/(d1x1+d0)
             * = (n1(x2/2)+n0)/(d1(x2/2)+d0)
             * = ((n1/2)x2+n0)/((d1/2)x2+d0)
             * = (n1x2+2n0)/(d1x2+2d0)
             */
            if (_n1 % 2 || _d1 % 2)
            {
                assert(!__builtin_mul_overflow(_n0, 2, &_n0));
                assert(!__builtin_mul_overflow(_d0, 2, &_d0));
            }
            else
            {
                _n1 /= 2;
                _d1 /= 2;
            }
            break;
        case Protocol::Uncover:
            /*
             * x2 = 1/x1-1 => 1/x1 = x2+1 => x1 = 1/(x2+1)
             *
             * (n1x1+n0)/(d1x1+d0)
             * = (n1(1/(x2+1))+n0)/(d1(1/(x2+1)+d0)
             * = (n1+n0(x2+1))/(d1+d0(x2+1))
             * = (n1+n0x2+n0)/(d1+d0x2+d0)
             * = (n0x2+(n1+n0))/(d0x2+(d1+d0))
             */
            assert(!__builtin_add_overflow(_n1, _n0, &_n1));
            assert(!__builtin_add_overflow(_d1, _d0, &_d1));
            std::swap(_n1, _n0);
            std::swap(_d1, _d0);
            break;
        case Protocol::Turn:
            /*
             * x2 = 1/x1 => x1 = 1/x2
             *
             * (n1x1+n0)/(d1x1+d0)
             * = (n1(1/x2)+n0)/(d1(1/x2)+d0)
             * = (n1+n0x2)/(d1+d0x2)
             * = (n0x2+n1)/(d0x2+d1)
             */
            std::swap(_n1, _n0);
            std::swap(_d1, _d0);
            break;
        case Protocol::Reflect:
            /*
             * x2 = -x1 => x1 = -x2
             *
             * (n1x1+n0)/(d1x1+d0)
             * = (n1(-x2)+n0)/(d1(-x2)+d0)
             * = ((-n1)x2+n0)/((-d1)x2+d0)
             * = (n1x2+(-n0))/(d1x2+(-d0))
             */
            if (_n0 || _d0)
            {
                assert(!__builtin_mul_overflow(_n0, -1, &_n0));
                assert(!__builtin_mul_overflow(_d0, -1, &_d0));
            }
            else
            {
                assert(!__builtin_mul_overflow(_n1, -1, &_n1));
                assert(!__builtin_mul_overflow(_d1, -1, &_d1));
            }
            break;
        case Protocol::Ground:
            /*
             * x2 = -1/x1 => x1 = -1/x2
             * = (n1(-1/x2)+n0)/(d1(-1/x2)+d0)
             * = (-n1+n0x2)/(-d1+d0x2)
             * = (n0x2+(-n1))/(d0x2+(-d1))
             */
            // FIXME: performance?
            assert(!__builtin_mul_overflow(_n1, -1, &_n1));
            assert(!__builtin_mul_overflow(_d1, -1, &_d1));
            std::swap(_n1, _n0);
            std::swap(_d1, _d0);
            break;
        default:
            throw std::logic_error("unhandled protocol message");
    }
    tracelog("ingesting " << input << " from " << _x << ", new state " << _n1 << " " << _n0 << " " << _d1 << " " << _d0);
}

}  // namespace strategy
}  // namespace clarith
}  // namespace deepnum

