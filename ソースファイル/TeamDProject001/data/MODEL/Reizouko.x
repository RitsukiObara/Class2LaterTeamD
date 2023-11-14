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
 296;
 28.61840;345.88779;-113.46620;,
 35.45130;345.88779;-113.46620;,
 35.45130;339.54739;-113.46620;,
 28.61840;339.54739;-113.46620;,
 35.45130;345.88779;-113.46620;,
 35.45130;345.88779;-110.77750;,
 35.45130;339.54739;-110.77750;,
 35.45130;339.54739;-113.46620;,
 35.45130;345.88779;-110.77750;,
 28.61840;345.88779;-110.77750;,
 28.61840;339.54739;-110.77750;,
 35.45130;339.54739;-110.77750;,
 28.61840;345.88779;-110.77750;,
 28.61840;345.88779;-113.46620;,
 28.61840;339.54739;-113.46620;,
 28.61840;339.54739;-110.77750;,
 35.45130;345.88779;-113.46620;,
 28.61840;345.88779;-113.46620;,
 28.61840;339.54739;-113.46620;,
 35.45130;339.54739;-113.46620;,
 -100.00000;410.68579;-90.00000;,
 100.00000;410.68579;-90.00000;,
 100.00000;10.68580;-90.00000;,
 -100.00000;10.68580;-90.00000;,
 100.00000;410.68579;-90.00000;,
 100.00000;410.68579;90.00000;,
 100.00000;10.68580;90.00000;,
 100.00000;10.68580;-90.00000;,
 100.00000;410.68579;90.00000;,
 -100.00000;410.68579;90.00000;,
 -100.00000;10.68580;90.00000;,
 100.00000;10.68580;90.00000;,
 -100.00000;410.68579;90.00000;,
 -100.00000;410.68579;-90.00000;,
 -100.00000;10.68580;-90.00000;,
 -100.00000;10.68580;90.00000;,
 100.00000;410.68579;-90.00000;,
 -100.00000;410.68579;-90.00000;,
 -100.00000;10.68580;-90.00000;,
 100.00000;10.68580;-90.00000;,
 90.00000;24.88090;-104.47710;,
 90.00000;24.88090;-90.39950;,
 -90.00000;24.88090;-90.39950;,
 -90.00000;24.88090;-104.04530;,
 -90.00000;24.88090;-110.39950;,
 90.00000;24.88090;-110.39950;,
 -32.14070;141.32899;-105.72430;,
 -31.38090;141.32899;-110.39950;,
 -90.00000;141.32899;-110.39950;,
 -90.00000;141.32899;-106.53370;,
 -90.00000;141.32899;-90.39950;,
 -33.08070;141.32899;-90.39950;,
 90.00000;141.32899;-106.96540;,
 90.00000;141.32899;-110.39950;,
 33.77000;141.32899;-110.39950;,
 33.73030;141.32899;-105.88220;,
 33.67950;141.32899;-90.39950;,
 90.00000;141.32899;-90.39950;,
 -20.83950;132.46310;-90.39950;,
 -19.26420;132.46310;-105.78170;,
 -7.65540;141.32899;-110.39950;,
 7.23020;141.32899;-110.39950;,
 18.95960;132.46310;-105.81790;,
 17.87120;132.46310;-90.39950;,
 90.00000;127.24830;-110.39950;,
 90.00000;24.88090;-110.39950;,
 -90.00000;24.88090;-110.39950;,
 -90.00000;126.04110;-110.39950;,
 -90.00000;141.32899;-110.39950;,
 90.00000;141.32899;-110.39950;,
 -90.00000;124.59200;-90.39950;,
 -90.00000;24.88090;-90.39950;,
 90.00000;24.88090;-90.39950;,
 90.00000;125.79930;-90.39950;,
 90.00000;141.32899;-90.39950;,
 -90.00000;141.32899;-90.39950;,
 90.00000;125.79930;-90.39950;,
 90.00000;24.88090;-104.47710;,
 90.00000;126.97730;-106.65880;,
 90.00000;141.32899;-106.96540;,
 90.00000;24.88090;-110.39950;,
 90.00000;127.24830;-110.39950;,
 90.00000;141.32899;-110.39950;,
 -90.00000;126.04110;-110.39950;,
 -90.00000;24.88090;-110.39950;,
 -90.00000;24.88090;-104.04530;,
 -90.00000;125.73690;-106.20050;,
 -90.00000;141.32899;-106.53370;,
 -90.00000;141.32899;-110.39950;,
 -90.00000;124.59200;-90.39950;,
 -90.00000;401.07581;-90.39950;,
 90.00000;401.07581;-90.39950;,
 90.00000;401.07581;-110.39950;,
 -90.00000;401.07581;-110.39950;,
 73.06590;161.07581;-90.39950;,
 72.43680;161.07581;-106.40760;,
 90.00000;161.07581;-106.39420;,
 90.00000;161.07581;-90.39950;,
 72.27990;161.07581;-110.39950;,
 90.00000;161.07581;-110.39950;,
 65.67320;168.57159;-90.39950;,
 65.00330;168.57159;-106.41320;,
 64.83650;161.07581;-110.39950;,
 32.22210;168.57159;-90.39950;,
 32.09360;168.57159;-106.43820;,
 32.06180;161.07581;-110.39950;,
 17.50990;161.07581;-90.39950;,
 -90.00000;161.07581;-90.39950;,
 -90.00000;161.07581;-106.53080;,
 17.50350;161.07581;-106.44920;,
 -90.00000;161.07581;-110.39950;,
 17.50190;161.07581;-110.39950;,
 90.00000;181.13680;-110.39950;,
 90.00000;161.07581;-110.39950;,
 -90.00000;161.07581;-110.39950;,
 -90.00000;181.56461;-110.39950;,
 -90.00000;401.07581;-110.39950;,
 90.00000;401.07581;-110.39950;,
 90.00000;180.15860;-90.39950;,
 90.00000;161.07581;-110.39950;,
 90.00000;181.13680;-110.39950;,
 90.00000;401.07581;-110.39950;,
 -90.00000;180.58640;-90.39950;,
 -90.00000;161.07581;-90.39950;,
 90.00000;161.07581;-90.39950;,
 90.00000;180.15860;-90.39950;,
 90.00000;401.07581;-90.39950;,
 -90.00000;401.07581;-90.39950;,
 -90.00000;181.56461;-110.39950;,
 -90.00000;161.07581;-110.39950;,
 -90.00000;180.58640;-90.39950;,
 -90.00000;401.07581;-110.39950;,
 -73.77980;302.03351;-111.43020;,
 -33.64160;302.03351;-111.43020;,
 -33.64160;261.89539;-111.43020;,
 -73.77980;261.89539;-111.43020;,
 -81.94780;21.12760;61.09560;,
 -74.56440;21.12760;64.15400;,
 -74.56440;0.24400;64.15400;,
 -81.94780;0.24400;61.09560;,
 -71.50610;21.12760;71.53740;,
 -71.50610;0.24400;71.53740;,
 -74.56440;21.12760;78.92080;,
 -74.56440;0.24400;78.92080;,
 -81.94780;21.12760;81.97920;,
 -81.94780;0.24400;81.97920;,
 -89.33130;21.12760;78.92080;,
 -89.33130;0.24400;78.92080;,
 -92.38960;21.12760;71.53740;,
 -92.38960;0.24400;71.53740;,
 -89.33130;21.12760;64.15400;,
 -89.33130;0.24400;64.15400;,
 -81.94780;21.12760;61.09560;,
 -81.94780;0.24400;61.09560;,
 -81.94780;21.12760;71.53740;,
 -81.94780;21.12760;71.53740;,
 -81.94780;21.12760;71.53740;,
 -81.94780;21.12760;71.53740;,
 -81.94780;21.12760;71.53740;,
 -81.94780;21.12760;71.53740;,
 -81.94780;21.12760;71.53740;,
 -81.94780;21.12760;71.53740;,
 -81.94780;0.24400;71.53740;,
 -81.94780;0.24400;71.53740;,
 -81.94780;0.24400;71.53740;,
 -81.94780;0.24400;71.53740;,
 -81.94780;0.24400;71.53740;,
 -81.94780;0.24400;71.53740;,
 -81.94780;0.24400;71.53740;,
 -81.94780;0.24400;71.53740;,
 -81.94780;21.12760;-81.49740;,
 -74.56440;21.12760;-78.43900;,
 -74.56440;0.24400;-78.43900;,
 -81.94780;0.24400;-81.49740;,
 -71.50610;21.12760;-71.05560;,
 -71.50610;0.24400;-71.05560;,
 -74.56440;21.12760;-63.67220;,
 -74.56440;0.24400;-63.67220;,
 -81.94780;21.12760;-60.61380;,
 -81.94780;0.24400;-60.61380;,
 -89.33130;21.12760;-63.67220;,
 -89.33130;0.24400;-63.67220;,
 -92.38960;21.12760;-71.05560;,
 -92.38960;0.24400;-71.05560;,
 -89.33130;21.12760;-78.43900;,
 -89.33130;0.24400;-78.43900;,
 -81.94780;21.12760;-81.49740;,
 -81.94780;0.24400;-81.49740;,
 -81.94780;21.12760;-71.05560;,
 -81.94780;21.12760;-71.05560;,
 -81.94780;21.12760;-71.05560;,
 -81.94780;21.12760;-71.05560;,
 -81.94780;21.12760;-71.05560;,
 -81.94780;21.12760;-71.05560;,
 -81.94780;21.12760;-71.05560;,
 -81.94780;21.12760;-71.05560;,
 -81.94780;0.24400;-71.05560;,
 -81.94780;0.24400;-71.05560;,
 -81.94780;0.24400;-71.05560;,
 -81.94780;0.24400;-71.05560;,
 -81.94780;0.24400;-71.05560;,
 -81.94780;0.24400;-71.05560;,
 -81.94780;0.24400;-71.05560;,
 -81.94780;0.24400;-71.05560;,
 83.08780;21.12760;61.09560;,
 90.47130;21.12760;64.15400;,
 90.47130;0.24400;64.15400;,
 83.08780;0.24400;61.09560;,
 93.52960;21.12760;71.53740;,
 93.52960;0.24400;71.53740;,
 90.47130;21.12760;78.92080;,
 90.47130;0.24400;78.92080;,
 83.08780;21.12760;81.97920;,
 83.08780;0.24400;81.97920;,
 75.70440;21.12760;78.92080;,
 75.70440;0.24400;78.92080;,
 72.64610;21.12760;71.53740;,
 72.64610;0.24400;71.53740;,
 75.70440;21.12760;64.15400;,
 75.70440;0.24400;64.15400;,
 83.08780;21.12760;61.09560;,
 83.08780;0.24400;61.09560;,
 83.08780;21.12760;71.53740;,
 83.08780;21.12760;71.53740;,
 83.08780;21.12760;71.53740;,
 83.08780;21.12760;71.53740;,
 83.08780;21.12760;71.53740;,
 83.08780;21.12760;71.53740;,
 83.08780;21.12760;71.53740;,
 83.08780;21.12760;71.53740;,
 83.08780;0.24400;71.53740;,
 83.08780;0.24400;71.53740;,
 83.08780;0.24400;71.53740;,
 83.08780;0.24400;71.53740;,
 83.08780;0.24400;71.53740;,
 83.08780;0.24400;71.53740;,
 83.08780;0.24400;71.53740;,
 83.08780;0.24400;71.53740;,
 83.08780;21.12760;-81.49740;,
 90.47130;21.12760;-78.43900;,
 90.47130;0.24400;-78.43900;,
 83.08780;0.24400;-81.49740;,
 93.52960;21.12760;-71.05560;,
 93.52960;0.24400;-71.05560;,
 90.47130;21.12760;-63.67220;,
 90.47130;0.24400;-63.67220;,
 83.08780;21.12760;-60.61380;,
 83.08780;0.24400;-60.61380;,
 75.70440;21.12760;-63.67220;,
 75.70440;0.24400;-63.67220;,
 72.64610;21.12760;-71.05560;,
 72.64610;0.24400;-71.05560;,
 75.70440;21.12760;-78.43900;,
 75.70440;0.24400;-78.43900;,
 83.08780;21.12760;-81.49740;,
 83.08780;0.24400;-81.49740;,
 83.08780;21.12760;-71.05560;,
 83.08780;21.12760;-71.05560;,
 83.08780;21.12760;-71.05560;,
 83.08780;21.12760;-71.05560;,
 83.08780;21.12760;-71.05560;,
 83.08780;21.12760;-71.05560;,
 83.08780;21.12760;-71.05560;,
 83.08780;21.12760;-71.05560;,
 83.08780;0.24400;-71.05560;,
 83.08780;0.24400;-71.05560;,
 83.08780;0.24400;-71.05560;,
 83.08780;0.24400;-71.05560;,
 83.08780;0.24400;-71.05560;,
 83.08780;0.24400;-71.05560;,
 83.08780;0.24400;-71.05560;,
 83.08780;0.24400;-71.05560;,
 10.92490;344.00290;-111.43020;,
 51.06320;344.00290;-111.43020;,
 51.06320;303.86469;-111.43020;,
 10.92490;303.86469;-111.43020;,
 -56.26760;304.60980;-113.46620;,
 -49.43470;304.60980;-113.46620;,
 -49.43470;298.26941;-113.46620;,
 -56.26760;298.26941;-113.46620;,
 -49.43470;304.60980;-113.46620;,
 -49.43470;304.60980;-110.77750;,
 -49.43470;298.26941;-110.77750;,
 -49.43470;298.26941;-113.46620;,
 -49.43470;304.60980;-110.77750;,
 -56.26760;304.60980;-110.77750;,
 -56.26760;298.26941;-110.77750;,
 -49.43470;298.26941;-110.77750;,
 -56.26760;304.60980;-110.77750;,
 -56.26760;304.60980;-113.46620;,
 -56.26760;298.26941;-113.46620;,
 -56.26760;298.26941;-110.77750;,
 -49.43470;304.60980;-113.46620;,
 -56.26760;304.60980;-113.46620;,
 -56.26760;298.26941;-113.46620;,
 -49.43470;298.26941;-113.46620;;
 
 159;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;40,43,44,45;,
 4;46,47,48,49;,
 4;46,49,50,51;,
 4;52,53,54,55;,
 4;52,55,56,57;,
 4;46,51,58,59;,
 4;46,59,60,47;,
 4;55,54,61,62;,
 4;55,62,63,56;,
 4;62,61,60,59;,
 4;62,59,58,63;,
 4;64,65,66,67;,
 4;64,67,68,69;,
 4;70,71,72,73;,
 4;70,73,74,75;,
 4;76,41,77,78;,
 4;76,78,79,57;,
 4;78,77,80,81;,
 4;78,81,82,79;,
 4;83,84,85,86;,
 4;83,86,87,88;,
 4;86,85,42,89;,
 4;86,89,50,87;,
 4;90,91,92,93;,
 4;94,95,96,97;,
 4;95,98,99,96;,
 4;100,101,95,94;,
 4;101,102,98,95;,
 4;103,104,101,100;,
 4;104,105,102,101;,
 4;106,107,108,109;,
 4;106,109,104,103;,
 4;109,108,110,111;,
 4;109,111,105,104;,
 4;112,113,114,115;,
 4;112,115,116,117;,
 4;118,97,119,120;,
 4;118,120,121,91;,
 4;122,123,124,125;,
 4;122,125,126,127;,
 4;128,129,107,130;,
 4;128,130,90,131;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;137,140,141,138;,
 4;140,142,143,141;,
 4;142,144,145,143;,
 4;144,146,147,145;,
 4;146,148,149,147;,
 4;148,150,151,149;,
 4;150,152,153,151;,
 3;154,137,136;,
 3;155,140,137;,
 3;156,142,140;,
 3;157,144,142;,
 3;158,146,144;,
 3;159,148,146;,
 3;160,150,148;,
 3;161,152,150;,
 3;162,139,138;,
 3;163,138,141;,
 3;164,141,143;,
 3;165,143,145;,
 3;166,145,147;,
 3;167,147,149;,
 3;168,149,151;,
 3;169,151,153;,
 4;170,171,172,173;,
 4;171,174,175,172;,
 4;174,176,177,175;,
 4;176,178,179,177;,
 4;178,180,181,179;,
 4;180,182,183,181;,
 4;182,184,185,183;,
 4;184,186,187,185;,
 3;188,171,170;,
 3;189,174,171;,
 3;190,176,174;,
 3;191,178,176;,
 3;192,180,178;,
 3;193,182,180;,
 3;194,184,182;,
 3;195,186,184;,
 3;196,173,172;,
 3;197,172,175;,
 3;198,175,177;,
 3;199,177,179;,
 3;200,179,181;,
 3;201,181,183;,
 3;202,183,185;,
 3;203,185,187;,
 4;204,205,206,207;,
 4;205,208,209,206;,
 4;208,210,211,209;,
 4;210,212,213,211;,
 4;212,214,215,213;,
 4;214,216,217,215;,
 4;216,218,219,217;,
 4;218,220,221,219;,
 3;222,205,204;,
 3;223,208,205;,
 3;224,210,208;,
 3;225,212,210;,
 3;226,214,212;,
 3;227,216,214;,
 3;228,218,216;,
 3;229,220,218;,
 3;230,207,206;,
 3;231,206,209;,
 3;232,209,211;,
 3;233,211,213;,
 3;234,213,215;,
 3;235,215,217;,
 3;236,217,219;,
 3;237,219,221;,
 4;238,239,240,241;,
 4;239,242,243,240;,
 4;242,244,245,243;,
 4;244,246,247,245;,
 4;246,248,249,247;,
 4;248,250,251,249;,
 4;250,252,253,251;,
 4;252,254,255,253;,
 3;256,239,238;,
 3;257,242,239;,
 3;258,244,242;,
 3;259,246,244;,
 3;260,248,246;,
 3;261,250,248;,
 3;262,252,250;,
 3;263,254,252;,
 3;264,241,240;,
 3;265,240,243;,
 3;266,243,245;,
 3;267,245,247;,
 3;268,247,249;,
 3;269,249,251;,
 3;270,251,253;,
 3;271,253,255;,
 4;272,273,274,275;,
 4;276,277,278,279;,
 4;280,281,282,283;,
 4;284,285,286,287;,
 4;288,289,290,291;,
 4;288,281,292,293;,
 4;294,295,282,291;;
 
 MeshMaterialList {
  6;
  159;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  5,
  0,
  1,
  0,
  5,
  5,
  5,
  0,
  5,
  0,
  5,
  0,
  5,
  0,
  5,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  5,
  0,
  5,
  5,
  5,
  0,
  5,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  3,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.517600;0.517600;0.517600;1.000000;;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\reizouko_memo00.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\reizouko_memo01.png";
   }
  }
  Material {
   0.166400;0.166400;0.166400;1.000000;;
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
  55;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.176712;0.935449;0.306117;,
  0.302427;0.952854;0.024654;,
  -0.163174;0.945961;0.280236;,
  -0.259881;0.965595;-0.009374;,
  0.171901;0.628908;0.758238;,
  -0.160955;0.652940;0.740110;,
  0.243062;0.955687;0.166079;,
  -0.214550;0.967263;0.135539;,
  0.259173;0.864590;0.430480;,
  -0.230813;0.887556;0.398710;,
  -1.000000;0.000000;0.000000;,
  -0.130655;-0.959713;0.248758;,
  -0.385121;-0.922734;0.015622;,
  -0.259322;-0.956089;0.136551;,
  -0.278392;-0.872171;0.402264;,
  -0.131753;-0.687566;0.714068;,
  0.234255;-0.972175;-0.000982;,
  0.207708;-0.962223;0.176023;,
  0.070990;-0.687959;0.722270;,
  0.154900;-0.979170;0.131271;,
  0.071003;-0.962542;0.261671;,
  0.000002;0.000000;-1.000000;,
  0.707111;0.000000;-0.707103;,
  0.707111;0.000000;0.707102;,
  0.000002;0.000000;1.000000;,
  -0.707109;0.000000;0.707104;,
  -0.707109;0.000000;-0.707105;,
  0.000002;0.000000;-1.000000;,
  0.707111;0.000000;-0.707103;,
  1.000000;0.000000;-0.000000;,
  0.707111;0.000000;0.707102;,
  0.000002;0.000000;1.000000;,
  -0.707109;0.000000;0.707104;,
  -1.000000;0.000000;-0.000000;,
  -0.707109;0.000000;-0.707105;,
  -0.000002;0.000000;-1.000000;,
  0.707109;0.000000;-0.707105;,
  0.707109;0.000000;0.707104;,
  -0.000002;0.000000;1.000000;,
  -0.707111;0.000000;0.707102;,
  -0.707111;0.000000;-0.707103;,
  -0.000002;0.000000;-1.000000;,
  0.707109;0.000000;-0.707105;,
  1.000000;0.000000;-0.000000;,
  0.707109;0.000000;0.707104;,
  -0.000002;0.000000;1.000000;,
  -0.707111;0.000000;0.707102;,
  -1.000000;0.000000;-0.000000;,
  -0.707111;0.000000;-0.707103;,
  -0.000336;-0.468386;0.883524;;
  159;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;15,15,15,15;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;15,15,15,15;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;11,5,3,3;,
  4;11,3,3,6;,
  4;3,3,7,12;,
  4;3,12,8,3;,
  4;11,6,6,13;,
  4;11,13,9,5;,
  4;12,7,10,14;,
  4;12,14,8,8;,
  4;14,10,9,13;,
  4;14,13,6,8;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;15,15,15,15;,
  4;15,15,15,15;,
  4;15,15,15,15;,
  4;15,15,15,15;,
  4;3,3,3,3;,
  4;17,18,4,4;,
  4;18,16,4,4;,
  4;17,19,18,17;,
  4;19,20,16,18;,
  4;21,22,19,17;,
  4;54,23,20,19;,
  4;21,4,4,24;,
  4;21,24,22,21;,
  4;24,4,4,25;,
  4;24,25,23,22;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;15,15,15,15;,
  4;15,15,15,15;,
  4;0,0,0,0;,
  4;26,27,27,26;,
  4;27,1,1,27;,
  4;1,28,28,1;,
  4;28,29,29,28;,
  4;29,30,30,29;,
  4;30,15,15,30;,
  4;15,31,31,15;,
  4;31,26,26,31;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  4;32,33,33,32;,
  4;33,34,34,33;,
  4;34,35,35,34;,
  4;35,36,36,35;,
  4;36,37,37,36;,
  4;37,38,38,37;,
  4;38,39,39,38;,
  4;39,32,32,39;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  4;40,41,41,40;,
  4;41,1,1,41;,
  4;1,42,42,1;,
  4;42,43,43,42;,
  4;43,44,44,43;,
  4;44,15,15,44;,
  4;15,45,45,15;,
  4;45,40,40,45;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  4;46,47,47,46;,
  4;47,48,48,47;,
  4;48,49,49,48;,
  4;49,50,50,49;,
  4;50,51,51,50;,
  4;51,52,52,51;,
  4;52,53,53,52;,
  4;53,46,46,53;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;15,15,15,15;,
  4;3,3,3,3;,
  4;4,4,4,4;;
 }
 MeshTextureCoords {
  296;
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
  1.000000;0.556750;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.578340;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.321440;0.553020;,
  0.325660;1.000000;,
  0.000000;1.000000;,
  0.000000;0.546080;,
  0.000000;0.000000;,
  0.316220;0.000000;,
  1.000000;0.567670;,
  1.000000;1.000000;,
  0.687610;1.000000;,
  0.687390;0.560920;,
  0.687110;0.000000;,
  1.000000;0.000000;,
  0.451280;0.000000;,
  0.454720;0.555900;,
  0.457470;1.000000;,
  0.540170;1.000000;,
  0.538280;0.557700;,
  0.535900;0.000000;,
  1.000000;0.120920;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.131290;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.143730;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.133360;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.133360;,
  0.556750;1.000000;,
  0.447670;0.123250;,
  0.432330;0.000000;,
  0.000000;1.000000;,
  0.000000;0.120920;,
  0.000000;0.000000;,
  1.000000;0.131290;,
  1.000000;1.000000;,
  0.421660;1.000000;,
  0.529420;0.133900;,
  0.546080;0.000000;,
  1.000000;0.000000;,
  0.000000;0.143730;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.905920;1.000000;,
  0.902430;0.199600;,
  1.000000;0.200260;,
  1.000000;1.000000;,
  0.901560;0.000000;,
  1.000000;0.000000;,
  0.864850;1.000000;,
  0.861130;0.199320;,
  0.860200;0.000000;,
  0.679010;1.000000;,
  0.678300;0.198070;,
  0.678120;0.000000;,
  0.597280;1.000000;,
  0.000000;1.000000;,
  0.000000;0.193440;,
  0.597240;0.197520;,
  0.000000;0.000000;,
  0.597230;0.000000;,
  1.000000;0.916410;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.914630;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.920490;,
  0.000000;1.000000;,
  0.000000;0.916410;,
  0.000000;0.000000;,
  1.000000;0.918710;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.920490;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.914630;,
  1.000000;1.000000;,
  0.000000;0.918710;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
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
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
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
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
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
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
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
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
