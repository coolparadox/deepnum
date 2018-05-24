[![API Reference](https://img.shields.io/badge/api-reference-blue.svg)](https://coolparadox.github.io/number-reducer/)
[![Build Status](https://travis-ci.com/coolparadox/number-reducer.svg?branch=master)](https://travis-ci.com/coolparadox/number-reducer)

This does nothing useful yet. Someday it'll handle arithmetic in [continued logarithm](https://perl.plover.com/classes/cftalk/INFO/gosper.txt) format.

Continued logarithms is one form of representing quantities with arbitrary precision.

The library is called number "reducer" in the sense the intended interface will provide means to extract pieces of information from numeric values on each access, causing the reduction of the underlying "quantity of (continued log) information" of the represented value.

The roadmap intends to cover at least the reducing of:
- Ratios of integers
- Basic arithmetic operations with two inputs
- Exponentiation to integer quantities
- Rational approximations of common irrational functions (logarithm, trigonometry etc)

This library will be the foundation of a more ambitious (and so far poorly defined) project for offering easy arithmetic of rational numbers with arbitrary precision. This arbitrary precision rational library wannabe, on its turn, will someday be the foundation of another more ambitious and almost insane project for offering some form of computation of irrational quantities, where the level of precision of rational approximations used for measurement of irrational values is automatically detected based on caller's constraints.

On second thoughts, we'll probably be safer using floating point arithmetic instead as usual ;-)

Cheers,
Rafael
