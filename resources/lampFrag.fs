#version 440 core
out vec4 fragmentColor; // For outgoing lamp color (smaller cube) to the GPU

uniform vec4 color;

void main()
{
    fragmentColor = color; // Set color to white (1.0f,1.0f,1.0f) with alpha 1.0
}