struct VertexShaderOutput
{
	float4 Position : SV_POSITION;
	float4 Color : color;
};

VertexShaderOutput vertexShader(float3 inPos : position, float4 inColor : color)
{
	VertexShaderOutput output;
	output.Position.xyz = inPos;
	output.Position.w = 1;
	output.Color = inColor;
	return output;
}