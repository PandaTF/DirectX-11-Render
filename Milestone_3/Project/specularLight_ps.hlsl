////////////////////////////////////////////////////////////////////////////////
// Filename: light.ps
////////////////////////////////////////////////////////////////////////////////

/////////////
// DEFINES //
/////////////
#define NUM_LIGHTS 4

/////////////
// GLOBALS //
/////////////
Texture2D shaderTexture;
SamplerState SampleType;

cbuffer LightBuffer
{
    float4 ambientColor;
    float4 diffuseColor;
    float3 lightDirection;
    float specularPower;
    float4 specularColor;
};

cbuffer LightColorBuffer
{
    float4 pointLightColor[NUM_LIGHTS];
};

//////////////
// TYPEDEFS //
//////////////
struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 viewDirection : TEXCOORD1;
    float3 lightPos1 : TEXCOORD2;
    float3 lightPos2 : TEXCOORD3;
    float3 lightPos3 : TEXCOORD4;
    float3 lightPos4 : TEXCOORD5;
    float4 PLParameter1 : TEXCOOR6;
    float4 PLParameter2 : TEXCOOR7;
    float4 PLParameter3 : TEXCOOR8;
    float4 PLParameter4 : TEXCOOR9;
};

float PointLightAttenuation(float intensity, float distance, float maxDistance)
{
    if (distance > maxDistance)
    {
        intensity *= (1.0f - (distance - maxDistance) / maxDistance);
    }

    return intensity;
}
////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 LightPixelShader(PixelInputType input) : SV_TARGET
{
    float4 textureColor;
    float3 lightDir;
    float lightIntensity;
    float4 color;
    float3 reflection;
    float4 specular;

    float lightIntensity1, lightIntensity2, lightIntensity3, lightIntensity4;
    float4 color1, color2, color3, color4;

    // Calculate the different amounts of light on this pixel based on the positions of the lights.
    lightIntensity1 = saturate(dot(input.normal, input.lightPos1));
    lightIntensity2 = saturate(dot(input.normal, input.lightPos2));
    lightIntensity3 = saturate(dot(input.normal, input.lightPos3));
    lightIntensity4 = saturate(dot(input.normal, input.lightPos4));
    
    lightIntensity1 = PointLightAttenuation(lightIntensity1, input.PLParameter1.x, 30.0f);
    lightIntensity2 = PointLightAttenuation(lightIntensity2, input.PLParameter2.x, 30.0f);
    lightIntensity3 = PointLightAttenuation(lightIntensity3, input.PLParameter3.x, 30.0f);
    lightIntensity4 = PointLightAttenuation(lightIntensity4, input.PLParameter4.x, 30.0f);

    // Determine the diffuse color amount of each of the four lights.
    color1 = pointLightColor[0] * lightIntensity1;
    color2 = pointLightColor[1] * lightIntensity2;
    color3 = pointLightColor[2] * lightIntensity3;
    color4 = pointLightColor[3] * lightIntensity4;
    
	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
    textureColor = shaderTexture.Sample(SampleType, input.tex);

	// Set the default output color to the ambient light value for all pixels.
    color = saturate(color1 + color2 + color3 + color4 + ambientColor);

	// Initialize the specular color.
    specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// Invert the light direction for calculations.
    lightDir = -lightDirection;

    // Calculate the amount of light on this pixel.
    lightIntensity = saturate(dot(input.normal, lightDir));

    if (lightIntensity > 0.0f)
    {
        // Determine the final diffuse color based on the diffuse color and the amount of light intensity.
        color += (diffuseColor * lightIntensity);

	    // Saturate the ambient and diffuse color.
        color = saturate(color);

		// Calculate the reflection vector based on the light intensity, normal vector, and light direction.
        reflection = normalize(2 * lightIntensity * input.normal - lightDir);

		// Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
        specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower);
    }

    // Multiply the texture pixel and the input color to get the textured result.
    color = color * textureColor;

	// Add the specular component last to the output color.
    color = saturate(color + specular);

    return color;
}