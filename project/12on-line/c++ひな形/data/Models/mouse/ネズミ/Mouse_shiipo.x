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
 109;
 -3.74146;0.50853;8.56553;,
 1.30189;-0.29691;9.38804;,
 1.17703;17.87064;50.49107;,
 -3.47810;18.33281;49.53410;,
 5.34633;1.95998;7.08409;,
 4.91017;19.16540;47.81012;,
 5.34633;5.57973;3.38816;,
 4.91017;21.24198;43.51036;,
 1.30189;7.83667;1.08395;,
 1.17703;22.53673;40.82973;,
 -3.74146;7.03120;1.90634;,
 -3.47810;22.07463;41.78646;,
 -5.98596;3.76992;5.23619;,
 -5.54984;20.20373;45.66026;,
 -3.74146;0.50853;8.56553;,
 -3.47810;18.33281;49.53410;,
 1.02232;51.17746;68.82066;,
 -3.15164;51.45712;67.91011;,
 4.36958;51.96114;66.26906;,
 4.36958;53.21802;62.17640;,
 1.02232;54.00168;59.62470;,
 -3.15164;53.72198;60.53528;,
 -5.00921;52.58953;64.22269;,
 -3.15164;51.45712;67.91011;,
 0.84748;84.58001;78.42351;,
 -2.78276;84.82324;77.63115;,
 3.75875;85.26157;76.20427;,
 3.75875;86.35471;72.64470;,
 0.84748;87.03625;70.42528;,
 -2.78276;86.79306;71.21739;,
 -4.39838;85.80812;74.42418;,
 -2.78276;84.82324;77.63115;,
 0.66364;112.03204;91.53906;,
 -2.39487;112.30730;90.89771;,
 3.11639;112.80334;89.74158;,
 3.11639;114.04047;86.85840;,
 0.66364;114.81182;85.06139;,
 -2.39487;114.53658;85.70319;,
 -3.75602;113.42181;88.30022;,
 -2.39487;112.30730;90.89771;,
 0.48242;127.77259;114.16815;,
 -2.01248;128.10101;113.70288;,
 2.48320;128.69229;112.86414;,
 2.48320;130.16766;110.77319;,
 0.48242;131.08752;109.46967;,
 -2.01248;130.75919;109.93481;,
 -3.12283;129.43005;111.81842;,
 -2.01248;128.10101;113.70288;,
 0.31531;133.31644;137.59430;,
 -1.65988;133.63855;137.27679;,
 1.89927;134.21582;136.70709;,
 1.89927;135.65854;135.28491;,
 0.31531;136.55804;134.39801;,
 -1.65988;136.23822;134.71375;,
 -2.53894;134.93842;135.99536;,
 -1.65988;133.63855;137.27679;,
 0.17286;134.99820;155.00739;,
 -1.35937;135.27203;154.78967;,
 1.40166;135.76550;154.39801;,
 1.40166;136.99625;153.42047;,
 0.17286;137.76358;152.81067;,
 -1.35937;137.48969;153.02844;,
 -2.04129;136.38086;153.90906;,
 -1.35937;135.27203;154.78967;,
 0.06415;136.28976;165.96204;,
 -1.13001;136.51193;165.80396;,
 1.02180;136.91205;165.51910;,
 1.02180;137.90994;164.80884;,
 0.06415;138.53217;164.36615;,
 -1.13001;138.31015;164.52423;,
 -1.66146;137.41113;165.16418;,
 -1.13001;136.51193;165.80396;,
 -0.00395;137.61551;172.45786;,
 -0.98628;137.80109;172.33243;,
 0.78382;138.13577;172.10617;,
 0.78382;138.97043;171.54105;,
 -0.00395;139.49066;171.18918;,
 -0.98628;139.30502;171.31467;,
 -1.42346;138.55304;171.82388;,
 -0.98628;137.80109;172.33243;,
 -0.02713;138.84247;176.76828;,
 -0.93735;139.01584;176.65359;,
 0.70280;139.32831;176.44754;,
 0.70280;140.10745;175.93338;,
 -0.02713;140.59338;175.61258;,
 -0.93735;140.41989;175.72672;,
 -1.34243;139.71786;176.19046;,
 -0.93735;139.01584;176.65359;,
 3.01695;1.81263;-1.71272;,
 3.01695;-0.31905;0.46349;,
 0.63519;3.14180;-3.06982;,
 0.63519;-1.64811;1.82040;,
 -2.07187;2.66740;-2.58534;,
 -2.07187;-1.17378;1.33609;,
 -3.39362;0.74682;-0.62458;,
 0.70280;139.32831;176.44754;,
 0.70280;140.10745;175.93338;,
 -0.02713;138.84247;176.76828;,
 -0.02713;140.59338;175.61258;,
 -0.93735;139.01584;176.65359;,
 -0.93735;140.41989;175.72672;,
 -1.34243;139.71786;176.19046;,
 -3.74146;0.50853;8.56553;,
 -5.98596;3.76992;5.23619;,
 -3.74146;7.03120;1.90634;,
 1.30189;7.83667;1.08395;,
 5.34633;5.57973;3.38816;,
 5.34633;1.95998;7.08409;,
 1.30189;-0.29691;9.38804;;
 
 87;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;3,2,16,17;,
 4;2,5,18,16;,
 4;5,7,19,18;,
 4;7,9,20,19;,
 4;9,11,21,20;,
 4;11,13,22,21;,
 4;13,15,23,22;,
 4;17,16,24,25;,
 4;16,18,26,24;,
 4;18,19,27,26;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;25,24,32,33;,
 4;24,26,34,32;,
 4;26,27,35,34;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;33,32,40,41;,
 4;32,34,42,40;,
 4;34,35,43,42;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;41,40,48,49;,
 4;40,42,50,48;,
 4;42,43,51,50;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;49,48,56,57;,
 4;48,50,58,56;,
 4;50,51,59,58;,
 4;51,52,60,59;,
 4;52,53,61,60;,
 4;53,54,62,61;,
 4;54,55,63,62;,
 4;57,56,64,65;,
 4;56,58,66,64;,
 4;58,59,67,66;,
 4;59,60,68,67;,
 4;60,61,69,68;,
 4;61,62,70,69;,
 4;62,63,71,70;,
 4;65,64,72,73;,
 4;64,66,74,72;,
 4;66,67,75,74;,
 4;67,68,76,75;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;73,72,80,81;,
 4;72,74,82,80;,
 4;74,75,83,82;,
 4;75,76,84,83;,
 4;76,77,85,84;,
 4;77,78,86,85;,
 4;78,79,87,86;,
 3;88,89,90;,
 3;89,91,90;,
 3;90,91,92;,
 3;91,93,92;,
 3;93,94,92;,
 3;95,96,97;,
 3;96,98,97;,
 3;97,98,99;,
 3;98,100,99;,
 3;100,101,99;,
 4;102,103,94,93;,
 4;103,104,92,94;,
 4;104,105,90,92;,
 4;105,106,88,90;,
 4;106,107,89,88;,
 4;107,108,91,89;,
 4;108,102,93,91;;
 
 MeshMaterialList {
  8;
  87;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "2017-03-13-14-35-07.png";
   }
  }
  Material {
   0.400000;0.272000;0.392000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "2017-03-13-14-35-07.png";
   }
  }
  Material {
   0.400000;0.272000;0.392000;1.000000;;
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
 }
 MeshNormals {
  101;
  -0.563177;-0.801484;0.201131;,
  0.191473;-0.941967;0.275745;,
  0.852644;-0.519457;0.056242;,
  0.895367;0.292991;-0.335371;,
  0.211557;0.800822;-0.560292;,
  -0.613062;0.624860;-0.483430;,
  -0.890836;0.314801;-0.327583;,
  -0.622191;-0.581105;0.524590;,
  0.221208;-0.722948;0.654532;,
  0.902074;-0.316333;0.293592;,
  0.898280;0.344998;-0.272158;,
  0.218998;0.752937;-0.620586;,
  -0.617784;0.609190;-0.497222;,
  -0.980609;0.185691;-0.062650;,
  -0.624644;-0.295115;0.722999;,
  0.223120;-0.371343;0.901289;,
  0.901596;-0.155548;0.403646;,
  0.900711;0.189436;-0.390941;,
  0.222654;0.404749;-0.886907;,
  -0.623639;0.326944;-0.710058;,
  -0.999866;0.015386;0.005544;,
  -0.624190;-0.273287;0.731916;,
  0.222883;-0.344781;0.911838;,
  0.901302;-0.141877;0.409300;,
  0.900586;0.181113;-0.395150;,
  0.222466;0.381439;-0.897225;,
  -0.623356;0.308946;-0.718317;,
  -0.999818;0.017987;0.006323;,
  -0.623227;-0.504158;0.597840;,
  0.221998;-0.631557;0.742868;,
  0.902018;-0.269533;0.337219;,
  0.897645;0.307810;-0.315415;,
  0.219468;0.657161;-0.721091;,
  -0.618110;0.533347;-0.577478;,
  -0.999782;0.018441;0.009792;,
  -0.592199;-0.733715;0.333111;,
  0.204296;-0.893210;0.400549;,
  0.890050;-0.409822;0.199640;,
  0.881186;0.441815;-0.168260;,
  0.200735;0.903469;-0.378746;,
  -0.583290;0.751216;-0.308946;,
  -0.999747;0.016794;0.014933;,
  -0.574350;-0.806326;0.141282;,
  0.194568;-0.967187;0.163381;,
  0.882776;-0.460121;0.094844;,
  0.870570;0.489377;-0.051154;,
  0.190103;0.972502;-0.134543;,
  -0.562421;0.819689;-0.108595;,
  -0.849441;0.524229;-0.060272;,
  -0.582865;-0.807084;0.094257;,
  0.199311;-0.974071;0.107056;,
  0.886592;-0.457179;0.070299;,
  0.872625;0.488253;-0.011604;,
  0.193377;0.979174;-0.061831;,
  -0.568672;0.821247;-0.046538;,
  -0.855363;0.517672;-0.019241;,
  -0.598648;-0.789589;0.134795;,
  0.208183;-0.965332;0.157463;,
  0.892899;-0.440285;0.094234;,
  0.880102;0.474064;-0.026129;,
  0.201982;0.974475;-0.097985;,
  -0.585073;0.807477;-0.075301;,
  -0.999330;0.018320;0.031680;,
  -0.609265;-0.768928;0.193765;,
  0.214348;-0.948503;0.233233;,
  0.896287;-0.426273;0.122316;,
  0.888863;0.452801;-0.069953;,
  0.210491;0.960042;-0.184427;,
  -0.601152;0.785637;-0.146257;,
  -0.999617;0.013757;0.024007;,
  -0.612537;-0.759107;0.220352;,
  0.216308;-0.938670;0.268531;,
  0.897048;-0.421626;0.132423;,
  0.892830;0.439720;-0.097474;,
  0.214084;0.948116;-0.235040;,
  -0.607913;0.771393;-0.188134;,
  -0.999831;0.009177;0.015923;,
  -0.000026;-0.714379;-0.699759;,
  -0.071614;-0.889145;-0.451988;,
  -0.000015;-0.714385;-0.699753;,
  0.000003;-0.714390;-0.699748;,
  0.000052;-0.714377;-0.699761;,
  0.198350;-0.851309;-0.485726;,
  0.077172;-0.906166;-0.415822;,
  -0.842821;-0.532531;0.077872;,
  -0.867204;-0.456078;0.199875;,
  -0.862629;-0.496515;0.096665;,
  -0.870346;-0.487784;0.067554;,
  0.000151;0.550786;0.834646;,
  0.000042;0.550830;0.834617;,
  -0.000049;0.550845;0.834608;,
  -0.000220;0.550892;0.834577;,
  0.000012;0.550910;0.834565;,
  0.000133;0.550927;0.834553;,
  0.000629;0.550927;0.834553;,
  -0.926126;-0.254634;-0.278301;,
  -0.800465;-0.597628;-0.045793;,
  -0.616746;0.441646;-0.651593;,
  0.215564;0.627705;-0.748010;,
  0.865708;0.122038;-0.485444;,
  0.937230;-0.249120;-0.244004;;
  87;
  4;0,1,8,7;,
  4;1,2,9,8;,
  4;2,3,10,9;,
  4;3,4,11,10;,
  4;4,5,12,11;,
  4;5,6,13,12;,
  4;84,0,7,85;,
  4;7,8,15,14;,
  4;8,9,16,15;,
  4;9,10,17,16;,
  4;10,11,18,17;,
  4;11,12,19,18;,
  4;12,13,20,19;,
  4;13,7,14,20;,
  4;14,15,22,21;,
  4;15,16,23,22;,
  4;16,17,24,23;,
  4;17,18,25,24;,
  4;18,19,26,25;,
  4;19,20,27,26;,
  4;20,14,21,27;,
  4;21,22,29,28;,
  4;22,23,30,29;,
  4;23,24,31,30;,
  4;24,25,32,31;,
  4;25,26,33,32;,
  4;26,27,34,33;,
  4;27,21,28,34;,
  4;28,29,36,35;,
  4;29,30,37,36;,
  4;30,31,38,37;,
  4;31,32,39,38;,
  4;32,33,40,39;,
  4;33,34,41,40;,
  4;34,28,35,41;,
  4;35,36,43,42;,
  4;36,37,44,43;,
  4;37,38,45,44;,
  4;38,39,46,45;,
  4;39,40,47,46;,
  4;40,41,48,47;,
  4;41,35,42,86;,
  4;42,43,50,49;,
  4;43,44,51,50;,
  4;44,45,52,51;,
  4;45,46,53,52;,
  4;46,47,54,53;,
  4;47,48,55,54;,
  4;86,42,49,87;,
  4;49,50,57,56;,
  4;50,51,58,57;,
  4;51,52,59,58;,
  4;52,53,60,59;,
  4;53,54,61,60;,
  4;54,55,62,61;,
  4;87,49,56,62;,
  4;56,57,64,63;,
  4;57,58,65,64;,
  4;58,59,66,65;,
  4;59,60,67,66;,
  4;60,61,68,67;,
  4;61,62,69,68;,
  4;62,56,63,69;,
  4;63,64,71,70;,
  4;64,65,72,71;,
  4;65,66,73,72;,
  4;66,67,74,73;,
  4;67,68,75,74;,
  4;68,69,76,75;,
  4;69,63,70,76;,
  3;81,82,80;,
  3;82,83,80;,
  3;80,83,79;,
  3;83,78,79;,
  3;78,77,79;,
  3;88,89,90;,
  3;89,91,90;,
  3;90,91,92;,
  3;91,93,92;,
  3;93,94,92;,
  4;0,84,95,96;,
  4;6,5,97,95;,
  4;5,4,98,97;,
  4;4,3,99,98;,
  4;3,2,100,99;,
  4;2,1,83,82;,
  4;1,0,78,83;;
 }
 MeshTextureCoords {
  109;
  0.375000;0.312500;,
  0.410710;0.312500;,
  0.410710;0.350090;,
  0.375000;0.350090;,
  0.446430;0.312500;,
  0.446430;0.350090;,
  0.482140;0.312500;,
  0.482140;0.350090;,
  0.517860;0.312500;,
  0.517860;0.350090;,
  0.553570;0.312500;,
  0.553570;0.350090;,
  0.589290;0.312500;,
  0.589290;0.350090;,
  0.625000;0.312500;,
  0.625000;0.350090;,
  0.410710;0.387690;,
  0.375000;0.387690;,
  0.446430;0.387690;,
  0.482140;0.387690;,
  0.517860;0.387690;,
  0.553570;0.387690;,
  0.589290;0.387690;,
  0.625000;0.387690;,
  0.410710;0.425280;,
  0.375000;0.425280;,
  0.446430;0.425280;,
  0.482140;0.425280;,
  0.517860;0.425280;,
  0.553570;0.425280;,
  0.589290;0.425280;,
  0.625000;0.425280;,
  0.410710;0.462880;,
  0.375000;0.462880;,
  0.446430;0.462880;,
  0.482140;0.462880;,
  0.517860;0.462880;,
  0.553570;0.462880;,
  0.589290;0.462880;,
  0.625000;0.462880;,
  0.410710;0.500470;,
  0.375000;0.500470;,
  0.446430;0.500470;,
  0.482140;0.500470;,
  0.517860;0.500470;,
  0.553570;0.500470;,
  0.589290;0.500470;,
  0.625000;0.500470;,
  0.410710;0.538060;,
  0.375000;0.538060;,
  0.446430;0.538060;,
  0.482140;0.538060;,
  0.517860;0.538060;,
  0.553570;0.538060;,
  0.589290;0.538060;,
  0.625000;0.538060;,
  0.410710;0.575660;,
  0.375000;0.575660;,
  0.446430;0.575660;,
  0.482140;0.575660;,
  0.517860;0.575660;,
  0.553570;0.575660;,
  0.589290;0.575660;,
  0.625000;0.575660;,
  0.410710;0.613250;,
  0.375000;0.613250;,
  0.446430;0.613250;,
  0.482140;0.613250;,
  0.517860;0.613250;,
  0.553570;0.613250;,
  0.589290;0.613250;,
  0.625000;0.613250;,
  0.410710;0.650850;,
  0.375000;0.650850;,
  0.446430;0.650850;,
  0.482140;0.650850;,
  0.517860;0.650850;,
  0.553570;0.650850;,
  0.589290;0.650850;,
  0.625000;0.650850;,
  0.410710;0.688440;,
  0.375000;0.688440;,
  0.446430;0.688440;,
  0.482140;0.688440;,
  0.517860;0.688440;,
  0.553570;0.688440;,
  0.589290;0.688440;,
  0.625000;0.688440;,
  0.359220;0.224040;,
  0.359220;0.088460;,
  0.465230;0.308580;,
  0.465230;0.003920;,
  0.597420;0.278410;,
  0.597420;0.034090;,
  0.656250;0.156250;,
  0.359220;0.911540;,
  0.359220;0.775960;,
  0.465230;0.996080;,
  0.465230;0.691420;,
  0.597420;0.965910;,
  0.597420;0.721590;,
  0.656250;0.843750;,
  0.597420;0.034090;,
  0.656250;0.156250;,
  0.597420;0.278410;,
  0.465230;0.308580;,
  0.359220;0.224040;,
  0.359220;0.088460;,
  0.465230;0.003920;;
 }
}
