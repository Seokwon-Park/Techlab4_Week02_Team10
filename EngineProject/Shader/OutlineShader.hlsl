cbuffer constants : register(b0)
{
    matrix MVP;
    float4 scale;
};

struct VS_INPUT
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

PS_INPUT mainVS(VS_INPUT input)
{
    PS_INPUT output;
    float3 localPos = input.position;
    
    float3 dir = sign(localPos);
    float3 thickness = 0.025f;
    
    float3 adjustThickness = dir * (thickness / scale.xyz);
    
    float3 outlinePos = localPos + adjustThickness;
    
    output.position = mul(float4(outlinePos, 1.0f), MVP);
    output.color = float4(1.0f, 0.5f, 0.0f, 1.0f);
    return output;
}

float4 mainPS(PS_INPUT input) : SV_TARGET
{
    return input.color;
}