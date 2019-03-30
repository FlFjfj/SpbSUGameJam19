#version 410 core

uniform mat4 u_ProjTrans;
uniform mat4 u_ViewTrans;
uniform mat4 u_ModelTrans;

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

out vec2 v_TexCoord;
out vec3 v_WorldCoord;
out vec3 v_Normal;

void main() {
  vec4 vert = u_ModelTrans * vec4(a_Position, 1.0);
  v_TexCoord   = a_TexCoord;
  v_WorldCoord = normalize(vert.xyz);
  v_Normal     = (u_ModelTrans * vec4(a_Normal, 0.0)).xyz;;
  gl_Position  = u_ProjTrans * u_ViewTrans * vert;
}