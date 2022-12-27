/*
 * loader.h
 *
 *  Created on: Feb 14, 2022
 *      Author: mballance
 */
#include <dlfcn.h>
#include <stdio.h>
#include "zsp/arl/dm/IArl.h"


static arl::IArl *get_arl(const char *path) {
	static arl::IArl *prv_arl = 0;

	if (!prv_arl) {
		void *dlh = dlopen(path, RTLD_LAZY);

		if (!dlh) {
			fprintf(stdout, "libvsc Error: failed to load library %s: %s\n",
					path, dlerror());
		} else {
			void *arl_f = dlsym(dlh, "iarl");

			if (!arl_f) {
				fprintf(stdout, "libvsc Error: failed to find symbol ivsc in library %s: %s\n",
						path, dlerror());
			} else {
				void *arl_h = ((void *(*)())arl_f)();
				prv_arl = reinterpret_cast<arl::IArl *>(arl_h);
			}
		}
	}

	return prv_arl;
}




