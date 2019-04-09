#version 130

// Vertex buffer
in vec2 vertex;
in vec2 dir;
in float t;
in vec2 uv;
out vec2 uv_interp;

// Uniform (global) buffer
uniform mat4 x;
uniform float time;
uniform mat4 viewMatrix;
uniform float pSpeed;

// Attributes forwarded to the fragment shader
out vec4 color_interp;
out float curr_time;

void main()
{
	vec4 ppos;
	float acttime;
	float speed = pSpeed;
	acttime = mod(time + t*10.0, 2.0);
    ppos = vec4(vertex.x+dir.x*acttime*speed , vertex.y+dir.y*acttime*speed, 0.0, 1.0);
	vec4 vertexPos = vec4(vertex, 0.0, 1.0);
    gl_Position = viewMatrix * x * ppos;

	uv_interp = uv;
	curr_time = time + t;
}