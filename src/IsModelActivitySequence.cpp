/*
 * IsModelActivitySequence.cpp
 *
 *  Created on: Jun 17, 2022
 *      Author: mballance
 */

#include "IsModelActivitySequence.h"

namespace arl {

IsModelActivitySequence::IsModelActivitySequence() : m_is(false) {
	// TODO Auto-generated constructor stub

}

IsModelActivitySequence::~IsModelActivitySequence() {
	// TODO Auto-generated destructor stub
}

bool IsModelActivitySequence::test(IModelActivity *a) {
	m_is = false;
	if (a) {
		a->accept(this);
	}
	return m_is;
}

} /* namespace arl */
