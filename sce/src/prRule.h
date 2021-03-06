// file: allocLet.h
// author:  tom

#ifndef  LGFRSCEPRIORITYRULE_H
#define  LGFRSCEPRIORITYRULE_H

#include <string>

#include <stdlib.h>
#include <sce/src/sceDefin.h>
// #include <sce/src/mPlantH.h>
// #include <wit/src/wit.h>


class WitRun;
class LgFrMultiPlantHelper;

class LgFrScePriorityRule {  
public:

  // set/gets (if needed)
  void partName(const std::string & partName);
  std::string partName() const;
  void sourceLoc(const std::string & sourceLoc);
  std::string sourceLoc() const;
  void customerLoc(const std::string & customerLoc);
  std::string customerLoc() const;
  void demandClass(const std::string & demandClass);
  std::string demandClass() const;
  void demandLevel(const std::string & demandLevel);
  std::string demandLevel() const;
  void partClass(const std::string & partClass);
  std::string partClass() const;
  void effect_start(const std::string & effect_start);
  std::string effect_start() const;
  void effect_end(const std::string & effect_end);
  std::string effect_end() const;
  void priority(int priority);
  int priority() const;
  void startPeriod(int sP);
  int startPeriod() const;
  void endPeriod(int eP);
  int endPeriod() const;
  void prValHitVecPosition(int prValHitVecPosition);
  int prValHitVecPosition() const;


  // hardcoding the attributes is sloppy.   Finish_me: parameerize it.
  void isPartAll(bool isPartAll);
  bool isPartAll() const;
  void isSourceLocAll(bool isPartAll) ;
  bool isSourceLocAll() const ;
  void isCustomerLocAll(bool isPartAll) ;
  bool isCustomerLocAll() const ;
  void isDemandClassAll(bool isPartAll) ;
  bool isDemandClassAll() const ;
  void isDemandLevelAll(bool isPartAll) ;
  bool isDemandLevelAll() const ;
  void isPartClassAll(bool isPartAll) ;
  bool isPartClassAll() const ;





  // set/get the dependent 
  void backlogDependent(LgFrScePriorityRule * dependent);
  LgFrScePriorityRule * backlogDependent();




  // create a TRACE STRING
  std::string
  traceString();


   // create a Human Readable TRACE STRING
  std::string
  hrTraceString(WitRun * const theWitRun, 
		LgFrMultiPlantHelper * mpHelper, 
		int equitCount);

   


  // print the allocLet to stdout
  void
  print();




  

  // preferred constructor 
  LgFrScePriorityRule( std::string & partName,
		       std::string & sourceLoc,
		       std::string & customerLoc,
		       std::string & demandClass,
		       std::string & demandLevel,
		       std::string & partClass,
		       std::string & effect_start,
		       std::string & effect_end,
		       int           priority,
		       int startPeriod,
		       int endPeriod,
		       bool isPartAll,
		       bool isSourceLocAll,
		       bool isCustomerLocAll,
		       bool isDemandClassAll,
		       bool isDemandLevelAll,
		       bool isPartClassAll);


  
  // Construct from a Trace String
  LgFrScePriorityRule(std::string & traceString);



  // destructor
  virtual
  ~LgFrScePriorityRule();


  // copy constructor
  LgFrScePriorityRule(const LgFrScePriorityRule& source);
  
  // assignment operator
  LgFrScePriorityRule&
  operator=(const LgFrScePriorityRule& rhs);
  
  // default constructor
  LgFrScePriorityRule();
  
  
  
private:
  std::string partName_;
  std::string sourceLoc_;
  std::string customerLoc_;
  std::string demandClass_;
  std::string demandLevel_;
  std::string partClass_;
  std::string effect_start_;
  std::string effect_end_;
  int         priority_;
  int startPeriod_;
  int endPeriod_;
  bool isPartAll_;
  bool isSourceLocAll_;
  bool isCustomerLocAll_;
  bool isDemandClassAll_;
  bool isDemandLevelAll_;
  bool isPartClassAll_;
};



#endif
















