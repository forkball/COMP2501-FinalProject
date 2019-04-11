// Source code of vertex shader
#version 130

// Vertex buffer
in vec2 vertex;
in vec3 color;
in vec2 uv;

// Uniform (global) buffer
uniform mat4 transformationMatrix;
uniform float UVSize;
uniform int charCol;
uniform int charRow;

// Attributes forwarded to the fragment shader
out vec2 uv_interp;

void main()
{
    gl_Position = transformationMatrix * vec4(vertex, 0.0, 1.0);
	
	uv_interp = vec2(uv.x * UVSize + (charCol * UVSize), uv.y * UVSize + (charRow * UVSize));
}