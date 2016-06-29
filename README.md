# indri-ranking
Implement different ranking function for indri by implementing scoring function
for each query term.

First, implement the ranking function at **INDRI_HOME/include/indri/** following the
sample code *_TFIDFTermScoreFunction.hpp_sample*. You need to implement the constructor and
two functions:
```
double scoreOccurrence( double occurrences, int documentLength ) 
double scoreOccurrence( double occurrences, int contextSize, double documentOccurrences, int documentLength )
```
The *idf* and *avgDocLength*, as well as parameters are computed and passed  to the
constructor from the caller(will be discussed latter).

The first function is acturally where the score for each query term is computed and the second scoring function is usually implemented by simply returning the first scoring function (it acutally is used for some complex query logic involving beliefs of a query node, which is rarely used. So leave it like that would not be a problem).
```
return scoreOccurrence(occurrences, contextSize);
```


It is important to note that in the previous functions, the *contextSize* refers to the document length of the current document which score is computed on. Therefore, *idf* and *avgDocLength* need to be computed by the caller, which is *TermScoreFunctionFactory*. 


After implementing the scoring function, you need to include it to the **INDRI_HOME/src/TermScoreFunctionFactory.cpp** and define the string you use in the indri runQuery parameter file to indicate that you are using this new ranking function, following the sample code _TermScoreFunctionFactory.cpp_sample

Finally, put the code into the corresponding directory wrt $INDRI_HOME and re-compile indri, the method is then ready to use.


 
