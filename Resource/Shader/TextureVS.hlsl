float4x4 WorldMatrix;
float4x4 ViewMatrix;
float4x4 ProjectionMatrix;

struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
};


struct PixelInputType
{
	float4 position : SV_POSITION;
    	float2 tex : TEXCOORD0;
};

PixelInputType VShader(VertexInputType input)
{
	PixelInputType output;
    

	// Change the position vector to be 4 units for proper matrix calculations.
    	input.position.w = 1.0f;

    	output.position = mul(input.position, worldMatrix);
    	output.position = mul(output.position, viewMatrix);
    	output.position = mul(output.position, projectionMatrix);

    	// Store the texture coordinates for the pixel shader.
    	output.tex = input.tex;
    
    	return output;
}

technique FirstTechnique
{
	pass FirstPass
	{
		Lighting = FALSE;
		ZEnable = TRUE;

		VertexShader = compile vs_2_0 VShader();
	}
}