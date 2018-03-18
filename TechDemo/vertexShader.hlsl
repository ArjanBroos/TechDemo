struct VertexShaderOutput
{
	float4 Position : SV_POSITION;
	float4 Color : color;
};

VertexShaderOutput vertexShader(float4 inPos : position, float4 inColor : color)
{
	VertexShaderOutput output;
	output.Position = inPos;
	output.Color = inColor;
	return output;
}