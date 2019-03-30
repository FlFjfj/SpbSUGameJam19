#version 410 core

uniform sampler2D texture0;

in vec2 v_TexCoord;
in vec3 v_WorldCoord;
in vec3 v_Normal;

out vec4 frag_color;

const vec3 light_pos = vec3(0.0, 0.0, 0.0); 

void main() {
  vec4 tex_color = texture(texture0, v_TexCoord);
  frag_color     = vec4(tex_color.xyz * (0.3 + 0.7 * abs(dot(normalize(light_pos - v_WorldCoord), v_Normal))), tex_color.a);
}