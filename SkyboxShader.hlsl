#include"ConstantBuffers.hlsli"

SamplerState ss : register(s0);
TextureCube cubeMap : register(t0);

struct VertexInput
{
    float4 mPosition : POSITION0;
    float3 mNormal : NORMAL0;
    float2 mTexcoord : TEXCOORD0;
};

struct PixelInput
{
    float4 mPosition : SV_Position;
    float4 mLocalPosition : POSITION0;
    float4 mNormal : TEXCOORD0;
    float2 mTexcoord : TEXCOORD1;
};

PixelInput SkyVS(VertexInput input)
{
    PixelInput output = (PixelInput) 0;
    
    input.mPosition.w = 1.0f;
    
    
    float4 world = mul(input.mPosition, gWorld);
    float4 view = mul(world, gView);
    float4 projection = mul(view, gProjection);
    
    
    float4 normal = float4(mul(input.mNormal, (float3x3) gWorld), 1.0f);
    
    float2 uv = input.mTexcoord;
    
    output.mPosition = projection;
    output.mNormal = normal;
    output.mTexcoord = uv;
    output.mLocalPosition = input.mPosition;
    
    return output;
}

float4 SkyPS(PixelInput input) : SV_Target0
{
    float4 position = input.mPosition;
    float4 normal = input.mNormal;
    float2 uv = input.mTexcoord;

    float4 cube = cubeMap.Sample(ss, input.mLocalPosition.xyz);
    
    return cube;

}