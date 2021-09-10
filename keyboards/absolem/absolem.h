#ifndef ABSOLEM_H
#define ABSOLEM_H

#include "quantum.h"

#define KNO KC_NO

// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
  lpt, lrt, lmt, lxt, lit, rit, rxt, rmt, rrt, rpt, \
  lph, lrh, lmh, lxh, lih, rih, rxh, rmh, rrh, rph, \
  lpb, lrb, lmb, lxb, lib, rib, rxb, rmb, rrb, rpb, \
            ltn, lth, ltf, rtf, rth, rtn \
) \
{ \
  { lit, lxt, lmt, lrt, lpt}, \
  { lih, lxh, lmh, lrh, lph}, \
  { lib, lxb, lmb, lrb, lpb}, \
  { ltf, lth, ltn, KNO, KNO}, \
  { rit, rxt, rmt, rrt, rpt}, \
  { rih, rxh, rmh, rrh, rph}, \
  { rib, rxb, rmb, rrb, rpb}, \
  { rtf, rth, rtn, KNO, KNO} \
}


#endif
