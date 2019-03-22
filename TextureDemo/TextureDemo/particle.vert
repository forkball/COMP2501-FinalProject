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

// Attributes forwarded to the fragment shader
out vec4 color_interp;


void main()
{
	vec4 ppos;
	float acttime;
	float speed = 9.0;
	acttime = mod(time + t*10.0, 2.0);
//	acttime = mod(time,4);
    ppos = vec4(vertex.x+dir.x*acttime*speed , vertex.y+dir.y*acttime*speed, 0.0, 1.0);
    gl_Position = x*ppos;
	
    color_interp = vec4(uv,0.5, 1.0);
	uv_interp = uv;
}