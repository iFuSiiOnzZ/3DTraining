#pragma once

#include <Windows.h>

#include "Common/TaskPool/Task.h"
#include "Common/TaskPool/Utils/RWLock.h"

enum E_MOUSE_BUTTONS
{
    BUTTON_LEFT = 0,
    BUTTON_CENTER,
    BUTTON_RIGHT,

    BUTTON_COUNT
};

class CMouse : public CTask
{
	private:
        POINT m_DeltaPos;
        POINT m_ScreenSize;

        POINT m_ScreenPos;
        POINT m_PrevScreenPos;

		bool m_LeftButton;
		bool m_RightButton;

        HWND m_ScreenHandle;
        CRWLock m_RWLock;

	public:
        CMouse              (int sWidth, int sHeight, const HWND &hWnd);
		~CMouse	            (void);

		void	Update		(void);
        void    Execute     (void);

        int     GetDeltaX   (void);
        int     GetDeltaY   (void);

		bool	isLeftPress	(void);
		bool	isRightPress(void);
};
