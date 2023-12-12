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
 184;
 -7.46401;25.18797;-16.51876;,
 14.10871;25.18797;-16.51876;,
 14.10871;20.96677;-16.51876;,
 -7.46401;20.96677;-16.51876;,
 14.10871;25.18797;-16.51876;,
 14.10871;25.18797;4.28625;,
 14.10871;20.96677;4.28625;,
 14.10871;20.96677;-16.51876;,
 14.10871;25.18797;4.28625;,
 -7.46401;25.18797;4.28625;,
 -7.46401;20.96677;4.28625;,
 14.10871;20.96677;4.28625;,
 -7.46401;25.18797;4.28625;,
 -7.46401;25.18797;-16.51876;,
 -7.46401;20.96677;-16.51876;,
 -7.46401;20.96677;4.28625;,
 14.10871;25.18797;-16.51876;,
 -7.46401;25.18797;-16.51876;,
 -7.46401;20.96677;-16.51876;,
 14.10871;20.96677;-16.51876;,
 -1.49573;41.56349;-10.88029;,
 8.61987;41.56349;-10.88029;,
 8.61987;39.23794;-10.88029;,
 -1.49573;39.23794;-10.88029;,
 8.61987;20.92970;-10.88029;,
 -1.49573;20.92970;-10.88029;,
 8.61987;41.56349;-10.88029;,
 8.61987;41.56349;0.86571;,
 8.61987;39.23794;0.86571;,
 8.61987;39.23794;-10.88029;,
 8.61987;20.92970;0.86571;,
 8.61987;20.92970;-10.88029;,
 8.61987;41.56349;0.86571;,
 -1.49573;41.56349;0.86571;,
 -1.49573;39.23794;0.86571;,
 8.61987;39.23794;0.86571;,
 -1.49573;20.92970;0.86571;,
 8.61987;20.92970;0.86571;,
 -1.49573;41.56349;0.86571;,
 -1.49573;41.56349;-10.88029;,
 -1.49573;39.23794;-10.88029;,
 -1.49573;39.23794;0.86571;,
 -1.49573;20.92970;-10.88029;,
 -1.49573;20.92970;0.86571;,
 8.61987;41.56349;-10.88029;,
 -1.49573;41.56349;-10.88029;,
 -1.49573;20.92970;-10.88029;,
 8.61987;20.92970;-10.88029;,
 12.53053;6.36849;-59.40350;,
 12.52675;3.86075;-54.32141;,
 12.40968;0.21351;-47.82034;,
 12.41406;-0.00022;-58.35242;,
 14.01674;25.70379;-16.90936;,
 -6.78512;25.70379;-17.27249;,
 -6.90158;23.83211;-10.59846;,
 13.90028;23.83211;-10.23541;,
 -8.27509;3.86075;-54.68452;,
 -8.27134;6.36849;-59.96679;,
 -8.38779;-0.00022;-58.71557;,
 -8.39217;0.05375;-47.84239;,
 -8.27134;6.36849;-59.96679;,
 12.53053;6.36849;-59.40350;,
 12.41406;-0.00022;-58.35242;,
 -8.38779;-0.00022;-58.71557;,
 12.52675;3.86075;-54.32141;,
 12.53053;6.36849;-59.40350;,
 12.41406;-0.00022;-58.35242;,
 12.40968;0.21351;-47.82034;,
 12.52101;9.04284;-38.84825;,
 -8.28085;9.04284;-39.21138;,
 14.01674;25.70379;-16.90936;,
 12.52101;9.04284;-38.84825;,
 14.01674;25.70379;-16.90936;,
 13.90028;23.83211;-10.23541;,
 12.40401;7.47224;-29.32470;,
 -8.28085;9.04284;-39.21138;,
 -8.39785;8.20073;-29.39096;,
 -6.90158;23.83211;-10.59846;,
 -6.78512;25.70379;-17.27249;,
 12.40401;7.47224;-29.32470;,
 13.90028;23.83211;-10.23541;,
 -8.39785;8.20073;-29.39096;,
 56.24534;6.36808;5.10272;,
 51.47923;4.13765;5.10087;,
 49.58808;-0.18280;5.04229;,
 58.49659;0.67304;5.04452;,
 13.64301;24.79521;5.14740;,
 13.82458;24.79682;-15.65684;,
 7.15209;20.76946;-15.71511;,
 6.97052;21.82569;5.08913;,
 51.66079;4.13919;-15.70337;,
 56.42692;6.36970;-15.70152;,
 58.67816;0.67457;-15.75979;,
 49.86007;0.00314;-15.69315;,
 56.42692;6.36970;-15.70152;,
 56.24534;6.36808;5.10272;,
 58.49659;0.67304;5.04452;,
 58.67816;0.67457;-15.75979;,
 51.47923;4.13765;5.10087;,
 56.24534;6.36808;5.10272;,
 58.49659;0.67304;5.04452;,
 49.58808;-0.18280;5.04229;,
 38.52753;8.48111;-15.69861;,
 13.64301;24.79521;5.14740;,
 38.34597;8.47957;5.10563;,
 38.52753;8.48111;-15.69861;,
 34.51686;5.33901;-15.69538;,
 7.15209;20.76946;-15.71511;,
 13.82458;24.79682;-15.65684;,
 38.34597;8.47957;5.10563;,
 13.64301;24.79521;5.14740;,
 6.97052;21.82569;5.08913;,
 35.27852;6.45688;5.04713;,
 34.51686;5.33901;-15.69538;,
 35.27852;6.45688;5.04713;,
 6.97052;21.82569;5.08913;,
 -11.75920;7.00359;54.71368;,
 -11.04676;5.42802;49.50205;,
 -11.13075;1.15324;44.95826;,
 -11.90215;0.49401;58.85695;,
 -6.91056;25.55048;3.95706;,
 13.88730;25.49981;4.50252;,
 14.23668;23.75472;-1.25264;,
 -6.56110;23.80531;-1.79818;,
 9.75102;5.37735;50.04753;,
 9.03859;6.95292;55.25908;,
 8.89564;0.52794;59.40241;,
 8.85594;0.00129;46.76478;,
 9.03859;6.95292;55.25908;,
 -11.75920;7.00359;54.71368;,
 -11.90215;0.49401;58.85695;,
 8.89564;0.52794;59.40241;,
 -11.04676;5.42802;49.50205;,
 -11.75920;7.00359;54.71368;,
 -11.90215;0.49401;58.85695;,
 -11.13075;1.15324;44.95826;,
 10.55788;7.69700;34.22995;,
 -6.91056;25.55048;3.95706;,
 -10.23990;7.74766;33.68451;,
 10.55788;7.69700;34.22995;,
 10.03161;3.33317;29.69646;,
 14.23668;23.75472;-1.25264;,
 13.88730;25.49981;4.50252;,
 -10.23990;7.74766;33.68451;,
 -6.91056;25.55048;3.95706;,
 -6.56110;23.80531;-1.79818;,
 -9.83801;4.58185;25.74335;,
 10.03161;3.33317;29.69646;,
 -9.83801;4.58185;25.74335;,
 -6.56110;23.80531;-1.79818;,
 -58.67987;5.18757;-16.41887;,
 -48.67649;4.10126;-16.42079;,
 -45.59535;0.90773;-16.47922;,
 -55.55781;-0.00163;-16.47706;,
 -7.89232;25.86024;-16.64919;,
 -7.71075;25.86024;4.15505;,
 -2.08457;24.41073;4.09686;,
 -2.26613;24.41073;-16.70738;,
 -48.49494;4.10126;4.38344;,
 -58.49830;5.18757;4.38536;,
 -55.37618;-0.00163;4.32709;,
 -45.64626;1.22986;4.11874;,
 -58.49830;5.18757;4.38536;,
 -58.67987;5.18757;-16.41887;,
 -55.55781;-0.00163;-16.47706;,
 -55.37618;-0.00163;4.32709;,
 -48.67649;4.10126;-16.42079;,
 -58.67987;5.18757;-16.41887;,
 -55.55781;-0.00163;-16.47706;,
 -45.59535;0.90773;-16.47922;,
 -36.51945;6.58094;-16.45688;,
 -36.33781;7.53175;4.34736;,
 -7.89232;25.86024;-16.64919;,
 -36.51945;6.58094;-16.45688;,
 -7.89232;25.86024;-16.64919;,
 -2.26613;24.41073;-16.70738;,
 -29.45458;4.72376;-16.51522;,
 -36.33781;7.53175;4.34736;,
 -29.46880;5.03223;4.11528;,
 -2.08457;24.41073;4.09686;,
 -7.71075;25.86024;4.15505;,
 -29.45458;4.72376;-16.51522;,
 -2.26613;24.41073;-16.70738;,
 -29.46880;5.03223;4.11528;;
 
 72;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;23,22,24,25;,
 4;26,27,28,29;,
 4;29,28,30,31;,
 4;32,33,34,35;,
 4;35,34,36,37;,
 4;38,39,40,41;,
 4;41,40,42,43;,
 4;38,27,44,45;,
 4;46,47,30,43;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;60,56,64,65;,
 4;66,67,59,63;,
 4;68,64,56,69;,
 4;68,69,53,70;,
 4;71,72,73,74;,
 4;71,74,50,49;,
 4;75,56,59,76;,
 4;75,76,77,78;,
 4;79,80,54,81;,
 4;79,81,59,67;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;94,95,96,97;,
 4;94,90,98,99;,
 4;100,101,93,97;,
 4;102,87,103,104;,
 4;102,104,98,90;,
 4;105,90,93,106;,
 4;105,106,107,108;,
 4;109,110,111,112;,
 4;109,112,84,83;,
 4;113,93,101,114;,
 4;113,114,115,88;,
 4;116,117,118,119;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;128,124,132,133;,
 4;134,135,127,131;,
 4;136,121,137,138;,
 4;136,138,132,124;,
 4;139,124,127,140;,
 4;139,140,141,142;,
 4;143,144,145,146;,
 4;143,146,118,117;,
 4;147,127,135,148;,
 4;147,148,149,122;,
 4;150,151,152,153;,
 4;154,155,156,157;,
 4;158,159,160,161;,
 4;162,163,164,165;,
 4;162,158,166,167;,
 4;168,169,161,165;,
 4;170,166,158,171;,
 4;170,171,155,172;,
 4;173,174,175,176;,
 4;173,176,152,151;,
 4;177,158,161,178;,
 4;177,178,179,180;,
 4;181,182,156,183;,
 4;181,183,161,169;;
 
 MeshMaterialList {
  4;
  72;
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  1,
  2,
  1,
  2,
  1,
  2,
  1,
  2,
  1,
  3,
  1,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  3,
  1,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  3,
  1,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  3,
  1,
  3,
  3,
  3,
  3,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.583200;0.583200;0.620800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.000000;1.000000;;
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
   0.398400;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  84;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.999679;-0.025011;-0.003992;,
  0.999738;-0.022798;0.001929;,
  0.003269;0.982308;-0.187245;,
  -0.004712;0.962863;0.269948;,
  -0.999742;0.022636;-0.002112;,
  -0.999682;0.024881;0.004119;,
  0.008163;0.883889;-0.467625;,
  0.998593;-0.052989;0.001872;,
  -0.998450;0.055552;-0.003366;,
  0.021919;-0.178174;-0.983755;,
  -0.009669;0.900052;0.435676;,
  -0.002227;0.997962;0.063773;,
  0.003785;-0.999913;0.012628;,
  -0.004834;-0.979304;0.202338;,
  0.996344;-0.085337;-0.004109;,
  -0.995882;0.090643;0.001614;,
  -0.016908;-0.853113;0.521452;,
  -0.020141;-0.763130;0.645932;,
  0.002404;-0.011395;0.999932;,
  -0.001617;-0.013012;0.999914;,
  -0.462206;0.886399;-0.025758;,
  -0.003128;0.001688;-0.999994;,
  -0.005668;0.004806;-0.999972;,
  0.436314;0.899786;0.003875;,
  0.000532;0.001154;-0.999999;,
  -0.006026;-0.013831;0.999886;,
  0.929975;0.367533;0.008144;,
  -0.423863;0.905719;-0.003631;,
  -0.059172;0.998248;-0.000442;,
  0.085784;-0.996308;-0.003541;,
  -0.148764;-0.988813;0.010850;,
  0.551117;0.834414;0.004873;,
  0.001652;0.003738;-0.999992;,
  -0.006414;-0.013034;0.999894;,
  -0.430113;-0.901945;0.038714;,
  -0.483487;-0.873767;0.052639;,
  -0.996270;0.010265;-0.085682;,
  -0.997234;0.028280;-0.068742;,
  -0.000783;0.992527;0.122021;,
  0.009926;0.957092;-0.289613;,
  0.992583;-0.112396;0.046332;,
  0.996490;-0.056356;0.061901;,
  -0.006501;0.942062;0.335376;,
  0.989293;-0.139657;0.042370;,
  -0.996540;0.052936;-0.064082;,
  -0.021849;0.539671;0.841593;,
  0.009889;0.957540;-0.288132;,
  0.004352;0.997300;-0.073303;,
  -0.026239;-0.999646;-0.004310;,
  -0.029620;-0.994999;-0.095397;,
  0.992333;-0.111127;0.054093;,
  -0.995296;0.059582;-0.076393;,
  0.000834;-0.925024;-0.379907;,
  0.034386;-0.829041;-0.558129;,
  -0.000318;0.014248;-0.999898;,
  -0.002830;0.013365;-0.999907;,
  -0.163749;0.986462;-0.008930;,
  0.249468;0.968381;-0.002177;,
  0.016047;-0.050079;0.998616;,
  0.014117;-0.037399;0.999201;,
  -0.398249;0.917114;-0.017298;,
  -0.006998;0.007487;-0.999947;,
  0.016923;-0.040625;0.999031;,
  -0.856807;-0.515583;0.007479;,
  0.107960;0.994155;-0.000942;,
  -0.064928;0.997834;-0.010597;,
  0.108238;-0.994098;0.007352;,
  0.169157;-0.985524;0.011321;,
  -0.008654;0.002491;-0.999959;,
  0.015862;-0.018479;0.999703;,
  0.413602;-0.910406;0.009675;,
  0.582099;-0.813110;0.003736;;
  72;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,13,13,12;,
  4;14,14,15,15;,
  4;16,17,17,16;,
  4;21,21,21,21;,
  4;22,23,23,22;,
  4;24,25,25,24;,
  4;18,23,23,18;,
  4;18,18,14,14;,
  4;19,26,26,19;,
  4;19,19,13,13;,
  4;20,16,16,20;,
  4;20,20,27,27;,
  4;28,29,29,28;,
  4;28,28,25,25;,
  4;30,31,31,30;,
  4;32,32,32,32;,
  4;33,34,34,33;,
  4;38,38,38,38;,
  4;39,40,40,39;,
  4;41,42,42,41;,
  4;35,43,43,35;,
  4;35,35,40,40;,
  4;36,33,33,36;,
  4;36,36,44,44;,
  4;37,45,45,37;,
  4;37,37,31,31;,
  4;46,42,42,46;,
  4;46,46,47,47;,
  4;48,49,49,48;,
  4;50,50,51,51;,
  4;52,53,53,52;,
  4;57,57,57,57;,
  4;58,59,59,58;,
  4;60,61,61,60;,
  4;54,50,50,54;,
  4;54,54,59,59;,
  4;55,52,52,55;,
  4;55,55,62,62;,
  4;56,63,63,56;,
  4;56,56,49,49;,
  4;64,61,61,64;,
  4;64,64,65,65;,
  4;66,67,67,66;,
  4;68,68,69,69;,
  4;70,71,71,70;,
  4;75,75,75,75;,
  4;76,77,77,76;,
  4;78,79,79,78;,
  4;72,77,77,72;,
  4;72,72,68,68;,
  4;73,80,80,73;,
  4;73,73,67,67;,
  4;74,70,70,74;,
  4;74,74,81,81;,
  4;82,83,83,82;,
  4;82,82,79,79;;
 }
 MeshTextureCoords {
  184;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.564770;1.000000;,
  0.564770;0.000000;,
  1.000000;1.000000;,
  0.564770;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.564770;1.000000;,
  0.435230;0.000000;,
  0.435230;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.564770;0.000000;,
  1.000000;0.000000;,
  0.564770;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.551540;0.000000;,
  1.000000;1.000000;,
  0.551540;1.000000;,
  0.448460;0.000000;,
  0.448460;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.551540;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.551540;1.000000;,
  0.551540;1.000000;,
  0.551540;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.564980;0.000000;,
  1.000000;1.000000;,
  0.564980;1.000000;,
  0.435020;0.000000;,
  0.435020;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.564980;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.564980;1.000000;,
  0.564980;1.000000;,
  0.564980;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.578940;1.000000;,
  0.578940;0.000000;,
  1.000000;1.000000;,
  0.578940;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.578940;1.000000;,
  0.421060;0.000000;,
  0.421060;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.578940;0.000000;,
  1.000000;0.000000;,
  0.578940;1.000000;;
 }
}
