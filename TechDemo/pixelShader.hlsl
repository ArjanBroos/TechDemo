struct VertexShaderOutput
{
	float4 Position : SV_POSITION;
	float4 Color : color;
};

float4 pixelShader(VertexShaderOutput input) : SV_TARGET
{
	return input.Color;
}