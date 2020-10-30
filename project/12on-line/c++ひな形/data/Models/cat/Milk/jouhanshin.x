xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 166;
 75.52797;18.03004;-144.31543;,
 85.87236;28.66584;-190.36815;,
 67.22639;50.60391;-170.54568;,
 63.21588;44.12632;-131.70354;,
 19.23446;87.31520;-119.06747;,
 22.07310;93.76059;-165.18802;,
 -3.94303;100.72384;-161.46899;,
 -3.94303;99.03411;-115.76411;,
 48.47752;75.21696;-181.52448;,
 44.30650;70.03577;-124.10789;,
 -3.94303;103.27170;-73.83614;,
 22.64311;91.56216;-77.05425;,
 48.05745;66.09099;-78.91163;,
 67.83861;27.06368;-85.99752;,
 -3.94303;104.68241;-26.87664;,
 22.64311;92.96350;-30.19751;,
 46.14260;65.42207;-31.39094;,
 63.83790;28.83419;-35.40635;,
 38.56286;-89.26057;-183.42120;,
 17.30995;-108.61739;-183.42120;,
 21.61075;-108.68893;-206.75502;,
 47.16446;-89.33211;-206.75502;,
 46.81453;-86.34696;-160.08748;,
 21.43575;-105.70385;-160.08748;,
 -3.94303;-120.30620;-206.75502;,
 -3.94303;-120.23585;-183.42120;,
 -3.94303;-117.32231;-160.08748;,
 24.31576;-76.94351;-137.56757;,
 -3.94303;-82.71648;-137.56757;,
 -3.94303;-82.84135;-36.01780;,
 -3.94303;-86.02237;-91.35400;,
 27.04289;-81.62202;-91.35400;,
 27.98019;-79.81302;-36.01780;,
 67.90504;-30.16559;-111.92580;,
 70.49567;-24.85007;-77.28287;,
 67.61377;-51.60050;-78.15682;,
 64.25503;-53.33776;-115.48405;,
 70.36785;-24.06054;-37.69248;,
 70.42357;-50.96196;-40.26736;,
 52.06313;-67.55532;-146.00761;,
 62.99671;-39.26650;-144.74097;,
 71.68476;5.07241;-113.18153;,
 50.85192;-66.96088;-83.38757;,
 47.63934;-65.66203;-124.27086;,
 52.36686;-65.79118;-38.84321;,
 50.17712;19.14311;-249.60382;,
 76.14320;8.48309;-235.54474;,
 70.44954;-38.22028;-240.76779;,
 50.06267;-38.22028;-256.03781;,
 24.34075;-38.22028;-267.14352;,
 -3.94303;-38.22028;-273.80283;,
 -3.94303;-0.63469;-277.15442;,
 25.08387;5.15207;-267.81735;,
 -3.94303;-76.41026;-260.11020;,
 22.07023;-70.06979;-254.77879;,
 -3.94303;-103.71304;-235.75146;,
 20.33892;-93.16377;-234.51212;,
 44.55073;-70.08596;-242.68643;,
 67.58109;-86.52000;-216.42006;,
 37.78908;-84.92491;-230.28445;,
 60.88866;51.12184;-216.70123;,
 -83.41396;18.03004;-144.31543;,
 -71.10194;44.12632;-131.70354;,
 -75.11238;50.60391;-170.54568;,
 -93.75828;28.66584;-190.36815;,
 -27.12045;87.31520;-119.06747;,
 -29.95909;93.76059;-165.18802;,
 -52.19249;70.03577;-124.10789;,
 -56.36351;75.21696;-181.52448;,
 -30.52917;91.56216;-77.05425;,
 -75.72474;27.06368;-85.99752;,
 -55.94351;66.09099;-78.91163;,
 -30.52917;92.96350;-30.19751;,
 -54.02859;65.42207;-31.39094;,
 -71.72388;28.83419;-35.40635;,
 -46.44885;-89.26057;-183.42120;,
 -55.05045;-89.33211;-206.75502;,
 -29.49674;-108.68893;-206.75502;,
 -25.19594;-108.61739;-183.42120;,
 -29.32174;-105.70385;-160.08748;,
 -54.70052;-86.34696;-160.08748;,
 -3.94303;-120.30620;-206.75502;,
 -3.94303;-120.23585;-183.42120;,
 -3.94303;-117.32231;-160.08748;,
 -3.94303;-82.71648;-137.56757;,
 -32.20175;-76.94351;-137.56757;,
 -3.94303;-82.84135;-36.01780;,
 -35.86611;-79.81302;-36.01780;,
 -34.92888;-81.62202;-91.35400;,
 -3.94303;-86.02237;-91.35400;,
 -75.79096;-30.16559;-111.92580;,
 -72.14109;-53.33776;-115.48405;,
 -75.49976;-51.60050;-78.15682;,
 -78.38166;-24.85007;-77.28287;,
 -78.30956;-50.96196;-40.26736;,
 -78.25377;-24.06054;-37.69248;,
 -70.88270;-39.26650;-144.74097;,
 -59.94912;-67.55532;-146.00761;,
 -79.57082;5.07241;-113.18153;,
 -55.52533;-65.66203;-124.27086;,
 -58.73791;-66.96088;-83.38757;,
 -60.25285;-65.79118;-38.84321;,
 -58.06311;19.14311;-249.60382;,
 -57.94873;-38.22028;-256.03781;,
 -78.33553;-38.22028;-240.76779;,
 -84.02919;8.48309;-235.54474;,
 -32.22674;-38.22028;-267.14352;,
 -32.96986;5.15207;-267.81735;,
 -3.94303;-0.63469;-277.15442;,
 -3.94303;-38.22028;-273.80283;,
 -3.94303;-76.41026;-260.11020;,
 -29.95622;-70.06979;-254.77879;,
 -28.22498;-93.16377;-234.51212;,
 -3.94303;-103.71304;-235.75146;,
 -52.43679;-70.08596;-242.68643;,
 -75.46707;-86.52000;-216.42006;,
 -45.67507;-84.92491;-230.28445;,
 -68.77458;51.12184;-216.70123;,
 43.47672;68.08298;-227.82864;,
 35.64197;44.69283;-251.89452;,
 34.39884;85.70688;-202.09930;,
 17.28804;34.45932;-265.21649;,
 15.08591;99.27022;-190.15038;,
 -3.94303;30.22677;-272.04584;,
 -3.94303;104.36335;-187.43018;,
 -25.17410;34.45932;-265.21649;,
 -22.97190;99.27022;-190.15038;,
 -42.28490;85.70688;-202.09930;,
 -43.52803;44.69283;-251.89452;,
 -51.36271;68.08298;-227.82864;,
 82.81203;-3.43462;-222.34164;,
 89.55408;10.55145;-191.03546;,
 78.86649;-35.79877;-225.96098;,
 76.87868;-69.26899;-209.08867;,
 82.38573;3.18115;-159.12225;,
 62.73050;-71.21772;-202.39107;,
 56.76993;-71.16816;-186.22142;,
 73.70188;-36.52369;-159.41708;,
 62.48809;-69.14915;-170.05183;,
 66.12522;-56.12712;-160.29489;,
 -74.01128;-56.12712;-160.29489;,
 -81.58794;-36.52369;-159.41708;,
 -70.37415;-69.14915;-170.05183;,
 -64.65599;-71.16816;-186.22142;,
 -90.27165;3.18115;-159.12225;,
 -70.61663;-71.21772;-202.39107;,
 -97.43999;10.55145;-191.03546;,
 -84.76475;-69.26899;-209.08867;,
 -86.75253;-35.79877;-225.96098;,
 -90.69802;-3.43462;-222.34164;,
 51.07396;-34.86063;-2.02769;,
 51.03273;-14.95872;-0.12278;,
 37.71551;-45.83138;-0.97412;,
 46.20182;24.17317;1.56849;,
 33.11070;51.24119;4.53915;,
 19.67399;-56.20489;1.11615;,
 15.72564;71.61658;5.42206;,
 -3.94303;-58.44524;1.11615;,
 -3.94303;80.28629;7.87892;,
 -23.61163;71.61658;5.42206;,
 -27.55998;-56.20489;1.11615;,
 -40.99669;51.24119;4.53915;,
 -45.60143;-45.83138;-0.97412;,
 -54.08781;24.17317;1.56849;,
 -58.95995;-34.86063;-2.02769;,
 -58.91872;-14.95872;-0.12278;;
 
 174;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;3,2,8,9;,
 4;9,8,5,4;,
 4;7,10,11,4;,
 4;9,12,13,3;,
 4;12,9,4,11;,
 4;11,10,14,15;,
 4;16,17,13,12;,
 4;15,16,12,11;,
 4;18,19,20,21;,
 4;18,22,23,19;,
 4;24,20,19,25;,
 4;19,23,26,25;,
 4;26,23,27,28;,
 4;29,30,31,32;,
 4;28,27,31,30;,
 4;33,34,35,36;,
 4;34,37,38,35;,
 4;36,39,40,33;,
 4;34,13,17,37;,
 4;40,0,41,33;,
 4;3,13,41,0;,
 4;34,33,41,13;,
 4;36,35,42,43;,
 4;35,38,44,42;,
 4;43,42,31,27;,
 4;42,44,32,31;,
 4;39,36,43,22;,
 4;27,23,22,43;,
 4;45,46,47,48;,
 4;49,50,51,52;,
 4;48,49,52,45;,
 4;53,50,49,54;,
 4;20,24,55,56;,
 4;56,55,53,54;,
 4;57,48,47,58;,
 4;21,59,57,58;,
 4;21,20,56,59;,
 4;59,56,54,57;,
 4;54,49,48,57;,
 4;2,1,60,8;,
 4;46,45,60,1;,
 4;61,62,63,64;,
 4;65,7,6,66;,
 4;62,67,68,63;,
 4;67,65,66,68;,
 4;7,65,69,10;,
 4;67,62,70,71;,
 4;71,69,65,67;,
 4;69,72,14,10;,
 4;73,71,70,74;,
 4;72,69,71,73;,
 4;75,76,77,78;,
 4;75,78,79,80;,
 4;81,82,78,77;,
 4;78,82,83,79;,
 4;83,84,85,79;,
 4;86,87,88,89;,
 4;84,89,88,85;,
 4;90,91,92,93;,
 4;93,92,94,95;,
 4;91,90,96,97;,
 4;93,95,74,70;,
 4;96,90,98,61;,
 4;62,61,98,70;,
 4;93,70,98,90;,
 4;91,99,100,92;,
 4;92,100,101,94;,
 4;99,85,88,100;,
 4;100,88,87,101;,
 4;97,80,99,91;,
 4;85,99,80,79;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;103,102,107,106;,
 4;110,111,106,109;,
 4;77,112,113,81;,
 4;112,111,110,113;,
 4;114,115,104,103;,
 4;76,115,114,116;,
 4;76,116,112,77;,
 4;116,114,111,112;,
 4;111,114,103,106;,
 4;63,68,117,64;,
 4;105,64,117,102;,
 3;118,119,120;,
 3;119,121,120;,
 3;120,121,122;,
 3;121,123,122;,
 3;122,123,124;,
 3;123,125,124;,
 3;124,125,126;,
 3;126,125,127;,
 3;125,128,127;,
 3;128,129,127;,
 4;6,5,122,124;,
 4;5,8,120,122;,
 4;8,60,118,120;,
 4;60,45,119,118;,
 4;45,52,121,119;,
 4;52,108,123,121;,
 4;108,107,125,123;,
 4;107,102,128,125;,
 4;102,117,129,128;,
 4;117,68,127,129;,
 4;68,66,126,127;,
 4;66,6,124,126;,
 3;130,131,132;,
 3;132,131,133;,
 3;131,134,133;,
 3;133,134,135;,
 3;135,134,136;,
 3;134,137,136;,
 3;136,137,138;,
 3;137,139,138;,
 3;140,141,142;,
 3;142,141,143;,
 3;141,144,143;,
 3;143,144,145;,
 3;144,146,145;,
 3;145,146,147;,
 3;147,146,148;,
 3;146,149,148;,
 4;21,58,133,135;,
 4;58,47,132,133;,
 4;47,46,130,132;,
 4;46,1,131,130;,
 4;1,0,134,131;,
 4;0,40,137,134;,
 4;40,39,139,137;,
 4;39,22,138,139;,
 4;22,18,136,138;,
 4;18,21,135,136;,
 4;75,80,142,143;,
 4;80,97,140,142;,
 4;97,96,141,140;,
 4;96,61,144,141;,
 4;61,64,146,144;,
 4;64,105,149,146;,
 4;105,104,148,149;,
 4;104,115,147,148;,
 4;115,76,145,147;,
 4;76,75,143,145;,
 3;150,151,152;,
 3;151,153,152;,
 3;153,154,152;,
 3;152,154,155;,
 3;154,156,155;,
 3;155,156,157;,
 3;156,158,157;,
 3;158,159,157;,
 3;157,159,160;,
 3;159,161,160;,
 3;160,161,162;,
 3;161,163,162;,
 3;162,163,164;,
 3;163,165,164;,
 4;14,72,159,158;,
 4;72,73,161,159;,
 4;73,74,163,161;,
 4;74,95,165,163;,
 4;95,94,164,165;,
 4;94,101,162,164;,
 4;101,87,160,162;,
 4;87,29,157,160;,
 4;29,32,155,157;,
 4;32,44,152,155;,
 4;44,38,150,152;,
 4;38,37,151,150;,
 4;37,17,153,151;,
 4;17,16,154,153;,
 4;16,15,156,154;,
 4;15,14,158,156;;
 
 MeshMaterialList {
  15;
  174;
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14,
  14;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "2017-03-13-14-35-03.jpg.png";
   }
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.384000;0.208000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "2017-03-13-14-35-03.jpg.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  169;
  0.674120;-0.736708;0.053146;,
  0.572237;-0.564751;-0.594643;,
  0.667772;-0.715817;0.204172;,
  0.738653;-0.175237;-0.650910;,
  0.941845;-0.243453;0.231644;,
  0.966591;0.106831;0.233001;,
  0.805705;0.181446;-0.563841;,
  0.907634;0.409108;-0.093977;,
  0.511761;0.858984;0.015753;,
  0.708406;0.705799;0.003002;,
  0.883750;0.449778;0.129173;,
  0.828414;0.552524;0.091908;,
  0.732868;0.677326;0.064300;,
  0.461795;0.881924;0.094634;,
  0.555747;0.830105;-0.045505;,
  0.792913;0.609268;0.009053;,
  0.935030;0.251945;0.249483;,
  0.585421;0.768368;0.258635;,
  0.813459;0.525107;0.250095;,
  0.963300;0.263763;0.049820;,
  -0.000000;-0.970341;-0.241742;,
  0.546327;-0.835769;0.054921;,
  0.513940;-0.840420;-0.171930;,
  0.430269;-0.816156;0.385692;,
  0.334493;-0.941854;-0.032030;,
  0.311160;-0.899736;0.306032;,
  0.325807;-0.881695;0.341267;,
  0.999579;-0.026051;-0.012738;,
  0.888779;-0.455934;-0.046862;,
  0.971972;0.023325;0.233937;,
  0.882626;-0.469678;-0.019310;,
  0.988255;-0.138588;-0.064380;,
  0.869301;-0.414627;0.269074;,
  0.999261;0.025987;0.028333;,
  0.581178;-0.794334;0.176821;,
  0.584445;-0.810565;-0.037529;,
  0.572073;-0.769353;0.284305;,
  -0.000000;-0.209133;-0.977887;,
  0.354577;-0.191696;-0.915165;,
  0.383731;0.087638;-0.919277;,
  0.608712;0.235823;-0.757533;,
  0.509058;-0.178971;-0.841920;,
  0.341440;-0.513799;-0.787038;,
  -0.000000;-0.520251;-0.854014;,
  0.402240;-0.721218;-0.563958;,
  0.393505;-0.601919;-0.694872;,
  0.366709;-0.775230;-0.514338;,
  0.547061;-0.828886;-0.116929;,
  0.857914;-0.451152;0.245858;,
  0.756021;0.547093;-0.359335;,
  -0.000001;-0.997921;0.064446;,
  -0.000000;0.054209;-0.998530;,
  -0.000000;0.999956;-0.009365;,
  -0.000000;0.997202;-0.074749;,
  -0.000000;-0.999739;-0.022831;,
  -0.000000;0.957876;0.287182;,
  -0.000000;-0.776230;-0.630450;,
  -0.000000;0.992876;0.119155;,
  -0.000000;-0.859977;0.510333;,
  -0.000000;-0.910491;0.413529;,
  -0.000000;-0.951334;0.308163;,
  -0.674119;-0.736709;0.053146;,
  -0.547060;-0.828886;-0.116929;,
  -0.572237;-0.564751;-0.594644;,
  -0.667772;-0.715818;0.204173;,
  -0.738653;-0.175237;-0.650910;,
  -0.941845;-0.243452;0.231644;,
  -0.805705;0.181447;-0.563840;,
  -0.966591;0.106830;0.233000;,
  -0.907634;0.409108;-0.093977;,
  -0.828414;0.552524;0.091907;,
  -0.883750;0.449778;0.129172;,
  -0.511761;0.858984;0.015752;,
  -0.461795;0.881924;0.094634;,
  -0.708407;0.705798;0.003002;,
  -0.732867;0.677327;0.064300;,
  -0.555747;0.830105;-0.045506;,
  -0.585422;0.768368;0.258635;,
  -0.935031;0.251944;0.249484;,
  -0.813459;0.525107;0.250095;,
  -0.792913;0.609268;0.009053;,
  -0.963300;0.263762;0.049820;,
  -0.546328;-0.835769;0.054921;,
  -0.513940;-0.840420;-0.171930;,
  -0.430269;-0.816156;0.385692;,
  -0.325807;-0.881695;0.341267;,
  -0.334493;-0.941854;-0.032030;,
  -0.311160;-0.899736;0.306032;,
  -0.869301;-0.414626;0.269075;,
  -0.971972;0.023325;0.233937;,
  -0.988255;-0.138588;-0.064380;,
  -0.999579;-0.026052;-0.012737;,
  -0.888779;-0.455933;-0.046861;,
  -0.882627;-0.469677;-0.019310;,
  -0.857914;-0.451152;0.245859;,
  -0.999261;0.025985;0.028332;,
  -0.584445;-0.810565;-0.037529;,
  -0.581177;-0.794335;0.176821;,
  -0.572072;-0.769353;0.284305;,
  -0.608713;0.235823;-0.757533;,
  -0.509058;-0.178971;-0.841920;,
  -0.354577;-0.191696;-0.915166;,
  -0.383731;0.087637;-0.919277;,
  -0.341440;-0.513799;-0.787038;,
  -0.402240;-0.721218;-0.563958;,
  -0.393505;-0.601919;-0.694872;,
  -0.366709;-0.775230;-0.514337;,
  -0.756022;0.547092;-0.359334;,
  0.252370;0.883048;-0.395645;,
  -0.014393;0.925999;-0.377251;,
  0.266885;0.843384;-0.466343;,
  -0.308924;0.730328;-0.609251;,
  0.268859;0.589536;-0.761684;,
  0.211520;0.565914;-0.796869;,
  0.022267;0.553734;-0.832396;,
  -0.194942;0.600803;-0.775263;,
  -0.268860;0.589536;-0.761684;,
  0.308926;0.730328;-0.609250;,
  -0.266885;0.843384;-0.466343;,
  -0.300883;0.900281;-0.314585;,
  0.628877;-0.563856;0.535331;,
  0.879259;-0.401786;0.255874;,
  0.939422;-0.140471;-0.312658;,
  0.947014;0.016311;-0.320777;,
  0.999401;-0.007249;-0.033826;,
  0.915202;-0.248370;0.317361;,
  0.951139;-0.281172;0.127583;,
  0.846115;-0.403153;0.348650;,
  0.879499;-0.475643;0.015673;,
  0.879245;-0.474380;-0.043508;,
  -0.879244;-0.474380;-0.043508;,
  -0.879498;-0.475644;0.015673;,
  -0.846114;-0.403153;0.348652;,
  -0.951139;-0.281171;0.127583;,
  -0.958924;-0.200010;0.201146;,
  -0.988875;-0.081793;0.124244;,
  -0.947014;0.016312;-0.320777;,
  -0.939422;-0.140470;-0.312658;,
  -0.436160;-0.405305;0.803425;,
  -0.725223;-0.476084;0.497389;,
  -0.000000;-0.048689;0.998814;,
  -0.276145;0.276346;0.920531;,
  -0.091817;-0.044497;0.994781;,
  0.053431;-0.065158;0.996444;,
  0.395400;-0.088327;0.914252;,
  0.142808;-0.071920;0.987134;,
  -0.308946;-0.324178;0.894126;,
  -0.157276;-0.369409;0.915861;,
  -0.000000;-0.338930;0.940812;,
  0.157275;-0.369409;0.915861;,
  0.267329;-0.283568;0.920936;,
  0.598674;-0.286068;0.748168;,
  0.561918;-0.024283;0.826837;,
  0.074340;-0.045195;0.996208;,
  0.091817;-0.044497;0.994781;,
  0.142428;0.175986;0.974034;,
  0.758003;0.518786;-0.395339;,
  -0.758004;0.518785;-0.395338;,
  -0.934519;-0.202904;-0.292411;,
  0.420189;-0.537255;0.731299;,
  -0.420190;-0.537257;0.731297;,
  -0.000000;0.818487;0.574524;,
  -0.760661;0.460419;0.457611;,
  -0.868469;0.223646;0.442430;,
  -0.891289;0.024436;0.452778;,
  -0.765337;-0.355120;0.536795;,
  0.868469;0.223647;0.442430;,
  0.760661;0.460420;0.457611;,
  0.681839;0.561454;0.468898;;
  174;
  4;5,7,11,10;,
  4;8,13,57,52;,
  4;10,11,9,12;,
  4;12,9,13,8;,
  4;52,53,14,8;,
  4;12,15,19,10;,
  4;15,12,8,14;,
  4;14,53,55,17;,
  4;18,16,19,15;,
  4;17,18,15,14;,
  4;0,21,22,47;,
  4;0,2,23,21;,
  4;20,22,21,50;,
  4;21,23,58,50;,
  4;58,23,26,59;,
  4;60,54,24,25;,
  4;59,26,24,54;,
  4;31,27,28,30;,
  4;27,29,32,28;,
  4;30,48,4,31;,
  4;27,19,16,29;,
  4;4,5,33,31;,
  4;10,19,33,5;,
  4;27,31,33,19;,
  4;30,28,35,34;,
  4;28,32,36,35;,
  4;34,35,24,26;,
  4;35,36,25,24;,
  4;48,30,34,2;,
  4;26,23,2,34;,
  4;40,6,3,41;,
  4;38,37,51,39;,
  4;41,38,39,40;,
  4;43,37,38,42;,
  4;22,20,56,44;,
  4;44,56,43,42;,
  4;45,41,3,1;,
  4;47,46,45,1;,
  4;47,22,44,46;,
  4;46,44,42,45;,
  4;42,38,41,45;,
  4;11,7,49,9;,
  4;6,40,49,7;,
  4;68,71,70,69;,
  4;72,52,57,73;,
  4;71,75,74,70;,
  4;75,72,73,74;,
  4;52,72,76,53;,
  4;75,71,81,80;,
  4;80,76,72,75;,
  4;76,77,55,53;,
  4;79,80,81,78;,
  4;77,76,80,79;,
  4;61,62,83,82;,
  4;61,82,84,64;,
  4;20,50,82,83;,
  4;82,50,58,84;,
  4;58,59,85,84;,
  4;60,87,86,54;,
  4;59,54,86,85;,
  4;90,93,92,91;,
  4;91,92,88,89;,
  4;93,90,66,94;,
  4;91,89,78,81;,
  4;66,90,95,68;,
  4;71,68,95,81;,
  4;91,81,95,90;,
  4;93,97,96,92;,
  4;92,96,98,88;,
  4;97,85,86,96;,
  4;96,86,87,98;,
  4;94,64,97,93;,
  4;85,97,64,84;,
  4;99,100,65,67;,
  4;101,102,51,37;,
  4;100,99,102,101;,
  4;43,103,101,37;,
  4;83,104,56,20;,
  4;104,103,43,56;,
  4;105,63,65,100;,
  4;62,63,105,106;,
  4;62,106,104,83;,
  4;106,105,103,104;,
  4;103,105,100,101;,
  4;70,74,107,69;,
  4;67,69,107,99;,
  3;111,112,110;,
  3;112,113,110;,
  3;110,113,108;,
  3;113,114,108;,
  3;108,114,109;,
  3;114,115,109;,
  3;109,115,119;,
  3;119,115,118;,
  3;115,116,118;,
  3;116,117,118;,
  4;57,13,108,109;,
  4;13,9,110,108;,
  4;9,49,156,110;,
  4;49,40,112,156;,
  4;40,39,113,112;,
  4;39,51,114,113;,
  4;51,102,115,114;,
  4;102,99,116,115;,
  4;99,107,157,116;,
  4;107,74,118,157;,
  4;74,73,119,118;,
  4;73,57,109,119;,
  3;123,124,122;,
  3;122,124,121;,
  3;124,125,121;,
  3;121,125,120;,
  3;120,125,129;,
  3;125,126,129;,
  3;129,126,128;,
  3;126,127,128;,
  3;132,133,131;,
  3;131,133,130;,
  3;133,134,130;,
  3;130,134,139;,
  3;134,135,139;,
  3;139,135,138;,
  3;158,135,137;,
  3;135,136,137;,
  4;159,159,121,120;,
  4;1,3,122,121;,
  4;3,6,123,122;,
  4;6,7,124,123;,
  4;7,5,125,124;,
  4;5,4,126,125;,
  4;4,48,127,126;,
  4;48,2,128,127;,
  4;2,0,129,128;,
  4;0,47,120,129;,
  4;61,64,131,130;,
  4;64,94,132,131;,
  4;94,66,133,132;,
  4;66,68,134,133;,
  4;68,69,135,134;,
  4;69,67,136,135;,
  4;67,65,137,136;,
  4;65,63,158,137;,
  4;160,160,139,138;,
  4;62,61,130,139;,
  3;151,152,150;,
  3;152,153,150;,
  3;153,154,150;,
  3;150,154,149;,
  3;154,155,149;,
  3;149,155,148;,
  3;155,140,148;,
  3;140,141,148;,
  3;148,141,147;,
  3;141,142,147;,
  3;147,142,146;,
  3;142,143,146;,
  3;146,143,145;,
  3;143,144,145;,
  4;55,77,141,161;,
  4;77,79,162,141;,
  4;79,78,163,162;,
  4;78,89,164,163;,
  4;89,88,165,164;,
  4;88,98,146,165;,
  4;98,87,147,146;,
  4;87,60,148,147;,
  4;60,25,149,148;,
  4;25,36,150,149;,
  4;36,32,151,150;,
  4;32,29,152,151;,
  4;29,16,166,152;,
  4;16,18,167,166;,
  4;18,17,168,167;,
  4;17,55,161,155;;
 }
 MeshTextureCoords {
  166;
  1.121892;-0.395687;,
  1.409081;-0.459529;,
  1.365900;-0.238157;,
  1.079337;-0.181757;,
  1.036842;0.332956;,
  1.456070;0.318961;,
  1.413214;0.626778;,
  0.990445;0.568080;,
  1.535934;-0.028800;,
  1.064418;0.069520;,
  0.673848;0.524124;,
  0.718201;0.307411;,
  0.733329;0.050419;,
  0.747943;-0.241829;,
  0.372919;0.482342;,
  0.413190;0.291346;,
  0.425892;0.064259;,
  0.433706;-0.179865;,
  1.164505;-1.132847;,
  1.140620;-1.309218;,
  1.280236;-1.295413;,
  1.298872;-1.103032;,
  1.038337;-1.042054;,
  1.001179;-1.257336;,
  1.272914;-1.483426;,
  1.127207;-1.474117;,
  0.977316;-1.453573;,
  0.859518;-1.226439;,
  0.832181;-1.438933;,
  0.173007;-1.315144;,
  0.529248;-1.403534;,
  0.571308;-1.179169;,
  0.243280;-1.088924;,
  0.823660;-0.633622;,
  0.631177;-0.530563;,
  0.575486;-0.774479;,
  0.784619;-0.847865;,
  0.398743;-0.473502;,
  0.359953;-0.712720;,
  0.971903;-0.913428;,
  1.003325;-0.733142;,
  0.897134;-0.413580;,
  0.567931;-0.959249;,
  0.812038;-1.015563;,
  0.310618;-0.886394;,
  1.805880;-0.680708;,
  1.600468;-0.660737;,
  1.532318;-0.874348;,
  1.640846;-0.957095;,
  1.764181;-1.077355;,
  1.895040;-1.231630;,
  2.068625;-1.072961;,
  1.933016;-0.885986;,
  1.688986;-1.369205;,
  1.615752;-1.195672;,
  1.476906;-1.449197;,
  1.459676;-1.270204;,
  1.514312;-1.077177;,
  1.349664;-1.000798;,
  1.433464;-1.148360;,
  1.690704;-0.366877;,
  0.854361;1.531203;,
  0.871697;1.313772;,
  1.132056;1.446107;,
  1.113296;1.670869;,
  0.971032;0.806950;,
  1.370591;0.934626;,
  0.925797;1.067935;,
  1.352693;1.290990;,
  0.657484;0.744722;,
  0.536472;1.281290;,
  0.602027;0.996115;,
  0.359633;0.677085;,
  0.309990;0.899043;,
  0.251002;1.136062;,
  0.694538;2.252090;,
  0.831945;2.260008;,
  0.761604;2.440035;,
  0.623508;2.415282;,
  0.503476;2.327375;,
  0.597877;2.130359;,
  0.703339;2.618943;,
  0.565679;2.570290;,
  0.427054;2.509689;,
  0.291397;2.456063;,
  0.375590;2.259054;,
  -0.309120;2.157379;,
  -0.179877;1.958859;,
  0.111159;2.135056;,
  0.009566;2.339475;,
  0.502590;1.678891;,
  0.406658;1.874395;,
  0.225429;1.746810;,
  0.345463;1.527293;,
  0.034872;1.628670;,
  0.137366;1.409067;,
  0.648345;1.823593;,
  0.568997;1.988499;,
  0.633230;1.487188;,
  0.387354;2.043219;,
  0.167822;1.922533;,
  -0.059910;1.782335;,
  1.434830;1.991782;,
  1.200742;2.212755;,
  1.118861;2.103572;,
  1.242628;1.916607;,
  1.286649;2.362066;,
  1.501234;2.223925;,
  1.580775;2.440778;,
  1.370529;2.546156;,
  1.134790;2.622392;,
  1.111602;2.435471;,
  0.941124;2.464665;,
  0.908940;2.641581;,
  1.046280;2.293824;,
  0.908667;2.175478;,
  0.949097;2.340289;,
  1.409508;1.658437;,
  1.690704;-0.366877;,
  1.805880;-0.680708;,
  1.535934;-0.028800;,
  1.933016;-0.885986;,
  1.456070;0.318961;,
  1.580775;2.440778;,
  1.413214;0.626778;,
  1.501234;2.223925;,
  1.370591;0.934626;,
  1.352693;1.290990;,
  1.434830;1.991782;,
  1.409508;1.658437;,
  1.600468;-0.660737;,
  1.409081;-0.459529;,
  1.532318;-0.874348;,
  1.349664;-1.000798;,
  1.121892;-0.395687;,
  1.298872;-1.103032;,
  1.164505;-1.132847;,
  1.003325;-0.733142;,
  1.038337;-1.042054;,
  0.971903;-0.913428;,
  0.568997;1.988499;,
  0.648345;1.823593;,
  0.597877;2.130359;,
  0.694538;2.252090;,
  0.854361;1.531203;,
  0.831945;2.260008;,
  1.113296;1.670869;,
  0.908667;2.175478;,
  1.118861;2.103572;,
  1.242628;1.916607;,
  0.359953;-0.712720;,
  0.398743;-0.473502;,
  0.310618;-0.886394;,
  0.433706;-0.179865;,
  0.425892;0.064259;,
  0.243280;-1.088924;,
  0.413190;0.291346;,
  0.173007;-1.315144;,
  0.372919;0.482342;,
  0.359633;0.677085;,
  -0.179877;1.958859;,
  0.309990;0.899043;,
  -0.059910;1.782335;,
  0.251002;1.136062;,
  0.034872;1.628670;,
  0.137366;1.409067;;
 }
}
