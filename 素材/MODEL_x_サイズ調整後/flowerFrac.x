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
 32;
 14.46475;4.88942;-17.63841;,
 19.23343;0.00413;-5.17334;,
 -18.77893;-0.16111;-5.17334;,
 -9.34340;6.97238;-17.63841;,
 19.35143;1.35252;-5.17334;,
 14.54816;5.84292;-17.01514;,
 -9.25998;7.92581;-17.01514;,
 -18.66099;1.18727;-5.17334;,
 17.32553;4.63916;8.81830;,
 -9.57586;6.99275;7.29173;,
 17.40894;5.59259;8.19511;,
 -9.49244;7.94617;6.66854;,
 11.47246;24.36592;12.45501;,
 -9.76632;18.64250;12.45501;,
 11.47246;24.36592;11.57358;,
 -9.76632;18.64250;11.57358;,
 14.46475;4.88942;-17.63841;,
 14.54816;5.84292;-17.01514;,
 19.35143;1.35252;-5.17334;,
 19.23343;0.00413;-5.17334;,
 -9.34340;6.97238;-17.63841;,
 -18.77893;-0.16111;-5.17334;,
 -18.66099;1.18727;-5.17334;,
 -9.25998;7.92581;-17.01514;,
 17.40894;5.59259;8.19511;,
 17.32553;4.63916;8.81830;,
 -9.57586;6.99275;7.29173;,
 -9.49244;7.94617;6.66854;,
 11.47246;24.36592;11.57358;,
 11.47246;24.36592;12.45501;,
 -9.76632;18.64250;12.45501;,
 -9.76632;18.64250;11.57358;;
 
 14;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;1,8,9,2;,
 4;10,4,7,11;,
 4;8,12,13,9;,
 4;14,10,11,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;19,18,24,25;,
 4;21,26,27,22;,
 4;25,24,28,29;,
 4;26,30,31,27;,
 4;5,16,20,6;,
 4;29,14,15,30;;
 
 MeshMaterialList {
  1;
  14;
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
   0.000000;0.511200;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  19;
  -0.039334;-0.907892;-0.417356;,
  -0.048113;-0.998801;-0.009021;,
  -0.016883;-0.669299;0.742801;,
  0.017711;-0.304494;0.952350;,
  0.039538;0.911125;0.410229;,
  0.047965;0.998807;0.009122;,
  0.015947;0.673931;-0.738622;,
  -0.019274;0.308690;-0.950967;,
  0.933216;0.026461;-0.358340;,
  0.994270;-0.008218;-0.106583;,
  -0.448389;0.438710;-0.778769;,
  -0.827543;0.219527;-0.516702;,
  0.977403;0.105688;0.183066;,
  -0.834217;0.217186;0.506865;,
  -0.963627;0.114142;0.241649;,
  0.944974;0.251286;0.209476;,
  -0.998886;-0.000054;-0.047177;,
  0.047560;0.543618;-0.837984;,
  -0.260198;0.965555;0.000000;;
  14;
  4;0,1,1,0;,
  4;5,4,4,5;,
  4;1,2,2,1;,
  4;6,5,5,6;,
  4;2,3,3,2;,
  4;7,6,6,7;,
  4;8,8,9,9;,
  4;10,11,11,10;,
  4;9,9,12,12;,
  4;13,14,14,13;,
  4;12,12,15,15;,
  4;14,16,16,14;,
  4;17,17,10,10;,
  4;18,18,18,18;;
 }
 MeshTextureCoords {
  32;
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
