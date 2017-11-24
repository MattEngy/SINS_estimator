#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <assert.h>

class progbar_t
{
	public:
		progbar_t(int maxval, int barlen = 30)
		: _maxval(maxval),
		_barlen(  barlen) {
			assert(barlen > 2);
			_bar = new char[barlen + 3];
			_bar[0] = '|';
			for (int i = 1; i <= barlen; i++) {
                        	_bar[i] = '-';
			}
			_bar[barlen + 1] = '|';
			_bar[barlen + 2] = '\0';
		}

		~progbar_t() {
			delete[] _bar;
		}

		void upd(int val) {
			float prog = val / (float)_maxval;
			int apb = (int)trunc(prog * (_barlen - 1)) + 1; // arrow pos buffer
			if ((apb != _arrpos) && (val >= 0) && (val <= _maxval)) {
				_bar[_arrpos] = '=';
				_bar[apb] = '>';
				printf("\r%s   [%3d%%]", _bar, (int)round(prog * 100));
				fflush(stdout);
				_arrpos = apb;
			}
		}
	private:
		const int _maxval,
		          _barlen;

		int       _arrpos = 2; //2 is to force update during first call

		char*     _bar;
};
