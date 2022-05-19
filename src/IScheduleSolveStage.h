/*
 * IScheduleSolveStage.h
 *
 *  Created on: May 16, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>

namespace arl {

class IScheduleSolveStage;
using IScheduleSolveStageUP=std::unique_ptr<IScheduleSolveStage>;
class IScheduleSolveStage {
public:

	virtual ~IScheduleSolveStage() { }

	/**
	 * Evaluates the stage and returns:
	 * - true: SAT
	 *   - non-null SolveStage: must continue
	 *   - null SolveStage: complete solution
	 * - false: UnSAT
	 */
	virtual std::pair<bool,IScheduleSolveStage *> next() = 0;

	/**
	 * Indicates whether there are more choices to be evaluated
	 */
	virtual bool hasNext() = 0;


};

}
