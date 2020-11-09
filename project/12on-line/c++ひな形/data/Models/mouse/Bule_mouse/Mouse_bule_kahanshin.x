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
 93;
 11.34662;0.19475;17.71016;,
 10.79455;3.62904;17.11372;,
 10.79455;-1.74996;18.12726;,
 9.19237;6.72719;16.57572;,
 -10.65601;-1.74996;18.12726;,
 6.69688;9.18587;16.14872;,
 3.55236;10.76445;15.87463;,
 0.06928;11.30836;15.78020;,
 -3.41383;10.76445;15.87463;,
 -6.55832;9.18587;16.14872;,
 -9.05381;6.72719;16.57572;,
 -10.65601;3.62904;17.11372;,
 -11.20809;0.19475;17.71016;,
 -27.49193;-1.00989;3.12742;,
 -23.37572;6.94957;1.74517;,
 -16.68493;0.42221;-13.85112;,
 -19.14064;-5.52865;-13.85112;,
 -16.96451;13.26625;0.64821;,
 -12.35273;5.36349;-13.85112;,
 -8.88590;17.32175;-0.05606;,
 -6.54838;8.64409;-13.85112;,
 0.06928;18.71921;-0.29876;,
 0.06928;9.79485;-13.85112;,
 9.02446;17.32175;-0.05606;,
 6.68691;8.64409;-13.85112;,
 17.10303;13.26622;0.64821;,
 12.49127;5.36347;-13.85112;,
 23.51424;6.94957;1.74517;,
 16.82346;0.42221;-13.85112;,
 27.63045;-1.00989;3.12742;,
 19.27918;-5.52865;-13.85112;,
 29.04885;-9.83301;4.65959;,
 19.73013;-11.79130;-13.85112;,
 27.63045;-14.82921;5.73125;,
 18.42612;-15.19443;-13.85112;,
 -27.49193;-14.82921;5.73125;,
 -28.91030;-9.83301;4.65959;,
 -19.59160;-11.79130;-13.85112;,
 -18.28758;-15.19443;-13.85112;,
 -27.49193;-1.00989;3.12742;,
 -19.14064;-5.52865;-13.85112;,
 27.63045;-14.82921;5.73125;,
 -27.49193;-1.00989;3.12742;,
 -28.91030;-9.83301;4.65959;,
 -22.45073;-6.29644;8.46716;,
 -21.34841;0.56100;7.27630;,
 -27.49193;-14.82921;5.73125;,
 -21.34841;-10.17950;9.30002;,
 21.48693;-10.17950;9.30002;,
 29.04885;-9.83301;4.65959;,
 22.58930;-6.29644;8.46716;,
 27.63045;-1.00989;3.12742;,
 21.48693;0.56100;7.27630;,
 23.51424;6.94957;1.74517;,
 18.28773;6.74715;6.20202;,
 17.10303;13.26622;0.64821;,
 13.30491;11.65652;5.34944;,
 9.02446;17.32175;-0.05606;,
 7.02617;14.80850;4.80207;,
 0.06928;18.71921;-0.29876;,
 0.06928;15.89460;4.61347;,
 -8.88590;17.32175;-0.05606;,
 -6.88762;14.80850;4.80207;,
 -16.96451;13.26625;0.64821;,
 -13.16635;11.65652;5.34944;,
 -23.37572;6.94957;1.74517;,
 -18.14921;6.74715;6.20202;,
 -20.22625;-4.60388;12.47792;,
 -19.23273;1.57641;11.40465;,
 -19.23273;-8.10351;13.22854;,
 19.37127;-8.10351;13.22854;,
 20.36477;-4.60388;12.47792;,
 19.37127;1.57639;11.40465;,
 16.48799;7.15171;10.43643;,
 11.99719;11.57631;9.66807;,
 6.33843;14.41707;9.17474;,
 0.06928;15.39593;9.00475;,
 -6.19990;14.41707;9.17474;,
 -11.85866;11.57631;9.66807;,
 -16.34946;7.15171;10.43646;,
 -15.54985;-2.05016;15.76961;,
 -14.78524;2.70606;14.94366;,
 -14.78524;-4.74345;16.34727;,
 14.92379;-4.74345;16.34727;,
 15.68837;-2.05016;15.76961;,
 14.92379;2.70606;14.94366;,
 12.70486;6.99672;14.19854;,
 9.24882;10.40183;13.60717;,
 4.89391;12.58804;13.22753;,
 0.06928;13.34134;13.09672;,
 -4.75539;12.58804;13.22753;,
 -9.11025;10.40183;13.60717;,
 -12.56633;6.99672;14.19854;;
 
 88;
 3;0,1,2;,
 3;1,3,2;,
 3;2,3,4;,
 3;3,5,4;,
 3;5,6,4;,
 3;6,7,4;,
 3;7,8,4;,
 3;8,9,4;,
 3;9,10,4;,
 3;10,11,4;,
 3;11,12,4;,
 4;13,14,15,16;,
 4;14,17,18,15;,
 4;17,19,20,18;,
 4;19,21,22,20;,
 4;21,23,24,22;,
 4;23,25,26,24;,
 4;25,27,28,26;,
 4;27,29,30,28;,
 4;29,31,32,30;,
 4;31,33,34,32;,
 4;35,36,37,38;,
 4;36,39,40,37;,
 3;41,35,34;,
 3;32,34,30;,
 3;30,34,28;,
 3;34,35,38;,
 3;34,38,28;,
 3;28,38,26;,
 3;26,38,24;,
 3;24,38,22;,
 3;22,38,20;,
 3;20,38,18;,
 3;18,38,15;,
 3;15,38,16;,
 3;38,37,16;,
 4;42,43,44,45;,
 4;43,46,47,44;,
 4;46,41,48,47;,
 4;41,49,50,48;,
 4;49,51,52,50;,
 4;51,53,54,52;,
 4;53,55,56,54;,
 4;55,57,58,56;,
 4;57,59,60,58;,
 4;59,61,62,60;,
 4;61,63,64,62;,
 4;63,65,66,64;,
 4;65,42,45,66;,
 4;45,44,67,68;,
 4;44,47,69,67;,
 4;47,48,70,69;,
 4;48,50,71,70;,
 4;50,52,72,71;,
 4;52,54,73,72;,
 4;54,56,74,73;,
 4;56,58,75,74;,
 4;58,60,76,75;,
 4;60,62,77,76;,
 4;62,64,78,77;,
 4;64,66,79,78;,
 4;66,45,68,79;,
 4;68,67,80,81;,
 4;67,69,82,80;,
 4;69,70,83,82;,
 4;70,71,84,83;,
 4;71,72,85,84;,
 4;72,73,86,85;,
 4;73,74,87,86;,
 4;74,75,88,87;,
 4;75,76,89,88;,
 4;76,77,90,89;,
 4;77,78,91,90;,
 4;78,79,92,91;,
 4;79,68,81,92;,
 4;81,80,12,11;,
 4;80,82,4,12;,
 4;82,83,2,4;,
 4;83,84,0,2;,
 4;84,85,1,0;,
 4;85,86,3,1;,
 4;86,87,5,3;,
 4;87,88,6,5;,
 4;88,89,7,6;,
 4;89,90,8,7;,
 4;90,91,9,8;,
 4;91,92,10,9;,
 4;92,81,11,10;;
 
 MeshMaterialList {
  7;
  88;
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
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
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
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.432000;0.432000;0.432000;1.000000;;
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
   0.065882;0.000000;0.800000;1.000000;;
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
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.736000;0.312000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  89;
  -0.856859;0.200696;-0.474882;,
  -0.734006;0.454151;-0.504958;,
  -0.536187;0.657738;-0.529040;,
  -0.282856;0.789562;-0.544597;,
  0.000000;0.835182;-0.549974;,
  0.282857;0.789561;-0.544597;,
  0.536188;0.657738;-0.529040;,
  0.734006;0.454152;-0.504957;,
  0.856860;0.200697;-0.474882;,
  0.890693;-0.134923;-0.434121;,
  0.857149;-0.328444;-0.396762;,
  -0.857150;-0.328442;-0.396762;,
  -0.890693;-0.134923;-0.434121;,
  0.000000;0.471878;-0.881664;,
  0.160094;0.446883;-0.880151;,
  0.305026;0.374173;-0.875759;,
  -0.305026;0.374173;-0.875759;,
  -0.160093;0.446883;-0.880151;,
  -0.740077;0.091092;0.666325;,
  -0.746558;0.348196;0.566931;,
  -0.405736;-0.471329;0.783088;,
  0.405734;-0.471331;0.783088;,
  0.740075;0.091091;0.666326;,
  0.746557;0.348198;0.566931;,
  0.665265;0.576680;0.474197;,
  0.501079;0.771843;0.391379;,
  0.269449;0.903442;0.333452;,
  0.000000;0.949892;0.312579;,
  -0.269449;0.903441;0.333453;,
  -0.501078;0.771844;0.391379;,
  -0.665265;0.576680;0.474197;,
  -0.764082;0.084353;0.639580;,
  -0.767382;0.349687;0.537442;,
  -0.539957;-0.302649;0.785398;,
  0.000000;-0.793422;0.608671;,
  0.764082;0.084353;0.639581;,
  0.767382;0.349689;0.537441;,
  0.680772;0.582513;0.444103;,
  0.510719;0.779752;0.362150;,
  0.273892;0.911897;0.305659;,
  0.000000;0.958384;0.285482;,
  -0.273892;0.911897;0.305659;,
  -0.510718;0.779753;0.362150;,
  -0.680771;0.582514;0.444105;,
  -0.542437;0.134842;0.829204;,
  -0.568860;0.323559;0.756114;,
  -0.279680;-0.306327;0.909913;,
  0.279681;-0.306326;0.909914;,
  0.542438;0.134843;0.829204;,
  0.568862;0.323559;0.756113;,
  0.526733;0.511565;0.678862;,
  0.409858;0.683234;0.604324;,
  0.225243;0.804834;0.549098;,
  0.000000;0.848876;0.528592;,
  -0.225243;0.804833;0.549098;,
  -0.409858;0.683234;0.604325;,
  -0.526731;0.511565;0.678864;,
  -0.346357;0.162593;0.923905;,
  -0.285435;0.254503;0.923989;,
  -0.052908;0.109629;0.992564;,
  0.117059;0.022594;0.992868;,
  0.346359;0.162593;0.923904;,
  0.285436;0.254502;0.923989;,
  0.201018;0.312606;0.928369;,
  0.196207;0.430500;0.881007;,
  0.109982;0.496756;0.860893;,
  -0.000066;0.521884;0.853017;,
  -0.110628;0.498100;0.860034;,
  -0.198788;0.433294;0.879056;,
  -0.253700;0.346080;0.903252;,
  0.000000;-0.892738;0.450576;,
  0.000000;-0.952864;0.303399;,
  0.000000;-0.999826;0.018647;,
  0.000000;0.000000;-1.000000;,
  -0.584899;0.326711;0.742397;,
  -0.556232;0.132744;0.820357;,
  -0.521556;0.034794;0.852507;,
  0.521554;0.034789;0.852509;,
  0.556232;0.132743;0.820357;,
  0.584899;0.326712;0.742396;,
  0.542454;0.520073;0.659749;,
  0.422409;0.696697;0.579814;,
  0.232151;0.821673;0.520538;,
  0.000000;0.866884;0.498510;,
  -0.232150;0.821672;0.520539;,
  -0.422407;0.696696;0.579816;,
  -0.542453;0.520072;0.659750;,
  0.000000;-0.884143;0.467217;,
  0.727518;-0.059941;0.683465;;
  88;
  3;61,62,60;,
  3;62,63,60;,
  3;60,63,59;,
  3;63,64,59;,
  3;64,65,59;,
  3;65,66,59;,
  3;66,67,59;,
  3;67,68,59;,
  3;68,69,59;,
  3;69,58,59;,
  3;58,57,59;,
  4;0,1,1,0;,
  4;1,2,16,1;,
  4;2,3,17,16;,
  4;3,4,13,17;,
  4;4,5,14,13;,
  4;5,6,15,14;,
  4;6,7,7,15;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;11,12,12,11;,
  4;12,0,0,12;,
  3;70,71,72;,
  3;73,73,73;,
  3;73,73,73;,
  3;72,71,72;,
  3;73,73,73;,
  3;73,73,15;,
  3;15,73,14;,
  3;14,73,13;,
  3;13,73,17;,
  3;17,73,16;,
  3;16,73,73;,
  3;73,73,73;,
  3;73,73,73;,
  4;74,75,18,19;,
  4;75,76,20,18;,
  4;71,70,21,20;,
  4;77,78,22,21;,
  4;78,79,23,22;,
  4;79,80,24,23;,
  4;80,81,25,24;,
  4;81,82,26,25;,
  4;82,83,27,26;,
  4;83,84,28,27;,
  4;84,85,29,28;,
  4;85,86,30,29;,
  4;86,74,19,30;,
  4;19,18,31,32;,
  4;18,20,33,31;,
  4;20,21,34,87;,
  4;21,22,35,88;,
  4;22,23,36,35;,
  4;23,24,37,36;,
  4;24,25,38,37;,
  4;25,26,39,38;,
  4;26,27,40,39;,
  4;27,28,41,40;,
  4;28,29,42,41;,
  4;29,30,43,42;,
  4;30,19,32,43;,
  4;32,31,44,45;,
  4;31,33,46,44;,
  4;33,34,47,46;,
  4;88,35,48,47;,
  4;35,36,49,48;,
  4;36,37,50,49;,
  4;37,38,51,50;,
  4;38,39,52,51;,
  4;39,40,53,52;,
  4;40,41,54,53;,
  4;41,42,55,54;,
  4;42,43,56,55;,
  4;43,32,45,56;,
  4;45,44,57,58;,
  4;44,46,59,57;,
  4;46,47,60,59;,
  4;47,48,61,60;,
  4;48,49,62,61;,
  4;49,50,63,62;,
  4;50,51,64,63;,
  4;51,52,65,64;,
  4;52,53,66,65;,
  4;53,54,67,66;,
  4;54,55,68,67;,
  4;55,56,69,68;,
  4;56,45,58,69;;
 }
 MeshTextureCoords {
  93;
  0.250000;0.250000;,
  0.262236;0.172746;,
  0.262236;0.327254;,
  0.297746;0.103054;,
  0.737764;0.327254;,
  0.353054;0.047746;,
  0.422746;0.012236;,
  0.500000;-0.000000;,
  0.577254;0.012236;,
  0.646946;0.047746;,
  0.702254;0.103054;,
  0.737764;0.172746;,
  0.750000;0.250000;,
  0.250000;0.500000;,
  0.275000;0.500000;,
  0.339211;0.642691;,
  0.325752;0.651505;,
  0.300000;0.500000;,
  0.354149;0.635372;,
  0.325000;0.500000;,
  0.370679;0.630513;,
  0.350000;0.500000;,
  0.388642;0.628808;,
  0.375000;0.500000;,
  0.407628;0.630513;,
  0.400000;0.500000;,
  0.427074;0.635372;,
  0.425000;0.500000;,
  0.446404;0.642691;,
  0.450000;0.500000;,
  0.465151;0.651505;,
  0.475000;0.500000;,
  0.483039;0.660781;,
  0.500000;0.500000;,
  0.500000;0.666980;,
  0.700000;0.500000;,
  0.725000;0.500000;,
  0.652648;0.660781;,
  0.633208;0.666980;,
  0.750000;0.500000;,
  0.674247;0.651505;,
  0.262236;0.327254;,
  0.737764;0.172746;,
  0.750000;0.250000;,
  0.750000;0.250000;,
  0.737764;0.172746;,
  0.737764;0.327254;,
  0.737764;0.327254;,
  0.262236;0.327254;,
  0.250000;0.250000;,
  0.250000;0.250000;,
  0.262236;0.172746;,
  0.262236;0.172746;,
  0.297746;0.103054;,
  0.297746;0.103054;,
  0.353054;0.047746;,
  0.353054;0.047746;,
  0.422746;0.012236;,
  0.422746;0.012236;,
  0.500000;-0.000000;,
  0.500000;-0.000000;,
  0.577254;0.012236;,
  0.577254;0.012236;,
  0.646946;0.047746;,
  0.646946;0.047746;,
  0.702254;0.103054;,
  0.702254;0.103054;,
  0.750000;0.250000;,
  0.737764;0.172746;,
  0.737764;0.327254;,
  0.262236;0.327254;,
  0.250000;0.250000;,
  0.262236;0.172746;,
  0.297746;0.103054;,
  0.353054;0.047746;,
  0.422746;0.012236;,
  0.500000;-0.000000;,
  0.577254;0.012236;,
  0.646946;0.047746;,
  0.702254;0.103054;,
  0.750000;0.250000;,
  0.737764;0.172746;,
  0.737764;0.327254;,
  0.262236;0.327254;,
  0.250000;0.250000;,
  0.262236;0.172746;,
  0.297746;0.103054;,
  0.353054;0.047746;,
  0.422746;0.012236;,
  0.500000;-0.000000;,
  0.577254;0.012236;,
  0.646946;0.047746;,
  0.702254;0.103054;;
 }
}
