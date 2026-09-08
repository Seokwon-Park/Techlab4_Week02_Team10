cbuffer constants : register(b0)
{
    matrix MVP;
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
    float3 outlinePos = float3(1.1f, 1.1f, 1.1f) * input.position;
    
    // 1.1배 큰 메시를 그림
    output.position = mul(outlinePos, MVP);
    //output.position = float4(input.position, 1.0f);
    output.color = float4(1.0f, 0.0f, 0.0f, 1.0f);  // 빨간색으로 그림
    return output;
}

float4 mainPS(PS_INPUT input) : SV_TARGET
{
    return input.color;
}