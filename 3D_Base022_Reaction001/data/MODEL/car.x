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
 174;
 -3.03000;1.12838;-6.54141;,
 0.00000;1.12235;-7.57945;,
 0.00000;0.00000;-9.16337;,
 -2.19991;0.00000;-8.77887;,
 3.03000;1.12838;-6.54141;,
 2.19991;0.00000;-8.77887;,
 0.00000;-2.98578;-9.13249;,
 -2.10474;-2.91165;-7.68256;,
 2.10474;-2.91165;-7.68256;,
 2.78245;2.18609;-4.89002;,
 4.34970;0.00000;-5.13793;,
 3.58760;2.88047;-2.52345;,
 4.45403;0.00000;-2.52345;,
 3.46876;2.77397;0.21370;,
 4.05871;0.00000;0.41533;,
 2.42009;2.15383;2.63831;,
 2.55676;0.00000;3.09420;,
 3.51666;-2.89140;-5.99182;,
 4.09761;-2.63577;-0.56199;,
 3.61313;-1.32110;0.37711;,
 3.16390;-2.77588;2.03001;,
 0.00000;2.32344;2.98130;,
 0.00000;0.00000;3.93786;,
 -2.42009;2.15383;2.63831;,
 -2.55676;0.00000;3.09420;,
 0.00000;-2.90098;3.01596;,
 -3.16390;-2.77588;2.03001;,
 -3.46876;2.77397;0.21370;,
 -4.05871;0.00000;0.41533;,
 -3.58760;2.88047;-2.52345;,
 -4.45403;0.00000;-2.52345;,
 -2.78245;2.18609;-4.89002;,
 -4.34970;0.00000;-5.13793;,
 -3.61313;-1.32110;0.37711;,
 -4.09761;-2.63577;-0.56199;,
 -3.51666;-2.89140;-5.99182;,
 0.00000;3.06136;0.41533;,
 0.00000;3.20524;-2.52345;,
 0.00000;2.86319;-4.82894;,
 0.00000;-3.13704;1.05435;,
 0.00000;-3.32616;-2.52345;,
 0.00000;-3.14792;-5.00000;,
 3.93646;-2.39451;-0.47783;,
 3.96326;-1.74803;-0.23369;,
 4.16557;-1.83378;-0.14482;,
 4.12194;-2.40840;-0.36414;,
 3.93209;-1.46094;0.39468;,
 4.14596;-1.57854;0.41614;,
 3.86121;-1.70140;1.03920;,
 4.07458;-1.79220;0.99012;,
 3.79213;-2.32856;1.32231;,
 3.99325;-2.34960;1.24090;,
 3.76532;-2.97503;1.07818;,
 3.94962;-2.92422;1.02158;,
 3.79649;-3.26212;0.44980;,
 3.96923;-3.17946;0.46062;,
 3.86738;-3.02166;-0.19472;,
 4.00884;-2.96293;-0.11601;,
 3.86429;-2.36153;0.42224;,
 4.02583;-2.37613;0.43573;,
 3.80391;-2.33848;-0.59570;,
 3.85278;-1.83310;-0.47468;,
 4.11563;-1.90984;-0.45080;,
 4.06677;-2.41522;-0.57182;,
 3.86697;-1.45327;-0.11695;,
 4.12983;-1.53001;-0.09306;,
 3.84269;-1.30078;0.38165;,
 4.10555;-1.37752;0.40553;,
 3.78644;-1.41647;0.88751;,
 4.04930;-1.49321;0.91139;,
 3.71329;-1.76936;1.26508;,
 3.97615;-1.84610;1.28897;,
 3.64285;-2.26488;1.41321;,
 3.90571;-2.34162;1.43709;,
 3.59398;-2.77026;1.29219;,
 3.85684;-2.84700;1.31607;,
 3.57979;-3.15008;0.93445;,
 3.84265;-3.22682;0.95834;,
 3.60407;-3.30258;0.43586;,
 3.86693;-3.37931;0.45974;,
 3.66032;-3.18688;-0.07000;,
 3.92318;-3.26362;-0.04612;,
 3.73347;-2.83400;-0.44758;,
 3.99633;-2.91074;-0.42369;,
 3.72338;-2.30168;0.40875;,
 3.98624;-2.37842;0.43264;,
 -4.12194;-2.40840;-0.36414;,
 -4.16557;-1.83378;-0.14482;,
 -3.96326;-1.74803;-0.23369;,
 -3.93646;-2.39451;-0.47783;,
 -4.14596;-1.57854;0.41614;,
 -3.93209;-1.46094;0.39468;,
 -4.07458;-1.79220;0.99012;,
 -3.86121;-1.70140;1.03920;,
 -3.99325;-2.34960;1.24090;,
 -3.79213;-2.32856;1.32231;,
 -3.94962;-2.92422;1.02158;,
 -3.76532;-2.97503;1.07818;,
 -3.96923;-3.17946;0.46062;,
 -3.79649;-3.26212;0.44980;,
 -4.00884;-2.96293;-0.11601;,
 -3.86738;-3.02166;-0.19472;,
 -3.86429;-2.36153;0.42224;,
 -4.02583;-2.37613;0.43573;,
 -4.06677;-2.41522;-0.57182;,
 -4.11563;-1.90984;-0.45080;,
 -3.85278;-1.83310;-0.47468;,
 -3.80391;-2.33848;-0.59570;,
 -4.12983;-1.53001;-0.09306;,
 -3.86697;-1.45327;-0.11695;,
 -4.10555;-1.37752;0.40553;,
 -3.84269;-1.30078;0.38165;,
 -4.04930;-1.49321;0.91139;,
 -3.78644;-1.41647;0.88751;,
 -3.97615;-1.84610;1.28897;,
 -3.71329;-1.76936;1.26508;,
 -3.90571;-2.34162;1.43709;,
 -3.64285;-2.26488;1.41321;,
 -3.85684;-2.84700;1.31607;,
 -3.59398;-2.77026;1.29219;,
 -3.84265;-3.22682;0.95834;,
 -3.57979;-3.15008;0.93445;,
 -3.86693;-3.37931;0.45974;,
 -3.60407;-3.30258;0.43586;,
 -3.92318;-3.26362;-0.04612;,
 -3.66032;-3.18688;-0.07000;,
 -3.99633;-2.91074;-0.42369;,
 -3.73347;-2.83400;-0.44758;,
 -3.72338;-2.30168;0.40875;,
 -3.98624;-2.37842;0.43264;,
 3.77164;-2.39451;-6.61848;,
 3.84249;-1.74803;-6.38332;,
 4.05761;-1.83378;-6.33280;,
 3.97474;-2.40840;-6.54049;,
 3.92636;-1.46094;-5.75978;,
 4.14055;-1.57854;-5.77766;,
 3.97411;-1.70140;-5.11314;,
 4.17497;-1.79220;-5.20028;,
 3.95779;-2.32856;-4.82218;,
 4.14070;-2.34960;-4.93888;,
 3.88694;-2.97503;-5.05735;,
 4.05783;-2.92422;-5.14658;,
 3.80307;-3.26212;-5.68088;,
 3.97489;-3.17946;-5.70172;,
 3.75532;-3.02166;-6.32752;,
 3.90876;-2.96293;-6.27592;,
 3.86471;-2.36153;-5.72033;,
 4.02600;-2.37613;-5.73651;,
 3.61984;-2.33848;-6.71023;,
 3.68994;-1.83310;-6.60014;,
 3.95275;-1.90984;-6.62455;,
 3.88265;-2.41522;-6.73464;,
 3.76909;-1.45327;-6.25098;,
 4.03190;-1.53001;-6.27540;,
 3.83607;-1.30078;-5.75631;,
 4.09889;-1.37752;-5.78072;,
 3.87295;-1.41647;-5.24867;,
 4.13577;-1.49321;-5.27309;,
 3.86984;-1.76936;-4.86409;,
 4.13265;-1.84610;-4.88850;,
 3.82756;-2.26488;-4.70560;,
 4.09038;-2.34162;-4.73002;,
 3.75747;-2.77026;-4.81569;,
 4.02027;-2.84700;-4.84011;,
 3.67832;-3.15008;-5.16485;,
 3.94113;-3.22682;-5.18927;,
 3.61133;-3.30258;-5.65952;,
 3.87414;-3.37931;-5.68394;,
 3.57445;-3.18688;-6.16716;,
 3.83726;-3.26362;-6.19158;,
 3.57757;-2.83400;-6.55175;,
 3.84038;-2.91074;-6.57616;,
 3.72370;-2.30168;-5.70792;,
 3.98651;-2.37842;-5.73233;;
 
 221;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;3,2,6,7;,
 4;2,5,8,6;,
 4;4,9,10,5;,
 4;9,11,12,10;,
 4;11,13,14,12;,
 4;13,15,16,14;,
 4;5,10,17,8;,
 4;10,12,18,17;,
 4;12,14,19,18;,
 4;14,16,20,19;,
 4;15,21,22,16;,
 4;21,23,24,22;,
 4;16,22,25,20;,
 4;22,24,26,25;,
 4;23,27,28,24;,
 4;27,29,30,28;,
 4;29,31,32,30;,
 4;24,28,33,26;,
 4;28,30,34,33;,
 4;30,32,35,34;,
 4;32,3,7,35;,
 4;23,21,36,27;,
 4;21,15,13,36;,
 4;27,36,37,29;,
 4;36,13,11,37;,
 4;29,37,38,31;,
 4;37,11,9,38;,
 4;31,38,1,0;,
 4;38,9,4,1;,
 4;33,39,25,26;,
 4;39,19,20,25;,
 4;34,40,39,33;,
 4;40,18,19,39;,
 4;35,41,40,34;,
 4;41,17,18,40;,
 4;7,6,41,35;,
 4;6,8,17,41;,
 4;0,3,32,31;,
 3;0,4,1;,
 4;42,43,44,45;,
 4;43,46,47,44;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 4;50,52,53,51;,
 4;52,54,55,53;,
 4;54,56,57,55;,
 4;56,42,45,57;,
 3;58,43,42;,
 3;58,46,43;,
 3;58,48,46;,
 3;58,50,48;,
 3;58,52,50;,
 3;58,54,52;,
 3;58,56,54;,
 3;58,42,56;,
 3;59,45,44;,
 3;59,44,47;,
 3;59,47,49;,
 3;59,49,51;,
 3;59,51,53;,
 3;59,53,55;,
 3;59,55,57;,
 3;59,57,45;,
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
 3;84,61,60;,
 3;84,64,61;,
 3;84,66,64;,
 3;84,68,66;,
 3;84,70,68;,
 3;84,72,70;,
 3;84,74,72;,
 3;84,76,74;,
 3;84,78,76;,
 3;84,80,78;,
 3;84,82,80;,
 3;84,60,82;,
 3;85,63,62;,
 3;85,62,65;,
 3;85,65,67;,
 3;85,67,69;,
 3;85,69,71;,
 3;85,71,73;,
 3;85,73,75;,
 3;85,75,77;,
 3;85,77,79;,
 3;85,79,81;,
 3;85,81,83;,
 3;85,83,63;,
 4;86,87,88,89;,
 4;87,90,91,88;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,100,101,99;,
 4;100,86,89,101;,
 3;89,88,102;,
 3;88,91,102;,
 3;91,93,102;,
 3;93,95,102;,
 3;95,97,102;,
 3;97,99,102;,
 3;99,101,102;,
 3;101,89,102;,
 3;87,86,103;,
 3;90,87,103;,
 3;92,90,103;,
 3;94,92,103;,
 3;96,94,103;,
 3;98,96,103;,
 3;100,98,103;,
 3;86,100,103;,
 4;104,105,106,107;,
 4;105,108,109,106;,
 4;108,110,111,109;,
 4;110,112,113,111;,
 4;112,114,115,113;,
 4;114,116,117,115;,
 4;116,118,119,117;,
 4;118,120,121,119;,
 4;120,122,123,121;,
 4;122,124,125,123;,
 4;124,126,127,125;,
 4;126,104,107,127;,
 3;107,106,128;,
 3;106,109,128;,
 3;109,111,128;,
 3;111,113,128;,
 3;113,115,128;,
 3;115,117,128;,
 3;117,119,128;,
 3;119,121,128;,
 3;121,123,128;,
 3;123,125,128;,
 3;125,127,128;,
 3;127,107,128;,
 3;105,104,129;,
 3;108,105,129;,
 3;110,108,129;,
 3;112,110,129;,
 3;114,112,129;,
 3;116,114,129;,
 3;118,116,129;,
 3;120,118,129;,
 3;122,120,129;,
 3;124,122,129;,
 3;126,124,129;,
 3;104,126,129;,
 4;130,131,132,133;,
 4;131,134,135,132;,
 4;134,136,137,135;,
 4;136,138,139,137;,
 4;138,140,141,139;,
 4;140,142,143,141;,
 4;142,144,145,143;,
 4;144,130,133,145;,
 3;146,131,130;,
 3;146,134,131;,
 3;146,136,134;,
 3;146,138,136;,
 3;146,140,138;,
 3;146,142,140;,
 3;146,144,142;,
 3;146,130,144;,
 3;147,133,132;,
 3;147,132,135;,
 3;147,135,137;,
 3;147,137,139;,
 3;147,139,141;,
 3;147,141,143;,
 3;147,143,145;,
 3;147,145,133;,
 4;148,149,150,151;,
 4;149,152,153,150;,
 4;152,154,155,153;,
 4;154,156,157,155;,
 4;156,158,159,157;,
 4;158,160,161,159;,
 4;160,162,163,161;,
 4;162,164,165,163;,
 4;164,166,167,165;,
 4;166,168,169,167;,
 4;168,170,171,169;,
 4;170,148,151,171;,
 3;172,149,148;,
 3;172,152,149;,
 3;172,154,152;,
 3;172,156,154;,
 3;172,158,156;,
 3;172,160,158;,
 3;172,162,160;,
 3;172,164,162;,
 3;172,166,164;,
 3;172,168,166;,
 3;172,170,168;,
 3;172,148,170;,
 3;173,151,150;,
 3;173,150,153;,
 3;173,153,155;,
 3;173,155,157;,
 3;173,157,159;,
 3;173,159,161;,
 3;173,161,163;,
 3;173,163,165;,
 3;173,165,167;,
 3;173,167,169;,
 3;173,169,171;,
 3;173,171,151;;
 
 MeshMaterialList {
  4;
  221;
  1,
  1,
  1,
  1,
  1,
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
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
   0.102660;0.092220;0.374970;0.710000;;
   5.000000;
   0.560000;0.560000;0.560000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   4.000000;
   0.620000;0.620000;0.620000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.489600;0.496000;0.470400;0.960000;;
   56.000000;
   0.360000;0.360000;0.360000;;
   0.373320;0.378200;0.358680;;
  }
 }
 MeshNormals {
  249;
  -0.307396;0.866011;-0.394377;,
  0.000000;0.899057;-0.437832;,
  -0.506079;0.708741;-0.491498;,
  0.000000;0.841860;-0.539696;,
  -0.612925;-0.179306;-0.769527;,
  0.000000;-0.179084;-0.983834;,
  0.307396;0.866011;-0.394377;,
  0.555415;0.746493;-0.366418;,
  0.934355;0.351031;-0.061301;,
  0.933438;0.223761;0.280402;,
  0.683888;0.443966;-0.578958;,
  0.934457;0.135013;-0.329487;,
  0.995666;0.092245;0.011833;,
  0.950683;0.057390;0.304808;,
  0.612925;-0.179306;-0.769527;,
  0.920238;-0.213975;-0.327684;,
  0.981432;-0.172540;0.083795;,
  0.816693;-0.388851;0.426388;,
  0.479202;0.574128;0.663885;,
  0.000000;0.720307;0.693656;,
  0.649068;0.024961;0.760321;,
  0.000000;0.005845;0.999983;,
  0.659145;-0.216792;0.720090;,
  0.000000;-0.300573;0.953759;,
  -0.479202;0.574128;0.663885;,
  -0.933438;0.223761;0.280402;,
  -0.934355;0.351031;-0.061301;,
  -0.555415;0.746493;-0.366418;,
  -0.649068;0.024961;0.760321;,
  -0.950683;0.057390;0.304808;,
  -0.995666;0.092245;0.011833;,
  -0.934457;0.135013;-0.329487;,
  -0.659145;-0.216792;0.720090;,
  -0.816693;-0.388851;0.426388;,
  -0.981432;-0.172540;0.083795;,
  -0.920238;-0.213975;-0.327684;,
  0.000000;0.986331;0.164774;,
  0.000000;0.995759;-0.092004;,
  0.000000;0.923660;-0.383213;,
  0.000000;-0.991095;0.133157;,
  0.000000;-0.967464;0.253007;,
  0.000000;-0.999545;-0.030153;,
  0.372353;-0.166206;-0.913088;,
  -0.094896;0.981880;0.164031;,
  0.094896;0.981880;0.164031;,
  -0.124797;0.987974;-0.091284;,
  0.124797;0.987974;-0.091284;,
  -0.187594;-0.947907;-0.257449;,
  0.000000;-0.965040;-0.262103;,
  0.187594;-0.947907;-0.257449;,
  -0.207651;-0.946377;0.247492;,
  0.207651;-0.946377;0.247492;,
  -0.082175;-0.996165;-0.030051;,
  0.082175;-0.996165;-0.030051;,
  -0.061844;-0.997311;-0.039316;,
  0.000000;-0.999224;-0.039392;,
  0.061844;-0.997311;-0.039316;,
  -0.993977;0.072311;-0.082343;,
  0.537460;-0.071612;-0.840243;,
  0.525679;0.579979;-0.622323;,
  0.487373;0.873165;0.007087;,
  0.423331;0.626746;0.654202;,
  0.375497;-0.003901;0.926815;,
  0.374725;-0.634032;0.676449;,
  0.438039;-0.896523;0.066088;,
  0.510113;-0.666235;-0.543982;,
  0.864851;-0.433260;-0.253610;,
  0.990498;-0.114264;0.076539;,
  -0.989758;0.115718;-0.083594;,
  0.079853;-0.036494;-0.996138;,
  0.210864;0.452633;-0.866406;,
  0.283897;0.815414;-0.504482;,
  0.281279;0.959543;-0.012604;,
  0.204763;0.851576;0.482587;,
  0.072969;0.515650;0.853687;,
  -0.079851;0.036495;0.996138;,
  -0.210862;-0.452640;0.866403;,
  -0.283887;-0.815419;0.504481;,
  -0.281262;-0.959548;0.012606;,
  -0.204755;-0.851580;-0.482584;,
  -0.072971;-0.515655;-0.853683;,
  0.989758;-0.115717;0.083592;,
  0.993977;0.072311;-0.082343;,
  -0.537460;-0.071612;-0.840243;,
  -0.525679;0.579979;-0.622323;,
  -0.487373;0.873165;0.007087;,
  -0.423331;0.626746;0.654202;,
  -0.375497;-0.003901;0.926815;,
  -0.374725;-0.634032;0.676449;,
  -0.438039;-0.896523;0.066088;,
  -0.510113;-0.666235;-0.543982;,
  -0.864851;-0.433260;-0.253610;,
  -0.990498;-0.114264;0.076539;,
  0.989758;0.115718;-0.083594;,
  -0.079853;-0.036494;-0.996138;,
  -0.210864;0.452633;-0.866406;,
  -0.283897;0.815414;-0.504482;,
  -0.281279;0.959543;-0.012604;,
  -0.204763;0.851576;0.482587;,
  -0.072969;0.515650;0.853687;,
  0.079851;0.036495;0.996138;,
  0.210862;-0.452640;0.866403;,
  0.283887;-0.815419;0.504481;,
  0.281262;-0.959548;0.012606;,
  0.204755;-0.851580;-0.482584;,
  0.072971;-0.515655;-0.853683;,
  -0.989758;-0.115717;0.083592;,
  -0.993977;0.072307;-0.082346;,
  -0.993977;0.072308;-0.082349;,
  -0.993978;0.072311;-0.082338;,
  -0.993978;0.072313;-0.082335;,
  -0.993977;0.072315;-0.082338;,
  -0.993977;0.072313;-0.082340;,
  -0.993977;0.072310;-0.082345;,
  -0.993977;0.072311;-0.082349;,
  0.983342;-0.133333;0.123534;,
  0.984657;-0.133809;0.112005;,
  0.985623;-0.146378;0.084382;,
  0.989137;-0.135863;0.056124;,
  0.993143;-0.108409;0.043758;,
  0.995294;-0.080090;0.054545;,
  0.996178;-0.068509;0.054193;,
  -0.989758;0.115719;-0.083596;,
  -0.989758;0.115719;-0.083592;,
  -0.989759;0.115715;-0.083594;,
  -0.989758;0.115719;-0.083591;,
  -0.989758;0.115720;-0.083595;,
  -0.989759;0.115715;-0.083594;,
  -0.989759;0.115718;-0.083591;,
  -0.989758;0.115720;-0.083594;,
  -0.989758;0.115716;-0.083595;,
  -0.989758;0.115718;-0.083591;,
  -0.989758;0.115720;-0.083595;,
  -0.989758;0.115716;-0.083595;,
  0.989760;-0.115708;0.083591;,
  0.989759;-0.115715;0.083586;,
  0.989759;-0.115721;0.083586;,
  0.989758;-0.115718;0.083592;,
  0.989758;-0.115719;0.083595;,
  0.989759;-0.115715;0.083594;,
  0.989758;-0.115719;0.083592;,
  0.989758;-0.115720;0.083595;,
  0.989758;-0.115717;0.083594;,
  0.989758;-0.115720;0.083591;,
  0.989758;-0.115721;0.083596;,
  0.989758;-0.115716;0.083595;,
  0.993977;0.072308;-0.082349;,
  0.993977;0.072307;-0.082346;,
  0.993978;0.072311;-0.082338;,
  0.993978;0.072313;-0.082335;,
  0.993977;0.072315;-0.082338;,
  0.993977;0.072313;-0.082340;,
  0.993977;0.072310;-0.082345;,
  0.993977;0.072311;-0.082349;,
  -0.984657;-0.133809;0.112005;,
  -0.983342;-0.133333;0.123534;,
  -0.985623;-0.146378;0.084382;,
  -0.989137;-0.135863;0.056124;,
  -0.993143;-0.108409;0.043758;,
  -0.995294;-0.080090;0.054545;,
  -0.996178;-0.068509;0.054193;,
  0.989758;0.115719;-0.083592;,
  0.989758;0.115719;-0.083596;,
  0.989759;0.115715;-0.083594;,
  0.989758;0.115719;-0.083591;,
  0.989758;0.115720;-0.083595;,
  0.989759;0.115715;-0.083594;,
  0.989759;0.115718;-0.083591;,
  0.989758;0.115720;-0.083594;,
  0.989758;0.115716;-0.083595;,
  0.989758;0.115718;-0.083591;,
  0.989758;0.115720;-0.083595;,
  0.989758;0.115716;-0.083595;,
  -0.989759;-0.115715;0.083586;,
  -0.989760;-0.115708;0.083591;,
  -0.989759;-0.115721;0.083586;,
  -0.989758;-0.115718;0.083592;,
  -0.989758;-0.115719;0.083595;,
  -0.989759;-0.115715;0.083594;,
  -0.989758;-0.115719;0.083592;,
  -0.989758;-0.115720;0.083595;,
  -0.989758;-0.115717;0.083594;,
  -0.989758;-0.115720;0.083591;,
  -0.989758;-0.115721;0.083596;,
  -0.989758;-0.115716;0.083595;,
  -0.992338;0.072310;0.100178;,
  0.375327;-0.071615;-0.924122;,
  0.403478;0.579971;-0.707699;,
  0.480509;0.873162;-0.081847;,
  0.535464;0.626745;0.566100;,
  0.538112;-0.003905;0.842864;,
  0.491726;-0.634035;0.596829;,
  0.442740;-0.896527;-0.014843;,
  0.402415;-0.666238;-0.627845;,
  0.804151;-0.433258;-0.406975;,
  0.987860;-0.114262;-0.105244;,
  -0.988419;0.115717;0.098175;,
  -0.102980;-0.036496;-0.994014;,
  0.049467;0.452629;-0.890326;,
  0.187209;0.815414;-0.547771;,
  0.274264;0.959546;-0.063649;,
  0.289266;0.851580;0.437191;,
  0.227310;0.515654;0.826094;,
  0.103008;0.036496;0.994011;,
  -0.049444;-0.452642;0.890320;,
  -0.187195;-0.815420;0.547767;,
  -0.274253;-0.959549;0.063652;,
  -0.289267;-0.851581;-0.437189;,
  -0.227304;-0.515657;-0.826094;,
  0.988418;-0.115721;-0.098176;,
  -0.992338;0.072317;0.100177;,
  -0.992339;0.072307;0.100175;,
  -0.992338;0.072319;0.100174;,
  -0.992338;0.072311;0.100179;,
  -0.992338;0.072306;0.100187;,
  -0.992338;0.072309;0.100186;,
  -0.992339;0.072308;0.100176;,
  -0.992340;0.072303;0.100171;,
  0.989389;-0.133328;-0.057730;,
  0.988580;-0.133813;-0.069303;,
  0.984496;-0.146380;-0.096646;,
  0.982800;-0.135867;-0.125078;,
  0.984486;-0.108413;-0.137965;,
  0.988568;-0.080087;-0.127746;,
  0.989374;-0.068500;-0.128243;,
  -0.988419;0.115719;0.098174;,
  -0.988419;0.115715;0.098172;,
  -0.988419;0.115718;0.098170;,
  -0.988419;0.115715;0.098172;,
  -0.988418;0.115714;0.098182;,
  -0.988418;0.115724;0.098177;,
  -0.988419;0.115716;0.098171;,
  -0.988419;0.115707;0.098177;,
  -0.988418;0.115717;0.098182;,
  -0.988418;0.115716;0.098182;,
  -0.988418;0.115721;0.098174;,
  -0.988419;0.115720;0.098169;,
  0.988419;-0.115715;-0.098172;,
  0.988418;-0.115719;-0.098174;,
  0.988418;-0.115724;-0.098177;,
  0.988417;-0.115725;-0.098181;,
  0.988417;-0.115728;-0.098178;,
  0.988418;-0.115724;-0.098177;,
  0.988417;-0.115725;-0.098181;,
  0.988418;-0.115720;-0.098174;,
  0.988419;-0.115711;-0.098175;,
  0.988418;-0.115716;-0.098182;,
  0.988418;-0.115720;-0.098173;,
  0.988419;-0.115719;-0.098169;;
  221;
  4;0,1,3,2;,
  4;1,6,10,3;,
  4;4,5,5,4;,
  4;5,42,14,5;,
  4;6,7,11,10;,
  4;7,8,12,11;,
  4;8,9,13,12;,
  4;9,18,20,13;,
  4;10,11,15,14;,
  4;11,12,16,15;,
  4;12,13,17,16;,
  4;13,20,22,17;,
  4;18,19,21,20;,
  4;19,24,28,21;,
  4;20,21,23,22;,
  4;21,28,32,23;,
  4;24,25,29,28;,
  4;25,26,30,29;,
  4;26,27,31,30;,
  4;28,29,33,32;,
  4;29,30,34,33;,
  4;30,31,35,34;,
  4;31,4,4,35;,
  4;24,19,36,43;,
  4;19,18,44,36;,
  4;43,36,37,45;,
  4;36,44,46,37;,
  4;45,37,38,27;,
  4;37,46,7,38;,
  4;27,38,1,0;,
  4;38,7,6,1;,
  4;47,39,48,47;,
  4;39,49,49,48;,
  4;50,40,39,33;,
  4;40,51,17,39;,
  4;52,41,40,50;,
  4;41,53,51,40;,
  4;54,55,41,52;,
  4;55,56,53,41;,
  4;0,2,31,27;,
  3;0,6,1;,
  4;58,59,59,58;,
  4;59,60,60,59;,
  4;60,61,61,60;,
  4;61,62,62,61;,
  4;62,63,63,62;,
  4;63,64,64,63;,
  4;64,65,66,64;,
  4;65,58,58,66;,
  3;57,107,108;,
  3;57,109,107;,
  3;57,110,109;,
  3;57,111,110;,
  3;57,112,111;,
  3;57,113,112;,
  3;57,114,113;,
  3;57,108,114;,
  3;67,115,116;,
  3;67,116,117;,
  3;67,117,118;,
  3;67,118,119;,
  3;67,119,120;,
  3;67,120,121;,
  3;67,121,66;,
  3;67,66,115;,
  4;69,70,70,69;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,80,80,79;,
  4;80,69,69,80;,
  3;68,122,123;,
  3;68,124,122;,
  3;68,125,124;,
  3;68,126,125;,
  3;68,127,126;,
  3;68,128,127;,
  3;68,129,128;,
  3;68,130,129;,
  3;68,131,130;,
  3;68,132,131;,
  3;68,133,132;,
  3;68,123,133;,
  3;81,134,135;,
  3;81,135,136;,
  3;81,136,137;,
  3;81,137,138;,
  3;81,138,139;,
  3;81,139,140;,
  3;81,140,141;,
  3;81,141,142;,
  3;81,142,143;,
  3;81,143,144;,
  3;81,144,145;,
  3;81,145,134;,
  4;83,84,84,83;,
  4;84,85,85,84;,
  4;85,86,86,85;,
  4;86,87,87,86;,
  4;87,88,88,87;,
  4;88,89,89,88;,
  4;89,91,90,89;,
  4;91,83,83,90;,
  3;146,147,82;,
  3;147,148,82;,
  3;148,149,82;,
  3;149,150,82;,
  3;150,151,82;,
  3;151,152,82;,
  3;152,153,82;,
  3;153,146,82;,
  3;154,155,92;,
  3;156,154,92;,
  3;157,156,92;,
  3;158,157,92;,
  3;159,158,92;,
  3;160,159,92;,
  3;91,160,92;,
  3;155,91,92;,
  4;94,95,95,94;,
  4;95,96,96,95;,
  4;96,97,97,96;,
  4;97,98,98,97;,
  4;98,99,99,98;,
  4;99,100,100,99;,
  4;100,101,101,100;,
  4;101,102,102,101;,
  4;102,103,103,102;,
  4;103,104,104,103;,
  4;104,105,105,104;,
  4;105,94,94,105;,
  3;161,162,93;,
  3;162,163,93;,
  3;163,164,93;,
  3;164,165,93;,
  3;165,166,93;,
  3;166,167,93;,
  3;167,168,93;,
  3;168,169,93;,
  3;169,170,93;,
  3;170,171,93;,
  3;171,172,93;,
  3;172,161,93;,
  3;173,174,106;,
  3;175,173,106;,
  3;176,175,106;,
  3;177,176,106;,
  3;178,177,106;,
  3;179,178,106;,
  3;180,179,106;,
  3;181,180,106;,
  3;182,181,106;,
  3;183,182,106;,
  3;184,183,106;,
  3;174,184,106;,
  4;186,187,187,186;,
  4;187,188,188,187;,
  4;188,189,189,188;,
  4;189,190,190,189;,
  4;190,191,191,190;,
  4;191,192,192,191;,
  4;192,193,194,192;,
  4;193,186,186,194;,
  3;185,210,211;,
  3;185,212,210;,
  3;185,213,212;,
  3;185,214,213;,
  3;185,215,214;,
  3;185,216,215;,
  3;185,217,216;,
  3;185,211,217;,
  3;195,218,219;,
  3;195,219,220;,
  3;195,220,221;,
  3;195,221,222;,
  3;195,222,223;,
  3;195,223,224;,
  3;195,224,194;,
  3;195,194,218;,
  4;197,198,198,197;,
  4;198,199,199,198;,
  4;199,200,200,199;,
  4;200,201,201,200;,
  4;201,202,202,201;,
  4;202,203,203,202;,
  4;203,204,204,203;,
  4;204,205,205,204;,
  4;205,206,206,205;,
  4;206,207,207,206;,
  4;207,208,208,207;,
  4;208,197,197,208;,
  3;196,225,226;,
  3;196,227,225;,
  3;196,228,227;,
  3;196,229,228;,
  3;196,230,229;,
  3;196,231,230;,
  3;196,232,231;,
  3;196,233,232;,
  3;196,234,233;,
  3;196,235,234;,
  3;196,236,235;,
  3;196,226,236;,
  3;209,237,238;,
  3;209,238,239;,
  3;209,239,240;,
  3;209,240,241;,
  3;209,241,242;,
  3;209,242,243;,
  3;209,243,244;,
  3;209,244,245;,
  3;209,245,246;,
  3;209,246,247;,
  3;209,247,248;,
  3;209,248,237;;
 }
}
