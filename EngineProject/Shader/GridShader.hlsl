cbuffer GridCB : register(b0)
{
    float4x4 ViewProj;
    float3 CameraPos;
    float Padding;
};

static const float GridSize = 200.0f; // 충분히 크게 (카메라 시야 밖까지 덮도록)
static const float4 Positions[4] =
{
    float4(-0.5, 0.5, 0.0, 1.0), // z를 0으로, xy를 평면으로
    float4(0.5, 0.5, 0.0, 1.0),
    float4(-0.5, -0.5, 0.0, 1.0),
    float4(0.5, -0.5, 0.0, 1.0)
};

struct VSOut
{
    float4 pos : SV_POSITION;
    float2 coords : TEXCOORD0; // world space xz
    float3 camPos : TEXCOORD1;
};

VSOut mainVS(uint vid : SV_VertexID)
{
    VSOut o;
    float4 worldPos = Positions[vid];
    worldPos.xyz *= GridSize;
    worldPos.xy += CameraPos.xy; 

    o.pos = mul(worldPos, ViewProj);
    o.coords = worldPos.xy; 
    o.camPos = CameraPos;
    return o;
}

#define MOD(x,y) ((x) - (y) * floor((x)/(y))) 

static const float CellSize = 1.0f;
static const float SubCellSize = 0.1f;
static const float4 CellColor = float4(0.75, 0.75, 0.75, 0.6);
static const float4 SubCellColor = float4(0.5, 0.5, 0.5, 0.35);

static const float HeightToFadeRatio = 25.0f;
static const float MinFadeDistance = 5.0f;
static const float MaxFadeDistance = 150.0f;

struct PSIn
{
    float4 pos : SV_POSITION;
    float2 coords : TEXCOORD0;
    float3 camPos : TEXCOORD1;
};

float4 mainPS(PSIn input) : SV_TARGET
{
    float2 cellCoords = MOD(input.coords + CellSize * 0.5, CellSize);
    float2 subCellCoords = MOD(input.coords + SubCellSize * 0.5, SubCellSize);

    float2 distToCell = abs(cellCoords - CellSize * 0.5);
    float2 distToSubCell = abs(subCellCoords - SubCellSize * 0.5);

    float2 d = fwidth(input.coords); // 카메라 거리에 따라 라인 두께 자동 보정
    float2 cellLineWidth = 0.5 * (0.02 + d);
    float2 subCellLineWidth = 0.5 * (0.01 + d);

    float4 color = float4(0, 0, 0, 0);
    if (any(distToSubCell < subCellLineWidth))
        color = SubCellColor;
    if (any(distToCell < cellLineWidth))
        color = CellColor;

    float distToCamera = length(input.coords - input.camPos.xy);
    float fadeDist = clamp(abs(input.camPos.z) * HeightToFadeRatio, MinFadeDistance, MaxFadeDistance);
    float falloff = smoothstep(1.0, 0.0, distToCamera / fadeDist);

    color.a *= falloff;
    if (color.a < 0.01)
        discard;
    return color;
}