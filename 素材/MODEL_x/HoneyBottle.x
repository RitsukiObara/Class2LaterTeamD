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
 -57.88553;404.89722;-62.91807;,
 57.88552;404.89722;-62.91809;,
 80.45078;320.80600;-87.44515;,
 -80.45078;320.80600;-87.44514;,
 139.74799;404.89722;-26.06154;,
 194.22534;320.80600;-36.22097;,
 139.74799;404.89722;26.06154;,
 194.22534;320.80600;36.22097;,
 57.88550;404.89722;62.91809;,
 80.45077;320.80600;87.44515;,
 -57.88555;404.89722;62.91807;,
 -80.45081;320.80600;87.44514;,
 -139.74797;404.89722;26.06154;,
 -194.22533;320.80600;36.22099;,
 -139.74799;404.89722;-26.06152;,
 -194.22534;320.80600;-36.22097;,
 -57.88553;404.89722;-62.91807;,
 -80.45078;320.80600;-87.44514;,
 80.45078;236.71480;-87.44515;,
 -80.45078;236.71480;-87.44514;,
 194.22534;236.71480;-36.22097;,
 194.22534;236.71480;36.22097;,
 80.45077;236.71480;87.44515;,
 -80.45081;236.71480;87.44514;,
 -194.22533;236.71480;36.22099;,
 -194.22534;236.71480;-36.22097;,
 -80.45078;236.71480;-87.44514;,
 -80.45078;236.71480;-87.44514;,
 80.45078;236.71480;-87.44515;,
 78.07893;157.58194;-84.86715;,
 -78.07894;157.58194;-84.86713;,
 194.22534;236.71480;-36.22097;,
 188.49922;157.58194;-35.15311;,
 188.49922;157.58194;35.15311;,
 188.49922;157.58194;-35.15311;,
 78.07893;157.58194;84.86715;,
 -78.07897;157.58194;84.86713;,
 -188.49921;157.58194;35.15313;,
 -188.49922;157.58194;-35.15311;,
 -194.22534;236.71480;-36.22097;,
 -188.49922;157.58194;-35.15311;,
 76.53668;80.00000;-83.19080;,
 -76.53669;80.00000;-83.19080;,
 184.77591;80.00000;-34.45875;,
 184.77591;80.00000;34.45875;,
 184.77591;80.00000;-34.45875;,
 76.53667;80.00000;83.19080;,
 -76.53672;80.00000;83.19080;,
 -184.77589;80.00000;34.45876;,
 -184.77591;80.00000;-34.45875;,
 -184.77591;80.00000;-34.45875;,
 -76.53669;80.00000;-83.19080;,
 76.53668;80.00000;-83.19080;,
 69.27052;0.00000;-75.29298;,
 -69.27052;0.00000;-75.29298;,
 167.23381;0.00000;-31.18734;,
 167.23381;0.00000;31.18734;,
 69.27051;0.00000;75.29298;,
 -69.27055;0.00000;75.29298;,
 -167.23380;0.00000;31.18734;,
 -167.23381;0.00000;-31.18734;,
 -76.53669;80.00000;-83.19080;,
 -69.27052;0.00000;-75.29298;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 -57.88553;455.23309;-62.91807;,
 57.88552;455.23309;-62.91809;,
 0.00000;455.23309;0.00000;,
 139.74799;455.23309;-26.06154;,
 0.00000;455.23309;0.00000;,
 139.74799;455.23309;26.06154;,
 0.00000;455.23309;0.00000;,
 57.88550;455.23309;62.91809;,
 0.00000;455.23309;0.00000;,
 -57.88555;455.23309;62.91807;,
 0.00000;455.23309;0.00000;,
 -139.74797;455.23309;26.06154;,
 0.00000;455.23309;0.00000;,
 -139.74799;455.23309;-26.06152;,
 0.00000;455.23309;0.00000;,
 -57.88553;455.23309;-62.91807;,
 0.00000;455.23309;0.00000;;
 
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
   0.633726;0.357647;0.200784;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.621176;0.081569;1.000000;;
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
  65;
  -0.205838;0.163691;-0.964798;,
  0.205838;0.163691;-0.964798;,
  0.799413;0.271854;-0.535756;,
  0.799413;0.271854;0.535756;,
  0.205838;0.163691;0.964798;,
  -0.205838;0.163691;0.964798;,
  -0.799413;0.271854;0.535757;,
  -0.799413;0.271854;-0.535756;,
  -0.205838;0.163691;-0.964798;,
  0.205838;0.163691;0.964798;,
  -0.205838;0.163691;0.964798;,
  -0.799413;0.271854;0.535757;,
  -0.799413;0.271854;-0.535756;,
  -0.209890;-0.019062;-0.977539;,
  0.209890;-0.019062;-0.977539;,
  0.410445;-0.020992;-0.911644;,
  0.999348;-0.036110;-0.000000;,
  0.209890;-0.019062;0.977539;,
  -0.209890;-0.019062;0.977539;,
  -0.410445;-0.020992;0.911644;,
  -0.999348;-0.036110;0.000000;,
  -0.209815;-0.031704;-0.977227;,
  0.209815;-0.031704;-0.977227;,
  0.410285;-0.034914;-0.911289;,
  0.998195;-0.060059;-0.000000;,
  0.209815;-0.031704;0.977227;,
  -0.209815;-0.031704;0.977227;,
  -0.410285;-0.034914;0.911289;,
  -0.998195;-0.060059;0.000000;,
  -0.209256;-0.070122;-0.975343;,
  0.209256;-0.070122;-0.975343;,
  0.409312;-0.077165;-0.909126;,
  0.991313;-0.131525;-0.000000;,
  0.209256;-0.070122;0.975344;,
  -0.209256;-0.070122;0.975344;,
  -0.409312;-0.077165;0.909126;,
  -0.991313;-0.131525;0.000000;,
  -0.208226;-0.114804;-0.971320;,
  0.208226;-0.114804;-0.971320;,
  0.407249;-0.126289;-0.904544;,
  0.976793;-0.214187;-0.000000;,
  0.208226;-0.114804;0.971320;,
  -0.208226;-0.114804;0.971320;,
  -0.407249;-0.126289;0.904544;,
  -0.976793;-0.214187;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.209947;0.000000;-0.977713;,
  0.209947;0.000000;-0.977713;,
  0.410535;0.000000;-0.911845;,
  1.000000;0.000000;0.000000;,
  0.209947;0.000000;0.977713;,
  -0.209947;0.000000;0.977713;,
  -0.410535;0.000000;0.911845;,
  -1.000000;0.000000;0.000000;,
  0.410445;-0.020992;0.911644;,
  -0.410445;-0.020992;-0.911644;,
  0.410285;-0.034914;0.911289;,
  -0.410285;-0.034914;-0.911289;,
  0.409312;-0.077165;0.909126;,
  -0.409312;-0.077165;-0.909126;,
  0.407249;-0.126289;0.904544;,
  -0.407249;-0.126289;-0.904544;,
  0.410535;0.000000;0.911845;,
  -0.410536;0.000000;-0.911845;;
  64;
  4;0,1,1,8;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,9,3;,
  4;4,5,10,9;,
  4;5,6,11,10;,
  4;6,7,12,11;,
  4;7,0,8,12;,
  4;8,1,14,13;,
  4;1,2,15,14;,
  4;2,3,16,16;,
  4;3,9,17,55;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,20;,
  4;12,8,13,56;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;16,16,24,24;,
  4;55,17,25,57;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;20,20,28,28;,
  4;56,13,21,58;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;24,24,32,32;,
  4;57,25,33,59;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;28,28,36,36;,
  4;58,21,29,60;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;32,32,40,40;,
  4;59,33,41,61;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;36,36,44,44;,
  4;60,29,37,62;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  4;47,48,1,0;,
  3;46,46,46;,
  4;48,49,2,1;,
  3;46,46,46;,
  4;50,50,3,2;,
  3;46,46,46;,
  4;63,51,4,3;,
  3;46,46,46;,
  4;51,52,5,4;,
  3;46,46,46;,
  4;52,53,6,5;,
  3;46,46,46;,
  4;54,54,7,6;,
  3;46,46,46;,
  4;64,47,0,7;,
  3;46,46,46;;
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
  0.292893;-0.000000;,
  0.707107;-0.000000;,
  0.701001;0.504948;,
  0.298999;0.504948;,
  1.000000;-0.000000;,
  0.985259;0.504948;,
  0.375000;0.600000;,
  0.250000;0.600000;,
  0.500000;0.600000;,
  0.625000;0.600000;,
  0.750000;0.600000;,
  0.875000;0.600000;,
  0.000000;-0.000000;,
  0.014741;0.504948;,
  0.697031;1.000000;,
  0.302969;1.000000;,
  0.975674;1.000000;,
  0.375000;0.800000;,
  0.250000;0.800000;,
  0.500000;0.800000;,
  0.625000;0.800000;,
  0.750000;0.800000;,
  0.875000;0.800000;,
  0.024326;1.000000;,
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
