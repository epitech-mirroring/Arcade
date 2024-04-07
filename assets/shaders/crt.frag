#version 120
uniform sampler2D texture;
#define res (vec2(224.0/1.0,288.0/1.0))

// Hardness of scanline.
//  -8.0 = soft
// -16.0 = medium
float hardScan=-10.0;

// Hardness of pixels in scanline.
// -2.0 = soft
// -4.0 = hard
float hardPix=-4.0;

// Display warp.
// 0.0 = none
// 1.0/8.0 = extreme
vec2 warp=vec2(1.0/42.0,1.0/32.0);

// Amount of shadow mask.
float maskDark=0.5;
float maskLight=10.0;

//------------------------------------------------------------------------

vec3 Fetch(vec2 pos,vec2 off) {
  pos = floor(pos*res+off)/res;
  if (max(abs(pos.x-0.5),abs(pos.y-0.5))>0.5)
    return vec3(0.0,0.0,0.0);
  return texture2D(texture,pos).rgb;
}

vec2 Dist(vec2 pos){
  pos=pos*res;return -((pos-floor(pos))-vec2(0.5));
}

// 1D Gaussian.
float Gaus(float pos,float scale){return exp2(scale*pos*pos);}

// 3-tap Gaussian filter along horz line.
vec3 Horz3(vec2 pos,float off){
  vec3 b=Fetch(pos,vec2(-1.0,off));
  vec3 c=Fetch(pos,vec2( 0.0,off));
  vec3 d=Fetch(pos,vec2( 1.0,off));
  float dst=Dist(pos).x;
  // Convert distance to weight.
  float scale=hardPix;
  float wb=Gaus(dst-1.0,scale);
  float wc=Gaus(dst+0.0,scale);
  float wd=Gaus(dst+1.0,scale);
  // Return filtered sample.
  return (b*wb+c*wc+d*wd)/(wb+wc+wd);}

// 5-tap Gaussian filter along horz line.
vec3 Horz5(vec2 pos,float off){
  vec3 a=Fetch(pos,vec2(-2.0,off));
  vec3 b=Fetch(pos,vec2(-1.0,off));
  vec3 c=Fetch(pos,vec2( 0.0,off));
  vec3 d=Fetch(pos,vec2( 1.0,off));
  vec3 e=Fetch(pos,vec2( 2.0,off));
  float dst=Dist(pos).x;
  // Convert distance to weight.
  float scale=hardPix;
  float wa=Gaus(dst-2.0,scale);
  float wb=Gaus(dst-1.0,scale);
  float wc=Gaus(dst+0.0,scale);
  float wd=Gaus(dst+1.0,scale);
  float we=Gaus(dst+2.0,scale);
  // Return filtered sample.
  return (a*wa+b*wb+c*wc+d*wd+e*we)/(wa+wb+wc+wd+we);}

// Return scanline weight.
float Scan(vec2 pos,float off){
  float dst=Dist(pos).y;
  return Gaus(dst+off,hardScan);}

// Allow nearest three lines to effect pixel.
vec3 Tri(vec2 pos){
  vec3 a=Horz3(pos,-1.0);
  vec3 b=Horz5(pos, 0.0);
  vec3 c=Horz3(pos, 1.0);
  float wa=Scan(pos,-1.0);
  float wb=Scan(pos, 0.0);
  float wc=Scan(pos, 1.0);
  return a*wa+b*wb+c*wc;}

// Distortion of scanlines, and end of screen alpha.
vec2 Warp(vec2 pos) {
  pos= pos*2.0 - 1.0;
  pos*= vec2(1.0+(pos.y*pos.y)*warp.x,1.0+(pos.x*pos.x)*warp.y);
  return pos*0.5+0.5;
}

// Shadow mask.
vec3 Mask(vec2 pos){
  vec2 off=fract(pos*res);
  vec3 mask=vec3(0.0,0.0,0.0);
  mask+=Fetch(pos,vec2(-1.0,-1.0))*maskDark;
  mask+=Fetch(pos,vec2( 0.0,-1.0))*maskDark;
  mask+=Fetch(pos,vec2( 1.0,-1.0))*maskDark;
  mask+=Fetch(pos,vec2(-1.0, 0.0))*maskDark;
  mask+=Fetch(pos,vec2( 0.0, 0.0))*maskLight;
  mask+=Fetch(pos,vec2( 1.0, 0.0))*maskDark;
  mask+=Fetch(pos,vec2(-1.0, 1.0))*maskDark;
  mask+=Fetch(pos,vec2( 0.0, 1.0))*maskDark;
  mask+=Fetch(pos,vec2( 1.0, 1.0))*maskDark;
  return mask/6.0;
}

// Entry.
void main() {
  vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
  vec2 pos = Warp(gl_TexCoord[0].xy);
  gl_FragColor = vec4(Tri(pos)*Mask(pos),pixel.a);
}

