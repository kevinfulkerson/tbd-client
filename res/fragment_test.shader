#version 330 core
uniform float time;

vec3 colorA = vec3(1.0, 1.0, 1.0);
vec3 colorB = vec3(1.0, 0.0, 1.0);

void main(){
  float pct = abs(sin(time));

  vec3 color = mix(colorA, colorB, pct);

  gl_FragColor = vec4(color, 1.0);
}