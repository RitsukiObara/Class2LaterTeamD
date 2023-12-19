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
 294;
 -51.53000;10.49730;-38.61000;,
 54.47000;10.49730;-38.61000;,
 54.47000;-0.00270;-38.61000;,
 -51.53000;-0.00270;-38.61000;,
 54.47000;10.49730;57.99000;,
 54.47000;-0.00270;57.99000;,
 -51.53000;10.49730;57.99000;,
 -51.53000;-0.00270;57.99000;,
 0.00000;110.72000;-3.91000;,
 12.16230;110.72000;1.12780;,
 12.16230;8.57560;1.12780;,
 0.00000;8.57560;-3.91000;,
 17.20000;110.72000;13.29000;,
 17.20000;8.57560;13.29000;,
 12.16230;110.72000;25.45230;,
 12.16230;8.57560;25.45230;,
 0.00000;110.72000;30.49000;,
 0.00000;8.57560;30.49000;,
 -12.16220;110.72000;25.45230;,
 -12.16220;8.57560;25.45230;,
 -17.20000;110.72000;13.29000;,
 -17.20000;8.57560;13.29000;,
 -12.16220;110.72000;1.12780;,
 -12.16220;8.57560;1.12780;,
 0.00000;110.72000;13.29000;,
 0.00000;8.57560;13.29000;,
 -0.00350;175.31380;0.78770;,
 8.34040;175.31380;4.24380;,
 8.34040;64.61380;4.24380;,
 -0.00350;64.61380;0.78770;,
 11.79650;175.31380;12.58770;,
 11.79650;64.61380;12.58770;,
 8.34040;175.31380;20.93160;,
 8.34040;64.61380;20.93160;,
 -0.00350;175.31380;24.38770;,
 -0.00350;64.61380;24.38770;,
 -8.34730;175.31380;20.93160;,
 -8.34730;64.61380;20.93160;,
 -11.80350;175.31380;12.58770;,
 -11.80350;64.61380;12.58770;,
 -8.34730;175.31380;4.24380;,
 -8.34730;64.61380;4.24380;,
 -0.00350;175.31380;12.58770;,
 -0.00350;64.61380;12.58770;,
 -0.00350;190.47031;36.47550;,
 11.23950;185.81351;36.43490;,
 11.23950;186.22800;-11.06330;,
 -0.00350;190.88480;-11.02260;,
 15.89650;174.57080;36.33680;,
 15.89650;174.98540;-11.16140;,
 11.23950;163.32820;36.23870;,
 11.23950;163.74280;-11.25950;,
 -0.00350;158.67140;36.19800;,
 -0.00350;159.08600;-11.30010;,
 -11.24650;163.32829;36.23870;,
 -11.24650;163.74280;-11.25950;,
 -15.90350;174.57080;36.33680;,
 -15.90350;174.98540;-11.16140;,
 -11.24650;185.81351;36.43490;,
 -11.24650;186.22800;-11.06330;,
 -0.00350;174.57080;36.33680;,
 -0.00350;174.98540;-11.16140;,
 0.00000;89.32170;-36.85390;,
 60.58110;114.41520;-36.85390;,
 60.58110;114.41520;-23.83510;,
 0.00000;89.32170;-23.83510;,
 85.67460;174.99620;-36.85390;,
 85.67460;174.99620;-23.83510;,
 60.58110;235.57730;-36.85390;,
 60.58110;235.57730;-23.83510;,
 0.00000;260.67130;-36.85380;,
 0.00000;260.67120;-23.83500;,
 -60.58110;235.57730;-36.85390;,
 -60.58110;235.57730;-23.83510;,
 -85.67460;174.99620;-36.85390;,
 -85.67460;174.99620;-23.83510;,
 -60.58110;114.41520;-36.85390;,
 -60.58110;114.41520;-23.83510;,
 0.00000;97.88920;-36.85390;,
 54.52300;120.47330;-36.85390;,
 54.52300;120.47330;-10.79290;,
 0.00000;97.88910;-10.79290;,
 77.10710;174.99620;-36.85390;,
 77.10710;174.99620;-10.79290;,
 54.52300;229.51930;-36.85390;,
 54.52300;229.51920;-10.79290;,
 0.00000;252.10400;-36.85380;,
 0.00000;252.10390;-10.79280;,
 -54.52300;229.51930;-36.85390;,
 -54.52300;229.51920;-10.79290;,
 -77.10710;174.99620;-36.85390;,
 -77.10710;174.99620;-10.79290;,
 -54.52300;120.47330;-36.85390;,
 -54.52300;120.47330;-10.79290;,
 0.00000;252.10390;-17.09400;,
 -54.52300;229.51920;-17.09400;,
 54.52300;229.51920;-17.09400;,
 -77.10710;174.99620;-17.09400;,
 77.10710;174.99620;-17.09400;,
 -54.52300;120.47330;-17.09400;,
 54.52300;120.47330;-17.09400;,
 0.00000;97.88910;-17.09400;,
 -1.25940;174.99350;-4.34490;,
 -27.89270;202.25670;-1.98180;,
 -39.18480;174.99510;-1.98180;,
 -1.26240;174.99429;4.22640;,
 -0.63120;213.54910;-1.98180;,
 26.63030;202.25670;-1.98180;,
 37.92230;174.99510;-1.98180;,
 26.63030;147.73370;-1.98180;,
 -0.63120;136.44170;-1.98180;,
 -27.89270;147.73370;-1.98180;,
 0.00000;89.32170;-24.13610;,
 0.00000;89.32170;-37.15490;,
 60.58110;114.41520;-37.15490;,
 60.58110;114.41520;-24.13610;,
 85.67460;174.99620;-37.15490;,
 85.67460;174.99620;-24.13610;,
 60.58110;235.57730;-37.15490;,
 60.58110;235.57730;-24.13610;,
 0.00000;260.67120;-37.15500;,
 0.00000;260.67130;-24.13620;,
 -60.58110;235.57730;-37.15490;,
 -60.58110;235.57730;-24.13610;,
 -85.67460;174.99620;-37.15490;,
 -85.67460;174.99620;-24.13610;,
 -60.58110;114.41520;-37.15490;,
 -60.58110;114.41520;-24.13610;,
 54.52300;120.47330;-24.13610;,
 0.00000;97.88920;-24.13610;,
 0.00000;97.88910;-50.19710;,
 54.52300;120.47330;-50.19710;,
 77.10710;174.99620;-24.13610;,
 77.10710;174.99620;-50.19710;,
 54.52300;229.51930;-24.13610;,
 54.52300;229.51920;-50.19710;,
 0.00000;252.10400;-24.13620;,
 0.00000;252.10390;-50.19720;,
 -54.52300;229.51930;-24.13610;,
 -54.52300;229.51920;-50.19710;,
 -77.10710;174.99620;-24.13610;,
 -77.10710;174.99620;-50.19710;,
 -54.52300;120.47330;-24.13610;,
 -54.52300;120.47330;-50.19710;,
 0.00000;252.10390;-43.89600;,
 -54.52300;229.51920;-43.89600;,
 54.52300;229.51920;-43.89600;,
 -77.10710;174.99620;-43.89600;,
 77.10710;174.99620;-43.89600;,
 -54.52300;120.47330;-43.89600;,
 54.52300;120.47330;-43.89600;,
 0.00000;97.88910;-43.89600;,
 -58.26950;11.16490;-44.75180;,
 -58.26950;-0.67030;-44.75180;,
 61.20950;-0.67030;-44.75180;,
 61.20950;11.16490;-44.75180;,
 61.20950;-0.67030;64.13180;,
 61.20950;11.16490;64.13180;,
 -58.26950;-0.67030;64.13180;,
 -58.26950;11.16490;64.13180;,
 0.00000;82.66630;-37.34790;,
 0.00000;82.66630;-23.31770;,
 65.28720;109.70910;-23.31770;,
 65.28720;109.70910;-37.34790;,
 92.33000;174.99620;-23.31770;,
 92.33000;174.99620;-37.34790;,
 65.28720;240.28340;-23.31770;,
 65.28720;240.28340;-37.34790;,
 0.00000;267.32669;-23.31760;,
 0.00000;267.32681;-37.34780;,
 -65.28720;240.28340;-23.31770;,
 -65.28720;240.28340;-37.34790;,
 -92.33000;174.99620;-23.31770;,
 -92.33000;174.99620;-37.34790;,
 -65.28720;109.70910;-23.31770;,
 -65.28720;109.70910;-37.34790;,
 58.75850;116.23780;-37.34790;,
 0.00000;91.89930;-37.34790;,
 0.00000;91.89920;-9.26240;,
 58.75850;116.23780;-9.26240;,
 83.09700;174.99620;-37.34790;,
 83.09700;174.99620;-9.26240;,
 58.75850;233.75481;-37.34790;,
 58.75850;233.75470;-9.26240;,
 0.00000;258.09390;-37.34780;,
 0.00000;258.09381;-9.26230;,
 -58.75850;233.75481;-37.34790;,
 -58.75850;233.75470;-9.26240;,
 -83.09700;174.99620;-37.34790;,
 -83.09700;174.99620;-9.26240;,
 -58.75850;116.23780;-37.34790;,
 -58.75850;116.23780;-9.26240;,
 0.00000;258.09381;-16.05300;,
 -58.75850;233.75470;-16.05300;,
 58.75850;233.75470;-16.05300;,
 -83.09700;174.99620;-16.05300;,
 83.09700;174.99620;-16.05300;,
 -58.75850;116.23780;-16.05300;,
 58.75850;116.23780;-16.05300;,
 0.00000;91.89920;-16.05300;,
 0.00000;82.66630;-23.64210;,
 65.28720;109.70910;-23.64210;,
 65.28720;109.70910;-37.67230;,
 0.00000;82.66630;-37.67230;,
 92.33000;174.99620;-23.64210;,
 92.33000;174.99620;-37.67230;,
 65.28720;240.28340;-23.64210;,
 65.28720;240.28340;-37.67230;,
 0.00000;267.32681;-23.64220;,
 0.00000;267.32669;-37.67240;,
 -65.28720;240.28340;-23.64210;,
 -65.28720;240.28340;-37.67230;,
 -92.33000;174.99620;-23.64210;,
 -92.33000;174.99620;-37.67230;,
 -65.28720;109.70910;-23.64210;,
 -65.28720;109.70910;-37.67230;,
 0.00000;91.89930;-23.64210;,
 58.75850;116.23780;-23.64210;,
 58.75850;116.23780;-51.72760;,
 0.00000;91.89920;-51.72760;,
 83.09700;174.99620;-23.64210;,
 83.09700;174.99620;-51.72760;,
 58.75850;233.75481;-23.64210;,
 58.75850;233.75470;-51.72760;,
 0.00000;258.09390;-23.64220;,
 0.00000;258.09381;-51.72770;,
 -58.75850;233.75481;-23.64210;,
 -58.75850;233.75470;-51.72760;,
 -83.09700;174.99620;-23.64210;,
 -83.09700;174.99620;-51.72760;,
 -58.75850;116.23780;-23.64210;,
 -58.75850;116.23780;-51.72760;,
 0.00000;258.09381;-44.93700;,
 -58.75850;233.75470;-44.93700;,
 58.75850;233.75470;-44.93700;,
 -83.09700;174.99620;-44.93700;,
 83.09700;174.99620;-44.93700;,
 -58.75850;116.23780;-44.93700;,
 58.75850;116.23780;-44.93700;,
 0.00000;91.89920;-44.93700;,
 -0.00350;193.27780;40.74920;,
 -0.00350;193.76640;-15.24670;,
 13.25100;188.27650;-15.29470;,
 13.25100;187.78780;40.70140;,
 18.74110;175.02251;-15.41030;,
 18.74110;174.53371;40.58570;,
 13.25100;161.76849;-15.52600;,
 13.25100;161.27969;40.47010;,
 -0.00350;156.27850;-15.57380;,
 -0.00350;155.78979;40.42210;,
 -13.25800;161.76849;-15.52600;,
 -13.25800;161.27980;40.47010;,
 -18.74810;175.02251;-15.41030;,
 -18.74810;174.53371;40.58570;,
 -13.25800;188.27650;-15.29470;,
 -13.25800;187.78780;40.70140;,
 -0.00350;174.53371;40.58570;,
 -0.00350;175.02251;-15.41030;,
 -0.00350;181.42551;-0.51530;,
 -0.00350;58.50210;-0.51530;,
 9.26170;58.50210;3.32250;,
 9.26170;181.42551;3.32250;,
 13.09950;58.50210;12.58770;,
 13.09950;181.42551;12.58770;,
 9.26170;58.50210;21.85290;,
 9.26170;181.42551;21.85290;,
 -0.00350;58.50210;25.69060;,
 -0.00350;181.42551;25.69060;,
 -9.26860;58.50210;21.85290;,
 -9.26860;181.42551;21.85290;,
 -13.10650;58.50210;12.58770;,
 -13.10650;181.42551;12.58770;,
 -9.26860;58.50210;3.32250;,
 -9.26860;181.42551;3.32250;,
 -0.00350;181.42551;12.58770;,
 -0.00350;58.50210;12.58770;,
 0.00000;118.96300;-6.68610;,
 0.00000;0.33260;-6.68610;,
 14.12530;0.33260;-0.83520;,
 14.12530;118.96300;-0.83520;,
 19.97610;0.33260;13.29000;,
 19.97610;118.96300;13.29000;,
 14.12530;0.33260;27.41530;,
 14.12530;118.96300;27.41530;,
 0.00000;0.33260;33.26600;,
 0.00000;118.96300;33.26600;,
 -14.12520;0.33260;27.41530;,
 -14.12520;118.96300;27.41530;,
 -19.97610;0.33260;13.29000;,
 -19.97610;118.96300;13.29000;,
 -14.12520;0.33260;-0.83520;,
 -14.12520;118.96300;-0.83520;,
 0.00000;118.96300;13.29000;,
 0.00000;0.33260;13.29000;;
 
 308;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,0,3,7;,
 4;6,4,1,0;,
 4;3,2,5,7;,
 4;8,9,10,11;,
 4;9,12,13,10;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,8,11,23;,
 3;24,9,8;,
 3;24,12,9;,
 3;24,14,12;,
 3;24,16,14;,
 3;24,18,16;,
 3;24,20,18;,
 3;24,22,20;,
 3;24,8,22;,
 3;25,11,10;,
 3;25,10,13;,
 3;25,13,15;,
 3;25,15,17;,
 3;25,17,19;,
 3;25,19,21;,
 3;25,21,23;,
 3;25,23,11;,
 4;26,27,28,29;,
 4;27,30,31,28;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,26,29,41;,
 3;42,27,26;,
 3;42,30,27;,
 3;42,32,30;,
 3;42,34,32;,
 3;42,36,34;,
 3;42,38,36;,
 3;42,40,38;,
 3;42,26,40;,
 3;43,29,28;,
 3;43,28,31;,
 3;43,31,33;,
 3;43,33,35;,
 3;43,35,37;,
 3;43,37,39;,
 3;43,39,41;,
 3;43,41,29;,
 4;44,45,46,47;,
 4;45,48,49,46;,
 4;48,50,51,49;,
 4;50,52,53,51;,
 4;52,54,55,53;,
 4;54,56,57,55;,
 4;56,58,59,57;,
 4;58,44,47,59;,
 3;60,45,44;,
 3;60,48,45;,
 3;60,50,48;,
 3;60,52,50;,
 3;60,54,52;,
 3;60,56,54;,
 3;60,58,56;,
 3;60,44,58;,
 3;61,47,46;,
 3;61,46,49;,
 3;61,49,51;,
 3;61,51,53;,
 3;61,53,55;,
 3;61,55,57;,
 3;61,57,59;,
 3;61,59,47;,
 4;62,63,64,65;,
 4;63,66,67,64;,
 4;66,68,69,67;,
 4;68,70,71,69;,
 4;70,72,73,71;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 4;76,62,65,77;,
 4;62,78,79,63;,
 4;65,64,80,81;,
 4;63,79,82,66;,
 4;64,67,83,80;,
 4;66,82,84,68;,
 4;67,69,85,83;,
 4;68,84,86,70;,
 4;69,71,87,85;,
 4;70,86,88,72;,
 4;71,73,89,87;,
 4;72,88,90,74;,
 4;73,75,91,89;,
 4;74,90,92,76;,
 4;75,77,93,91;,
 4;76,92,78,62;,
 4;77,65,81,93;,
 4;94,95,88,86;,
 4;94,86,84,96;,
 4;95,97,90,88;,
 4;96,84,82,98;,
 4;97,99,92,90;,
 4;98,82,79,100;,
 4;99,101,78,92;,
 4;100,79,78,101;,
 3;97,102,99;,
 3;102,97,95;,
 3;95,94,102;,
 3;94,96,102;,
 3;98,102,96;,
 3;98,100,102;,
 3;102,100,101;,
 3;99,102,101;,
 3;103,104,105;,
 3;106,103,105;,
 3;107,106,105;,
 3;108,107,105;,
 3;109,108,105;,
 3;110,109,105;,
 3;111,105,104;,
 3;111,110,105;,
 4;89,103,106,87;,
 4;107,85,87,106;,
 4;85,107,108,83;,
 4;83,108,109,80;,
 4;110,81,80,109;,
 4;111,93,81,110;,
 4;111,104,91,93;,
 4;91,104,103,89;,
 4;112,113,114,115;,
 4;115,114,116,117;,
 4;117,116,118,119;,
 4;119,118,120,121;,
 4;121,120,122,123;,
 4;123,122,124,125;,
 4;125,124,126,127;,
 4;127,126,113,112;,
 4;112,115,128,129;,
 4;113,130,131,114;,
 4;115,117,132,128;,
 4;114,131,133,116;,
 4;117,119,134,132;,
 4;116,133,135,118;,
 4;119,121,136,134;,
 4;118,135,137,120;,
 4;121,123,138,136;,
 4;120,137,139,122;,
 4;123,125,140,138;,
 4;122,139,141,124;,
 4;125,127,142,140;,
 4;124,141,143,126;,
 4;127,112,129,142;,
 4;126,143,130,113;,
 4;144,136,138,145;,
 4;144,146,134,136;,
 4;145,138,140,147;,
 4;146,148,132,134;,
 4;147,140,142,149;,
 4;148,150,128,132;,
 4;149,142,129,151;,
 4;150,151,129,128;,
 4;152,153,154,155;,
 4;155,154,156,157;,
 4;157,156,158,159;,
 4;159,158,153,152;,
 4;159,152,155,157;,
 4;153,158,156,154;,
 4;160,161,162,163;,
 4;163,162,164,165;,
 4;165,164,166,167;,
 4;167,166,168,169;,
 4;169,168,170,171;,
 4;171,170,172,173;,
 4;173,172,174,175;,
 4;175,174,161,160;,
 4;160,163,176,177;,
 4;161,178,179,162;,
 4;163,165,180,176;,
 4;162,179,181,164;,
 4;165,167,182,180;,
 4;164,181,183,166;,
 4;167,169,184,182;,
 4;166,183,185,168;,
 4;169,171,186,184;,
 4;168,185,187,170;,
 4;171,173,188,186;,
 4;170,187,189,172;,
 4;173,175,190,188;,
 4;172,189,191,174;,
 4;175,160,177,190;,
 4;174,191,178,161;,
 4;192,184,186,193;,
 4;192,194,182,184;,
 4;193,186,188,195;,
 4;194,196,180,182;,
 4;195,188,190,197;,
 4;196,198,176,180;,
 4;197,190,177,199;,
 4;198,199,177,176;,
 4;200,201,202,203;,
 4;201,204,205,202;,
 4;204,206,207,205;,
 4;206,208,209,207;,
 4;208,210,211,209;,
 4;210,212,213,211;,
 4;212,214,215,213;,
 4;214,200,203,215;,
 4;200,216,217,201;,
 4;203,202,218,219;,
 4;201,217,220,204;,
 4;202,205,221,218;,
 4;204,220,222,206;,
 4;205,207,223,221;,
 4;206,222,224,208;,
 4;207,209,225,223;,
 4;208,224,226,210;,
 4;209,211,227,225;,
 4;210,226,228,212;,
 4;211,213,229,227;,
 4;212,228,230,214;,
 4;213,215,231,229;,
 4;214,230,216,200;,
 4;215,203,219,231;,
 4;232,233,226,224;,
 4;232,224,222,234;,
 4;233,235,228,226;,
 4;234,222,220,236;,
 4;235,237,230,228;,
 4;236,220,217,238;,
 4;237,239,216,230;,
 4;238,217,216,239;,
 4;240,241,242,243;,
 4;243,242,244,245;,
 4;245,244,246,247;,
 4;247,246,248,249;,
 4;249,248,250,251;,
 4;251,250,252,253;,
 4;253,252,254,255;,
 4;255,254,241,240;,
 3;256,240,243;,
 3;256,243,245;,
 3;256,245,247;,
 3;256,247,249;,
 3;256,249,251;,
 3;256,251,253;,
 3;256,253,255;,
 3;256,255,240;,
 3;257,242,241;,
 3;257,244,242;,
 3;257,246,244;,
 3;257,248,246;,
 3;257,250,248;,
 3;257,252,250;,
 3;257,254,252;,
 3;257,241,254;,
 4;258,259,260,261;,
 4;261,260,262,263;,
 4;263,262,264,265;,
 4;265,264,266,267;,
 4;267,266,268,269;,
 4;269,268,270,271;,
 4;271,270,272,273;,
 4;273,272,259,258;,
 3;274,258,261;,
 3;274,261,263;,
 3;274,263,265;,
 3;274,265,267;,
 3;274,267,269;,
 3;274,269,271;,
 3;274,271,273;,
 3;274,273,258;,
 3;275,260,259;,
 3;275,262,260;,
 3;275,264,262;,
 3;275,266,264;,
 3;275,268,266;,
 3;275,270,268;,
 3;275,272,270;,
 3;275,259,272;,
 4;276,277,278,279;,
 4;279,278,280,281;,
 4;281,280,282,283;,
 4;283,282,284,285;,
 4;285,284,286,287;,
 4;287,286,288,289;,
 4;289,288,290,291;,
 4;291,290,277,276;,
 3;292,276,279;,
 3;292,279,281;,
 3;292,281,283;,
 3;292,283,285;,
 3;292,285,287;,
 3;292,287,289;,
 3;292,289,291;,
 3;292,291,276;,
 3;293,278,277;,
 3;293,280,278;,
 3;293,282,280;,
 3;293,284,282;,
 3;293,286,284;,
 3;293,288,286;,
 3;293,290,288;,
 3;293,277,290;;
 
 MeshMaterialList {
  5;
  308;
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
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
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
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
   0.615200;0.615200;0.615200;1.000000;;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;1.000000;1.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\senpuki.png";
   }
  }
  Material {
   0.294000;0.294000;0.294000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  249;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000001;0.000000;-1.000000;,
  0.707108;0.000000;-0.707105;,
  1.000000;0.000000;-0.000001;,
  0.707107;0.000000;0.707107;,
  -0.000001;0.000000;1.000000;,
  -0.707105;0.000000;0.707108;,
  -1.000000;0.000000;-0.000001;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000002;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;-0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000002;0.000000;1.000000;,
  -0.707105;0.000000;0.707109;,
  -1.000000;0.000000;-0.000000;,
  -0.707105;0.000000;-0.707109;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;-0.008726;0.999962;,
  -0.000000;0.999962;0.008726;,
  0.707107;0.707080;0.006171;,
  1.000000;-0.000001;-0.000000;,
  0.707107;-0.707080;-0.006172;,
  -0.000002;-0.999962;-0.008728;,
  -0.707107;-0.707079;-0.006171;,
  -1.000000;-0.000002;-0.000000;,
  -0.707107;0.707080;0.006171;,
  0.000000;0.008726;-0.999962;,
  -0.000001;-0.008724;0.999962;,
  0.000000;-0.008723;0.999962;,
  0.000000;-0.008725;0.999962;,
  -0.000002;-0.008727;0.999962;,
  -0.000000;-0.008729;0.999962;,
  0.000002;-0.008727;0.999962;,
  0.000000;-0.008725;0.999962;,
  0.000001;-0.008724;0.999962;,
  0.000000;0.008730;-0.999962;,
  -0.000002;0.008727;-0.999962;,
  0.000000;0.008725;-0.999962;,
  -0.000001;0.008724;-0.999962;,
  0.000000;0.008723;-0.999962;,
  0.000001;0.008724;-0.999962;,
  0.000002;0.008727;-0.999962;,
  0.000000;-1.000000;-0.000000;,
  0.707107;-0.707107;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  0.707109;0.707105;0.000002;,
  0.000000;1.000000;0.000004;,
  -0.707109;0.707105;0.000002;,
  -1.000000;-0.000000;0.000000;,
  -0.707107;-0.707107;0.000000;,
  0.000000;-0.957098;0.289765;,
  0.676770;-0.676770;0.289765;,
  0.957098;-0.000000;0.289766;,
  0.676773;0.676768;0.289765;,
  0.000000;0.957098;0.289766;,
  -0.676773;0.676768;0.289765;,
  -0.957098;-0.000000;0.289766;,
  -0.676770;-0.676771;0.289765;,
  0.000000;0.000000;-1.000000;,
  -0.000001;0.000000;-1.000000;,
  0.000000;0.000001;-1.000000;,
  0.000001;0.000000;-1.000000;,
  -0.000326;-0.561845;0.827242;,
  0.396361;-0.396681;0.827974;,
  0.560323;-0.000001;0.828275;,
  0.396362;0.396677;0.827976;,
  -0.000326;0.561839;0.827247;,
  -0.398226;0.397888;0.826499;,
  -0.563398;-0.000001;0.826186;,
  -0.398225;-0.397893;0.826497;,
  0.000000;-1.000000;-0.000005;,
  0.707110;-0.707103;-0.000003;,
  -0.707110;-0.707103;-0.000003;,
  1.000000;0.000000;-0.000001;,
  -1.000000;0.000000;-0.000001;,
  0.707107;0.707107;0.000001;,
  -0.707107;0.707107;0.000001;,
  0.000000;1.000000;0.000003;,
  -0.001499;-0.000003;0.999999;,
  0.001533;0.000004;-0.999999;,
  -0.194008;-0.000001;0.981000;,
  -0.136809;0.136283;0.981178;,
  -0.000512;0.190958;0.981598;,
  0.133292;0.133789;0.982005;,
  0.187997;-0.000001;0.982170;,
  0.133294;-0.133796;0.982004;,
  -0.000512;-0.190969;0.981596;,
  -0.136812;-0.136290;0.981177;,
  1.000000;-0.000000;-0.000000;,
  0.707109;0.707105;-0.000002;,
  0.000000;1.000000;-0.000004;,
  -0.707109;0.707105;-0.000002;,
  -1.000000;-0.000000;0.000000;,
  0.000000;-0.957098;-0.289764;,
  0.676770;-0.676771;-0.289765;,
  0.957098;-0.000000;-0.289766;,
  0.676773;0.676768;-0.289765;,
  0.000000;0.957097;-0.289766;,
  -0.676773;0.676768;-0.289765;,
  -0.957098;-0.000000;-0.289766;,
  -0.676770;-0.676771;-0.289765;,
  0.000000;0.000000;1.000000;,
  -0.000001;0.000000;1.000000;,
  0.000000;0.000001;1.000000;,
  0.000001;0.000000;1.000000;,
  0.000000;-0.835799;-0.549036;,
  0.590998;-0.590999;-0.549037;,
  0.835797;-0.000000;-0.549038;,
  0.591001;0.590997;-0.549036;,
  0.000000;0.835799;-0.549036;,
  -0.591001;0.590997;-0.549036;,
  -0.835797;-0.000000;-0.549038;,
  -0.590998;-0.590999;-0.549037;,
  0.000000;-1.000000;0.000005;,
  0.707110;-0.707103;0.000003;,
  -0.707110;-0.707103;0.000003;,
  1.000000;0.000000;0.000001;,
  -1.000000;0.000000;0.000001;,
  0.707107;0.707107;-0.000001;,
  -0.707107;0.707107;-0.000001;,
  0.000000;1.000000;-0.000003;,
  0.165763;0.000001;-0.986166;,
  0.116892;0.116440;-0.986295;,
  0.116887;-0.116432;-0.986297;,
  0.000443;-0.163128;-0.986605;,
  -0.113850;-0.114282;-0.986903;,
  -0.160575;0.000001;-0.987024;,
  -0.113854;0.114289;-0.986902;,
  0.000443;0.163141;-0.986603;,
  0.000000;-0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  -0.707107;0.707107;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.707109;-0.707104;-0.000002;,
  0.000000;-1.000000;-0.000004;,
  0.707109;-0.707104;-0.000002;,
  1.000000;0.000000;0.000000;,
  0.707107;0.707107;0.000000;,
  0.000000;0.957098;-0.289765;,
  -0.676770;0.676770;-0.289766;,
  -0.957098;0.000000;-0.289766;,
  -0.676773;-0.676768;-0.289766;,
  0.000000;-0.957097;-0.289767;,
  0.676773;-0.676768;-0.289766;,
  0.957097;0.000000;-0.289766;,
  0.676770;0.676770;-0.289766;,
  0.000001;-0.000000;1.000000;,
  0.000000;-0.000001;1.000000;,
  -0.000001;-0.000000;1.000000;,
  0.000000;0.835798;-0.549037;,
  -0.590998;0.590998;-0.549038;,
  -0.835797;0.000000;-0.549039;,
  -0.591001;-0.590996;-0.549037;,
  0.000000;-0.835798;-0.549037;,
  0.591001;-0.590996;-0.549037;,
  0.835797;0.000000;-0.549039;,
  0.590998;0.590998;-0.549038;,
  0.000000;1.000000;0.000005;,
  -0.707110;0.707104;0.000003;,
  0.707110;0.707104;0.000003;,
  -1.000000;-0.000000;0.000001;,
  1.000000;-0.000000;0.000001;,
  -0.707107;-0.707107;-0.000001;,
  0.707107;-0.707107;-0.000001;,
  0.000000;-1.000000;-0.000002;,
  -1.000000;0.000000;0.000000;,
  -0.707109;-0.707104;0.000002;,
  0.000000;-1.000000;0.000004;,
  0.707109;-0.707104;0.000002;,
  1.000000;0.000000;0.000000;,
  0.000000;0.957098;0.289765;,
  -0.676770;0.676770;0.289766;,
  -0.957098;0.000000;0.289766;,
  -0.676773;-0.676768;0.289766;,
  0.000000;-0.957097;0.289767;,
  0.676773;-0.676768;0.289766;,
  0.957097;0.000000;0.289766;,
  0.676770;0.676770;0.289766;,
  0.000001;-0.000000;-1.000000;,
  0.000000;-0.000001;-1.000000;,
  -0.000001;-0.000000;-1.000000;,
  0.000000;0.835798;0.549037;,
  -0.590998;0.590998;0.549038;,
  -0.835797;0.000000;0.549039;,
  -0.591001;-0.590996;0.549037;,
  0.000000;-0.835798;0.549037;,
  0.591001;-0.590996;0.549037;,
  0.835797;0.000000;0.549039;,
  0.590998;0.590998;0.549038;,
  0.000000;1.000000;-0.000005;,
  -0.707110;0.707104;-0.000003;,
  0.707110;0.707104;-0.000003;,
  -1.000000;-0.000000;-0.000001;,
  1.000000;-0.000000;-0.000001;,
  -0.707107;-0.707107;0.000001;,
  0.707107;-0.707107;0.000001;,
  0.000000;-1.000000;0.000002;,
  0.000000;0.008725;-0.999962;,
  0.000000;-0.999962;-0.008726;,
  -0.707109;-0.707078;-0.006171;,
  -1.000000;0.000000;0.000000;,
  -0.707108;0.707078;0.006172;,
  0.000002;0.999962;0.008728;,
  0.707109;0.707078;0.006171;,
  1.000000;0.000001;-0.000000;,
  0.707109;-0.707078;-0.006171;,
  0.000000;-0.008725;0.999962;,
  0.000000;-1.000000;-0.000000;,
  0.000002;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -0.707103;0.000000;-0.707110;,
  0.000002;0.000000;-1.000000;,
  0.707102;0.000000;-0.707112;,
  1.000000;0.000000;0.000000;,
  0.707105;0.000000;0.707109;,
  0.000001;0.000000;1.000000;,
  -0.707108;0.000000;0.707106;,
  -1.000000;0.000000;0.000001;,
  -0.707105;0.000000;-0.707109;,
  0.000001;0.000000;-1.000000;,
  0.707103;0.000000;-0.707110;,
  1.000000;0.000000;0.000001;,
  0.707107;0.000000;0.707107;,
  0.000000;0.008722;-0.999962;,
  0.000003;0.008726;-0.999962;,
  0.000000;0.008725;-0.999962;,
  0.000003;0.008725;-0.999962;,
  0.000000;0.008728;-0.999962;,
  -0.000003;0.008725;-0.999962;,
  0.000000;0.008725;-0.999962;,
  -0.000003;0.008726;-0.999962;,
  0.000003;-0.008725;0.999962;,
  0.000000;-0.008728;0.999962;,
  0.000000;-0.008725;0.999962;,
  0.000003;-0.008726;0.999962;,
  0.000000;-0.008722;0.999962;,
  -0.000003;-0.008726;0.999962;,
  -0.000003;-0.008725;0.999962;;
  308;
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
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;21,22,22,21;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,17,17,24;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;16,16,16;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  3;25,25,25;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;29,30,30,29;,
  4;30,31,31,30;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;33,34,34,33;,
  4;34,27,27,34;,
  3;26,36,37;,
  3;26,38,36;,
  3;26,39,38;,
  3;26,40,39;,
  3;26,41,40;,
  3;26,42,41;,
  3;26,43,42;,
  3;26,37,43;,
  3;35,44,45;,
  3;35,45,46;,
  3;35,46,47;,
  3;35,47,48;,
  3;35,48,49;,
  3;35,49,46;,
  3;35,46,50;,
  3;35,50,44;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,57,65,64;,
  4;57,58,66,65;,
  4;58,51,59,66;,
  4;67,67,67,67;,
  4;59,60,72,71;,
  4;67,67,67,67;,
  4;60,61,73,72;,
  4;67,67,68,68;,
  4;61,62,74,73;,
  4;68,68,69,69;,
  4;62,63,75,74;,
  4;69,69,70,70;,
  4;63,64,76,75;,
  4;70,70,67,67;,
  4;64,65,77,76;,
  4;67,67,67,67;,
  4;65,66,78,77;,
  4;67,67,67,67;,
  4;66,59,71,78;,
  4;79,80,80,79;,
  4;79,79,81,81;,
  4;80,82,82,80;,
  4;81,81,83,83;,
  4;82,84,84,82;,
  4;83,83,85,85;,
  4;84,86,86,84;,
  4;85,85,86,86;,
  3;130,88,131;,
  3;88,130,132;,
  3;132,133,88;,
  3;133,134,88;,
  3;135,88,134;,
  3;135,136,88;,
  3;88,136,137;,
  3;131,88,137;,
  3;90,89,87;,
  3;91,90,87;,
  3;92,91,87;,
  3;93,92,87;,
  3;94,93,87;,
  3;95,94,87;,
  3;96,87,89;,
  3;96,95,87;,
  4;76,90,91,75;,
  4;92,74,75,91;,
  4;74,92,93,73;,
  4;73,93,94,72;,
  4;95,71,72,94;,
  4;96,78,71,95;,
  4;96,89,77,78;,
  4;77,89,90,76;,
  4;51,102,103,52;,
  4;52,103,104,97;,
  4;97,104,105,98;,
  4;98,105,106,99;,
  4;99,106,107,100;,
  4;100,107,108,101;,
  4;101,108,109,58;,
  4;58,109,102,51;,
  4;110,110,110,110;,
  4;102,114,115,103;,
  4;110,110,110,110;,
  4;103,115,116,104;,
  4;110,111,111,110;,
  4;104,116,117,105;,
  4;111,112,112,111;,
  4;105,117,118,106;,
  4;112,113,113,112;,
  4;106,118,119,107;,
  4;113,110,110,113;,
  4;107,119,120,108;,
  4;110,110,110,110;,
  4;108,120,121,109;,
  4;110,110,110,110;,
  4;109,121,114,102;,
  4;122,122,123,123;,
  4;122,124,124,122;,
  4;123,123,125,125;,
  4;124,126,126,124;,
  4;125,125,127,127;,
  4;126,128,128,126;,
  4;127,127,129,129;,
  4;128,129,129,128;,
  4;138,138,138,138;,
  4;139,139,139,139;,
  4;140,140,140,140;,
  4;224,224,224,224;,
  4;218,218,218,218;,
  4;141,141,141,141;,
  4;141,149,150,142;,
  4;142,150,151,143;,
  4;143,151,152,144;,
  4;144,152,153,145;,
  4;145,153,154,146;,
  4;146,154,155,147;,
  4;147,155,156,148;,
  4;148,156,149,141;,
  4;138,138,138,138;,
  4;149,160,161,150;,
  4;138,138,138,138;,
  4;150,161,162,151;,
  4;138,157,157,138;,
  4;151,162,163,152;,
  4;157,158,158,157;,
  4;152,163,164,153;,
  4;158,159,159,158;,
  4;153,164,165,154;,
  4;159,138,138,159;,
  4;154,165,166,155;,
  4;138,138,138,138;,
  4;155,166,167,156;,
  4;138,138,138,138;,
  4;156,167,160,149;,
  4;168,168,169,169;,
  4;168,170,170,168;,
  4;169,169,171,171;,
  4;170,172,172,170;,
  4;171,171,173,173;,
  4;172,174,174,172;,
  4;173,173,175,175;,
  4;174,175,175,174;,
  4;141,142,182,181;,
  4;142,176,183,182;,
  4;176,177,184,183;,
  4;177,178,185,184;,
  4;178,179,186,185;,
  4;179,180,187,186;,
  4;180,148,188,187;,
  4;148,141,181,188;,
  4;140,140,140,140;,
  4;181,182,193,192;,
  4;140,140,140,140;,
  4;182,183,194,193;,
  4;140,140,189,189;,
  4;183,184,195,194;,
  4;189,189,190,190;,
  4;184,185,196,195;,
  4;190,190,191,191;,
  4;185,186,197,196;,
  4;191,191,140,140;,
  4;186,187,198,197;,
  4;140,140,140,140;,
  4;187,188,199,198;,
  4;140,140,140,140;,
  4;188,181,192,199;,
  4;200,201,201,200;,
  4;200,200,202,202;,
  4;201,203,203,201;,
  4;202,202,204,204;,
  4;203,205,205,203;,
  4;204,204,206,206;,
  4;205,207,207,205;,
  4;206,206,207,207;,
  4;209,209,210,210;,
  4;210,210,211,211;,
  4;211,211,212,212;,
  4;212,212,213,213;,
  4;213,213,214,214;,
  4;214,214,215,215;,
  4;215,215,216,216;,
  4;216,216,209,209;,
  3;208,234,235;,
  3;208,235,236;,
  3;208,236,237;,
  3;208,237,238;,
  3;208,238,239;,
  3;208,239,240;,
  3;208,240,241;,
  3;208,241,234;,
  3;217,242,243;,
  3;217,244,242;,
  3;217,245,244;,
  3;217,246,245;,
  3;217,247,246;,
  3;217,244,247;,
  3;217,248,244;,
  3;217,243,248;,
  4;219,219,220,220;,
  4;220,220,139,139;,
  4;139,139,221,221;,
  4;221,221,222,222;,
  4;222,222,223,223;,
  4;223,223,224,224;,
  4;224,224,225,225;,
  4;225,225,219,219;,
  3;218,218,218;,
  3;218,218,218;,
  3;218,218,218;,
  3;218,218,218;,
  3;218,218,218;,
  3;218,218,218;,
  3;218,218,218;,
  3;218,218,218;,
  3;141,141,141;,
  3;141,141,141;,
  3;141,141,141;,
  3;141,141,141;,
  3;141,141,141;,
  3;141,141,141;,
  3;141,141,141;,
  3;141,141,141;,
  4;226,226,227,227;,
  4;227,227,228,228;,
  4;228,228,229,229;,
  4;229,229,230,230;,
  4;230,230,231,231;,
  4;231,231,232,232;,
  4;232,232,233,233;,
  4;233,233,226,226;,
  3;218,218,218;,
  3;218,218,218;,
  3;218,218,218;,
  3;218,218,218;,
  3;218,218,218;,
  3;218,218,218;,
  3;218,218,218;,
  3;218,218,218;,
  3;141,141,141;,
  3;141,141,141;,
  3;141,141,141;,
  3;141,141,141;,
  3;141,141,141;,
  3;141,141,141;,
  3;141,141,141;,
  3;141,141,141;;
 }
}
