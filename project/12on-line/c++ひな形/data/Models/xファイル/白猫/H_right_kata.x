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
 10.57767;-142.76273;0.22974;,
 3.83912;-140.39940;-18.14673;,
 1.61613;-107.82879;-15.40994;,
 9.24102;-109.24174;5.46483;,
 -12.43064;-139.42010;-25.75769;,
 -16.79051;-107.24282;-24.05669;,
 -28.69927;-140.39940;-18.14673;,
 -35.19708;-107.82879;-15.40994;,
 -35.43789;-142.76273;0.22974;,
 -42.82092;-109.24174;5.46483;,
 -28.69927;-145.12607;18.60621;,
 -35.19708;-110.65469;26.33960;,
 -12.43064;-146.10535;26.21822;,
 -16.79051;-111.23946;34.98642;,
 3.83912;-145.12607;18.60621;,
 1.61613;-110.65469;26.33960;,
 10.57767;-142.76273;0.22974;,
 9.24102;-109.24174;5.46483;,
 9.76483;-79.42678;10.69999;,
 1.25465;-78.96423;-12.67322;,
 0.87973;-53.17473;-12.63381;,
 9.48125;-53.10319;10.69999;,
 -19.28986;-78.77277;-22.35478;,
 -19.53689;-50.36262;-22.29892;,
 -39.83437;-78.96423;-12.67322;,
 -39.80931;-46.31298;-12.63381;,
 -48.34357;-79.42678;10.69999;,
 -48.06098;-43.39944;10.69999;,
 -39.83437;-79.88926;34.07306;,
 -39.45939;-43.32909;34.03365;,
 -19.28986;-80.08192;43.75462;,
 -19.04283;-46.14113;43.69883;,
 1.25465;-79.88926;34.07306;,
 1.22966;-50.18964;34.03365;,
 9.76483;-79.42678;10.69999;,
 9.48125;-53.10319;10.69999;,
 -40.54089;-3.32138;-27.70362;,
 -22.40535;-2.06291;-46.64667;,
 -50.70930;0.26928;3.75298;,
 -40.11024;0.35579;37.47163;,
 -14.95267;-3.10905;49.38024;,
 -40.54089;34.73490;-27.70362;,
 -28.09901;44.64045;-41.42362;,
 -46.47961;38.32548;3.75298;,
 -40.11024;38.41319;37.47163;,
 -27.48378;54.18742;49.80570;,
 -37.82817;64.82321;3.75298;,
 -4.01901;-31.39807;48.11352;,
 -8.26941;0.22442;-32.66046;,
 -12.31184;33.38327;-28.95214;,
 -6.23283;-34.06773;-15.37382;,
 8.26262;-36.06427;-8.51172;,
 14.36964;-36.01345;8.05490;,
 -19.21944;47.71268;3.12270;,
 8.51113;-33.94488;24.62152;,
 4.78468;-20.60311;34.61808;,
 -2.97804;-0.51829;35.51737;,
 -11.87504;40.16145;35.81949;,
 5.13405;-154.88693;0.22981;,
 -0.01018;-156.69110;14.25851;,
 -0.01018;-153.08267;-13.79875;,
 -12.43049;-157.43863;20.06949;,
 -12.43049;-152.33514;-19.60896;,
 -24.84996;-156.69110;14.25851;,
 -24.84996;-153.08267;-13.79875;,
 -29.99426;-154.88693;0.22981;;
 
 67;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,5,4;,
 4;8,9,7,6;,
 4;10,11,9,8;,
 4;12,13,11,10;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;18,19,20,21;,
 4;19,22,23,20;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;23,25,36,37;,
 4;25,27,38,36;,
 4;27,29,39,38;,
 4;29,31,40,39;,
 4;37,36,41,42;,
 4;36,38,43,41;,
 4;38,39,44,43;,
 4;39,40,45,44;,
 4;41,43,46,42;,
 4;43,44,45,46;,
 4;19,18,3,2;,
 4;22,19,2,5;,
 4;7,24,22,5;,
 4;9,26,24,7;,
 4;11,28,26,9;,
 4;13,30,28,11;,
 4;32,30,13,15;,
 4;34,32,15,17;,
 4;47,40,31,33;,
 3;48,49,50;,
 3;50,49,51;,
 3;51,49,52;,
 3;49,53,52;,
 3;52,53,54;,
 3;54,53,55;,
 3;55,53,56;,
 3;53,57,56;,
 4;21,20,51,52;,
 4;20,23,50,51;,
 4;23,37,48,50;,
 4;37,42,49,48;,
 4;42,46,53,49;,
 4;46,45,57,53;,
 4;45,40,56,57;,
 4;40,47,55,56;,
 4;47,33,54,55;,
 4;33,21,52,54;,
 3;58,59,60;,
 3;59,61,60;,
 3;60,61,62;,
 3;61,63,62;,
 3;62,63,64;,
 3;63,65,64;,
 4;1,16,58,60;,
 4;16,14,59,58;,
 4;14,12,61,59;,
 4;12,10,63,61;,
 4;10,8,65,63;,
 4;8,6,64,65;,
 4;6,4,62,64;,
 4;4,1,60,62;;
 
 MeshMaterialList {
  15;
  67;
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
  77;
  0.981357;-0.190893;-0.022312;,
  0.999932;0.011537;0.001585;,
  0.737887;0.089321;-0.668987;,
  0.718199;-0.162873;-0.676507;,
  0.000416;0.056354;-0.998411;,
  0.000546;-0.197964;-0.980209;,
  -0.698018;-0.256242;-0.668664;,
  -0.731550;-0.069866;-0.678199;,
  -0.949300;-0.312430;-0.034885;,
  -0.980505;-0.195823;-0.016202;,
  -0.705779;-0.363929;0.607809;,
  -0.718861;-0.275102;0.638403;,
  0.001637;-0.364260;0.931296;,
  0.003234;-0.258393;0.966034;,
  0.736694;-0.129448;0.663721;,
  0.723754;-0.278606;0.631315;,
  0.999991;-0.003611;-0.002125;,
  0.991069;-0.133295;0.003904;,
  0.733801;-0.069950;-0.675754;,
  0.738475;0.041455;-0.673006;,
  0.133978;-0.140650;-0.980952;,
  -0.000345;0.031595;-0.999501;,
  -0.775403;-0.120636;-0.619836;,
  -0.738057;-0.025346;-0.674262;,
  -0.999423;-0.033427;0.005970;,
  -0.996205;-0.086961;-0.003662;,
  -0.743609;-0.024115;0.668180;,
  -0.735019;-0.133183;0.664838;,
  -0.103113;-0.110711;0.988489;,
  0.002011;-0.136299;0.990666;,
  0.721615;-0.146656;0.676582;,
  0.739975;-0.077385;0.668169;,
  -0.658432;-0.175864;-0.731805;,
  -0.843919;-0.106534;-0.525787;,
  -0.999964;-0.008329;0.001677;,
  -0.777646;-0.032231;0.627875;,
  -0.312555;-0.167599;0.934997;,
  -0.834725;0.200250;-0.512965;,
  -0.890462;0.152046;-0.428906;,
  -0.972906;0.230399;-0.019218;,
  -0.865290;0.131628;0.483680;,
  -0.780449;0.170912;0.601406;,
  -0.916319;0.399116;-0.032637;,
  0.616797;-0.077377;0.783309;,
  0.730105;-0.067844;-0.679959;,
  0.996035;0.088855;-0.004394;,
  0.944768;-0.101054;-0.311771;,
  0.880972;-0.006485;-0.473123;,
  0.910439;0.336572;-0.240459;,
  0.889282;0.457347;-0.003424;,
  0.889915;0.413624;0.192267;,
  0.906200;0.263197;0.330952;,
  0.927651;0.213159;0.306639;,
  0.957060;0.094668;0.273997;,
  -0.000011;-0.991831;-0.127559;,
  -0.000004;-0.991831;-0.127563;,
  0.000002;-0.991831;-0.127559;,
  -0.000004;-0.991830;-0.127566;,
  0.000008;-0.991831;-0.127563;,
  0.000011;-0.991831;-0.127559;,
  0.000016;-0.991831;-0.127559;,
  -0.000001;-0.991830;-0.127566;,
  0.420744;-0.057066;-0.905383;,
  0.406989;-0.144873;-0.901871;,
  0.707144;-0.065092;-0.704068;,
  0.728364;0.482652;-0.486348;,
  0.673024;0.734997;-0.082567;,
  0.782796;0.494684;0.377517;,
  0.722561;0.200461;0.661605;,
  0.911244;-0.409139;-0.047335;,
  0.648189;-0.415482;-0.638143;,
  0.685781;-0.444817;0.576058;,
  -0.000012;-0.476873;0.878972;,
  -0.685789;-0.444816;0.576050;,
  -0.911243;-0.409140;-0.047335;,
  -0.648196;-0.415482;-0.638136;,
  -0.000011;-0.429862;-0.902895;;
  67;
  4;0,3,2,1;,
  4;3,5,4,2;,
  4;6,7,4,5;,
  4;8,9,7,6;,
  4;10,11,9,8;,
  4;12,13,11,10;,
  4;12,15,14,13;,
  4;15,0,1,14;,
  4;16,19,18,17;,
  4;19,21,20,18;,
  4;21,23,22,20;,
  4;23,25,24,22;,
  4;25,27,26,24;,
  4;27,29,28,26;,
  4;29,31,30,28;,
  4;31,16,17,30;,
  4;20,22,33,32;,
  4;22,24,34,33;,
  4;24,26,35,34;,
  4;26,28,36,35;,
  4;32,33,38,37;,
  4;33,34,39,38;,
  4;34,35,40,39;,
  4;35,36,41,40;,
  4;38,39,42,37;,
  4;39,40,41,42;,
  4;19,16,1,2;,
  4;21,19,2,4;,
  4;7,23,21,4;,
  4;9,25,23,7;,
  4;11,27,25,9;,
  4;13,29,27,11;,
  4;31,29,13,14;,
  4;16,31,14,1;,
  4;43,36,28,30;,
  3;47,48,46;,
  3;62,63,44;,
  3;44,48,45;,
  3;48,49,45;,
  3;45,49,53;,
  3;53,49,52;,
  3;52,49,51;,
  3;49,50,51;,
  4;17,18,44,45;,
  4;18,20,62,44;,
  4;20,64,47,46;,
  4;64,65,48,47;,
  4;65,66,49,48;,
  4;66,67,50,49;,
  4;67,68,51,50;,
  4;68,43,52,51;,
  4;43,30,53,52;,
  4;30,17,45,53;,
  3;54,56,55;,
  3;56,57,55;,
  3;55,57,61;,
  3;57,58,61;,
  3;61,58,60;,
  3;58,59,60;,
  4;3,0,69,70;,
  4;0,15,71,69;,
  4;15,12,72,71;,
  4;12,10,73,72;,
  4;10,8,74,73;,
  4;8,6,75,74;,
  4;6,5,76,75;,
  4;5,3,70,76;;
 }
 MeshTextureCoords {
  66;
  -0.450054;1.611583;,
  -0.514751;1.612268;,
  -0.510311;1.510449;,
  -0.438329;1.509543;,
  -0.582003;1.614220;,
  -0.583156;1.511235;,
  -0.650281;1.615754;,
  -0.656927;1.511375;,
  -0.717676;1.617871;,
  -0.729996;1.512376;,
  -0.782962;1.623302;,
  -0.801523;1.517513;,
  -0.845888;1.634581;,
  -0.871199;1.529771;,
  -0.906742;1.652938;,
  -0.938977;1.550895;,
  -0.965960;1.677815;,
  -1.005255;1.580528;,
  -0.423435;1.418911;,
  -0.504107;1.424238;,
  -0.510898;1.355532;,
  -0.424385;1.354581;,
  -0.582757;1.421601;,
  -0.578713;1.327962;,
  -0.664798;1.421123;,
  -0.665160;1.317792;,
  -0.744431;1.422881;,
  -0.750265;1.315726;,
  -0.819957;1.427923;,
  -0.832972;1.322219;,
  -0.892631;1.439227;,
  -0.916014;1.338904;,
  -0.963153;1.460991;,
  -0.989094;1.377080;,
  -1.035994;1.491797;,
  -1.065466;1.413841;,
  -0.641887;1.185115;,
  -0.557165;1.171098;,
  -0.742070;1.188258;,
  -0.848896;1.196314;,
  -0.945045;1.213245;,
  -0.659116;1.080343;,
  -0.609136;1.037685;,
  -0.752750;1.083454;,
  -0.852375;1.090844;,
  -0.905433;1.043706;,
  -0.760295;1.002510;,
  -0.986242;1.290568;,
  -0.557165;1.171098;,
  -0.609136;1.037685;,
  -0.578713;1.327962;,
  -0.510898;1.355532;,
  -0.424385;1.354581;,
  -0.760295;1.002510;,
  -0.989094;1.377080;,
  -0.986242;1.290568;,
  -0.945045;1.213245;,
  -0.905433;1.043706;,
  -0.965960;1.677815;,
  -0.906742;1.652938;,
  -0.514751;1.612268;,
  -0.845888;1.634581;,
  -0.582003;1.614220;,
  -0.782962;1.623302;,
  -0.650281;1.615754;,
  -0.717676;1.617871;;
 }
}
