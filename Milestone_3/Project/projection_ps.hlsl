////////////////////////////////////////////////////////////////////////////////
// Filename: projection.ps
////////////////////////////////////////////////////////////////////////////////

//////////////
// TEXTURES //
//////////////
Texture2D shaderTexture : register(t0);
Texture2D projectionTexture : register(t1);
Texture2D shaderTexture2 : register(t2);

//////////////
// SAMPLERS //
//////////////
SamplerState SampleType;

//////////////////////
// CONSTANT BUFFERS //
//////////////////////
cbuffer LightBuffer
{
	float4 ambientColor;
    float4 diffuseColor;
    float3 lightDirection;
    float padding;
};

//////////////
// TYPEDEFS //
//////////////
struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
    float4 viewPosition : TEXCOORD1;
	float3 lightPos : TEXCOORD2;
};

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 ProjectionPixelShader(PixelInputType input) : SV_TARGET
{
	float brightness;
    float4 color;
	float lightIntensity;
    float4 textureColor;
    float4 textureColor2;
	float2 projectTexCoord;
	float4 projectionColor;
    float3 lightDir;

	// Set brightness of the light.
	brightness = 2.5f;
    lightDir = -lightDirection;

    // Calculate the amount of light on this pixel.
	//lightIntensity = saturate(dot(input.normal, input.lightPos));
    lightIntensity = saturate(dot(input.normal, lightDir));

    if(lightIntensity > 0.0f)
	{
		// Determine the light color based on the diffuse color and the amount of light intensity.
		color = (diffuseColor * lightIntensity) * brightness;
        color = saturate(color);
    }

	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = shaderTexture.Sample(SampleType, input.tex);
    textureColor2 = shaderTexture2.Sample(SampleType, input.tex);

    // Blend the two textures
    textureColor = saturate(textureColor * textureColor2 * 2.0f);

	// Calculate the projected texture coordinates.
	projectTexCoord.x =  input.viewPosition.x / input.viewPosition.w / 2.0f + 0.5f;
	projectTexCoord.y = -input.viewPosition.y / input.viewPosition.w / 2.0f + 0.5f;

	// Determine if the projected coordinates are in the 0 to 1 range.  If it is then this pixel is inside the projected view port.
	if((saturate(projectTexCoord.x) == projectTexCoord.x) && (saturate(projectTexCoord.y) == projectTexCoord.y))
	{
		// Sample the color value from the projection texture using the sampler at the projected texture coordinate location.
		projectionColor = projectionTexture.Sample(SampleType, projectTexCoord);

		// Set the output color of this pixel to the projection texture overriding the regular color value.
		color = saturate((color * projectionColor * textureColor) + (ambientColor * textureColor));
	}
	else
	{
        // If not, use the normal color
        color = saturate(ambientColor * textureColor);
    }

    return color;
}