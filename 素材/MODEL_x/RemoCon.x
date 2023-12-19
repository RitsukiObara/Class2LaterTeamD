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
 192;
 -31.91330;1.99570;72.28040;,
 -31.91330;14.76430;72.28040;,
 -31.91330;14.76430;-9.82650;,
 -31.91330;1.99570;-9.82650;,
 -28.61380;17.08550;70.95820;,
 -28.61380;17.08550;-9.82650;,
 31.91330;1.99570;72.28040;,
 31.91330;1.99570;-9.82650;,
 31.91330;14.76430;-9.82650;,
 31.91330;14.76430;72.28040;,
 28.61380;17.08550;-9.82650;,
 28.61380;17.08550;70.95820;,
 -31.91330;1.99570;-66.32110;,
 -31.91330;14.76430;-66.32110;,
 -31.91330;14.76430;-125.67220;,
 -31.91330;1.99570;-125.67220;,
 -28.61380;17.08550;-64.99880;,
 -28.61380;17.08550;-123.02790;,
 31.91330;1.99570;-66.32110;,
 31.91330;1.99570;-125.67220;,
 31.91330;14.76430;-125.67220;,
 31.91330;14.76430;-66.32110;,
 28.61380;17.08550;-123.02790;,
 28.61380;17.08550;-64.99880;,
 -31.91330;1.99570;98.95480;,
 -31.91330;1.99570;128.08070;,
 -31.91330;14.76430;128.08070;,
 -31.91330;14.76430;98.95480;,
 -28.61380;17.08550;123.70700;,
 -28.61380;17.08550;96.97150;,
 31.91330;1.99570;98.95480;,
 31.91330;14.76430;98.95480;,
 31.91330;14.76430;128.08070;,
 31.91330;1.99570;128.08070;,
 28.61380;17.08550;96.97150;,
 28.61380;17.08550;123.70700;,
 -29.91330;0.99570;-12.47090;,
 -29.91330;-0.00430;-7.18200;,
 -29.91330;-0.00430;69.63600;,
 -29.91330;0.99570;74.92490;,
 29.91330;0.99570;-12.47090;,
 29.91330;-0.00430;-7.18200;,
 29.91330;0.99570;74.92490;,
 29.91330;-0.00430;69.63600;,
 -29.91330;-0.00430;-68.96550;,
 -29.91330;0.99570;-63.67660;,
 -29.91330;-0.00430;-123.02790;,
 29.91330;0.99570;-63.67660;,
 29.91330;-0.00430;-68.96550;,
 29.91330;-0.00430;-123.02790;,
 -29.91330;0.99570;96.31040;,
 -29.91330;-0.00430;101.59930;,
 29.91330;-0.00430;101.59930;,
 29.91330;0.99570;96.31040;,
 -29.91330;-0.00430;123.70700;,
 29.91330;-0.00430;123.70700;,
 -15.95670;14.76430;-132.43140;,
 -15.95670;1.99570;-132.43140;,
 -14.30690;17.08550;-129.78700;,
 -14.95670;-0.00430;-129.78700;,
 -14.30690;17.08550;-64.99880;,
 -14.95670;-0.00430;-68.96550;,
 -14.30690;17.08550;-9.82650;,
 -14.95670;0.99570;-63.67660;,
 -14.30690;17.08550;70.95820;,
 -14.95670;0.99570;-12.47090;,
 -14.30690;17.08550;96.97150;,
 -14.95670;-0.00430;-7.18200;,
 -14.30690;17.08550;129.36560;,
 -14.95670;-0.00430;69.63600;,
 -15.95670;14.76430;133.73920;,
 -14.95670;0.99570;74.92490;,
 -15.95670;1.99570;133.73920;,
 -14.95670;0.99570;96.31040;,
 -14.95670;-0.00430;129.36560;,
 -14.95670;-0.00430;101.59930;,
 15.95670;14.76430;-132.43140;,
 15.95670;1.99570;-132.43140;,
 14.30690;17.08550;-129.78700;,
 14.95670;-0.00430;-129.78700;,
 14.30690;17.08550;-64.99880;,
 14.95670;-0.00430;-68.96550;,
 14.30690;17.08550;-9.82650;,
 14.95670;0.99570;-63.67660;,
 14.30690;17.08550;70.95820;,
 14.95670;0.99570;-12.47090;,
 14.30690;17.08550;96.97150;,
 14.95670;-0.00430;-7.18200;,
 14.30690;17.08550;129.36560;,
 14.95670;-0.00430;69.63600;,
 15.95670;14.76430;133.73920;,
 14.95670;0.99570;74.92490;,
 15.95670;1.99570;133.73920;,
 14.95670;0.99570;96.31040;,
 14.95670;-0.00430;129.36560;,
 14.95670;-0.00430;101.59930;,
 -31.91330;-1.50980;74.82510;,
 -31.91330;-1.50980;-10.19890;,
 -31.91330;18.09780;-10.19890;,
 -31.91330;18.09780;74.82510;,
 -28.61380;21.66230;-10.19890;,
 -28.61380;21.66230;73.45600;,
 31.91330;-1.50980;74.82510;,
 31.91330;18.09780;74.82510;,
 31.91330;18.09780;-10.19890;,
 31.91330;-1.50980;-10.19890;,
 28.61380;21.66230;73.45600;,
 28.61380;21.66230;-10.19890;,
 -31.91330;-1.50980;-68.70060;,
 -31.91330;18.09780;-68.70060;,
 -31.91330;-1.50980;-130.16040;,
 -31.91330;18.09780;-130.16040;,
 -28.61380;21.66230;-67.33130;,
 -28.61380;21.66230;-127.42200;,
 31.91330;-1.50980;-68.70060;,
 31.91330;18.09780;-68.70060;,
 31.91330;18.09780;-130.16040;,
 31.91330;-1.50980;-130.16040;,
 28.61380;21.66230;-67.33130;,
 28.61380;21.66230;-127.42200;,
 -31.91330;-1.50980;102.44730;,
 -31.91330;18.09780;102.44730;,
 -31.91330;18.09780;132.60789;,
 -31.91330;-1.50980;132.60789;,
 -28.61380;21.66230;100.39350;,
 -28.61380;21.66230;128.07890;,
 31.91330;-1.50980;102.44730;,
 31.91330;18.09780;102.44730;,
 31.91330;-1.50980;132.60789;,
 31.91330;18.09780;132.60789;,
 28.61380;21.66230;100.39350;,
 28.61380;21.66230;128.07890;,
 -29.91330;-3.04540;-12.93720;,
 -29.91330;-4.58100;-7.46040;,
 -29.91330;-4.58100;72.08680;,
 -29.91330;-3.04540;77.56360;,
 29.91330;-3.04540;-12.93720;,
 29.91330;-4.58100;-7.46040;,
 29.91330;-4.58100;72.08680;,
 29.91330;-3.04540;77.56360;,
 -29.91330;-4.58100;-71.43890;,
 -29.91330;-3.04540;-65.96220;,
 -29.91330;-4.58100;-127.42200;,
 29.91330;-4.58100;-71.43890;,
 29.91330;-3.04540;-65.96220;,
 29.91330;-4.58100;-127.42200;,
 -29.91330;-3.04540;99.70890;,
 -29.91330;-4.58100;105.18570;,
 29.91330;-3.04540;99.70890;,
 29.91330;-4.58100;105.18570;,
 -29.91330;-4.58100;128.07890;,
 29.91330;-4.58100;128.07890;,
 -15.95670;18.09780;-137.15961;,
 -15.95670;-1.50980;-137.15961;,
 -14.30690;21.66230;-134.42140;,
 -14.95670;-4.58100;-134.42140;,
 -14.30690;21.66230;-67.33130;,
 -14.95670;-4.58100;-71.43890;,
 -14.30690;21.66230;-10.19890;,
 -14.95670;-3.04540;-65.96220;,
 -14.30690;21.66230;73.45600;,
 -14.95670;-3.04540;-12.93720;,
 -14.30690;21.66230;100.39350;,
 -14.95670;-4.58100;-7.46040;,
 -14.30690;21.66230;133.93829;,
 -14.95670;-4.58100;72.08680;,
 -15.95670;18.09780;138.46741;,
 -14.95670;-3.04540;77.56360;,
 -15.95670;-1.50980;138.46741;,
 -14.95670;-3.04540;99.70890;,
 -14.95670;-4.58100;133.93829;,
 -14.95670;-4.58100;105.18570;,
 15.95670;18.09780;-137.15961;,
 15.95670;-1.50980;-137.15961;,
 14.30690;21.66230;-134.42140;,
 14.95670;-4.58100;-134.42140;,
 14.30690;21.66230;-67.33130;,
 14.95670;-4.58100;-71.43890;,
 14.30690;21.66230;-10.19890;,
 14.95670;-3.04540;-65.96220;,
 14.30690;21.66230;73.45600;,
 14.95670;-3.04540;-12.93720;,
 14.30690;21.66230;100.39350;,
 14.95670;-4.58100;-7.46040;,
 14.30690;21.66230;133.93829;,
 14.95670;-4.58100;72.08680;,
 15.95670;18.09780;138.46741;,
 14.95670;-3.04540;77.56360;,
 15.95670;-1.50980;138.46741;,
 14.95670;-3.04540;99.70890;,
 14.95670;-4.58100;133.93829;,
 14.95670;-4.58100;105.18570;;
 
 196;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;9,8,10,11;,
 4;12,3,2,13;,
 4;12,13,14,15;,
 4;13,2,5,16;,
 4;13,16,17,14;,
 4;18,19,20,21;,
 4;18,21,8,7;,
 4;21,20,22,23;,
 4;21,23,10,8;,
 4;24,25,26,27;,
 4;24,27,1,0;,
 4;27,26,28,29;,
 4;27,29,4,1;,
 4;30,6,9,31;,
 4;30,31,32,33;,
 4;31,9,11,34;,
 4;31,34,35,32;,
 3;36,37,3;,
 4;38,0,3,37;,
 3;39,0,38;,
 3;40,7,41;,
 3;6,42,43;,
 4;6,43,41,7;,
 3;44,45,12;,
 4;44,12,15,46;,
 3;18,47,48;,
 4;36,3,12,45;,
 4;18,48,49,19;,
 4;7,40,47,18;,
 3;50,51,24;,
 4;50,24,0,39;,
 3;30,52,53;,
 4;54,25,24,51;,
 4;30,53,42,6;,
 4;33,55,52,30;,
 4;56,57,15,14;,
 4;56,14,17,58;,
 4;57,59,46,15;,
 4;58,17,16,60;,
 4;59,61,44,46;,
 4;60,16,5,62;,
 4;61,63,45,44;,
 4;62,5,4,64;,
 4;63,65,36,45;,
 4;64,4,29,66;,
 4;65,67,37,36;,
 4;66,29,28,68;,
 4;67,69,38,37;,
 4;68,28,26,70;,
 4;69,71,39,38;,
 4;70,26,25,72;,
 4;71,73,50,39;,
 4;72,25,54,74;,
 4;73,75,51,50;,
 4;74,54,51,75;,
 4;76,20,19,77;,
 4;76,78,22,20;,
 4;77,19,49,79;,
 4;78,80,23,22;,
 4;79,49,48,81;,
 4;80,82,10,23;,
 4;81,48,47,83;,
 4;82,84,11,10;,
 4;83,47,40,85;,
 4;84,86,34,11;,
 4;85,40,41,87;,
 4;86,88,35,34;,
 4;87,41,43,89;,
 4;88,90,32,35;,
 4;89,43,42,91;,
 4;90,92,33,32;,
 4;91,42,53,93;,
 4;92,94,55,33;,
 4;93,53,52,95;,
 4;94,95,52,55;,
 4;56,76,77,57;,
 4;78,76,56,58;,
 4;80,78,58,60;,
 4;82,80,60,62;,
 4;62,64,84,82;,
 4;84,64,66,86;,
 4;86,66,68,88;,
 4;68,70,90,88;,
 4;70,72,92,90;,
 4;74,94,92,72;,
 4;75,95,94,74;,
 4;75,73,93,95;,
 4;91,93,73,71;,
 4;69,89,91,71;,
 4;67,87,89,69;,
 4;67,65,85,87;,
 4;65,63,83,85;,
 4;63,61,81,83;,
 4;61,59,79,81;,
 4;77,79,59,57;,
 4;96,97,98,99;,
 4;99,98,100,101;,
 4;102,103,104,105;,
 4;103,106,107,104;,
 4;108,109,98,97;,
 4;108,110,111,109;,
 4;109,112,100,98;,
 4;109,111,113,112;,
 4;114,115,116,117;,
 4;114,105,104,115;,
 4;115,118,119,116;,
 4;115,104,107,118;,
 4;120,121,122,123;,
 4;120,96,99,121;,
 4;121,124,125,122;,
 4;121,99,101,124;,
 4;126,127,103,102;,
 4;126,128,129,127;,
 4;127,130,106,103;,
 4;127,129,131,130;,
 3;132,97,133;,
 4;134,133,97,96;,
 3;135,134,96;,
 3;136,137,105;,
 3;102,138,139;,
 4;102,105,137,138;,
 3;140,108,141;,
 4;140,142,110,108;,
 3;114,143,144;,
 4;132,141,108,97;,
 4;114,117,145,143;,
 4;105,114,144,136;,
 3;146,120,147;,
 4;146,135,96,120;,
 3;126,148,149;,
 4;150,147,120,123;,
 4;126,102,139,148;,
 4;128,126,149,151;,
 4;152,111,110,153;,
 4;152,154,113,111;,
 4;153,110,142,155;,
 4;154,156,112,113;,
 4;155,142,140,157;,
 4;156,158,100,112;,
 4;157,140,141,159;,
 4;158,160,101,100;,
 4;159,141,132,161;,
 4;160,162,124,101;,
 4;161,132,133,163;,
 4;162,164,125,124;,
 4;163,133,134,165;,
 4;164,166,122,125;,
 4;165,134,135,167;,
 4;166,168,123,122;,
 4;167,135,146,169;,
 4;168,170,150,123;,
 4;169,146,147,171;,
 4;170,171,147,150;,
 4;172,173,117,116;,
 4;172,116,119,174;,
 4;173,175,145,117;,
 4;174,119,118,176;,
 4;175,177,143,145;,
 4;176,118,107,178;,
 4;177,179,144,143;,
 4;178,107,106,180;,
 4;179,181,136,144;,
 4;180,106,130,182;,
 4;181,183,137,136;,
 4;182,130,131,184;,
 4;183,185,138,137;,
 4;184,131,129,186;,
 4;185,187,139,138;,
 4;186,129,128,188;,
 4;187,189,148,139;,
 4;188,128,151,190;,
 4;189,191,149,148;,
 4;190,151,149,191;,
 4;152,153,173,172;,
 4;174,154,152,172;,
 4;176,156,154,174;,
 4;178,158,156,176;,
 4;158,178,180,160;,
 4;180,182,162,160;,
 4;182,184,164,162;,
 4;164,184,186,166;,
 4;166,186,188,168;,
 4;170,168,188,190;,
 4;171,170,190,191;,
 4;171,191,189,169;,
 4;187,167,169,189;,
 4;165,167,187,185;,
 4;163,165,185,183;,
 4;163,183,181,161;,
 4;161,181,179,159;,
 4;159,179,177,157;,
 4;157,177,175,155;,
 4;173,153,155,175;;
 
 MeshMaterialList {
  2;
  196;
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
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
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
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "RemoCon.png";
   }
  }
  Material {
   0.194400;0.194400;0.194400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  149;
  -0.723935;0.658247;-0.206471;,
  0.723935;0.658247;-0.206471;,
  0.698302;0.697414;0.161206;,
  -0.698302;0.697414;0.161206;,
  -0.254788;0.956817;0.139941;,
  0.254788;0.956817;0.139941;,
  0.287059;0.940206;-0.183330;,
  -0.287059;0.940206;-0.183330;,
  -0.887520;0.460770;0.000000;,
  -0.301758;0.953385;0.000000;,
  0.887520;0.460770;0.000000;,
  0.301758;0.953385;0.000000;,
  -0.887520;0.460770;0.000000;,
  -0.301758;0.953385;0.000000;,
  0.887520;0.460770;0.000000;,
  0.301758;0.953385;0.000000;,
  0.765579;-0.611086;-0.201154;,
  -0.765579;-0.611086;-0.201154;,
  -0.923880;-0.382683;0.000000;,
  0.923880;-0.382683;-0.000000;,
  -0.842398;-0.537806;0.033619;,
  -0.842398;-0.537807;-0.033619;,
  -0.348550;-0.932970;0.089886;,
  -0.348549;-0.932971;-0.089886;,
  0.348549;-0.932971;-0.089886;,
  0.348550;-0.932970;0.089886;,
  0.842398;-0.537806;0.033619;,
  0.842398;-0.537807;-0.033619;,
  -0.842398;-0.537806;0.033619;,
  -0.348550;-0.932970;0.089886;,
  -0.337715;-0.923045;-0.184218;,
  0.337715;-0.923045;-0.184218;,
  0.348550;-0.932970;0.089886;,
  -0.271843;-0.958345;0.087615;,
  0.271843;-0.958345;0.087615;,
  0.271842;-0.958345;-0.087615;,
  -0.271842;-0.958345;-0.087615;,
  0.842398;-0.537806;0.033619;,
  -0.842398;-0.537807;-0.033619;,
  -0.271842;-0.958345;-0.087615;,
  -0.271843;-0.958345;0.087615;,
  0.271843;-0.958345;0.087615;,
  0.271842;-0.958345;-0.087615;,
  -0.348549;-0.932971;-0.089886;,
  0.348549;-0.932971;-0.089886;,
  0.303216;-0.943449;0.134032;,
  -0.303216;-0.943449;0.134032;,
  0.842398;-0.537807;-0.033619;,
  -0.176125;0.446721;-0.877166;,
  -0.175143;-0.466417;-0.867053;,
  -0.061392;0.948251;-0.311531;,
  -0.058428;-0.954656;-0.291921;,
  0.000000;1.000000;0.000000;,
  0.000000;-0.995638;0.093299;,
  0.000000;-0.995638;-0.093299;,
  -0.038487;0.974073;0.222938;,
  0.000000;-0.995638;0.093299;,
  -0.075103;0.897276;0.435035;,
  -0.169568;0.000000;0.985519;,
  0.000000;-0.995638;-0.093299;,
  -0.034912;-0.978818;0.201732;,
  0.176125;0.446721;-0.877166;,
  0.175143;-0.466417;-0.867053;,
  0.061392;0.948251;-0.311531;,
  0.058428;-0.954656;-0.291921;,
  0.038487;0.974073;0.222938;,
  0.075103;0.897276;0.435035;,
  0.169568;0.000000;0.985519;,
  0.034912;-0.978818;0.201732;,
  -0.390047;0.000000;-0.920795;,
  -0.334225;0.000000;0.942493;,
  -0.068429;-0.915954;0.395405;,
  -0.136507;-0.917773;0.372907;,
  0.390047;0.000000;-0.920795;,
  0.334225;0.000000;0.942493;,
  0.068429;-0.915954;0.395405;,
  0.136507;-0.917773;0.372907;,
  0.800437;-0.542610;0.254705;,
  -0.800437;-0.542610;0.254705;,
  -0.931091;-0.364788;0.000000;,
  0.931091;-0.364788;-0.000000;,
  0.345839;-0.917541;-0.196248;,
  -0.345839;-0.917541;-0.196248;,
  -0.386963;-0.889739;0.242123;,
  0.386963;-0.889739;0.242123;,
  0.400437;-0.916324;-0.000000;,
  -0.400437;-0.916324;0.000000;,
  -0.958640;0.284623;0.000000;,
  0.958640;0.284623;0.000000;,
  0.958640;0.284623;0.000000;,
  -0.958640;0.284623;0.000000;,
  0.903123;0.427609;-0.038973;,
  0.903122;0.427611;0.038973;,
  0.444490;0.886770;-0.126761;,
  0.444487;0.886771;0.126762;,
  -0.444487;0.886771;0.126762;,
  -0.444490;0.886770;-0.126761;,
  -0.903123;0.427609;-0.038973;,
  -0.903122;0.427611;0.038973;,
  0.903123;0.427609;-0.038973;,
  0.444490;0.886769;-0.126763;,
  0.433638;0.866804;0.246189;,
  -0.433638;0.866804;0.246189;,
  -0.444490;0.886769;-0.126763;,
  0.366569;0.922324;-0.122252;,
  -0.366569;0.922324;-0.122252;,
  -0.366567;0.922325;0.122250;,
  0.366567;0.922325;0.122250;,
  -0.903123;0.427609;-0.038973;,
  0.903123;0.427610;0.038973;,
  0.366569;0.922324;0.122250;,
  0.366570;0.922324;-0.122250;,
  -0.366570;0.922324;-0.122250;,
  -0.366569;0.922324;0.122250;,
  0.444489;0.886770;0.126761;,
  -0.444489;0.886770;0.126761;,
  -0.388961;0.901186;-0.191243;,
  0.388961;0.901186;-0.191243;,
  -0.903123;0.427610;0.038973;,
  0.191439;-0.356705;0.914392;,
  0.189994;0.377551;0.906288;,
  0.083105;-0.913726;0.397742;,
  0.079407;0.922036;0.378871;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.990673;-0.136259;,
  0.000000;0.990674;0.136257;,
  0.000000;0.990674;0.136257;,
  0.054845;-0.951049;-0.304133;,
  0.000000;0.990674;-0.136257;,
  0.156681;-0.455089;-0.876553;,
  0.000000;0.990674;-0.136257;,
  0.154230;0.479415;-0.863929;,
  0.050189;0.958950;-0.279100;,
  -0.191439;-0.356705;0.914392;,
  -0.189994;0.377551;0.906288;,
  -0.083105;-0.913726;0.397742;,
  -0.079407;0.922036;0.378871;,
  -0.054845;-0.951049;-0.304133;,
  -0.156681;-0.455089;-0.876553;,
  -0.154230;0.479415;-0.863929;,
  -0.050189;0.958950;-0.279100;,
  0.401695;0.000000;0.915773;,
  0.375128;0.384921;0.843276;,
  0.311526;-0.461849;-0.830450;,
  0.305659;0.478760;-0.823020;,
  -0.375128;0.384921;0.843276;,
  -0.401695;0.000000;0.915773;,
  -0.311526;-0.461849;-0.830450;,
  -0.305659;0.478760;-0.823020;;
  196;
  4;20,12,8,21;,
  4;12,13,9,8;,
  4;26,27,10,14;,
  4;14,10,11,15;,
  4;28,21,8,8;,
  4;28,8,0,17;,
  4;8,8,9,9;,
  4;8,9,7,0;,
  4;37,16,1,10;,
  4;37,10,10,27;,
  4;10,1,6,11;,
  4;10,11,11,10;,
  4;38,18,3,8;,
  4;38,8,12,20;,
  4;8,3,4,9;,
  4;8,9,13,12;,
  4;47,26,14,10;,
  4;47,10,2,19;,
  4;10,14,15,11;,
  4;10,11,5,2;,
  3;36,23,21;,
  4;22,20,21,23;,
  3;40,20,22;,
  3;35,27,24;,
  3;26,41,25;,
  4;26,25,24,27;,
  3;29,33,28;,
  4;29,28,17,30;,
  3;37,34,32;,
  4;36,21,28,33;,
  4;37,32,31,16;,
  4;27,35,34,37;,
  3;39,43,38;,
  4;39,38,20,40;,
  3;47,44,42;,
  4;46,18,38,43;,
  4;47,42,41,26;,
  4;19,45,44,47;,
  4;48,49,69,69;,
  4;48,0,7,50;,
  4;49,51,30,17;,
  4;50,7,9,52;,
  4;51,53,29,30;,
  4;52,9,9,52;,
  4;53,53,33,29;,
  4;52,9,13,52;,
  4;53,54,36,33;,
  4;52,13,9,52;,
  4;54,54,23,36;,
  4;52,9,4,55;,
  4;54,56,22,23;,
  4;55,4,3,57;,
  4;56,56,40,22;,
  4;58,70,70,58;,
  4;56,59,39,40;,
  4;71,72,46,60;,
  4;59,59,43,39;,
  4;60,46,43,59;,
  4;61,73,73,62;,
  4;61,63,6,1;,
  4;62,16,31,64;,
  4;63,52,11,6;,
  4;64,31,32,53;,
  4;52,52,11,11;,
  4;53,32,34,53;,
  4;52,52,15,11;,
  4;53,34,35,54;,
  4;52,52,11,15;,
  4;54,35,24,54;,
  4;52,65,5,11;,
  4;54,24,25,56;,
  4;65,66,2,5;,
  4;56,25,41,56;,
  4;67,67,74,74;,
  4;56,41,42,59;,
  4;75,68,45,76;,
  4;59,42,44,59;,
  4;68,59,44,45;,
  4;48,61,62,49;,
  4;63,61,48,50;,
  4;52,63,50,52;,
  4;52,52,52,52;,
  4;52,52,52,52;,
  4;52,52,52,52;,
  4;52,52,55,65;,
  4;55,57,66,65;,
  4;58,58,67,67;,
  4;60,68,75,71;,
  4;59,59,68,60;,
  4;59,59,59,59;,
  4;56,59,59,56;,
  4;56,56,56,56;,
  4;54,54,56,56;,
  4;54,54,54,54;,
  4;54,53,53,54;,
  4;53,53,53,53;,
  4;53,51,64,53;,
  4;62,64,51,49;,
  4;91,92,80,80;,
  4;80,80,85,85;,
  4;97,79,79,98;,
  4;79,86,86,79;,
  4;99,80,80,92;,
  4;99,88,77,80;,
  4;80,85,85,80;,
  4;80,77,84,85;,
  4;108,79,78,87;,
  4;108,98,79,79;,
  4;79,86,83,78;,
  4;79,79,86,86;,
  4;109,80,80,89;,
  4;109,91,80,80;,
  4;80,85,81,80;,
  4;80,80,85,85;,
  4;118,79,79,97;,
  4;118,90,79,79;,
  4;79,86,86,79;,
  4;79,79,82,86;,
  3;107,92,94;,
  4;93,94,92,91;,
  3;111,93,91;,
  3;106,95,98;,
  3;97,96,112;,
  4;97,98,95,96;,
  3;100,99,104;,
  4;100,101,88,99;,
  3;108,103,105;,
  4;107,104,99,92;,
  4;108,87,102,103;,
  4;98,108,105,106;,
  3;110,109,114;,
  4;110,111,91,109;,
  3;118,113,115;,
  4;117,114,109,89;,
  4;118,97,112,113;,
  4;90,118,115,116;,
  4;119,141,142,120;,
  4;119,121,84,77;,
  4;120,142,101,122;,
  4;121,123,85,84;,
  4;122,101,100,124;,
  4;123,123,85,85;,
  4;124,100,104,124;,
  4;123,123,85,85;,
  4;124,104,107,125;,
  4;123,123,85,85;,
  4;125,107,94,126;,
  4;123,127,81,85;,
  4;126,94,93,128;,
  4;127,129,143,81;,
  4;128,93,111,130;,
  4;129,131,144,143;,
  4;130,111,110,125;,
  4;131,132,117,144;,
  4;125,110,114,126;,
  4;132,126,114,117;,
  4;133,134,145,146;,
  4;133,78,83,135;,
  4;134,136,102,145;,
  4;135,83,86,123;,
  4;136,124,103,102;,
  4;123,86,86,123;,
  4;124,124,105,103;,
  4;123,86,86,123;,
  4;124,125,106,105;,
  4;123,86,86,123;,
  4;125,126,95,106;,
  4;123,86,82,137;,
  4;126,128,96,95;,
  4;137,82,147,138;,
  4;128,130,112,96;,
  4;138,147,148,139;,
  4;130,125,113,112;,
  4;139,148,116,140;,
  4;125,126,115,113;,
  4;140,116,115,126;,
  4;119,120,134,133;,
  4;135,121,119,133;,
  4;123,123,121,135;,
  4;123,123,123,123;,
  4;123,123,123,123;,
  4;123,123,123,123;,
  4;123,137,127,123;,
  4;127,137,138,129;,
  4;129,138,139,131;,
  4;132,131,139,140;,
  4;126,132,140,126;,
  4;126,126,125,125;,
  4;130,130,125,125;,
  4;128,130,130,128;,
  4;126,128,128,126;,
  4;126,126,125,125;,
  4;125,125,124,124;,
  4;124,124,124,124;,
  4;124,124,136,122;,
  4;134,120,122,136;;
 }
}
