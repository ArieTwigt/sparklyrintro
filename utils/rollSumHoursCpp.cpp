#include <Rcpp.h>
#include <vector>
#include <string>
using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::export]]
NumericVector rollSumHoursCpp(StringVector time, StringVector animal_ids, NumericVector activity, int hours) {
  int n = time.length();
  NumericVector rollSum(n);
  for (int i = 1 ; i < time.length(); i++){
    auto animal_id = animal_ids[i];
    if(i < 2){
      rollSum[i] = activity[i];
    }
    else if (std::strncmp (animal_id, animal_ids[i - 1], 2) == 0){
      if(i > hours){
        if (std::strncmp(animal_id, animal_ids[i - hours + 1], 2) == 0){
          rollSum[i] = (rollSum[i - 1] + activity[i]) - activity[i - hours];
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