// Source code of fragment shader
#version 130

// Attributes passed from the vertex shader
in vec4 color_interp;
in vec2 uv_interp;
in float curr_time;

out vec4 FragColor;

uniform sampler2D onetex;

void main()
{
	vec4 color = texture2D(onetex, uv_interp);
	color = vec4(color.r,color.g,color.b,color.a);
	vec4 color2 = color * vec4(0,0,0.5,1.0);

	float a = curr_time - int(curr_time);
	FragColor = mix(color, color2, a * 1.5);

    if((color.r + color.g + color.b) / 3.0 > 0.95)
	{
		discard;
	}
}