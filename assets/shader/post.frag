#version 410 core

uniform sampler2D texture0;

in vec2 v_TexCoord;
in vec2  one;
in float mod_factor;

out vec4 frag_color;

const vec4 sourceSize = vec4(1280, 720, 0, 0);

#define distortion 0.08
#define inputGamma  2.4
#define outputGamma 2.2
#define TEX2D(c) pow(texture2D(texture0, vec2((c).x, 1.0 - (c).y)), vec4(inputGamma))
#define PI 3.141592653589

vec2 radialDistortion(vec2 coord){
    vec2 cc = coord - 0.5;
    float dist = dot(cc, cc) * distortion;
    return (coord + cc * (1.0 + dist) * dist);
}

vec4 scanlineWeights(float distance, vec4 color){
    vec4 wid = 6.0 + 2.0 * pow(color, vec4(4.0));
    vec4 weights = vec4(distance / 0.3);
    return 1.4 * exp(-pow(weights * inversesqrt(0.5 * wid), wid)) / (0.6 + 0.2 * wid);
}


void main() {
  vec2 xy = radialDistortion(v_TexCoord);
  vec2 ratio_scale = xy * sourceSize.xy - vec2(0.5);
  vec2 uv_ratio = fract(ratio_scale);

   xy.y = (floor(ratio_scale.y) + 0.5) / sourceSize.y;
   vec4 col  = TEX2D(xy);
   vec4 col2 = TEX2D(xy + vec2(0.0, one.y));

   vec4 weights  = scanlineWeights(uv_ratio.y, col);
   vec4 weights2 = scanlineWeights(1.0 - uv_ratio.y, col2);
   vec3 mul_res  = (col * weights + col2 * weights2).rgb;

   vec3 dotMaskWeights = mix(
           vec3(1.0, 0.7, 1.0),
           vec3(0.7, 1.0, 0.7),
           floor(mod(mod_factor, 2.0))
       );

    mul_res *= dotMaskWeights;

    frag_color = vec4(pow(mul_res, vec3(1.0 / outputGamma)), 1.0);
}