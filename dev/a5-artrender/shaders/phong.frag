#version 330

// CSci-4611 Assignment 5:  Art Render

// TODO: You need to calculate per-fragment shading here using the Phong shading
// model.


in vec3 Position;
in vec3 Normal;

out vec4 color;

uniform vec3 lightPosition;
uniform vec4 Ia, Id, Is;

uniform vec4 ka, kd, ks;
uniform float s;


void main() {
    color = vec4(0,0,0,1);
    vec3 n = normalize(Normal);
    vec3 sl = normalize(lightPosition - Position);
    vec3 e = normalize(-Position);
    vec3 h = normalize(sl + e);
    
     color.xyz += (ka*Ia).xyz;
    color.xyz += (kd*Id *
     dot(n, sl)).xyz;
     color.xyz += (ks*Is *pow(dot(n,h),s)).xyz;
    
    
    //vec4 amb = ka *Ia;
    // vec4 diffuse = kd*Id * max(dot(n,l),0);
    // vec4 sp = ks*Is*pow(max(dot(n,h),0),s);
    // color = amb + diffuse +sp;
    


}
