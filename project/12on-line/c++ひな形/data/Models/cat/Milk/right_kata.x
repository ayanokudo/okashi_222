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
 66;
 -4.15490;-38.64370;-0.27170;,
 -3.91920;-30.02400;1.07450;,
 -1.95850;-29.66070;-4.29330;,
 -2.42210;-38.03600;-4.99710;,
 2.77470;-29.51000;-6.51680;,
 1.76150;-37.78410;-6.95410;,
 5.94490;-38.03600;-4.99710;,
 7.50780;-29.66070;-4.29330;,
 7.67770;-38.64370;-0.27170;,
 9.46820;-30.02400;1.07450;,
 5.94490;-39.25140;4.45370;,
 7.50780;-30.38730;6.44230;,
 1.76150;-39.50320;6.41110;,
 2.77470;-30.53770;8.66580;,
 -1.95850;-30.38730;6.44230;,
 -2.42210;-39.25140;4.45370;,
 -3.91920;-30.02400;1.07450;,
 -4.15490;-38.64370;-0.27170;,
 -4.08560;-22.35730;2.42070;,
 -4.01270;-15.58840;2.42070;,
 -1.80090;-15.60680;-3.57940;,
 -1.89730;-22.23840;-3.58960;,
 3.44910;-14.88370;-6.06470;,
 3.38560;-22.18910;-6.07910;,
 8.66200;-13.84230;-3.57940;,
 8.66850;-22.23840;-3.58960;,
 10.78390;-13.09310;2.42070;,
 10.85650;-22.35730;2.42070;,
 8.57200;-13.07500;8.42080;,
 8.66850;-22.47620;8.43090;,
 3.32210;-13.79810;10.90610;,
 3.38560;-22.52580;10.92040;,
 -1.89090;-14.83920;8.42080;,
 -1.89730;-22.47620;8.43090;,
 -4.01270;-15.58840;2.42070;,
 -4.08560;-22.35730;2.42070;,
 4.18670;-2.46370;-12.32560;,
 8.85010;-2.78740;-7.45450;,
 11.46490;-1.86400;0.63430;,
 8.73940;-1.84180;9.30480;,
 2.27030;-2.73280;12.36700;,
 5.65080;9.54570;-10.98250;,
 8.85010;6.99850;-7.45450;,
 10.37720;7.92180;0.63430;,
 8.73940;7.94440;9.30480;,
 5.49260;12.00070;12.47640;,
 8.15260;14.73560;0.63430;,
 -0.54120;-10.00710;12.04130;,
 2.32380;8.65910;9.14440;,
 4.26910;10.65920;0.48410;,
 -0.03270;-2.11550;9.06430;,
 -2.08880;-7.43530;8.82610;,
 2.43950;6.86380;-8.01130;,
 -3.07580;-10.96900;6.17840;,
 -4.62750;-11.51690;1.79050;,
 -3.01000;-11.53040;-2.59740;,
 1.36880;-1.91880;-8.99350;,
 0.82940;-11.00160;-4.41490;,
 5.81150;-40.31390;-0.27160;,
 4.62530;-40.73000;2.96320;,
 4.62530;-39.89790;-3.50650;,
 1.76150;-40.90240;4.30320;,
 1.76150;-39.72550;-4.84630;,
 -1.10250;-40.73000;2.96320;,
 -1.10250;-39.89790;-3.50650;,
 -2.28880;-40.31390;-0.27160;;
 
 67;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;6,5,4,7;,
 4;8,6,7,9;,
 4;10,8,9,11;,
 4;12,10,11,13;,
 4;12,13,14,15;,
 4;15,14,16,17;,
 4;18,19,20,21;,
 4;21,20,22,23;,
 4;23,22,24,25;,
 4;25,24,26,27;,
 4;27,26,28,29;,
 4;29,28,30,31;,
 4;31,30,32,33;,
 4;33,32,34,35;,
 4;22,36,37,24;,
 4;24,37,38,26;,
 4;26,38,39,28;,
 4;28,39,40,30;,
 4;36,41,42,37;,
 4;37,42,43,38;,
 4;38,43,44,39;,
 4;39,44,45,40;,
 4;42,41,46,43;,
 4;43,46,45,44;,
 4;21,2,1,18;,
 4;23,4,2,21;,
 4;7,4,23,25;,
 4;9,7,25,27;,
 4;11,9,27,29;,
 4;13,11,29,31;,
 4;33,14,13,31;,
 4;35,16,14,33;,
 4;47,32,30,40;,
 3;48,49,50;,
 3;50,49,51;,
 3;49,52,51;,
 3;51,52,53;,
 3;53,52,54;,
 3;54,52,55;,
 3;52,56,55;,
 3;56,57,55;,
 4;20,34,54,55;,
 4;34,32,53,54;,
 4;32,47,51,53;,
 4;47,40,50,51;,
 4;40,45,48,50;,
 4;45,46,49,48;,
 4;46,41,52,49;,
 4;41,36,56,52;,
 4;36,22,57,56;,
 4;22,20,55,57;,
 3;58,59,60;,
 3;59,61,60;,
 3;60,61,62;,
 3;61,63,62;,
 3;62,63,64;,
 3;63,65,64;,
 4;0,3,64,65;,
 4;3,5,62,64;,
 4;5,6,60,62;,
 4;6,8,58,60;,
 4;8,10,59,58;,
 4;10,12,61,59;,
 4;12,15,63,61;,
 4;15,0,65,63;;
 
 MeshMaterialList {
  1;
  67;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.200000;0.200000;0.200000;;
  }
 }
 MeshNormals {
  69;
  -0.914614;-0.401353;-0.048962;,
  -0.665595;-0.364299;-0.651360;,
  -0.000520;-0.391383;-0.920228;,
  0.635820;-0.441733;-0.632934;,
  0.863487;-0.500908;-0.058995;,
  0.639720;-0.568003;0.517813;,
  -0.001542;-0.586238;0.810138;,
  -0.668788;-0.500917;0.549367;,
  -0.999981;-0.005669;-0.002250;,
  -0.738487;0.039901;-0.673086;,
  0.000338;0.031609;-0.999500;,
  0.738152;-0.023805;-0.674214;,
  0.996377;-0.084974;-0.003549;,
  0.735153;-0.131783;0.664968;,
  -0.001929;-0.136315;0.990664;,
  -0.739925;-0.078846;0.668053;,
  -0.997549;-0.069964;-0.000853;,
  0.037227;-0.070847;-0.996792;,
  0.775402;-0.120634;-0.619838;,
  0.999423;-0.033427;0.005970;,
  0.743607;-0.024115;0.668182;,
  0.103116;-0.110711;0.988489;,
  -0.741279;-0.105406;0.662869;,
  0.658435;-0.175865;-0.731803;,
  0.843918;-0.106534;-0.525788;,
  0.999964;-0.008328;0.001675;,
  0.777645;-0.032229;0.627877;,
  0.312556;-0.167596;0.934997;,
  0.890462;0.152043;-0.428905;,
  0.972907;0.230395;-0.019220;,
  0.865291;0.131626;0.483680;,
  0.780450;0.170908;0.601406;,
  0.834729;0.200243;-0.512962;,
  0.916324;0.399106;-0.032639;,
  -0.999994;0.003352;0.000834;,
  -0.738069;0.083143;-0.669583;,
  -0.000371;0.056350;-0.998411;,
  0.732249;-0.063790;-0.678043;,
  0.982034;-0.188065;-0.015498;,
  0.719894;-0.269658;0.639560;,
  -0.002998;-0.258440;0.966023;,
  -0.736405;-0.135290;0.662876;,
  -0.738808;-0.023431;-0.673509;,
  -0.053550;-0.336137;0.940290;,
  -0.995009;0.096448;-0.025580;,
  -0.781836;-0.040628;-0.622159;,
  -0.954503;0.157893;0.252971;,
  -0.940886;0.253055;0.225158;,
  -0.920369;0.268619;0.284192;,
  -0.907481;0.391809;0.151537;,
  -0.880005;0.472929;-0.043931;,
  -0.918656;0.344990;-0.192491;,
  -0.738484;-0.092809;-0.667853;,
  -0.537980;-0.201603;-0.818495;,
  -0.240179;-0.912709;-0.330568;,
  -0.465741;-0.878159;-0.109192;,
  0.000002;-0.933372;-0.358910;,
  0.191026;-0.937722;-0.290151;,
  0.465734;-0.878162;-0.109193;,
  0.260309;-0.958701;0.114596;,
  0.000000;-0.989285;0.145996;,
  -0.206770;-0.976333;0.063407;,
  -0.856554;0.113837;0.503345;,
  -0.780473;0.219732;0.585303;,
  -0.825519;0.467352;0.316385;,
  -0.720383;0.689170;-0.078057;,
  -0.779081;0.454673;-0.431631;,
  -0.766539;-0.048007;-0.640401;,
  -0.758228;-0.257021;-0.599191;;
  67;
  4;0,34,35,1;,
  4;1,35,36,2;,
  4;3,2,36,37;,
  4;4,3,37,38;,
  4;5,4,38,39;,
  4;6,5,39,40;,
  4;6,40,41,7;,
  4;7,41,34,0;,
  4;8,16,42,9;,
  4;9,42,17,10;,
  4;10,17,18,11;,
  4;11,18,19,12;,
  4;12,19,20,13;,
  4;13,20,21,14;,
  4;14,21,22,15;,
  4;15,22,16,8;,
  4;17,23,24,18;,
  4;18,24,25,19;,
  4;19,25,26,20;,
  4;20,26,27,21;,
  4;23,32,28,24;,
  4;24,28,29,25;,
  4;25,29,30,26;,
  4;26,30,31,27;,
  4;28,32,33,29;,
  4;29,33,31,30;,
  4;9,35,34,8;,
  4;10,36,35,9;,
  4;37,36,10,11;,
  4;38,37,11,12;,
  4;39,38,12,13;,
  4;40,39,13,14;,
  4;15,41,40,14;,
  4;8,34,41,15;,
  4;43,22,21,27;,
  3;49,50,48;,
  3;48,50,47;,
  3;50,51,47;,
  3;47,51,46;,
  3;46,51,44;,
  3;44,51,45;,
  3;51,52,45;,
  3;52,53,45;,
  4;42,16,44,45;,
  4;16,22,46,44;,
  4;22,62,47,46;,
  4;62,63,48,47;,
  4;63,64,49,48;,
  4;64,65,50,49;,
  4;65,66,51,50;,
  4;66,67,52,51;,
  4;67,68,53,52;,
  4;17,42,45,53;,
  3;58,59,57;,
  3;59,60,57;,
  3;57,60,56;,
  3;60,61,56;,
  3;56,61,54;,
  3;61,55,54;,
  4;0,1,54,55;,
  4;1,2,56,54;,
  4;2,3,57,56;,
  4;3,4,58,57;,
  4;4,5,59,58;,
  4;5,6,60,59;,
  4;6,7,61,60;,
  4;7,0,55,61;;
 }
 MeshTextureCoords {
  66;
  1.450050;1.611580;,
  1.438330;1.509540;,
  1.510310;1.510450;,
  1.514750;1.612270;,
  1.583160;1.511230;,
  1.582000;1.614220;,
  1.650280;1.615750;,
  1.656930;1.511370;,
  1.717680;1.617870;,
  1.730000;1.512380;,
  1.782960;1.623300;,
  1.801530;1.517510;,
  1.845890;1.634580;,
  1.871200;1.529770;,
  1.938980;1.550890;,
  1.906740;1.652940;,
  2.005250;1.580530;,
  1.965960;1.677810;,
  1.423430;1.418910;,
  1.424380;1.354580;,
  1.510900;1.355530;,
  1.504110;1.424240;,
  1.578710;1.327960;,
  1.582760;1.421600;,
  1.665160;1.317790;,
  1.664800;1.421120;,
  1.750270;1.315730;,
  1.744430;1.422880;,
  1.832970;1.322220;,
  1.819960;1.427920;,
  1.916010;1.338900;,
  1.892630;1.439230;,
  1.989090;1.377080;,
  1.963150;1.460990;,
  2.065470;1.413840;,
  2.035990;1.491800;,
  1.557170;1.171100;,
  1.641890;1.185110;,
  1.742070;1.188260;,
  1.848900;1.196310;,
  1.945040;1.213250;,
  1.609140;1.037690;,
  1.659120;1.080340;,
  1.752750;1.083450;,
  1.852380;1.090840;,
  1.905430;1.043710;,
  1.760300;1.002510;,
  1.986240;1.290570;,
  1.905430;1.043710;,
  1.760300;1.002510;,
  1.945040;1.213250;,
  1.986240;1.290570;,
  1.609140;1.037690;,
  1.989090;1.377080;,
  2.065470;1.413840;,
  1.510900;1.355530;,
  1.557170;1.171100;,
  1.578710;1.327960;,
  1.717680;1.617870;,
  1.782960;1.623300;,
  1.650280;1.615750;,
  1.845890;1.634580;,
  1.582000;1.614220;,
  1.906740;1.652940;,
  1.514750;1.612270;,
  1.450050;1.611580;;
 }
}
