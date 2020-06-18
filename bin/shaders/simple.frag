#version 330 core

struct Geometry
{
    vec3 position;
    vec3 normal;
    vec2 uv;
};

struct Material
{
    sampler2D ambientTexture;
    sampler2D diffuseTexture;
    sampler2D specularTexture;

    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;

    sampler2D bump;
    bool hasBump;
};

struct PointLight
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;

    float constant;
    float linear;
    float exp;

    samplerCube shadowMap;
    bool hasShadow;
};

struct DirectionalLight
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 direction;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLightUniform
{
    int counter;
    PointLight lights[64];
};

in VS_OUT
{
    vec2 uv;
    vec3 vertex;
    vec3 normal;

    vec4 vertexLightSpace;
    mat3 TBN;
} fs_in;

///////////////////////////////////////////////////////////////////////////////

uniform Material material;
uniform vec3 userViewPos;

uniform SpotLight spotLight;
uniform PointLightUniform pointLight;
uniform DirectionalLight directionalLight;

uniform sampler2D dirLightShadowMap;
uniform float zFar;

out vec4 screenColor;

///////////////////////////////////////////////////////////////////////////////

float fnc_get_atenuation(float constant, float linear, float exp, vec3 lightPos, vec3 vertexPos)
{
    float dist = distance(lightPos, vertexPos);
    return 1.0 / (constant + linear * dist + exp * dist * dist);
}

float fnc_get_specular(vec3 viewPos, vec3 vertexPos, vec3 lightDir, vec3 vertexNormal)
{
    vec3 viewDir = normalize(viewPos - vertexPos);
    vec3 reflectDir = reflect(-lightDir, vertexNormal);
    return pow(max(dot(viewDir, reflectDir), 0.0), 32);
}

float fnc_sample_show_map(sampler2D shadowMap, vec2 coords, float compare)
{
    return step(compare, texture(shadowMap, coords).r);
}

float fnc_sample_shadow_map_linear(sampler2D shadowMap, vec2 coords, vec2 texelSize, float compare)
{
    vec2 pixelPos = (coords / texelSize) + vec2(0.5);
    vec2 fracPart = fract(pixelPos), startTexel = (pixelPos - fracPart) * texelSize;

    float brTexel = fnc_sample_show_map(shadowMap, startTexel, compare);
    float blTexel = fnc_sample_show_map(shadowMap, startTexel + vec2(texelSize.x, 0), compare);
    float trTexel = fnc_sample_show_map(shadowMap, startTexel + vec2(0, texelSize.y), compare);
    float tlTexel = fnc_sample_show_map(shadowMap, startTexel + texelSize, compare);

    float mixA = mix(blTexel, brTexel, fracPart.x);
    float mixB = mix(tlTexel, trTexel, fracPart.x);

    return mix(mixA, mixB, fracPart.y);
}

float fnc_sample_shadow_map_pfc(sampler2D shadowMap, vec2 coords, vec2 texelSize, float compare)
{
    const float NUM_SAMPLES = 3.0f;
    const float SAMPLES_START = (NUM_SAMPLES - 1.0f) / 2.0f;
    const float NUM_SAMPLES_SQUARED = NUM_SAMPLES * NUM_SAMPLES;

    float result = 0.0f;
    for(float y = -SAMPLES_START; y <= SAMPLES_START; y += 1.0f)
    {
        for(float x = -SAMPLES_START; x <= SAMPLES_START; x += 1.0f)
        {
            vec2 coordsOffset = vec2(x, y) * texelSize;
            result += fnc_sample_show_map(shadowMap, coords + coordsOffset, compare);
            //result += fnc_sample_shadow_map_linear(shadowMap, coords + coordsOffset, texelSize, compare);
        }
    }

    return result / NUM_SAMPLES_SQUARED;
}

float fnc_shadow_directional_light(vec4 vertexLightSpace, vec3 normal, vec3 lightDir)
{
    vec3 projCoords = vertexLightSpace.xyz / vertexLightSpace.w;
    vec2 texelSize = 1.0 / textureSize(dirLightShadowMap, 0);
    projCoords = projCoords * 0.5 + 0.5;

    float bias = max(0.002 * (1.0 - dot(normal, lightDir)), 0.001);
    return 1.0f - fnc_sample_shadow_map_pfc(dirLightShadowMap, projCoords.xy, texelSize, projCoords.z - bias);
}

float fnc_shadow_point_light(samplerCube cubeMap, vec3 vertexPos, vec3 lightPos)
{
    vec3 gridSamplingDisk[20] = vec3[]
    (
       vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
       vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
       vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
       vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
       vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
    );

    vec3 lightToVertex = vertexPos - lightPos;
    float currentDepth = length(lightToVertex);

    float viewDistance = length(userViewPos - vertexPos);
    float diskRadius = (1.0 + (viewDistance / zFar)) / 25.0;

    float shadow = 0.0, bias = 0.15;
    int samples = 20;

    for(int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(cubeMap, lightToVertex + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= zFar;

        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }

    shadow /= float(samples);
    return shadow;
}

///////////////////////////////////////////////////////////////////////////////

vec3 light_point(vec3 texAmbient, vec3 texSpecular, vec3 texDiffuse)
{
    vec3 normal = normalize(fs_in.normal);
    vec3 accLight = vec3(0.0, 0.0, 0.0);

    if(material.hasBump)
    {
        normal = texture(material.bump, vec2(fs_in.uv.x, -fs_in.uv.y)).rgb;
        normal = normalize(fs_in.TBN * (normal * 2.0 - 1.0));
    }

    for(int i = 0; i < pointLight.counter; ++i)
    {
        vec3 lightDir = normalize(pointLight.lights[i].position - fs_in.vertex);
        float diff = max(dot(lightDir, normal), 0.0);

        float constant = pointLight.lights[i].constant;
        float linear = pointLight.lights[i].linear;
        float exp = pointLight.lights[i].exp;

        float att = fnc_get_atenuation(constant, linear, exp, pointLight.lights[i].position, fs_in.vertex);
        float spec = fnc_get_specular(userViewPos, fs_in.vertex, lightDir, normal);
        float shadow = 0;

        if(pointLight.lights[i].hasShadow)
        {
            shadow = fnc_shadow_point_light(pointLight.lights[i].shadowMap, fs_in.vertex, pointLight.lights[i].position);
        }

        vec3 ambient  = pointLight.lights[i].ambient  * material.ambientColor  * texAmbient;
        vec3 specular = pointLight.lights[i].specular * material.specularColor * texSpecular * spec;
        vec3 diffuse  = pointLight.lights[i].diffuse  * material.diffuseColor  * diff * att * (1 - shadow);

        accLight += texDiffuse * (ambient + diffuse + specular);
    }

    return accLight;
}

vec3 light_spot()
{
    vec3 lightDir = normalize(spotLight.position - fs_in.vertex);
    float theta = dot(lightDir, normalize(-spotLight.direction));

    if(theta > spotLight.cutOff)
    {
        float a = 0.01, b = 0.001;
        vec3 normal = normalize(fs_in.normal);

        vec3 lightDir = normalize(spotLight.position - fs_in.vertex);
        float diff = dot(lightDir, normal);

        vec3 l = spotLight.ambient + spotLight.diffuse + spotLight.specular;
        return l * max(diff, 0.0) ;
    }

    return vec3(0.0);
}

vec3 light_directional(vec3 texAmbient, vec3 texSpecular, vec3 texDiffuse)
{
    vec3 normal = normalize(fs_in.normal), lightDir = normalize(directionalLight.direction);
    float shadow = fnc_shadow_directional_light(fs_in.vertexLightSpace, normal, lightDir);

    if(material.hasBump)
    {
        normal = texture(material.bump, vec2(fs_in.uv.x, -fs_in.uv.y)).rgb;
        normal = normalize(fs_in.TBN * (normal * 2.0 - 1.0));
    }

    float diff = max(dot(lightDir, normal), 0.0);
    float spec = fnc_get_specular(userViewPos, fs_in.vertex, lightDir, normal);

    vec3 ambient  = directionalLight.ambient  * material.ambientColor  * texAmbient;
    vec3 diffuse  = directionalLight.diffuse  * material.diffuseColor  * diff * (1.0 - shadow);
    vec3 specular = directionalLight.specular * material.specularColor * texSpecular * spec;

    return texDiffuse * (ambient + diffuse + specular);
}

void main()
{
    vec2 uv = vec2(fs_in.uv.x, -fs_in.uv.y);

    vec4 diffuseColor  = texture(material.diffuseTexture , uv);
    vec4 ambientColor  = texture(material.ambientTexture , uv);
    vec4 specularColor = texture(material.specularTexture, uv);
    
    vec3 p = light_point(ambientColor.xyz, specularColor.xyz, diffuseColor.xyz);
    vec3 d = light_directional(ambientColor.xyz, specularColor.xyz, diffuseColor.xyz);

    vec3 l = pow((p + d), vec3(1.0/2.2));
    screenColor = vec4(l, diffuseColor.a);
}
