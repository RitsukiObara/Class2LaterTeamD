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
 -52.10000;31.44430;-98.78670;,
 59.36690;31.44430;-98.78670;,
 52.10000;22.31090;-88.32570;,
 -63.15130;22.31090;-88.32570;,
 52.10000;13.17760;-88.32570;,
 -63.15130;13.17760;-88.32570;,
 59.91830;4.04430;-98.78670;,
 -52.10000;4.04430;-98.78670;,
 59.36690;31.44430;45.51330;,
 52.10000;22.31090;36.40980;,
 52.10000;13.17760;36.40980;,
 59.91830;4.04430;45.51330;,
 -52.10000;31.44430;45.51330;,
 -63.15130;22.31090;36.40980;,
 -63.15130;13.17760;36.40980;,
 -52.10000;4.04430;45.51330;,
 -56.29373;32.58237;-104.78028;,
 -68.26306;22.69025;-93.45027;,
 56.56229;22.69025;-93.45027;,
 64.43285;32.58237;-104.78028;,
 -68.26306;12.79824;-93.45027;,
 56.56229;12.79824;-93.45027;,
 -56.29373;2.90623;-104.78028;,
 65.03008;2.90623;-104.78028;,
 56.56229;22.69025;41.64714;,
 64.43285;32.58237;51.50689;,
 56.56229;12.79824;41.64714;,
 65.03008;2.90623;51.50689;,
 -68.26306;22.69025;41.64714;,
 -56.29373;32.58237;51.50689;,
 -68.26306;12.79824;41.64714;,
 -56.29373;2.90623;51.50689;;
 
 28;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;1,8,9,2;,
 4;2,9,10,4;,
 4;4,10,11,6;,
 4;8,12,13,9;,
 4;9,13,14,10;,
 4;10,14,15,11;,
 4;12,0,3,13;,
 4;13,3,5,14;,
 4;14,5,7,15;,
 4;12,8,1,0;,
 4;7,6,11,15;,
 4;16,17,18,19;,
 4;17,20,21,18;,
 4;20,22,23,21;,
 4;19,18,24,25;,
 4;18,21,26,24;,
 4;21,23,27,26;,
 4;25,24,28,29;,
 4;24,26,30,28;,
 4;26,27,31,30;,
 4;29,28,17,16;,
 4;28,30,20,17;,
 4;30,31,22,20;,
 4;29,16,19,25;,
 4;22,31,27,23;;
 
 MeshMaterialList {
  6;
  28;
  4,
  1,
  4,
  4,
  1,
  4,
  4,
  1,
  4,
  4,
  4,
  4,
  4,
  4,
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
  5;;
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
   0.480000;0.721600;0.800000;1.000000;;
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
  Material {
   0.800000;0.800000;0.000000;1.000000;;
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
  36;
  0.000000;-0.753289;-0.657690;,
  0.000000;-0.413709;-0.910409;,
  0.000000;0.413712;-0.910408;,
  0.000000;0.753293;-0.657686;,
  0.782530;-0.622613;-0.000000;,
  0.944068;-0.329750;-0.000000;,
  0.937997;0.346643;0.000000;,
  0.759677;0.650300;0.000000;,
  0.000000;-0.705947;0.708265;,
  0.000000;-0.381926;0.924193;,
  0.000000;0.381928;0.924192;,
  0.000000;0.705950;0.708261;,
  -0.338510;0.940963;0.000000;,
  -0.904724;0.425999;0.000000;,
  -0.904723;-0.426001;0.000000;,
  -0.338507;-0.940964;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.753289;0.657690;,
  0.000000;0.413709;0.910409;,
  0.000000;-0.413712;0.910408;,
  0.000000;-0.753293;0.657685;,
  -0.782531;0.622612;0.000000;,
  -0.944069;0.329749;0.000000;,
  -0.937997;-0.346643;0.000000;,
  -0.759677;-0.650301;0.000000;,
  0.000000;0.705947;-0.708265;,
  0.000000;0.381926;-0.924193;,
  0.000000;-0.381929;-0.924192;,
  0.000000;-0.705951;-0.708261;,
  0.338510;-0.940963;-0.000000;,
  0.904724;-0.425999;-0.000000;,
  0.904723;0.426001;0.000000;,
  0.338507;0.940964;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;;
  28;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;4,4,5,5;,
  4;5,5,6,6;,
  4;6,6,7,7;,
  4;8,8,9,9;,
  4;9,9,10,10;,
  4;10,10,11,11;,
  4;12,12,13,13;,
  4;13,13,14,14;,
  4;14,14,15,15;,
  4;12,16,16,12;,
  4;15,17,17,15;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,25,25,24;,
  4;26,27,27,26;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;30,31,31,30;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;30,30,34,34;,
  4;33,33,35,35;;
 }
}
