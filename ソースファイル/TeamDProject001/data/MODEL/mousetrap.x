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
 96;
 -195.09760;12.46380;-88.71850;,
 195.09760;12.46380;-88.71850;,
 195.09760;-0.47400;-88.71850;,
 -195.09760;-0.47400;-88.71850;,
 195.09760;12.46380;-88.71850;,
 195.09760;12.46380;88.71850;,
 195.09760;-0.47400;88.71850;,
 195.09760;-0.47400;-88.71850;,
 195.09760;12.46380;88.71850;,
 -195.09760;12.46380;88.71850;,
 -195.09760;-0.47400;88.71850;,
 195.09760;-0.47400;88.71850;,
 -195.09760;12.46380;88.71850;,
 -195.09760;12.46380;-88.71850;,
 -195.09760;-0.47400;-88.71850;,
 -195.09760;-0.47400;88.71850;,
 195.09760;12.46380;-88.71850;,
 -195.09760;12.46380;-88.71850;,
 -195.09760;-0.47400;-88.71850;,
 195.09760;-0.47400;-88.71850;,
 0.00000;46.21890;77.92850;,
 13.63590;40.57070;77.92850;,
 13.63590;40.57070;-77.92850;,
 0.00000;46.21890;-77.92850;,
 19.28410;26.93480;77.92850;,
 19.28410;26.93480;-77.92850;,
 13.63590;13.29890;77.92850;,
 13.63590;13.29890;-77.92850;,
 0.00000;7.65070;77.92850;,
 0.00000;7.65070;-77.92850;,
 -13.63590;13.29890;77.92850;,
 -13.63590;13.29890;-77.92850;,
 -19.28410;26.93480;77.92850;,
 -19.28410;26.93480;-77.92850;,
 -13.63590;40.57070;77.92850;,
 -13.63590;40.57070;-77.92850;,
 0.00000;26.93480;77.92850;,
 0.00000;26.93480;-77.92850;,
 0.00000;46.21890;77.92850;,
 13.63590;40.57070;77.92850;,
 13.63590;40.57070;-77.92850;,
 0.00000;46.21890;-77.92850;,
 19.28410;26.93480;77.92850;,
 19.28410;26.93480;-77.92850;,
 13.63590;13.29890;77.92850;,
 13.63590;13.29890;-77.92850;,
 0.00000;7.65070;77.92850;,
 0.00000;7.65070;-77.92850;,
 -13.63590;13.29890;77.92850;,
 -13.63590;13.29890;-77.92850;,
 -19.28410;26.93480;77.92850;,
 -19.28410;26.93480;-77.92850;,
 -13.63590;40.57070;77.92850;,
 -13.63590;40.57070;-77.92850;,
 0.00000;26.93480;77.92850;,
 0.00000;26.93480;-77.92850;,
 -89.24650;19.09550;-42.19600;,
 -5.06010;13.20860;-42.19600;,
 -5.09500;12.70910;-42.19600;,
 -89.28140;18.59600;-42.19600;,
 -5.06010;13.20860;-42.19600;,
 -5.06010;13.20860;42.19600;,
 -5.09500;12.70910;42.19600;,
 -5.09500;12.70910;-42.19600;,
 -5.06010;13.20860;42.19600;,
 -89.24650;19.09550;42.19600;,
 -89.28140;18.59600;42.19600;,
 -5.09500;12.70910;42.19600;,
 -89.24650;19.09550;42.19600;,
 -89.24650;19.09550;-42.19600;,
 -89.28140;18.59600;-42.19600;,
 -89.28140;18.59600;42.19600;,
 -5.06010;13.20860;-42.19600;,
 -89.24650;19.09550;-42.19600;,
 -89.28140;18.59600;-42.19600;,
 -5.09500;12.70910;-42.19600;,
 -204.05460;12.52865;-96.56879;,
 -204.05460;-0.53885;-96.56879;,
 204.05460;-0.53885;-96.56879;,
 204.05460;12.52865;-96.56879;,
 204.05460;12.52865;-96.56879;,
 204.05460;-0.53885;-96.56879;,
 204.05460;-0.53885;96.56879;,
 204.05460;12.52865;96.56879;,
 204.05460;12.52865;96.56879;,
 204.05460;-0.53885;96.56879;,
 -204.05460;-0.53885;96.56879;,
 -204.05460;12.52865;96.56879;,
 -204.05460;12.52865;96.56879;,
 -204.05460;-0.53885;96.56879;,
 -204.05460;-0.53885;-96.56879;,
 -204.05460;12.52865;-96.56879;,
 -204.05460;12.52865;-96.56879;,
 204.05460;12.52865;-96.56879;,
 -204.05460;-0.53885;-96.56879;,
 204.05460;-0.53885;-96.56879;;
 
 66;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;21,24,25,22;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,20,23,35;,
 3;36,21,20;,
 3;36,24,21;,
 3;36,26,24;,
 3;36,28,26;,
 3;36,30,28;,
 3;36,32,30;,
 3;36,34,32;,
 3;36,20,34;,
 3;37,23,22;,
 3;37,22,25;,
 3;37,25,27;,
 3;37,27,29;,
 3;37,29,31;,
 3;37,31,33;,
 3;37,33,35;,
 3;37,35,23;,
 4;38,39,40,41;,
 4;39,42,43,40;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 4;50,52,53,51;,
 4;52,38,41,53;,
 3;54,39,38;,
 3;54,42,39;,
 3;54,44,42;,
 3;54,46,44;,
 3;54,48,46;,
 3;54,50,48;,
 3;54,52,50;,
 3;54,38,52;,
 3;55,41,40;,
 3;55,40,43;,
 3;55,43,45;,
 3;55,45,47;,
 3;55,47,49;,
 3;55,49,51;,
 3;55,51,53;,
 3;55,53,41;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;68,61,72,73;,
 4;74,75,62,71;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;88,92,93,83;,
 4;94,89,82,95;;
 
 MeshMaterialList {
  4;
  66;
  1,
  1,
  1,
  1,
  1,
  1,
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
  2,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "coil000.png";
   }
  }
  Material {
   0.545600;0.382400;0.181600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.170500;0.119500;0.056750;;
  }
  Material {
   0.396800;0.396800;0.396800;1.000000;;
   9.000000;
   0.690000;0.690000;0.690000;;
   0.080600;0.080600;0.080600;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;1.000000;1.000000;;
  }
 }
 MeshNormals {
  28;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.707107;0.707107;0.000000;,
  1.000000;-0.000000;-0.000000;,
  0.707107;-0.707107;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.707107;-0.707107;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -0.707107;0.707107;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.997568;-0.069699;-0.000000;,
  0.000000;0.000000;1.000000;,
  -0.997567;0.069709;0.000000;,
  0.069757;0.997564;0.000000;,
  -0.069757;-0.997564;0.000000;,
  0.000000;-0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;;
  66;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,7,7,14;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,7,7,14;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  3;15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;;
 }
 MeshTextureCoords {
  96;
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
  0.500051;0.823984;,
  0.448448;0.823995;,
  0.448343;0.176027;,
  0.499948;0.176016;,
  0.401167;0.823999;,
  0.401050;0.176031;,
  0.373096;0.823995;,
  0.372922;0.176027;,
  0.500311;0.823984;,
  0.499689;0.176016;,
  0.627078;0.823973;,
  0.626904;0.176005;,
  0.598950;0.823969;,
  0.598833;0.176001;,
  0.551657;0.823973;,
  0.551552;0.176005;,
  0.500088;0.823984;,
  0.499912;0.176016;,
  0.500080;0.995040;,
  0.448480;0.995050;,
  0.448310;0.004970;,
  0.499920;0.004960;,
  0.401200;0.995050;,
  0.401020;0.004980;,
  0.373140;0.995050;,
  0.372870;0.004970;,
  0.500480;0.995040;,
  0.499520;0.004960;,
  0.627130;0.995030;,
  0.626860;0.004950;,
  0.598980;0.995020;,
  0.598800;0.004950;,
  0.551690;0.995030;,
  0.551520;0.004950;,
  0.500140;0.995040;,
  0.499860;0.004960;,
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
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
