#version 330 core
in vec3 ourColor;
in vec2 texCoords;
uniform sampler2D text;
uniform sampler2D text2;
uniform float opacity;
out vec4 FragColor;

void main(){

  FragColor = mix( texture(text,vec2(texCoords.x,texCoords.y)), texture(text2,vec2(texCoords.x,texCoords.y)),opacity);
};