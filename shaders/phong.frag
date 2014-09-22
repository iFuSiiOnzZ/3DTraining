#version 330

uniform vec4 l_Pos;
uniform vec4 c_Pos;

uniform vec4 l_Amb;
uniform vec4 l_Diff;
uniform vec4 l_Spec;

in vec4 N;
in vec4 V;

in vec4 L;
in vec4 C;

out vec4 MyColor;

void main(void)
{
	vec4 vertexToLight  = normalize(L - V);
	vec4 vertexToCamera = normalize(C - V);

	//Ambient light
	vec4 iAmb = l_Amb;

	//Diffuse light
	float diffCoef = max(dot(normalize(N), vertexToLight), 0.0f);
	vec4 iDiff = diffCoef * l_Diff;

	//Specular light
	float specCoef = 0.0f;
	if(diffCoef > 0.0f) specCoef = pow(max(dot(vertexToCamera, -reflect(vertexToLight, N)), 0.0f), 5.0f);
	vec4 iSpec = l_Spec * specCoef;

	//Atenuation
	float dstToLight = length(L - V);
	float attenuation = 1.0f / (1.0f + 0.0f * pow(dstToLight, 2.0f));

	//Linear color
	vec4 linearColor = iAmb + attenuation * (iDiff + iSpec);

	//Gamma correction
	vec4 gamma = vec4(1.0f/2.2f);
	vec4 fColor = pow(linearColor, gamma);

	//Final color
	MyColor = fColor;
}
