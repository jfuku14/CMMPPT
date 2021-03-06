// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
//----------------------------------------------------- 
// Simple example usage of the cut generation library. 
//
// This sample program iteratively tightens a 
// given formulation by adding cuts, then calls 
// branch-and-bound to solve the tightened
// formulation.
//
// usage:
//   cgl1 mpsFileName objectiveSense
// where:
//   mpsFileName: Name of an mps file (without the
//                file extension)
//   objectiveSense: min for minimization, 
//                   max for maximization. 
// example:
//   cgl1 ../Mps/p0033 min              
//----------------------------------------------------- 
// The knapsack cut generator assumes the primal solution is feasible.
#include <cassert>
#include <iostream>

#include "OsiCuts.hpp"
#include "OsiClpSolverInterface.hpp"

#include "CglKnapsackCover.hpp"
#include "CglSimpleRounding.hpp"

using std::cerr;
using std::cout;
using std::endl;

int main(int argc, const char *argv[])
{
  // Make sure a file name and objective sense
  // were specified
  if ( argc<3 ) {
    cerr <<"Incorrect number of command line parameters." <<endl;
    cerr <<"  usage:" <<endl;
    cerr <<"    "<<argv[0] <<" mpsFileName objectiveSense" <<endl;
    cerr <<"  where:" <<endl;
    cerr <<"    mpsFileName: Name of an mps file" <<endl;
    cerr <<"                 without \".mps\" file extension" <<endl;
    cerr <<"    objectiveSense: min for minimization," <<endl; 
    cerr <<"                    max for maximization." <<endl; 
    return 1;
  }  

  // Make sure valid objective sense was specified
  if( strcmp(argv[2],"min") && strcmp(argv[2],"max" ) ){
    cerr <<"Unrecognized objective sense specifed" <<endl;
    cerr <<"  specified value: \"" <<argv[2] <<"\"" <<endl;

    cerr <<"  valid values: \"min\" for minimization," <<endl; 
    cerr <<"                \"max\" for maximization." <<endl; 
    return 1;
  }  
  
  // Instantiate a specific solver interface
  OsiClpSolverInterface si;

  // Read file describing problem
  si.readMps(argv[1],"mps"); 

  // Set objective min to max
  // First make sure min or max were specified
  if ( !strcmp(argv[2],"min") ) si.setObjSense(1.0);
  else si.setObjSense(-1.0);
  
  // Solve continuous problem
  si.initialSolve();

  // Save the orig lp relaxation value for 
  // comparisons later
  double origLpObj = si.getObjValue();

  // Track the total number of cuts applied
  int totalNumberApplied = 0;

  // Instantiate cut generators
  CglKnapsackCover cg1;
  CglSimpleRounding cg2;

  //---------------------------------------------------
  // Keep applying cuts until 
  //   1. no more cuts are generated
  // or
  //   2. the objective function value doesn't change
  //---------------------------------------------------
  bool equalObj;
  CoinRelFltEq eq(0.0001);
  OsiSolverInterface::ApplyCutsReturnCode acRc;
  double obj;

  do {
    // Get current solution value
    obj = si.getObjValue();

    // Generate and apply cuts
    OsiCuts cuts;
    cg1.generateCuts(si,cuts);
    cg2.generateCuts(si,cuts);
    acRc = si.applyCuts(cuts,0.0);

    // Print applyCuts return code
    cout << endl << endl;
    cout <<cuts.sizeCuts() <<" cuts were generated" <<endl;
    cout <<"  " <<acRc.getNumInconsistent() <<" were inconsistent" <<endl;
    cout <<"  " <<acRc.getNumInconsistentWrtIntegerModel() 
         <<" were inconsistent for this problem" <<endl;
    cout <<"  " <<acRc.getNumInfeasible() <<" were infeasible" <<endl;
    cout <<"  " <<acRc.getNumIneffective() <<" were ineffective" <<endl;
    cout <<"  " <<acRc.getNumApplied() <<" were applied" <<endl;
    cout << endl << endl;

    // Increment the counter of total cuts applied
    totalNumberApplied += acRc.getNumApplied();

    // If no cuts were applied, then done
    if ( acRc.getNumApplied()==0 ) break;

    // Resolve
    si.resolve();

    cout << endl;
    cout <<"After applying cuts objective value changed from "
         <<obj <<" to " <<si.getObjValue() <<endl << endl;
    
    // -----------------------------------------------
    // Set Boolean flag to true if new objective is 
    // almost equal to prior value.
    //
    // The test is:
    // abs(oldObj-newObj) <= 0.0001*(max(abs(oldObj),abs(newObj))+1.);
    // see CoinRelFloatEqual.h 
    // -----------------------------------------------
    equalObj = eq( si.getObjValue(), obj );
  } while( !equalObj );
  
  // Print total number of cuts applied, 
  // and total improvement in the lp objective value
  cout << endl << endl;
  cout << "----------------------------------------------------------" 
       << endl;
  cout << "Cut generation phase completed:" << endl;
  cout << "   " << totalNumberApplied << " cuts were applied in total," 
       << endl;
  cout << "   changing the lp objective value from " << origLpObj 
       << " to " << si.getObjValue() << endl;
  cout << "----------------------------------------------------------" 
       << endl;
  cout << endl << endl;

  // If you want to solve problem, change "#if 0" to "#if 1"
#if 0
  // Solve MIP Problem
  si.branchAndBound();

  // Print the solution
  cout <<"The objective function value: " <<si.objvalue() <<endl;
  const double * soln = si.colsol();
  int i;
  for ( i=0; i<si.numcols(); i ++ ) {
    cout <<" x[" <<i <<"] = " <<soln[i] <<endl;
  }
#endif

  return 0;
}
