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
 -4.63393;-40.39334;1.22833;,
 -4.26007;-33.79202;-5.78407;,
 -2.05144;-31.61531;0.75495;,
 -2.90116;-38.13358;5.47921;,
 -8.81758;-41.32970;-0.53243;,
 -9.59238;-34.69368;-8.49273;,
 -13.00095;-40.39334;1.22833;,
 -14.92468;-33.79202;-5.78407;,
 -14.73373;-38.13358;5.47921;,
 -17.13328;-31.61531;0.75495;,
 -13.00095;-35.87380;9.72978;,
 -14.92468;-30.06857;8.09448;,
 -8.81758;-34.93776;11.49056;,
 -9.59238;-29.16720;10.80312;,
 -4.63393;-35.87380;9.72978;,
 -4.26007;-30.06857;8.09448;,
 -2.90116;-38.13358;5.47921;,
 -2.05144;-31.61531;0.75495;,
 -0.42694;-25.09702;-3.96903;,
 -3.11139;-27.19040;-12.79648;,
 -3.11139;-21.18047;-14.36597;,
 -0.42694;-20.83939;-5.22125;,
 -9.59238;-28.05764;-16.45301;,
 -9.59238;-18.35926;-18.15387;,
 -16.07335;-27.19040;-12.79676;,
 -16.07335;-17.69251;-14.36597;,
 -18.75780;-25.09702;-3.96903;,
 -18.75780;-18.22045;-5.22125;,
 -16.07335;-24.26358;6.45917;,
 -16.07335;-18.74839;6.71145;,
 -9.59238;-23.36520;10.57334;,
 -9.59238;-18.96698;11.00058;,
 -3.11139;-24.26358;6.45917;,
 -3.11139;-20.14448;5.80098;,
 -0.42694;-25.09702;-3.96903;,
 -0.42694;-20.83939;-5.22125;,
 -4.72971;-14.80398;-14.62025;,
 -1.54175;-17.05898;-5.35765;,
 -10.76601;-9.68444;-17.62003;,
 -16.01897;-8.68016;-13.75055;,
 -17.51593;-8.59623;-2.94574;,
 -14.91084;-9.90096;9.96607;,
 -8.41849;-13.08757;13.03165;,
 -3.06961;-16.34804;6.61920;,
 -1.54175;-17.05898;-5.35765;,
 -14.46366;2.58096;-11.95464;,
 -9.65662;2.14202;-16.55569;,
 -16.08150;2.94429;0.87308;,
 -12.69331;1.66390;13.43361;,
 -5.89768;-2.72661;16.81055;,
 -11.67023;12.72366;-9.04402;,
 -6.82808;16.47411;-13.44903;,
 -13.39039;13.52417;2.32586;,
 -9.80148;10.98559;12.75319;,
 -4.19158;7.37485;17.34215;,
 -7.63342;18.79437;1.86598;,
 -2.17801;-10.56858;12.28460;,
 -4.27415;18.33436;12.89157;,
 -1.68462;13.65171;16.62013;,
 -4.48970;-7.21907;-13.53579;,
 -3.63951;1.84428;-12.72012;,
 0.13630;-11.14251;-11.23689;,
 2.57944;-12.87065;-4.13837;,
 -1.47180;12.82787;-10.33930;,
 1.40854;-12.32581;5.04026;,
 -2.08899;14.60603;1.39755;,
 2.09182;-7.89666;9.38199;,
 0.48543;14.25350;9.84716;,
 -0.75879;-1.88686;12.85052;,
 0.54871;5.85453;13.25793;,
 2.46995;10.66489;12.70459;,
 -4.76902;-40.47472;5.47916;,
 -5.95474;-38.92839;8.38778;,
 -5.95474;-42.02103;2.57034;,
 -8.81755;-38.28786;9.59264;,
 -8.81755;-42.66177;1.36547;,
 -11.68016;-38.92839;8.38778;,
 -11.68016;-42.02103;2.57034;,
 -12.86588;-40.47472;5.47916;;
 
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
  1;
  80;
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
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  87;
  0.908849;-0.377069;0.178360;,
  0.682358;-0.633282;-0.365159;,
  0.003254;-0.792824;-0.609443;,
  -0.660236;-0.675436;-0.328444;,
  -0.863774;-0.457863;0.210371;,
  -0.616277;-0.293247;0.730896;,
  0.003843;-0.194542;0.980887;,
  0.649652;-0.212211;0.730013;,
  0.983211;-0.176036;0.048027;,
  0.720022;-0.543270;-0.431770;,
  0.003281;-0.765810;-0.643059;,
  -0.702555;-0.590384;-0.397319;,
  -0.960537;-0.265103;0.084197;,
  -0.756963;-0.018305;0.653201;,
  0.003852;0.122229;0.992494;,
  0.772197;0.068375;0.631694;,
  0.992500;-0.121425;0.014121;,
  0.995306;0.089846;-0.035959;,
  0.788980;0.025624;-0.613885;,
  0.765727;-0.366214;-0.528724;,
  -0.014081;-0.058130;-0.998210;,
  -0.009109;-0.513815;-0.857853;,
  -0.807370;-0.021600;-0.589650;,
  -0.774825;-0.347262;-0.528258;,
  -0.999451;0.031211;-0.011116;,
  -0.992164;-0.124406;0.011596;,
  -0.816972;-0.052124;0.574317;,
  -0.801807;-0.011775;0.597467;,
  -0.532189;-0.135282;0.835747;,
  -0.523390;0.010592;0.852027;,
  0.847235;-0.017552;0.530928;,
  0.808365;0.022460;0.588253;,
  0.957226;-0.269955;-0.104128;,
  0.751153;-0.034736;-0.659214;,
  0.527164;0.081196;-0.845876;,
  -0.842546;0.119197;-0.525269;,
  -0.994534;0.100806;0.027192;,
  -0.811753;-0.065414;0.580326;,
  -0.262109;-0.341126;0.902736;,
  0.732992;-0.443301;0.515953;,
  -0.660932;0.247372;-0.708503;,
  -0.859510;0.247449;-0.447227;,
  -0.978011;0.196015;0.071224;,
  -0.782720;0.075352;0.617796;,
  0.134902;-0.212976;0.967700;,
  -0.723256;0.550083;-0.417504;,
  -0.819587;0.467693;-0.330970;,
  -0.860643;0.500789;0.092217;,
  -0.695285;0.358827;0.622754;,
  -0.489689;0.225622;0.842199;,
  -0.708074;0.700483;0.089188;,
  0.559198;-0.439463;0.702972;,
  -0.491480;0.323564;0.808551;,
  -0.624142;0.507437;0.594100;,
  0.739158;-0.057443;-0.671078;,
  0.949123;-0.208667;-0.235846;,
  0.507228;0.055522;-0.860022;,
  0.687120;0.074548;-0.722709;,
  0.906027;0.271255;-0.324862;,
  0.895712;0.414343;-0.161307;,
  0.961734;0.231963;-0.145813;,
  0.553130;-0.309873;-0.773322;,
  0.772591;-0.233878;-0.590258;,
  0.853507;-0.111303;0.509056;,
  0.945262;-0.118486;0.304042;,
  0.973529;-0.198237;0.113771;,
  0.534059;-0.754294;0.381867;,
  0.242407;-0.742456;0.624499;,
  0.000007;-0.758741;0.651392;,
  -0.192789;-0.778878;0.596810;,
  -0.534060;-0.754293;0.381867;,
  -0.346863;-0.929535;0.125106;,
  -0.000006;-0.882975;0.469420;,
  0.214004;-0.895995;0.389096;,
  0.543543;0.054616;0.837602;,
  0.603667;-0.122988;0.787693;,
  -0.586194;0.094737;-0.804613;,
  0.609369;-0.271307;0.745025;,
  0.538612;0.050472;-0.841041;,
  0.538641;0.075588;-0.839138;,
  0.595502;0.798337;-0.089636;,
  0.592194;0.797121;-0.117913;,
  0.675611;0.733653;0.072817;,
  0.755547;0.266323;0.598516;,
  0.617008;-0.151009;0.772332;,
  -0.000011;-0.818515;-0.574485;,
  0.391125;-0.753307;-0.528726;;
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
