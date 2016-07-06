/*==========================================================================
 * Author: Kuang Lu, University of Delaware 
 * lukuang@udel.edu
 *
 *==========================================================================
 */


//
// language model with JM smoothing
// based on:
// A Study of Smoothing Methods for Language
// Models Applied to Information Retrieval
//
// http://www.stat.uchicago.edu/~lafferty/pdf/smooth-tois.pdf
// 
//
// 
//

#ifndef INDRI_JMSMOOTHING_HPP
#define INDRI_JMSMOOTHING_HPP

#include "indri/TermScoreFunction.hpp"
#include <math.h>
#include <iostream>
using namespace std;

namespace indri
{
  namespace query
  {
    
    class JMSmoothingTermScoreFunction : public TermScoreFunction {
    private:
      /// collection frequency of query term p(t|c)
      double _collectionFrequency; 
      /// document frequency of query term p(t/d)
      double _documentFrequency;

      double _lambda;

      
      double _smoothed_cf;
      

      void _precomputeConstants() {
        _smoothed_cf = _lambda * _collectionFrequency;
      }

    public:
      JMSmoothingTermScoreFunction( double collectionFrequency,  double lambda ) {
        _collectionFrequency = collectionFrequency;
        

        _lambda = lambda;

        
        _precomputeConstants();
      }

      double scoreOccurrence( double occurrences, int documentLength ) {
        //
        // Score function is:
        //             [      (1-lambda)* occurrences)                        ]
        // score = log [ 1 + ----------------------------------               ]
        //             [       lambda * collectionFrequency                   ]                
        //

        double smoothed_df = (1-_lambda) * occurrences;
        return log(1+ smoothed_df/_smoothed_cf);
      }


      double scoreOccurrence( double occurrences, int contextSize, double documentOccurrences, int documentLength ) {
        return scoreOccurrence( occurrences, contextSize );
      }
      
    };
  }
}

#endif // INDRI_JMSMOOTHING_HPP

