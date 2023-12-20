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
 134;
 0.00000;29.17310;0.00000;,
 7.89420;26.95240;-7.89420;,
 0.00000;26.95240;-11.16400;,
 11.16400;26.95240;0.00000;,
 7.89420;26.95240;7.89420;,
 0.00000;26.95240;11.16400;,
 -7.89420;26.95240;7.89420;,
 -11.16400;26.95240;0.00000;,
 -7.89420;26.95240;-7.89420;,
 0.00000;26.95240;-11.16400;,
 7.89420;26.95240;-7.89420;,
 14.58660;20.62850;-14.58660;,
 0.00000;20.62850;-20.62850;,
 20.62850;20.62850;0.00000;,
 14.58660;20.62850;14.58660;,
 0.00000;20.62850;20.62850;,
 -14.58660;20.62850;14.58660;,
 -20.62850;20.62850;0.00000;,
 -14.58660;20.62850;-14.58660;,
 0.00000;20.62850;-20.62850;,
 19.05820;11.16400;-19.05820;,
 0.00000;11.16400;-26.95240;,
 26.95240;11.16400;0.00000;,
 19.05820;11.16400;19.05820;,
 0.00000;11.16400;26.95240;,
 -19.05820;11.16400;19.05820;,
 -26.95240;11.16400;0.00000;,
 -19.05820;11.16400;-19.05820;,
 0.00000;11.16400;-26.95240;,
 20.62850;0.00000;-20.62850;,
 0.00000;0.00000;-29.17310;,
 29.17310;0.00000;0.00000;,
 20.62850;0.00000;20.62850;,
 0.00000;0.00000;29.17310;,
 -20.62850;0.00000;20.62850;,
 -29.17310;0.00000;0.00000;,
 -20.62850;0.00000;-20.62850;,
 0.00000;0.00000;-29.17310;,
 19.05820;-11.16410;-19.05820;,
 0.00000;-11.16410;-26.95240;,
 26.95240;-11.16410;-0.00000;,
 19.05820;-11.16410;19.05820;,
 0.00000;-11.16410;26.95240;,
 -19.05820;-11.16410;19.05820;,
 -26.95240;-11.16410;0.00000;,
 -19.05820;-11.16410;-19.05820;,
 0.00000;-11.16410;-26.95240;,
 14.58660;-20.62850;-14.58660;,
 0.00000;-20.62850;-20.62850;,
 20.62850;-20.62850;-0.00000;,
 14.58660;-20.62850;14.58660;,
 0.00000;-20.62850;20.62850;,
 -14.58660;-20.62850;14.58660;,
 -20.62850;-20.62850;0.00000;,
 -14.58660;-20.62850;-14.58660;,
 0.00000;-20.62850;-20.62850;,
 7.89420;-26.95240;-7.89420;,
 0.00000;-26.95240;-11.16400;,
 11.16400;-26.95240;-0.00000;,
 7.89420;-26.95240;7.89420;,
 0.00000;-26.95240;11.16400;,
 -7.89420;-26.95240;7.89420;,
 -11.16400;-26.95240;0.00000;,
 -7.89420;-26.95240;-7.89420;,
 0.00000;-26.95240;-11.16400;,
 0.00000;-29.17310;-0.00000;,
 0.00000;-29.17310;-0.00000;,
 0.00000;33.71308;0.00000;,
 0.00000;31.14677;-12.90136;,
 9.12271;31.14677;-9.12271;,
 12.90136;31.14677;0.00000;,
 9.12271;31.14677;9.12271;,
 0.00000;31.14677;12.90136;,
 -9.12271;31.14677;9.12271;,
 -12.90136;31.14677;0.00000;,
 -9.12271;31.14677;-9.12271;,
 0.00000;31.14677;-12.90136;,
 0.00000;23.83874;-23.83874;,
 16.85660;23.83874;-16.85660;,
 9.12271;31.14677;-9.12271;,
 23.83874;23.83874;0.00000;,
 16.85660;23.83874;16.85660;,
 0.00000;23.83874;23.83874;,
 -16.85660;23.83874;16.85660;,
 -23.83874;23.83874;0.00000;,
 -16.85660;23.83874;-16.85660;,
 0.00000;23.83874;-23.83874;,
 0.00000;12.90136;-31.14677;,
 22.02408;12.90136;-22.02408;,
 31.14677;12.90136;0.00000;,
 22.02408;12.90136;22.02408;,
 0.00000;12.90136;31.14677;,
 -22.02408;12.90136;22.02408;,
 -31.14677;12.90136;0.00000;,
 -22.02408;12.90136;-22.02408;,
 0.00000;12.90136;-31.14677;,
 0.00000;0.00000;-33.71308;,
 23.83874;0.00000;-23.83874;,
 33.71308;0.00000;0.00000;,
 23.83874;0.00000;23.83874;,
 0.00000;0.00000;33.71308;,
 -23.83874;0.00000;23.83874;,
 -33.71308;0.00000;0.00000;,
 -23.83874;0.00000;-23.83874;,
 0.00000;0.00000;-33.71308;,
 0.00000;-12.90148;-31.14677;,
 22.02408;-12.90148;-22.02408;,
 31.14677;-12.90148;-0.00000;,
 22.02408;-12.90148;22.02408;,
 0.00000;-12.90148;31.14677;,
 -22.02408;-12.90148;22.02408;,
 -31.14677;-12.90148;0.00000;,
 -22.02408;-12.90148;-22.02408;,
 0.00000;-12.90148;-31.14677;,
 0.00000;-23.83874;-23.83874;,
 16.85660;-23.83874;-16.85660;,
 23.83874;-23.83874;-0.00000;,
 16.85660;-23.83874;16.85660;,
 0.00000;-23.83874;23.83874;,
 -16.85660;-23.83874;16.85660;,
 -23.83874;-23.83874;0.00000;,
 -16.85660;-23.83874;-16.85660;,
 0.00000;-23.83874;-23.83874;,
 0.00000;-31.14677;-12.90136;,
 9.12271;-31.14677;-9.12271;,
 12.90136;-31.14677;-0.00000;,
 9.12271;-31.14677;9.12271;,
 0.00000;-31.14677;12.90136;,
 -9.12271;-31.14677;9.12271;,
 -12.90136;-31.14677;0.00000;,
 -9.12271;-31.14677;-9.12271;,
 0.00000;-31.14677;-12.90136;,
 0.00000;-33.71308;-0.00000;,
 0.00000;-33.71308;-0.00000;;
 
 128;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;9,10,11,12;,
 4;10,3,13,11;,
 4;3,4,14,13;,
 4;4,5,15,14;,
 4;5,6,16,15;,
 4;6,7,17,16;,
 4;7,8,18,17;,
 4;8,2,19,18;,
 4;12,11,20,21;,
 4;11,13,22,20;,
 4;13,14,23,22;,
 4;14,15,24,23;,
 4;15,16,25,24;,
 4;16,17,26,25;,
 4;17,18,27,26;,
 4;18,19,28,27;,
 4;21,20,29,30;,
 4;20,22,31,29;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 4;26,27,36,35;,
 4;27,28,37,36;,
 4;30,29,38,39;,
 4;29,31,40,38;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;34,35,44,43;,
 4;35,36,45,44;,
 4;36,37,46,45;,
 4;39,38,47,48;,
 4;38,40,49,47;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;43,44,53,52;,
 4;44,45,54,53;,
 4;45,46,55,54;,
 4;48,47,56,57;,
 4;47,49,58,56;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;52,53,62,61;,
 4;53,54,63,62;,
 4;54,55,64,63;,
 3;57,56,65;,
 3;56,58,65;,
 3;58,59,65;,
 3;59,60,66;,
 3;60,61,66;,
 3;61,62,66;,
 3;62,63,66;,
 3;63,64,66;,
 3;67,68,69;,
 3;67,69,70;,
 3;67,70,71;,
 3;67,71,72;,
 3;67,72,73;,
 3;67,73,74;,
 3;67,74,75;,
 3;67,75,68;,
 4;76,77,78,79;,
 4;79,78,80,70;,
 4;70,80,81,71;,
 4;71,81,82,72;,
 4;72,82,83,73;,
 4;73,83,84,74;,
 4;74,84,85,75;,
 4;75,85,86,68;,
 4;77,87,88,78;,
 4;78,88,89,80;,
 4;80,89,90,81;,
 4;81,90,91,82;,
 4;82,91,92,83;,
 4;83,92,93,84;,
 4;84,93,94,85;,
 4;85,94,95,86;,
 4;87,96,97,88;,
 4;88,97,98,89;,
 4;89,98,99,90;,
 4;90,99,100,91;,
 4;91,100,101,92;,
 4;92,101,102,93;,
 4;93,102,103,94;,
 4;94,103,104,95;,
 4;96,105,106,97;,
 4;97,106,107,98;,
 4;98,107,108,99;,
 4;99,108,109,100;,
 4;100,109,110,101;,
 4;101,110,111,102;,
 4;102,111,112,103;,
 4;103,112,113,104;,
 4;105,114,115,106;,
 4;106,115,116,107;,
 4;107,116,117,108;,
 4;108,117,118,109;,
 4;109,118,119,110;,
 4;110,119,120,111;,
 4;111,120,121,112;,
 4;112,121,122,113;,
 4;114,123,124,115;,
 4;115,124,125,116;,
 4;116,125,126,117;,
 4;117,126,127,118;,
 4;118,127,128,119;,
 4;119,128,129,120;,
 4;120,129,130,121;,
 4;121,130,131,122;,
 3;123,132,124;,
 3;124,132,125;,
 3;125,132,126;,
 3;126,133,127;,
 3;127,133,128;,
 3;128,133,129;,
 3;129,133,130;,
 3;130,133,131;;
 
 MeshMaterialList {
  2;
  128;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "HairBall.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.250980;0.000000;;
  }
 }
 MeshNormals {
  116;
  -0.000000;1.000000;0.000000;,
  0.000000;0.924735;-0.380611;,
  0.269131;0.924736;-0.269131;,
  0.380611;0.924735;0.000000;,
  0.269131;0.924736;0.269131;,
  0.000000;0.924735;0.380611;,
  -0.269131;0.924736;0.269131;,
  -0.380611;0.924735;0.000000;,
  -0.269131;0.924736;-0.269131;,
  0.000000;0.709229;-0.704978;,
  0.498494;0.709230;-0.498494;,
  0.704978;0.709229;0.000000;,
  0.498494;0.709230;0.498494;,
  0.000000;0.709229;0.704978;,
  -0.498494;0.709230;0.498494;,
  -0.704978;0.709229;0.000000;,
  -0.498494;0.709230;-0.498494;,
  0.000000;0.384549;-0.923105;,
  0.652733;0.384549;-0.652733;,
  0.923105;0.384549;0.000000;,
  0.652733;0.384549;0.652733;,
  0.000000;0.384549;0.923105;,
  -0.652733;0.384549;0.652733;,
  -0.923105;0.384549;0.000000;,
  -0.652733;0.384549;-0.652733;,
  0.000000;0.000001;-1.000000;,
  0.707107;0.000001;-0.707107;,
  1.000000;0.000001;0.000000;,
  0.707107;0.000001;0.707107;,
  0.000000;0.000001;1.000000;,
  -0.707107;0.000001;0.707107;,
  -1.000000;0.000001;0.000000;,
  -0.707107;0.000001;-0.707107;,
  0.000000;-0.384551;-0.923104;,
  0.652733;-0.384551;-0.652733;,
  0.923104;-0.384551;-0.000000;,
  0.652733;-0.384551;0.652733;,
  0.000000;-0.384551;0.923104;,
  -0.652733;-0.384551;0.652733;,
  -0.923104;-0.384551;0.000000;,
  -0.652733;-0.384551;-0.652733;,
  0.000000;-0.709231;-0.704977;,
  0.498493;-0.709232;-0.498493;,
  0.704977;-0.709231;-0.000000;,
  0.498493;-0.709232;0.498493;,
  0.000000;-0.709231;0.704977;,
  -0.498493;-0.709232;0.498493;,
  -0.704977;-0.709231;0.000000;,
  -0.498493;-0.709232;-0.498493;,
  0.000000;-0.924735;-0.380611;,
  0.269131;-0.924736;-0.269131;,
  0.380611;-0.924735;-0.000000;,
  0.269131;-0.924736;0.269131;,
  0.000000;-0.924735;0.380611;,
  -0.269131;-0.924736;0.269131;,
  -0.380611;-0.924735;0.000000;,
  -0.269131;-0.924736;-0.269131;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000000;,
  0.000000;-0.924735;0.380611;,
  -0.269131;-0.924736;0.269131;,
  -0.380611;-0.924735;0.000000;,
  -0.269131;-0.924736;-0.269131;,
  0.000000;-0.924735;-0.380611;,
  0.269131;-0.924736;-0.269131;,
  0.380611;-0.924735;-0.000000;,
  0.269131;-0.924736;0.269131;,
  0.000000;-0.709229;0.704978;,
  -0.498494;-0.709230;0.498494;,
  -0.704978;-0.709229;0.000000;,
  -0.498494;-0.709230;-0.498494;,
  0.000000;-0.709229;-0.704978;,
  0.498494;-0.709230;-0.498494;,
  0.704978;-0.709229;-0.000000;,
  0.498494;-0.709230;0.498494;,
  0.000000;-0.384549;0.923104;,
  -0.652733;-0.384549;0.652733;,
  -0.923104;-0.384549;0.000000;,
  -0.652733;-0.384549;-0.652733;,
  0.000000;-0.384549;-0.923104;,
  0.652733;-0.384549;-0.652733;,
  0.923104;-0.384549;-0.000000;,
  0.652733;-0.384549;0.652733;,
  0.000000;-0.000001;1.000000;,
  -0.707107;-0.000001;0.707107;,
  -1.000000;-0.000001;0.000000;,
  -0.707107;-0.000001;-0.707107;,
  0.000000;-0.000001;-1.000000;,
  0.707107;-0.000001;-0.707107;,
  1.000000;-0.000001;-0.000000;,
  0.707107;-0.000001;0.707107;,
  0.000000;0.384550;0.923104;,
  -0.652733;0.384550;0.652733;,
  -0.923104;0.384550;0.000000;,
  -0.652733;0.384550;-0.652733;,
  0.000000;0.384550;-0.923104;,
  0.652733;0.384550;-0.652733;,
  0.923104;0.384550;0.000000;,
  0.652733;0.384550;0.652733;,
  0.000000;0.709230;0.704977;,
  -0.498493;0.709231;0.498493;,
  -0.704977;0.709230;0.000000;,
  -0.498493;0.709231;-0.498493;,
  0.000000;0.709230;-0.704977;,
  0.498493;0.709231;-0.498493;,
  0.704977;0.709230;0.000000;,
  0.498493;0.709231;0.498493;,
  0.000000;0.924735;0.380611;,
  -0.269131;0.924736;0.269131;,
  -0.380611;0.924735;0.000000;,
  -0.269131;0.924736;-0.269131;,
  0.000000;0.924735;-0.380611;,
  0.269131;0.924736;-0.269131;,
  0.380611;0.924735;0.000000;,
  0.269131;0.924736;0.269131;,
  -0.000000;1.000000;0.000000;;
  128;
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
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;,
  3;58,59,60;,
  3;58,60,61;,
  3;58,61,62;,
  3;58,62,63;,
  3;58,63,64;,
  3;58,64,65;,
  3;58,65,66;,
  3;58,66,59;,
  4;59,67,68,60;,
  4;60,68,69,61;,
  4;61,69,70,62;,
  4;62,70,71,63;,
  4;63,71,72,64;,
  4;64,72,73,65;,
  4;65,73,74,66;,
  4;66,74,67,59;,
  4;67,75,76,68;,
  4;68,76,77,69;,
  4;69,77,78,70;,
  4;70,78,79,71;,
  4;71,79,80,72;,
  4;72,80,81,73;,
  4;73,81,82,74;,
  4;74,82,75,67;,
  4;75,83,84,76;,
  4;76,84,85,77;,
  4;77,85,86,78;,
  4;78,86,87,79;,
  4;79,87,88,80;,
  4;80,88,89,81;,
  4;81,89,90,82;,
  4;82,90,83,75;,
  4;83,91,92,84;,
  4;84,92,93,85;,
  4;85,93,94,86;,
  4;86,94,95,87;,
  4;87,95,96,88;,
  4;88,96,97,89;,
  4;89,97,98,90;,
  4;90,98,91,83;,
  4;91,99,100,92;,
  4;92,100,101,93;,
  4;93,101,102,94;,
  4;94,102,103,95;,
  4;95,103,104,96;,
  4;96,104,105,97;,
  4;97,105,106,98;,
  4;98,106,99,91;,
  4;99,107,108,100;,
  4;100,108,109,101;,
  4;101,109,110,102;,
  4;102,110,111,103;,
  4;103,111,112,104;,
  4;104,112,113,105;,
  4;105,113,114,106;,
  4;106,114,107,99;,
  3;107,115,108;,
  3;108,115,109;,
  3;109,115,110;,
  3;110,115,111;,
  3;111,115,112;,
  3;112,115,113;,
  3;113,115,114;,
  3;114,115,107;;
 }
 MeshTextureCoords {
  134;
  0.750000;0.000000;,
  1.125000;0.125000;,
  1.000000;0.125000;,
  0.250000;0.125000;,
  0.375000;0.125000;,
  0.500000;0.125000;,
  0.625000;0.125000;,
  0.750000;0.125000;,
  0.875000;0.125000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
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
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  -0.250000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  1.000000;0.125000;,
  1.125000;0.125000;,
  0.250000;0.125000;,
  0.375000;0.125000;,
  0.500000;0.125000;,
  0.625000;0.125000;,
  0.750000;0.125000;,
  0.875000;0.125000;,
  0.000000;0.125000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.125000;0.125000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  -0.250000;1.000000;,
  0.750000;1.000000;;
 }
}
