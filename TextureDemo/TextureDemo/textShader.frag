// Source code of fragment shader
#version 130

// Attributes passed from the vertex shader
in vec2 uv_interp;

out vec4 FragColor;

uniform sampler2D textSpritesheet;
uniform vec3 textColour;

void main()
{
	vec3 textureColour = texture2D(textSpritesheet, uv_interp).rgb;

	if (textureColour.r < 0.1 && textureColour.g < 0.1 && textureColour.b < 0.1) {
		discard;
	}

	FragColor = vec4(textureColour * textColour, 1.0);
}