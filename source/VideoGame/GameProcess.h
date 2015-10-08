#pragma once

#include "Core/Process.h"

#include "Common/Math/Constants.h"
#include "Common/Math/Matrix/Matrix.h"
#include "Common/Math/Vector/Vector.h"

#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Shaders/Shader.h"

class CGraphicsManager;
class CInputManager;
class CTimer;

class CObject3D;
class CCamera;

class CGameProcess : public CProcess
{
	private:
        CMatrix4f m_Model;
        CFrustumf m_Frustum;

        CLookAtf m_View;
        CObject3D *m_p3DObject;

        CTimer *m_pTimer;
        CCamera *m_pCamera;
        CInputManager *m_pInput;

        CShaderProgram m_ShaderProgram;

	public:
        CGameProcess(CGraphicsManager *l_pGraphicsManager);
        ~CGameProcess(void);

		void Update (void);
        void Render (void);

        void Init    (void);
        void Release (void);
};
