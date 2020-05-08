#include "./Timer.h"

CTimer::CTimer(unsigned int fpsControl)
{
    QueryPerformanceCounter(&m_lastTime);
    QueryPerformanceFrequency(&m_timeFreq);

    m_fpsLimit	= fpsControl;
    m_speedFactor = 1.0;

    m_actualTime.QuadPart = 0L;
    m_timeFreq.QuadPart = 0L;

    m_framesCount = 0;
    m_totalFrameTime = 0;
}

void CTimer::updateTimer(void)
{
    QueryPerformanceCounter(&m_actualTime);
    QueryPerformanceFrequency(&m_timeFreq);

    m_frameTime = (float) (m_actualTime.QuadPart - m_lastTime.QuadPart) / (float) m_timeFreq.QuadPart;
    m_gameTime  = (float) m_actualTime.QuadPart / (float) m_timeFreq.QuadPart;

    m_speedFactor = m_fpsLimit / (1.0f / m_frameTime);
    if(m_speedFactor <= 0.0) m_speedFactor = 1.0;

    m_lastTime  = m_actualTime;
}

void CTimer::updateFrames(void)
{
    m_framesCount++;
    m_totalFrameTime += m_frameTime;
    m_gameFps = m_framesCount / m_totalFrameTime;

    if(m_totalFrameTime * 1000.0 > 1000.0)
    {
         m_framesCount = 0;
         m_totalFrameTime = 0.0;
    }
}

void CTimer::updateObjectTimer(void)
{
    HashMap<float>::HashMapType l_HashMap =  m_pObjectTimer.GetHashMap();

    for (HashMap<float>::HashMapType::iterator it = l_HashMap.begin(); it != l_HashMap.end(); it++)
    {
        if (m_gameTime >= it->Value) it = --l_HashMap.erase(it);
    }
}

void CTimer::Update(void)
{
    updateTimer();
    updateFrames();
    updateObjectTimer();
}

bool CTimer::EndOfTime(const std::string &object, float ms)
{
    bool isEndOfTimer = false;
    HashMap<float>::MapEntryType *l_MapEntry = m_pObjectTimer.find(object);

    if(l_MapEntry == NULL)
    {
        m_pObjectTimer.Add(object, ms);
        isEndOfTimer = true;
    }

    return isEndOfTimer;
}
