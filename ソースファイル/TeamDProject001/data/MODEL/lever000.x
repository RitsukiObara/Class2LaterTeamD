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
 170;
 -34.19389;-47.06822;14.78817;,
 -34.19389;-51.66043;15.70162;,
 -37.46527;-47.06822;15.70162;,
 -34.19389;-55.55350;18.30289;,
 -38.46814;-53.06823;18.30289;,
 -40.23858;-47.06822;18.30289;,
 -34.19389;-58.15479;22.19596;,
 -38.14279;-56.66946;22.19596;,
 -41.03356;-52.61150;22.19596;,
 -42.09169;-47.06822;22.19596;,
 -34.19389;-59.06823;26.78817;,
 -37.46527;-58.15479;26.78817;,
 -40.23859;-55.55350;26.78817;,
 -42.09170;-51.66043;26.78817;,
 -42.74237;-47.06822;26.78817;,
 -37.46527;48.93178;15.70163;,
 -34.19389;53.52398;15.70163;,
 -34.19389;48.93178;14.78819;,
 -38.46814;54.93178;18.30290;,
 -34.19389;57.41706;18.30290;,
 -40.23858;48.93178;18.30290;,
 -38.14279;58.53302;22.19598;,
 -34.19389;60.01834;22.19598;,
 -41.03355;54.47506;22.19598;,
 -42.09169;48.93178;22.19598;,
 -37.46527;60.01834;26.78818;,
 -34.19389;60.93178;26.78818;,
 -40.23858;57.41706;26.78818;,
 -42.09169;53.52398;26.78818;,
 -42.74237;48.93178;26.78818;,
 37.46527;-47.06822;15.70162;,
 34.19389;-51.66043;15.70162;,
 34.19389;-47.06822;14.78817;,
 38.46814;-53.06823;18.30289;,
 34.19389;-55.55350;18.30289;,
 40.23858;-47.06822;18.30289;,
 38.14279;-56.66946;22.19596;,
 34.19389;-58.15479;22.19596;,
 41.03355;-52.61150;22.19596;,
 42.09169;-47.06822;22.19596;,
 37.46527;-58.15479;26.78817;,
 34.19389;-59.06823;26.78817;,
 40.23858;-55.55350;26.78817;,
 42.09169;-51.66043;26.78817;,
 42.74237;-47.06822;26.78817;,
 34.19389;48.93178;14.78819;,
 34.19389;53.52398;15.70163;,
 37.46527;48.93178;15.70163;,
 34.19389;57.41706;18.30290;,
 38.46814;54.93178;18.30290;,
 40.23858;48.93178;18.30290;,
 34.19389;60.01834;22.19598;,
 38.14279;58.53302;22.19598;,
 41.03356;54.47506;22.19598;,
 42.09169;48.93178;22.19598;,
 34.19389;60.93178;26.78818;,
 37.46527;60.01834;26.78818;,
 40.23859;57.41706;26.78818;,
 42.09170;53.52398;26.78818;,
 42.74237;48.93178;26.78818;,
 -24.46477;-47.06822;14.78817;,
 -24.49047;-51.66043;15.70162;,
 -24.62921;-55.55350;18.30289;,
 -24.85990;-58.15479;22.19596;,
 -25.14741;-59.06823;26.78817;,
 -25.15035;48.93178;14.78819;,
 -25.24162;53.52398;15.70163;,
 -25.43597;57.41706;18.30290;,
 -25.70382;60.01834;22.19598;,
 -26.00436;60.93178;26.78818;,
 -25.23309;-47.06822;26.78817;,
 -25.15280;-58.31173;26.78817;,
 -25.91867;48.93178;26.78818;,
 -12.49209;-47.06822;14.78817;,
 -12.52103;-51.66043;15.70162;,
 -12.61889;-55.55350;18.30289;,
 -12.77081;-58.15479;22.19596;,
 -12.95364;-59.06823;26.78817;,
 -12.69823;53.52398;15.70163;,
 -12.65382;48.93178;14.78819;,
 -12.80924;57.41706;18.30290;,
 -12.96991;60.01834;22.19598;,
 -13.15580;60.93178;26.78818;,
 -12.95466;-58.46722;26.78817;,
 -12.97386;-47.06822;26.78817;,
 -13.13559;48.93178;26.78818;,
 14.06330;-47.06822;14.78817;,
 14.08449;-51.66043;15.70162;,
 14.12618;-55.55350;18.30289;,
 14.18202;-58.15479;22.19596;,
 14.24353;-59.06823;26.78817;,
 13.87110;53.52398;15.70163;,
 13.86855;48.93178;14.78819;,
 13.89699;57.41706;18.30290;,
 13.94228;60.01833;22.19598;,
 14.00008;60.93178;26.78818;,
 14.24302;-58.81391;26.78817;,
 14.21918;-47.06822;26.78817;,
 14.02442;48.93178;26.78818;,
 25.33957;-47.06822;14.78817;,
 21.88116;-51.66043;15.70162;,
 21.91910;-55.55350;18.30289;,
 22.00590;-58.15479;22.19596;,
 22.12830;-59.06823;26.78817;,
 22.85940;53.52398;15.70163;,
 26.23240;48.93178;14.78819;,
 22.96976;57.41706;18.30290;,
 23.10493;60.01833;22.19598;,
 23.24433;60.93178;26.78818;,
 22.12974;-58.91444;26.78817;,
 22.23991;-47.06822;26.78817;,
 23.13272;48.93178;26.78818;,
 -34.19389;39.24546;14.78818;,
 -37.46527;39.38589;15.70162;,
 -40.23858;39.84756;18.30289;,
 -42.09169;40.56005;22.19598;,
 -42.74237;41.41497;26.78818;,
 37.46527;40.09084;15.70162;,
 34.19389;39.88886;14.78818;,
 40.23858;40.60470;18.30290;,
 42.09169;41.35205;22.19598;,
 42.74237;42.21919;26.78818;,
 -34.19389;39.24546;14.78818;,
 -34.19389;48.93178;14.78819;,
 -25.15035;48.93178;14.78819;,
 -25.08179;34.62846;14.78818;,
 -36.10452;41.47742;26.78818;,
 -25.78266;29.88590;26.78818;,
 -25.86612;41.57366;26.78818;,
 -12.63784;34.74555;14.78818;,
 -12.65382;48.93178;14.78819;,
 -13.12339;41.69361;26.78818;,
 -13.07946;15.62011;26.78818;,
 13.88728;34.99511;14.78818;,
 13.86855;48.93178;14.78819;,
 14.03859;41.94914;26.78818;,
 14.15405;-14.96334;26.78818;,
 34.19389;39.88886;14.78818;,
 26.49577;35.07806;14.78818;,
 26.23240;48.93178;14.78819;,
 23.06857;42.03406;26.78818;,
 22.45182;-24.28179;26.78818;,
 -13.00408;-29.12860;26.78817;,
 -25.36092;-29.16872;26.78817;,
 14.18261;-29.04034;26.78817;,
 26.65309;-28.99985;26.78817;,
 22.40781;-29.01363;26.78817;,
 -34.19390;-29.78378;14.78817;,
 -37.46527;-29.74975;15.70161;,
 -40.23858;-29.63166;18.30289;,
 -42.09169;-29.44744;22.19596;,
 -42.74237;-29.22515;26.78817;,
 37.46527;-29.50648;15.70162;,
 34.19389;-29.56174;14.78817;,
 40.23858;-29.37037;18.30289;,
 42.09169;-29.17412;22.19596;,
 42.74237;-28.94761;26.78817;,
 -24.58843;-34.45528;14.78817;,
 -24.46477;-47.06822;14.78817;,
 -34.19389;-47.06822;14.78817;,
 -34.19390;-29.78378;14.78817;,
 -27.42992;-29.17544;26.78817;,
 -12.52133;-34.41610;14.78817;,
 -12.49209;-47.06822;14.78817;,
 14.02792;-34.32990;14.78817;,
 14.06330;-47.06822;14.78817;,
 34.19389;-29.56174;14.78817;,
 34.19389;-47.06822;14.78817;,
 25.33957;-47.06822;14.78817;,
 25.85049;-34.30382;14.78817;;
 
 184;
 3;0,1,2;,
 3;1,3,4;,
 3;4,2,1;,
 3;2,4,5;,
 3;3,6,7;,
 3;7,4,3;,
 3;4,7,8;,
 3;8,5,4;,
 3;5,8,9;,
 3;6,10,11;,
 3;11,7,6;,
 3;7,11,12;,
 3;12,8,7;,
 3;8,12,13;,
 3;13,9,8;,
 3;9,13,14;,
 3;15,16,17;,
 3;18,19,16;,
 3;16,15,18;,
 3;20,18,15;,
 3;21,22,19;,
 3;19,18,21;,
 3;23,21,18;,
 3;18,20,23;,
 3;24,23,20;,
 3;25,26,22;,
 3;22,21,25;,
 3;27,25,21;,
 3;21,23,27;,
 3;28,27,23;,
 3;23,24,28;,
 3;29,28,24;,
 3;30,31,32;,
 3;33,34,31;,
 3;31,30,33;,
 3;35,33,30;,
 3;36,37,34;,
 3;34,33,36;,
 3;38,36,33;,
 3;33,35,38;,
 3;39,38,35;,
 3;40,41,37;,
 3;37,36,40;,
 3;42,40,36;,
 3;36,38,42;,
 3;43,42,38;,
 3;38,39,43;,
 3;44,43,39;,
 3;45,46,47;,
 3;46,48,49;,
 3;49,47,46;,
 3;47,49,50;,
 3;48,51,52;,
 3;52,49,48;,
 3;49,52,53;,
 3;53,50,49;,
 3;50,53,54;,
 3;51,55,56;,
 3;56,52,51;,
 3;52,56,57;,
 3;57,53,52;,
 3;53,57,58;,
 3;58,54,53;,
 3;54,58,59;,
 4;14,13,12,11;,
 4;40,42,43,44;,
 3;41,40,44;,
 4;58,57,56,55;,
 4;29,26,25,27;,
 3;55,59,58;,
 4;60,61,1,0;,
 4;61,62,3,1;,
 4;62,63,6,3;,
 4;63,64,10,6;,
 4;65,17,16,66;,
 4;66,16,19,67;,
 4;67,19,22,68;,
 4;68,22,26,69;,
 4;70,14,11,71;,
 4;69,26,29,72;,
 4;73,74,61,60;,
 4;74,75,62,61;,
 4;75,76,63,62;,
 4;76,77,64,63;,
 4;78,79,65,66;,
 4;80,78,66,67;,
 4;81,80,67,68;,
 4;82,81,68,69;,
 4;83,84,70,71;,
 4;85,82,69,72;,
 4;86,87,74,73;,
 4;87,88,75,74;,
 4;88,89,76,75;,
 4;89,90,77,76;,
 4;91,92,79,78;,
 4;93,91,78,80;,
 4;94,93,80,81;,
 4;95,94,81,82;,
 4;96,97,84,83;,
 4;98,95,82,85;,
 4;99,32,31,100;,
 4;99,100,87,86;,
 4;100,31,34,101;,
 4;100,101,88,87;,
 4;101,34,37,102;,
 4;101,102,89,88;,
 4;102,37,41,103;,
 4;102,103,90,89;,
 4;104,46,45,105;,
 4;104,105,92,91;,
 4;106,48,46,104;,
 4;106,104,91,93;,
 4;107,51,48,106;,
 4;107,106,93,94;,
 4;108,55,51,107;,
 4;108,107,94,95;,
 4;109,41,44,110;,
 4;109,110,97,96;,
 4;111,59,55,108;,
 4;111,108,95,98;,
 4;112,113,15,17;,
 4;113,114,20,15;,
 4;114,115,24,20;,
 4;115,116,29,24;,
 4;117,118,45,47;,
 4;119,117,47,50;,
 4;120,119,50,54;,
 4;121,120,54,59;,
 4;122,123,124,125;,
 3;126,29,116;,
 3;126,127,128;,
 4;126,128,72,29;,
 4;129,125,124,130;,
 4;131,85,72,128;,
 4;131,128,127,132;,
 4;133,129,130,134;,
 4;135,98,85,131;,
 4;135,131,132,136;,
 4;137,138,139,45;,
 4;138,133,134,139;,
 4;121,59,111,140;,
 4;140,111,98,135;,
 4;140,135,136,141;,
 4;142,132,127,143;,
 4;142,143,70,84;,
 4;144,136,132,142;,
 4;144,142,84,97;,
 3;145,141,146;,
 4;145,146,110,44;,
 4;146,141,136,144;,
 4;146,144,97,110;,
 4;147,0,2,148;,
 4;147,148,113,112;,
 4;148,2,5,149;,
 4;148,149,114,113;,
 4;149,5,9,150;,
 4;149,150,115,114;,
 4;150,9,14,151;,
 4;150,151,116,115;,
 4;152,30,32,153;,
 4;152,153,118,117;,
 4;154,35,30,152;,
 4;154,152,117,119;,
 4;155,39,35,154;,
 4;155,154,119,120;,
 4;156,44,39,155;,
 4;156,155,120,121;,
 4;157,158,159,160;,
 4;157,160,122,125;,
 4;151,14,70,161;,
 4;151,161,126,116;,
 3;161,70,143;,
 4;161,143,127,126;,
 4;162,163,158,157;,
 4;162,157,125,129;,
 4;164,165,163,162;,
 4;164,162,129,133;,
 4;166,167,168,169;,
 4;166,169,138,137;,
 4;169,168,165,164;,
 4;169,164,133,138;,
 3;145,44,156;,
 4;145,156,121,140;,
 3;145,140,141;;
 
 MeshMaterialList {
  4;
  184;
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
  1,
  0,
  0,
  0,
  0,
  0,
  1,
  0,
  0,
  0;;
  Material {
   0.489412;0.489412;0.489412;1.000000;;
   6.000000;
   0.340000;0.340000;0.340000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.050196;0.025098;1.000000;;
   5.000000;
   0.250000;0.250000;0.250000;;
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
  126;
  0.135128;0.097151;-0.986054;,
  0.135128;-0.097151;-0.986054;,
  -0.135128;0.097151;-0.986054;,
  -0.135128;-0.097151;-0.986054;,
  -0.987707;0.069634;-0.139950;,
  -0.987707;-0.069633;-0.139950;,
  0.987707;0.069633;-0.139950;,
  0.987707;-0.069634;-0.139950;,
  0.133254;-0.972039;-0.193349;,
  -0.133254;-0.972039;-0.193349;,
  0.133254;0.972039;-0.193350;,
  -0.133254;0.972039;-0.193349;,
  -0.476208;0.141544;-0.867866;,
  -0.476209;-0.141544;-0.867866;,
  -0.809759;0.124520;-0.573397;,
  -0.809760;-0.124520;-0.573397;,
  -0.958521;0.099945;-0.266924;,
  -0.958521;-0.099944;-0.266925;,
  0.476209;0.141544;-0.867865;,
  0.476209;-0.141544;-0.867866;,
  0.809760;0.124520;-0.573397;,
  0.809759;-0.124520;-0.573397;,
  0.958521;0.099944;-0.266925;,
  0.958521;-0.099945;-0.266924;,
  0.204823;-0.364572;-0.908369;,
  -0.204823;-0.364572;-0.908369;,
  0.207483;-0.700517;-0.682808;,
  -0.207483;-0.700517;-0.682808;,
  0.185957;-0.917267;-0.352196;,
  -0.185957;-0.917267;-0.352196;,
  0.204823;0.364572;-0.908369;,
  -0.204823;0.364572;-0.908369;,
  0.207483;0.700518;-0.682807;,
  -0.207483;0.700517;-0.682808;,
  0.185957;0.917267;-0.352196;,
  -0.185957;0.917267;-0.352196;,
  -0.956191;-0.252288;-0.148489;,
  -0.799377;-0.578875;-0.160934;,
  -0.437546;-0.878314;-0.192660;,
  0.956191;-0.252289;-0.148488;,
  0.799378;-0.578875;-0.160934;,
  0.437546;-0.878314;-0.192660;,
  -0.956191;0.252289;-0.148488;,
  -0.799378;0.578875;-0.160934;,
  -0.437546;0.878314;-0.192660;,
  0.956191;0.252288;-0.148489;,
  0.799377;0.578875;-0.160934;,
  0.437546;0.878314;-0.192660;,
  -0.587664;-0.434391;-0.682610;,
  -0.566550;-0.732920;-0.376630;,
  -0.874248;-0.362048;-0.323438;,
  -0.587664;0.434391;-0.682610;,
  -0.566550;0.732919;-0.376630;,
  -0.874248;0.362048;-0.323438;,
  0.587664;-0.434391;-0.682610;,
  0.566550;-0.732919;-0.376630;,
  0.874248;-0.362048;-0.323438;,
  0.587664;0.434391;-0.682610;,
  0.566550;0.732920;-0.376630;,
  0.874248;0.362048;-0.323438;,
  -0.000000;0.098017;-0.995185;,
  0.000000;-0.098017;-0.995185;,
  -0.000000;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.980785;-0.195089;,
  0.000000;0.980785;-0.195089;,
  0.000000;-0.382684;-0.923879;,
  0.000000;-0.707106;-0.707107;,
  0.000000;-0.923879;-0.382684;,
  -0.000000;0.382684;-0.923880;,
  -0.000000;0.707106;-0.707107;,
  0.000000;0.923879;-0.382684;,
  -0.000000;0.098017;-0.995185;,
  -0.000000;-0.098017;-0.995185;,
  0.000000;0.980785;-0.195090;,
  -0.000000;0.382683;-0.923880;,
  0.000000;0.707107;-0.707107;,
  0.000000;0.923879;-0.382684;,
  -0.000000;-0.000000;1.000000;,
  0.000000;0.098017;-0.995185;,
  -0.000000;-0.098017;-0.995185;,
  0.000000;0.980785;-0.195091;,
  0.000000;0.382683;-0.923880;,
  0.000000;0.707107;-0.707107;,
  0.000000;0.923879;-0.382684;,
  -0.000000;-0.000001;1.000000;,
  -0.000000;0.098017;-0.995185;,
  0.000000;-0.098017;-0.995185;,
  -0.000000;0.980785;-0.195091;,
  0.000000;-0.707106;-0.707107;,
  0.000000;0.382684;-0.923879;,
  -0.000000;0.707107;-0.707107;,
  -0.000000;0.923879;-0.382684;,
  0.000001;-0.000001;1.000000;,
  0.135724;0.000000;-0.990747;,
  -0.135724;0.000000;-0.990747;,
  -0.990110;0.000000;-0.140290;,
  0.990110;0.000000;-0.140290;,
  -0.490657;0.000000;-0.871353;,
  -0.807538;0.000000;-0.589816;,
  -0.957523;0.000000;-0.288356;,
  0.490658;0.000000;-0.871352;,
  0.807538;0.000000;-0.589815;,
  0.957523;0.000000;-0.288356;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000001;-0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.135724;0.000000;-0.990747;,
  -0.135724;0.000000;-0.990747;,
  0.000001;-0.000001;1.000000;,
  -0.490657;0.000000;-0.871353;,
  -0.807538;0.000000;-0.589815;,
  -0.957523;0.000000;-0.288356;,
  0.490657;0.000000;-0.871353;,
  0.807538;0.000000;-0.589816;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000000;-0.000001;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;;
  184;
  3;3,25,13;,
  3;25,27,48;,
  3;48,13,25;,
  3;13,48,15;,
  3;27,29,49;,
  3;49,48,27;,
  3;48,49,50;,
  3;50,15,48;,
  3;15,50,17;,
  3;29,9,38;,
  3;38,49,29;,
  3;49,38,37;,
  3;37,50,49;,
  3;50,37,36;,
  3;36,17,50;,
  3;17,36,5;,
  3;12,31,2;,
  3;51,33,31;,
  3;31,12,51;,
  3;14,51,12;,
  3;52,35,33;,
  3;33,51,52;,
  3;53,52,51;,
  3;51,14,53;,
  3;16,53,14;,
  3;44,11,35;,
  3;35,52,44;,
  3;43,44,52;,
  3;52,53,43;,
  3;42,43,53;,
  3;53,16,42;,
  3;4,42,16;,
  3;19,24,1;,
  3;54,26,24;,
  3;24,19,54;,
  3;21,54,19;,
  3;55,28,26;,
  3;26,54,55;,
  3;56,55,54;,
  3;54,21,56;,
  3;23,56,21;,
  3;41,8,28;,
  3;28,55,41;,
  3;40,41,55;,
  3;55,56,40;,
  3;39,40,56;,
  3;56,23,39;,
  3;7,39,23;,
  3;0,30,18;,
  3;30,32,57;,
  3;57,18,30;,
  3;18,57,20;,
  3;32,34,58;,
  3;58,57,32;,
  3;57,58,59;,
  3;59,20,57;,
  3;20,59,22;,
  3;34,10,47;,
  3;47,58,34;,
  3;58,47,46;,
  3;46,59,58;,
  3;59,46,45;,
  3;45,22,59;,
  3;22,45,6;,
  4;63,63,63,63;,
  4;63,63,63,63;,
  3;63,63,63;,
  4;63,63,63,63;,
  4;63,63,63,63;,
  3;63,63,63;,
  4;61,66,25,3;,
  4;66,67,27,25;,
  4;67,68,29,27;,
  4;68,64,9,29;,
  4;60,2,31,69;,
  4;69,31,33,70;,
  4;70,33,35,71;,
  4;71,35,11,65;,
  4;63,63,63,63;,
  4;63,63,63,63;,
  4;73,66,66,61;,
  4;66,67,67,66;,
  4;67,68,68,67;,
  4;68,64,64,68;,
  4;75,72,60,69;,
  4;76,75,69,70;,
  4;77,76,70,71;,
  4;74,77,71,65;,
  4;63,63,63,63;,
  4;63,63,63,63;,
  4;80,66,66,73;,
  4;66,67,67,66;,
  4;67,68,68,67;,
  4;68,64,64,68;,
  4;82,79,72,75;,
  4;83,82,75,76;,
  4;84,83,76,77;,
  4;81,84,77,74;,
  4;63,63,63,63;,
  4;63,63,63,63;,
  4;87,1,24,66;,
  4;87,66,66,80;,
  4;66,24,26,89;,
  4;66,89,67,66;,
  4;89,26,28,68;,
  4;89,68,68,67;,
  4;68,28,8,64;,
  4;68,64,64,68;,
  4;90,30,0,86;,
  4;90,86,79,82;,
  4;91,32,30,90;,
  4;91,90,82,83;,
  4;92,34,32,91;,
  4;92,91,83,84;,
  4;88,10,34,92;,
  4;88,92,84,81;,
  4;63,63,63,63;,
  4;63,63,63,63;,
  4;63,63,63,63;,
  4;63,63,63,63;,
  4;95,98,12,2;,
  4;98,99,14,12;,
  4;99,100,16,14;,
  4;100,96,4,16;,
  4;101,94,0,18;,
  4;102,101,18,20;,
  4;103,102,20,22;,
  4;97,103,22,6;,
  4;95,2,60,104;,
  3;109,63,124;,
  3;109,62,63;,
  4;109,63,63,63;,
  4;105,104,60,72;,
  4;63,63,63,63;,
  4;63,63,62,78;,
  4;106,105,72,79;,
  4;63,63,63,63;,
  4;63,63,78,85;,
  4;94,107,86,0;,
  4;107,106,79,86;,
  4;125,63,63,108;,
  4;108,63,63,63;,
  4;108,63,85,93;,
  4;78,78,62,62;,
  4;78,62,63,63;,
  4;85,85,78,78;,
  4;85,78,63,63;,
  3;112,93,123;,
  4;112,123,63,63;,
  4;123,93,85,85;,
  4;123,85,63,63;,
  4;111,3,13,113;,
  4;111,113,98,95;,
  4;113,13,15,114;,
  4;113,114,99,98;,
  4;114,15,17,115;,
  4;114,115,100,99;,
  4;115,17,5,96;,
  4;115,96,96,100;,
  4;116,19,1,110;,
  4;116,110,94,101;,
  4;117,21,19,116;,
  4;117,116,101,102;,
  4;103,23,21,117;,
  4;103,117,102,103;,
  4;97,7,23,103;,
  4;97,103,103,97;,
  4;118,61,3,111;,
  4;118,111,95,104;,
  4;124,63,63,119;,
  4;124,119,109,124;,
  3;119,63,62;,
  4;119,62,62,109;,
  4;120,73,61,118;,
  4;120,118,104,105;,
  4;121,80,73,120;,
  4;121,120,105,106;,
  4;110,1,87,122;,
  4;110,122,107,94;,
  4;122,87,80,121;,
  4;122,121,106,107;,
  3;112,63,125;,
  4;112,125,125,108;,
  3;112,108,93;;
 }
 MeshTextureCoords {
  170;
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
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.100899;1.000000;,
  0.000000;1.000000;,
  0.000000;0.867761;,
  0.100007;0.866758;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.098787;0.684797;,
  0.000000;0.685030;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.096187;0.296933;,
  0.000000;0.297207;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.094197;0.000000;,
  0.095323;0.167988;,
  0.000000;0.166744;,
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
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.819629;0.859544;,
  1.000000;0.857736;,
  1.000000;1.000000;,
  0.819954;1.000000;,
  0.000000;0.000000;,
  0.819221;0.683093;,
  1.000000;0.682666;,
  0.818323;0.294877;,
  1.000000;0.294359;,
  0.817641;0.000000;,
  1.000000;0.000000;,
  1.000000;0.179799;,
  0.818051;0.177424;;
 }
}
