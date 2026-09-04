struct VS_INPUT
{
	float4 position : POSITION;
	float scale : SCALE;
	float3 color : COLOR; 
};

struct PS_INPUT
{
	float4 position : POSITION;
	float scale : SCALE;
	float3 color : COLOR;
};

PS_INPUT mainVS(VS_INPUT input)
{
	PS_INPUT output;
	float3 newPosition = input.position * input.scale;
	float4 position = float4(newPosition, 1.0f);
	output.position = position;
	output.color = input.color;
	return output;
}

float4 mainPS(PS_INPUT input) : SV_TARGET
{
	return input.color;
}