#pragma once

class CProcess;
struct S_PLATFORM;

class CEngine
{
    private:
        CProcess *m_pProcess;

    public:
        CEngine  (CProcess *process);
        virtual ~CEngine (void) {}

        void Update (const S_PLATFORM *platform);
        void Render (const S_PLATFORM *platform);

        void Init    (const S_PLATFORM *platform);
        void Release (const S_PLATFORM *platform);
};
