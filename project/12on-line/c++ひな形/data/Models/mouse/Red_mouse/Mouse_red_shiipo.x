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
 110;
 -1.59800;-0.44777;-0.05098;,
 -1.01572;-0.84770;0.47060;,
 -0.81561;6.69974;11.33609;,
 -1.27871;7.04961;11.04863;,
 -0.19470;-1.03717;0.71768;,
 -0.15673;6.52010;11.44029;,
 0.67698;-0.97276;0.63370;,
 0.54501;6.55544;11.33918;,
 1.32847;0.40831;0.98616;,
 1.09260;6.81602;11.04310;,
 1.71578;0.85738;0.40055;,
 1.40718;7.18402;10.69307;,
 1.80771;0.33817;-1.07601;,
 1.44349;7.63306;10.22646;,
 1.39964;0.81126;-1.69303;,
 1.11341;8.02252;9.88616;,
 0.67698;1.11479;-2.08881;,
 0.53698;8.28090;9.68277;,
 -0.19470;1.17919;-2.17280;,
 -0.15427;8.34988;9.67524;,
 -1.01572;0.98972;-1.92570;,
 -0.80506;8.21457;9.86960;,
 -1.59800;0.58981;-1.40415;,
 -1.26935;7.90399;10.22187;,
 -1.80813;0.07101;-0.72757;,
 -1.44122;7.48546;10.64321;,
 -1.59800;-0.44777;-0.05098;,
 -1.27871;7.04961;11.04863;,
 1.80771;0.33817;-1.07601;,
 1.71578;0.85738;0.40055;,
 1.39964;0.81126;-1.69303;,
 1.32847;0.40831;0.98616;,
 0.67698;1.11479;-2.08881;,
 0.67698;-0.97276;0.63370;,
 -0.19470;1.17919;-2.17280;,
 -0.19470;-1.03717;0.71768;,
 -1.01572;0.98972;-1.92570;,
 -1.01572;-0.84770;0.47060;,
 -1.59800;0.58981;-1.40415;,
 -1.59800;-0.44777;-0.05098;,
 -1.80813;0.07101;-0.72757;,
 0.34485;27.71823;30.43200;,
 0.34485;27.83743;30.31419;,
 0.26695;27.61268;30.53631;,
 0.26698;27.94289;30.20984;,
 0.12903;28.01061;30.14286;,
 0.12903;27.54502;30.60334;,
 -0.03734;27.53061;30.61747;,
 -0.03734;28.02497;30.12864;,
 -0.19403;27.57290;30.57570;,
 -0.19403;27.98269;30.17044;,
 -0.30517;27.66213;30.48748;,
 -0.30517;27.89349;30.25868;,
 -0.34530;27.77780;30.37301;,
 -0.60125;19.45890;22.41719;,
 -0.38156;19.31265;22.61949;,
 -0.19403;27.57290;30.57570;,
 -0.30517;27.66213;30.48748;,
 -0.07310;19.26677;22.73719;,
 -0.03734;27.53061;30.61747;,
 0.25298;19.33113;22.74394;,
 0.12903;27.54502;30.60334;,
 0.51272;19.49512;22.63159;,
 0.26695;27.61268;30.53631;,
 0.66180;19.70885;22.44235;,
 0.34485;27.71823;30.43200;,
 0.67443;19.93489;22.20942;,
 0.34485;27.83743;30.31419;,
 0.52287;20.11945;21.98248;,
 0.26698;27.94289;30.20984;,
 0.25336;20.21967;21.81697;,
 0.12903;28.01061;30.14286;,
 -0.07321;20.21217;21.75076;,
 -0.03734;28.02497;30.12864;,
 -0.38205;20.09803;21.79994;,
 -0.19403;27.98269;30.17044;,
 -0.60168;19.90300;21.95372;,
 -0.30517;27.89349;30.25868;,
 -0.68092;19.67212;22.17671;,
 -0.34530;27.77780;30.37301;,
 -0.60125;19.45890;22.41719;,
 -0.30517;27.66213;30.48748;,
 -1.03658;13.92465;11.53465;,
 -0.65921;13.64243;11.81498;,
 -0.50982;19.49865;14.25738;,
 -0.80225;19.79511;14.11705;,
 -0.12645;13.52453;11.92365;,
 -0.09773;19.36802;14.34628;,
 0.43917;13.57889;11.87986;,
 0.33885;19.43635;14.36144;,
 0.88334;13.82168;11.66159;,
 0.68330;19.70111;14.28897;,
 1.14005;14.16026;11.33582;,
 0.88143;20.07467;14.16067;,
 1.17030;14.53753;10.97818;,
 0.90172;20.47471;14.00900;,
 0.90554;14.85972;10.66521;,
 0.69808;20.82352;13.85820;,
 0.43781;15.06360;10.45536;,
 0.33780;21.03946;13.74356;,
 -0.12601;15.10726;10.40246;,
 -0.09741;21.07021;13.69226;,
 -0.65741;14.95987;10.54021;,
 -0.50843;20.90610;13.71872;,
 -1.03496;14.65802;10.83416;,
 -0.80101;20.58894;13.81515;,
 -1.17200;14.28934;11.18719;,
 -0.90730;20.19271;13.95807;,
 -1.03658;13.92465;11.53465;,
 -0.80225;19.79511;14.11705;;
 
 87;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 3;28,29,30;,
 3;29,31,30;,
 3;30,31,32;,
 3;31,33,32;,
 3;32,33,34;,
 3;33,35,34;,
 3;34,35,36;,
 3;35,37,36;,
 3;36,37,38;,
 3;37,39,38;,
 3;39,40,38;,
 3;41,42,43;,
 3;42,44,43;,
 3;44,45,43;,
 3;43,45,46;,
 3;46,45,47;,
 3;45,48,47;,
 3;47,48,49;,
 3;48,50,49;,
 3;49,50,51;,
 3;50,52,51;,
 3;52,53,51;,
 4;54,55,56,57;,
 4;55,58,59,56;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 4;64,66,67,65;,
 4;66,68,69,67;,
 4;68,70,71,69;,
 4;70,72,73,71;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 4;82,83,84,85;,
 4;83,86,87,84;,
 4;86,88,89,87;,
 4;88,90,91,89;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,100,101,99;,
 4;100,102,103,101;,
 4;102,104,105,103;,
 4;104,106,107,105;,
 4;106,108,109,107;,
 4;85,84,55,54;,
 4;84,87,58,55;,
 4;87,89,60,58;,
 4;89,91,62,60;,
 4;91,93,64,62;,
 4;93,95,66,64;,
 4;95,97,68,66;,
 4;97,99,70,68;,
 4;99,101,72,70;,
 4;101,103,74,72;,
 4;103,105,76,74;,
 4;105,107,78,76;,
 4;107,109,80,78;,
 4;3,2,83,82;,
 4;2,5,86,83;,
 4;5,7,88,86;,
 4;7,9,90,88;,
 4;9,11,92,90;,
 4;11,13,94,92;,
 4;13,15,96,94;,
 4;15,17,98,96;,
 4;17,19,100,98;,
 4;19,21,102,100;,
 4;21,23,104,102;,
 4;23,25,106,104;,
 4;25,27,108,106;;
 
 MeshMaterialList {
  7;
  87;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
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
   0.800000;0.000000;0.000000;1.000000;;
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
  110;
  -0.870362;-0.395707;0.293064;,
  -0.532890;-0.690285;0.489423;,
  -0.102942;-0.813140;0.572892;,
  0.672808;-0.686632;0.275438;,
  0.832226;-0.547638;0.086564;,
  0.900723;-0.423808;0.095313;,
  0.974327;0.202164;-0.099078;,
  0.705805;0.608896;-0.362057;,
  0.316778;0.811571;-0.490922;,
  -0.114017;0.849809;-0.514612;,
  -0.530252;0.726958;-0.436310;,
  -0.861990;0.439735;-0.252202;,
  -0.999553;0.024648;0.016942;,
  -0.000345;0.703168;0.711024;,
  0.000125;0.703148;0.711044;,
  -0.000120;0.703137;0.711055;,
  0.000000;0.703189;0.711003;,
  -0.000093;0.703074;0.711116;,
  -0.000042;0.702952;0.711237;,
  -0.000402;0.703015;0.711175;,
  -0.000430;0.703078;0.711112;,
  -0.000046;0.703142;0.711050;,
  0.000037;0.703129;0.711062;,
  0.000096;0.703167;0.711025;,
  -0.000609;0.703168;0.711023;,
  -0.001383;0.703168;0.711023;,
  -0.877817;-0.444344;0.178873;,
  -0.537943;-0.782655;0.313159;,
  -0.078650;-0.920262;0.383317;,
  0.401064;-0.843471;0.357358;,
  0.769949;-0.587738;0.248481;,
  0.969073;-0.222950;0.105789;,
  0.968601;0.243928;-0.048081;,
  0.716539;0.670647;-0.191846;,
  0.305666;0.906508;-0.291225;,
  -0.161023;0.936370;-0.311902;,
  -0.580786;0.775805;-0.246605;,
  -0.880860;0.457169;-0.122805;,
  -0.999539;0.016604;0.025436;,
  -0.814366;-0.106716;0.570457;,
  -0.446955;-0.192901;0.873510;,
  -0.075510;-0.227913;0.970749;,
  0.301515;-0.221245;0.927437;,
  0.667416;-0.163913;0.726422;,
  0.934658;-0.055818;0.351139;,
  0.967249;0.105275;-0.230970;,
  0.663717;0.235282;-0.710015;,
  0.287174;0.291233;-0.912532;,
  -0.101909;0.299331;-0.948691;,
  -0.496531;0.261710;-0.827626;,
  -0.844067;0.172721;-0.507660;,
  -0.998868;0.032796;0.034455;,
  -0.876201;-0.396528;0.273928;,
  -0.534412;-0.708435;0.461003;,
  -0.109494;-0.381003;0.918067;,
  0.291355;-0.370171;0.882091;,
  0.767455;-0.525792;0.366819;,
  0.964727;-0.201638;0.169247;,
  0.971670;0.224710;-0.073229;,
  0.719404;0.626896;-0.299098;,
  0.323520;0.459642;-0.827082;,
  -0.083642;0.480497;-0.872999;,
  -0.620586;0.581918;-0.525590;,
  -0.883258;0.422984;-0.202336;,
  -0.999213;0.020916;0.033716;,
  -0.856310;-0.214117;0.469986;,
  -0.504443;-0.402826;0.763720;,
  -0.078687;-0.485814;0.870513;,
  0.402628;-0.434897;0.805454;,
  0.755902;-0.293800;0.585059;,
  0.949715;-0.127542;0.285962;,
  0.973346;0.135884;-0.184749;,
  0.700552;0.379023;-0.604623;,
  0.307396;0.508689;-0.804204;,
  -0.128143;0.531613;-0.837238;,
  -0.546274;0.445903;-0.709052;,
  -0.869521;0.267361;-0.415272;,
  -0.999241;0.030486;0.024244;,
  -0.831623;-0.538067;0.137431;,
  -0.612481;-0.790460;-0.006408;,
  0.693885;-0.714560;-0.089037;,
  -0.312237;-0.938183;-0.149398;,
  -0.162967;-0.903863;-0.395568;,
  0.895443;-0.353276;-0.270884;,
  0.000006;-0.793564;-0.608487;,
  0.000006;-0.793563;-0.608488;,
  -0.000001;-0.793564;-0.608487;,
  -0.000004;-0.793565;-0.608485;,
  -0.000001;-0.793565;-0.608485;,
  0.000016;-0.793564;-0.608486;,
  0.000025;-0.793564;-0.608487;,
  0.000036;-0.793564;-0.608487;,
  -0.567847;-0.564307;0.599255;,
  -0.885078;-0.309795;0.347369;,
  -0.120531;-0.684807;0.718687;,
  0.363366;-0.641423;0.675679;,
  0.754527;-0.445874;0.481545;,
  0.968197;-0.156332;0.195335;,
  0.972767;0.184311;-0.140550;,
  0.748186;0.492276;-0.444840;,
  0.354503;0.685390;-0.636056;,
  -0.120450;0.726273;-0.676771;,
  -0.567895;0.605476;-0.557579;,
  -0.885075;0.350797;-0.305914;,
  -0.999576;0.020488;0.020672;,
  -0.024012;-0.999627;-0.012997;,
  0.381602;-0.924283;-0.008971;,
  0.205999;0.973503;0.099284;,
  -0.172835;0.979557;0.102939;,
  -0.347286;0.932478;0.099379;;
  87;
  4;0,1,66,65;,
  4;1,2,67,66;,
  4;2,3,68,67;,
  4;3,4,69,68;,
  4;4,5,70,69;,
  4;5,6,71,70;,
  4;6,7,72,71;,
  4;7,8,73,72;,
  4;8,9,74,73;,
  4;9,10,75,74;,
  4;10,11,76,75;,
  4;11,12,77,76;,
  4;12,0,65,77;,
  3;78,78,79;,
  3;5,4,80;,
  3;79,81,82;,
  3;4,3,83;,
  3;82,84,85;,
  3;84,86,85;,
  3;85,86,87;,
  3;86,88,87;,
  3;87,88,89;,
  3;88,90,89;,
  3;90,91,89;,
  3;18,19,17;,
  3;19,20,17;,
  3;20,21,17;,
  3;17,21,16;,
  3;16,21,15;,
  3;21,22,15;,
  3;15,22,14;,
  3;22,23,14;,
  3;14,23,13;,
  3;23,24,13;,
  3;24,25,13;,
  4;26,27,92,93;,
  4;27,28,94,92;,
  4;28,29,95,94;,
  4;29,30,96,95;,
  4;30,31,97,96;,
  4;31,32,98,97;,
  4;32,33,99,98;,
  4;33,34,100,99;,
  4;34,35,101,100;,
  4;35,36,102,101;,
  4;36,37,103,102;,
  4;37,38,104,103;,
  4;38,26,93,104;,
  4;39,40,53,52;,
  4;40,41,54,53;,
  4;41,42,55,54;,
  4;42,43,56,55;,
  4;43,44,57,56;,
  4;44,45,58,57;,
  4;45,46,59,58;,
  4;46,47,60,59;,
  4;47,48,61,60;,
  4;48,49,62,61;,
  4;49,50,63,62;,
  4;50,51,64,63;,
  4;51,39,52,64;,
  4;52,53,27,26;,
  4;53,105,28,27;,
  4;105,106,29,28;,
  4;106,56,30,29;,
  4;56,57,31,30;,
  4;57,58,32,31;,
  4;58,59,33,32;,
  4;59,107,34,33;,
  4;107,108,35,34;,
  4;108,109,36,35;,
  4;62,63,37,36;,
  4;63,64,38,37;,
  4;64,52,26,38;,
  4;65,66,40,39;,
  4;66,67,41,40;,
  4;67,68,42,41;,
  4;68,69,43,42;,
  4;69,70,44,43;,
  4;70,71,45,44;,
  4;71,72,46,45;,
  4;72,73,47,46;,
  4;73,74,48,47;,
  4;74,75,49,48;,
  4;75,76,50,49;,
  4;76,77,51,50;,
  4;77,65,39,51;;
 }
 MeshTextureCoords {
  110;
  0.375000;0.312500;,
  0.394231;0.312500;,
  0.394231;0.404056;,
  0.375000;0.405344;,
  0.413462;0.312500;,
  0.413462;0.403227;,
  0.432692;0.312500;,
  0.432692;0.403056;,
  0.451923;0.312500;,
  0.451923;0.396029;,
  0.471154;0.312500;,
  0.471154;0.397125;,
  0.490385;0.312500;,
  0.490385;0.406095;,
  0.509615;0.312500;,
  0.509615;0.407494;,
  0.528846;0.312500;,
  0.528846;0.408562;,
  0.548077;0.312500;,
  0.548077;0.409062;,
  0.567308;0.312500;,
  0.567308;0.408885;,
  0.586539;0.312500;,
  0.586539;0.408068;,
  0.605769;0.312500;,
  0.605769;0.406792;,
  0.625000;0.312500;,
  0.625000;0.405344;,
  0.348290;0.193643;,
  0.348290;0.118857;,
  0.383045;0.259863;,
  0.383045;0.052637;,
  0.444593;0.302346;,
  0.444593;0.010154;,
  0.518834;0.311361;,
  0.518834;0.001139;,
  0.588760;0.284841;,
  0.588760;0.027659;,
  0.638353;0.228863;,
  0.638353;0.083637;,
  0.656250;0.156250;,
  0.348290;0.881143;,
  0.348290;0.806357;,
  0.383045;0.947363;,
  0.383045;0.740137;,
  0.444593;0.697654;,
  0.444593;0.989846;,
  0.518834;0.998861;,
  0.518834;0.688639;,
  0.588760;0.972341;,
  0.588760;0.715159;,
  0.638353;0.916363;,
  0.638353;0.771137;,
  0.656250;0.843750;,
  0.375000;0.602344;,
  0.394231;0.602651;,
  0.394231;0.688440;,
  0.375000;0.688440;,
  0.413462;0.603036;,
  0.413462;0.688440;,
  0.432692;0.603410;,
  0.432692;0.688440;,
  0.451923;0.601405;,
  0.451923;0.688440;,
  0.471154;0.601526;,
  0.471154;0.688440;,
  0.490385;0.603743;,
  0.490385;0.688440;,
  0.509615;0.603507;,
  0.509615;0.688440;,
  0.528846;0.603153;,
  0.528846;0.688440;,
  0.548077;0.602762;,
  0.548077;0.688440;,
  0.567308;0.602423;,
  0.567308;0.688440;,
  0.586539;0.602215;,
  0.586539;0.688440;,
  0.605769;0.602186;,
  0.605769;0.688440;,
  0.625000;0.602344;,
  0.625000;0.688440;,
  0.375000;0.475757;,
  0.394231;0.475611;,
  0.394231;0.543959;,
  0.375000;0.543899;,
  0.413462;0.475573;,
  0.413462;0.544174;,
  0.432692;0.475653;,
  0.432692;0.544494;,
  0.451923;0.470144;,
  0.451923;0.540994;,
  0.471154;0.470380;,
  0.471154;0.541297;,
  0.490385;0.476307;,
  0.490385;0.545331;,
  0.509615;0.476495;,
  0.509615;0.545355;,
  0.528846;0.476589;,
  0.528846;0.545215;,
  0.548077;0.476568;,
  0.548077;0.544942;,
  0.567308;0.476436;,
  0.567308;0.544597;,
  0.586539;0.476223;,
  0.586539;0.544259;,
  0.605769;0.475978;,
  0.605769;0.544007;,
  0.625000;0.475757;,
  0.625000;0.543899;;
 }
}
