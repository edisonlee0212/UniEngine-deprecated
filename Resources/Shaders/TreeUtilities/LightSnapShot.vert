layout (location = 0) in vec3 aPos;
layout (location = 11) in uvec2 aLeafIndex;
layout (location = 12) in mat4 aInstanceMatrix;

uniform mat4 model;
uniform mat4 lightSpaceMatrix;

out VS_OUT {
    flat uint LeafIndex;
} vs_out;

void main()
{
    vs_out.LeafIndex = aLeafIndex.x;
    gl_Position = lightSpaceMatrix * (model * aInstanceMatrix) * vec4(aPos, 1.0);
}