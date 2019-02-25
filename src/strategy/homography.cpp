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

#include "homography.hpp"

#include <cassert>
#include <stdexcept>

#include "number.hpp"
#include "protocol/protocol.hpp"
#include "strategy/zero.hpp"
#include "strategy/exhaustion_error.hpp"
#include "strategy/ratio.hpp"
#include "strategy/unavailable_error.hpp"
#include "strategy/undefined_ratio_error.hpp"

using deepnum::clarith::protocol::Protocol;

namespace deepnum
{

namespace clarith
{

namespace strategy
{

Homography::Homography(Number* x, int n1, int n0, int d1, int d0)
        : _x(x), _n1(n1), _n0(n0), _d1(d1), _d0(d0),
        _exhausted(false)
{
    if (n1 == 0 && n0 == 0 && d1 == 0 && d0 == 0)
    {
        delete _x;
        throw UndefinedRatioError();
    }
    if (_n1 == 0 && _d1 == 0)
    {
        _exhausted = true;
        return;
    }
    if (_n1 == _d1 && _n0 == _d0)
    {
        _exhausted = true;
        return;
    }
    if (_n0 == 0 && _d0 == 0)
    {
        _n0 = _n1;
        _d0 = _d1;
        _exhausted = true;
        return;
    }
    // FIXME: normalize signs?
    // FIXME: normalize coefficients?
}

Homography::~Homography()
{
    delete _x;
}

protocol::Protocol Homography::Egest()
{
    if (_exhausted)
    {
        throw ExhaustionError();
    }

    int min_n;
    int min_d;
    int max_n;
    int max_d;
    Protocol output;
    do
    {

        // Ingest
        Protocol input = _x->Egest();
        switch (input)
        {
            case Protocol::End:
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
                    // FIXME: overflow
                    _n0 *= 2;
                    _d0 *= 2;
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
                // FIXME: performance?
                std::swap(_n1, _n0);
                std::swap(_d1, _d0);
                // FIXME: overflow
                _n0 += _n1;
                _d0 += _d1;
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
                _n0 *= -1;
                _d0 *= -1;
                break;
            case Protocol::Ground:
                /*
                 * x2 = -1/x1 => x1 = -1/x2
                 *
                 * (n1x1+n0)/(d1x1+d0)
                 * = (n1(-1/x2)+n0)/(d1(-1/x2)+d0)
                 * = (-n1+n0x2)/(-d1+d0x2)
                 * = (n0x2+(-n1))/(d0x2+(-d1))
                 */
                // FIXME: performance?
                std::swap(_n1, _n0);
                std::swap(_d1, _d0);
                _n0 *= -1;
                _d0 *= -1;
                break;
            default:
                throw std::logic_error("unhandled protocol message");
        }

        // value at 0
        min_n = max_n = _n0;
        min_d = max_d = _d0;

        // value at 1
        // FIXME:: overflow
        MinMax(&min_n, &min_d, &max_n, &max_d, _n1 + _n0, _d1 + _d0);

        // zero location
        if (IsBetweenZeroAndOne(-_n0, _n1)) {

            MinMax(&min_n, &min_d, &max_n, &max_d, 0, 1);

        }

        // pole location
        if (IsBetweenZeroAndOne(-_d0, _d1))
        {

            max_n = 1;
            max_d = 0;

        }

        output = CanEgest(min_n, min_d, max_n, max_d);

    } while (output == Protocol::End);
    return Egest(output);

}

void Homography::MinMax(int* min_n, int* min_d, int* max_n, int* max_d, int n, int d)
{
    if (Compare(n, d, *min_n, *min_d) < 0)
    {
        *min_n = n;
        *min_d = d;
    }
    else if (Compare(n, d, *max_n, *max_d) > 0)
    {
        *max_n = n;
        *max_d = d;
    }
}

bool Homography::IsBetweenZeroAndOne(int n, int d)
{
    return Compare(n, d, 0, 1) >= 0 && Compare(n, d, 1, 1) <= 0;
}

Protocol Homography::CanEgest(int min_n, int min_d, int max_n, int max_d)
{
    // End is reserved as negative for egestion.
    // FIXME: superfluous assertion?
    assert(min_n != 0 || max_n != 0);

    // FIXME: superfluous assertion?
    assert(Compare(min_n, min_d, max_n, max_d) <= 0);

    if (Compare(max_n, max_d, -1, 1) < 0) { return Protocol::Ground; }
    if (Compare(min_n, min_d, 1, 1) > 0) { return Protocol::Turn; }
    if (Compare(max_n, max_d, 0, 1) < 0 && Compare(min_n, min_d, -1, 1) >= 0) { return Protocol::Reflect; }
    if (Compare(min_n, min_d, 1, 2) > 0 && Compare(max_n, max_d, 1, 1) <= 0) { return Protocol::Uncover; }
    if (Compare(min_n, min_d, 0, 1) > 0 && Compare(max_n, max_d, 1, 2) <= 0) { return Protocol::Amplify; }

    // Given range does not fit to any available egestion possibility.
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
                // FIXME: overflow
                _n1 *= 2;
                _n0 *= 2;
            }
            else
            {
                _d1 /= 2;
                _d0 /= 2;
            }
        case Protocol:: Uncover:
            /*
             * 1/((n1x+n0)/(d1x+d0))-1
             * = (d1x+d0)/(n1x+n0)-1
             * = (d1x+d0)/(n1x+n0)-(n1x+n0)/(n1x+n0)
             * = ((d1-n1)x+(d0-n0))/(n1x+n0)
             */
            // FIXME: performance?
            std::swap(_n1, _d1);
            std::swap(_n0, _d0);
            // FIXME: overflow?
            _n1 -= _d1;
            _n0 -= _d0;
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
            _n1 *= -1;
            _n0 *= -1;
            break;
        case Protocol:: Ground:
            /*
             * 1/(-(n1x+n0)/(d1x+d0))
             * = -(d1x+d0)/(n1x+n0)
             * = ((-d1)x+(-d0))/(n1x+n0)
             */
            std::swap(_n1, _d1);
            std::swap(_n0, _d0);
            _n1 *= -1;
            _n0 *= -1;
            break;
        default:
            throw std::logic_error("unhandled protocol message");
    }
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

int Homography::Compare(int n0, int d0, int n1, int d1)
{
    // FIXME: overflow
    int p0 = n0 * d1;
    int p1 = n1 * d0;
    return (p0 > p1) - (p0 < p1);
}

}  // namespace strategy
}  // namespace clarith
}  // namespace deepnum

