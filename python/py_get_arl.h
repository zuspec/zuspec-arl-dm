/*
 * py_get_arl.h
 *
 *  Created on: Apr 21, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IArl.h"

extern "C" arl::IArl *py_get_arl(const char *path);
