/* --------------------------------------------------------------------- 

Copyright 2012 JKU Linz
Author: Philippe Seil (philippe.seil@jku.at)

This file is part of plbXml.

plbXml is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 2 of the License, or (at
your option) any later version.

plbXml is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with plbXml. If not, see http://www.gnu.org/licenses/.

---------------------------------------------------------------------- */


#ifndef TASKCLASSES2D_H_LBDEM
#define TASKCLASSES2D_H_LBDEM

#ifdef TASK_LIST
addToTaskMap<SetPressureBc>("setPressureBc");
addToTaskMap<SetPressureBcFromFile>("setPressureBcFromFile");
addToTaskMap<SetVelocityBc>("setVelocityBc");
addToTaskMap<SetVelocityBcFromFile>("setVelocityBcFromFile");
#else

#include "plbHeaders2D.h"
#include "taskBase.h"
#include "globalDefs.h"
#include "boundary2D.h"
#include "region2D.h"

#include <vector>

class PlbXmlController2D;
template<typename T> class LBconverter;
template<typename T> class SingleTaskFactory;


namespace Task {
  


  class SetPressureBc : public TaskBase {
  public:
    SetPressureBc(PlbXmlController2D const *controller, XMLreaderProxy const &r);
    virtual ~SetPressureBc();
    virtual void perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 plint nStep);
  protected:
    void setVal(T physVal);
    T valFromXml(XMLreaderProxy const &r);
    SetPressureBc(PlbXmlController2D const *controller, Box2D const &reg_,
		  T val, plint id);
  private:
    Box2D reg;
    T val,physVal;
  };

  class SetPressureBcFromFile : public SetPressureBc {
  public:
    SetPressureBcFromFile(PlbXmlController2D const *controller,
			  XMLreaderProxy const &r);
    virtual ~SetPressureBcFromFile();
    virtual void perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice,
			 plint nStep);
  private:
    std::vector<T> t,p;
    bool startFlag,endFlag,constantFlag;
    plint cursor, nStepThis, nStepNext;
  };

  class SetVelocityBc : public TaskBase {
  public:
    SetVelocityBc(PlbXmlController2D const *controller, XMLreaderProxy const &r);
    virtual ~SetVelocityBc();
    virtual void perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 plint nStep);
  protected:
    void setVal(Array<T,2> physVal);
    SetVelocityBc(PlbXmlController2D const *controller, Box2D const &reg_,
		  Array<T,2> const &val, plint id);
  private:
    Box2D reg;
    Array<T,2> val;    
  };

  class SetVelocityBcFromFile : public SetVelocityBc {
  public:
    SetVelocityBcFromFile(PlbXmlController2D const *controller, XMLreaderProxy const &r);
    virtual ~SetVelocityBcFromFile();
    virtual void perform(MultiBlockLattice2D<T,DESCRIPTOR> &lattice, 
			 plint nStep);
    friend TaskBase* setVelocityBcFromXml(PlbXmlController2D const *controller, 
					  XMLreaderProxy const &r);
  private:
    std::vector<T> t,vx,vy;
    bool startFlag,endFlag,constantFlag;
    plint cursor, nStepThis, nStepNext;

  };

};


#endif /* TASK_LIST */
#endif /* TASKCLASSES2D_H_LBDEM */
