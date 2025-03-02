#ifndef __INDI__
#define __INDI__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cstdint>


class TIndi {
public:
  TIndi();
  ~TIndi();
  void Define( int N );
  void Redefine(int N);
  TIndi& operator = ( const TIndi& src );   /* Copy */
  bool operator == (  const TIndi& indi2 ); /* Return true if two tours are the same, false otherwise */

  int fN;                 /* Number of cities */
  int** fLink;            /* fLink[i][]: two vertices adjacent to i */
  int64_t fEvaluationValue;   /* Tour length of */
};


#endif

