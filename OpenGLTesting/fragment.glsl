#version 400
in vec3 fCol;
out vec4 FragColor;
void main()
{
	FragColor = vec4(fCol, 1.0);
}