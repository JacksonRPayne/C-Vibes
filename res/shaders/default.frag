#version 330 core
out vec4 FragColor;

uniform float time;
uniform sampler2D inputTexture;

in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  
in vec2 pos;
in vec2 texCoord;

void main()
{
    FragColor = texture(inputTexture, texCoord);
} 