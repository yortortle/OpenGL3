#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;
out vec3 LightPos;

uniform vec3 lightPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    //world space from multiplying vertex position and model matrix
    FragPos = vec3(view * model * vec4(aPos, 1.0));

    //transpose and inverse to the get the normal matrix of model
    //normalizing the Normal vec3 because fragment shader acts in world space
    Normal = mat3(transpose(inverse(view * model))) * aNormal;

    // Transform world-space light position to view-space light position
    LightPos = vec3(view * vec4(lightPos, 1.0));
}