#version 330 core
layout (location = 0) in vec2 aPos; // the position variable has attribute position 0
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec2 texCoordOffset;

out vec2 pos;
out vec2 texCoord;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 0.0, 1.0); // see how we directly give a vec3 to vec4's constructor
    pos = aPos;
    texCoord = aTexCoord + texCoordOffset;
}