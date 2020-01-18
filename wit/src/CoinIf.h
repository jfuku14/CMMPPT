//==============================================================================
// Constrained Materials Management and Production Planning Tool
//
// (C) Copyright IBM Corp. 1993, 2012  All Rights Reserved
//==============================================================================

#ifndef CoinIfH
#define CoinIfH

//------------------------------------------------------------------------------
// Header file: "CoinIf.h"
//
// Contains the declaration of class CoinIf.
//------------------------------------------------------------------------------

#include <SolverIf.h>

class ClpSimplex;
class CbcModel;

//------------------------------------------------------------------------------
// Class CoinIf
//
// "COIN Interface"
// Responsible for all interactions with COIN.
//
// Class Hierarchy:
//
// ProbAssoc
//    SolverIf
//       CoinIf
//------------------------------------------------------------------------------

class WitCoinIf: public WitSolverIf
   {
   public:

      //------------------------------------------------------------------------
      // Static public member functions.
      //------------------------------------------------------------------------

      static bool coinEmbedded ();
         //
         // Returns true, iff COIN embedded into the current build of WIT.

      static WitCoinIf * newInstance (WitOptSolveMgr * theOptSolveMgr);
         //
         // If COIN is embedded,
         //    creates and returns a new CoinIf for theOptSolveMgr.
         // If COIN is not embedded,
         //    issues a fatal error.

      //------------------------------------------------------------------------
      // Destructor function.
      //------------------------------------------------------------------------

      virtual ~WitCoinIf ();

      //------------------------------------------------------------------------
      // Overrides from class SolverIf.
      //------------------------------------------------------------------------

      virtual void         solveOptProbAsLexOpt ();
      virtual void         issueVersionMsg      ();
      virtual void         loadLp               ();
      virtual void         loadIntData          ();
      virtual void         reviseLp             ();
      virtual void         solverWriteMps       ();
      virtual void         loadInitSoln         (const WitVector <double> &);
      virtual void         reSolveLp            ();
      virtual void         solveLp              (bool);
      virtual void         solveMip             (bool);
      virtual void         getPrimalSoln        (WitVector <double> &);
      virtual void         getDualSoln          (WitVector <double> &);
      virtual const char * solverName           ();

   private:

      //------------------------------------------------------------------------
      // Private constructor functions.
      //------------------------------------------------------------------------

      WitCoinIf (WitOptSolveMgr *);

      //------------------------------------------------------------------------
      // Other private member functions.
      //------------------------------------------------------------------------

      noCopyCtorAssign (WitCoinIf);

      static CbcModel * newClpBasedCbcModel ();
         //
         // creates and return a CbcModel that owns a ClpSimplex.

      void setUpMessageHandler ();
         //
         // Sets up the COIN Message Handler.

      void shutDownMessageHandler ();
         //
         // Shouts down the COIN Message Handler.

      void checkStatusCode (int statusCode);
         //
         // Checks the status of the LP solution, given by statusCode.

      void reviseVarBounds ();
         //
         // Revises the upper and lower bounds on variables of the LP problem
         // that was previously loaded into CLP.

      void reviseConBounds ();
         //
         // Revises the upper and lower bounds on constraints of the LP problem
         // that was previously loaded into CLP.

      void reviseObjCoeffs ();
         //
         // Revises the objective function coefficients of the LP problem that
         // was previously loaded into CLP.

      void checkMipSolnStatus (bool optNeeded);
         //
         // Checks the status of the MIP solution.
         // optNeeded is to be true, iff an optimal solution is required.

      ClpSimplex * myClpSimplex ();
         //
         // Returns the ClpSimplex for this CoinIf.

      ClpSimplex * getClpSimplexFromCbcModel ();
         //
         // Returns the ClpSimplex owned by myCbcModel_;
         // Valid only in MIP mode.

      static void enterCoin ();
         //
         // Indicates, for timing purposes, that COIN functions are about to
         // be called.

      static void leaveCoin ();
         //
         // Indicates, for timing purposes, that COIN functions are no longer
         // about to be called.

      //-----------------------------------------------------------------------
      // Private member data.
      //-----------------------------------------------------------------------

      ClpSimplex * myClpSimplex_;
         //
         // The ClpSimplex owned by this CoinIf, in LP  mode.
         // NULL,                                in MIP mode.

      CbcModel * myCbcModel_;
         //
         // The CbcModel owned by this CoinIf, in MIP  mode.
         // NULL,                              in LP mode.
   };

#endif
