#pragma once

class CProcess;

class CEngine
{
	private:
        CProcess *m_pProcess;

	public:
        CEngine  (CProcess *l_pProcess);
        ~CEngine (void);

        void Update (void);
        void Render (void);

        void Init    (void);
        void Release (void);
		
};
