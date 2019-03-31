#version 410 core

uniform mat4 u_ProjTrans;
uniform mat4 u_ModelTrans;

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void main() {
  v_TexCoord   = a_TexCoord;
  gl_Position  = u_ProjTrans *  u_ModelTrans * vec4(a_Position, 1.0);
}