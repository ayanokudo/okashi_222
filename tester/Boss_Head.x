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
 303;
 -103.14900;8.75350;-360.57379;,
 -120.24850;12.61810;-336.29321;,
 -107.35790;38.01630;-339.94379;,
 -89.28810;24.15690;-371.80310;,
 -128.05589;28.36950;-312.04840;,
 -122.91250;50.63870;-306.29349;,
 -113.15360;69.85150;-304.32709;,
 -95.42570;56.09360;-341.12689;,
 -76.13050;40.69300;-376.45810;,
 -86.93720;62.49830;-339.35901;,
 -64.21530;41.44870;-385.80591;,
 -112.14380;79.19580;-292.42819;,
 -107.56470;67.10290;-300.34729;,
 -87.88070;52.38300;-335.75439;,
 -70.54150;37.94440;-372.47839;,
 -97.29760;33.06880;-332.78021;,
 -81.74300;20.44640;-366.43051;,
 -115.36750;46.92810;-300.92090;,
 -122.46700;25.62090;-308.06851;,
 -112.70350;8.90750;-330.92059;,
 -97.56000;6.00480;-356.59409;,
 -121.19220;2.50290;-332.68851;,
 -99.66380;-2.47810;-366.36169;,
 -133.28830;24.00380;-300.85220;,
 -128.05589;28.36950;-312.04840;,
 -120.24850;12.61810;-336.29321;,
 -103.14900;8.75350;-360.57379;,
 -133.28830;24.00380;-300.85220;,
 -124.74420;53.19710;-292.68909;,
 -122.46700;25.62090;-308.06851;,
 -115.36750;46.92810;-300.92090;,
 -107.56470;67.10290;-300.34729;,
 -112.14380;79.19580;-292.42819;,
 -97.56000;6.00480;-356.59409;,
 -99.66380;-2.47810;-366.36169;,
 -79.91150;17.88800;-380.03500;,
 -81.74300;20.44640;-366.43051;,
 -64.21530;41.44870;-385.80591;,
 -70.54150;37.94440;-372.47839;,
 100.16220;8.75340;-360.57391;,
 86.30120;24.15690;-371.80310;,
 104.37110;38.01630;-339.94391;,
 117.26170;12.61810;-336.29321;,
 119.92570;50.63870;-306.29349;,
 125.06920;28.36950;-312.04840;,
 92.43890;56.09360;-341.12701;,
 110.16670;69.85150;-304.32721;,
 73.14370;40.69300;-376.45810;,
 61.22850;41.44860;-385.80591;,
 83.95030;62.49830;-339.35901;,
 109.15700;79.19580;-292.42831;,
 84.89390;52.38310;-335.75439;,
 104.57790;67.10280;-300.34729;,
 67.55480;37.94440;-372.47839;,
 78.75620;20.44640;-366.43051;,
 94.31080;33.06880;-332.78021;,
 112.38070;46.92810;-300.92090;,
 109.71670;8.90750;-330.92059;,
 119.48020;25.62100;-308.06851;,
 94.57320;6.00480;-356.59409;,
 96.67700;-2.47810;-366.36169;,
 118.20530;2.50290;-332.68851;,
 130.30150;24.00380;-300.85220;,
 117.26170;12.61810;-336.29321;,
 125.06920;28.36950;-312.04840;,
 100.16220;8.75340;-360.57391;,
 121.75730;53.19710;-292.68909;,
 130.30150;24.00380;-300.85220;,
 112.38070;46.92810;-300.92090;,
 119.48020;25.62100;-308.06851;,
 109.15700;79.19580;-292.42831;,
 104.57790;67.10280;-300.34729;,
 94.57320;6.00480;-356.59409;,
 78.75620;20.44640;-366.43051;,
 76.92470;17.88800;-380.03500;,
 96.67700;-2.47810;-366.36169;,
 61.22850;41.44860;-385.80591;,
 67.55480;37.94440;-372.47839;,
 11.46910;-16.02410;-485.31921;,
 -1.49340;-25.28900;-487.03299;,
 -1.49340;-3.31390;-489.23621;,
 20.48180;-3.31390;-487.03299;,
 -14.45590;-16.02410;-485.31921;,
 -23.46860;-3.31390;-487.03299;,
 -17.77130;12.96410;-485.31921;,
 -1.49340;13.57670;-487.03299;,
 14.78450;12.96410;-485.31921;,
 -1.49340;20.90180;-480.42310;,
 20.48180;18.66130;-480.42310;,
 -23.46860;18.66130;-480.42310;,
 -17.77130;12.96410;-475.52679;,
 -1.49340;13.57670;-473.81320;,
 14.78450;12.96410;-475.52679;,
 -1.49340;-3.31390;-471.60999;,
 20.48180;-3.31390;-473.81320;,
 -23.46860;-3.31390;-473.81320;,
 -14.45590;-16.02410;-475.52679;,
 -1.49340;-25.28900;-473.81320;,
 11.46910;-16.02410;-475.52679;,
 -1.49340;-32.61410;-480.42310;,
 15.42140;-21.72140;-480.42310;,
 -18.40820;-21.72140;-480.42310;,
 -14.45590;-16.02410;-485.31921;,
 -1.49340;-25.28900;-487.03299;,
 11.46910;-16.02410;-485.31921;,
 -18.40820;-21.72140;-480.42310;,
 -30.79370;-3.31390;-480.42310;,
 -14.45590;-16.02410;-475.52679;,
 -23.46860;-3.31390;-473.81320;,
 -17.77130;12.96410;-475.52679;,
 -23.46860;18.66130;-480.42310;,
 11.46910;-16.02410;-475.52679;,
 15.42140;-21.72140;-480.42310;,
 27.80680;-3.31390;-480.42310;,
 20.48180;-3.31390;-473.81320;,
 20.48180;18.66130;-480.42310;,
 14.78450;12.96410;-475.52679;,
 -112.67310;-40.77310;-337.33359;,
 -220.45309;-39.20580;-230.48109;,
 -220.45309;-38.16370;-230.48109;,
 -112.67310;-36.59640;-337.33359;,
 -219.72720;-38.16370;-229.73351;,
 -109.76350;-36.59640;-334.33719;,
 -219.72720;-39.20580;-229.73351;,
 -109.76350;-40.77310;-334.33719;,
 -220.45309;-39.20580;-230.48109;,
 -112.67310;-40.77310;-337.33359;,
 -219.72720;-39.20580;-229.73351;,
 -219.72720;-38.16370;-229.73351;,
 -109.76350;-40.77310;-334.33719;,
 -109.76350;-36.59640;-334.33719;,
 109.68640;-40.77310;-337.33359;,
 109.68640;-36.59640;-337.33359;,
 217.46640;-38.16370;-230.48109;,
 217.46640;-39.20580;-230.48109;,
 106.77670;-36.59640;-334.33719;,
 216.74030;-38.16370;-229.73351;,
 106.77670;-40.77310;-334.33719;,
 216.74030;-39.20580;-229.73351;,
 109.68640;-40.77310;-337.33359;,
 217.46640;-39.20580;-230.48109;,
 216.74030;-38.16370;-229.73351;,
 216.74030;-39.20580;-229.73351;,
 106.77670;-40.77310;-334.33719;,
 106.77670;-36.59640;-334.33719;,
 -112.67330;-32.04450;-336.80759;,
 -220.45309;-19.18240;-230.72060;,
 -220.45309;-18.14620;-230.83090;,
 -112.67320;-27.89130;-337.24951;,
 -219.72710;-18.06710;-230.08760;,
 -109.76350;-27.57430;-334.26999;,
 -219.72720;-19.10340;-229.97720;,
 -109.76350;-31.72760;-333.82809;,
 -220.45309;-19.18240;-230.72060;,
 -112.67330;-32.04450;-336.80759;,
 -219.72720;-19.10340;-229.97720;,
 -219.72710;-18.06710;-230.08760;,
 -109.76350;-31.72760;-333.82809;,
 -109.76350;-27.57430;-334.26999;,
 109.68650;-32.04450;-336.80759;,
 109.68640;-27.89130;-337.24951;,
 217.46629;-18.14620;-230.83090;,
 217.46629;-19.18240;-230.72060;,
 106.77660;-27.57430;-334.27011;,
 216.74030;-18.06710;-230.08760;,
 106.77660;-31.72760;-333.82809;,
 216.74030;-19.10340;-229.97710;,
 109.68650;-32.04450;-336.80759;,
 217.46629;-19.18240;-230.72060;,
 216.74030;-18.06710;-230.08760;,
 216.74030;-19.10340;-229.97710;,
 106.77660;-31.72760;-333.82809;,
 106.77660;-27.57430;-334.27011;,
 -2.18810;178.38091;-280.65399;,
 -2.18810;180.71159;-155.43250;,
 73.50520;164.98320;-180.00870;,
 74.45520;164.57291;-248.03180;,
 -2.18810;110.40440;-351.02771;,
 49.91840;72.63570;-340.71600;,
 -2.18810;-135.88980;-252.97310;,
 133.94290;-68.31440;-260.45981;,
 137.02150;-72.06230;-117.15090;,
 -2.18810;-136.00169;-108.80650;,
 28.17430;-92.18210;-433.40640;,
 86.49460;-97.74820;-343.32660;,
 -2.18810;-127.83560;-410.94250;,
 -2.18810;-111.98490;-440.63199;,
 10.99630;-66.85060;-468.27551;,
 -2.18810;-78.07590;-463.23529;,
 28.17430;-10.85470;-465.25491;,
 -2.18810;-1.14910;-482.69879;,
 -2.18810;32.85300;-468.53891;,
 34.46870;4.24910;-445.16531;,
 107.42630;-36.47530;-342.73929;,
 48.71680;-48.75400;-427.37421;,
 182.50130;-8.31880;-129.21530;,
 155.83591;2.00210;-271.79691;,
 119.56250;132.10320;-184.28650;,
 109.07410;136.98790;-242.07100;,
 145.38721;203.73090;-179.16960;,
 151.47591;179.23061;-189.40750;,
 136.96980;188.67039;-240.85361;,
 132.21480;212.95180;-243.06250;,
 84.77800;28.37780;-334.52539;,
 135.88850;156.95610;-182.66060;,
 118.20690;179.68610;-171.38480;,
 73.50520;164.98320;-180.00870;,
 119.56250;132.10320;-184.28650;,
 118.20690;179.68610;-171.38480;,
 103.79840;189.45689;-251.38811;,
 74.45520;164.57291;-248.03180;,
 73.50520;164.98320;-180.00870;,
 118.78000;167.59920;-247.63620;,
 109.07410;136.98790;-242.07100;,
 118.78000;167.59920;-247.63620;,
 109.07410;136.98790;-242.07100;,
 145.38721;203.73090;-179.16960;,
 71.61820;-122.21990;-340.67249;,
 110.68480;-82.77820;-279.95380;,
 -2.18810;-135.45590;-261.01541;,
 -2.18810;-159.26390;-389.05350;,
 57.95770;130.96030;-86.08540;,
 0.04680;152.54820;-89.24940;,
 176.39790;-14.84970;9.91960;,
 152.58380;-49.20570;39.87260;,
 195.50079;34.99030;15.80660;,
 0.04680;-114.83070;-43.65840;,
 -2.18810;178.38091;-280.65399;,
 -78.83150;164.57291;-248.03180;,
 -77.88150;164.98320;-180.00870;,
 -2.18810;180.71159;-155.43250;,
 -2.18810;110.40440;-351.02771;,
 -54.29480;72.63570;-340.71600;,
 -2.18810;-135.88980;-252.97310;,
 -2.18810;-136.00169;-108.80650;,
 -141.39760;-72.06230;-117.15090;,
 -138.31911;-68.31440;-260.45981;,
 -32.55040;-92.18210;-433.40640;,
 -2.18810;-111.98490;-440.63199;,
 -2.18810;-127.83560;-410.94250;,
 -90.87090;-97.74820;-343.32660;,
 -15.37250;-66.85060;-468.27551;,
 -2.18810;-78.07590;-463.23529;,
 -32.55040;-10.85470;-465.25491;,
 -2.18810;-1.14910;-482.69879;,
 -2.18810;32.85300;-468.53891;,
 -38.84480;4.24910;-445.16531;,
 -111.80260;-36.47530;-342.73929;,
 -53.09310;-48.75400;-427.37421;,
 -186.87750;-8.31880;-129.21530;,
 -160.21220;2.00210;-271.79691;,
 -123.48140;130.89571;-182.96880;,
 -112.54520;135.98891;-243.22060;,
 -149.76350;203.73090;-179.16960;,
 -136.60249;212.95180;-243.06250;,
 -141.63190;189.87790;-241.95100;,
 -156.75729;180.03510;-188.30850;,
 -89.15430;28.37780;-334.52539;,
 -140.50430;156.80969;-181.27361;,
 -123.48140;130.89571;-182.96880;,
 -77.88150;164.98320;-180.00870;,
 -122.58330;179.68610;-171.38480;,
 -122.58330;179.68610;-171.38480;,
 -77.88150;164.98320;-180.00870;,
 -78.83150;164.57291;-248.03180;,
 -108.17470;189.45689;-251.38811;,
 -122.66550;167.90710;-249.02319;,
 -112.54520;135.98891;-243.22060;,
 -122.66550;167.90710;-249.02319;,
 -112.54520;135.98891;-243.22060;,
 -149.76350;203.73090;-179.16960;,
 -75.20490;-122.21990;-340.67249;,
 -2.18810;-159.26390;-389.05350;,
 -2.18810;-135.45590;-261.01541;,
 -114.27140;-82.77820;-279.95380;,
 -57.86410;130.96030;-86.08540;,
 0.04680;152.54820;-89.24940;,
 -152.49020;-49.20570;39.87260;,
 -176.30420;-14.84970;9.91960;,
 -195.40720;34.99030;15.80660;,
 0.04680;-114.83070;-43.65840;,
 137.21730;30.17990;55.00780;,
 40.68900;97.53210;-16.50050;,
 123.81080;-4.79800;50.87640;,
 107.09800;-28.90920;71.89750;,
 0.04680;-74.96520;13.27500;,
 0.04680;112.68270;-18.72100;,
 -40.59540;97.53210;-16.50050;,
 -107.00440;-28.90920;71.89750;,
 -137.12370;30.17990;55.00780;,
 -123.71720;-4.79800;50.87640;,
 47.58660;-84.34750;-300.05960;,
 64.51490;-73.84640;-270.49481;,
 56.21700;-79.00660;-277.44989;,
 42.27910;-93.07840;-299.11261;,
 -17.44810;-95.08190;-324.18311;,
 -17.44810;-106.29470;-316.37369;,
 -49.08770;-84.34750;-300.05960;,
 -17.44810;-95.08190;-324.18311;,
 -17.44810;-106.29470;-316.37369;,
 -43.49860;-93.07840;-299.11261;,
 -66.01600;-73.84640;-270.49481;,
 -57.43640;-79.00660;-277.44989;;
 
 194;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;2,5,6,7;,
 4;3,2,7,8;,
 4;8,7,9,10;,
 4;7,6,11,9;,
 4;9,11,12,13;,
 4;10,9,13,14;,
 4;14,13,15,16;,
 4;13,12,17,15;,
 4;15,17,18,19;,
 4;16,15,19,20;,
 4;20,19,21,22;,
 4;19,18,23,21;,
 4;21,23,24,25;,
 4;22,21,25,26;,
 4;4,27,28,5;,
 4;27,29,30,28;,
 4;28,30,31,32;,
 4;5,28,32,6;,
 4;33,34,35,36;,
 4;34,0,3,35;,
 4;35,3,8,37;,
 4;36,35,37,38;,
 4;39,40,41,42;,
 4;42,41,43,44;,
 4;41,45,46,43;,
 4;40,47,45,41;,
 4;47,48,49,45;,
 4;45,49,50,46;,
 4;49,51,52,50;,
 4;48,53,51,49;,
 4;53,54,55,51;,
 4;51,55,56,52;,
 4;55,57,58,56;,
 4;54,59,57,55;,
 4;59,60,61,57;,
 4;57,61,62,58;,
 4;61,63,64,62;,
 4;60,65,63,61;,
 4;44,43,66,67;,
 4;67,66,68,69;,
 4;66,70,71,68;,
 4;43,46,70,66;,
 4;72,73,74,75;,
 4;75,74,40,39;,
 4;74,76,47,40;,
 4;73,77,76,74;,
 4;78,79,80,81;,
 4;79,82,83,80;,
 4;80,83,84,85;,
 4;81,80,85,86;,
 4;86,85,87,88;,
 4;85,84,89,87;,
 4;87,89,90,91;,
 4;88,87,91,92;,
 4;92,91,93,94;,
 4;91,90,95,93;,
 4;93,95,96,97;,
 4;94,93,97,98;,
 4;98,97,99,100;,
 4;97,96,101,99;,
 4;99,101,102,103;,
 4;100,99,103,104;,
 4;82,105,106,83;,
 4;105,107,108,106;,
 4;106,108,109,110;,
 4;83,106,110,84;,
 4;111,112,113,114;,
 4;112,78,81,113;,
 4;113,81,86,115;,
 4;114,113,115,116;,
 4;117,118,119,120;,
 4;120,119,121,122;,
 4;122,121,123,124;,
 4;124,123,125,126;,
 4;118,127,128,119;,
 4;129,117,120,130;,
 4;131,132,133,134;,
 4;132,135,136,133;,
 4;135,137,138,136;,
 4;137,139,140,138;,
 4;134,133,141,142;,
 4;143,144,132,131;,
 4;145,146,147,148;,
 4;148,147,149,150;,
 4;150,149,151,152;,
 4;152,151,153,154;,
 4;146,155,156,147;,
 4;157,145,148,158;,
 4;159,160,161,162;,
 4;160,163,164,161;,
 4;163,165,166,164;,
 4;165,167,168,166;,
 4;162,161,169,170;,
 4;171,172,160,159;,
 4;173,174,175,176;,
 4;177,173,176,178;,
 4;179,180,181,182;,
 4;183,184,185,186;,
 4;187,183,186,188;,
 4;189,187,188,190;,
 4;191,192,189,190;,
 4;191,177,178,192;,
 4;193,194,189,192;,
 4;193,184,183,194;,
 4;187,189,194,183;,
 4;195,181,180,196;,
 4;197,195,196,198;,
 4;199,200,201,202;,
 4;178,176,198,203;,
 4;204,205,206,207;,
 4;208,209,210,211;,
 4;212,213,210,209;,
 4;214,204,207,215;,
 4;200,216,205,204;,
 4;208,199,202,209;,
 4;209,202,201,212;,
 4;201,200,204,214;,
 4;193,196,180,184;,
 4;203,198,196,193;,
 4;203,193,192,178;,
 4;217,218,219,220;,
 4;221,175,174,222;,
 4;181,195,223,224;,
 4;195,197,225,223;,
 4;197,175,221,225;,
 4;182,181,224,226;,
 4;227,228,229,230;,
 4;231,232,228,227;,
 4;233,234,235,236;,
 4;237,238,239,240;,
 4;241,242,238,237;,
 4;243,244,242,241;,
 4;245,244,243,246;,
 4;245,246,232,231;,
 4;247,246,243,248;,
 4;247,248,237,240;,
 4;241,237,248,243;,
 4;249,250,236,235;,
 4;251,252,250,249;,
 4;253,254,255,256;,
 4;232,257,252,228;,
 4;258,259,260,261;,
 4;262,263,264,265;,
 4;266,265,264,267;,
 4;268,269,259,258;,
 4;256,258,261,270;,
 4;262,265,254,253;,
 4;265,266,255,254;,
 4;255,268,258,256;,
 4;247,240,236,250;,
 4;257,247,250,252;,
 4;257,232,246,247;,
 4;271,272,273,274;,
 4;275,276,230,229;,
 4;235,277,278,249;,
 4;249,278,279,251;,
 4;251,279,275,229;,
 4;234,280,277,235;,
 3;281,282,283;,
 3;283,282,284;,
 3;284,282,285;,
 3;282,286,285;,
 3;286,287,285;,
 3;285,287,288;,
 3;287,289,288;,
 3;289,290,288;,
 4;276,275,287,286;,
 4;275,279,289,287;,
 4;279,278,290,289;,
 4;278,277,288,290;,
 4;277,226,285,288;,
 4;226,224,284,285;,
 4;224,223,283,284;,
 4;223,225,281,283;,
 4;225,221,282,281;,
 4;221,276,286,282;,
 4;291,292,293,294;,
 4;180,179,219,218;,
 4;295,291,294,296;,
 4;297,298,299,300;,
 4;233,236,274,273;,
 4;301,297,300,302;,
 4;184,180,292,291;,
 4;180,218,293,292;,
 4;218,217,294,293;,
 4;185,184,291,295;,
 4;217,220,296,294;,
 4;240,239,298,297;,
 4;272,271,300,299;,
 4;236,240,297,301;,
 4;271,274,302,300;,
 4;274,236,301,302;;
 
 MeshMaterialList {
  9;
  194;
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
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
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
  7,
  0,
  0,
  0,
  7,
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
  7,
  0,
  0,
  0,
  7,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  6,
  0,
  6,
  6,
  0,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6;;
  Material {
   0.168000;0.056000;0.096000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.168000;0.056000;0.096000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.552000;0.536000;0.104000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.088000;0.016000;0.064000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.600000;0.600000;0.600000;1.000000;;
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
   0.248000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.400000;0.160000;0.248000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.096000;0.096000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  255;
  -0.768001;0.118922;-0.629310;,
  -0.902565;0.224905;-0.367144;,
  -0.598963;0.461605;-0.654343;,
  -0.714294;0.552441;-0.429642;,
  0.878436;-0.264960;0.397676;,
  0.763099;-0.174127;0.622383;,
  0.689594;-0.597910;0.408611;,
  0.555024;-0.491930;0.670786;,
  -0.538557;0.481983;-0.691121;,
  0.642285;-0.346745;0.683548;,
  0.614791;-0.569394;0.545731;,
  0.796037;-0.467834;0.384000;,
  0.475997;-0.525416;0.705241;,
  0.654800;-0.666232;0.356893;,
  -0.852881;0.152398;-0.499369;,
  -0.843834;0.384117;-0.374698;,
  -0.602911;0.582651;-0.544992;,
  -0.690088;0.263029;-0.674236;,
  -0.696727;0.606559;-0.382958;,
  0.858032;-0.135821;0.495312;,
  -0.757027;0.370360;-0.538278;,
  -0.460922;0.715031;-0.525625;,
  0.755299;-0.373387;0.538615;,
  0.490112;-0.691253;0.530998;,
  -0.895110;0.375470;-0.240417;,
  0.802217;-0.538171;0.258496;,
  0.768001;0.118921;-0.629311;,
  0.902566;0.224903;-0.367141;,
  0.598961;0.461606;-0.654343;,
  0.714294;0.552442;-0.429642;,
  -0.878435;-0.264962;0.397678;,
  -0.763098;-0.174126;0.622383;,
  -0.689595;-0.597909;0.408611;,
  -0.555025;-0.491929;0.670785;,
  0.538555;0.481986;-0.691121;,
  -0.642285;-0.346745;0.683547;,
  -0.614792;-0.569392;0.545732;,
  -0.796038;-0.467833;0.384001;,
  -0.476000;-0.525415;0.705240;,
  -0.654801;-0.666231;0.356893;,
  0.852882;0.152394;-0.499368;,
  0.843835;0.384117;-0.374695;,
  0.602910;0.582652;-0.544992;,
  0.690088;0.263029;-0.674237;,
  0.696726;0.606561;-0.382958;,
  -0.858031;-0.135823;0.495312;,
  0.757027;0.370360;-0.538279;,
  0.460917;0.715034;-0.525625;,
  -0.755299;-0.373386;0.538615;,
  -0.490115;-0.691250;0.530999;,
  0.895111;0.375471;-0.240413;,
  -0.802217;-0.538169;0.258498;,
  0.368121;-0.371619;-0.852283;,
  -0.368120;-0.371619;-0.852283;,
  0.274551;0.358652;-0.892183;,
  -0.274550;0.358652;-0.892183;,
  0.274552;0.358653;0.892182;,
  -0.274550;0.358653;0.892183;,
  0.368123;-0.371621;0.852281;,
  -0.368122;-0.371620;0.852282;,
  0.355044;0.464870;-0.811073;,
  -0.363183;-0.050358;0.930356;,
  0.000000;-0.360886;0.932610;,
  0.363184;-0.050358;0.930355;,
  -0.462633;-0.467244;0.753428;,
  0.462635;-0.467244;0.753427;,
  -0.000000;-0.360884;-0.932611;,
  -0.363181;-0.050358;-0.930357;,
  -0.000000;0.404713;-0.914443;,
  0.363182;-0.050358;-0.930356;,
  -0.355042;0.464870;-0.811074;,
  -0.000000;0.404715;0.914443;,
  -0.000000;-0.008242;-0.999966;,
  -0.000000;0.642820;-0.766017;,
  -0.000000;-0.008242;0.999966;,
  0.000000;-0.568307;0.822816;,
  -0.586232;-0.091240;-0.804989;,
  0.586243;-0.091241;0.804981;,
  -0.704045;0.000000;-0.710156;,
  -0.007409;0.999947;0.007194;,
  0.689228;0.000000;0.724545;,
  0.704045;0.000000;-0.710156;,
  0.007408;0.999947;0.007195;,
  -0.689228;0.000000;0.724544;,
  -0.704044;-0.075148;-0.706169;,
  -0.007418;0.995096;-0.098638;,
  0.689228;0.076669;0.720477;,
  0.704044;-0.075148;-0.706169;,
  0.007419;0.995096;-0.098639;,
  -0.689228;0.076751;0.720467;,
  0.333675;0.849523;0.408622;,
  0.662350;-0.749040;0.015188;,
  0.978168;-0.186399;-0.091889;,
  0.985360;-0.032810;-0.167299;,
  0.626762;0.539214;-0.562511;,
  0.660735;-0.479483;-0.577516;,
  0.475931;-0.357572;-0.803512;,
  0.667373;0.011479;-0.744635;,
  0.754390;0.390201;-0.527863;,
  0.644822;0.511170;-0.568252;,
  0.825827;-0.153216;-0.542710;,
  0.848438;0.054436;-0.526488;,
  0.692399;0.420745;-0.586138;,
  -0.000267;-0.999956;0.009358;,
  0.598739;-0.799965;-0.039581;,
  0.933121;-0.018917;-0.359064;,
  0.133326;0.969247;0.206845;,
  0.452139;0.749172;-0.484058;,
  0.858209;0.206192;-0.470066;,
  0.942549;-0.189718;-0.274969;,
  0.950712;0.245330;-0.189633;,
  0.286160;-0.210950;0.934672;,
  -0.571217;0.806551;0.152275;,
  0.163984;-0.082324;-0.983022;,
  0.902391;-0.338692;0.266417;,
  0.996224;-0.010427;-0.086186;,
  0.455530;-0.844782;0.280778;,
  0.000079;0.896466;0.443112;,
  0.203331;-0.973091;0.108403;,
  0.765040;-0.456049;-0.454680;,
  0.000872;-0.913306;0.407273;,
  0.000080;0.981417;0.191889;,
  -0.000000;-0.417956;-0.908467;,
  0.554715;0.616660;-0.558590;,
  -0.455535;-0.839622;0.295843;,
  -0.877845;-0.191125;0.439158;,
  -0.998325;-0.003197;-0.057763;,
  -0.133674;0.967308;0.215513;,
  -0.980482;-0.180642;-0.077611;,
  -0.663866;-0.747387;0.026347;,
  0.000906;-0.995174;0.098119;,
  -0.765039;-0.456049;-0.454680;,
  -0.660735;-0.479484;-0.577516;,
  -0.475931;-0.357572;-0.803512;,
  -0.667373;0.011479;-0.744635;,
  -0.000001;0.125990;-0.992032;,
  -0.754389;0.390201;-0.527863;,
  -0.825827;-0.153216;-0.542711;,
  -0.933201;-0.016812;-0.358963;,
  -0.858239;0.208021;-0.469205;,
  -0.453173;0.748884;-0.483537;,
  -0.598689;-0.799914;-0.041333;,
  -0.987170;-0.027943;-0.157212;,
  -0.945940;-0.174632;-0.273316;,
  -0.943905;0.274924;-0.182920;,
  -0.258985;-0.180617;0.948843;,
  0.571182;0.806580;0.152246;,
  -0.131693;-0.052115;-0.989920;,
  -0.848468;0.054637;-0.526419;,
  -0.627407;0.538916;-0.562076;,
  -0.693149;0.420624;-0.585337;,
  -0.333647;0.845911;0.416070;,
  0.000000;0.921465;-0.388461;,
  0.209941;-0.711858;-0.670211;,
  0.000000;0.566729;0.823904;,
  0.079130;0.577191;0.812766;,
  0.050709;0.691938;0.720174;,
  -0.741896;-0.163924;0.650169;,
  0.446958;0.342887;0.826231;,
  0.000000;0.237157;0.971471;,
  0.072959;0.424129;0.902658;,
  0.225795;0.192409;0.954984;,
  -0.541452;0.109067;0.833627;,
  -0.084487;0.545004;0.834166;,
  0.417323;-0.899413;0.129994;,
  0.398145;-0.890312;0.220965;,
  -0.001061;-0.990078;0.140515;,
  -0.001568;-0.970667;0.240422;,
  -0.401020;-0.889304;0.219822;,
  -0.419388;-0.899124;0.125259;,
  0.400162;-0.908468;0.120650;,
  0.585447;-0.629420;-0.510962;,
  0.699572;-0.707545;-0.099898;,
  0.361198;-0.432901;-0.825913;,
  -0.692272;-0.619558;-0.370011;,
  -0.388080;-0.912331;0.130561;,
  -0.683413;-0.725528;-0.080967;,
  0.896327;0.047562;0.440836;,
  0.752995;-0.106400;0.649367;,
  0.911174;-0.230972;0.341194;,
  -0.891516;-0.011770;-0.452836;,
  -0.938107;0.170036;-0.301732;,
  -0.759314;0.029219;-0.650068;,
  0.535428;-0.328062;0.778262;,
  -0.628334;0.165361;-0.760166;,
  -0.896326;0.047556;0.440838;,
  -0.752994;-0.106400;0.649368;,
  -0.911172;-0.230976;0.341197;,
  0.891517;-0.011779;-0.452833;,
  0.938110;0.170033;-0.301727;,
  0.759314;0.029216;-0.650068;,
  -0.535430;-0.328061;0.778261;,
  0.628334;0.165362;-0.760166;,
  -0.000000;0.642827;0.766012;,
  -0.355045;0.464874;0.811070;,
  0.355047;0.464874;0.811069;,
  -0.000000;-0.568298;-0.822823;,
  -0.462628;-0.467239;-0.753434;,
  0.462630;-0.467239;-0.753433;,
  -0.586240;-0.091241;0.804983;,
  0.586235;-0.091240;-0.804987;,
  -0.007409;-0.999947;0.007194;,
  -0.717442;0.000000;0.696619;,
  0.717421;0.000000;-0.696640;,
  0.007408;-0.999947;0.007195;,
  0.717339;0.000000;0.696724;,
  -0.717410;0.000000;-0.696652;,
  -0.007442;-0.993578;0.112900;,
  -0.717393;0.073809;0.692748;,
  0.717393;-0.073719;-0.692757;,
  0.007447;-0.993579;0.112897;,
  0.717392;0.073808;0.692749;,
  -0.717375;-0.073731;-0.692774;,
  0.091743;-0.258153;0.961738;,
  -0.502719;0.860579;0.081713;,
  0.020453;-0.170801;-0.985093;,
  0.811710;-0.514354;-0.276706;,
  0.468913;-0.155148;0.869511;,
  -0.632523;0.742367;0.220920;,
  0.302853;0.008493;-0.953000;,
  0.489941;0.812152;0.316808;,
  0.371457;0.839344;0.396890;,
  -0.554714;0.616660;-0.558590;,
  -0.560705;-0.727096;-0.396157;,
  -0.644822;0.511169;-0.568252;,
  -0.066264;-0.229340;0.971088;,
  0.502719;0.860579;0.081713;,
  0.011177;-0.147146;-0.989052;,
  -0.811710;-0.514355;-0.276705;,
  -0.441345;-0.124669;0.888635;,
  0.632461;0.742436;0.220864;,
  -0.270686;0.044450;-0.961641;,
  -0.490703;0.805676;0.331807;,
  -0.371679;0.835705;0.404292;,
  -0.753081;-0.354139;0.554486;,
  -0.824385;-0.083314;0.559865;,
  -0.549024;-0.302464;0.779159;,
  -0.625246;0.219541;0.748912;,
  -0.000000;-0.819150;0.573580;,
  -0.038291;-0.818549;0.573159;,
  0.038291;-0.818549;0.573159;,
  0.625245;0.219541;0.748913;,
  0.549023;-0.302464;0.779159;,
  0.245101;0.848750;0.468561;,
  -0.635465;-0.454819;-0.623958;,
  0.034094;-0.943050;0.330900;,
  0.026233;0.787586;-0.615646;,
  0.028984;0.808666;-0.587554;,
  0.008419;0.819917;-0.572421;,
  -0.008383;-0.939128;0.343465;,
  0.004063;0.810473;-0.585762;,
  -0.041839;-0.942266;0.332241;,
  -0.003721;0.820098;-0.572210;,
  -0.027812;0.808957;-0.587210;,
  -0.025157;0.787739;-0.615495;;
  194;
  4;0,14,20,17;,
  4;14,1,15,20;,
  4;20,15,3,16;,
  4;17,20,16,2;,
  4;2,16,21,8;,
  4;16,3,18,21;,
  4;177,178,5,19;,
  4;179,177,19,4;,
  4;4,19,22,11;,
  4;19,5,9,22;,
  4;22,9,7,10;,
  4;11,22,10,6;,
  4;6,10,23,13;,
  4;10,7,12,23;,
  4;180,181,1,14;,
  4;182,180,14,0;,
  4;1,181,24,15;,
  4;12,7,9,183;,
  4;183,9,5,178;,
  4;15,24,18,3;,
  4;6,13,25,11;,
  4;182,0,17,184;,
  4;184,17,2,8;,
  4;11,25,179,4;,
  4;26,43,46,40;,
  4;40,46,41,27;,
  4;46,42,29,41;,
  4;43,28,42,46;,
  4;28,34,47,42;,
  4;42,47,44,29;,
  4;185,45,31,186;,
  4;187,30,45,185;,
  4;30,37,48,45;,
  4;45,48,35,31;,
  4;48,36,33,35;,
  4;37,32,36,48;,
  4;32,39,49,36;,
  4;36,49,38,33;,
  4;188,40,27,189;,
  4;190,26,40,188;,
  4;27,41,50,189;,
  4;38,191,35,33;,
  4;191,186,31,35;,
  4;41,29,44,50;,
  4;32,37,51,39;,
  4;190,192,43,26;,
  4;192,34,28,43;,
  4;37,30,187,51;,
  4;52,66,72,69;,
  4;66,53,67,72;,
  4;72,67,55,68;,
  4;69,72,68,54;,
  4;54,68,73,60;,
  4;68,55,70,73;,
  4;193,194,57,71;,
  4;195,193,71,56;,
  4;56,71,74,63;,
  4;71,57,61,74;,
  4;74,61,59,62;,
  4;63,74,62,58;,
  4;58,62,75,65;,
  4;62,59,64,75;,
  4;196,197,53,66;,
  4;198,196,66,52;,
  4;53,197,76,67;,
  4;64,59,61,199;,
  4;199,61,57,194;,
  4;67,76,70,55;,
  4;58,65,77,63;,
  4;198,52,69,200;,
  4;200,69,54,60;,
  4;63,77,195,56;,
  4;78,78,78,78;,
  4;79,79,79,79;,
  4;80,80,80,80;,
  4;201,201,201,201;,
  4;202,202,202,202;,
  4;203,203,203,203;,
  4;81,81,81,81;,
  4;82,82,82,82;,
  4;83,83,83,83;,
  4;204,204,204,204;,
  4;205,205,205,205;,
  4;206,206,206,206;,
  4;84,84,84,84;,
  4;85,85,85,85;,
  4;86,86,86,86;,
  4;207,207,207,207;,
  4;208,208,208,208;,
  4;209,209,209,209;,
  4;87,87,87,87;,
  4;88,88,88,88;,
  4;89,89,89,89;,
  4;210,210,210,210;,
  4;211,211,211,211;,
  4;212,212,212,212;,
  4;152,121,106,107;,
  4;123,152,107,94;,
  4;103,104,91,130;,
  4;95,119,118,153;,
  4;96,95,153,122;,
  4;97,96,122,135;,
  4;99,98,97,135;,
  4;99,123,94,98;,
  4;101,100,97,98;,
  4;101,119,95,100;,
  4;96,97,100,95;,
  4;92,91,104,105;,
  4;93,92,105,108;,
  4;110,109,109,110;,
  4;94,107,108,102;,
  4;111,111,213,213;,
  4;112,112,214,106;,
  4;113,215,215,113;,
  4;216,216,93,108;,
  4;217,217,111,111;,
  4;112,218,218,112;,
  4;113,219,219,113;,
  4;109,109,216,216;,
  4;101,105,104,119;,
  4;102,108,105,101;,
  4;102,101,98,94;,
  4;165,164,166,167;,
  4;90,106,121,117;,
  4;91,92,114,116;,
  4;92,93,115,114;,
  4;220,106,90,221;,
  4;130,91,116,120;,
  4;152,140,127,121;,
  4;222,149,140,152;,
  4;103,130,129,141;,
  4;132,223,223,131;,
  4;133,122,153,132;,
  4;134,135,122,133;,
  4;224,135,134,136;,
  4;224,136,149,222;,
  4;148,136,134,137;,
  4;148,137,132,131;,
  4;133,132,137,134;,
  4;128,138,141,129;,
  4;142,139,138,128;,
  4;144,144,143,143;,
  4;149,150,139,140;,
  4;145,225,225,145;,
  4;146,127,226,146;,
  4;147,147,227,227;,
  4;228,139,142,228;,
  4;229,145,145,229;,
  4;146,146,230,230;,
  4;147,147,231,231;,
  4;143,228,228,143;,
  4;148,131,141,138;,
  4;150,148,138,139;,
  4;150,149,136,148;,
  4;168,167,166,169;,
  4;151,117,121,127;,
  4;129,124,125,128;,
  4;128,125,126,142;,
  4;232,233,151,127;,
  4;130,120,124,129;,
  3;162,163,161;,
  3;161,163,160;,
  3;160,163,159;,
  3;163,154,159;,
  3;154,155,159;,
  3;159,155,158;,
  3;155,156,158;,
  3;234,157,235;,
  4;117,151,155,154;,
  4;151,233,156,155;,
  4;236,125,157,234;,
  4;125,237,235,157;,
  4;124,120,238,239;,
  4;120,116,240,238;,
  4;241,241,161,160;,
  4;114,242,242,161;,
  4;221,90,163,243;,
  4;90,117,154,163;,
  4;171,170,172,171;,
  4;104,103,166,164;,
  4;173,171,171,173;,
  4;174,244,244,174;,
  4;103,141,169,166;,
  4;175,174,174,176;,
  4;245,104,170,245;,
  4;246,247,247,246;,
  4;247,248,248,247;,
  4;118,245,245,249;,
  4;248,250,250,248;,
  4;251,118,249,251;,
  4;250,252,252,250;,
  4;141,251,251,175;,
  4;252,253,253,252;,
  4;253,254,254,253;;
 }
 MeshTextureCoords {
  303;
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.375000;0.125000;,
  0.625000;0.000000;,
  0.625000;0.125000;,
  0.625000;0.250000;,
  0.500000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.375000;,
  0.375000;0.375000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.500000;0.500000;,
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
  0.625000;1.000000;,
  0.500000;1.000000;,
  0.375000;1.000000;,
  0.750000;0.000000;,
  0.750000;0.125000;,
  0.875000;0.000000;,
  0.875000;0.125000;,
  0.875000;0.250000;,
  0.750000;0.250000;,
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.125000;,
  0.125000;0.125000;,
  0.250000;0.250000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.125000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.750000;0.125000;,
  0.750000;0.000000;,
  0.875000;0.125000;,
  0.875000;0.000000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.125000;,
  0.250000;0.125000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.375000;0.125000;,
  0.625000;0.000000;,
  0.625000;0.125000;,
  0.625000;0.250000;,
  0.500000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.375000;,
  0.375000;0.375000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.500000;0.500000;,
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
  0.625000;1.000000;,
  0.500000;1.000000;,
  0.375000;1.000000;,
  0.750000;0.000000;,
  0.750000;0.125000;,
  0.875000;0.000000;,
  0.875000;0.125000;,
  0.875000;0.250000;,
  0.750000;0.250000;,
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.125000;,
  0.125000;0.125000;,
  0.250000;0.250000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.000000;,
  0.375000;0.500000;,
  0.625000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;0.250000;,
  0.875000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.000000;,
  0.375000;0.500000;,
  0.625000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;0.250000;,
  0.875000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.575400;0.793600;,
  0.583900;0.743700;,
  0.626400;0.761000;,
  0.617600;0.783100;,
  0.582400;0.869900;,
  0.619900;0.865900;,
  0.779800;0.867200;,
  0.713900;0.826400;,
  0.747300;0.771300;,
  0.816200;0.810200;,
  0.666100;0.941600;,
  0.691400;0.895800;,
  0.691700;0.961900;,
  0.674700;0.965400;,
  0.650300;0.951100;,
  0.648500;0.969600;,
  0.633000;0.937800;,
  0.617000;0.954100;,
  0.603500;0.932300;,
  0.631200;0.918900;,
  0.669300;0.880900;,
  0.652000;0.929200;,
  0.713700;0.759900;,
  0.684200;0.815100;,
  0.645700;0.760900;,
  0.633400;0.789000;,
  0.959700;0.067600;,
  0.961500;0.076400;,
  0.932400;0.073800;,
  0.937100;0.067900;,
  0.643600;0.868500;,
  0.960400;0.093400;,
  0.972800;0.092800;,
  0.970600;0.109900;,
  0.956000;0.108900;,
  0.961500;0.052900;,
  0.930200;0.058500;,
  0.925600;0.044000;,
  0.952900;0.036100;,
  0.920500;0.061100;,
  0.915100;0.047100;,
  0.924900;0.087600;,
  0.925200;0.105800;,
  0.969700;0.076100;,
  0.691400;0.895800;,
  0.713900;0.826400;,
  0.779800;0.867200;,
  0.691700;0.961900;,
  0.626500;0.718900;,
  0.584600;0.717900;,
  0.746000;0.685400;,
  0.770400;0.684100;,
  0.726900;0.671800;,
  0.836500;0.782700;,
  0.424600;0.793600;,
  0.382400;0.783100;,
  0.373600;0.761000;,
  0.416100;0.743700;,
  0.417600;0.869900;,
  0.380100;0.865900;,
  0.220200;0.867200;,
  0.183800;0.810200;,
  0.252700;0.771300;,
  0.286100;0.826400;,
  0.333900;0.941600;,
  0.325300;0.965400;,
  0.308300;0.961900;,
  0.308600;0.895800;,
  0.349700;0.951100;,
  0.351500;0.969600;,
  0.367000;0.937800;,
  0.383000;0.954100;,
  0.396500;0.932300;,
  0.368800;0.918900;,
  0.330700;0.880900;,
  0.348000;0.929200;,
  0.286300;0.759900;,
  0.315800;0.815100;,
  0.354300;0.760900;,
  0.366600;0.789000;,
  0.040300;0.067600;,
  0.062900;0.067900;,
  0.067600;0.073800;,
  0.038600;0.076400;,
  0.356400;0.868500;,
  0.039600;0.093400;,
  0.044000;0.108900;,
  0.029500;0.110000;,
  0.027300;0.092800;,
  0.038600;0.052900;,
  0.047100;0.036100;,
  0.074400;0.044000;,
  0.069800;0.058500;,
  0.079500;0.061100;,
  0.084900;0.047100;,
  0.075100;0.087600;,
  0.074800;0.105800;,
  0.030300;0.076100;,
  0.308600;0.895800;,
  0.308300;0.961900;,
  0.220200;0.867200;,
  0.286100;0.826400;,
  0.373500;0.718900;,
  0.415400;0.718000;,
  0.229600;0.684100;,
  0.254000;0.685400;,
  0.273100;0.671800;,
  0.163500;0.782700;,
  0.726900;0.671800;,
  0.626500;0.718900;,
  0.746000;0.685400;,
  0.770400;0.684100;,
  0.836500;0.782700;,
  0.415400;0.718000;,
  0.373500;0.718900;,
  0.229600;0.684100;,
  0.273100;0.671800;,
  0.254000;0.685400;,
  0.691400;0.895800;,
  0.713900;0.826400;,
  0.713900;0.826400;,
  0.691400;0.895800;,
  0.691700;0.961900;,
  0.691700;0.961900;,
  0.308600;0.895800;,
  0.308300;0.961900;,
  0.308300;0.961900;,
  0.308600;0.895800;,
  0.286100;0.826400;,
  0.286100;0.826400;;
 }
}