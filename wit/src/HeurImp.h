//==============================================================================
// IBM Confidential
//
// OCO Source Materials
//
// Watson Implosion Technology
//
// (C) Copyright IBM Corp. 1993, 2012  All Rights Reserved
//
// The Source code for this program is not published or otherwise divested of
// its trade secrets, irrespective of what has been deposited with the U. S.
// Copyright office.
//==============================================================================

#ifndef HeurImpH
#define HeurImpH

//------------------------------------------------------------------------------
// Header file: "HeurImp.h"
//
// Contains the declaration of class HeurImploder.
//------------------------------------------------------------------------------

#include <Assoc.h>

//------------------------------------------------------------------------------
// class HeurImploder
//
// This class provides the interface between heuristic implosion and the rest
// of WIT. An instance of this class exists of long as the Problem that owns it
// exists.
//------------------------------------------------------------------------------

class WitHeurImploder: public WitProbAssoc
   {
   public:

      //------------------------------------------------------------------------
      // Constructor functions.
      //------------------------------------------------------------------------

      WitHeurImploder (WitProblem * theProblem);
         //
         // ProbAssoc <<< theProblem.

      //------------------------------------------------------------------------
      // Destructor function.
      //------------------------------------------------------------------------

      ~WitHeurImploder ();

      //------------------------------------------------------------------------
      // Other public member functions.
      //------------------------------------------------------------------------

      void implode (bool forOpt);
         //
         // Performs a heuristic implosion.
         // forOpt indicates whether or not the heuristic implosion is for
         // optimizing implosion.

      void genPriorities (WitSchedule <WitDemand, int> & newPriority);
         //
         // Automatically generates priorities from objective data.
         // Stores the new priorities in newPriority.
         // The priorities are generated as follows:
         //    The demands are sorted according to objective function data.
         //    Then the priorities are assigned according to the order in which
         //    the demands appear in the sorted list.

      accessFunc (WitHeurImpPerf *, myHeurImpPerf)

   private:

      //------------------------------------------------------------------------
      // Private member functions.
      //------------------------------------------------------------------------

      static bool compareObj (WitDemand *, WitDemand *);
         //
         // Comparison function for sorting demands in order to generate
         // priorities.
         //
         // Compares for:
         //   higher shipReward,    then
         //   higher cumShipReward, then
         //   higher stockCost,     then
         //   lower  index,
         // all in priorityPer_.

      noCopyCtorAssign (WitHeurImploder);

      //------------------------------------------------------------------------
      // Private member data.
      //------------------------------------------------------------------------

      WitHeurImpPerf * myHeurImpPerf_;
         //
         // During heuristic implosion, myHeurImpPerf_ is the HeurImpPerf that
         // performs it.
         // Otherwise NULL.

      WitPeriod priorityPer_;
         //
         // The period for which priorities are currently being generated by
         // genPriorities.
   };

#endif