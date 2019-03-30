#version 410 core

uniform sampler2D texture0;

uniform int u_FrameCount;
uniform float u_FrameTime;
uniform float u_Time;

in vec2 v_TexCoord;

flat in int v_Frame;
flat in float v_Trans;

out vec4 frag_color;


float norm(float x) {
    return x - trunc(x);
}

void main() {
    vec4 color1 = texture2D(texture0, vec2(v_TexCoord.x, v_TexCoord.y + v_Frame / float(u_FrameCount)));

    frag_color = color1;
}
