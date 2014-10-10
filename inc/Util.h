/* 
 * File:   Util.h
 * Author: khoai
 *
 * Created on October 10, 2014, 2:09 PM
 */

#ifndef UTIL_H
#define	UTIL_H

class Util {
public:
	static int isPercentProcStep(uint32_t total, uint32_t current, uint16_t step = 10) {
		uint16_t percent = (100*current / total);
		if (!current) {
			return 0;
		}
		if ((!(total % current) || (!(total % (total - current))))) {
			if (!(percent % 10)) {
				return percent;
			}
		}
		return 0;
	}
};

#endif	/* UTIL_H */

