/*
 * protocol.h
 *
 * Copyleft ...
 */

#ifndef SRC_PROTOCOL_H_
#define SRC_PROTOCOL_H_

namespace coolparadox {
namespace number {
namespace reducer {

/*
 * Based from Gosper (...)
 */
enum class Protocol {

    /**
     * I was a non positive number.
     * I negativated myself; so now I am at least zero.
     */
    kNegativated,

    /*
     * I was at least zero and lesser than one.
     * I reciprocated myself; so now I am at least one.
     */
    kReciprocated,

    /*
     * I was at least one and lesser than two.
     * I subtracted one from myself; so now I am at least zero and lesser than
     * one.
     */
    kSubtracted,

    /*
     * I was at least two.
     * I halved myself; so now I am at least one.
     */
    kHalved,

    /*
     * I am positive infinity.
     * There is no more information to extract from me.
     */
    kInfinite,
}

}  // namespace reducer
}  // namespace number
}  // namespace coolparadox

#endif  // SRC_PROTOCOL_H_
