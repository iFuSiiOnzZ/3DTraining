#pragma once

class CTask
{
    private:
        CTask   *m_pDependency;

    public:
        CTask   (void) { m_pDependency = 0; }
        ~CTask  (void) { m_pDependency = 0; }

        virtual void Execute        (void) = 0;
        void         AddDependency  (CTask *dependency)  { m_pDependency = dependency; }
        CTask        *GetDependency (void)                  { return m_pDependency; }
};
