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
 35;
 0.00000;73.77962;16.48858;,
 -69.43924;42.87504;16.48858;,
 -51.43642;18.83762;93.31087;,
 0.00000;42.87504;120.19869;,
 69.43924;42.87504;16.48858;,
 51.43642;18.83762;93.31087;,
 0.00000;-36.58665;154.76834;,
 69.43924;-36.58665;120.19869;,
 -69.43924;-36.58665;120.19869;,
 -51.43642;-59.14736;93.31087;,
 0.00000;-67.04362;120.19869;,
 51.43642;-59.14736;93.31087;,
 0.00000;-77.19602;16.48858;,
 69.43924;-67.04362;16.48858;,
 -69.43924;-67.04362;16.48858;,
 -69.43924;-67.04362;16.48858;,
 -51.43642;-59.14736;93.31087;,
 -69.43924;-36.58665;120.19869;,
 -92.58551;-36.58665;16.48858;,
 -51.43642;18.83762;93.31087;,
 -69.43924;42.87504;16.48858;,
 51.43642;-59.14736;93.31087;,
 69.43924;-67.04362;16.48858;,
 92.58546;-36.58665;16.48858;,
 69.43924;-36.58665;120.19869;,
 69.43924;42.87504;16.48858;,
 51.43642;18.83762;93.31087;,
 81.42215;-32.38121;-0.09468;,
 61.06665;-59.16579;-0.09468;,
 61.06665;37.49946;-0.09468;,
 0.00000;-68.09417;-0.09468;,
 0.00000;64.67765;-0.09468;,
 -61.06665;-59.16579;-0.09468;,
 -61.06665;37.49946;-0.09468;,
 -81.42215;-32.38121;-0.09468;;
 
 26;
 4;0,1,2,3;,
 4;4,0,3,5;,
 4;5,3,6,7;,
 4;3,2,8,6;,
 4;6,8,9,10;,
 4;7,6,10,11;,
 4;11,10,12,13;,
 4;10,9,14,12;,
 4;15,16,17,18;,
 4;18,17,19,20;,
 4;21,22,23,24;,
 4;24,23,25,26;,
 3;27,28,29;,
 3;28,30,29;,
 3;29,30,31;,
 3;30,32,31;,
 3;31,32,33;,
 3;32,34,33;,
 4;25,23,27,29;,
 4;23,13,28,27;,
 4;13,12,30,28;,
 4;12,15,32,30;,
 4;15,18,34,32;,
 4;18,1,33,34;,
 4;1,0,31,33;,
 4;0,25,29,31;;
 
 MeshMaterialList {
  8;
  26;
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
  33;
  0.662552;0.575161;0.479806;,
  -0.662552;0.575161;0.479807;,
  0.436308;-0.848099;0.300604;,
  -0.436308;-0.848099;0.300605;,
  0.748276;0.653223;-0.115687;,
  -0.736981;0.398757;0.545758;,
  0.000000;-0.936388;0.350967;,
  0.736981;0.398757;0.545758;,
  -0.478043;-0.853298;-0.208224;,
  0.478043;-0.853298;-0.208224;,
  -0.748275;0.653223;-0.115687;,
  0.000000;0.760614;0.649204;,
  0.000000;0.996125;-0.087949;,
  0.000000;0.476324;0.879270;,
  0.000000;-0.981322;-0.192370;,
  -0.869251;-0.357940;-0.341003;,
  0.751989;-0.627665;-0.201367;,
  0.000000;0.000000;-1.000000;,
  0.370202;-0.281342;-0.885323;,
  0.228276;-0.398924;-0.888116;,
  -0.179031;-0.136058;-0.974390;,
  -0.581359;-0.099945;-0.807485;,
  0.000000;-0.818639;0.574308;,
  -0.552895;-0.740217;0.382605;,
  0.552895;-0.740216;0.382605;,
  -0.910515;0.329159;0.250233;,
  0.941596;0.308822;-0.134263;,
  0.832175;0.242403;-0.498724;,
  0.643903;0.570359;-0.509980;,
  0.000000;-0.876637;-0.481152;,
  -0.127130;-0.869524;-0.477248;,
  -0.643903;0.570359;-0.509981;,
  0.000000;0.876637;-0.481152;;
  26;
  4;12,10,1,11;,
  4;4,12,11,0;,
  4;0,11,13,7;,
  4;11,1,5,13;,
  4;22,23,3,6;,
  4;24,22,6,2;,
  4;2,6,14,9;,
  4;6,3,8,14;,
  4;8,3,23,15;,
  4;25,5,1,10;,
  4;2,9,16,24;,
  4;7,26,4,0;,
  3;18,19,17;,
  3;19,17,17;,
  3;17,17,17;,
  3;17,20,17;,
  3;17,20,17;,
  3;20,21,17;,
  4;4,26,27,28;,
  4;16,9,19,18;,
  4;9,14,29,19;,
  4;14,8,30,29;,
  4;8,15,21,20;,
  4;15,10,31,21;,
  4;10,12,32,31;,
  4;12,4,28,32;;
 }
 MeshTextureCoords {
  35;
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.500000;0.500000;,
  0.375000;0.375000;,
  0.375000;0.500000;,
  0.500000;0.625000;,
  0.375000;0.625000;,
  0.625000;0.625000;,
  0.625000;0.750000;,
  0.500000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.875000;,
  0.375000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.000000;,
  0.875000;0.000000;,
  0.875000;0.125000;,
  0.750000;0.125000;,
  0.875000;0.250000;,
  0.750000;0.250000;,
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.125000;,
  0.125000;0.125000;,
  0.250000;0.250000;,
  0.125000;0.250000;,
  0.250000;0.125000;,
  0.375000;0.875000;,
  0.250000;0.250000;,
  0.500000;0.875000;,
  0.500000;0.375000;,
  0.750000;0.000000;,
  0.625000;0.375000;,
  0.750000;0.125000;;
 }
}
