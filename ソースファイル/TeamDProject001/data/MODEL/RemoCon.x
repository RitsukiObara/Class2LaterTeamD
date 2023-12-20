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
 240;
 -26.01135;1.63030;51.93361;,
 -26.01135;12.03751;51.93361;,
 -26.01135;12.03751;-6.84922;,
 -26.01135;1.63030;-6.84922;,
 -23.32206;13.92944;50.98711;,
 -23.32206;13.92944;-6.84922;,
 26.01135;1.63030;51.93361;,
 26.01135;1.63030;-6.84922;,
 26.01135;12.03751;-6.84922;,
 26.01135;12.03751;51.93361;,
 23.32206;13.92944;-6.84922;,
 23.32206;13.92944;50.98711;,
 -26.01135;1.63030;-47.29572;,
 -26.01135;12.03751;-47.29572;,
 -26.01135;12.03751;-89.78706;,
 -26.01135;1.63030;-89.78706;,
 -23.32206;13.92944;-46.34896;,
 -23.32206;13.92944;-87.89404;,
 26.01135;1.63030;-47.29572;,
 26.01135;1.63030;-89.78706;,
 26.01135;12.03751;-89.78706;,
 26.01135;12.03751;-47.29572;,
 23.32206;13.92944;-87.89404;,
 23.32206;13.92944;-46.34896;,
 -26.01135;1.63030;71.03072;,
 -26.01135;1.63030;91.88297;,
 -26.01135;12.03751;91.88297;,
 -26.01135;12.03751;71.03072;,
 -23.32206;13.92944;88.75175;,
 -23.32206;13.92944;69.61069;,
 26.01135;1.63030;71.03072;,
 26.01135;12.03751;71.03072;,
 26.01135;12.03751;91.88297;,
 26.01135;1.63030;91.88297;,
 23.32206;13.92944;69.61069;,
 23.32206;13.92944;88.75175;,
 -24.38123;0.81524;-8.74267;,
 -24.38123;0.00017;-4.95614;,
 -24.38123;0.00017;50.04051;,
 -24.38123;0.81524;53.82678;,
 24.38123;0.81524;-8.74267;,
 24.38123;0.00017;-4.95614;,
 24.38123;0.81524;53.82678;,
 24.38123;0.00017;50.04051;,
 -24.38123;0.00017;-49.18895;,
 -24.38123;0.81524;-45.40224;,
 -24.38123;0.00017;-87.89404;,
 24.38123;0.81524;-45.40224;,
 24.38123;0.00017;-49.18895;,
 24.38123;0.00017;-87.89404;,
 -24.38123;0.81524;69.13754;,
 -24.38123;0.00017;72.92378;,
 24.38123;0.00017;72.92378;,
 24.38123;0.81524;69.13754;,
 -24.38123;0.00017;88.75175;,
 24.38123;0.00017;88.75175;,
 -13.00572;12.03751;-94.62614;,
 -13.00572;1.63030;-94.62614;,
 -26.01135;1.63030;-89.78706;,
 -26.01135;12.03751;-89.78706;,
 -11.66103;13.92944;-92.73277;,
 -12.19066;0.00017;-92.73277;,
 -11.66103;13.92944;-92.73277;,
 -23.32206;13.92944;-87.89404;,
 -23.32206;13.92944;-46.34896;,
 -11.66103;13.92944;-46.34896;,
 -12.19066;0.00017;-49.18895;,
 -23.32206;13.92944;-6.84922;,
 -11.66103;13.92944;-6.84922;,
 -12.19066;0.81524;-45.40224;,
 -23.32206;13.92944;50.98711;,
 -11.66103;13.92944;50.98711;,
 -12.19066;0.81524;-8.74267;,
 -23.32206;13.92944;69.61069;,
 -11.66103;13.92944;69.61069;,
 -12.19066;0.00017;-4.95614;,
 -23.32206;13.92944;88.75175;,
 -11.66103;13.92944;92.80270;,
 -12.19066;0.00017;50.04051;,
 -11.66103;13.92944;92.80270;,
 -26.01135;12.03751;91.88297;,
 -13.00572;12.03751;95.93394;,
 -12.19066;0.81524;53.82678;,
 -26.01135;1.63030;91.88297;,
 -13.00572;1.63030;95.93394;,
 -12.19066;0.81524;69.13754;,
 -12.19066;0.00017;92.80270;,
 -12.19066;0.00017;72.92378;,
 13.00572;12.03751;-94.62614;,
 26.01135;12.03751;-89.78706;,
 26.01135;1.63030;-89.78706;,
 13.00572;1.63030;-94.62614;,
 11.66103;13.92944;-92.73277;,
 12.19066;0.00017;-92.73277;,
 11.66103;13.92944;-92.73277;,
 11.66103;13.92944;-46.34896;,
 23.32206;13.92944;-46.34896;,
 23.32206;13.92944;-87.89404;,
 12.19066;0.00017;-49.18895;,
 11.66103;13.92944;-6.84922;,
 23.32206;13.92944;-6.84922;,
 12.19066;0.81524;-45.40224;,
 11.66103;13.92944;50.98711;,
 23.32206;13.92944;50.98711;,
 12.19066;0.81524;-8.74267;,
 11.66103;13.92944;69.61069;,
 23.32206;13.92944;69.61069;,
 12.19066;0.00017;-4.95614;,
 11.66103;13.92944;92.80270;,
 23.32206;13.92944;88.75175;,
 12.19066;0.00017;50.04051;,
 11.66103;13.92944;92.80270;,
 13.00572;12.03751;95.93394;,
 26.01135;12.03751;91.88297;,
 12.19066;0.81524;53.82678;,
 13.00572;1.63030;95.93394;,
 26.01135;1.63030;91.88297;,
 12.19066;0.81524;69.13754;,
 12.19066;0.00017;92.80270;,
 12.19066;0.00017;72.92378;,
 -28.73982;-1.22690;53.49117;,
 -28.73982;-1.22690;-7.07726;,
 -28.73982;14.75453;-7.07726;,
 -28.73982;14.75453;53.49117;,
 -25.76843;17.65982;-7.07726;,
 -25.76843;17.65982;52.51604;,
 28.73982;-1.22690;53.49117;,
 28.73982;14.75453;53.49117;,
 28.73982;14.75453;-7.07726;,
 28.73982;-1.22690;-7.07726;,
 25.76843;17.65982;52.51604;,
 25.76843;17.65982;-7.07726;,
 -28.73982;-1.22690;-48.75222;,
 -28.73982;14.75453;-48.75222;,
 -28.73982;-1.22690;-92.53432;,
 -28.73982;14.75453;-92.53432;,
 -25.76843;17.65982;-47.77671;,
 -25.76843;17.65982;-90.58342;,
 28.73982;-1.22690;-48.75222;,
 28.73982;14.75453;-48.75222;,
 28.73982;14.75453;-92.53432;,
 28.73982;-1.22690;-92.53432;,
 25.76843;17.65982;-47.77671;,
 25.76843;17.65982;-90.58342;,
 -28.73982;-1.22690;73.16857;,
 -28.73982;14.75453;73.16857;,
 -28.73982;14.75453;94.65405;,
 -28.73982;-1.22690;94.65405;,
 -25.76843;17.65982;71.70530;,
 -25.76843;17.65982;91.42770;,
 28.73982;-1.22690;73.16857;,
 28.73982;14.75453;73.16857;,
 28.73982;-1.22690;94.65405;,
 28.73982;14.75453;94.65405;,
 25.76843;17.65982;71.70530;,
 25.76843;17.65982;91.42770;,
 -26.93871;-2.47851;-9.02797;,
 -26.93871;-3.73012;-5.12656;,
 -26.93871;-3.73012;51.54060;,
 -26.93871;-2.47851;55.44217;,
 26.93871;-2.47851;-9.02797;,
 26.93871;-3.73012;-5.12656;,
 26.93871;-3.73012;51.54060;,
 26.93871;-2.47851;55.44217;,
 -26.93871;-3.73012;-50.70270;,
 -26.93871;-2.47851;-46.80140;,
 -26.93871;-3.73012;-90.58342;,
 26.93871;-3.73012;-50.70270;,
 26.93871;-2.47851;-46.80140;,
 26.93871;-3.73012;-90.58342;,
 -26.93871;-2.47851;71.21763;,
 -26.93871;-3.73012;75.11913;,
 26.93871;-2.47851;71.21763;,
 26.93871;-3.73012;75.11913;,
 -26.93871;-3.73012;91.42770;,
 26.93871;-3.73012;91.42770;,
 -14.36996;14.75453;-97.52036;,
 -28.73982;14.75453;-92.53432;,
 -28.73982;-1.22690;-92.53432;,
 -14.36996;-1.22690;-97.52036;,
 -12.88422;17.65982;-95.56990;,
 -13.46940;-3.73012;-95.56990;,
 -12.88422;17.65982;-95.56990;,
 -12.88422;17.65982;-47.77671;,
 -25.76843;17.65982;-47.77671;,
 -25.76843;17.65982;-90.58342;,
 -13.46940;-3.73012;-50.70270;,
 -12.88422;17.65982;-7.07726;,
 -25.76843;17.65982;-7.07726;,
 -13.46940;-2.47851;-46.80140;,
 -12.88422;17.65982;52.51604;,
 -25.76843;17.65982;52.51604;,
 -13.46940;-2.47851;-9.02797;,
 -12.88422;17.65982;71.70530;,
 -25.76843;17.65982;71.70530;,
 -13.46940;-3.73012;-5.12656;,
 -12.88422;17.65982;95.60177;,
 -25.76843;17.65982;91.42770;,
 -13.46940;-3.73012;51.54060;,
 -12.88422;17.65982;95.60177;,
 -14.36996;14.75453;98.82816;,
 -28.73982;14.75453;94.65405;,
 -13.46940;-2.47851;55.44217;,
 -14.36996;-1.22690;98.82816;,
 -28.73982;-1.22690;94.65405;,
 -13.46940;-2.47851;71.21763;,
 -13.46940;-3.73012;95.60177;,
 -13.46940;-3.73012;75.11913;,
 14.36996;14.75453;-97.52036;,
 14.36996;-1.22690;-97.52036;,
 28.73982;-1.22690;-92.53432;,
 28.73982;14.75453;-92.53432;,
 12.88422;17.65982;-95.56990;,
 13.46940;-3.73012;-95.56990;,
 12.88422;17.65982;-95.56990;,
 25.76843;17.65982;-90.58342;,
 25.76843;17.65982;-47.77671;,
 12.88422;17.65982;-47.77671;,
 13.46940;-3.73012;-50.70270;,
 25.76843;17.65982;-7.07726;,
 12.88422;17.65982;-7.07726;,
 13.46940;-2.47851;-46.80140;,
 25.76843;17.65982;52.51604;,
 12.88422;17.65982;52.51604;,
 13.46940;-2.47851;-9.02797;,
 25.76843;17.65982;71.70530;,
 12.88422;17.65982;71.70530;,
 13.46940;-3.73012;-5.12656;,
 25.76843;17.65982;91.42770;,
 12.88422;17.65982;95.60177;,
 13.46940;-3.73012;51.54060;,
 12.88422;17.65982;95.60177;,
 28.73982;14.75453;94.65405;,
 14.36996;14.75453;98.82816;,
 13.46940;-2.47851;55.44217;,
 28.73982;-1.22690;94.65405;,
 14.36996;-1.22690;98.82816;,
 13.46940;-2.47851;71.21763;,
 13.46940;-3.73012;95.60177;,
 13.46940;-3.73012;75.11913;;
 
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
 4;56,57,58,59;,
 4;56,59,17,60;,
 4;57,61,46,58;,
 4;62,63,64,65;,
 4;61,66,44,46;,
 4;65,64,67,68;,
 4;66,69,45,44;,
 4;68,67,70,71;,
 4;69,72,36,45;,
 4;71,70,73,74;,
 4;72,75,37,36;,
 4;74,73,76,77;,
 4;75,78,38,37;,
 4;79,28,80,81;,
 4;78,82,39,38;,
 4;81,80,83,84;,
 4;82,85,50,39;,
 4;84,83,54,86;,
 4;85,87,51,50;,
 4;86,54,51,87;,
 4;88,89,90,91;,
 4;88,92,22,89;,
 4;91,90,49,93;,
 4;94,95,96,97;,
 4;93,49,48,98;,
 4;95,99,100,96;,
 4;98,48,47,101;,
 4;99,102,103,100;,
 4;101,47,40,104;,
 4;102,105,106,103;,
 4;104,40,41,107;,
 4;105,108,109,106;,
 4;107,41,43,110;,
 4;111,112,113,35;,
 4;110,43,42,114;,
 4;112,115,116,113;,
 4;114,42,53,117;,
 4;115,118,55,116;,
 4;117,53,52,119;,
 4;118,119,52,55;,
 4;56,88,91,57;,
 4;92,88,56,60;,
 4;95,94,62,65;,
 4;99,95,65,68;,
 4;68,71,102,99;,
 4;102,71,74,105;,
 4;105,74,77,108;,
 4;79,81,112,111;,
 4;81,84,115,112;,
 4;86,118,115,84;,
 4;87,119,118,86;,
 4;87,85,117,119;,
 4;114,117,85,82;,
 4;78,110,114,82;,
 4;75,107,110,78;,
 4;75,72,104,107;,
 4;72,69,101,104;,
 4;69,66,98,101;,
 4;66,61,93,98;,
 4;91,93,61,57;,
 4;120,121,122,123;,
 4;123,122,124,125;,
 4;126,127,128,129;,
 4;127,130,131,128;,
 4;132,133,122,121;,
 4;132,134,135,133;,
 4;133,136,124,122;,
 4;133,135,137,136;,
 4;138,139,140,141;,
 4;138,129,128,139;,
 4;139,142,143,140;,
 4;139,128,131,142;,
 4;144,145,146,147;,
 4;144,120,123,145;,
 4;145,148,149,146;,
 4;145,123,125,148;,
 4;150,151,127,126;,
 4;150,152,153,151;,
 4;151,154,130,127;,
 4;151,153,155,154;,
 3;156,121,157;,
 4;158,157,121,120;,
 3;159,158,120;,
 3;160,161,129;,
 3;126,162,163;,
 4;126,129,161,162;,
 3;164,132,165;,
 4;164,166,134,132;,
 3;138,167,168;,
 4;156,165,132,121;,
 4;138,141,169,167;,
 4;129,138,168,160;,
 3;170,144,171;,
 4;170,159,120,144;,
 3;150,172,173;,
 4;174,171,144,147;,
 4;150,126,163,172;,
 4;152,150,173,175;,
 4;176,177,178,179;,
 4;176,180,137,177;,
 4;179,178,166,181;,
 4;182,183,184,185;,
 4;181,166,164,186;,
 4;183,187,188,184;,
 4;186,164,165,189;,
 4;187,190,191,188;,
 4;189,165,156,192;,
 4;190,193,194,191;,
 4;192,156,157,195;,
 4;193,196,197,194;,
 4;195,157,158,198;,
 4;199,200,201,149;,
 4;198,158,159,202;,
 4;200,203,204,201;,
 4;202,159,170,205;,
 4;203,206,174,204;,
 4;205,170,171,207;,
 4;206,207,171,174;,
 4;208,209,210,211;,
 4;208,211,143,212;,
 4;209,213,169,210;,
 4;214,215,216,217;,
 4;213,218,167,169;,
 4;217,216,219,220;,
 4;218,221,168,167;,
 4;220,219,222,223;,
 4;221,224,160,168;,
 4;223,222,225,226;,
 4;224,227,161,160;,
 4;226,225,228,229;,
 4;227,230,162,161;,
 4;231,155,232,233;,
 4;230,234,163,162;,
 4;233,232,235,236;,
 4;234,237,172,163;,
 4;236,235,175,238;,
 4;237,239,173,172;,
 4;238,175,173,239;,
 4;176,179,209,208;,
 4;212,180,176,208;,
 4;217,183,182,214;,
 4;220,187,183,217;,
 4;187,220,223,190;,
 4;223,226,193,190;,
 4;226,229,196,193;,
 4;199,231,233,200;,
 4;200,233,236,203;,
 4;206,203,236,238;,
 4;207,206,238,239;,
 4;207,239,237,205;,
 4;234,202,205,237;,
 4;198,202,234,230;,
 4;195,198,230,227;,
 4;195,227,224,192;,
 4;192,224,221,189;,
 4;189,221,218,186;,
 4;186,218,213,181;,
 4;209,179,181,213;;
 
 MeshMaterialList {
  3;
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
  2;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\RemoCon.png";
   }
  }
  Material {
   0.194400;0.194400;0.194400;1.000000;;
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
  147;
  -0.724965;0.650059;-0.227703;,
  0.724965;0.650059;-0.227703;,
  0.699462;0.691628;0.180009;,
  -0.699462;0.691628;0.180009;,
  -0.254824;0.954247;0.156455;,
  0.254824;0.954247;0.156455;,
  0.286165;0.936542;-0.202480;,
  -0.286165;0.936542;-0.202480;,
  -0.887520;0.460769;0.000000;,
  -0.301758;0.953384;0.000000;,
  0.887520;0.460769;0.000000;,
  0.301758;0.953384;0.000000;,
  0.923880;-0.382683;-0.000000;,
  -0.923880;-0.382683;0.000000;,
  -0.842400;-0.537500;0.038169;,
  -0.842401;-0.537498;-0.038167;,
  -0.348350;-0.931799;0.101994;,
  -0.348353;-0.931799;-0.101987;,
  0.348353;-0.931799;-0.101987;,
  0.348350;-0.931799;0.101994;,
  0.842400;-0.537500;0.038169;,
  0.842401;-0.537498;-0.038167;,
  -0.842401;-0.537499;0.038165;,
  -0.348352;-0.931800;0.101982;,
  -0.337329;-0.919087;-0.203687;,
  0.337329;-0.919087;-0.203687;,
  0.348352;-0.931800;0.101982;,
  -0.271592;-0.957265;0.099408;,
  0.271592;-0.957265;0.099408;,
  0.271593;-0.957264;-0.099412;,
  -0.271593;-0.957264;-0.099412;,
  0.842401;-0.537499;0.038165;,
  -0.842400;-0.537499;-0.038170;,
  -0.271590;-0.957264;-0.099420;,
  -0.271590;-0.957264;0.099419;,
  0.271590;-0.957264;0.099419;,
  0.271590;-0.957264;-0.099420;,
  -0.348350;-0.931799;-0.101995;,
  0.348350;-0.931799;-0.101995;,
  0.303720;-0.940813;0.150419;,
  -0.303720;-0.940813;0.150419;,
  0.842400;-0.537499;-0.038170;,
  -0.159268;0.418509;-0.894139;,
  -0.158256;-0.438827;-0.884526;,
  -0.059711;0.938270;-0.340710;,
  -0.056856;-0.945397;-0.320923;,
  0.000000;1.000000;0.000000;,
  0.000000;-0.994387;0.105806;,
  0.000000;-0.994387;0.105806;,
  0.000000;-0.994386;-0.105811;,
  -0.037847;0.967899;0.248475;,
  0.000000;-0.994385;0.105818;,
  -0.073384;0.873216;0.481777;,
  0.000000;-0.994386;0.105818;,
  -0.150404;0.000000;0.988625;,
  0.000000;-0.994385;-0.105819;,
  -0.034518;-0.973543;0.225883;,
  0.159268;0.418509;-0.894139;,
  0.158256;-0.438827;-0.884526;,
  0.059711;0.938270;-0.340710;,
  0.056856;-0.945397;-0.320923;,
  0.037847;0.967899;0.248475;,
  0.073384;0.873216;0.481777;,
  0.150404;0.000000;0.988625;,
  0.034518;-0.973543;0.225883;,
  -0.315041;-0.449412;-0.835929;,
  -0.348720;0.000000;-0.937227;,
  -0.297387;0.000000;0.954757;,
  -0.067291;-0.895306;0.440340;,
  -0.134241;-0.899086;0.416682;,
  0.348720;0.000000;-0.937227;,
  0.315041;-0.449412;-0.835929;,
  0.297387;0.000000;0.954757;,
  0.067291;-0.895306;0.440340;,
  0.134241;-0.899086;0.416682;,
  0.921713;-0.387874;-0.000000;,
  -0.921713;-0.387874;0.000000;,
  -0.921713;-0.387874;0.000000;,
  0.921713;-0.387874;-0.000000;,
  0.323823;-0.921032;-0.216423;,
  -0.323823;-0.921032;-0.216423;,
  -0.360077;-0.894760;0.264101;,
  0.360077;-0.894760;0.264101;,
  0.377481;-0.926017;-0.000000;,
  -0.377481;-0.926017;0.000000;,
  -0.951767;0.306822;0.000000;,
  0.951767;0.306822;0.000000;,
  0.951767;0.306822;0.000000;,
  -0.951767;0.306822;0.000000;,
  0.890127;0.453259;-0.047219;,
  0.890126;0.453262;0.047222;,
  0.422323;0.894696;-0.145472;,
  0.422319;0.894697;0.145479;,
  -0.422319;0.894697;0.145479;,
  -0.422323;0.894696;-0.145472;,
  -0.890127;0.453259;-0.047219;,
  -0.890126;0.453262;0.047222;,
  0.890127;0.453259;-0.047223;,
  0.422322;0.894695;-0.145482;,
  0.409751;0.871796;0.268471;,
  -0.409751;0.871796;0.268471;,
  -0.422322;0.894695;-0.145482;,
  0.343304;0.928638;-0.140619;,
  -0.343304;0.928638;-0.140619;,
  -0.343300;0.928640;0.140616;,
  0.343300;0.928640;0.140616;,
  -0.890127;0.453259;-0.047223;,
  0.890127;0.453259;0.047220;,
  0.343304;0.928639;0.140613;,
  0.343305;0.928639;-0.140610;,
  -0.343305;0.928639;-0.140610;,
  -0.343304;0.928639;0.140613;,
  0.422323;0.894696;0.145475;,
  -0.422323;0.894696;0.145475;,
  -0.370107;0.904582;-0.211545;,
  0.370107;0.904582;-0.211545;,
  -0.890127;0.453259;0.047220;,
  0.157023;-0.327220;0.931810;,
  0.155696;0.347488;0.924668;,
  0.072179;-0.900666;0.428475;,
  0.069003;0.909301;0.410377;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.987977;-0.154600;,
  0.000000;0.987978;0.154596;,
  0.048228;-0.940968;-0.335041;,
  0.000000;0.987979;-0.154590;,
  0.128008;-0.426192;-0.895530;,
  0.000000;0.987979;-0.154590;,
  0.126075;0.451409;-0.883366;,
  0.000000;0.987978;0.154593;,
  0.044382;0.949885;-0.309434;,
  -0.157023;-0.327220;0.931810;,
  -0.155696;0.347488;0.924668;,
  -0.072179;-0.900666;0.428475;,
  -0.069003;0.909301;0.410377;,
  -0.048228;-0.940968;-0.335041;,
  -0.128008;-0.426192;-0.895530;,
  -0.126075;0.451409;-0.883366;,
  -0.044382;0.949885;-0.309434;,
  0.313384;-0.354946;0.880797;,
  0.309610;0.361405;0.879504;,
  0.255889;-0.438520;-0.861522;,
  0.251190;0.455601;-0.854009;,
  -0.309610;0.361405;0.879504;,
  -0.313384;-0.354946;0.880797;,
  -0.255889;-0.438520;-0.861522;,
  -0.251190;0.455601;-0.854009;;
  196;
  4;14,8,8,15;,
  4;8,9,9,8;,
  4;20,21,10,10;,
  4;10,10,11,11;,
  4;22,15,8,8;,
  4;22,8,0,13;,
  4;8,8,9,9;,
  4;8,9,7,0;,
  4;31,12,1,10;,
  4;31,10,10,21;,
  4;10,1,6,11;,
  4;10,11,11,10;,
  4;32,13,3,8;,
  4;32,8,8,14;,
  4;8,3,4,9;,
  4;8,9,9,8;,
  4;41,20,10,10;,
  4;41,10,2,12;,
  4;10,10,11,11;,
  4;10,11,5,2;,
  3;30,17,15;,
  4;16,14,15,17;,
  3;34,14,16;,
  3;29,21,18;,
  3;20,35,19;,
  4;20,19,18,21;,
  3;23,27,22;,
  4;23,22,13,24;,
  3;31,28,26;,
  4;30,15,22,27;,
  4;31,26,25,12;,
  4;21,29,28,31;,
  3;33,37,32;,
  4;33,32,14,34;,
  3;41,38,36;,
  4;40,13,32,37;,
  4;41,36,35,20;,
  4;12,39,38,41;,
  4;42,43,65,66;,
  4;42,0,7,44;,
  4;43,45,24,65;,
  4;44,7,9,46;,
  4;45,47,23,24;,
  4;46,9,9,46;,
  4;47,48,27,23;,
  4;46,9,9,46;,
  4;48,49,30,27;,
  4;46,9,9,46;,
  4;49,49,17,30;,
  4;46,9,4,50;,
  4;49,51,16,17;,
  4;50,4,3,52;,
  4;51,53,34,16;,
  4;54,67,67,54;,
  4;53,55,33,34;,
  4;68,69,40,56;,
  4;55,55,37,33;,
  4;56,40,37,55;,
  4;57,70,71,58;,
  4;57,59,6,1;,
  4;58,71,25,60;,
  4;59,46,11,6;,
  4;60,25,26,47;,
  4;46,46,11,11;,
  4;47,26,28,48;,
  4;46,46,11,11;,
  4;48,28,29,49;,
  4;46,46,11,11;,
  4;49,29,18,49;,
  4;46,61,5,11;,
  4;49,18,19,51;,
  4;61,62,2,5;,
  4;51,19,35,53;,
  4;63,63,72,72;,
  4;53,35,36,55;,
  4;73,64,39,74;,
  4;55,36,38,55;,
  4;64,55,38,39;,
  4;42,57,58,43;,
  4;59,57,42,44;,
  4;46,59,44,46;,
  4;46,46,46,46;,
  4;46,46,46,46;,
  4;46,46,46,46;,
  4;46,46,50,61;,
  4;50,52,62,61;,
  4;54,54,63,63;,
  4;56,64,73,68;,
  4;55,55,64,56;,
  4;55,55,55,55;,
  4;53,55,55,53;,
  4;51,51,53,53;,
  4;49,49,51,51;,
  4;49,49,49,49;,
  4;49,48,48,49;,
  4;48,47,47,48;,
  4;47,45,60,47;,
  4;58,60,45,43;,
  4;89,90,78,78;,
  4;78,78,83,83;,
  4;95,77,77,96;,
  4;77,84,84,77;,
  4;97,75,78,90;,
  4;97,86,75,75;,
  4;75,83,83,78;,
  4;75,75,82,83;,
  4;106,76,76,85;,
  4;106,96,77,76;,
  4;76,84,81,76;,
  4;76,77,84,84;,
  4;107,78,78,87;,
  4;107,89,78,78;,
  4;78,83,79,78;,
  4;78,78,83,83;,
  4;116,77,77,95;,
  4;116,88,77,77;,
  4;77,84,84,77;,
  4;77,77,80,84;,
  3;105,90,92;,
  4;91,92,90,89;,
  3;109,91,89;,
  3;104,93,96;,
  3;95,94,110;,
  4;95,96,93,94;,
  3;98,97,102;,
  4;98,99,86,97;,
  3;106,101,103;,
  4;105,102,97,90;,
  4;106,85,100,101;,
  4;96,106,103,104;,
  3;108,107,112;,
  4;108,109,89,107;,
  3;116,111,113;,
  4;115,112,107,87;,
  4;116,95,110,111;,
  4;88,116,113,114;,
  4;117,139,140,118;,
  4;117,119,82,139;,
  4;118,140,99,120;,
  4;119,121,83,82;,
  4;120,99,98,122;,
  4;121,121,83,83;,
  4;122,98,102,122;,
  4;121,121,83,83;,
  4;122,102,105,123;,
  4;121,121,83,83;,
  4;123,105,92,123;,
  4;121,124,79,83;,
  4;123,92,91,125;,
  4;124,126,141,79;,
  4;125,91,109,127;,
  4;126,128,142,141;,
  4;127,109,108,129;,
  4;128,130,115,142;,
  4;129,108,112,129;,
  4;130,129,112,115;,
  4;131,132,143,144;,
  4;131,144,81,133;,
  4;132,134,100,143;,
  4;133,81,84,121;,
  4;134,122,101,100;,
  4;121,84,84,121;,
  4;122,122,103,101;,
  4;121,84,84,121;,
  4;122,123,104,103;,
  4;121,84,84,121;,
  4;123,123,93,104;,
  4;121,84,80,135;,
  4;123,125,94,93;,
  4;135,80,145,136;,
  4;125,127,110,94;,
  4;136,145,146,137;,
  4;127,129,111,110;,
  4;137,146,114,138;,
  4;129,129,113,111;,
  4;138,114,113,129;,
  4;117,118,132,131;,
  4;133,119,117,131;,
  4;121,121,119,133;,
  4;121,121,121,121;,
  4;121,121,121,121;,
  4;121,121,121,121;,
  4;121,135,124,121;,
  4;124,135,136,126;,
  4;126,136,137,128;,
  4;130,128,137,138;,
  4;129,130,138,129;,
  4;129,129,129,129;,
  4;127,127,129,129;,
  4;125,127,127,125;,
  4;123,125,125,123;,
  4;123,123,123,123;,
  4;123,123,122,122;,
  4;122,122,122,122;,
  4;122,122,134,120;,
  4;132,118,120,134;;
 }
 MeshTextureCoords {
  240;
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;0.250000;,
  0.000000;0.500000;,
  0.750000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.750000;0.000000;,
  1.000000;0.500000;,
  1.000000;0.250000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.750000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.750000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.125000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.125000;,
  1.000000;0.000000;,
  0.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  0.000000;0.250000;,
  0.000000;0.250000;,
  0.000000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  0.000000;0.875000;,
  0.000000;0.875000;,
  1.000000;0.875000;,
  1.000000;0.875000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.249920;0.989510;,
  0.000000;0.963420;,
  0.000080;0.739510;,
  0.250000;0.739510;,
  0.250000;0.250000;,
  0.000140;0.526610;,
  0.250070;0.526620;,
  0.250000;0.250000;,
  0.000240;0.214890;,
  0.250170;0.214890;,
  0.250000;0.500000;,
  0.000280;0.114510;,
  0.250200;0.114520;,
  0.250000;0.500000;,
  0.000310;0.011350;,
  0.250240;-0.010480;,
  0.250000;0.750000;,
  0.250000;0.000000;,
  1.000000;0.000000;,
  0.750000;0.000000;,
  0.250000;0.750000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.250000;0.875000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.749770;0.989520;,
  0.749850;0.739520;,
  0.999770;0.739520;,
  0.999700;0.963440;,
  0.750000;0.250000;,
  0.749910;0.526630;,
  0.999840;0.526630;,
  0.750000;0.250000;,
  0.750010;0.214900;,
  0.999940;0.214910;,
  0.750000;0.500000;,
  0.750050;0.114520;,
  0.999970;0.114530;,
  0.750000;0.500000;,
  0.750090;-0.010480;,
  1.000000;0.011360;,
  0.750000;0.750000;,
  0.750000;0.000000;,
  0.250000;0.000000;,
  0.000000;0.000000;,
  0.750000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.750000;0.875000;,
  0.750000;1.000000;,
  0.750000;0.875000;,
  0.250000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.250000;0.000000;,
  0.000000;0.500000;,
  0.000000;0.250000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  1.000000;0.250000;,
  1.000000;0.500000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.750000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;0.125000;,
  0.000000;0.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  1.000000;0.000000;,
  0.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  0.000000;0.250000;,
  0.000000;0.250000;,
  0.000000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  0.000000;0.875000;,
  0.000000;0.875000;,
  1.000000;0.875000;,
  1.000000;0.875000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.250000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.249920;0.989510;,
  0.250000;0.739510;,
  0.000080;0.739510;,
  0.000000;0.963420;,
  0.250000;0.250000;,
  0.250070;0.526620;,
  0.000140;0.526610;,
  0.250000;0.250000;,
  0.250170;0.214890;,
  0.000240;0.214890;,
  0.250000;0.500000;,
  0.250200;0.114520;,
  0.000280;0.114510;,
  0.250000;0.500000;,
  0.250240;-0.010480;,
  0.000310;0.011350;,
  0.250000;0.750000;,
  0.250000;0.000000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  0.250000;0.750000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.250000;0.875000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.749770;0.989520;,
  0.999700;0.963440;,
  0.999770;0.739520;,
  0.749850;0.739520;,
  0.750000;0.250000;,
  0.999840;0.526630;,
  0.749910;0.526630;,
  0.750000;0.250000;,
  0.999940;0.214910;,
  0.750010;0.214900;,
  0.750000;0.500000;,
  0.999970;0.114530;,
  0.750050;0.114520;,
  0.750000;0.500000;,
  1.000000;0.011360;,
  0.750090;-0.010480;,
  0.750000;0.750000;,
  0.750000;0.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.750000;0.750000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.750000;0.875000;,
  0.750000;1.000000;,
  0.750000;0.875000;;
 }
}
