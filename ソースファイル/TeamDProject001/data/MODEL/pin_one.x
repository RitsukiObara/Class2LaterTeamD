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
 95;
 -0.04281;1.66894;-0.01924;,
 -1.26423;2.05804;-1.73163;,
 -2.11731;2.05804;-0.36639;,
 -0.04281;1.66894;-0.01924;,
 0.30434;2.05804;-2.09376;,
 -0.04281;1.66894;-0.01924;,
 1.66956;2.05804;-1.24066;,
 -0.04281;1.66894;-0.01924;,
 2.03170;2.05804;0.32790;,
 -0.04281;1.66894;-0.01924;,
 1.17862;2.05804;1.69312;,
 -0.04281;1.66894;-0.01924;,
 -0.38997;2.05804;2.05526;,
 -0.04281;1.66894;-0.01924;,
 -1.75518;2.05804;1.20219;,
 -0.04281;1.66894;-0.01924;,
 -2.11731;2.05804;-0.36639;,
 -2.29971;1.12892;-3.18330;,
 -3.87600;1.12892;-0.66070;,
 0.59865;1.12892;-3.85244;,
 3.12125;1.12892;-2.27615;,
 3.79038;1.12892;0.62221;,
 2.21409;1.12892;3.14481;,
 -0.68426;1.12892;3.81394;,
 -3.20686;1.12892;2.23764;,
 -3.87600;1.12892;-0.66070;,
 -2.99159;1.31872;-4.15329;,
 -5.05111;1.31872;-0.85735;,
 0.79529;1.31872;-5.02755;,
 4.09122;1.31872;-2.96803;,
 4.96549;1.31872;0.81885;,
 2.90597;1.31872;4.11479;,
 -0.88092;1.31872;4.98905;,
 -4.17684;1.31872;2.92952;,
 -5.05111;1.31872;-0.85735;,
 -2.99159;-0.00344;-4.15329;,
 -5.05111;-0.00344;-0.85735;,
 0.79529;-0.00344;-5.02755;,
 4.09122;-0.00344;-2.96803;,
 4.96549;-0.00362;0.81885;,
 2.90597;-0.00344;4.11479;,
 -0.88092;-0.00344;4.98905;,
 -4.17684;-0.00344;2.92952;,
 -5.05111;-0.00344;-0.85735;,
 -5.05111;-0.00344;-0.85735;,
 -2.99159;-0.00344;-4.15329;,
 -0.04281;-0.00362;-0.01924;,
 0.79529;-0.00344;-5.02755;,
 -0.04281;-0.00362;-0.01924;,
 4.09122;-0.00344;-2.96803;,
 -0.04281;-0.00362;-0.01924;,
 4.96549;-0.00362;0.81885;,
 -0.04281;-0.00362;-0.01924;,
 2.90597;-0.00344;4.11479;,
 -0.04281;-0.00362;-0.01924;,
 -0.88092;-0.00344;4.98905;,
 -0.04281;-0.00362;-0.01924;,
 -4.17684;-0.00344;2.92952;,
 -0.04281;-0.00362;-0.01924;,
 -5.05111;-0.00344;-0.85735;,
 -0.04281;-0.00362;-0.01924;,
 -0.60220;6.40199;-0.11285;,
 -0.37216;6.40199;-0.48098;,
 -0.37216;1.41376;-0.48098;,
 -0.60220;1.41376;-0.11285;,
 0.05080;6.40199;-0.57863;,
 0.05080;1.41376;-0.57863;,
 0.41893;6.40199;-0.34860;,
 0.41893;1.41376;-0.34860;,
 0.51658;6.40199;0.07437;,
 0.51658;1.41376;0.07437;,
 0.28654;6.40199;0.44250;,
 0.28654;1.41376;0.44250;,
 -0.13642;6.40199;0.54015;,
 -0.13642;1.41376;0.54015;,
 -0.50455;6.40199;0.31011;,
 -0.50455;1.41376;0.31011;,
 -0.60220;6.40199;-0.11285;,
 -0.60220;1.41376;-0.11285;,
 -0.04281;1.41376;-0.01924;,
 -0.04281;1.41376;-0.01924;,
 -0.04281;1.41376;-0.01924;,
 -0.04281;1.41376;-0.01924;,
 -0.04281;1.41376;-0.01924;,
 -0.04281;1.41376;-0.01924;,
 -0.04281;1.41376;-0.01924;,
 -0.04281;1.41376;-0.01924;,
 -0.04281;9.04743;-0.01924;,
 -0.04281;9.04743;-0.01924;,
 -0.04281;9.04743;-0.01924;,
 -0.04281;9.04743;-0.01924;,
 -0.04281;9.04743;-0.01924;,
 -0.04281;9.04743;-0.01924;,
 -0.04281;9.04743;-0.01924;,
 -0.04281;9.04743;-0.01924;;
 
 64;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 3;44,45,46;,
 3;45,47,48;,
 3;47,49,50;,
 3;49,51,52;,
 3;51,53,54;,
 3;53,55,56;,
 3;55,57,58;,
 3;57,59,60;,
 4;61,62,63,64;,
 4;62,65,66,63;,
 4;65,67,68,66;,
 4;67,69,70,68;,
 4;69,71,72,70;,
 4;71,73,74,72;,
 4;73,75,76,74;,
 4;75,77,78,76;,
 3;79,64,63;,
 3;80,63,66;,
 3;81,66,68;,
 3;82,68,70;,
 3;83,70,72;,
 3;84,72,74;,
 3;85,74,76;,
 3;86,76,78;,
 3;87,67,65;,
 3;88,65,62;,
 3;89,62,61;,
 3;90,69,67;,
 3;91,71,69;,
 3;92,73,71;,
 3;93,75,73;,
 3;94,77,75;;
 
 MeshMaterialList {
  3;
  64;
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
   0.731200;0.800000;0.000000;1.000000;;
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
  63;
  -0.000000;1.000000;0.000000;,
  -0.143591;0.989345;-0.024029;,
  -0.084543;0.989345;-0.118526;,
  0.024029;0.989345;-0.143591;,
  0.118525;0.989345;-0.084543;,
  0.143591;0.989345;0.024029;,
  0.084543;0.989345;0.118525;,
  -0.024029;0.989345;0.143592;,
  -0.118526;0.989345;0.084544;,
  -0.155738;0.987455;-0.026061;,
  -0.091695;0.987455;-0.128552;,
  0.026061;0.987455;-0.155738;,
  0.128551;0.987455;-0.091694;,
  0.155737;0.987455;0.026061;,
  0.091695;0.987455;0.128551;,
  -0.026062;0.987454;0.155738;,
  -0.128552;0.987454;0.091696;,
  0.155160;0.987548;0.025964;,
  0.091354;0.987548;0.128074;,
  -0.025965;0.987548;0.155160;,
  -0.128075;0.987548;0.091355;,
  -0.155160;0.987548;-0.025965;,
  -0.091355;0.987548;-0.128075;,
  0.025965;0.987548;-0.155160;,
  0.128075;0.987548;-0.091355;,
  -0.986286;0.000000;-0.165047;,
  -0.580702;0.000000;-0.814116;,
  0.165048;0.000000;-0.986286;,
  0.814115;0.000000;-0.580703;,
  0.986286;0.000000;0.165048;,
  0.580703;0.000000;0.814116;,
  -0.165049;0.000000;0.986285;,
  -0.814116;0.000000;0.580702;,
  -0.000009;-1.000000;-0.000001;,
  0.161384;0.209628;-0.964371;,
  -0.980774;0.105573;-0.164123;,
  -0.577451;0.105572;-0.809571;,
  0.164129;0.105571;-0.980773;,
  0.809562;0.105572;-0.577463;,
  0.980773;0.105573;0.164129;,
  0.577455;0.105572;0.809568;,
  -0.164124;0.105573;0.980774;,
  -0.809565;0.105573;0.577459;,
  -0.986286;0.000000;-0.165045;,
  -0.580696;0.000000;-0.814121;,
  0.165051;0.000000;-0.986285;,
  0.814112;0.000000;-0.580708;,
  0.986285;0.000000;0.165051;,
  0.580700;0.000000;0.814118;,
  -0.165046;0.000000;0.986286;,
  -0.814114;0.000000;0.580705;,
  0.000000;-1.000000;-0.000000;,
  -0.000035;-1.000000;-0.000006;,
  -0.000021;-1.000000;-0.000029;,
  0.000006;-1.000000;-0.000035;,
  0.000014;-1.000000;-0.000041;,
  -0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000043;,
  -0.000006;-1.000000;0.000035;,
  -0.000029;-1.000000;0.000021;,
  -0.964371;0.209631;-0.161378;,
  0.964370;0.209631;0.161384;,
  -0.161379;0.209631;0.964371;;
  64;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;25,26,26,25;,
  4;26,27,27,26;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;29,30,30,29;,
  4;30,31,31,30;,
  4;31,32,32,31;,
  4;32,25,25,32;,
  3;52,53,33;,
  3;53,54,33;,
  3;54,55,33;,
  3;55,56,33;,
  3;56,57,33;,
  3;57,58,33;,
  3;58,59,33;,
  3;59,52,33;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;42,35,43,50;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;34,38,37;,
  3;34,37,36;,
  3;60,36,35;,
  3;61,39,38;,
  3;61,40,39;,
  3;62,41,40;,
  3;62,42,41;,
  3;60,35,42;;
 }
 MeshTextureCoords {
  95;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.062500;1.000000;,
  0.250000;0.875000;,
  0.187500;1.000000;,
  0.375000;0.875000;,
  0.312500;1.000000;,
  0.500000;0.875000;,
  0.437500;1.000000;,
  0.625000;0.875000;,
  0.562500;1.000000;,
  0.750000;0.875000;,
  0.687500;1.000000;,
  0.875000;0.875000;,
  0.812500;1.000000;,
  1.000000;0.875000;,
  0.937500;1.000000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.500000;,
  0.250000;1.000000;,
  0.375000;0.500000;,
  0.375000;1.000000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.625000;0.500000;,
  0.625000;1.000000;,
  0.750000;0.500000;,
  0.750000;1.000000;,
  0.875000;0.500000;,
  0.875000;1.000000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.312500;0.000000;,
  0.187500;0.000000;,
  0.062500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;;
 }
}
