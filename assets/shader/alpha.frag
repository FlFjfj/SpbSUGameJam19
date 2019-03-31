#version 410 core

uniform sampler2D texture0;
uniform float u_alpha;

in vec2 v_TexCoord;

out vec4 frag_color;

void main() {
  frag_color = texture(texture0, v_TexCoord) * vec4(vec3(1), u_alpha);
}