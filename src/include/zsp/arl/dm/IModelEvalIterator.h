/*
 * IModelEvalIterator.h
 *
 *  Created on: Apr 24, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IModelEvalIteratorListener.h"
#include "zsp/arl/dm/IModelFieldAction.h"
#include "vsc/dm/IModelField.h"

namespace zsp {
namespace arl {
namespace dm {


enum class ModelEvalNodeT {
	/**
	 * 'action' supplies the model to traverse
	 */
	Action,

	/**
	 * 'iterator' provides the branch iterator
	 */
	Parallel,

	/**
	 * 'iterator' provides the sequence iterator
	 */
	Sequence

};

class IModelEvalIterator;
using IModelEvalIteratorUP=std::unique_ptr<IModelEvalIterator>;
class IModelEvalIterator {
public:

	virtual ~IModelEvalIterator() { }

	/**
	 * Either 'action' or 'iterator' will be valid on a 'true' return.
	 * On return of 'false', the iterator is no longer valid
	 */
	virtual bool next() = 0;

	virtual bool valid() = 0;

	virtual ModelEvalNodeT type() const = 0;

	virtual IModelFieldAction *action() = 0;

	virtual IModelEvalIterator *iterator() = 0;

    virtual void addListener(IModelEvalIteratorListener *l) = 0;

    virtual void remListener(IModelEvalIteratorListener *l) = 0;


};

}
}
}
