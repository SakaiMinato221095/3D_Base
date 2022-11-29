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
 376;
 -1.60153;46.68996;1.49345;,
 1.60153;46.68996;1.49345;,
 1.60153;-0.42240;1.49345;,
 -1.60153;-0.42240;1.49345;,
 1.60153;46.68996;1.49345;,
 1.60153;46.68996;-1.49345;,
 1.60153;-0.42240;-1.49345;,
 1.60153;-0.42240;1.49345;,
 1.60153;46.68996;-1.49345;,
 -1.60153;46.68996;-1.49345;,
 -1.60153;-0.42240;-1.49345;,
 1.60153;-0.42240;-1.49345;,
 -1.60153;46.68996;-1.49345;,
 -1.60153;46.68996;1.49345;,
 -1.60153;-0.42240;1.49345;,
 -1.60153;-0.42240;-1.49345;,
 1.60153;46.68996;1.49345;,
 -1.60153;46.68996;1.49345;,
 -1.60153;-0.42240;1.49345;,
 1.60153;-0.42240;1.49345;,
 -25.99050;35.11008;1.42464;,
 25.99050;35.11008;1.42464;,
 25.99050;32.11946;1.42464;,
 -25.99050;32.11946;1.42464;,
 25.99050;35.11008;1.42464;,
 25.99050;35.11008;-1.42464;,
 25.99050;32.11946;-1.42464;,
 25.99050;32.11946;1.42464;,
 25.99050;35.11008;-1.42464;,
 -25.99050;35.11008;-1.42464;,
 -25.99050;32.11946;-1.42464;,
 25.99050;32.11946;-1.42464;,
 -25.99050;35.11008;-1.42464;,
 -25.99050;35.11008;1.42464;,
 -25.99050;32.11946;1.42464;,
 -25.99050;32.11946;-1.42464;,
 25.99050;35.11008;1.42464;,
 -25.99050;35.11008;1.42464;,
 -25.99050;32.11946;1.42464;,
 25.99050;32.11946;1.42464;,
 -18.95611;35.39752;-3.95730;,
 -4.27423;35.39752;-5.33892;,
 -4.27423;31.30184;-5.33892;,
 -18.95611;31.30184;-3.95730;,
 -0.67666;35.39752;-5.33892;,
 -0.67666;31.30184;-5.33892;,
 4.27423;35.39752;-5.33892;,
 4.27423;31.30184;-5.33892;,
 18.95611;35.39752;-3.95730;,
 18.95611;31.30184;-3.95730;,
 -4.27423;27.20615;-5.33892;,
 -10.75755;27.20615;-3.95730;,
 -0.67666;27.20615;-5.33892;,
 4.27423;27.20615;-5.33892;,
 10.75755;27.20615;-3.95730;,
 -4.27423;23.11046;-5.33892;,
 -10.75755;23.11046;-3.95730;,
 -0.67666;23.11046;-5.33892;,
 4.27423;23.11046;-5.33892;,
 10.75755;23.11046;-3.95730;,
 -4.27423;11.67541;-5.33892;,
 -10.75755;19.01476;-3.95730;,
 -0.67666;11.67541;-5.33892;,
 4.27423;11.67541;-5.33892;,
 10.75755;19.01476;-3.95730;,
 18.95611;35.39752;-3.95730;,
 17.93115;35.39752;-1.87883;,
 17.93115;31.30184;-1.87883;,
 18.95611;31.30184;-3.95730;,
 18.04810;35.39752;0.19963;,
 18.04810;31.30184;0.19963;,
 17.93115;35.39752;2.27810;,
 17.93115;31.30184;2.27810;,
 17.60279;35.39752;4.35657;,
 17.60279;31.30184;4.35657;,
 9.40424;27.20615;-1.87883;,
 10.75755;27.20615;-3.95730;,
 9.40424;27.20615;0.19963;,
 9.40424;27.20615;2.27810;,
 9.40424;27.20615;4.35657;,
 9.40424;23.11046;-1.87883;,
 10.75755;23.11046;-3.95730;,
 9.40424;23.11046;0.19963;,
 9.40424;23.11046;2.27810;,
 9.40424;23.11046;4.35657;,
 9.40424;19.01476;-1.87883;,
 10.75755;19.01476;-3.95730;,
 9.40424;19.01476;0.19963;,
 9.40424;19.01476;2.27810;,
 9.40424;19.01476;4.35657;,
 17.60279;35.39752;4.35657;,
 2.92092;35.39752;6.02223;,
 2.92092;31.30184;6.02223;,
 17.60279;31.30184;4.35657;,
 -0.67666;35.39752;6.02223;,
 -0.67666;31.30184;6.02223;,
 -2.92092;35.39752;6.02223;,
 -2.92092;31.30184;6.02223;,
 -17.60279;35.39752;4.35657;,
 -17.60279;31.30184;4.35657;,
 2.92092;27.20615;6.02223;,
 9.40424;27.20615;4.35657;,
 -0.67666;27.20615;6.02223;,
 -2.92092;27.20615;6.02223;,
 -9.40424;27.20615;4.35657;,
 2.92092;23.11046;6.02223;,
 9.40424;23.11046;4.35657;,
 -0.67666;23.11046;6.02223;,
 -2.92092;23.11046;6.02223;,
 -9.40424;23.11046;4.35657;,
 2.92092;11.67541;6.02223;,
 9.40424;19.01476;4.35657;,
 -0.67666;11.67541;6.02223;,
 -2.92092;11.67541;6.02223;,
 -9.40424;19.01476;4.35657;,
 -17.60279;35.39752;4.35657;,
 -17.93115;35.39752;2.27810;,
 -17.93115;31.30184;2.27810;,
 -17.60279;31.30184;4.35657;,
 -18.04810;35.39752;0.19963;,
 -18.04810;31.30184;0.19963;,
 -17.93115;35.39752;-1.87883;,
 -17.93115;31.30184;-1.87883;,
 -18.95611;35.39752;-3.95730;,
 -18.95611;31.30184;-3.95730;,
 -9.40424;27.20615;2.27810;,
 -9.40424;27.20615;4.35657;,
 -9.40424;27.20615;0.19963;,
 -9.40424;27.20615;-1.87883;,
 -10.75755;27.20615;-3.95730;,
 -9.40424;23.11046;2.27810;,
 -9.40424;23.11046;4.35657;,
 -9.40424;23.11046;0.19963;,
 -9.40424;23.11046;-1.87883;,
 -10.75755;23.11046;-3.95730;,
 -9.40424;19.01476;2.27810;,
 -9.40424;19.01476;4.35657;,
 -9.40424;19.01476;0.19963;,
 -9.40424;19.01476;-1.87883;,
 -10.75755;19.01476;-3.95730;,
 -2.92092;35.39752;6.02223;,
 -4.27423;35.39752;3.57600;,
 -17.93115;35.39752;2.27810;,
 -0.67666;35.39752;3.57600;,
 2.92092;35.39752;6.02223;,
 4.27423;35.39752;3.57600;,
 17.93115;35.39752;2.27810;,
 -4.27423;35.39752;0.19963;,
 -18.04810;35.39752;0.19963;,
 -0.67666;35.39752;0.19963;,
 4.27423;35.39752;0.19963;,
 18.04810;35.39752;0.19963;,
 -4.27423;35.39752;-3.26045;,
 -17.93115;35.39752;-1.87883;,
 -0.67666;35.39752;-3.26045;,
 4.27423;35.39752;-3.26045;,
 17.93115;35.39752;-1.87883;,
 -4.27423;35.39752;-5.33892;,
 -18.95611;35.39752;-3.95730;,
 -0.67666;35.39752;-5.33892;,
 4.27423;35.39752;-5.33892;,
 18.95611;35.39752;-3.95730;,
 -9.40424;19.01476;2.27810;,
 -4.27423;11.67541;3.57600;,
 -2.92092;11.67541;6.02223;,
 -0.67666;11.67541;3.57600;,
 4.27423;11.67541;3.57600;,
 2.92092;11.67541;6.02223;,
 9.40424;19.01476;2.27810;,
 -9.40424;19.01476;0.19963;,
 -4.27423;11.67541;0.19963;,
 -0.67666;11.67541;0.19963;,
 4.27423;11.67541;0.19963;,
 9.40424;19.01476;0.19963;,
 -9.40424;19.01476;-1.87883;,
 -4.27423;11.67541;-3.26045;,
 -0.67666;11.67541;-3.26045;,
 4.27423;11.67541;-3.26045;,
 9.40424;19.01476;-1.87883;,
 -10.75755;19.01476;-3.95730;,
 -4.27423;11.67541;-5.33892;,
 -0.67666;11.67541;-5.33892;,
 4.27423;11.67541;-5.33892;,
 10.75755;19.01476;-3.95730;,
 -6.19073;51.80710;-8.00452;,
 0.00000;54.54438;-8.00452;,
 0.00000;47.27029;-10.75505;,
 -8.08125;47.27029;-6.28389;,
 6.19073;51.80710;-8.00452;,
 8.08125;47.27029;-6.28389;,
 0.00000;40.83112;-7.93974;,
 -5.64309;41.95973;-7.36047;,
 5.64309;41.95973;-7.36047;,
 6.19073;51.80710;-8.00452;,
 7.23113;54.50144;-0.12934;,
 10.79608;47.27029;-0.12934;,
 8.08125;47.27029;-6.28389;,
 5.18822;52.27482;7.10179;,
 8.75318;47.27029;7.10179;,
 7.23113;40.03920;-0.12934;,
 5.64309;41.95973;-7.36047;,
 5.18822;42.30220;7.10179;,
 5.18822;52.27482;7.10179;,
 0.00000;55.01207;7.10179;,
 0.00000;47.27029;9.82080;,
 8.75318;47.27029;7.10179;,
 -5.18822;52.27482;7.10179;,
 -8.75318;47.27029;7.10179;,
 0.00000;41.17358;7.10179;,
 5.18822;42.30220;7.10179;,
 -5.18822;42.30220;7.10179;,
 -5.18822;52.27482;7.10179;,
 -7.23113;54.50144;-0.12934;,
 -10.79608;47.27029;-0.12934;,
 -8.75318;47.27029;7.10179;,
 -6.19073;51.80710;-8.00452;,
 -8.08125;47.27029;-6.28389;,
 -7.23113;40.03920;-0.12934;,
 -5.18822;42.30220;7.10179;,
 -5.64309;41.95973;-7.36047;,
 0.00000;57.23868;-0.12934;,
 -7.23113;54.50144;-0.12934;,
 7.23113;54.50144;-0.12934;,
 0.00000;54.54438;-8.00452;,
 -6.19073;51.80710;-8.00452;,
 6.19073;51.80710;-8.00452;,
 -7.23113;40.03920;-0.12934;,
 0.00000;38.91057;-0.12934;,
 7.23113;40.03920;-0.12934;,
 -5.64309;41.95973;-7.36047;,
 0.00000;40.83112;-7.93974;,
 5.64309;41.95973;-7.36047;,
 -6.02500;57.24152;-5.48833;,
 0.00000;57.24152;-7.82635;,
 0.00000;54.09837;-15.93774;,
 -9.55102;54.09837;-13.60508;,
 6.02500;57.24152;-5.48833;,
 9.55102;54.09837;-13.60508;,
 0.00000;51.45276;-15.93774;,
 -10.66499;51.45276;-14.23967;,
 10.66499;51.45276;-14.23967;,
 6.02500;57.24152;-5.48833;,
 6.45919;57.24152;0.07681;,
 15.58171;54.09837;0.07681;,
 9.55102;54.09837;-13.60508;,
 5.88635;57.24152;5.25228;,
 10.66499;54.09837;11.77976;,
 15.58171;51.45276;0.07681;,
 10.66499;51.45276;-14.23967;,
 10.66499;51.45276;11.77976;,
 5.88635;57.24152;5.25228;,
 0.00000;57.24152;7.50225;,
 0.00000;54.09837;14.70469;,
 10.66499;54.09837;11.77976;,
 -5.88635;57.24152;5.25228;,
 -10.66499;54.09837;11.77976;,
 0.00000;51.45276;14.70469;,
 10.66499;51.45276;11.77976;,
 -10.66499;51.45276;11.77976;,
 -5.88635;57.24152;5.25228;,
 -6.45919;57.24152;0.07681;,
 -15.58171;54.09837;0.07681;,
 -10.66499;54.09837;11.77976;,
 -6.02500;57.24152;-5.48833;,
 -9.55102;54.09837;-13.60508;,
 -15.58171;51.45276;0.07681;,
 -10.66499;51.45276;11.77976;,
 -10.66499;51.45276;-14.23967;,
 0.00000;58.15673;0.07681;,
 -6.45919;57.24152;0.07681;,
 6.45919;57.24152;0.07681;,
 0.00000;57.24152;-7.82635;,
 -6.02500;57.24152;-5.48833;,
 6.02500;57.24152;-5.48833;,
 -15.58171;51.45276;0.07681;,
 0.00000;51.45276;0.07681;,
 15.58171;51.45276;0.07681;,
 -10.66499;51.45276;-14.23967;,
 0.00000;51.45276;-15.93774;,
 10.66499;51.45276;-14.23967;,
 23.99660;36.17399;-1.91520;,
 25.58246;36.86907;-1.91520;,
 25.58246;33.72019;-3.03780;,
 23.00349;33.72019;-1.91520;,
 29.51747;36.17399;-1.91520;,
 30.15583;33.72019;-1.91520;,
 25.58246;30.12747;-1.91520;,
 23.99660;31.34246;-1.91520;,
 29.51747;31.34246;-1.91520;,
 29.51747;36.17399;-1.91520;,
 30.34525;36.17399;0.03655;,
 31.33836;33.72019;0.03655;,
 30.15583;33.72019;-1.91520;,
 29.51747;36.17399;1.65949;,
 30.22924;33.72019;1.65949;,
 30.34525;31.34246;0.03655;,
 29.51747;31.34246;-1.91520;,
 29.51747;31.34246;1.65949;,
 29.51747;36.17399;1.65949;,
 25.58246;36.86907;1.65949;,
 25.58246;33.72019;2.33409;,
 30.22924;33.72019;1.65949;,
 23.99660;36.17399;1.65949;,
 23.22345;33.72019;1.65949;,
 25.58246;30.12747;1.65949;,
 29.51747;31.34246;1.65949;,
 23.99660;31.34246;1.65949;,
 23.99660;36.17399;1.65949;,
 23.16880;36.17399;0.03655;,
 23.04923;33.72019;0.03655;,
 23.22345;33.72019;1.65949;,
 23.99660;36.17399;-1.91520;,
 23.00349;33.72019;-1.91520;,
 23.16880;31.34246;0.03655;,
 23.99660;31.34246;1.65949;,
 23.99660;31.34246;-1.91520;,
 25.58246;36.86907;0.03655;,
 23.16880;36.17399;0.03655;,
 30.34525;36.17399;0.03655;,
 25.58246;36.86907;-1.91520;,
 23.99660;36.17399;-1.91520;,
 29.51747;36.17399;-1.91520;,
 23.16880;31.34246;0.03655;,
 25.58246;30.12747;0.03655;,
 30.34525;31.34246;0.03655;,
 23.99660;31.34246;-1.91520;,
 25.58246;30.12747;-1.91520;,
 29.51747;31.34246;-1.91520;,
 -25.12184;36.17399;1.87684;,
 -26.70770;36.86907;1.87684;,
 -26.70770;33.72019;2.99944;,
 -24.12874;33.72019;1.87684;,
 -30.64271;36.17399;1.87684;,
 -31.28107;33.72019;1.87684;,
 -26.70770;30.12747;1.87684;,
 -25.12184;31.34246;1.87684;,
 -30.64271;31.34246;1.87684;,
 -30.64271;36.17399;1.87684;,
 -31.47049;36.17399;-0.07492;,
 -32.46360;33.72019;-0.07492;,
 -31.28107;33.72019;1.87684;,
 -30.64271;36.17399;-1.69785;,
 -31.35447;33.72019;-1.69785;,
 -31.47049;31.34246;-0.07492;,
 -30.64271;31.34246;1.87684;,
 -30.64271;31.34246;-1.69785;,
 -30.64271;36.17399;-1.69785;,
 -26.70770;36.86907;-1.69785;,
 -26.70770;33.72019;-2.37245;,
 -31.35447;33.72019;-1.69785;,
 -25.12184;36.17399;-1.69785;,
 -24.34869;33.72019;-1.69785;,
 -26.70770;30.12747;-1.69785;,
 -30.64271;31.34246;-1.69785;,
 -25.12184;31.34246;-1.69785;,
 -25.12184;36.17399;-1.69785;,
 -24.29404;36.17399;-0.07492;,
 -24.17447;33.72019;-0.07492;,
 -24.34869;33.72019;-1.69785;,
 -25.12184;36.17399;1.87684;,
 -24.12874;33.72019;1.87684;,
 -24.29404;31.34246;-0.07492;,
 -25.12184;31.34246;-1.69785;,
 -25.12184;31.34246;1.87684;,
 -26.70770;36.86907;-0.07492;,
 -24.29404;36.17399;-0.07492;,
 -31.47049;36.17399;-0.07492;,
 -26.70770;36.86907;1.87684;,
 -25.12184;36.17399;1.87684;,
 -30.64271;36.17399;1.87684;,
 -24.29404;31.34246;-0.07492;,
 -26.70770;30.12747;-0.07492;,
 -31.47049;31.34246;-0.07492;,
 -25.12184;31.34246;1.87684;,
 -26.70770;30.12747;1.87684;,
 -30.64271;31.34246;1.87684;;
 
 204;
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
 4;41,44,45,42;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;43,42,50,51;,
 4;42,45,52,50;,
 4;45,47,53,52;,
 4;47,49,54,53;,
 4;51,50,55,56;,
 4;50,52,57,55;,
 4;52,53,58,57;,
 4;53,54,59,58;,
 4;56,55,60,61;,
 4;55,57,62,60;,
 4;57,58,63,62;,
 4;58,59,64,63;,
 4;65,66,67,68;,
 4;66,69,70,67;,
 4;69,71,72,70;,
 4;71,73,74,72;,
 4;68,67,75,76;,
 4;67,70,77,75;,
 4;70,72,78,77;,
 4;72,74,79,78;,
 4;76,75,80,81;,
 4;75,77,82,80;,
 4;77,78,83,82;,
 4;78,79,84,83;,
 4;81,80,85,86;,
 4;80,82,87,85;,
 4;82,83,88,87;,
 4;83,84,89,88;,
 4;90,91,92,93;,
 4;91,94,95,92;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;93,92,100,101;,
 4;92,95,102,100;,
 4;95,97,103,102;,
 4;97,99,104,103;,
 4;101,100,105,106;,
 4;100,102,107,105;,
 4;102,103,108,107;,
 4;103,104,109,108;,
 4;106,105,110,111;,
 4;105,107,112,110;,
 4;107,108,113,112;,
 4;108,109,114,113;,
 4;115,116,117,118;,
 4;116,119,120,117;,
 4;119,121,122,120;,
 4;121,123,124,122;,
 4;118,117,125,126;,
 4;117,120,127,125;,
 4;120,122,128,127;,
 4;122,124,129,128;,
 4;126,125,130,131;,
 4;125,127,132,130;,
 4;127,128,133,132;,
 4;128,129,134,133;,
 4;131,130,135,136;,
 4;130,132,137,135;,
 4;132,133,138,137;,
 4;133,134,139,138;,
 4;115,140,141,142;,
 4;140,94,143,141;,
 4;94,144,145,143;,
 4;144,73,146,145;,
 4;142,141,147,148;,
 4;141,143,149,147;,
 4;143,145,150,149;,
 4;145,146,151,150;,
 4;148,147,152,153;,
 4;147,149,154,152;,
 4;149,150,155,154;,
 4;150,151,156,155;,
 4;153,152,157,158;,
 4;152,154,159,157;,
 4;154,155,160,159;,
 4;155,156,161,160;,
 4;162,163,164,136;,
 4;163,165,112,164;,
 4;165,166,167,112;,
 4;166,168,89,167;,
 4;169,170,163,162;,
 4;170,171,165,163;,
 4;171,172,166,165;,
 4;172,173,168,166;,
 4;174,175,170,169;,
 4;175,176,171,170;,
 4;176,177,172,171;,
 4;177,178,173,172;,
 4;179,180,175,174;,
 4;180,181,176,175;,
 4;181,182,177,176;,
 4;182,183,178,177;,
 4;184,185,186,187;,
 4;185,188,189,186;,
 4;187,186,190,191;,
 4;186,189,192,190;,
 4;193,194,195,196;,
 4;194,197,198,195;,
 4;196,195,199,200;,
 4;195,198,201,199;,
 4;202,203,204,205;,
 4;203,206,207,204;,
 4;205,204,208,209;,
 4;204,207,210,208;,
 4;211,212,213,214;,
 4;212,215,216,213;,
 4;214,213,217,218;,
 4;213,216,219,217;,
 4;211,203,220,221;,
 4;203,197,222,220;,
 4;221,220,223,224;,
 4;220,222,225,223;,
 4;226,227,208,218;,
 4;227,228,201,208;,
 4;229,230,227,226;,
 4;230,231,228,227;,
 4;232,233,234,235;,
 4;233,236,237,234;,
 4;235,234,238,239;,
 4;234,237,240,238;,
 4;241,242,243,244;,
 4;242,245,246,243;,
 4;244,243,247,248;,
 4;243,246,249,247;,
 4;250,251,252,253;,
 4;251,254,255,252;,
 4;253,252,256,257;,
 4;252,255,258,256;,
 4;259,260,261,262;,
 4;260,263,264,261;,
 4;262,261,265,266;,
 4;261,264,267,265;,
 4;259,251,268,269;,
 4;251,245,270,268;,
 4;269,268,271,272;,
 4;268,270,273,271;,
 4;274,275,256,266;,
 4;275,276,249,256;,
 4;277,278,275,274;,
 4;278,279,276,275;,
 4;280,281,282,283;,
 4;281,284,285,282;,
 4;283,282,286,287;,
 4;282,285,288,286;,
 4;289,290,291,292;,
 4;290,293,294,291;,
 4;292,291,295,296;,
 4;291,294,297,295;,
 4;298,299,300,301;,
 4;299,302,303,300;,
 4;301,300,304,305;,
 4;300,303,306,304;,
 4;307,308,309,310;,
 4;308,311,312,309;,
 4;310,309,313,314;,
 4;309,312,315,313;,
 4;307,299,316,317;,
 4;299,293,318,316;,
 4;317,316,319,320;,
 4;316,318,321,319;,
 4;322,323,304,314;,
 4;323,324,297,304;,
 4;325,326,323,322;,
 4;326,327,324,323;,
 4;328,329,330,331;,
 4;329,332,333,330;,
 4;331,330,334,335;,
 4;330,333,336,334;,
 4;337,338,339,340;,
 4;338,341,342,339;,
 4;340,339,343,344;,
 4;339,342,345,343;,
 4;346,347,348,349;,
 4;347,350,351,348;,
 4;349,348,352,353;,
 4;348,351,354,352;,
 4;355,356,357,358;,
 4;356,359,360,357;,
 4;358,357,361,362;,
 4;357,360,363,361;,
 4;355,347,364,365;,
 4;347,341,366,364;,
 4;365,364,367,368;,
 4;364,366,369,367;,
 4;370,371,352,362;,
 4;371,372,345,352;,
 4;373,374,371,370;,
 4;374,375,372,371;;
 
 MeshMaterialList {
  5;
  204;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.800000;0.599200;0.486400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.464000;0.489600;0.207200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.230000;0.230000;0.230000;;
  }
  Material {
   0.618400;0.800000;0.612000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.420000;0.329600;0.266400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  232;
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.093690;0.000000;-0.995601;,
  -0.046897;0.000000;-0.998900;,
  0.000000;0.000000;-1.000000;,
  0.046897;0.000000;-0.998900;,
  -0.122607;-0.046429;-0.991369;,
  -0.061390;-0.023247;-0.997843;,
  0.061390;-0.023247;-0.997843;,
  -0.180057;-0.046428;-0.982560;,
  -0.090356;-0.023298;-0.995637;,
  0.090356;-0.023298;-0.995637;,
  -0.208424;0.000000;-0.978039;,
  -0.104789;0.000000;-0.994494;,
  0.104789;0.000000;-0.994494;,
  -0.208424;0.000000;-0.978039;,
  -0.104789;0.000000;-0.994495;,
  0.104789;0.000000;-0.994495;,
  0.093690;0.000000;-0.995601;,
  0.979874;0.000000;0.199615;,
  1.000000;0.000000;-0.000000;,
  0.994340;0.000000;0.106247;,
  0.122607;-0.046429;-0.991369;,
  0.180057;-0.046428;-0.982560;,
  0.432254;-0.894176;0.116640;,
  0.430582;-0.902551;-0.000000;,
  0.435158;-0.900058;0.023095;,
  0.208424;0.000000;-0.978039;,
  0.958650;0.000000;0.284589;,
  1.000000;0.000000;0.000000;,
  0.208424;0.000000;-0.978039;,
  0.923168;-0.324621;0.205868;,
  0.953842;-0.300311;-0.000000;,
  0.951587;-0.302541;0.054332;,
  0.987750;0.000000;0.156046;,
  0.056454;0.000000;0.998405;,
  0.000000;0.000000;1.000000;,
  -0.056454;0.000000;0.998405;,
  0.073725;-0.027867;0.996889;,
  -0.073725;-0.027867;0.996889;,
  0.439700;-0.897496;0.034142;,
  0.108237;-0.027956;0.993732;,
  -0.108237;-0.027956;0.993732;,
  0.125407;0.000000;0.992105;,
  -0.125407;0.000000;0.992105;,
  0.946463;-0.303881;0.108925;,
  -0.112727;0.000000;0.993626;,
  -0.994340;0.000000;0.106247;,
  -1.000000;0.000000;-0.000000;,
  -0.979874;0.000000;0.199615;,
  -0.147149;-0.055621;0.987549;,
  -0.215343;-0.055620;0.974953;,
  -0.435158;-0.900058;0.023095;,
  -0.430582;-0.902551;-0.000000;,
  -0.432254;-0.894176;0.116640;,
  -0.248834;0.000000;0.968546;,
  -1.000000;0.000000;0.000000;,
  -0.958650;0.000000;0.284589;,
  -0.951587;-0.302541;0.054332;,
  -0.953842;-0.300311;0.000000;,
  -0.923168;-0.324621;0.205868;,
  0.000000;1.000000;0.000000;,
  -0.454825;-0.888677;0.058204;,
  0.000000;-1.000000;-0.000000;,
  0.454825;-0.888677;0.058204;,
  -0.462116;-0.886819;0.000000;,
  0.462116;-0.886819;-0.000000;,
  -0.439829;-0.896072;0.060047;,
  0.439829;-0.896072;0.060047;,
  0.896877;0.000000;0.442279;,
  0.426768;-0.870996;0.243384;,
  0.838019;0.000000;0.545641;,
  0.838019;0.000000;0.545641;,
  0.850018;-0.334731;0.406724;,
  0.112727;0.000000;0.993626;,
  0.147149;-0.055621;0.987549;,
  0.215343;-0.055620;0.974953;,
  0.248834;0.000000;0.968546;,
  -0.987750;0.000000;0.156046;,
  -0.896877;0.000000;0.442279;,
  -0.439700;-0.897496;0.034142;,
  -0.426768;-0.870996;0.243384;,
  -0.838019;0.000000;0.545641;,
  -0.838019;0.000000;0.545641;,
  -0.946463;-0.303881;0.108925;,
  -0.850018;-0.334731;0.406724;,
  -0.445975;-0.887475;0.116164;,
  0.445975;-0.887475;0.116164;,
  -0.416107;-0.901512;0.118871;,
  0.416107;-0.901512;0.118871;,
  -0.607213;0.519716;-0.600989;,
  0.000000;0.122088;-0.992519;,
  -0.697884;-0.038848;-0.715156;,
  0.000000;-0.059823;-0.998209;,
  -0.538424;-0.606410;-0.585121;,
  0.000000;-0.240118;-0.970744;,
  0.607213;0.519716;-0.600989;,
  0.688117;0.725583;0.004983;,
  0.697884;-0.038848;-0.715156;,
  0.999973;-0.007335;0.000505;,
  0.538424;-0.606410;-0.585121;,
  0.594571;-0.803958;0.011699;,
  0.536852;0.603886;0.589162;,
  0.000000;0.666939;0.745112;,
  0.635509;-0.013511;0.771975;,
  0.000000;-0.022796;0.999740;,
  0.452081;-0.662660;0.597080;,
  0.000000;-0.707027;0.707187;,
  -0.536852;0.603886;0.589162;,
  -0.688117;0.725583;0.004983;,
  -0.221060;-0.022232;0.975007;,
  -0.999973;-0.007335;0.000505;,
  -0.452081;-0.662660;0.597080;,
  -0.594571;-0.803958;0.011699;,
  0.000000;0.999999;0.001256;,
  0.000000;-0.999591;0.028598;,
  -0.933070;-0.000635;0.359694;,
  0.000000;0.937617;-0.347670;,
  0.000000;-0.964730;-0.263240;,
  -0.189843;0.967093;-0.169384;,
  0.000000;0.979252;-0.202646;,
  -0.237633;0.945652;-0.221975;,
  0.000000;0.941116;-0.338085;,
  -0.625470;0.208144;-0.751973;,
  0.000000;0.149640;-0.988741;,
  0.189843;0.967093;-0.169384;,
  0.228903;0.973449;0.000833;,
  0.237633;0.945652;-0.221975;,
  0.774962;0.631954;0.008306;,
  0.625470;0.208144;-0.751973;,
  0.992680;0.119672;0.016252;,
  0.192907;0.963939;0.183326;,
  0.000000;0.974275;0.225362;,
  0.241570;0.940298;0.239757;,
  0.000000;0.926531;0.376219;,
  0.659661;0.000000;0.751563;,
  0.000000;0.000000;1.000000;,
  -0.192907;0.963939;0.183326;,
  -0.228903;0.973449;0.000833;,
  -0.241570;0.940298;0.239757;,
  -0.610530;0.780354;-0.135282;,
  -0.659661;0.000000;0.751563;,
  -0.992680;0.119672;0.016252;,
  0.000000;0.999996;0.002992;,
  0.000000;-1.000000;-0.000000;,
  -0.921940;0.000000;0.387332;,
  -0.272979;0.248731;-0.929309;,
  -0.062636;0.230341;-0.971092;,
  -0.300233;0.010209;-0.953811;,
  -0.070022;0.010250;-0.997493;,
  -0.716583;-0.510762;-0.475006;,
  -0.073977;-0.211751;-0.974520;,
  0.560727;0.268976;-0.783095;,
  0.947351;0.318824;0.029601;,
  0.584774;0.003149;-0.811190;,
  0.999500;-0.004919;0.031226;,
  0.566806;-0.262190;-0.781017;,
  0.662838;-0.748527;0.018777;,
  0.512845;0.229873;0.827133;,
  -0.046990;0.138561;0.989239;,
  0.528659;0.001095;0.848834;,
  -0.051035;0.006152;0.998678;,
  0.516458;-0.227427;0.825559;,
  -0.054186;-0.126700;0.990460;,
  -0.183793;0.148358;0.971705;,
  -0.754879;0.655037;0.032921;,
  -0.197737;0.006068;0.980236;,
  -0.998591;-0.002856;0.052994;,
  -0.207624;-0.136347;0.968660;,
  -0.820353;-0.570896;0.033151;,
  -0.093226;0.995634;0.004621;,
  -0.141856;-0.989855;0.007946;,
  -0.946579;0.162962;0.278265;,
  -0.959431;-0.002502;0.281933;,
  -0.744207;0.654229;-0.134685;,
  -0.983521;-0.003058;-0.180769;,
  -0.806232;-0.551671;0.213657;,
  -0.339299;0.938055;0.070208;,
  -0.093073;0.994125;0.055251;,
  0.159109;0.986577;0.036758;,
  0.159213;0.987240;0.003088;,
  -0.093140;0.994589;-0.046020;,
  0.159136;0.986783;-0.030584;,
  -0.141141;-0.985318;0.096059;,
  0.270747;-0.960607;0.062685;,
  -0.141467;-0.986686;-0.080234;,
  0.270882;-0.961195;-0.052220;,
  0.272980;0.248731;0.929309;,
  0.062636;0.230341;0.971092;,
  0.300233;0.010209;0.953811;,
  0.070022;0.010250;0.997493;,
  0.716583;-0.510761;0.475007;,
  0.073977;-0.211751;0.974520;,
  -0.560728;0.268976;0.783094;,
  -0.947352;0.318824;-0.029604;,
  -0.584775;0.003149;0.811189;,
  -0.999500;-0.004919;-0.031230;,
  -0.566807;-0.262191;0.781016;,
  -0.662839;-0.748527;-0.018778;,
  -0.512843;0.229872;-0.827134;,
  0.046990;0.138561;-0.989239;,
  -0.528657;0.001095;-0.848835;,
  0.051034;0.006152;-0.998678;,
  -0.516457;-0.227426;-0.825560;,
  0.054186;-0.126700;-0.990460;,
  0.183793;0.148358;-0.971705;,
  0.754880;0.655037;-0.032921;,
  0.197737;0.006068;-0.980236;,
  0.998591;-0.002856;-0.052994;,
  0.207624;-0.136347;-0.968660;,
  0.820353;-0.570896;-0.033151;,
  0.093226;0.995634;-0.004621;,
  0.141856;-0.989855;-0.007946;,
  0.946579;0.162962;-0.278266;,
  0.959431;-0.002502;-0.281934;,
  0.744208;0.654228;0.134686;,
  0.983520;-0.003058;0.180771;,
  0.806232;-0.551671;-0.213658;,
  0.339299;0.938055;-0.070209;,
  0.093073;0.994125;-0.055251;,
  -0.159109;0.986577;-0.036758;,
  -0.159213;0.987240;-0.003089;,
  0.093140;0.994589;0.046020;,
  -0.159136;0.986783;0.030584;,
  0.141141;-0.985318;-0.096060;,
  -0.270747;-0.960607;-0.062686;,
  0.141467;-0.986686;0.080234;,
  -0.270882;-0.961195;0.052219;;
  204;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,7,11,10;,
  4;7,8,8,11;,
  4;8,9,12,8;,
  4;9,22,26,12;,
  4;10,11,14,13;,
  4;11,8,8,14;,
  4;8,12,15,8;,
  4;12,26,27,15;,
  4;13,14,17,16;,
  4;14,8,8,17;,
  4;8,15,18,8;,
  4;15,27,31,18;,
  4;16,17,20,19;,
  4;17,8,8,20;,
  4;8,18,21,8;,
  4;18,31,34,21;,
  4;73,23,23,73;,
  4;23,24,24,23;,
  4;24,25,25,24;,
  4;25,38,38,25;,
  4;74,28,28,74;,
  4;28,29,29,28;,
  4;29,30,30,29;,
  4;30,44,44,30;,
  4;75,32,32,76;,
  4;32,33,33,32;,
  4;33,33,33,33;,
  4;33,33,33,33;,
  4;76,32,35,77;,
  4;32,33,36,35;,
  4;33,33,37,36;,
  4;33,33,49,37;,
  4;78,39,42,79;,
  4;39,40,40,42;,
  4;40,41,43,40;,
  4;41,50,54,43;,
  4;79,42,45,80;,
  4;42,40,40,45;,
  4;40,43,46,40;,
  4;43,54,55,46;,
  4;80,45,47,81;,
  4;45,40,40,47;,
  4;40,46,48,40;,
  4;46,55,59,48;,
  4;81,47,47,81;,
  4;47,40,40,47;,
  4;40,48,48,40;,
  4;48,59,59,48;,
  4;82,51,51,82;,
  4;51,52,52,51;,
  4;52,53,53,52;,
  4;53,83,83,53;,
  4;84,56,56,84;,
  4;56,57,57,56;,
  4;57,58,58,57;,
  4;58,85,85,58;,
  4;60,60,60,60;,
  4;60,60,60,60;,
  4;60,61,61,60;,
  4;61,86,87,61;,
  4;60,60,62,88;,
  4;60,60,63,62;,
  4;60,61,64,63;,
  4;61,87,89,64;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;65,65,65,65;,
  4;62,66,90,88;,
  4;66,67,67,90;,
  4;67,68,91,67;,
  4;68,37,49,91;,
  4;63,69,66,62;,
  4;69,67,67,66;,
  4;67,70,68,67;,
  4;70,36,37,68;,
  4;64,71,69,63;,
  4;71,67,67,69;,
  4;67,72,70,67;,
  4;72,35,36,70;,
  4;89,92,71,64;,
  4;92,67,67,71;,
  4;67,93,72,67;,
  4;93,77,35,72;,
  4;94,95,97,96;,
  4;95,100,102,97;,
  4;96,97,99,98;,
  4;97,102,104,99;,
  4;100,101,103,102;,
  4;101,106,108,103;,
  4;102,103,105,104;,
  4;103,108,110,105;,
  4;106,107,109,108;,
  4;107,112,114,109;,
  4;108,109,111,110;,
  4;109,114,116,111;,
  4;112,113,115,120;,
  4;113,94,96,115;,
  4;120,115,117,116;,
  4;115,96,98,117;,
  4;112,107,118,113;,
  4;107,106,101,118;,
  4;113,118,121,94;,
  4;118,101,100,121;,
  4;117,119,111,116;,
  4;119,105,110,111;,
  4;98,122,119,117;,
  4;122,104,105,119;,
  4;123,124,126,125;,
  4;124,129,131,126;,
  4;127,128,128,127;,
  4;128,133,133,128;,
  4;129,130,132,131;,
  4;130,135,137,132;,
  4;133,132,134,133;,
  4;132,139,139,134;,
  4;135,136,138,137;,
  4;136,141,143,138;,
  4;139,140,140,139;,
  4;140,145,145,140;,
  4;141,142,144,143;,
  4;142,123,125,144;,
  4;145,149,146,145;,
  4;144,127,127,146;,
  4;141,136,147,142;,
  4;136,135,130,147;,
  4;142,147,124,123;,
  4;147,130,129,124;,
  4;148,148,148,148;,
  4;148,148,148,148;,
  4;148,148,148,148;,
  4;148,148,148,148;,
  4;150,151,153,152;,
  4;151,156,158,153;,
  4;152,153,155,154;,
  4;153,158,160,155;,
  4;156,157,159,158;,
  4;157,162,164,159;,
  4;158,159,161,160;,
  4;159,164,166,161;,
  4;162,163,165,164;,
  4;163,168,170,165;,
  4;164,165,167,166;,
  4;165,170,172,167;,
  4;176,169,171,177;,
  4;169,178,179,171;,
  4;177,171,173,180;,
  4;171,179,154,173;,
  4;181,182,174,169;,
  4;182,183,184,174;,
  4;169,174,185,178;,
  4;174,184,186,185;,
  4;173,175,187,180;,
  4;175,161,188,187;,
  4;154,189,175,173;,
  4;189,190,161,175;,
  4;191,192,194,193;,
  4;192,197,199,194;,
  4;193,194,196,195;,
  4;194,199,201,196;,
  4;197,198,200,199;,
  4;198,203,205,200;,
  4;199,200,202,201;,
  4;200,205,207,202;,
  4;203,204,206,205;,
  4;204,209,211,206;,
  4;205,206,208,207;,
  4;206,211,213,208;,
  4;217,210,212,218;,
  4;210,219,220,212;,
  4;218,212,214,221;,
  4;212,220,195,214;,
  4;222,223,215,210;,
  4;223,224,225,215;,
  4;210,215,226,219;,
  4;215,225,227,226;,
  4;214,216,228,221;,
  4;216,202,229,228;,
  4;195,230,216,214;,
  4;230,231,202,216;;
 }
 MeshTextureCoords {
  376;
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
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.250000;1.000000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  0.750000;1.000000;,
  1.000000;0.750000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.500000;0.250000;,
  0.750000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.500000;0.000000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;;
 }
}