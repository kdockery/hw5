

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID =  (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
  const AvailabilityMatrix& avail,
  const size_t d,
  const size_t m,
  DailySchedule& sched,
  size_t row, size_t col, size_t n, size_t k,
  std::vector<size_t>& daysWorked
);

bool isValid(
  const AvailabilityMatrix& avail,
  const size_t d,
  const size_t m,
  DailySchedule& sched,
  size_t row, size_t i, size_t n,
  std::vector<size_t>& daysWorked
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    //finding number of days and workers
   size_t n = avail.size();
   size_t k = avail[0].size();
    // Setting appropriate dimensions for sched
    sched.resize(n, std::vector<Worker_T>(dailyNeed)) ;

    //setting all values of sched to 1000 
    for (size_t i=0; i<n; i++){
      for (size_t j=0; j< dailyNeed; j++){
        sched[i][j] = 1000;
      }
    }
    std::vector<size_t> daysWorked (k, 0);


    if (scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0, n, k, daysWorked) == true) return true;
    else return false;


}
//scheduleHelper(): create an n by d schedule matrix of k workers over n days that 
//follows the given parameters. Return true if schedule possible, false if not
bool scheduleHelper(
  const AvailabilityMatrix& avail,
  const size_t d,
  const size_t m,
  DailySchedule& sched,
  size_t row, size_t col, size_t n, size_t k,
  std::vector<size_t>& daysWorked
)
{
  //base case
  if (row == n) return true;
  
  if(sched[row][col] == 1000){
    //try workers 0-k here and recurse if the placement works
    for (size_t i=0; i<k; i++){
      //try i recurse if placement works
      sched[row][col] = i;
      daysWorked[i] ++;
      if(isValid(avail, d, m, sched, row, i, n, daysWorked) == true){
        //recurse 
        if(row == n-1) { 
          if(scheduleHelper(avail, d, m, sched, 0, col+1, n, k, daysWorked) == true) return true; }
        else { 
          if(scheduleHelper(avail, d, m, sched, row+1, col, n, k, daysWorked) == true) return true; }
      }
      daysWorked[i] --;
    }
    //backtracing step
    sched[row][col] = 1000;
  }
  else{
    //recurse onto next sched cell
    if(col == d) { if(scheduleHelper(avail, d, m, sched, row + 1, col, n, k, daysWorked) == true) return true; }
    else { if(scheduleHelper(avail, d, m, sched, row, col + 1, n, k, daysWorked) == true) return true; }
  }
  //if no valid schedule
  return false;
}

bool isValid(
  const AvailabilityMatrix& avail,
  const size_t d,
  const size_t m,
  DailySchedule& sched,
  size_t row, size_t i, size_t n,
  std::vector<size_t>& daysWorked
  )
{
  std::vector<std::vector<Worker_T>>::iterator rowIT;
  std::vector<Worker_T>::iterator colIT;
  //checks if worker is available specified day
  if(avail[row][i] == 0) return false; 
  
  //checks if specified worker already scheduled for day
  size_t num = std::count(sched[row].begin(), sched[row].end(), i);
  if (num > 1) return false;
  
  //checks if specified worker already scheduled max times
  if(daysWorked[i] > m) return false;

  return true;
}