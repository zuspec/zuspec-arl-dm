/*
 * py_get_arl.cpp
 *
 *  Created on: Apr 21, 2022
 *      Author: mballance
 */
#include "py_get_arl.h"
#include "arl/loader.h"

arl::IArl *py_get_arl(const char *path) {
	return get_arl(path);
}


