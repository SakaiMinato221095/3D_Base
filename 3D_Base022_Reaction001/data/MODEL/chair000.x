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
 220;
 -3.41842;6.55714;-3.14708;,
 2.99093;6.55714;-3.14708;,
 2.99093;5.25523;-3.14708;,
 -3.41842;5.25523;-3.14708;,
 2.99093;6.55714;-3.14708;,
 2.99093;6.55714;3.44705;,
 2.99093;5.25523;3.44705;,
 2.99093;5.25523;-3.14708;,
 2.99093;6.55714;3.44705;,
 -3.41842;6.55714;3.44705;,
 -3.41842;5.25523;3.44705;,
 2.99093;5.25523;3.44705;,
 -3.41842;6.55714;3.44705;,
 -3.41842;6.55714;-3.14708;,
 -3.41842;5.25523;-3.14708;,
 -3.41842;5.25523;3.44705;,
 2.99093;6.55714;-3.14708;,
 -3.41842;6.55714;-3.14708;,
 -3.41842;5.25523;-3.14708;,
 2.99093;5.25523;-3.14708;,
 -3.24304;5.12550;-3.16757;,
 -2.47261;5.12550;-3.16757;,
 -2.47261;-0.02420;-3.16757;,
 -3.24304;-0.02420;-3.16757;,
 -2.47261;5.12550;-3.16757;,
 -2.46922;5.12550;-2.16250;,
 -2.46922;-0.02420;-2.16250;,
 -2.47261;-0.02420;-3.16757;,
 -2.46922;5.12550;-2.16250;,
 -3.24643;5.12550;-2.16250;,
 -3.24643;-0.02420;-2.16250;,
 -2.46922;-0.02420;-2.16250;,
 -3.24643;5.12550;-2.16250;,
 -3.24304;5.12550;-3.16757;,
 -3.24304;-0.02420;-3.16757;,
 -3.24643;-0.02420;-2.16250;,
 -2.47261;5.12550;-3.16757;,
 -3.24304;5.12550;-3.16757;,
 -3.24304;-0.02420;-3.16757;,
 -2.47261;-0.02420;-3.16757;,
 1.89009;5.12550;-3.16757;,
 2.66052;5.12550;-3.16757;,
 2.66052;-0.02420;-3.16757;,
 1.89009;-0.02420;-3.16757;,
 2.66052;5.12550;-3.16757;,
 2.66391;5.12550;-2.16250;,
 2.66391;-0.02420;-2.16250;,
 2.66052;-0.02420;-3.16757;,
 2.66391;5.12550;-2.16250;,
 1.88669;5.12550;-2.16250;,
 1.88669;-0.02420;-2.16250;,
 2.66391;-0.02420;-2.16250;,
 1.88669;5.12550;-2.16250;,
 1.89009;5.12550;-3.16757;,
 1.89009;-0.02420;-3.16757;,
 1.88669;-0.02420;-2.16250;,
 2.66052;5.12550;-3.16757;,
 1.89009;5.12550;-3.16757;,
 1.89009;-0.02420;-3.16757;,
 2.66052;-0.02420;-3.16757;,
 1.89015;5.12550;2.46413;,
 2.66057;5.12550;2.46413;,
 2.66057;-0.02420;2.46413;,
 1.89015;-0.02420;2.46413;,
 2.66057;5.12550;2.46413;,
 2.66397;5.12550;3.46920;,
 2.66397;-0.02420;3.46920;,
 2.66057;-0.02420;2.46413;,
 2.66397;5.12550;3.46920;,
 1.88675;5.12550;3.46920;,
 1.88675;-0.02420;3.46920;,
 2.66397;-0.02420;3.46920;,
 1.88675;5.12550;3.46920;,
 1.89015;5.12550;2.46413;,
 1.89015;-0.02420;2.46413;,
 1.88675;-0.02420;3.46920;,
 2.66057;5.12550;2.46413;,
 1.89015;5.12550;2.46413;,
 1.89015;-0.02420;2.46413;,
 2.66057;-0.02420;2.46413;,
 -3.31253;5.12550;2.46413;,
 -2.54210;5.12550;2.46413;,
 -2.54210;-0.02420;2.46413;,
 -3.31253;-0.02420;2.46413;,
 -2.54210;5.12550;2.46413;,
 -2.53870;5.12550;3.46920;,
 -2.53870;-0.02420;3.46920;,
 -2.54210;-0.02420;2.46413;,
 -2.53870;5.12550;3.46920;,
 -3.31593;5.12550;3.46920;,
 -3.31593;-0.02420;3.46920;,
 -2.53870;-0.02420;3.46920;,
 -3.31593;5.12550;3.46920;,
 -3.31253;5.12550;2.46413;,
 -3.31253;-0.02420;2.46413;,
 -3.31593;-0.02420;3.46920;,
 -2.54210;5.12550;2.46413;,
 -3.31253;5.12550;2.46413;,
 -3.31253;-0.02420;2.46413;,
 -2.54210;-0.02420;2.46413;,
 -2.99339;14.56011;2.48106;,
 -2.22363;14.52862;2.47660;,
 -2.19894;6.64894;2.46413;,
 -2.96936;6.64894;2.46413;,
 -2.22363;14.52862;2.47660;,
 -2.21441;14.52846;3.48163;,
 -2.19554;6.64894;3.46920;,
 -2.19894;6.64894;2.46413;,
 -2.21441;14.52846;3.48163;,
 -2.99097;14.56024;3.48612;,
 -2.97276;6.64894;3.46920;,
 -2.19554;6.64894;3.46920;,
 -2.99097;14.56024;3.48612;,
 -2.99339;14.56011;2.48106;,
 -2.96936;6.64894;2.46413;,
 -2.97276;6.64894;3.46920;,
 -2.22363;14.52862;2.47660;,
 -2.99339;14.56011;2.48106;,
 -2.96936;6.64894;2.46413;,
 -2.19894;6.64894;2.46413;,
 1.87699;14.36088;2.45283;,
 2.64676;14.32940;2.44837;,
 2.67560;6.64894;2.46413;,
 1.90518;6.64894;2.46413;,
 2.64676;14.32940;2.44837;,
 2.65598;14.32926;3.45340;,
 2.67901;6.64894;3.46920;,
 2.67560;6.64894;2.46413;,
 2.65598;14.32926;3.45340;,
 1.87942;14.36102;3.45790;,
 1.90178;6.64894;3.46920;,
 2.67901;6.64894;3.46920;,
 1.87942;14.36102;3.45790;,
 1.87699;14.36088;2.45283;,
 1.90518;6.64894;2.46413;,
 1.90178;6.64894;3.46920;,
 2.64676;14.32940;2.44837;,
 1.87699;14.36088;2.45283;,
 1.90518;6.64894;2.46413;,
 2.67560;6.64894;2.46413;,
 -3.12634;14.32500;2.51480;,
 -3.11980;15.09531;2.50269;,
 2.97590;15.09108;2.41364;,
 2.96936;14.32078;2.42576;,
 -3.11980;15.09531;2.50269;,
 -3.10673;15.11439;3.50749;,
 2.98898;15.11018;3.41845;,
 2.97590;15.09108;2.41364;,
 -3.10673;15.11439;3.50749;,
 -3.11332;14.33730;3.51971;,
 2.98239;14.33307;3.43068;,
 2.98898;15.11018;3.41845;,
 -3.11332;14.33730;3.51971;,
 -3.12634;14.32500;2.51480;,
 2.96936;14.32078;2.42576;,
 2.98239;14.33307;3.43068;,
 -3.11980;15.09531;2.50269;,
 -3.12634;14.32500;2.51480;,
 2.96936;14.32078;2.42576;,
 2.97590;15.09108;2.41364;,
 -2.80660;11.08481;2.49710;,
 -2.83147;11.85476;2.48502;,
 2.29728;12.09966;2.43131;,
 2.32215;11.32973;2.44339;,
 -2.83147;11.85476;2.48502;,
 -2.82501;11.87413;3.48989;,
 2.30375;12.11906;3.43617;,
 2.29728;12.09966;2.43131;,
 -2.82501;11.87413;3.48989;,
 -2.79991;11.09740;3.50208;,
 2.32885;11.34233;3.44836;,
 2.30375;12.11906;3.43617;,
 -2.79991;11.09740;3.50208;,
 -2.80660;11.08481;2.49710;,
 2.32215;11.32973;2.44339;,
 2.32885;11.34233;3.44836;,
 -2.83147;11.85476;2.48502;,
 -2.80660;11.08481;2.49710;,
 2.32215;11.32973;2.44339;,
 2.29728;12.09966;2.43131;,
 -2.83397;2.89030;2.49710;,
 -2.85884;3.66023;2.48502;,
 2.50145;3.90515;2.43131;,
 2.52633;3.13522;2.44339;,
 -2.85884;3.66023;2.48502;,
 -2.85238;3.67962;3.48989;,
 2.50792;3.92453;3.43617;,
 2.50145;3.90515;2.43131;,
 -2.85238;3.67962;3.48989;,
 -2.82728;2.90288;3.50208;,
 2.53302;3.14781;3.44836;,
 2.50792;3.92453;3.43617;,
 -2.82728;2.90288;3.50208;,
 -2.83397;2.89030;2.49710;,
 2.52633;3.13522;2.44339;,
 2.53302;3.14781;3.44836;,
 -2.85884;3.66023;2.48502;,
 -2.83397;2.89030;2.49710;,
 2.52633;3.13522;2.44339;,
 2.50145;3.90515;2.43131;,
 -3.03990;2.89030;-3.06049;,
 -3.06477;3.66023;-3.07257;,
 2.00349;3.90515;-3.12628;,
 2.02836;3.13522;-3.11421;,
 -3.06477;3.66023;-3.07257;,
 -3.05831;3.67962;-2.06770;,
 2.00996;3.92453;-2.12142;,
 2.00349;3.90515;-3.12628;,
 -3.05831;3.67962;-2.06770;,
 -3.03321;2.90288;-2.05551;,
 2.03506;3.14781;-2.10923;,
 2.00996;3.92453;-2.12142;,
 -3.03321;2.90288;-2.05551;,
 -3.03990;2.89030;-3.06049;,
 2.02836;3.13522;-3.11421;,
 2.03506;3.14781;-2.10923;,
 -3.06477;3.66023;-3.07257;,
 -3.03990;2.89030;-3.06049;,
 2.02836;3.13522;-3.11421;,
 2.00349;3.90515;-3.12628;;
 
 66;
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
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;92,85,96,97;,
 4;98,99,86,95;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;112,105,116,117;,
 4;118,119,106,115;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;132,125,136,137;,
 4;138,139,126,135;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;152,145,156,157;,
 4;158,159,146,155;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;172,165,176,177;,
 4;178,179,166,175;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;192,185,196,197;,
 4;198,199,186,195;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;212,205,216,217;,
 4;218,219,206,215;;
 
 MeshMaterialList {
  2;
  66;
  0,
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  1,
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
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Chair000.jpg";
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
  66;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.999994;0.000000;-0.003381;,
  0.000000;0.000000;1.000000;,
  -0.999994;0.000000;-0.003381;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.999994;0.000000;-0.003381;,
  0.000000;0.000000;1.000000;,
  -0.999994;0.000000;-0.003380;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.999994;0.000000;-0.003380;,
  0.000000;0.000000;1.000000;,
  -0.999994;0.000000;-0.003380;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.999994;0.000000;-0.003380;,
  0.000000;0.000000;1.000000;,
  -0.999994;0.000000;-0.003380;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.002856;0.001852;-0.999994;,
  0.999977;0.002774;-0.006278;,
  0.002852;-0.001852;0.999994;,
  -0.999996;-0.002669;-0.000484;,
  0.040878;0.999164;-0.000223;,
  0.000000;-1.000000;-0.000000;,
  -0.002926;-0.001770;-0.999994;,
  0.999975;0.003364;-0.006280;,
  0.002926;0.001769;0.999994;,
  -0.999995;-0.003278;-0.000480;,
  0.040863;0.999165;-0.000239;,
  0.000000;-1.000000;-0.000000;,
  -0.014615;-0.015597;-0.999772;,
  0.000415;0.999819;-0.019006;,
  0.014615;0.015607;0.999771;,
  -0.000514;-0.999925;0.012243;,
  -0.999880;0.008692;0.012849;,
  0.999880;-0.008693;-0.012853;,
  -0.009708;-0.015999;-0.999825;,
  -0.047889;0.998673;-0.018955;,
  0.009707;0.016006;0.999825;,
  0.047824;-0.998781;0.012196;,
  -0.999457;-0.032183;0.007049;,
  0.999457;0.032177;-0.007057;,
  -0.009289;-0.015986;-0.999829;,
  -0.045824;0.998769;-0.018970;,
  0.009289;0.015993;0.999829;,
  0.045763;-0.998878;0.012207;,
  -0.999457;-0.032179;0.007051;,
  0.999457;0.032183;-0.007060;,
  -0.009824;-0.016002;-0.999824;,
  -0.048458;0.998645;-0.018951;,
  0.009824;0.016009;0.999824;,
  0.048394;-0.998754;0.012188;,
  -0.999457;-0.032178;0.007051;,
  0.999457;0.032183;-0.007061;;
  66;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
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
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;65,65,65,65;;
 }
 MeshTextureCoords {
  220;
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
