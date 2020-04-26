#pragma once

#include "Graphics/GraphicsManager/GraphicsManager.h"
#include "platform.h"

struct S_USER_INPUT;

class CProcess
{
    protected:
        CGraphicsManager *m_pGraphicsManager;

    public:
        CProcess  (CGraphicsManager *graphicsManager);
        virtual ~CProcess (void) {}

        virtual void Update (const S_PLATFORM *platform) = 0;
        virtual void Render (const S_PLATFORM *platform) = 0;

        virtual void Init    (const S_PLATFORM *platform);
        virtual void Release (const S_PLATFORM *platform);
};
