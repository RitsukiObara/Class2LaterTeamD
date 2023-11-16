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
 88;
 -11.85260;85.24180;-12.88310;,
 11.85260;85.24180;-12.88310;,
 16.47310;68.02320;-17.90530;,
 -16.47310;68.02320;-17.90530;,
 28.61480;85.24180;-5.33640;,
 39.76960;68.02320;-7.41660;,
 28.61480;85.24180;5.33640;,
 39.76960;68.02320;7.41660;,
 11.85260;85.24180;12.88310;,
 16.47310;68.02320;17.90530;,
 -11.85260;85.24180;12.88310;,
 -16.47310;68.02320;17.90530;,
 -28.61480;85.24180;5.33640;,
 -39.76960;68.02320;7.41660;,
 -28.61480;85.24180;-5.33640;,
 -39.76960;68.02320;-7.41660;,
 -11.85260;85.24180;-12.88310;,
 -16.47310;68.02320;-17.90530;,
 16.47310;50.80470;-17.90530;,
 -16.47310;50.80470;-17.90530;,
 39.76960;50.80470;-7.41660;,
 39.76960;50.80470;7.41660;,
 16.47310;50.80470;17.90530;,
 -16.47310;50.80470;17.90530;,
 -39.76960;50.80470;7.41660;,
 -39.76960;50.80470;-7.41660;,
 -16.47310;50.80470;-17.90530;,
 -16.47310;50.80470;-17.90530;,
 16.47310;50.80470;-17.90530;,
 15.98750;34.60150;-17.37740;,
 -15.98750;34.60150;-17.37740;,
 39.76960;50.80470;-7.41660;,
 38.59710;34.60150;-7.19800;,
 38.59710;34.60150;7.19800;,
 38.59710;34.60150;-7.19800;,
 15.98750;34.60150;17.37740;,
 -15.98750;34.60150;17.37740;,
 -38.59710;34.60150;7.19800;,
 -38.59710;34.60150;-7.19800;,
 -39.76960;50.80470;-7.41660;,
 -38.59710;34.60150;-7.19800;,
 15.67160;18.71580;-17.03410;,
 -15.67160;18.71580;-17.03410;,
 37.83470;18.71580;-7.05580;,
 37.83470;18.71580;7.05580;,
 37.83470;18.71580;-7.05580;,
 15.67160;18.71580;17.03410;,
 -15.67170;18.71580;17.03410;,
 -37.83470;18.71580;7.05580;,
 -37.83470;18.71580;-7.05580;,
 -37.83470;18.71580;-7.05580;,
 -15.67160;18.71580;-17.03410;,
 15.67160;18.71580;-17.03410;,
 14.18380;2.33500;-15.41700;,
 -14.18380;2.33500;-15.41700;,
 34.24280;2.33500;-6.38590;,
 34.24280;2.33500;6.38590;,
 14.18380;2.33500;15.41700;,
 -14.18380;2.33500;15.41700;,
 -34.24280;2.33500;6.38590;,
 -34.24280;2.33500;-6.38590;,
 -15.67160;18.71580;-17.03410;,
 -14.18380;2.33500;-15.41700;,
 0.00000;2.33500;0.00000;,
 0.00000;2.33500;0.00000;,
 0.00000;2.33500;0.00000;,
 0.00000;2.33500;0.00000;,
 0.00000;2.33500;0.00000;,
 0.00000;2.33500;0.00000;,
 0.00000;2.33500;0.00000;,
 0.00000;2.33500;0.00000;,
 -11.85260;95.54850;-12.88310;,
 11.85260;95.54850;-12.88310;,
 0.00000;95.54850;0.00000;,
 28.61480;95.54850;-5.33640;,
 0.00000;95.54850;0.00000;,
 28.61480;95.54850;5.33640;,
 0.00000;95.54850;0.00000;,
 11.85260;95.54850;12.88310;,
 0.00000;95.54850;0.00000;,
 -11.85260;95.54850;12.88310;,
 0.00000;95.54850;0.00000;,
 -28.61480;95.54850;5.33640;,
 0.00000;95.54850;0.00000;,
 -28.61480;95.54850;-5.33640;,
 0.00000;95.54850;0.00000;,
 -11.85260;95.54850;-12.88310;,
 0.00000;95.54850;0.00000;;
 
 64;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;3,2,18,19;,
 4;2,5,20,18;,
 4;5,7,21,20;,
 4;7,9,22,21;,
 4;9,11,23,22;,
 4;11,13,24,23;,
 4;13,15,25,24;,
 4;15,17,26,25;,
 4;27,28,29,30;,
 4;28,31,32,29;,
 4;20,21,33,34;,
 4;21,22,35,33;,
 4;22,23,36,35;,
 4;23,24,37,36;,
 4;24,25,38,37;,
 4;39,27,30,40;,
 4;30,29,41,42;,
 4;29,32,43,41;,
 4;34,33,44,45;,
 4;33,35,46,44;,
 4;35,36,47,46;,
 4;36,37,48,47;,
 4;37,38,49,48;,
 4;40,30,42,50;,
 4;51,52,53,54;,
 4;52,45,55,53;,
 4;45,44,56,55;,
 4;44,46,57,56;,
 4;46,47,58,57;,
 4;47,48,59,58;,
 4;48,49,60,59;,
 4;49,61,62,60;,
 3;63,54,53;,
 3;64,53,55;,
 3;65,55,56;,
 3;66,56,57;,
 3;67,57,58;,
 3;68,58,59;,
 3;69,59,60;,
 3;70,60,62;,
 4;71,72,1,0;,
 3;73,72,71;,
 4;72,74,4,1;,
 3;75,74,72;,
 4;74,76,6,4;,
 3;77,76,74;,
 4;76,78,8,6;,
 3;79,78,76;,
 4;78,80,10,8;,
 3;81,80,78;,
 4;80,82,12,10;,
 3;83,82,80;,
 4;82,84,14,12;,
 3;85,84,82;,
 4;84,86,16,14;,
 3;87,86,84;;
 
 MeshMaterialList {
  4;
  64;
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
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  2,
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
   0.633600;0.357600;0.200800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.620800;0.081600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\HoneyBottle.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  68;
  -0.205837;0.163691;-0.964799;,
  0.205837;0.163691;-0.964799;,
  0.799412;0.271853;-0.535757;,
  0.799412;0.271853;0.535757;,
  0.205837;0.163691;0.964799;,
  -0.205837;0.163691;0.964799;,
  -0.799412;0.271853;0.535757;,
  -0.799412;0.271853;-0.535757;,
  -0.205838;0.163691;-0.964798;,
  0.205838;0.163691;-0.964798;,
  0.799413;0.271853;-0.535757;,
  0.799413;0.271853;0.535757;,
  0.205838;0.163691;0.964798;,
  -0.205838;0.163691;0.964798;,
  -0.799413;0.271853;0.535757;,
  -0.799413;0.271853;-0.535757;,
  -0.209891;-0.019062;-0.977539;,
  0.209891;-0.019062;-0.977539;,
  0.410446;-0.020991;-0.911643;,
  0.999348;-0.036110;-0.000000;,
  0.209891;-0.019062;0.977539;,
  -0.209891;-0.019062;0.977539;,
  -0.410446;-0.020991;0.911643;,
  -0.999348;-0.036110;0.000000;,
  -0.209814;-0.031706;-0.977227;,
  0.209814;-0.031706;-0.977227;,
  0.410284;-0.034916;-0.911289;,
  0.998195;-0.060060;-0.000000;,
  0.209814;-0.031706;0.977227;,
  -0.209815;-0.031706;0.977227;,
  -0.410285;-0.034915;0.911289;,
  -0.998195;-0.060060;0.000000;,
  -0.209255;-0.070123;-0.975344;,
  0.209255;-0.070123;-0.975344;,
  0.409310;-0.077166;-0.909126;,
  0.991313;-0.131525;-0.000000;,
  0.209255;-0.070123;0.975344;,
  -0.209255;-0.070123;0.975344;,
  -0.409311;-0.077166;0.909126;,
  -0.991313;-0.131525;0.000000;,
  -0.208226;-0.114802;-0.971320;,
  0.208226;-0.114802;-0.971320;,
  0.407248;-0.126288;-0.904544;,
  0.976793;-0.214186;-0.000000;,
  0.208226;-0.114802;0.971320;,
  -0.208226;-0.114802;0.971320;,
  -0.407248;-0.126289;0.904544;,
  -0.976793;-0.214186;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.209945;0.000000;-0.977713;,
  0.209945;0.000000;-0.977713;,
  0.410532;0.000000;-0.911846;,
  1.000000;0.000000;0.000000;,
  0.209945;0.000000;0.977713;,
  -0.209945;0.000000;0.977713;,
  -0.410532;0.000000;0.911846;,
  -1.000000;0.000000;0.000000;,
  0.410446;-0.020991;0.911643;,
  -0.410446;-0.020991;-0.911643;,
  0.410284;-0.034916;0.911289;,
  -0.410284;-0.034916;-0.911289;,
  0.409310;-0.077166;0.909126;,
  -0.409310;-0.077166;-0.909126;,
  0.407248;-0.126288;0.904544;,
  -0.407248;-0.126288;-0.904544;,
  0.410532;0.000000;0.911846;,
  -0.410532;0.000000;-0.911846;;
  64;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,19;,
  4;11,12,20,58;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,23;,
  4;15,8,16,59;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;19,19,27,27;,
  4;58,20,28,60;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;23,23,31,31;,
  4;59,16,24,61;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;27,27,35,35;,
  4;60,28,36,62;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;31,31,39,39;,
  4;61,24,32,63;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;35,35,43,43;,
  4;62,36,44,64;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;39,39,47,47;,
  4;63,32,40,65;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  4;50,51,1,0;,
  3;49,49,49;,
  4;51,52,2,1;,
  3;49,49,49;,
  4;53,53,3,2;,
  3;49,49,49;,
  4;66,54,4,3;,
  3;49,49,49;,
  4;54,55,5,4;,
  3;49,49,49;,
  4;55,56,6,5;,
  3;49,49,49;,
  4;57,57,7,6;,
  3;49,49,49;,
  4;67,50,0,7;,
  3;49,49,49;;
 }
 MeshTextureCoords {
  88;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.200000;,
  0.000000;0.200000;,
  0.250000;0.000000;,
  0.250000;0.200000;,
  0.375000;0.000000;,
  0.375000;0.200000;,
  0.500000;0.000000;,
  0.500000;0.200000;,
  0.625000;0.000000;,
  0.625000;0.200000;,
  0.750000;0.000000;,
  0.750000;0.200000;,
  0.875000;0.000000;,
  0.875000;0.200000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.125000;0.400000;,
  0.000000;0.400000;,
  0.250000;0.400000;,
  0.375000;0.400000;,
  0.500000;0.400000;,
  0.625000;0.400000;,
  0.750000;0.400000;,
  0.875000;0.400000;,
  1.000000;0.400000;,
  0.292890;-0.000000;,
  0.707110;-0.000000;,
  0.701000;0.504950;,
  0.299000;0.504950;,
  1.000000;-0.000000;,
  0.985260;0.504950;,
  0.375000;0.600000;,
  0.250000;0.600000;,
  0.500000;0.600000;,
  0.625000;0.600000;,
  0.750000;0.600000;,
  0.875000;0.600000;,
  0.000000;-0.000000;,
  0.014740;0.504950;,
  0.697030;1.000000;,
  0.302970;1.000000;,
  0.975670;1.000000;,
  0.375000;0.800000;,
  0.250000;0.800000;,
  0.500000;0.800000;,
  0.625000;0.800000;,
  0.750000;0.800000;,
  0.875000;0.800000;,
  0.024330;1.000000;,
  0.000000;0.800000;,
  0.125000;0.800000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;0.800000;,
  1.000000;1.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.062500;0.000000;,
  0.250000;0.000000;,
  0.187500;0.000000;,
  0.375000;0.000000;,
  0.312500;0.000000;,
  0.500000;0.000000;,
  0.437500;0.000000;,
  0.625000;0.000000;,
  0.562500;0.000000;,
  0.750000;0.000000;,
  0.687500;0.000000;,
  0.875000;0.000000;,
  0.812500;0.000000;,
  1.000000;0.000000;,
  0.937500;0.000000;;
 }
}
