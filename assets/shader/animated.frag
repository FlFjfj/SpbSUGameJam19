#version 410 core

uniform sampler2D texture0;

uniform vec3 u_FrameData;//time, length, count

in vec2 v_TexCoord;
in int v_frameIndex;

out vec4 frag_color;

void main() {
  float frameCount = u_FrameData.b;

  frag_color = texture(texture0, vec2(v_TexCoord.x, (v_TexCoord.y + v_frameIndex) / frameCount));
}