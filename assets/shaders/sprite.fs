#version 330 core
//The fragment shader operates on each pixel in a given polygon

in vec3 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

//This is the 3 component float vector that gets outputted to
//the screen for each pixel

out vec4 color;

uniform sampler2D mySampler; // Texture sampler uniform
uniform float TIME; // Speed of scrolling

const vec4 movingColorArray[4] = 
{
	vec4(1.0f, float(152.0f / 255.0f), 0.0f, 1.0f),
	vec4(float(252.0f / 255.0f), float(106.0f / 255.0f), 0.0f, 1.0f),
	vec4(float(252.0f / 255.0f), float(95.0f / 255.0f), 0.0f, 1.0f),
	vec4(float(252.0f / 255.0f), float(72.0f / 255.0f), 0.0f, 1.0f)
}
;

void main()
{
	vec4 textureColor = texture(mySampler, fragmentUV);
	for (int i = 0; i<4; i++)
	{
		if (length(textureColor - movingColorArray[i]) < 0.1)
		{
			vec2 newUVCoord = vec2(fragmentUV.x + TIME, fragmentUV.y + TIME);
			textureColor = texture(mySampler,newUVCoord);
		}
	}

	color = textureColor * fragmentColor;


}