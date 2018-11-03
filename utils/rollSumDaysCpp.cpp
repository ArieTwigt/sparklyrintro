#include <Rcpp.h>
#include <vector>
#include <string>
using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::export]]
NumericVector rollSumDaysCpp(StringVector time, StringVector animal_ids, NumericVector activity, int window) {
  int n = time.length();
  NumericVector rollSum(n);
  for (int i = 1 ; i < time.length(); i++){
    auto animal_id = animal_ids[i];
    if(i < 2){
      rollSum[i] = activity[i];
    }
    else if (std::strncmp (animal_id, animal_ids[i - 1], 2) == 0){
      if(i > window){
        if (std::strncmp(animal_id, animal_ids[i - window + 1], 2) == 0){
          rollSum[i] = (rollSum[i - 1] + activity[i]) - activity[i - window];
        }
        else {
          rollSum[i] = rollSum[i - 1] + activity[i];
        }
      } else {
          rollSum[i] = rollSum[i - 1] + activity[i];
      }
    } else {
      rollSum[i] = activity[i];
    }
}
  return rollSum;
}

