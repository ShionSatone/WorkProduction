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
 79;
 3.25620;-2.61800;-0.76843;,
 2.48476;-2.61800;-1.08797;,
 2.48476;-2.00000;-2.01287;,
 3.91020;-2.00000;-1.42243;,
 1.71331;-2.61800;-0.76843;,
 1.05931;-2.00000;-1.42243;,
 1.39377;-2.61800;0.00302;,
 0.46887;-2.00000;0.00302;,
 1.71331;-2.61800;0.77446;,
 1.05931;-2.00000;1.42846;,
 2.48476;-2.61800;1.09401;,
 2.48476;-2.00000;2.01890;,
 3.25620;-2.61800;0.77446;,
 3.91020;-2.00000;1.42846;,
 3.57575;-2.61800;0.00302;,
 4.50064;-2.00000;0.00302;,
 3.25620;-2.61800;-0.76843;,
 3.91020;-2.00000;-1.42243;,
 2.48476;-1.07511;-2.63086;,
 4.34719;-1.07511;-1.85942;,
 0.62232;-1.07511;-1.85942;,
 -0.14912;-1.07511;0.00302;,
 0.62232;-1.07511;1.86545;,
 2.48476;-1.07511;2.63690;,
 4.34719;-1.07511;1.86545;,
 5.11864;-1.07511;0.00302;,
 4.34719;-1.07511;-1.85942;,
 2.48476;0.01588;-2.84787;,
 4.50064;0.01588;-2.01287;,
 0.46887;0.01588;-2.01287;,
 -0.36613;0.01588;0.00302;,
 0.46887;0.01588;2.01890;,
 2.48476;0.01588;2.85391;,
 4.50064;0.01588;2.01890;,
 5.33565;0.01588;0.00302;,
 4.50064;0.01588;-2.01287;,
 2.48476;1.10687;-2.63086;,
 4.34719;1.10687;-1.85942;,
 0.62232;1.10687;-1.85942;,
 -0.14912;1.10687;0.00302;,
 0.62232;1.10687;1.86545;,
 2.48476;1.10687;2.63690;,
 4.34719;1.10687;1.86545;,
 5.11864;1.10687;0.00302;,
 4.34719;1.10687;-1.85942;,
 2.48476;2.03177;-2.01287;,
 3.91020;2.03177;-1.42243;,
 1.05931;2.03177;-1.42243;,
 0.46887;2.03177;0.00302;,
 1.05931;2.03177;1.42846;,
 2.48476;2.03177;2.01890;,
 3.91020;2.03177;1.42846;,
 4.50064;2.03177;0.00302;,
 3.91020;2.03177;-1.42243;,
 2.48476;2.64977;-1.08797;,
 3.25620;2.64977;-0.76843;,
 1.71331;2.64977;-0.76843;,
 1.39377;2.64977;0.00302;,
 1.71331;2.64977;0.77446;,
 2.48476;2.64977;1.09401;,
 3.25620;2.64977;0.77446;,
 3.57575;2.64977;0.00302;,
 3.25620;2.64977;-0.76843;,
 2.48476;-2.83501;0.00302;,
 2.48476;-2.83501;0.00302;,
 2.48476;-2.83501;0.00302;,
 2.48476;-2.83501;0.00302;,
 2.48476;-2.83501;0.00302;,
 2.48476;-2.83501;0.00302;,
 2.48476;-2.83501;0.00302;,
 2.48476;-2.83501;0.00302;,
 2.48476;2.86677;0.00302;,
 2.48476;2.86677;0.00302;,
 2.48476;2.86677;0.00302;,
 2.48476;2.86677;0.00302;,
 2.48476;2.86677;0.00302;,
 2.48476;2.86677;0.00302;,
 2.48476;2.86677;0.00302;,
 2.48476;2.86677;0.00302;;
 
 64;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;3,2,18,19;,
 4;2,5,20,18;,
 4;5,7,21,20;,
 4;7,9,22,21;,
 4;9,11,23,22;,
 4;11,13,24,23;,
 4;13,15,25,24;,
 4;15,17,26,25;,
 4;19,18,27,28;,
 4;18,20,29,27;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 4;28,27,36,37;,
 4;27,29,38,36;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;34,35,44,43;,
 4;37,36,45,46;,
 4;36,38,47,45;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;43,44,53,52;,
 4;46,45,54,55;,
 4;45,47,56,54;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;52,53,62,61;,
 3;1,0,63;,
 3;4,1,64;,
 3;6,4,65;,
 3;8,6,66;,
 3;10,8,67;,
 3;12,10,68;,
 3;14,12,69;,
 3;16,14,70;,
 3;55,54,71;,
 3;54,56,72;,
 3;56,57,73;,
 3;57,58,74;,
 3;58,59,75;,
 3;59,60,76;,
 3;60,61,77;,
 3;61,62,78;;
 
 MeshMaterialList {
  1;
  64;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\miragequeen.jpg";
   }
  }
 }
 MeshNormals {
  58;
  0.269133;-0.924735;-0.269134;,
  0.000001;-0.924735;-0.380611;,
  -0.269132;-0.924735;-0.269132;,
  -0.380611;-0.924735;0.000001;,
  -0.269134;-0.924735;0.269133;,
  0.000001;-0.924735;0.380612;,
  0.269134;-0.924734;0.269134;,
  0.380612;-0.924735;0.000001;,
  0.498494;-0.709230;-0.498494;,
  0.000001;-0.709230;-0.704977;,
  -0.498494;-0.709230;-0.498494;,
  -0.704977;-0.709230;0.000001;,
  -0.498494;-0.709230;0.498494;,
  0.000001;-0.709231;0.704976;,
  0.498494;-0.709230;0.498494;,
  0.704976;-0.709231;0.000001;,
  0.652732;-0.384552;-0.652733;,
  0.000001;-0.384551;-0.923104;,
  -0.652733;-0.384551;-0.652733;,
  -0.923104;-0.384551;0.000001;,
  -0.652733;-0.384552;0.652732;,
  0.000001;-0.384553;0.923103;,
  0.652732;-0.384553;0.652732;,
  0.923103;-0.384553;0.000001;,
  0.707106;-0.000000;-0.707108;,
  0.000001;-0.000000;-1.000000;,
  -0.707107;-0.000000;-0.707107;,
  -1.000000;0.000000;0.000001;,
  -0.707108;-0.000000;0.707106;,
  0.000001;-0.000000;1.000000;,
  0.707107;-0.000000;0.707107;,
  1.000000;0.000000;0.000001;,
  0.652733;0.384550;-0.652734;,
  0.000001;0.384549;-0.923105;,
  -0.652733;0.384549;-0.652733;,
  -0.923105;0.384549;0.000001;,
  -0.652734;0.384550;0.652733;,
  0.000001;0.384551;0.923104;,
  0.652733;0.384550;0.652733;,
  0.923104;0.384551;0.000001;,
  0.498495;0.709228;-0.498496;,
  0.000001;0.709228;-0.704979;,
  -0.498495;0.709229;-0.498495;,
  -0.704979;0.709228;0.000001;,
  -0.498496;0.709228;0.498495;,
  0.000001;0.709229;0.704978;,
  0.498495;0.709228;0.498495;,
  0.704978;0.709229;0.000001;,
  0.269130;0.924736;-0.269131;,
  0.000001;0.924737;-0.380607;,
  -0.269129;0.924737;-0.269129;,
  -0.380607;0.924737;0.000001;,
  -0.269131;0.924736;0.269130;,
  0.000001;0.924737;0.380608;,
  0.269131;0.924736;0.269131;,
  0.380608;0.924736;0.000001;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;;
  64;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,8,16,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,16,24,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,24,32,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,32,40,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,40,48,55;,
  3;1,0,56;,
  3;2,1,56;,
  3;3,2,56;,
  3;4,3,56;,
  3;5,4,56;,
  3;6,5,56;,
  3;7,6,56;,
  3;0,7,56;,
  3;48,49,57;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,48,57;;
 }
 MeshTextureCoords {
  79;
  0.877460;0.087530;,
  0.888400;0.087530;,
  0.888400;0.076590;,
  0.877460;0.076590;,
  0.899340;0.087530;,
  0.899340;0.076590;,
  0.910280;0.087530;,
  0.910280;0.076590;,
  0.921220;0.087530;,
  0.921220;0.076590;,
  0.932160;0.087530;,
  0.932160;0.076590;,
  0.943100;0.087530;,
  0.943100;0.076590;,
  0.954040;0.087530;,
  0.954040;0.076590;,
  0.964980;0.087530;,
  0.964980;0.076590;,
  0.888400;0.065650;,
  0.877460;0.065650;,
  0.899340;0.065650;,
  0.910280;0.065650;,
  0.921220;0.065650;,
  0.932160;0.065650;,
  0.943100;0.065650;,
  0.954040;0.065650;,
  0.964980;0.065650;,
  0.888400;0.054710;,
  0.877460;0.054710;,
  0.899340;0.054710;,
  0.910280;0.054710;,
  0.921220;0.054710;,
  0.932160;0.054710;,
  0.943100;0.054710;,
  0.954040;0.054710;,
  0.964980;0.054710;,
  0.888400;0.043770;,
  0.877460;0.043770;,
  0.899340;0.043770;,
  0.910280;0.043770;,
  0.921220;0.043770;,
  0.932160;0.043770;,
  0.943100;0.043770;,
  0.954040;0.043770;,
  0.964980;0.043770;,
  0.888400;0.032840;,
  0.877460;0.032840;,
  0.899340;0.032840;,
  0.910280;0.032840;,
  0.921220;0.032840;,
  0.932160;0.032840;,
  0.943100;0.032840;,
  0.954040;0.032840;,
  0.964980;0.032840;,
  0.888400;0.021890;,
  0.877460;0.021890;,
  0.899340;0.021890;,
  0.910280;0.021890;,
  0.921220;0.021890;,
  0.932160;0.021890;,
  0.943100;0.021890;,
  0.954040;0.021890;,
  0.964980;0.021890;,
  0.882930;0.098470;,
  0.893870;0.098470;,
  0.904810;0.098470;,
  0.915750;0.098470;,
  0.926690;0.098470;,
  0.937630;0.098470;,
  0.948570;0.098470;,
  0.959510;0.098470;,
  0.882930;0.010950;,
  0.893870;0.010950;,
  0.904810;0.010950;,
  0.915750;0.010950;,
  0.926690;0.010950;,
  0.937630;0.010950;,
  0.948570;0.010950;,
  0.959510;0.010950;;
 }
}
