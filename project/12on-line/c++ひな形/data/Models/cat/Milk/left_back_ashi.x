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
 71;
 7.54130;-7.53270;2.95570;,
 5.80850;-7.89900;-1.79190;,
 4.25540;-4.24020;-2.42390;,
 5.98810;-1.98040;1.82690;,
 1.62490;-8.05080;-3.75860;,
 0.07170;-5.17650;-4.18470;,
 -2.55850;-7.89900;-1.79190;,
 -4.11170;-4.24020;-2.42390;,
 -4.29130;-7.53270;2.95570;,
 -5.84440;-1.98040;1.82690;,
 -2.55850;-7.16640;7.70330;,
 -4.11170;0.27930;6.07750;,
 1.62490;-7.01450;9.66990;,
 0.07170;1.21540;7.83830;,
 5.80850;-7.16640;7.70330;,
 4.25540;0.27930;6.07750;,
 7.54130;-7.53270;2.95570;,
 5.98810;-1.98040;1.82690;,
 8.54820;-15.26730;0.85120;,
 6.97850;-14.84500;-3.36710;,
 3.18920;-14.67000;-5.11430;,
 -0.60020;-14.84500;-3.36710;,
 -2.16960;-15.26730;0.85120;,
 -0.60020;-15.68970;5.06940;,
 3.18920;-15.86470;6.81670;,
 6.97850;-15.68970;5.06940;,
 8.54820;-15.26730;0.85120;,
 3.18920;-21.12070;-6.58680;,
 6.58450;-21.47630;-5.02230;,
 8.80230;-26.22510;-11.09250;,
 5.02950;-26.22510;-12.69260;,
 -0.20590;-21.47630;-5.02230;,
 1.25700;-26.22510;-11.09250;,
 8.80230;-30.73600;-13.00120;,
 5.02950;-30.73600;-14.60140;,
 1.25700;-30.73600;-13.00120;,
 11.72260;-26.22510;-5.71060;,
 11.72260;-30.73600;-7.61960;,
 -1.66350;-30.73600;-7.61960;,
 -1.66350;-26.22510;-5.71060;,
 11.72260;-30.73600;-7.61960;,
 11.72260;-26.22510;-5.71060;,
 10.07810;-26.67140;-0.73910;,
 10.07810;-30.69740;-3.82440;,
 -0.01880;-30.69740;-3.82440;,
 -0.01880;-26.67140;-0.73910;,
 5.02950;-30.44530;-1.58770;,
 5.02950;-27.33170;1.15360;,
 8.42490;-23.19270;1.43480;,
 5.02950;-23.54800;2.99900;,
 1.63440;-23.19270;1.43480;,
 0.22820;-22.33430;-1.85580;,
 9.83110;-22.33430;-1.85580;,
 9.83110;-22.33430;-1.85580;,
 -0.01880;-30.69740;-3.82440;,
 -1.66350;-30.73600;-7.61960;,
 5.02950;-30.73600;-6.82420;,
 5.02950;-30.44530;-1.58770;,
 10.07810;-30.69740;-3.82440;,
 11.72260;-30.73600;-7.61960;,
 1.25700;-30.73600;-13.00120;,
 5.02950;-30.73600;-14.60140;,
 8.80230;-30.73600;-13.00120;,
 3.54460;0.18600;0.42690;,
 2.52750;-1.14040;-2.06830;,
 2.52750;1.51240;2.92200;,
 0.07180;-1.69010;-3.10180;,
 0.07180;2.06190;3.95550;,
 -2.38380;-1.14040;-2.06830;,
 -2.38380;1.51240;2.92200;,
 -3.40090;0.18600;0.42690;;
 
 58;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;1,0,18,19;,
 4;4,1,19,20;,
 4;21,6,4,20;,
 4;22,8,6,21;,
 4;23,10,8,22;,
 4;24,12,10,23;,
 4;14,12,24,25;,
 4;16,14,25,26;,
 4;27,28,29,30;,
 4;31,27,30,32;,
 4;30,29,33,34;,
 4;32,30,34,35;,
 4;33,29,36,37;,
 4;32,35,38,39;,
 4;40,41,42,43;,
 4;39,38,44,45;,
 4;44,46,47,45;,
 4;43,42,47,46;,
 4;47,42,48,49;,
 4;47,49,50,45;,
 4;45,50,51,39;,
 4;39,51,31,32;,
 4;36,29,28,52;,
 4;42,41,53,48;,
 4;54,55,56,57;,
 4;58,57,56,59;,
 4;60,61,56,55;,
 4;56,61,62,59;,
 4;19,18,52,28;,
 4;26,25,48,53;,
 4;25,24,49,48;,
 4;24,23,50,49;,
 4;23,22,51,50;,
 4;22,21,31,51;,
 4;21,20,27,31;,
 4;20,19,28,27;,
 3;63,64,65;,
 3;64,66,65;,
 3;65,66,67;,
 3;66,68,67;,
 3;67,68,69;,
 3;68,70,69;,
 4;3,2,64,63;,
 4;2,5,66,64;,
 4;5,7,68,66;,
 4;7,9,70,68;,
 4;9,11,69,70;,
 4;11,13,67,69;,
 4;13,15,65,67;,
 4;15,3,63,65;;
 
 MeshMaterialList {
  1;
  58;
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
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  64;
  0.978629;0.202677;-0.034752;,
  0.865380;0.455412;-0.209089;,
  0.616109;0.270213;-0.739861;,
  0.700296;0.205750;-0.683559;,
  -0.005257;0.075495;-0.997132;,
  -0.009148;0.018134;-0.999794;,
  -0.679569;0.012020;-0.733513;,
  -0.733316;-0.215834;-0.644720;,
  -0.967969;0.203737;-0.146719;,
  -0.964100;-0.263383;0.033760;,
  -0.714018;-0.011546;0.700032;,
  -0.713405;-0.188210;0.675004;,
  0.002385;0.215759;0.976444;,
  0.005864;-0.049296;0.998767;,
  0.676206;0.641388;0.362445;,
  0.746140;0.101595;0.657992;,
  0.682785;0.239151;-0.690371;,
  0.990969;0.129274;-0.035626;,
  -0.003735;0.208107;-0.978099;,
  -0.772958;-0.006007;-0.634429;,
  -0.962641;-0.268585;0.034425;,
  -0.685325;-0.416621;0.597291;,
  0.010101;-0.379218;0.925252;,
  0.732541;-0.136842;0.666827;,
  -0.011338;0.536325;-0.843936;,
  -0.010895;0.605045;-0.796116;,
  0.569621;0.555387;-0.605869;,
  0.580117;0.517682;-0.628863;,
  -0.788264;0.314560;-0.528859;,
  -0.688651;0.431995;-0.582357;,
  -0.000013;0.389691;-0.920946;,
  0.648308;0.296706;-0.701186;,
  -0.648307;0.296707;-0.701187;,
  0.997506;0.002090;-0.070549;,
  0.967172;0.251377;-0.037254;,
  -0.991615;0.125453;0.031007;,
  -0.997507;0.002084;-0.070544;,
  0.682345;-0.435139;0.587418;,
  0.714382;-0.286793;0.638285;,
  -0.714379;-0.286791;0.638289;,
  -0.682335;-0.435142;0.587426;,
  -0.000011;-0.529902;0.848059;,
  -0.000005;-0.902420;0.430858;,
  0.005586;-0.430251;0.902692;,
  0.728781;-0.149748;0.668172;,
  -0.714246;-0.309720;0.627635;,
  -0.994324;-0.020551;0.104392;,
  0.948976;0.312636;-0.041274;,
  0.000000;-0.999863;0.016542;,
  0.285654;0.695093;-0.659732;,
  0.515275;0.755491;-0.404630;,
  -0.000004;0.706262;-0.707951;,
  -0.226587;0.745674;-0.626601;,
  -0.515273;0.755492;-0.404631;,
  -0.270001;0.935378;-0.228402;,
  0.000012;0.976301;-0.216419;,
  0.214360;0.934727;-0.283435;,
  0.012014;-0.999381;0.033078;,
  0.006008;-0.999845;0.016542;,
  -0.012013;-0.999381;0.033078;,
  -0.006008;-0.999845;0.016542;,
  0.000000;-1.000000;-0.000000;,
  -0.512252;0.857108;0.054442;,
  -0.000006;0.977051;0.213007;;
  58;
  4;0,3,2,1;,
  4;3,5,4,2;,
  4;5,7,6,4;,
  4;7,9,8,6;,
  4;9,11,10,8;,
  4;11,13,12,10;,
  4;13,15,14,12;,
  4;15,0,1,14;,
  4;3,0,17,16;,
  4;5,3,16,18;,
  4;19,7,5,18;,
  4;20,9,7,19;,
  4;21,11,9,20;,
  4;22,13,11,21;,
  4;15,13,22,23;,
  4;0,15,23,17;,
  4;24,27,26,25;,
  4;28,24,25,29;,
  4;25,26,31,30;,
  4;29,25,30,32;,
  4;31,26,34,33;,
  4;29,32,36,35;,
  4;33,34,38,37;,
  4;35,36,40,39;,
  4;40,42,41,39;,
  4;37,38,41,42;,
  4;41,38,44,43;,
  4;41,43,45,39;,
  4;39,45,46,35;,
  4;35,46,28,29;,
  4;34,26,27,47;,
  4;38,34,47,44;,
  4;57,58,48,42;,
  4;59,42,48,60;,
  4;61,61,48,58;,
  4;48,61,61,60;,
  4;16,17,47,27;,
  4;17,23,44,47;,
  4;23,22,43,44;,
  4;22,21,45,43;,
  4;21,20,46,45;,
  4;20,19,28,46;,
  4;19,18,24,28;,
  4;18,16,27,24;,
  3;50,49,56;,
  3;49,51,56;,
  3;56,51,55;,
  3;51,52,55;,
  3;55,52,54;,
  3;52,53,54;,
  4;1,2,49,50;,
  4;2,4,51,49;,
  4;4,6,52,51;,
  4;6,8,53,52;,
  4;8,62,54,53;,
  4;62,63,55,54;,
  4;63,14,56,55;,
  4;14,1,50,56;;
 }
 MeshTextureCoords {
  71;
  -0.254850;-1.027210;,
  -0.257610;-0.953490;,
  -0.316740;-0.952260;,
  -0.323300;-1.027210;,
  -0.256270;-0.865140;,
  -0.311180;-0.863270;,
  -0.251420;-0.773860;,
  -0.314420;-0.771050;,
  -0.244620;-0.694690;,
  -0.321490;-0.686220;,
  -0.234380;-0.630640;,
  -0.322510;-0.610920;,
  -0.218910;-0.575440;,
  -0.307920;-0.542210;,
  -0.196690;-0.523780;,
  -0.273790;-0.482700;,
  -0.165800;-0.470740;,
  -0.226640;-0.433030;,
  -0.160410;-1.004710;,
  -0.152300;-0.943280;,
  -0.143810;-0.872310;,
  -0.140140;-0.797640;,
  -0.139720;-0.727430;,
  -0.135830;-0.664370;,
  -0.123620;-0.607360;,
  -0.102720;-0.554710;,
  -0.073580;-0.504960;,
  -0.038190;-0.885010;,
  -0.052510;-0.950510;,
  0.048300;-0.953580;,
  0.068070;-0.905490;,
  -0.031810;-0.814900;,
  0.067680;-0.852720;,
  0.101350;-0.968900;,
  0.122260;-0.916930;,
  0.124480;-0.860200;,
  0.003420;-1.011050;,
  0.055710;-1.027520;,
  0.104510;-0.784150;,
  0.045410;-0.780760;,
  0.147930;-0.542680;,
  0.088670;-0.521760;,
  0.050580;-0.575740;,
  0.110850;-0.584510;,
  0.084550;-0.733130;,
  0.022690;-0.721140;,
  0.077900;-0.654860;,
  0.028200;-0.645790;,
  -0.003650;-0.582520;,
  -0.021570;-0.635470;,
  -0.028240;-0.693740;,
  -0.029330;-0.753210;,
  -0.067240;-0.999640;,
  0.015780;-0.536340;,
  -0.597410;-0.202010;,
  -0.559700;-0.165890;,
  -0.651450;-0.143130;,
  -0.673470;-0.203910;,
  -0.730820;-0.153840;,
  -0.736530;-0.101870;,
  -0.575550;-0.089510;,
  -0.618640;-0.053070;,
  -0.675370;-0.053390;,
  -0.323300;-1.027210;,
  -0.316740;-0.952260;,
  -0.273790;-0.482700;,
  -0.311180;-0.863270;,
  -0.307920;-0.542210;,
  -0.314420;-0.771050;,
  -0.322510;-0.610920;,
  -0.321490;-0.686220;;
 }
}
