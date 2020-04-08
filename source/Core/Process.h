#pragma once

#include "Graphics/GraphicsManager/GraphicsManager.h"

class CProcess
{
    protected:
        CGraphicsManager *m_pGraphicsManager;

    public:
        CProcess  (CGraphicsManager *graphicsManager);
        virtual ~CProcess (void) {}

        virtual void Update (void) = 0;
        virtual void Render (void) = 0;

        virtual void Init    (void);
        virtual void Release (void);
};
