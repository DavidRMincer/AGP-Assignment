
TextureCube texture0;
SamplerState sampler0;

cbuffer CBuffer0
{
	matrix WorldViewProjection;			// 64 bytes
										//TOTAL SIZE = 112 bytes
};

struct VOut
{
	float4 position : SV_POSITION;
	float4 color	: COLOR;	//Note the spelling of this and all instances below
	float3 texcoord	: TEXCOORD;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR,
	float3 texcoord : TEXCOORD, float3 normal : NORMAL)
{
	VOut output;

	output.position = mul(WorldViewProjection, position);
	output.texcoord = position.xyz;

	return output;
}

float4 PShader(float4 position : SV_POSITION, float4 color : COLOR,
	float3 texcoord : TEXCOORD) : SV_TARGET
{
	return color * texture0.Sample(sampler0, texcoord);
}
