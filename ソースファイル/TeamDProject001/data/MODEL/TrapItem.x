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
 196;
 -81.10080;5.30940;-36.87970;,
 81.10080;5.30940;-36.87970;,
 81.10080;-0.06870;-36.87970;,
 -81.10080;-0.06870;-36.87970;,
 81.10080;5.30940;-36.87970;,
 81.10080;5.30940;36.87970;,
 81.10080;-0.06870;36.87970;,
 81.10080;-0.06870;-36.87970;,
 81.10080;5.30940;36.87970;,
 -81.10080;5.30940;36.87970;,
 -81.10080;-0.06870;36.87970;,
 81.10080;-0.06870;36.87970;,
 -81.10080;5.30940;36.87970;,
 -81.10080;5.30940;-36.87970;,
 -81.10080;-0.06870;-36.87970;,
 -81.10080;-0.06870;36.87970;,
 81.10080;5.30940;-36.87970;,
 -81.10080;5.30940;-36.87970;,
 -81.10080;-0.06870;-36.87970;,
 81.10080;-0.06870;-36.87970;,
 0.00000;19.34120;32.39440;,
 5.66840;16.99330;32.39440;,
 5.66840;16.99330;-32.39440;,
 0.00000;19.34120;-32.39440;,
 8.01630;11.32490;32.39440;,
 8.01630;11.32490;-32.39440;,
 5.66840;5.65660;32.39440;,
 5.66840;5.65660;-32.39440;,
 0.00000;3.30860;32.39440;,
 0.00000;3.30860;-32.39440;,
 -5.66840;5.65660;32.39440;,
 -5.66840;5.65660;-32.39440;,
 -8.01630;11.32490;32.39440;,
 -8.01630;11.32490;-32.39440;,
 -5.66840;16.99330;32.39440;,
 -5.66840;16.99330;-32.39440;,
 0.00000;11.32490;32.39440;,
 0.00000;11.32490;-32.39440;,
 74.02500;11.38301;0.00310;,
 74.02500;8.05112;0.00310;,
 74.02500;8.05112;10.91890;,
 74.02500;11.38301;10.91890;,
 74.02500;8.05112;31.91100;,
 74.02500;11.38301;31.91100;,
 72.12030;8.05112;31.92480;,
 72.12030;11.38301;31.92480;,
 -0.08810;8.05112;31.92480;,
 -0.08810;11.38301;31.92480;,
 77.35700;8.05112;0.00310;,
 77.35700;8.05112;10.91890;,
 77.35700;8.05112;31.91100;,
 72.12030;8.05112;34.21700;,
 -0.08810;8.05112;34.21700;,
 77.35700;11.38301;0.00310;,
 77.35700;11.38301;10.91890;,
 77.35700;11.38301;31.91100;,
 72.12030;11.38301;34.21700;,
 -0.08810;11.38301;34.21700;,
 74.02500;11.38301;0.01750;,
 74.02500;11.38301;-10.89830;,
 74.02500;8.05112;-10.89830;,
 74.02500;8.05112;0.01750;,
 74.02500;11.38301;-31.89040;,
 74.02500;8.05112;-31.89040;,
 72.12030;11.38301;-31.90430;,
 72.12030;8.05112;-31.90430;,
 -0.08810;11.38301;-31.90430;,
 -0.08810;8.05112;-31.90430;,
 77.35700;8.05112;-10.89830;,
 77.35700;8.05112;0.01750;,
 77.35700;8.05112;-31.89040;,
 72.12030;8.05112;-34.19640;,
 -0.08810;8.05112;-34.19640;,
 77.35700;11.38301;-10.89830;,
 77.35700;11.38301;0.01750;,
 77.35700;11.38301;-31.89040;,
 72.12030;11.38301;-34.19640;,
 -0.08810;11.38301;-34.19640;,
 -37.09920;8.06620;-17.54060;,
 -2.10340;5.61900;-17.54060;,
 -2.11800;5.41140;-17.54060;,
 -37.11370;7.85850;-17.54060;,
 -2.10340;5.61900;-17.54060;,
 -2.10340;5.61900;17.54060;,
 -2.11800;5.41140;17.54060;,
 -2.11800;5.41140;-17.54060;,
 -2.10340;5.61900;17.54060;,
 -37.09920;8.06620;17.54060;,
 -37.11370;7.85850;17.54060;,
 -2.11800;5.41140;17.54060;,
 -37.09920;8.06620;17.54060;,
 -37.09920;8.06620;-17.54060;,
 -37.11370;7.85850;-17.54060;,
 -37.11370;7.85850;17.54060;,
 -2.10340;5.61900;-17.54060;,
 -37.09920;8.06620;-17.54060;,
 -37.11370;7.85850;-17.54060;,
 -2.11800;5.41140;-17.54060;,
 -83.14861;6.66080;-39.54684;,
 -83.14861;-2.20976;-39.54684;,
 83.14861;-2.20976;-39.54684;,
 83.14861;6.66080;-39.54684;,
 83.14861;6.66080;-39.54684;,
 83.14861;-2.20976;-39.54684;,
 83.14861;-2.20976;39.54684;,
 83.14861;6.66080;39.54684;,
 83.14861;6.66080;39.54684;,
 83.14861;-2.20976;39.54684;,
 -83.14861;-2.20976;39.54684;,
 -83.14861;6.66080;39.54684;,
 -83.14861;6.66080;39.54684;,
 -83.14861;-2.20976;39.54684;,
 -83.14861;-2.20976;-39.54684;,
 -83.14861;6.66080;-39.54684;,
 -83.14861;6.66080;-39.54684;,
 83.14861;6.66080;-39.54684;,
 -83.14861;-2.20976;-39.54684;,
 83.14861;-2.20976;-39.54684;,
 0.00000;19.58626;33.21238;,
 0.00000;19.58626;-33.21238;,
 5.81153;17.17908;-33.21238;,
 5.81153;17.17908;33.21238;,
 8.21872;11.36754;-33.21238;,
 8.21872;11.36754;33.21238;,
 5.81153;5.55611;-33.21238;,
 5.81153;5.55611;33.21238;,
 0.00000;3.14882;-33.21238;,
 0.00000;3.14882;33.21238;,
 -5.81153;5.55611;-33.21238;,
 -5.81153;5.55611;33.21238;,
 -8.21872;11.36754;-33.21238;,
 -8.21872;11.36754;33.21238;,
 -5.81153;17.17908;-33.21238;,
 -5.81153;17.17908;33.21238;,
 0.00000;11.36754;33.21238;,
 0.00000;11.36754;-33.21238;,
 72.93036;12.33284;0.00000;,
 72.93036;12.33284;11.19142;,
 72.93036;7.40912;11.19142;,
 72.93036;7.40912;0.00000;,
 72.93176;12.32997;30.67669;,
 72.93176;7.40625;30.67669;,
 72.93176;12.32997;30.67669;,
 -1.21025;12.32997;30.67669;,
 -1.21025;7.40625;30.67669;,
 72.93176;7.40625;30.67669;,
 78.28103;7.40625;11.19460;,
 78.28103;7.40625;0.00318;,
 78.28103;7.40625;32.71676;,
 -1.21025;7.40625;35.08099;,
 73.94141;7.40625;35.08099;,
 78.28103;12.32997;11.19460;,
 78.28103;12.32997;0.00318;,
 78.28103;12.32997;32.71676;,
 73.94141;12.32997;35.08099;,
 -1.21025;12.32997;35.08099;,
 72.93036;7.40912;-11.17667;,
 72.93036;12.33284;-11.17667;,
 72.93176;7.40625;-30.65569;,
 72.93176;12.32997;-30.65569;,
 72.93176;12.32997;-30.65569;,
 72.93176;7.40625;-30.65569;,
 -1.21025;7.40625;-30.65569;,
 -1.21025;12.32997;-30.65569;,
 78.28103;7.40625;-11.17349;,
 78.28103;7.40625;-32.69564;,
 73.94141;7.40625;-35.05987;,
 -1.21025;7.40625;-35.05987;,
 78.28103;12.32997;-11.17349;,
 78.28103;12.32997;-32.69564;,
 73.94141;12.32997;-35.05987;,
 -1.21025;12.32997;-35.05987;,
 -38.03597;8.38704;-17.98351;,
 -38.05085;7.50226;-17.98351;,
 -2.17148;4.99337;-17.98351;,
 -2.15651;5.87804;-17.98351;,
 -2.15651;5.87804;-17.98351;,
 -2.17148;4.99337;-17.98351;,
 -2.17148;4.99337;17.98351;,
 -2.15651;5.87804;17.98351;,
 -2.15651;5.87804;17.98351;,
 -2.17148;4.99337;17.98351;,
 -38.05085;7.50226;17.98351;,
 -38.03597;8.38704;17.98351;,
 -38.03597;8.38704;17.98351;,
 -38.05085;7.50226;17.98351;,
 -38.05085;7.50226;-17.98351;,
 -38.03597;8.38704;-17.98351;,
 -38.03597;8.38704;-17.98351;,
 -2.15651;5.87804;-17.98351;,
 -38.05085;7.50226;-17.98351;,
 -2.17148;4.99337;-17.98351;,
 72.93176;12.32997;-30.65569;,
 72.93176;7.40625;-30.65569;,
 72.93176;12.32997;30.67669;,
 72.93176;7.40625;30.67669;;
 
 140;
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
 4;41,40,42,43;,
 4;43,42,44,45;,
 4;45,44,46,47;,
 4;39,48,49,40;,
 4;40,49,50,42;,
 4;42,50,51,44;,
 4;44,51,52,46;,
 4;48,53,54,49;,
 4;49,54,55,50;,
 4;50,55,56,51;,
 4;51,56,57,52;,
 4;53,38,41,54;,
 4;54,41,43,55;,
 4;55,43,45,56;,
 4;56,45,47,57;,
 4;53,48,39,38;,
 4;47,46,52,57;,
 4;58,59,60,61;,
 4;59,62,63,60;,
 4;62,64,65,63;,
 4;64,66,67,65;,
 4;61,60,68,69;,
 4;60,63,70,68;,
 4;63,65,71,70;,
 4;65,67,72,71;,
 4;69,68,73,74;,
 4;68,70,75,73;,
 4;70,71,76,75;,
 4;71,72,77,76;,
 4;74,73,59,58;,
 4;73,75,62,59;,
 4;75,76,64,62;,
 4;76,77,66,64;,
 4;74,58,61,69;,
 4;66,77,72,67;,
 4;78,79,80,81;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;90,83,94,95;,
 4;96,97,84,93;,
 4;98,99,100,101;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;110,111,112,113;,
 4;110,114,115,105;,
 4;116,111,104,117;,
 4;118,119,120,121;,
 4;121,120,122,123;,
 4;123,122,124,125;,
 4;125,124,126,127;,
 4;127,126,128,129;,
 4;129,128,130,131;,
 4;131,130,132,133;,
 4;133,132,119,118;,
 3;134,118,121;,
 3;134,121,123;,
 3;134,123,125;,
 3;134,125,127;,
 3;134,127,129;,
 3;134,129,131;,
 3;134,131,133;,
 3;134,133,118;,
 3;135,120,119;,
 3;135,122,120;,
 3;135,124,122;,
 3;135,126,124;,
 3;135,128,126;,
 3;135,130,128;,
 3;135,132,130;,
 3;135,119,132;,
 4;136,137,138,139;,
 4;137,140,141,138;,
 4;142,143,144,145;,
 4;139,138,146,147;,
 4;138,141,148,146;,
 4;145,144,149,150;,
 4;147,146,151,152;,
 4;146,148,153,151;,
 4;148,150,154,153;,
 4;150,149,155,154;,
 4;151,153,140,137;,
 4;154,155,143,142;,
 4;143,155,149,144;,
 4;136,139,156,157;,
 4;157,156,158,159;,
 4;160,161,162,163;,
 4;139,147,164,156;,
 4;156,164,165,158;,
 4;161,166,167,162;,
 4;147,152,168,164;,
 4;164,168,169,165;,
 4;165,169,170,166;,
 4;166,170,171,167;,
 4;168,157,159,169;,
 4;170,160,163,171;,
 4;163,162,167,171;,
 4;172,173,174,175;,
 4;176,177,178,179;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;184,188,189,179;,
 4;190,185,178,191;,
 3;192,170,169;,
 3;193,165,166;,
 3;194,153,154;,
 3;195,150,148;,
 4;157,168,152,136;,
 4;151,137,136,152;;
 
 MeshMaterialList {
  4;
  140;
  1,
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
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
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
    "data\\TEXTURE\\coil.png";
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
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  76;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.707107;0.707107;0.000000;,
  1.000000;-0.000003;-0.000000;,
  0.707110;-0.707104;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.707110;-0.707104;0.000000;,
  -1.000000;-0.000003;0.000000;,
  -0.707107;0.707107;0.000000;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  -0.003623;0.000000;-0.999993;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.205918;0.000000;0.978569;,
  0.000000;0.000000;1.000000;,
  -0.003649;0.000000;0.999993;,
  0.205918;0.000000;-0.978569;,
  -0.007246;0.000000;-0.999974;,
  0.403010;0.000000;0.915196;,
  0.000000;1.000000;0.000000;,
  -0.007298;0.000000;0.999973;,
  0.403010;0.000000;-0.915196;,
  0.000000;0.000000;-1.000000;,
  0.997536;-0.070154;-0.000000;,
  0.000000;0.000000;1.000000;,
  -0.997572;0.069641;0.000000;,
  0.069758;0.997564;0.000000;,
  -0.069755;-0.997564;0.000000;,
  0.000000;-0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.707107;-0.707107;0.000000;,
  -1.000000;0.000003;0.000000;,
  -0.707110;0.707104;0.000000;,
  0.000000;1.000000;0.000000;,
  0.707110;0.707104;0.000000;,
  1.000000;0.000003;0.000000;,
  0.707107;-0.707107;-0.000000;,
  1.000000;0.000000;-0.000036;,
  1.000000;0.000000;-0.000072;,
  0.000389;1.000000;0.000037;,
  0.000120;1.000000;0.000037;,
  -0.246843;0.000000;-0.969055;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000036;,
  1.000000;0.000000;0.000072;,
  0.000537;1.000000;0.000000;,
  0.000389;1.000000;-0.000037;,
  0.000120;1.000000;-0.000037;,
  -0.246844;0.000000;0.969055;,
  -0.999857;0.016920;0.000000;,
  0.000080;1.000000;0.000025;,
  -0.478409;0.000000;-0.878137;,
  -0.000389;-1.000000;-0.000037;,
  -0.000120;-1.000000;-0.000037;,
  -0.000080;-1.000000;-0.000025;,
  1.000000;0.000000;0.000000;,
  0.000080;1.000000;-0.000025;,
  -0.478410;0.000000;0.878136;,
  -0.000389;-1.000000;0.000037;,
  -0.000080;-1.000000;0.000025;,
  -0.000120;-1.000000;0.000037;,
  1.000000;0.000000;-0.000000;,
  0.999858;-0.016821;-0.000000;,
  -0.069758;-0.997564;0.000000;,
  0.069755;0.997564;0.000000;,
  -0.000537;-1.000000;0.000000;;
  140;
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
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;25,25,17,17;,
  4;17,17,18,18;,
  4;19,19,19,19;,
  4;19,19,19,19;,
  4;19,19,19,19;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;26,26,21,21;,
  4;21,21,22,22;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;18,18,18,18;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;28,23,23,28;,
  4;23,22,22,23;,
  4;19,19,19,19;,
  4;19,19,19,19;,
  4;19,19,19,19;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;29,24,24,29;,
  4;24,18,18,24;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;22,22,22,22;,
  4;16,16,16,16;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;52,52,52,52;,
  4;39,39,39,39;,
  4;43,43,43,43;,
  4;39,39,40,40;,
  4;40,40,41,41;,
  4;41,41,42,42;,
  4;42,42,43,43;,
  4;43,43,44,44;,
  4;44,44,45,45;,
  4;45,45,46,46;,
  4;46,46,39,39;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;36,36,36;,
  3;36,36,36;,
  3;36,36,36;,
  3;36,36,36;,
  3;36,36,36;,
  3;36,36,36;,
  3;36,36,36;,
  3;36,36,36;,
  4;52,47,47,52;,
  4;47,48,48,47;,
  4;36,36,36,36;,
  4;55,49,49,55;,
  4;49,60,50,49;,
  4;60,43,43,43;,
  4;37,37,37,37;,
  4;37,37,37,37;,
  4;61,51,51,61;,
  4;51,38,38,51;,
  4;62,63,64,62;,
  4;39,39,39,64;,
  4;65,65,65,65;,
  4;52,52,53,53;,
  4;53,53,54,54;,
  4;38,38,38,38;,
  4;55,55,56,56;,
  4;56,56,57,66;,
  4;66,43,43,43;,
  4;37,37,37,37;,
  4;37,37,37,37;,
  4;67,67,58,58;,
  4;58,58,36,36;,
  4;68,68,69,70;,
  4;39,69,39,39;,
  4;71,71,71,71;,
  4;36,36,36,36;,
  4;59,59,59,59;,
  4;38,38,38,38;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;74,74,74,74;,
  3;69,39,70;,
  3;66,57,43;,
  3;64,63,39;,
  3;60,43,50;,
  4;68,68,75,75;,
  4;62,62,75,75;;
 }
 MeshTextureCoords {
  196;
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
  0.565540;0.084180;,
  0.434430;0.084340;,
  0.418860;0.084340;,
  0.581110;0.084180;,
  0.394970;0.084340;,
  0.605000;0.084180;,
  0.356290;0.084340;,
  0.643680;0.084180;,
  0.294750;0.084340;,
  0.705230;0.084180;,
  0.434460;0.915820;,
  0.418890;0.915820;,
  0.395000;0.915820;,
  0.356320;0.915820;,
  0.294770;0.915820;,
  0.565570;0.915660;,
  0.581140;0.915660;,
  0.605030;0.915660;,
  0.643710;0.915660;,
  0.705250;0.915660;,
  0.565540;0.084180;,
  0.581110;0.084180;,
  0.418860;0.084340;,
  0.434430;0.084340;,
  0.605000;0.084180;,
  0.394970;0.084340;,
  0.643680;0.084180;,
  0.356290;0.084340;,
  0.705230;0.084180;,
  0.294750;0.084340;,
  0.418890;0.915820;,
  0.434460;0.915820;,
  0.395000;0.915820;,
  0.356320;0.915820;,
  0.294770;0.915820;,
  0.581140;0.915660;,
  0.565570;0.915660;,
  0.605030;0.915660;,
  0.643710;0.915660;,
  0.705250;0.915660;,
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
  1.000000;0.000000;,
  0.500080;0.995040;,
  0.499920;0.004960;,
  0.448310;0.004970;,
  0.448480;0.995050;,
  0.401020;0.004980;,
  0.401200;0.995050;,
  0.372870;0.004970;,
  0.373140;0.995050;,
  0.499520;0.004960;,
  0.500480;0.995040;,
  0.626860;0.004950;,
  0.627130;0.995030;,
  0.598800;0.004950;,
  0.598980;0.995020;,
  0.551520;0.004950;,
  0.551690;0.995030;,
  0.500140;0.995040;,
  0.499860;0.004960;,
  0.565540;0.084180;,
  0.581110;0.084180;,
  0.418860;0.084340;,
  0.434430;0.084340;,
  0.605000;0.084180;,
  0.394970;0.084340;,
  0.643680;0.084180;,
  0.705230;0.084180;,
  0.294750;0.084340;,
  0.356290;0.084340;,
  0.418890;0.915820;,
  0.434460;0.915820;,
  0.395000;0.915820;,
  0.294770;0.915820;,
  0.356320;0.915820;,
  0.581140;0.915660;,
  0.565570;0.915660;,
  0.605030;0.915660;,
  0.643710;0.915660;,
  0.705250;0.915660;,
  0.418860;0.084340;,
  0.581110;0.084180;,
  0.394970;0.084340;,
  0.605000;0.084180;,
  0.643680;0.084180;,
  0.356290;0.084340;,
  0.294750;0.084340;,
  0.705230;0.084180;,
  0.418890;0.915820;,
  0.395000;0.915820;,
  0.356320;0.915820;,
  0.294770;0.915820;,
  0.581140;0.915660;,
  0.605030;0.915660;,
  0.643710;0.915660;,
  0.705250;0.915660;,
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
  1.000000;0.000000;,
  0.624340;0.084180;,
  0.375630;0.084340;,
  0.624340;0.084180;,
  0.375630;0.084340;;
 }
}
