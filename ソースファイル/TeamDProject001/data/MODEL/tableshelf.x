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
 189;
 103.66165;196.30341;-71.11456;,
 104.18185;193.05560;-73.97513;,
 -105.00000;193.05560;-73.97501;,
 -104.47971;196.30341;-71.11432;,
 -104.47961;196.30341;73.35138;,
 -105.00000;193.05560;77.00000;,
 104.18195;193.05560;76.99976;,
 103.66165;196.30341;73.35114;,
 104.18185;193.05560;-73.97513;,
 104.18185;143.68631;-73.97513;,
 -105.00000;143.68631;-73.97501;,
 -105.00000;193.05560;-73.97501;,
 -105.00000;193.05560;77.00000;,
 -105.00000;143.68631;77.00000;,
 104.18195;143.68631;76.99976;,
 104.18195;193.05560;76.99976;,
 104.18185;143.68631;-68.21466;,
 -105.00000;143.68631;-68.21442;,
 -105.00000;0.00000;77.00000;,
 -105.00000;0.00000;-68.21442;,
 104.18185;0.00000;-68.21466;,
 104.18195;0.00000;76.99976;,
 -105.00000;193.05560;-68.21442;,
 104.18185;193.05560;-68.21466;,
 -105.00000;193.05560;-68.21442;,
 -105.00000;143.68631;-68.21442;,
 -105.00000;143.68631;77.00000;,
 -105.00000;193.05560;77.00000;,
 -105.00000;143.68631;-73.97501;,
 -105.00000;193.05560;-73.97501;,
 104.18185;193.05560;-68.21466;,
 104.18185;143.68631;-68.21466;,
 104.18185;143.68631;-73.97513;,
 104.18185;193.05560;-73.97513;,
 104.18195;143.68631;76.99976;,
 104.18195;193.05560;76.99976;,
 104.18195;12.20290;76.99976;,
 -105.00000;12.20290;77.00000;,
 -105.00000;0.00000;77.00000;,
 -105.00000;143.68631;77.00000;,
 104.18195;143.68631;76.99976;,
 -105.00000;12.20290;-68.21442;,
 -105.00000;12.20290;77.00000;,
 -105.00000;143.68631;77.00000;,
 -105.00000;143.68631;-68.21442;,
 -105.00000;0.00000;77.00000;,
 -105.00000;0.00000;-68.21442;,
 104.18195;12.20290;76.99976;,
 104.18185;12.20290;-68.21466;,
 104.18185;143.68631;-68.21466;,
 104.18195;143.68631;76.99976;,
 104.18185;0.00000;-68.21466;,
 104.18195;0.00000;76.99976;,
 104.18185;0.00000;-68.21466;,
 104.18185;0.00000;-73.97513;,
 104.18185;12.20290;-73.97513;,
 104.18185;12.20290;-68.21466;,
 -105.00000;0.00000;-68.21442;,
 -105.00000;0.00000;-73.97501;,
 -105.00000;12.20290;-68.21442;,
 -105.00000;12.20290;-73.97501;,
 -0.67810;31.87050;-67.20273;,
 -0.67810;12.11730;-67.20273;,
 -0.67810;12.11730;-80.38992;,
 -0.67810;31.87050;-80.38992;,
 -105.92462;31.87050;-80.38992;,
 -105.92462;12.11730;-80.38992;,
 -105.92462;12.11730;-67.20270;,
 -105.92462;31.87050;-67.20270;,
 -0.67810;40.56810;-80.38992;,
 -0.67810;143.58630;-80.38992;,
 -0.67810;143.58630;-67.20273;,
 -0.67810;40.56810;-67.20273;,
 -105.92462;40.56810;-67.20270;,
 -105.92462;143.58630;-67.20270;,
 -105.92462;143.58630;-80.38992;,
 -105.92462;40.56810;-80.38992;,
 -43.45801;143.58630;-67.20273;,
 -43.45801;143.58630;-80.38992;,
 -105.92462;143.58630;-80.38992;,
 -43.45801;12.11730;-80.38992;,
 -43.45801;12.11730;-67.20273;,
 -105.92462;12.11730;-80.38992;,
 -43.45801;12.11730;-80.38992;,
 -105.92462;12.11730;-80.38992;,
 -105.92462;31.87050;-80.38992;,
 -43.45801;31.87050;-80.38992;,
 -43.45801;12.11730;-67.20273;,
 -43.45801;31.87050;-67.20273;,
 -105.92462;31.87050;-67.20270;,
 -105.92462;12.11730;-67.20270;,
 -43.45801;143.58630;-80.38992;,
 -43.45801;40.56810;-80.38992;,
 -105.92462;40.56810;-80.38992;,
 -105.92462;143.58630;-80.38992;,
 -43.45801;143.58630;-67.20273;,
 -105.92462;143.58630;-67.20270;,
 -105.92462;40.56810;-67.20270;,
 -43.45801;40.56810;-67.20273;,
 -19.96704;143.58630;-67.20273;,
 -0.67810;143.58630;-80.38992;,
 -19.96704;143.58630;-80.38992;,
 -19.96704;12.11730;-80.38992;,
 -0.67810;12.11730;-80.38992;,
 -19.96704;12.11730;-67.20273;,
 -19.96704;31.87050;-80.38992;,
 -0.67810;31.87050;-80.38992;,
 -0.67810;12.11730;-80.38992;,
 -19.96704;12.11730;-80.38992;,
 -19.96704;12.11730;-67.20273;,
 -0.67810;12.11730;-67.20273;,
 -0.67810;31.87050;-67.20273;,
 -19.96704;31.87050;-67.20273;,
 -19.96704;143.58630;-80.38992;,
 -0.67810;143.58630;-80.38992;,
 -0.67810;40.56810;-80.38992;,
 -19.96704;40.56810;-80.38992;,
 -19.96704;40.56810;-67.20273;,
 -0.67810;40.56810;-67.20273;,
 -0.67810;143.58630;-67.20273;,
 -19.96704;143.58630;-67.20273;,
 -19.96704;34.69010;-75.73044;,
 -19.96704;43.38760;-75.73044;,
 -43.45801;34.69010;-75.73044;,
 -43.45801;43.38760;-75.73044;,
 0.91638;31.87050;-67.20273;,
 0.91638;31.87050;-80.38992;,
 0.91638;12.11730;-80.38992;,
 0.91638;12.11730;-67.20273;,
 104.85196;31.87050;-80.38995;,
 104.85196;31.87050;-67.20288;,
 104.85196;12.11730;-67.20288;,
 104.85196;12.11730;-80.38995;,
 0.91638;40.56810;-80.38992;,
 0.91638;40.56810;-67.20273;,
 0.91638;143.58630;-67.20273;,
 0.91638;143.58630;-80.38992;,
 104.85196;40.56810;-67.20288;,
 104.85196;40.56810;-80.38995;,
 104.85196;143.58630;-80.38995;,
 104.85196;143.58630;-67.20288;,
 43.69629;143.58630;-67.20273;,
 104.85196;143.58630;-80.38995;,
 43.69629;143.58630;-80.38992;,
 43.69629;12.11730;-80.38992;,
 104.85196;12.11730;-80.38995;,
 43.69629;12.11730;-67.20273;,
 43.69629;12.11730;-80.38992;,
 43.69629;31.87050;-80.38992;,
 104.85196;31.87050;-80.38995;,
 104.85196;12.11730;-80.38995;,
 43.69629;12.11730;-67.20273;,
 104.85196;12.11730;-67.20288;,
 104.85196;31.87050;-67.20288;,
 43.69629;31.87050;-67.20273;,
 43.69629;143.58630;-80.38992;,
 104.85196;143.58630;-80.38995;,
 104.85196;40.56810;-80.38995;,
 43.69629;40.56810;-80.38992;,
 43.69629;143.58630;-67.20273;,
 43.69629;40.56810;-67.20273;,
 104.85196;40.56810;-67.20288;,
 104.85196;143.58630;-67.20288;,
 20.20529;143.58630;-67.20273;,
 20.20529;143.58630;-80.38992;,
 0.91638;143.58630;-80.38992;,
 20.20529;12.11730;-80.38992;,
 20.20529;12.11730;-67.20273;,
 0.91638;12.11730;-80.38992;,
 20.20529;31.87050;-80.38992;,
 20.20529;12.11730;-80.38992;,
 0.91638;12.11730;-80.38992;,
 0.91638;31.87050;-80.38992;,
 20.20529;12.11730;-67.20273;,
 20.20529;31.87050;-67.20273;,
 0.91638;31.87050;-67.20273;,
 0.91638;12.11730;-67.20273;,
 20.20529;143.58630;-80.38992;,
 20.20529;40.56810;-80.38992;,
 0.91638;40.56810;-80.38992;,
 0.91638;143.58630;-80.38992;,
 20.20529;40.56810;-67.20273;,
 20.20529;143.58630;-67.20273;,
 0.91638;143.58630;-67.20273;,
 0.91638;40.56810;-67.20273;,
 20.20529;34.69010;-75.73050;,
 20.20529;43.38760;-75.73050;,
 43.69629;34.69010;-75.73050;,
 43.69629;43.38760;-75.73050;;
 
 94;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;9,16,17,10;,
 4;18,19,20,21;,
 4;7,0,3,4;,
 4;3,22,5,4;,
 4;6,23,0,7;,
 4;24,25,26,27;,
 4;28,25,24,29;,
 4;30,31,32,33;,
 4;34,31,30,35;,
 3;22,3,2;,
 3;1,0,23;,
 4;36,37,38,21;,
 4;39,37,36,40;,
 4;41,42,43,44;,
 4;45,42,41,46;,
 4;47,48,49,50;,
 4;51,48,47,52;,
 4;53,54,55,56;,
 4;57,58,54,53;,
 4;59,60,58,57;,
 4;56,55,60,59;,
 4;60,55,54,58;,
 4;61,62,63,64;,
 4;65,66,67,68;,
 4;69,70,71,72;,
 4;69,72,61,64;,
 4;73,74,75,76;,
 4;73,76,65,68;,
 4;77,78,79,74;,
 4;80,81,67,82;,
 4;83,84,85,86;,
 4;87,88,89,90;,
 4;91,92,93,94;,
 4;92,86,85,93;,
 4;95,96,97,98;,
 4;98,97,89,88;,
 4;99,71,100,101;,
 4;99,101,78,77;,
 4;102,103,62,104;,
 4;102,104,81,80;,
 4;105,106,107,108;,
 4;105,108,83,86;,
 4;109,110,111,112;,
 4;109,112,88,87;,
 4;113,114,115,116;,
 4;113,116,92,91;,
 4;116,115,106,105;,
 4;117,118,119,120;,
 4;117,120,95,98;,
 4;112,111,118,117;,
 4;112,117,98,88;,
 4;121,122,116,105;,
 4;123,121,105,86;,
 4;124,123,86,92;,
 4;122,124,92,116;,
 4;122,121,123,124;,
 4;125,126,127,128;,
 4;129,130,131,132;,
 4;133,134,135,136;,
 4;133,126,125,134;,
 4;137,138,139,140;,
 4;137,130,129,138;,
 4;141,140,142,143;,
 4;144,145,131,146;,
 4;147,148,149,150;,
 4;151,152,153,154;,
 4;155,156,157,158;,
 4;158,157,149,148;,
 4;159,160,161,162;,
 4;160,154,153,161;,
 4;163,164,165,135;,
 4;163,141,143,164;,
 4;166,167,128,168;,
 4;166,144,146,167;,
 4;169,170,171,172;,
 4;169,148,147,170;,
 4;173,174,175,176;,
 4;173,151,154,174;,
 4;177,178,179,180;,
 4;177,155,158,178;,
 4;178,169,172,179;,
 4;181,182,183,184;,
 4;181,160,159,182;,
 4;174,181,184,175;,
 4;174,154,160,181;,
 4;185,169,178,186;,
 4;187,148,169,185;,
 4;188,158,148,187;,
 4;186,178,158,188;,
 4;186,188,187,185;;
 
 MeshMaterialList {
  3;
  94;
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
  1,
  1,
  1,
  1,
  1,
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
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.524000;0.279200;0.150400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.207200;0.109600;0.060000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.476800;0.254400;0.138400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  53;
  0.000000;-1.000000;-0.000000;,
  0.000001;0.409336;0.912384;,
  -0.000001;0.353256;-0.935527;,
  0.000000;0.934597;0.355708;,
  -0.000000;0.911307;-0.411727;,
  -0.000001;0.000000;-1.000000;,
  0.000001;0.000000;1.000000;,
  -0.996847;0.079345;0.000000;,
  0.996848;0.079331;-0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  -0.987409;0.158189;0.000000;,
  -0.996847;0.079348;0.000000;,
  -0.987408;0.158196;0.000000;,
  0.996848;0.079334;-0.000000;,
  0.987413;0.158161;-0.000000;,
  0.987412;0.158168;-0.000000;,
  -0.996848;0.079341;0.000000;,
  0.996849;0.079327;0.000000;,
  1.000000;0.000000;-0.000001;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000001;,
  0.000000;1.000000;0.000000;,
  -0.000001;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.236323;-0.971675;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.491060;-0.871126;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.855558;0.517707;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;0.236321;-0.971675;,
  0.000001;0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000001;0.000000;1.000000;,
  0.000000;0.236321;-0.971675;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.491058;-0.871127;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000002;0.000000;1.000000;,
  0.000002;0.000000;1.000000;,
  0.000000;-0.855555;0.517712;;
  94;
  4;4,2,2,4;,
  4;3,1,1,3;,
  4;2,5,5,2;,
  4;1,6,6,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;3,4,4,3;,
  4;12,7,13,14;,
  4;15,8,16,17;,
  4;7,9,9,13;,
  4;9,9,7,18;,
  4;8,10,11,19;,
  4;20,10,8,15;,
  3;7,12,18;,
  3;19,16,8;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;20,10,10,20;,
  4;21,10,20,22;,
  4;21,11,11,10;,
  4;0,0,0,0;,
  4;9,9,9,9;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;26,26,26,26;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;25,25,25,25;,
  4;25,25,25,25;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;31,31,31,29;,
  4;30,30,34,34;,
  4;31,31,31,31;,
  4;31,29,31,31;,
  4;30,34,34,30;,
  4;30,34,34,30;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;29,31,31,31;,
  4;29,31,31,29;,
  4;32,32,32,32;,
  4;32,32,30,30;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,29;,
  4;32,32,32,32;,
  4;32,32,30,30;,
  4;32,32,32,32;,
  4;32,32,30,30;,
  4;25,25,25,25;,
  4;33,33,29,29;,
  4;26,26,26,26;,
  4;35,35,35,35;,
  4;31,33,33,31;,
  4;37,37,37,37;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;37,37,37,37;,
  4;36,36,36,36;,
  4;36,36,36,36;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;48,40,49,49;,
  4;41,50,50,41;,
  4;48,49,49,42;,
  4;42,49,49,40;,
  4;43,43,51,51;,
  4;43,41,50,51;,
  4;38,38,38,38;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;39,39,39,39;,
  4;44,46,46,46;,
  4;44,40,48,46;,
  4;45,45,45,45;,
  4;45,41,41,45;,
  4;46,46,46,46;,
  4;46,48,42,46;,
  4;46,44,46,46;,
  4;45,45,45,45;,
  4;45,43,43,45;,
  4;45,45,45,45;,
  4;45,41,43,45;,
  4;36,36,36,36;,
  4;47,40,44,47;,
  4;37,37,37,37;,
  4;52,52,52,52;,
  4;46,46,47,47;;
 }
 MeshTextureCoords {
  189;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.221050;,
  1.000000;0.420240;,
  0.000000;0.420240;,
  0.000000;0.221050;,
  1.000000;0.221050;,
  1.000000;0.420240;,
  0.000000;0.420240;,
  0.000000;0.221050;,
  1.000000;0.446980;,
  0.000000;0.446980;,
  0.000000;0.000000;,
  0.862420;0.000000;,
  0.862420;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.862420;0.221050;,
  0.862420;0.420240;,
  0.000000;0.420240;,
  0.000000;0.221050;,
  1.000000;0.420240;,
  1.000000;0.221050;,
  0.137580;0.221050;,
  0.137580;0.420240;,
  0.000000;0.420240;,
  0.000000;0.221050;,
  1.000000;0.420240;,
  1.000000;0.221050;,
  0.000000;0.930720;,
  1.000000;0.930720;,
  1.000000;1.000000;,
  1.000000;0.446980;,
  0.000000;0.446980;,
  0.862420;0.930720;,
  0.000000;0.930720;,
  0.000000;0.446980;,
  0.862420;0.446980;,
  0.000000;1.000000;,
  0.862420;1.000000;,
  1.000000;0.930720;,
  0.137580;0.930720;,
  0.137580;0.446980;,
  1.000000;0.446980;,
  0.137580;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.930720;,
  1.000000;0.930720;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.930720;,
  0.000000;0.930720;,
  1.000000;0.849750;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.849750;,
  1.000000;0.849750;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.849750;,
  0.000000;0.783590;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.783590;,
  0.000000;0.783590;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.783590;,
  0.590980;0.000000;,
  0.590980;1.000000;,
  0.000000;1.000000;,
  0.590980;0.000000;,
  0.590980;1.000000;,
  0.000000;0.000000;,
  0.590980;1.000000;,
  0.000000;1.000000;,
  0.000000;0.849750;,
  0.590980;0.849750;,
  0.409020;1.000000;,
  0.409020;0.849750;,
  1.000000;0.849750;,
  1.000000;1.000000;,
  0.590980;0.000000;,
  0.590980;0.783590;,
  0.000000;0.783590;,
  0.000000;0.000000;,
  0.409020;0.000000;,
  1.000000;0.000000;,
  1.000000;0.783590;,
  0.409020;0.783590;,
  0.815580;0.000000;,
  1.000000;1.000000;,
  0.815580;1.000000;,
  0.815580;0.000000;,
  1.000000;0.000000;,
  0.815580;1.000000;,
  0.815580;0.849750;,
  1.000000;0.849750;,
  1.000000;1.000000;,
  0.815580;1.000000;,
  0.184420;1.000000;,
  0.000000;1.000000;,
  0.000000;0.849750;,
  0.184420;0.849750;,
  0.815580;0.000000;,
  1.000000;0.000000;,
  1.000000;0.783590;,
  0.815580;0.783590;,
  0.184420;0.783590;,
  0.000000;0.783590;,
  0.000000;0.000000;,
  0.184420;0.000000;,
  0.815580;0.849750;,
  0.815580;0.783590;,
  0.590980;0.849750;,
  0.590980;0.783590;,
  1.000000;0.849750;,
  0.000000;0.849750;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.849750;,
  0.000000;0.849750;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.783590;,
  1.000000;0.783590;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.783590;,
  1.000000;0.783590;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.590980;0.000000;,
  0.000000;1.000000;,
  0.590980;1.000000;,
  0.590980;0.000000;,
  0.000000;0.000000;,
  0.590980;1.000000;,
  0.590980;1.000000;,
  0.590980;0.849750;,
  0.000000;0.849750;,
  0.000000;1.000000;,
  0.409020;1.000000;,
  1.000000;1.000000;,
  1.000000;0.849750;,
  0.409020;0.849750;,
  0.590980;0.000000;,
  0.000000;0.000000;,
  0.000000;0.783590;,
  0.590980;0.783590;,
  0.409020;0.000000;,
  0.409020;0.783590;,
  1.000000;0.783590;,
  1.000000;0.000000;,
  0.815580;0.000000;,
  0.815580;1.000000;,
  1.000000;1.000000;,
  0.815580;0.000000;,
  0.815580;1.000000;,
  1.000000;0.000000;,
  0.815580;0.849750;,
  0.815580;1.000000;,
  1.000000;1.000000;,
  1.000000;0.849750;,
  0.184420;1.000000;,
  0.184420;0.849750;,
  0.000000;0.849750;,
  0.000000;1.000000;,
  0.815580;0.000000;,
  0.815580;0.783590;,
  1.000000;0.783590;,
  1.000000;0.000000;,
  0.184420;0.783590;,
  0.184420;0.000000;,
  0.000000;0.000000;,
  0.000000;0.783590;,
  0.815580;0.849750;,
  0.815580;0.783590;,
  0.590980;0.849750;,
  0.590980;0.783590;;
 }
}
