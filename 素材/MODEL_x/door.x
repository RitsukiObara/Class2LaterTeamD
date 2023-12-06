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
 197;
 148.27361;152.85831;-147.53081;,
 204.39380;152.85831;-146.66251;,
 204.39380;103.55830;-146.66251;,
 148.27361;103.55830;-147.53081;,
 204.39380;54.25830;-146.66251;,
 148.27361;54.25830;-147.53081;,
 204.39380;4.95830;-146.66251;,
 148.27361;4.95830;-147.53081;,
 204.03931;152.85831;-6.23430;,
 204.03931;103.55830;-6.23430;,
 204.03931;54.25830;-6.23430;,
 204.03931;4.95830;-6.23430;,
 147.91910;152.85831;-7.10250;,
 147.91910;103.55830;-7.10250;,
 147.91910;54.25830;-7.10250;,
 147.91910;4.95830;-7.10250;,
 197.21719;152.85831;-144.49471;,
 196.86270;152.85831;-6.34520;,
 197.21719;103.55830;-144.49471;,
 196.86270;103.55830;-6.34520;,
 197.21719;54.25830;-144.49471;,
 196.86270;54.25830;-6.34520;,
 197.21719;4.95830;-144.49471;,
 196.86270;4.95830;-6.34520;,
 197.64270;103.55830;-146.76691;,
 197.28819;103.55830;-6.33870;,
 197.64270;54.25830;-146.76691;,
 197.28819;54.25830;-6.33870;,
 0.40920;3.49640;-147.40160;,
 68.71150;3.49640;-147.40160;,
 68.71150;0.44560;-147.40160;,
 0.40920;0.44560;-147.40160;,
 137.01370;3.49640;-147.40160;,
 137.01370;0.44560;-147.40160;,
 205.31590;3.49640;-147.40160;,
 205.31590;0.44560;-147.40160;,
 205.31590;3.49640;-99.00160;,
 205.31590;0.44560;-99.00160;,
 205.31590;3.49640;-50.60160;,
 205.31590;0.44560;-50.60160;,
 205.31590;3.49640;-2.20160;,
 205.31590;0.44560;-2.20160;,
 137.01370;3.49640;-2.20160;,
 137.01370;0.44560;-2.20160;,
 68.71150;3.49640;-2.20160;,
 68.71150;0.44560;-2.20160;,
 0.40920;3.49640;-2.20160;,
 0.40920;0.44560;-2.20160;,
 0.40920;3.49640;-50.60160;,
 0.40920;0.44560;-50.60160;,
 0.40920;3.49640;-99.00160;,
 0.40920;0.44560;-99.00160;,
 68.71150;3.49640;-50.60160;,
 137.01370;3.49640;-50.60160;,
 68.71150;3.49640;-99.00160;,
 137.01370;3.49640;-99.00160;,
 68.71150;0.44560;-50.60160;,
 137.01370;0.44560;-50.60160;,
 68.71150;0.44560;-99.00160;,
 137.01370;0.44560;-99.00160;,
 -2.12340;22.11740;0.35770;,
 38.85660;22.11740;0.35770;,
 38.85660;1.21740;0.35770;,
 -2.12340;1.21740;0.35770;,
 79.83660;22.11740;0.35770;,
 79.83660;1.21740;0.35770;,
 120.81660;22.11740;0.35770;,
 120.81660;1.21740;0.35770;,
 161.79660;22.11740;0.35770;,
 161.79660;1.21740;0.35770;,
 202.77660;22.11740;0.35770;,
 202.77660;1.21740;0.35770;,
 202.77660;22.11740;394.15771;,
 202.77660;1.21740;394.15771;,
 161.79660;22.11740;394.15771;,
 161.79660;1.21740;394.15771;,
 120.81660;22.11740;394.15771;,
 120.81660;1.21740;394.15771;,
 79.83660;22.11740;394.15771;,
 79.83660;1.21740;394.15771;,
 38.85660;22.11740;394.15771;,
 38.85660;1.21740;394.15771;,
 -2.12340;22.11740;394.15771;,
 -2.12340;1.21740;394.15771;,
 202.61920;306.42871;15.55350;,
 205.48540;306.42871;-148.18530;,
 205.48540;0.59360;-148.18530;,
 202.61920;0.59360;15.55350;,
 218.88229;306.42871;-148.16220;,
 218.88229;0.59360;-148.16220;,
 216.01610;306.42871;15.57630;,
 216.01610;0.59360;15.57630;,
 203.55060;306.67700;36.35740;,
 216.38049;306.37210;36.82710;,
 215.05090;0.59360;36.26300;,
 203.55060;0.47110;36.35740;,
 219.12131;300.72141;394.06860;,
 219.12131;1.11510;394.06860;,
 203.02130;300.72141;394.06860;,
 203.02130;1.11510;394.06860;,
 202.61920;306.42871;15.55350;,
 216.01610;306.42871;15.57630;,
 216.01610;0.59360;15.57630;,
 202.61920;0.59360;15.55350;,
 216.38049;306.37210;36.82710;,
 215.05090;0.59360;36.26300;,
 203.55060;306.67700;36.35740;,
 203.55060;0.47110;36.35740;,
 99.96162;300.75293;-17.81160;,
 116.68690;300.72141;-16.99318;,
 116.68690;1.11510;-16.99318;,
 100.58689;1.11510;-16.99318;,
 115.43040;299.54559;7.14498;,
 114.10079;0.59360;6.58089;,
 101.11619;299.85049;6.67525;,
 101.11619;0.47110;6.67525;,
 -102.31441;298.12000;-15.44180;,
 99.96162;300.75293;-17.81160;,
 100.58689;1.11510;-16.99318;,
 -102.31441;2.04429;-14.41512;,
 101.11619;299.85049;6.67525;,
 101.11619;0.47110;6.67525;,
 -102.31441;298.12000;6.45827;,
 -103.73174;0.59360;6.58089;,
 -117.87089;300.75293;-16.78493;,
 -102.31441;298.12000;-15.44180;,
 -102.31441;2.04429;-14.41512;,
 -117.24561;1.11510;-15.96651;,
 -102.31441;298.12000;6.45827;,
 -103.73174;0.59360;6.58089;,
 -116.71631;299.85049;7.70190;,
 -116.71631;0.47110;7.70190;,
 -117.87089;300.75293;-16.78493;,
 -116.71631;299.85049;7.70190;,
 -116.71631;0.47110;7.70190;,
 -117.24561;1.11510;-15.96651;,
 11.35149;227.49889;-13.69002;,
 67.05149;227.49889;-13.69002;,
 67.05149;171.04889;-13.69002;,
 11.35149;171.04889;-13.69002;,
 -44.34851;171.04889;-13.69002;,
 11.35149;114.59889;-13.69002;,
 -44.34851;114.59889;-13.69002;,
 67.05149;114.59889;-13.69002;,
 67.05149;58.14889;-13.69002;,
 11.35149;58.14889;-13.69002;,
 -44.34851;58.14889;-13.69002;,
 11.35149;1.69889;-13.69002;,
 -44.34851;1.69889;-13.69002;,
 67.05149;227.49889;8.20998;,
 67.05149;171.04889;8.20998;,
 67.05149;114.59889;8.20998;,
 67.05149;58.14889;8.20998;,
 67.05149;1.69889;8.20998;,
 67.05149;1.69889;-13.69002;,
 11.35149;227.49889;8.20998;,
 11.35149;171.04889;8.20998;,
 -44.34851;227.49889;8.20998;,
 -44.34851;171.04889;8.20998;,
 11.35149;114.59889;8.20998;,
 -44.34851;114.59889;8.20998;,
 11.35149;58.14889;8.20998;,
 -44.34851;58.14889;8.20998;,
 11.35149;1.69889;8.20998;,
 -44.34851;1.69889;8.20998;,
 -44.34851;227.49889;-13.69002;,
 11.35149;227.49889;-1.68827;,
 -44.34851;227.49889;-1.68827;,
 11.35149;171.04889;-1.68827;,
 -44.34851;171.04889;-1.68827;,
 67.05149;171.04889;-1.68827;,
 67.05149;114.59889;-1.68827;,
 11.35149;114.59889;-1.68827;,
 -44.34851;114.59889;-1.68827;,
 11.35149;58.14889;-1.68827;,
 -44.34851;58.14889;-1.68827;,
 67.05149;58.14889;-1.68827;,
 67.05149;1.69889;-1.68827;,
 11.35149;1.69889;-1.68827;,
 -28.00425;122.88987;-19.73840;,
 -22.40782;124.73006;-19.29979;,
 -22.40782;123.57291;1.94725;,
 -28.00425;121.73277;1.50860;,
 -20.08970;129.17264;-18.24083;,
 -20.08970;128.01556;3.00621;,
 -22.40782;133.61528;-17.18185;,
 -22.40782;132.45818;4.06516;,
 -28.00425;135.45543;-16.74323;,
 -28.00425;134.29834;4.50379;,
 -33.60069;133.61528;-17.18185;,
 -33.60069;132.45818;4.06515;,
 -35.91877;129.17264;-18.24083;,
 -35.91877;128.01556;3.00621;,
 -33.60069;124.73006;-19.29979;,
 -33.60069;123.57293;1.94726;,
 -28.00425;129.17264;-18.24083;,
 -28.00425;128.01556;3.00621;;
 
 183;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;1,8,9,2;,
 4;2,9,10,4;,
 4;4,10,11,6;,
 4;8,12,13,9;,
 4;9,13,14,10;,
 4;10,14,15,11;,
 4;8,1,0,12;,
 4;15,7,6,11;,
 4;16,17,12,0;,
 4;18,16,0,3;,
 4;19,18,3,13;,
 4;17,19,13,12;,
 4;17,16,18,19;,
 4;20,21,14,5;,
 4;22,20,5,7;,
 4;23,22,7,15;,
 4;21,23,15,14;,
 4;21,20,22,23;,
 4;24,25,13,3;,
 4;26,24,3,5;,
 4;27,26,5,14;,
 4;25,27,14,13;,
 4;25,24,26,27;,
 4;28,29,30,31;,
 4;29,32,33,30;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 4;50,28,31,51;,
 4;46,44,52,48;,
 4;44,42,53,52;,
 4;42,40,38,53;,
 4;48,52,54,50;,
 4;52,53,55,54;,
 4;53,38,36,55;,
 4;50,54,29,28;,
 4;54,55,32,29;,
 4;55,36,34,32;,
 4;49,56,45,47;,
 4;56,57,43,45;,
 4;57,39,41,43;,
 4;51,58,56,49;,
 4;58,59,57,56;,
 4;59,37,39,57;,
 4;31,30,58,51;,
 4;30,33,59,58;,
 4;33,35,37,59;,
 4;60,61,62,63;,
 4;61,64,65,62;,
 4;64,66,67,65;,
 4;66,68,69,67;,
 4;68,70,71,69;,
 4;70,72,73,71;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 4;82,60,63,83;,
 4;82,80,61,60;,
 4;80,78,64,61;,
 4;78,76,66,64;,
 4;76,74,68,66;,
 4;74,72,70,68;,
 4;63,62,81,83;,
 4;62,65,79,81;,
 4;65,67,77,79;,
 4;67,69,75,77;,
 4;69,71,73,75;,
 4;84,85,86,87;,
 4;85,88,89,86;,
 4;88,90,91,89;,
 4;90,84,87,91;,
 4;90,88,85,84;,
 4;87,86,89,91;,
 4;92,93,94,95;,
 4;93,96,97,94;,
 4;96,98,99,97;,
 4;98,92,95,99;,
 4;98,96,93,92;,
 4;95,94,97,99;,
 4;100,101,102,103;,
 4;101,104,105,102;,
 4;104,106,107,105;,
 4;106,100,103,107;,
 4;106,104,101,100;,
 4;103,102,105,107;,
 4;108,109,110,111;,
 4;109,112,113,110;,
 4;112,114,115,113;,
 4;114,108,111,115;,
 4;114,112,109,108;,
 4;111,110,113,115;,
 4;116,117,118,119;,
 4;117,120,121,118;,
 4;120,122,123,121;,
 4;122,116,119,123;,
 4;122,120,117,116;,
 4;119,118,121,123;,
 4;124,125,126,127;,
 4;125,128,129,126;,
 4;128,130,131,129;,
 4;130,124,127,131;,
 4;130,128,125,124;,
 4;127,126,129,131;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;140,139,141,142;,
 4;141,143,144,145;,
 4;146,145,147,148;,
 4;137,149,150,138;,
 4;138,150,151,143;,
 4;143,151,152,144;,
 4;144,152,153,154;,
 4;149,155,156,150;,
 4;155,157,158,156;,
 4;150,156,159,151;,
 4;156,158,160,159;,
 4;151,159,161,152;,
 4;159,160,162,161;,
 4;152,161,163,153;,
 4;161,162,164,163;,
 4;157,165,140,158;,
 4;158,140,142,160;,
 4;160,142,146,162;,
 4;162,146,148,164;,
 4;157,155,136,165;,
 4;155,149,137,136;,
 4;148,147,163,164;,
 4;147,154,153,163;,
 4;166,167,165,136;,
 4;168,166,136,139;,
 4;169,168,139,140;,
 4;167,169,140,165;,
 4;167,166,168,169;,
 4;170,168,139,138;,
 4;171,170,138,143;,
 4;172,171,143,141;,
 4;168,172,141,139;,
 4;168,170,171,172;,
 4;172,173,142,141;,
 4;174,172,141,145;,
 4;175,174,145,146;,
 4;173,175,146,142;,
 4;173,172,174,175;,
 4;176,174,145,144;,
 4;177,176,144,154;,
 4;178,177,154,147;,
 4;174,178,147,145;,
 4;174,176,177,178;,
 4;179,180,181,182;,
 4;180,183,184,181;,
 4;183,185,186,184;,
 4;185,187,188,186;,
 4;187,189,190,188;,
 4;189,191,192,190;,
 4;191,193,194,192;,
 4;193,179,182,194;,
 3;195,180,179;,
 3;195,183,180;,
 3;195,185,183;,
 3;195,187,185;,
 3;195,189,187;,
 3;195,191,189;,
 3;195,193,191;,
 3;195,179,193;,
 3;196,182,181;,
 3;196,181,184;,
 3;196,184,186;,
 3;196,186,188;,
 3;196,188,190;,
 3;196,190,192;,
 3;196,192,194;,
 3;196,194,182;;
 
 MeshMaterialList {
  11;
  183;
  1,
  1,
  1,
  4,
  4,
  4,
  1,
  1,
  1,
  1,
  0,
  10,
  4,
  4,
  4,
  4,
  0,
  4,
  4,
  4,
  4,
  0,
  4,
  4,
  4,
  4,
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
  5,
  5,
  5,
  5,
  5,
  5,
  7,
  9,
  7,
  9,
  9,
  9,
  5,
  6,
  6,
  6,
  6,
  6,
  5,
  6,
  6,
  6,
  6,
  6,
  9,
  7,
  9,
  7,
  9,
  9,
  5,
  6,
  6,
  6,
  6,
  6,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8;;
  Material {
   0.800000;0.517600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.520800;0.094400;0.094400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.398400;0.398400;0.398400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.784000;0.401600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.636800;0.392000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.248000;0.257600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.558400;0.106400;0.106400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
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
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  97;
  -0.015469;0.000000;0.999880;,
  -0.015469;0.000000;0.999880;,
  0.015470;0.000000;-0.999880;,
  0.015470;0.000000;-0.999880;,
  0.999997;0.000000;0.002524;,
  0.999997;0.000000;0.002524;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.061914;0.000000;0.998082;,
  -0.015471;0.000000;0.999880;,
  -0.038703;0.000000;0.999251;,
  0.015471;0.000000;-0.999880;,
  0.015470;0.000000;-0.999880;,
  -0.999997;0.000000;-0.002566;,
  0.015469;0.000000;-0.999880;,
  -0.999997;0.000000;-0.002524;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.999847;0.000000;-0.017502;,
  0.001724;0.000000;-0.999999;,
  0.999847;0.000000;0.017502;,
  -0.001702;0.000000;0.999999;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.014182;0.000940;-0.999899;,
  0.999952;-0.002167;-0.009558;,
  0.000000;0.000000;1.000000;,
  -0.999999;0.000000;-0.001480;,
  0.011573;0.999801;0.016247;,
  0.005333;-0.999985;0.001637;,
  0.001702;0.000000;-0.999999;,
  0.999889;-0.002216;0.014738;,
  -0.014182;-0.000940;0.999899;,
  -0.998999;0.000000;0.044725;,
  0.011849;0.999918;-0.004839;,
  0.005300;-0.999981;-0.003181;,
  0.024442;-0.001313;-0.999700;,
  0.996752;-0.002314;0.080498;,
  -0.012759;-0.000960;0.999918;,
  -0.999397;-0.000978;0.034695;,
  0.009862;0.999016;0.043248;,
  0.004616;-0.999683;-0.024761;,
  -0.012194;-0.003113;-0.999921;,
  0.999397;0.000978;-0.034695;,
  -0.000765;0.000209;1.000000;,
  -0.999435;0.002364;-0.033532;,
  -0.010780;0.999769;0.018618;,
  -0.002744;-0.998842;-0.048039;,
  0.094578;-0.002996;-0.995513;,
  0.999435;-0.002364;0.033532;,
  0.086023;0.000000;0.996293;,
  0.999397;0.000978;-0.034695;,
  -0.999397;-0.000978;0.034695;,
  0.141906;0.989777;0.014298;,
  0.037870;-0.998233;-0.045786;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;0.231869;-0.972747;,
  -0.000000;-0.998520;-0.054380;,
  0.650168;-0.758666;-0.041317;,
  1.000000;-0.000001;-0.000000;,
  0.650168;0.758666;0.041316;,
  0.000000;0.998520;0.054379;,
  -0.650171;0.758664;0.041316;,
  -1.000000;-0.000001;-0.000000;,
  -0.650171;-0.758664;-0.041317;,
  -0.000000;-0.231867;0.972747;,
  -0.000002;0.231868;-0.972747;,
  -0.000000;0.231865;-0.972748;,
  0.000000;0.231870;-0.972747;,
  -0.000000;0.231870;-0.972747;,
  -0.000000;0.231870;-0.972747;,
  0.000000;0.231870;-0.972747;,
  0.000000;0.231870;-0.972747;,
  0.000002;0.231868;-0.972747;,
  0.000000;-0.231871;0.972747;,
  -0.000002;-0.231869;0.972747;,
  0.000000;-0.231866;0.972748;,
  0.000001;-0.231866;0.972748;,
  -0.000001;-0.231867;0.972748;,
  -0.000001;-0.231866;0.972748;,
  0.000000;-0.231865;0.972748;,
  0.000002;-0.231868;0.972747;;
  183;
  4;2,2,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,5,5;,
  4;5,5,5,5;,
  4;0,0,1,1;,
  4;1,1,1,1;,
  4;1,1,0,0;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;8,8,8,10;,
  4;7,7,7,7;,
  4;11,11,12,11;,
  4;13,13,13,13;,
  4;6,6,6,6;,
  4;8,8,10,8;,
  4;7,7,7,7;,
  4;11,11,11,12;,
  4;13,13,13,13;,
  4;6,6,6,6;,
  4;9,9,10,10;,
  4;7,7,7,7;,
  4;14,14,12,12;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;19,19,19,19;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;24,24,24,24;,
  4;24,24,24,24;,
  4;24,24,24,24;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;47,47,47,47;,
  4;48,48,48,48;,
  4;49,49,49,49;,
  4;50,50,50,50;,
  4;51,51,51,51;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  4;54,54,54,54;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;61,61,61,61;,
  4;66,66,66,66;,
  4;66,66,66,66;,
  4;66,66,66,66;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;67,67,67,67;,
  4;67,67,67,67;,
  4;67,67,67,67;,
  4;68,68,68,68;,
  4;68,68,68,68;,
  4;68,68,68,68;,
  4;68,68,68,68;,
  4;68,68,68,68;,
  4;68,68,68,68;,
  4;68,68,68,68;,
  4;68,68,68,68;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;70,70,70,70;,
  4;70,70,70,70;,
  4;69,69,69,69;,
  4;69,69,69,69;,
  4;69,69,69,69;,
  4;65,65,65,65;,
  4;70,70,70,70;,
  4;67,67,67,67;,
  4;66,66,66,66;,
  4;69,69,69,69;,
  4;65,65,65,65;,
  4;70,70,70,70;,
  4;67,67,67,67;,
  4;66,66,66,66;,
  4;69,69,69,69;,
  4;65,65,65,65;,
  4;70,70,70,70;,
  4;67,67,67,67;,
  4;66,66,66,66;,
  4;69,69,69,69;,
  4;65,65,65,65;,
  4;70,70,70,70;,
  4;67,67,67,67;,
  4;66,66,66,66;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,72,72,79;,
  3;71,81,82;,
  3;71,83,81;,
  3;71,84,83;,
  3;71,85,84;,
  3;71,86,85;,
  3;71,87,86;,
  3;71,88,87;,
  3;71,82,88;,
  3;80,89,90;,
  3;80,90,91;,
  3;80,91,92;,
  3;80,92,93;,
  3;80,93,94;,
  3;80,94,95;,
  3;80,95,96;,
  3;80,96,89;;
 }
}
