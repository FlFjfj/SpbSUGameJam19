#version 410 core

uniform mat4 u_ProjTrans;
uniform mat4 u_ModelTrans;

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

out vec2 v_TexCoord;
out vec2 one;
out float mod_factor;

const vec4 sourceSize = vec4(1280, 720, 0, 0);
const vec2 aspect_ratio = vec2(720. / 1280., 1.0);

void main() {
  v_TexCoord   = a_TexCoord;
  mod_factor   =  a_TexCoord.x * aspect_ratio.x;
  one = 1.0 / sourceSize.xy;
  gl_Position  = u_ProjTrans *  u_ModelTrans * vec4(a_Position, 1.0);
}