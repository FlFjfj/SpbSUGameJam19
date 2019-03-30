#version 410 core

uniform mat4 u_ProjTrans;
uniform mat4 u_ModelTrans;

uniform vec3 u_FrameData;//time, length, count

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

out vec2 v_TexCoord;
out int v_frameIndex;

void main() {

float time = u_FrameData.r;
float frame_len = u_FrameData.g;
float frame_count = u_FrameData.b;

  v_frameIndex = int(time / frame_len) % int(frame_count);

  v_TexCoord  = a_TexCoord;
  gl_Position = u_ProjTrans * u_ModelTrans * vec4(a_Position, 1.0);
}