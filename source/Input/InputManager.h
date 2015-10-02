#pragma once

#include <Windows.h>

#include "Common/TaskPool/Task.h"
#include "Common/TaskPool/Utils/RWLock.h"
#include "Common/TaskPool/Utils/ThreadLock.h"

#include "./Keyboard/Keyboard.h"
#include "./Mouse/Mouse.h"

class CInputManager : public CTask
{
	private:
        CMouse      m_MouseInput;
        CKeyboard   m_KeyboardInput;
        CRWLock     m_RWLock;

	public:
		~CInputManager	            (void);
		CInputManager	            (int sWidth, int sHeight, HWND &hWnd);

		void	Update			    (void);
        void    Execute             (void);

        int     GetDeltaX           (void);
        int     GetDeltaY           (void);

        bool    isKeyPressed        (const std::string &l_KeyName);
        void	AddKey				(const std::string &l_KeyName, unsigned int);

		bool	isLeftButtonPress	(void);
		bool	isRightButtonPress	(void);
};
