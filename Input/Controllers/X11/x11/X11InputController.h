/*
 * X11InputController.h
 *
 *  Created on: 2 Dec 2021
 *      Author: ykhan
 */

#ifndef X11_X11INPUTCONTROLLER_H_
#define X11_X11INPUTCONTROLLER_H_

#include "../InputController.h"
#include "X11InputDevice.h"
#include <X11/Xlib.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/XInput2.h>
#include <memory>

class X11InputController: public InputController {
private:
	Display* m_display{nullptr};
	Window* m_window{nullptr};
	XIDeviceInfoPtr m_xi_devices;
	int m_opcode{-1};
	int m_major{2};
	int m_minor{0};

public:
	X11InputController(Display* display, Window* window);
	virtual ~X11InputController() = default;
	void enumerate() override;
	bool initialize() override;
	X11InputDevicePtr createX11InputDevice(XIDeviceInfo* device_info);
	void getKeymap(char keymap[32]);
	char getKeysym(char key_code);
	MouseState getMouseState();
	XDeviceState* getXDeviceState(int deviceid);
	int detachDeviceById(int device_id);
};

#endif /* X11_X11INPUTCONTROLLER_H_ */
