#pragma once

#include <map>
#include <string>
#include <Windows.h>

#include "./../Utils/HashMap.h"

class CTimer
{
    private:
        LARGE_INTEGER m_timeFreq;
        LARGE_INTEGER m_lastTime;
        LARGE_INTEGER m_actualTime;

        float m_gameFps;
        float m_gameTime;

        float m_frameTime;
        float m_totalFrameTime;

        float m_speedFactor;
        HashMap<float> m_pObjectTimer;

        unsigned int m_fpsLimit;
        unsigned int m_framesCount;

        void updateTimer            (void);
        void updateFrames           (void);
        void updateObjectTimer      (void);

	public:
        CTimer                      (unsigned int fpsControl);
        ~CTimer                     (void);

        void	Update              (void);

        float   GetFrames           (void);
        float   GetSpeedFactor      (void);
        float	GetFrameTimeInMs	(void);

        bool    EndOfTime           (const std::string &object, float ms);
};
