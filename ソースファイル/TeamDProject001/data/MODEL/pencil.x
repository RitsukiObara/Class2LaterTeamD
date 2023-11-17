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
 47;
 39.09327;2.72174;-3.29923;,
 39.09327;-0.13551;-1.64963;,
 -52.25883;-0.13551;-1.64963;,
 -52.25883;2.72174;-3.29923;,
 39.09327;-0.13551;1.64963;,
 -52.25883;-0.13551;1.64963;,
 39.09327;2.72174;3.29923;,
 -52.25883;2.72174;3.29923;,
 39.09327;5.57893;1.64963;,
 -52.25883;5.57893;1.64963;,
 39.09327;5.57893;-1.64963;,
 -52.25883;5.57893;-1.64963;,
 39.09327;2.72174;-3.29923;,
 -52.25883;2.72174;-3.29923;,
 -52.71816;-0.13551;-1.64963;,
 -52.71816;2.72174;-3.29923;,
 -52.71816;-0.13551;1.64963;,
 -52.71816;2.72174;3.29923;,
 -52.71816;5.57893;1.64963;,
 -52.71816;5.57893;-1.64963;,
 -52.71816;2.72174;-3.29923;,
 53.43780;2.72174;0.00000;,
 53.43780;2.72163;-0.00005;,
 53.43780;2.72174;-0.00008;,
 53.43780;2.72174;0.00000;,
 53.43780;2.72163;0.00005;,
 53.43780;2.72174;0.00000;,
 53.43780;2.72174;0.00008;,
 53.43780;2.72174;0.00000;,
 53.43780;2.72179;0.00005;,
 53.43780;2.72174;0.00000;,
 53.43780;2.72179;-0.00005;,
 53.43780;2.72174;0.00000;,
 53.43780;2.72174;-0.00008;,
 -53.43771;2.72174;0.00000;,
 -53.43771;2.72174;0.00000;,
 -53.43771;2.72174;0.00000;,
 -53.43771;2.72174;0.00000;,
 -53.43771;2.72174;0.00000;,
 -53.43771;2.72174;0.00000;,
 48.61775;2.06633;-0.37837;,
 48.61775;2.72174;-0.75677;,
 48.61775;2.06633;0.37837;,
 48.61775;2.72174;0.75677;,
 48.61775;3.37708;0.37837;,
 48.61775;3.37708;-0.37837;,
 48.61775;2.72174;-0.75677;;
 
 36;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;3,2,14,15;,
 4;2,5,16,14;,
 4;5,7,17,16;,
 4;7,9,18,17;,
 4;9,11,19,18;,
 4;11,13,20,19;,
 3;21,22,23;,
 3;24,25,22;,
 3;26,27,25;,
 3;28,29,27;,
 3;30,31,29;,
 3;32,33,31;,
 3;34,15,14;,
 3;35,14,16;,
 3;36,16,17;,
 3;37,17,18;,
 3;38,18,19;,
 3;39,19,20;,
 4;40,1,0,41;,
 4;40,41,23,22;,
 4;42,4,1,40;,
 4;42,40,22,25;,
 4;43,6,4,42;,
 4;43,42,25,27;,
 4;44,8,6,43;,
 4;44,43,27,29;,
 4;45,10,8,44;,
 4;45,44,29,31;,
 4;46,12,10,45;,
 4;46,45,31,33;;
 
 MeshMaterialList {
  3;
  36;
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
  0,
  0,
  0,
  0,
  0,
  0,
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
  2;;
  Material {
   0.800000;0.724800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.684000;0.659200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.228800;0.228800;0.228800;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  40;
  1.000000;0.000000;0.000000;,
  0.170586;-0.189329;-0.966982;,
  0.170585;-0.742757;-0.647466;,
  0.170585;-0.932099;0.319519;,
  0.170586;-0.189329;0.966982;,
  0.170585;0.742765;0.647457;,
  0.170585;0.932101;-0.319513;,
  0.000000;-0.499993;-0.866030;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.499993;0.866030;,
  0.000000;0.500001;0.866025;,
  0.000000;1.000000;0.000000;,
  0.000000;-0.499993;-0.866029;,
  0.000000;-0.499993;0.866029;,
  -1.000000;0.000002;0.000000;,
  0.205720;0.030777;-0.978127;,
  0.185533;-0.426361;-0.885321;,
  0.214534;-0.827577;0.518740;,
  0.205720;0.030777;0.978127;,
  0.208282;0.843731;0.494708;,
  0.208282;0.843731;-0.494708;,
  0.000000;-0.499993;0.866029;,
  0.000000;0.500001;0.866025;,
  0.000000;0.500001;-0.866025;,
  0.000000;0.500001;-0.866025;,
  -0.977033;0.000001;-0.213088;,
  -0.977033;-0.184537;-0.106544;,
  -0.977033;-0.184537;0.106544;,
  -0.977033;0.000001;0.213088;,
  -0.977033;0.184541;0.106544;,
  -0.977033;0.184541;-0.106544;,
  0.154805;0.060243;-0.986107;,
  0.144531;-0.362590;-0.920673;,
  0.180165;-0.983636;-0.000000;,
  0.134712;-0.990885;-0.000000;,
  0.144531;-0.362590;0.920673;,
  0.154805;0.060243;0.986107;,
  0.136722;0.472040;0.870910;,
  0.134712;0.990885;0.000000;,
  0.136722;0.472040;-0.870910;;
  36;
  4;1,2,7,7;,
  4;8,3,8,8;,
  4;21,4,9,9;,
  4;22,5,10,10;,
  4;11,6,11,11;,
  4;23,23,24,24;,
  4;7,7,12,12;,
  4;8,8,8,8;,
  4;9,9,13,13;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;24,24,24,24;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;14,25,26;,
  3;14,26,27;,
  3;14,27,28;,
  3;14,28,29;,
  3;14,29,30;,
  3;14,30,25;,
  4;16,2,1,15;,
  4;16,15,31,32;,
  4;17,3,2,33;,
  4;17,33,34,34;,
  4;18,4,3,17;,
  4;18,17,35,36;,
  4;19,5,4,18;,
  4;19,18,36,37;,
  4;20,6,5,19;,
  4;20,19,38,38;,
  4;15,1,6,20;,
  4;15,20,39,31;;
 }
 MeshTextureCoords {
  47;
  0.000000;0.333330;,
  0.166670;0.333330;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.333330;,
  0.333330;0.666670;,
  0.500000;0.333330;,
  0.500000;0.666670;,
  0.666670;0.333330;,
  0.666670;0.666670;,
  0.833330;0.333330;,
  0.833330;0.666670;,
  1.000000;0.333330;,
  1.000000;0.666670;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.083330;0.000000;,
  0.166670;0.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.333330;0.000000;,
  0.416670;0.000000;,
  0.500000;0.000000;,
  0.583330;0.000000;,
  0.666670;0.000000;,
  0.750000;0.000000;,
  0.833330;0.000000;,
  0.916670;0.000000;,
  1.000000;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.166670;0.202210;,
  0.000000;0.202210;,
  0.333330;0.202210;,
  0.500000;0.202210;,
  0.666670;0.202210;,
  0.833330;0.202210;,
  1.000000;0.202210;;
 }
}
