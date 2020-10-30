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
 79;
 31.37447;-157.79088;2.99659;,
 32.82837;-132.11908;-24.27387;,
 41.41751;-123.65405;1.15565;,
 38.11302;-149.00294;19.52779;,
 15.10472;-161.43227;-3.85081;,
 12.09164;-135.62550;-34.80754;,
 -1.16391;-157.79088;2.99659;,
 -8.64509;-132.11908;-24.27387;,
 -7.90253;-149.00294;19.52779;,
 -17.23409;-123.65405;1.15565;,
 -1.16391;-140.21494;36.05780;,
 -8.64509;-117.63895;29.69830;,
 15.10472;-136.57472;42.90527;,
 12.09164;-114.13361;40.23190;,
 31.37447;-140.21494;36.05780;,
 32.82837;-117.63895;29.69830;,
 38.11302;-149.00294;19.52779;,
 41.41751;-123.65405;1.15565;,
 47.73501;-98.30515;-17.21535;,
 37.29549;-106.44608;-51.54433;,
 37.29549;-83.07416;-57.64792;,
 47.73501;-81.74773;-22.08511;,
 12.09164;-109.81867;-65.76418;,
 12.09164;-72.10278;-72.37862;,
 -13.11214;-106.44608;-51.54545;,
 -13.11214;-69.50984;-57.64792;,
 -23.55166;-98.30515;-17.21535;,
 -23.55166;-71.56293;-22.08511;,
 -13.11214;-95.06402;23.33873;,
 -13.11214;-73.61604;24.31985;,
 12.09164;-91.57032;39.33828;,
 12.09164;-74.46613;40.99979;,
 37.29549;-95.06402;23.33873;,
 37.29549;-79.04531;20.77911;,
 47.73501;-98.30515;-17.21535;,
 47.73501;-81.74773;-22.08511;,
 31.00200;-58.27665;-58.63680;,
 43.39963;-67.04612;-22.61557;,
 7.52750;-38.36735;-70.30255;,
 -12.90067;-34.46186;-55.25462;,
 -18.72215;-34.13544;-13.23592;,
 -8.59126;-39.20938;36.97668;,
 16.65676;-51.60174;48.89838;,
 37.45796;-64.28133;23.96109;,
 43.39963;-67.04612;-22.61557;,
 -6.85225;9.33139;-48.27050;,
 11.84181;7.62438;-66.16345;,
 -13.14385;10.74434;1.61506;,
 0.03246;5.76505;50.46156;,
 26.45991;-11.30914;63.59411;,
 4.01112;48.77531;-36.95144;,
 22.84168;63.36038;-54.08204;,
 -2.67843;51.88842;7.26476;,
 11.27845;42.01617;47.81548;,
 33.09472;27.97435;65.66142;,
 19.70981;72.38360;5.47634;,
 40.92527;-41.80568;45.99318;,
 32.77363;70.59467;48.35365;,
 42.84404;52.38437;62.85358;,
 31.93538;-28.77983;-54.41945;,
 35.24169;6.46651;-51.24740;,
 49.92538;-44.03762;-45.47926;,
 59.42648;-50.75817;-17.87392;,
 43.67165;49.18054;-41.98864;,
 54.87298;-48.63935;17.82076;,
 41.27149;56.09564;3.65465;,
 57.53018;-31.41490;34.70525;,
 51.28310;54.72470;36.51426;,
 46.44449;-8.04345;48.19398;,
 51.52922;22.06195;49.77835;,
 59.00067;40.76898;47.62648;,
 30.84912;-158.10735;19.52757;,
 26.23801;-152.09383;30.83887;,
 26.23801;-164.12077;8.21551;,
 15.10486;-149.60291;35.52446;,
 15.10486;-166.61256;3.52991;,
 3.97248;-152.09383;30.83887;,
 3.97248;-164.12077;8.21551;,
 -0.63863;-158.10735;19.52757;;
 
 80;
 4;0,1,2,3;,
 4;4,5,1,0;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;14,15,13,12;,
 4;16,17,15,14;,
 4;18,19,20,21;,
 4;19,22,23,20;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;21,20,36,37;,
 4;20,23,38,36;,
 4;23,25,39,38;,
 4;25,27,40,39;,
 4;27,29,41,40;,
 4;29,31,42,41;,
 4;31,33,43,42;,
 4;33,35,44,43;,
 4;38,39,45,46;,
 4;39,40,47,45;,
 4;40,41,48,47;,
 4;41,42,49,48;,
 4;45,50,51,46;,
 4;47,52,50,45;,
 4;47,48,53,52;,
 4;48,49,54,53;,
 4;52,55,51,50;,
 4;42,43,56,49;,
 4;57,53,54,58;,
 4;53,57,55,52;,
 4;1,19,18,2;,
 4;5,22,19,1;,
 4;24,22,5,7;,
 4;26,24,7,9;,
 4;28,26,9,11;,
 4;30,28,11,13;,
 4;15,32,30,13;,
 4;17,34,32,15;,
 3;59,60,61;,
 3;61,60,62;,
 3;60,63,62;,
 3;62,63,64;,
 3;63,65,64;,
 3;64,65,66;,
 3;65,67,66;,
 3;66,67,68;,
 3;68,67,69;,
 3;67,70,69;,
 4;37,36,61,62;,
 4;36,38,59,61;,
 4;38,46,60,59;,
 4;46,51,63,60;,
 4;51,55,65,63;,
 4;55,57,67,65;,
 4;57,58,70,67;,
 4;58,54,69,70;,
 4;54,49,68,69;,
 4;49,56,66,68;,
 4;56,43,64,66;,
 4;43,37,62,64;,
 3;71,72,73;,
 3;72,74,73;,
 3;73,74,75;,
 3;74,76,75;,
 3;75,76,77;,
 3;76,78,77;,
 4;16,14,72,71;,
 4;14,12,74,72;,
 4;12,10,76,74;,
 4;10,8,78,76;,
 4;8,6,77,78;,
 4;6,4,75,77;,
 4;4,0,73,75;,
 4;0,16,71,73;;
 
 MeshMaterialList {
  15;
  80;
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
  87;
  0.908849;-0.377070;0.178361;,
  0.682358;-0.633283;-0.365158;,
  0.003254;-0.792823;-0.609443;,
  -0.660235;-0.675436;-0.328444;,
  -0.863774;-0.457864;0.210371;,
  -0.616277;-0.293247;0.730896;,
  0.003843;-0.194542;0.980887;,
  0.649652;-0.212212;0.730013;,
  0.983211;-0.176036;0.048027;,
  0.720022;-0.543270;-0.431770;,
  0.003281;-0.765809;-0.643059;,
  -0.702555;-0.590384;-0.397319;,
  -0.960537;-0.265103;0.084197;,
  -0.756963;-0.018305;0.653201;,
  0.003852;0.122229;0.992494;,
  0.772197;0.068375;0.631694;,
  0.992500;-0.121425;0.014121;,
  0.995306;0.089846;-0.035959;,
  0.788979;0.025623;-0.613885;,
  0.765727;-0.366214;-0.528725;,
  -0.014081;-0.058130;-0.998210;,
  -0.009109;-0.513815;-0.857853;,
  -0.807370;-0.021600;-0.589650;,
  -0.774824;-0.347262;-0.528258;,
  -0.999451;0.031211;-0.011116;,
  -0.992164;-0.124405;0.011597;,
  -0.816972;-0.052124;0.574317;,
  -0.801807;-0.011775;0.597467;,
  -0.532189;-0.135282;0.835748;,
  -0.523390;0.010592;0.852027;,
  0.847235;-0.017552;0.530928;,
  0.808365;0.022460;0.588253;,
  0.957226;-0.269955;-0.104128;,
  0.751152;-0.034737;-0.659215;,
  0.527163;0.081196;-0.845876;,
  -0.842546;0.119197;-0.525270;,
  -0.994535;0.100806;0.027192;,
  -0.811753;-0.065414;0.580326;,
  -0.262109;-0.341127;0.902736;,
  0.732991;-0.443302;0.515953;,
  -0.660931;0.247372;-0.708504;,
  -0.859510;0.247448;-0.447227;,
  -0.978011;0.196015;0.071224;,
  -0.782720;0.075352;0.617796;,
  0.134902;-0.212976;0.967700;,
  -0.723256;0.550083;-0.417504;,
  -0.819586;0.467693;-0.330970;,
  -0.860643;0.500789;0.092217;,
  -0.695285;0.358826;0.622754;,
  -0.489689;0.225622;0.842199;,
  -0.708073;0.700484;0.089188;,
  0.559198;-0.439464;0.702972;,
  -0.491480;0.323564;0.808551;,
  -0.624142;0.507437;0.594100;,
  0.739158;-0.057443;-0.671078;,
  0.949123;-0.208667;-0.235846;,
  0.507227;0.055522;-0.860022;,
  0.687120;0.074548;-0.722710;,
  0.906027;0.271255;-0.324863;,
  0.895712;0.414343;-0.161307;,
  0.961734;0.231964;-0.145813;,
  0.553131;-0.309872;-0.773321;,
  0.772591;-0.233877;-0.590258;,
  0.853507;-0.111303;0.509056;,
  0.945262;-0.118486;0.304042;,
  0.973529;-0.198238;0.113771;,
  0.534058;-0.754294;0.381867;,
  0.242407;-0.742456;0.624498;,
  0.000007;-0.758741;0.651392;,
  -0.192789;-0.778878;0.596810;,
  -0.534058;-0.754294;0.381867;,
  -0.346863;-0.929535;0.125106;,
  -0.000007;-0.882975;0.469419;,
  0.214005;-0.895995;0.389095;,
  0.543543;0.054616;0.837602;,
  0.603667;-0.122988;0.787693;,
  -0.586193;0.094737;-0.804613;,
  0.609369;-0.271307;0.745025;,
  0.538611;0.050472;-0.841041;,
  0.538641;0.075588;-0.839138;,
  0.595502;0.798338;-0.089636;,
  0.592194;0.797122;-0.117913;,
  0.675610;0.733654;0.072817;,
  0.755546;0.266324;0.598516;,
  0.617008;-0.151009;0.772332;,
  -0.000011;-0.818515;-0.574486;,
  0.391125;-0.753307;-0.528725;;
  80;
  4;1,9,8,0;,
  4;2,10,9,1;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;7,15,14,6;,
  4;0,8,15,7;,
  4;16,19,18,17;,
  4;19,21,20,18;,
  4;21,23,22,20;,
  4;23,25,24,22;,
  4;25,27,26,24;,
  4;27,29,28,26;,
  4;74,31,30,75;,
  4;31,16,17,30;,
  4;17,18,33,32;,
  4;18,20,34,33;,
  4;20,22,35,76;,
  4;22,24,36,35;,
  4;24,26,37,36;,
  4;26,28,38,37;,
  4;75,30,39,77;,
  4;30,17,32,39;,
  4;76,35,41,40;,
  4;35,36,42,41;,
  4;36,37,43,42;,
  4;37,38,44,43;,
  4;41,46,45,40;,
  4;42,47,46,41;,
  4;42,43,48,47;,
  4;43,44,49,48;,
  4;47,50,45,46;,
  4;38,39,51,44;,
  4;53,48,49,52;,
  4;48,53,50,47;,
  4;9,19,16,8;,
  4;10,21,19,9;,
  4;23,21,10,11;,
  4;25,23,11,12;,
  4;27,25,12,13;,
  4;29,27,13,14;,
  4;15,31,74,14;,
  4;8,16,31,15;,
  3;56,57,54;,
  3;54,57,55;,
  3;57,58,55;,
  3;55,58,65;,
  3;58,59,65;,
  3;65,59,64;,
  3;59,60,64;,
  3;64,60,63;,
  3;63,60,62;,
  3;60,61,62;,
  4;32,33,54,55;,
  4;33,34,56,54;,
  4;34,78,57,56;,
  4;78,79,58,57;,
  4;80,81,59,58;,
  4;81,82,60,59;,
  4;82,83,83,60;,
  4;83,84,84,83;,
  4;84,44,63,84;,
  4;44,51,64,63;,
  4;51,39,65,64;,
  4;39,32,55,65;,
  3;66,67,73;,
  3;67,68,73;,
  3;73,68,72;,
  3;68,69,72;,
  3;72,69,71;,
  3;69,70,71;,
  4;0,7,67,66;,
  4;7,6,68,67;,
  4;6,5,69,68;,
  4;5,4,70,69;,
  4;4,3,71,70;,
  4;3,2,85,71;,
  4;2,1,86,85;,
  4;1,0,66,73;;
 }
 MeshTextureCoords {
  79;
  -0.316742;-0.952259;,
  -0.448267;-0.939314;,
  -0.426603;-1.022455;,
  -0.323296;-1.027208;,
  -0.311181;-0.863269;,
  -0.455964;-0.863792;,
  -0.314416;-0.771052;,
  -0.448168;-0.787876;,
  -0.321495;-0.686216;,
  -0.430777;-0.700717;,
  -0.322506;-0.610924;,
  -0.402589;-0.602245;,
  -0.307920;-0.542206;,
  -0.378511;-0.513454;,
  -0.273790;-0.482696;,
  -0.334504;-0.432614;,
  -0.226642;-0.433029;,
  -0.280198;-0.343664;,
  -0.524841;-1.021187;,
  -0.541437;-0.928232;,
  -0.591393;-0.929437;,
  -0.571742;-1.020554;,
  -0.547632;-0.864615;,
  -0.622844;-0.864511;,
  -0.539425;-0.800847;,
  -0.618173;-0.792465;,
  -0.520005;-0.715592;,
  -0.587127;-0.704811;,
  -0.480634;-0.596385;,
  -0.542457;-0.572273;,
  -0.451477;-0.483805;,
  -0.508398;-0.461793;,
  -0.394046;-0.380319;,
  -0.440059;-0.352940;,
  -0.329316;-0.252715;,
  -0.372097;-0.217223;,
  -0.649064;-0.923900;,
  -0.610720;-1.021187;,
  -0.705789;-0.853866;,
  -0.698659;-0.773435;,
  -0.676093;-0.658912;,
  -0.635916;-0.512272;,
  -0.581578;-0.419149;,
  -0.487448;-0.340812;,
  -0.417097;-0.200110;,
  -0.813508;-0.738250;,
  -0.840786;-0.819325;,
  -0.788508;-0.596617;,
  -0.759446;-0.452458;,
  -0.706106;-0.350953;,
  -0.923667;-0.687607;,
  -1.005572;-0.739784;,
  -0.898988;-0.560370;,
  -0.866800;-0.434528;,
  -0.836667;-0.331939;,
  -0.995432;-0.541724;,
  -0.586002;-0.320531;,
  -0.974516;-0.389931;,
  -0.923813;-0.320214;,
  -0.705789;-0.853866;,
  -0.840786;-0.819325;,
  -0.649064;-0.923900;,
  -0.610720;-1.021187;,
  -1.005572;-0.739784;,
  -0.487448;-0.340812;,
  -0.995432;-0.541724;,
  -0.586002;-0.320531;,
  -0.974516;-0.389931;,
  -0.706106;-0.350953;,
  -0.836667;-0.331939;,
  -0.923813;-0.320214;,
  -0.226642;-0.433029;,
  -0.273790;-0.482696;,
  -0.316742;-0.952259;,
  -0.307920;-0.542206;,
  -0.311181;-0.863269;,
  -0.322506;-0.610924;,
  -0.314416;-0.771052;,
  -0.321495;-0.686216;;
 }
}
