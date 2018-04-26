#version 330

// CSci-4611 Assignment 5:  Art Render

// TODO: You need to calculate per-fragment shading here using a toon shading model

in vec3 Position;
in vec3 Normal;

out vec4 color;

uniform vec3 lightPosition;
uniform vec4 Ia, Id, Is;

uniform vec4 ka, kd, ks;
uniform float s;
uniform sampler2D diffuseRamp;
uniform sampler2D specularRamp;


void main() {
 
    color = vec4(0,0,0,1);
    vec3 n = normalize(Normal);
    vec3 sl = normalize(lightPosition - Position);
    vec3 e = normalize(-Position);
    vec3 h = normalize(sl + e);
    
    color = (ka*Ia);
    color += (kd*Id *
    texture(diffuseRamp, vec2(max(0.5 * dot(n, sl) + 0.5, 0), 0)));
    color += (ks*Is *texture(specularRamp, vec2(pow(max(dot(n,h), 0), s), 0)));
    
    
}
