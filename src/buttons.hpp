#ifndef BUTTONS_HPP
#define BUTTONS_HPP

#include <string.h>

#include <psp2/kernel/processmgr.h>
#include <psp2/touch.h>
#include <psp2/ctrl.h>

class Input
{
	public:
		Input();

		enum buttonIndex
		{
			select = 0,
			start = 1,

			up = 2,
			right = 3,
			down = 4,
			left = 5,
			
			lTrigger = 6,
			rTrigger = 7,

			triangle = 8,
			circle = 9,
			cross = 10,
			square = 11,

			lAnalogUp = 12,
			lAnalogRight = 13,
			lAnalogDown = 14,
			lAnalogLeft = 15,

			frontTouch = 16
		};

		// Update button states
		bool wasPressed( buttonIndex id );

		bool isTouched();
		int getTouchX();
		int getTouchY();

	private:
		// Inputs
		SceCtrlData pad;

		SceTouchData touch_old[ SCE_TOUCH_PORT_MAX_NUM ];
		SceTouchData touch[ SCE_TOUCH_PORT_MAX_NUM ];

		// Analog stick deadzone
		const float ANALOG_DEADZONE = 0.6f;

		// Buttons
		bool button[ 16 ];
};


#endif // BUTTONS_HPP