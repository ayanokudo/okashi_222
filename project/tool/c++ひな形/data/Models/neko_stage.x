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
 196;
 58.99302;-1.33280;-176.66293;,
 -58.99302;-1.33280;-176.66293;,
 -58.99302;1.33280;-176.66293;,
 58.99302;1.33280;-176.66293;,
 -58.99302;1.33280;-58.67689;,
 58.99302;1.33280;-58.67689;,
 -58.99302;-1.33280;-58.67689;,
 58.99302;-1.33280;-58.67689;,
 -58.99302;-1.33280;-176.66293;,
 58.99302;-1.33280;-176.66293;,
 -58.99302;-1.33280;-58.67689;,
 -58.99302;1.33280;-58.67689;,
 58.99302;-1.33280;-58.67689;,
 58.99302;1.33280;-58.67689;,
 61.69084;-1.32109;-176.66293;,
 61.69084;-1.32109;-58.67689;,
 59.02523;-1.32109;-58.67689;,
 59.02523;-1.32109;-176.66293;,
 59.02523;116.66496;-58.67689;,
 59.02523;116.66496;-176.66293;,
 61.69084;116.66496;-58.67689;,
 61.69084;116.66496;-176.66293;,
 61.69084;-1.32109;-58.67689;,
 61.69084;-1.32109;-176.66293;,
 61.69084;116.66496;-58.67689;,
 59.02523;116.66496;-58.67689;,
 61.69084;116.66496;-176.66293;,
 59.02523;116.66496;-176.66293;,
 58.99302;-1.33280;-58.78866;,
 -58.99302;-1.33280;-58.78866;,
 -58.99302;1.33280;-58.78866;,
 58.99302;1.33280;-58.78866;,
 -58.99302;1.33280;59.19738;,
 58.99302;1.33280;59.19738;,
 -58.99302;-1.33280;59.19738;,
 58.99302;-1.33280;59.19738;,
 -58.99302;-1.33280;-58.78866;,
 58.99302;-1.33280;-58.78866;,
 -58.99302;-1.33280;59.19738;,
 -58.99302;1.33280;59.19738;,
 58.99302;-1.33280;59.19738;,
 58.99302;1.33280;59.19738;,
 61.69084;-1.32109;-58.89991;,
 61.69084;-1.32109;59.08614;,
 59.02523;-1.32109;59.08614;,
 59.02523;-1.32109;-58.89991;,
 59.02523;116.66496;59.08614;,
 59.02523;116.66496;-58.89991;,
 61.69084;116.66496;59.08614;,
 61.69084;116.66496;-58.89991;,
 61.69084;-1.32109;59.08614;,
 61.69084;-1.32109;-58.89991;,
 61.69084;116.66496;59.08614;,
 59.02523;116.66496;59.08614;,
 61.69084;116.66496;-58.89991;,
 59.02523;116.66496;-58.89991;,
 58.99302;-1.33280;58.82916;,
 -58.99302;-1.33280;58.82916;,
 -58.99302;1.33280;58.82916;,
 58.99302;1.33280;58.82916;,
 -58.99302;1.33280;176.81522;,
 58.99302;1.33280;176.81522;,
 -58.99302;-1.33280;176.81522;,
 58.99302;-1.33280;176.81522;,
 -58.99302;-1.33280;58.82916;,
 58.99302;-1.33280;58.82916;,
 -58.99302;-1.33280;176.81522;,
 -58.99302;1.33280;176.81522;,
 58.99302;-1.33280;176.81522;,
 58.99302;1.33280;176.81522;,
 62.36318;0.83496;-176.66293;,
 62.36318;0.83496;-58.67689;,
 58.35290;0.83496;-58.67689;,
 58.35290;0.83496;-176.66293;,
 58.35290;6.62215;-58.67689;,
 58.35290;6.62215;-176.66293;,
 62.36318;6.62215;-58.67689;,
 62.36318;6.62215;-176.66293;,
 62.36318;0.83496;-58.67689;,
 62.36318;0.83496;-176.66293;,
 62.36318;6.62215;-58.67689;,
 58.35290;6.62215;-58.67689;,
 62.36318;6.62215;-176.66293;,
 58.35290;6.62215;-176.66293;,
 62.06332;-1.32109;-60.79101;,
 62.06332;-1.32109;-55.79147;,
 58.65276;-1.32109;-55.79147;,
 58.65276;-1.32109;-60.79101;,
 58.65276;116.66496;-55.79147;,
 58.65276;116.66496;-60.79101;,
 62.06332;116.66496;-55.79147;,
 62.06332;116.66496;-60.79101;,
 62.06332;-1.32109;-55.79147;,
 62.06332;-1.32109;-60.79101;,
 62.06332;116.66496;-55.79147;,
 58.65276;116.66496;-55.79147;,
 62.06332;116.66496;-60.79101;,
 58.65276;116.66496;-60.79101;,
 61.69084;-1.32109;58.81258;,
 61.69084;-1.32109;176.79864;,
 59.02523;-1.32109;176.79864;,
 59.02523;-1.32109;58.81258;,
 59.02523;116.66496;176.79864;,
 59.02523;116.66496;58.81258;,
 61.69084;116.66496;176.79864;,
 61.69084;116.66496;58.81258;,
 61.69084;-1.32109;176.79864;,
 61.69084;-1.32109;58.81258;,
 61.69084;116.66496;176.79864;,
 59.02523;116.66496;176.79864;,
 61.69084;116.66496;58.81258;,
 59.02523;116.66496;58.81258;,
 62.36318;0.83496;-58.89991;,
 62.36318;0.83496;59.08614;,
 58.35290;0.83496;59.08614;,
 58.35290;0.83496;-58.89991;,
 58.35290;6.62215;59.08614;,
 58.35290;6.62215;-58.89991;,
 62.36318;6.62215;59.08614;,
 62.36318;6.62215;-58.89991;,
 62.36318;0.83496;59.08614;,
 62.36318;0.83496;-58.89991;,
 62.36318;6.62215;59.08614;,
 58.35290;6.62215;59.08614;,
 62.36318;6.62215;-58.89991;,
 58.35290;6.62215;-58.89991;,
 62.36318;111.40158;-176.66293;,
 62.36318;111.40158;-58.67689;,
 58.35290;111.40158;-58.67689;,
 58.35290;111.40158;-176.66293;,
 58.35290;117.18878;-58.67689;,
 58.35290;117.18878;-176.66293;,
 62.36318;117.18878;-58.67689;,
 62.36318;117.18878;-176.66293;,
 62.36318;111.40158;-58.67689;,
 62.36318;111.40158;-176.66293;,
 62.36318;117.18878;-58.67689;,
 58.35290;117.18878;-58.67689;,
 62.36318;117.18878;-176.66293;,
 58.35290;117.18878;-176.66293;,
 62.06332;-1.32109;55.66984;,
 62.06332;-1.32109;60.66938;,
 58.65276;-1.32109;60.66938;,
 58.65276;-1.32109;55.66984;,
 58.65276;116.66496;60.66938;,
 58.65276;116.66496;55.66984;,
 62.06332;116.66496;60.66938;,
 62.06332;116.66496;55.66984;,
 62.06332;-1.32109;60.66938;,
 62.06332;-1.32109;55.66984;,
 62.06332;116.66496;60.66938;,
 58.65276;116.66496;60.66938;,
 62.06332;116.66496;55.66984;,
 58.65276;116.66496;55.66984;,
 62.36318;0.83496;58.81258;,
 62.36318;0.83496;176.79864;,
 58.35290;0.83496;176.79864;,
 58.35290;0.83496;58.81258;,
 58.35290;6.62215;176.79864;,
 58.35290;6.62215;58.81258;,
 62.36318;6.62215;176.79864;,
 62.36318;6.62215;58.81258;,
 62.36318;0.83496;176.79864;,
 62.36318;0.83496;58.81258;,
 62.36318;6.62215;176.79864;,
 58.35290;6.62215;176.79864;,
 62.36318;6.62215;58.81258;,
 58.35290;6.62215;58.81258;,
 62.36318;111.40158;-58.89991;,
 62.36318;111.40158;59.08614;,
 58.35290;111.40158;59.08614;,
 58.35290;111.40158;-58.89991;,
 58.35290;117.18878;59.08614;,
 58.35290;117.18878;-58.89991;,
 62.36318;117.18878;59.08614;,
 62.36318;117.18878;-58.89991;,
 62.36318;111.40158;59.08614;,
 62.36318;111.40158;-58.89991;,
 62.36318;117.18878;59.08614;,
 58.35290;117.18878;59.08614;,
 62.36318;117.18878;-58.89991;,
 58.35290;117.18878;-58.89991;,
 62.36318;111.40158;58.81258;,
 62.36318;111.40158;176.79864;,
 58.35290;111.40158;176.79864;,
 58.35290;111.40158;58.81258;,
 58.35290;117.18878;176.79864;,
 58.35290;117.18878;58.81258;,
 62.36318;117.18878;176.79864;,
 62.36318;117.18878;58.81258;,
 62.36318;111.40158;176.79864;,
 62.36318;111.40158;58.81258;,
 62.36318;117.18878;176.79864;,
 58.35290;117.18878;176.79864;,
 62.36318;117.18878;58.81258;,
 58.35290;117.18878;58.81258;;
 
 84;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;1,10,11,2;,
 4;12,0,3,13;,
 4;14,15,16,17;,
 4;17,16,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;15,24,25,16;,
 4;26,14,17,27;,
 4;28,29,30,31;,
 4;31,30,32,33;,
 4;33,32,34,35;,
 4;35,34,36,37;,
 4;29,38,39,30;,
 4;40,28,31,41;,
 4;42,43,44,45;,
 4;45,44,46,47;,
 4;47,46,48,49;,
 4;49,48,50,51;,
 4;43,52,53,44;,
 4;54,42,45,55;,
 4;56,57,58,59;,
 4;59,58,60,61;,
 4;61,60,62,63;,
 4;63,62,64,65;,
 4;57,66,67,58;,
 4;68,56,59,69;,
 4;70,71,72,73;,
 4;73,72,74,75;,
 4;75,74,76,77;,
 4;77,76,78,79;,
 4;71,80,81,72;,
 4;82,70,73,83;,
 4;84,85,86,87;,
 4;87,86,88,89;,
 4;89,88,90,91;,
 4;91,90,92,93;,
 4;85,94,95,86;,
 4;96,84,87,97;,
 4;98,99,100,101;,
 4;101,100,102,103;,
 4;103,102,104,105;,
 4;105,104,106,107;,
 4;99,108,109,100;,
 4;110,98,101,111;,
 4;112,113,114,115;,
 4;115,114,116,117;,
 4;117,116,118,119;,
 4;119,118,120,121;,
 4;113,122,123,114;,
 4;124,112,115,125;,
 4;126,127,128,129;,
 4;129,128,130,131;,
 4;131,130,132,133;,
 4;133,132,134,135;,
 4;127,136,137,128;,
 4;138,126,129,139;,
 4;140,141,142,143;,
 4;143,142,144,145;,
 4;145,144,146,147;,
 4;147,146,148,149;,
 4;141,150,151,142;,
 4;152,140,143,153;,
 4;154,155,156,157;,
 4;157,156,158,159;,
 4;159,158,160,161;,
 4;161,160,162,163;,
 4;155,164,165,156;,
 4;166,154,157,167;,
 4;168,169,170,171;,
 4;171,170,172,173;,
 4;173,172,174,175;,
 4;175,174,176,177;,
 4;169,178,179,170;,
 4;180,168,171,181;,
 4;182,183,184,185;,
 4;185,184,186,187;,
 4;187,186,188,189;,
 4;189,188,190,191;,
 4;183,192,193,184;,
 4;194,182,185,195;;
 
 MeshMaterialList {
  17;
  84;
  16,
  16,
  16,
  16,
  16,
  16,
  16,
  13,
  13,
  13,
  13,
  13,
  16,
  15,
  15,
  15,
  15,
  15,
  15,
  13,
  13,
  13,
  13,
  13,
  15,
  14,
  14,
  14,
  14,
  14,
  13,
  13,
  13,
  13,
  15,
  13,
  16,
  13,
  13,
  13,
  13,
  13,
  14,
  13,
  13,
  13,
  13,
  13,
  15,
  15,
  15,
  15,
  15,
  15,
  13,
  13,
  13,
  13,
  13,
  13,
  15,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  15,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13,
  13;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "unnamed.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "ph_back01_00163s.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "PUNCH-DARKRED.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "d224580adc1be0d4943225f3efb27d7f_t.jpeg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "ph_back01_00163s.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "ph_back01_00163s.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "ph_back01_00163s.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "ph_back01_00163s.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "ph_back01_00163s.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "ph_back01_00163s.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "ph_back01_00163s.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "ph_back01_00163s.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "ph_back01_00163s.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.025098;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.661961;0.313726;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.570980;0.787451;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  6;
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;;
  84;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;0,0,0,0;;
 }
 MeshTextureCoords {
  196;
  -0.923557;-5.194226;,
  1.923557;-5.194226;,
  1.923557;-2.347113;,
  -0.923557;-2.347113;,
  1.923557;0.500000;,
  -0.923557;0.500000;,
  1.923557;3.347113;,
  -0.923557;3.347113;,
  1.923557;6.194226;,
  -0.923557;6.194226;,
  4.770669;-5.194226;,
  4.770669;-2.347113;,
  -3.770669;-5.194226;,
  -3.770669;-2.347113;,
  0.269732;-0.421070;,
  0.730268;-0.421070;,
  0.730268;0.039465;,
  0.269732;0.039465;,
  0.730268;0.500000;,
  0.269732;0.500000;,
  0.730268;0.960535;,
  0.269732;0.960535;,
  0.730268;1.421070;,
  0.269732;1.421070;,
  1.190803;-0.421070;,
  1.190803;0.039465;,
  -0.190803;-0.421070;,
  -0.190803;0.039465;,
  -0.036522;-1.165555;,
  1.036522;-1.165555;,
  1.036522;-0.092511;,
  -0.036522;-0.092511;,
  1.036522;0.980532;,
  -0.036522;0.980532;,
  1.036522;2.053575;,
  -0.036522;2.053575;,
  1.036522;3.126619;,
  -0.036522;3.126619;,
  2.109565;-1.165555;,
  2.109565;-0.092511;,
  -1.109565;-1.165555;,
  -1.109565;-0.092511;,
  0.269732;-0.421070;,
  0.730268;-0.421070;,
  0.730268;0.039465;,
  0.269732;0.039465;,
  0.730268;0.500000;,
  0.269732;0.500000;,
  0.730268;0.960535;,
  0.269732;0.960535;,
  0.730268;1.421070;,
  0.269732;1.421070;,
  1.190803;-0.421070;,
  1.190803;0.039465;,
  -0.190803;-0.421070;,
  -0.190803;0.039465;,
  -1.110268;-5.460539;,
  2.110268;-5.460539;,
  2.110268;-2.240003;,
  -1.110268;-2.240003;,
  2.110268;0.980533;,
  -1.110268;0.980533;,
  2.110268;4.201066;,
  -1.110268;4.201066;,
  2.110268;7.421603;,
  -1.110268;7.421603;,
  5.330802;-5.460539;,
  5.330802;-2.240003;,
  -4.330802;-5.460539;,
  -4.330802;-2.240003;,
  0.269732;-0.421070;,
  0.730268;-0.421070;,
  0.730268;0.039465;,
  0.269732;0.039465;,
  0.730268;0.500000;,
  0.269732;0.500000;,
  0.730268;0.960535;,
  0.269732;0.960535;,
  0.730268;1.421070;,
  0.269732;1.421070;,
  1.190803;-0.421070;,
  1.190803;0.039465;,
  -0.190803;-0.421070;,
  -0.190803;0.039465;,
  0.269732;-0.421070;,
  0.730268;-0.421070;,
  0.730268;0.039465;,
  0.269732;0.039465;,
  0.730268;0.500000;,
  0.269732;0.500000;,
  0.730268;0.960535;,
  0.269732;0.960535;,
  0.730268;1.421070;,
  0.269732;1.421070;,
  1.190803;-0.421070;,
  1.190803;0.039465;,
  -0.190803;-0.421070;,
  -0.190803;0.039465;,
  0.269732;-0.421070;,
  0.730268;-0.421070;,
  0.730268;0.039465;,
  0.269732;0.039465;,
  0.730268;0.500000;,
  0.269732;0.500000;,
  0.730268;0.960535;,
  0.269732;0.960535;,
  0.730268;1.421070;,
  0.269732;1.421070;,
  1.190803;-0.421070;,
  1.190803;0.039465;,
  -0.190803;-0.421070;,
  -0.190803;0.039465;,
  0.269732;-0.421070;,
  0.730268;-0.421070;,
  0.730268;0.039465;,
  0.269732;0.039465;,
  0.730268;0.500000;,
  0.269732;0.500000;,
  0.730268;0.960535;,
  0.269732;0.960535;,
  0.730268;1.421070;,
  0.269732;1.421070;,
  1.190803;-0.421070;,
  1.190803;0.039465;,
  -0.190803;-0.421070;,
  -0.190803;0.039465;,
  0.269732;-0.421070;,
  0.730268;-0.421070;,
  0.730268;0.039465;,
  0.269732;0.039465;,
  0.730268;0.500000;,
  0.269732;0.500000;,
  0.730268;0.960535;,
  0.269732;0.960535;,
  0.730268;1.421070;,
  0.269732;1.421070;,
  1.190803;-0.421070;,
  1.190803;0.039465;,
  -0.190803;-0.421070;,
  -0.190803;0.039465;,
  0.269732;-0.421070;,
  0.730268;-0.421070;,
  0.730268;0.039465;,
  0.269732;0.039465;,
  0.730268;0.500000;,
  0.269732;0.500000;,
  0.730268;0.960535;,
  0.269732;0.960535;,
  0.730268;1.421070;,
  0.269732;1.421070;,
  1.190803;-0.421070;,
  1.190803;0.039465;,
  -0.190803;-0.421070;,
  -0.190803;0.039465;,
  0.269732;-0.421070;,
  0.730268;-0.421070;,
  0.730268;0.039465;,
  0.269732;0.039465;,
  0.730268;0.500000;,
  0.269732;0.500000;,
  0.730268;0.960535;,
  0.269732;0.960535;,
  0.730268;1.421070;,
  0.269732;1.421070;,
  1.190803;-0.421070;,
  1.190803;0.039465;,
  -0.190803;-0.421070;,
  -0.190803;0.039465;,
  0.269732;-0.421070;,
  0.730268;-0.421070;,
  0.730268;0.039465;,
  0.269732;0.039465;,
  0.730268;0.500000;,
  0.269732;0.500000;,
  0.730268;0.960535;,
  0.269732;0.960535;,
  0.730268;1.421070;,
  0.269732;1.421070;,
  1.190803;-0.421070;,
  1.190803;0.039465;,
  -0.190803;-0.421070;,
  -0.190803;0.039465;,
  0.269732;-0.421070;,
  0.730268;-0.421070;,
  0.730268;0.039465;,
  0.269732;0.039465;,
  0.730268;0.500000;,
  0.269732;0.500000;,
  0.730268;0.960535;,
  0.269732;0.960535;,
  0.730268;1.421070;,
  0.269732;1.421070;,
  1.190803;-0.421070;,
  1.190803;0.039465;,
  -0.190803;-0.421070;,
  -0.190803;0.039465;;
 }
}
