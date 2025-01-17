layout (location = 0) out vec4 FragColor;
in VS_OUT {
	vec2 TexCoords;
} fs_in;

uniform sampler2D originalColor;
uniform sampler2D ao;
void main()
{
	
	vec3 result = texture(originalColor, fs_in.TexCoords).rgb * (1.0 - texture(ao, fs_in.TexCoords).r);
	FragColor = vec4(result, 1.0);
}