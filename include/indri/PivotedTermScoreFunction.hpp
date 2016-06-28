/*==========================================================================
 * Copyright (c) 2004 University of Massachusetts.  All Rights Reserved.
 *
 * Use of the Lemur Toolkit for Language Modeling and Information Retrieval
 * is subject to the terms of the software license set forth in the LICENSE
 * file included with this software, and also available at
 * http://www.lemurproject.org/license.html
 *
 *==========================================================================
 */


//
// TFIDFScoreFunction
//
// 23 January 2004 -- tds
//

#ifndef INDRI_PIVOTEDTERMSCOREFUNCTION_HPP
#define INDRI_PIVOTEDTERMSCOREFUNCTION_HPP
#include <iostream>
#include "indri/TermScoreFunction.hpp"
#include <math.h>
namespace indri
{
  namespace query
  {
    
    class PivotedTermScoreFunction : public TermScoreFunction {
    private:
      /// inverse document frequency (IDF) for this term
      double _inverseDocumentFrequency; 
      /// average document length in the collection
      double _averageDocumentLength;
      /// slope parameter
      double _slope;
      
      // The following values are precomputed so that score computation will go faster
      double _sOverAvgDocLength;
      
      void _precomputeConstants() {
        _sOverAvgDocLength = _slope*1.0 / _averageDocumentLength;
      }

    public:
      PivotedTermScoreFunction( double slope, double idf, double averageDocumentLength) {
        _slope = slope;
        _inverseDocumentFrequency = idf;
        _averageDocumentLength = averageDocumentLength;

        _precomputeConstants();
      }

      double scoreOccurrence( double occurrences, int documentLength ) {

          // Score function is:
          //                                                  1+log(1+log(occurrence))
          // score = IDF * ------------------------------------------------------------------
          //                              (1-s) + s * ( documentLength / avgDocLength) 
          //

          if (occurrences == 0){
            return 0;
          }
          double numerator = _inverseDocumentFrequency*(1.0+log( 1.0 + log(occurrences)));
          double denominator = 1.0 - _slope + _sOverAvgDocLength * documentLength;

          //cout << occurrences << " " << numerator << " " << denominator << endl;
          return numerator / denominator;
        
      }

      
      double scoreOccurrence( double occurrences, int contextSize, double documentOccurrences, int documentLength ) {
        return scoreOccurrence(occurrences, contextSize);
      }
      
      double maximumScore( int minimumDocumentLength, int maximumOccurrences ){
        return scoreOccurrence( maximumOccurrences, minimumDocumentLength );
      }
    };
  }
}

#endif // PIVOTED_TERMSCOREFUNCTION_HPP

