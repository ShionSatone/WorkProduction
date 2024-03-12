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
 89;
 0.00000;26.26562;-26.83657;,
 19.04631;26.26562;-18.94730;,
 16.31167;3.74562;-16.21267;,
 0.00000;3.74562;-22.96921;,
 26.93556;26.26562;0.09900;,
 23.06821;3.74562;0.09900;,
 19.04631;26.26562;19.14532;,
 16.31167;3.74562;16.41057;,
 0.00000;26.26562;27.03445;,
 0.00000;3.74562;23.16711;,
 -19.04631;26.26562;19.14532;,
 -16.31167;3.74562;16.41057;,
 -26.93556;26.26562;0.09900;,
 -23.06821;3.74562;0.09900;,
 -19.04631;26.26562;-18.94730;,
 -16.31167;3.74562;-16.21267;,
 15.59349;1.70573;-15.49459;,
 0.00000;1.70573;-21.95360;,
 22.05260;1.70573;0.09900;,
 15.59349;1.70573;15.69250;,
 0.00000;1.70573;22.15160;,
 -15.59349;1.70573;15.69250;,
 -22.05260;1.70573;0.09900;,
 -15.59349;1.70573;-15.49459;,
 14.51876;0.34288;-14.41986;,
 0.00000;0.34288;-20.43370;,
 20.53272;0.34288;0.09900;,
 14.51876;0.34288;14.61776;,
 0.00000;0.34288;20.63158;,
 -14.51876;0.34288;14.61776;,
 -20.53272;0.34288;0.09900;,
 -14.51876;0.34288;-14.41986;,
 13.25113;-0.13589;-13.15213;,
 0.00000;-0.13589;-18.64088;,
 18.73978;-0.13589;0.09900;,
 13.25113;-0.13589;13.35000;,
 0.00000;-0.13589;18.83879;,
 -13.25113;-0.13589;13.35000;,
 -18.73978;-0.13589;0.09900;,
 -13.25113;-0.13589;-13.15213;,
 0.00000;-0.13589;0.09900;,
 15.99545;107.73309;-15.89657;,
 0.00000;107.60645;-22.52205;,
 0.00000;114.50433;-25.39855;,
 18.02945;114.50433;-17.93058;,
 22.62105;107.75461;0.09900;,
 25.49755;114.50433;0.09900;,
 15.99545;107.65811;16.09446;,
 18.02945;114.50433;18.12845;,
 0.00000;107.50092;22.72005;,
 0.00000;114.50433;25.59655;,
 -15.99545;107.37402;16.09446;,
 -18.02945;114.50433;18.12845;,
 -22.62105;107.35260;0.09900;,
 -25.49755;114.50433;0.09900;,
 -15.99545;107.44885;-15.89657;,
 -18.02945;114.50433;-17.93058;,
 12.52741;97.29022;-12.42842;,
 0.00000;96.98444;-17.61744;,
 17.71644;97.34201;0.09900;,
 12.52939;96.72833;12.62839;,
 0.00000;96.72897;17.81544;,
 -12.52939;96.72833;12.62839;,
 -17.71403;96.72833;0.09900;,
 -12.52939;96.72833;-12.43052;,
 16.39942;92.93079;-16.30039;,
 0.00000;92.93079;-23.09331;,
 23.19230;92.93079;0.09900;,
 16.39942;92.93079;16.49842;,
 0.00000;92.93079;23.29118;,
 -16.39942;92.93079;16.49842;,
 -23.19230;92.93079;0.09900;,
 -16.39942;92.93079;-16.30039;,
 24.80911;79.84814;-24.71019;,
 0.00000;79.84814;-34.98637;,
 35.08537;79.84814;0.09900;,
 24.80911;79.84814;24.90811;,
 0.00000;79.84814;35.18436;,
 -24.80911;79.84814;24.90811;,
 -35.08537;79.84814;0.09900;,
 -24.80911;79.84814;-24.71019;,
 23.95798;69.05389;-23.85898;,
 0.00000;69.05389;-33.78260;,
 33.88160;69.05389;0.09900;,
 23.95798;69.05389;24.05690;,
 0.00000;69.05389;33.98060;,
 -23.95798;69.05389;24.05690;,
 -33.88160;69.05389;0.09900;,
 -23.95798;69.05389;-23.85898;;
 
 184;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,0,3,15;,
 4;3,2,16,17;,
 4;2,5,18,16;,
 4;5,7,19,18;,
 4;7,9,20,19;,
 4;9,11,21,20;,
 4;11,13,22,21;,
 4;13,15,23,22;,
 4;15,3,17,23;,
 4;17,16,24,25;,
 4;16,18,26,24;,
 4;18,19,27,26;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,17,25,31;,
 4;25,24,32,33;,
 4;24,26,34,32;,
 4;26,27,35,34;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,25,33,39;,
 3;33,32,40;,
 3;32,34,40;,
 3;34,35,40;,
 3;35,36,40;,
 3;36,37,40;,
 3;37,38,40;,
 3;38,39,40;,
 3;39,33,40;,
 4;3,2,1,0;,
 4;2,5,4,1;,
 4;5,7,6,4;,
 4;7,9,8,6;,
 4;9,11,10,8;,
 4;11,13,12,10;,
 4;13,15,14,12;,
 4;15,3,0,14;,
 4;17,16,2,3;,
 4;16,18,5,2;,
 4;18,19,7,5;,
 4;19,20,9,7;,
 4;20,21,11,9;,
 4;21,22,13,11;,
 4;22,23,15,13;,
 4;23,17,3,15;,
 4;25,24,16,17;,
 4;24,26,18,16;,
 4;26,27,19,18;,
 4;27,28,20,19;,
 4;28,29,21,20;,
 4;29,30,22,21;,
 4;30,31,23,22;,
 4;31,25,17,23;,
 4;33,32,24,25;,
 4;32,34,26,24;,
 4;34,35,27,26;,
 4;35,36,28,27;,
 4;36,37,29,28;,
 4;37,38,30,29;,
 4;38,39,31,30;,
 4;39,33,25,31;,
 3;40,32,33;,
 3;40,34,32;,
 3;40,35,34;,
 3;40,36,35;,
 3;40,37,36;,
 3;40,38,37;,
 3;40,39,38;,
 3;40,33,39;,
 4;41,42,43,44;,
 4;45,41,44,46;,
 4;47,45,46,48;,
 4;49,47,48,50;,
 4;51,49,50,52;,
 4;53,51,52,54;,
 4;55,53,54,56;,
 4;42,55,56,43;,
 4;41,44,43,42;,
 4;45,46,44,41;,
 4;47,48,46,45;,
 4;49,50,48,47;,
 4;51,52,50,49;,
 4;53,54,52,51;,
 4;55,56,54,53;,
 4;42,43,56,55;,
 4;57,58,42,41;,
 4;59,57,41,45;,
 4;60,59,45,47;,
 4;61,60,47,49;,
 4;62,61,49,51;,
 4;63,62,51,53;,
 4;64,63,53,55;,
 4;58,64,55,42;,
 4;58,57,41,42;,
 4;57,59,45,41;,
 4;59,60,47,45;,
 4;60,61,49,47;,
 4;61,62,51,49;,
 4;62,63,53,51;,
 4;63,64,55,53;,
 4;64,58,42,55;,
 4;65,66,58,57;,
 4;67,65,57,59;,
 4;68,67,59,60;,
 4;69,68,60,61;,
 4;70,69,61,62;,
 4;71,70,62,63;,
 4;72,71,63,64;,
 4;66,72,64,58;,
 4;66,65,57,58;,
 4;65,67,59,57;,
 4;67,68,60,59;,
 4;68,69,61,60;,
 4;69,70,62,61;,
 4;70,71,63,62;,
 4;71,72,64,63;,
 4;72,66,58,64;,
 4;57,58,58,57;,
 4;59,57,57,59;,
 4;60,59,59,60;,
 4;61,60,60,61;,
 4;62,61,61,62;,
 4;63,62,62,63;,
 4;64,63,63,64;,
 4;58,64,64,58;,
 4;73,74,66,65;,
 4;75,73,65,67;,
 4;76,75,67,68;,
 4;77,76,68,69;,
 4;78,77,69,70;,
 4;79,78,70,71;,
 4;80,79,71,72;,
 4;74,80,72,66;,
 4;74,73,65,66;,
 4;73,75,67,65;,
 4;75,76,68,67;,
 4;76,77,69,68;,
 4;77,78,70,69;,
 4;78,79,71,70;,
 4;79,80,72,71;,
 4;80,74,66,72;,
 4;81,1,0,82;,
 4;81,82,74,73;,
 4;83,4,1,81;,
 4;83,81,73,75;,
 4;84,6,4,83;,
 4;84,83,75,76;,
 4;85,8,6,84;,
 4;85,84,76,77;,
 4;86,10,8,85;,
 4;86,85,77,78;,
 4;87,12,10,86;,
 4;87,86,78,79;,
 4;88,14,12,87;,
 4;88,87,79,80;,
 4;82,0,14,88;,
 4;82,88,80,74;,
 4;82,0,1,81;,
 4;82,81,73,74;,
 4;81,1,4,83;,
 4;81,83,75,73;,
 4;83,4,6,84;,
 4;83,84,76,75;,
 4;84,6,8,85;,
 4;84,85,77,76;,
 4;85,8,10,86;,
 4;85,86,78,77;,
 4;86,10,12,87;,
 4;86,87,79,78;,
 4;87,12,14,88;,
 4;87,88,80,79;,
 4;88,14,0,82;,
 4;88,82,74,80;;
 
 MeshMaterialList {
  1;
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
   0.000000;0.511200;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  195;
  0.000933;-0.384349;-0.923187;,
  0.651587;-0.389542;-0.650916;,
  0.920631;-0.390433;-0.000237;,
  0.652759;-0.386445;0.651587;,
  0.000941;-0.380158;0.924921;,
  -0.655063;-0.375304;0.655774;,
  -0.927230;-0.374493;-0.000255;,
  -0.654003;-0.378143;-0.655201;,
  0.000000;-0.164748;-0.986336;,
  0.697445;-0.164748;-0.697445;,
  0.986336;-0.164748;0.000000;,
  0.697444;-0.164748;0.697446;,
  0.000000;-0.164749;0.986336;,
  -0.697444;-0.164748;0.697446;,
  -0.986336;-0.164748;0.000000;,
  -0.697445;-0.164748;-0.697445;,
  0.000000;-0.311654;-0.950195;,
  0.671889;-0.311657;-0.671890;,
  0.950194;-0.311660;0.000001;,
  0.671888;-0.311653;0.671892;,
  0.000000;-0.311646;0.950198;,
  -0.671888;-0.311653;0.671892;,
  -0.950194;-0.311660;0.000001;,
  -0.671889;-0.311657;-0.671890;,
  0.000000;-0.607981;-0.793952;,
  0.561407;-0.607982;-0.561409;,
  0.793949;-0.607984;0.000001;,
  0.561408;-0.607982;0.561408;,
  0.000000;-0.607981;0.793951;,
  -0.561408;-0.607982;0.561408;,
  -0.793949;-0.607984;0.000001;,
  -0.561407;-0.607982;-0.561409;,
  0.000000;-0.881277;-0.472600;,
  0.334177;-0.881278;-0.334179;,
  0.472598;-0.881278;0.000001;,
  0.334176;-0.881280;0.334175;,
  0.000000;-0.881282;0.472591;,
  -0.334176;-0.881280;0.334175;,
  -0.472598;-0.881278;0.000001;,
  -0.334177;-0.881278;-0.334179;,
  0.000000;-0.991548;-0.129742;,
  0.091740;-0.991548;-0.091741;,
  0.129740;-0.991548;0.000000;,
  0.091740;-0.991548;0.091741;,
  0.000000;-0.991548;0.129742;,
  -0.091740;-0.991548;0.091741;,
  -0.129740;-0.991548;0.000000;,
  -0.091740;-0.991548;-0.091741;,
  0.000000;-1.000000;-0.000000;,
  0.003096;-0.402009;-0.915631;,
  0.647288;-0.406525;-0.644791;,
  0.914120;-0.405439;-0.001907;,
  0.650002;-0.400740;0.645681;,
  0.001420;-0.397215;0.917725;,
  -0.648586;-0.396574;0.649665;,
  -0.918002;-0.396576;-0.000379;,
  -0.647212;-0.398103;-0.650100;,
  0.005255;-0.419483;-0.907748;,
  0.642780;-0.423321;-0.638461;,
  0.907387;-0.420281;-0.003570;,
  0.647085;-0.414936;0.639616;,
  0.001899;-0.414100;0.910229;,
  -0.641782;-0.417582;0.643227;,
  -0.908274;-0.418375;-0.000503;,
  -0.640128;-0.417845;-0.644703;,
  -0.001174;0.740986;-0.671519;,
  0.480627;0.732570;-0.482015;,
  0.678228;0.734850;0.001509;,
  0.471189;0.744918;0.472311;,
  0.000000;0.752633;0.658440;,
  -0.465570;0.752661;0.465560;,
  -0.658396;0.752672;0.000006;,
  -0.468471;0.749338;-0.468003;,
  0.000000;0.315435;-0.948947;,
  0.671007;0.315435;-0.671007;,
  0.948947;0.315435;0.000000;,
  0.671007;0.315435;0.671007;,
  0.000000;0.315435;0.948947;,
  -0.671007;0.315435;0.671007;,
  -0.948947;0.315435;0.000000;,
  -0.671007;0.315435;-0.671007;,
  0.000000;-0.135590;-0.990765;,
  0.700577;-0.135589;-0.700577;,
  0.990765;-0.135589;0.000000;,
  0.700577;-0.135589;0.700577;,
  0.000000;-0.135590;0.990765;,
  -0.700577;-0.135589;0.700577;,
  -0.990765;-0.135589;0.000000;,
  -0.700577;-0.135589;-0.700577;,
  0.000000;0.311654;0.950195;,
  -0.671889;0.311657;0.671890;,
  -0.697445;0.164748;0.697445;,
  0.000000;0.164748;0.986336;,
  -0.950194;0.311660;-0.000001;,
  -0.986336;0.164748;-0.000000;,
  -0.671888;0.311653;-0.671892;,
  -0.697444;0.164748;-0.697446;,
  0.000000;0.311646;-0.950198;,
  0.000000;0.164749;-0.986336;,
  0.671888;0.311653;-0.671892;,
  0.697444;0.164748;-0.697446;,
  0.950194;0.311660;-0.000001;,
  0.986336;0.164748;-0.000000;,
  0.671889;0.311657;0.671890;,
  0.697445;0.164748;0.697445;,
  0.000000;0.607981;0.793952;,
  -0.561407;0.607982;0.561409;,
  -0.793949;0.607984;-0.000001;,
  -0.561408;0.607982;-0.561408;,
  0.000000;0.607981;-0.793951;,
  0.561408;0.607982;-0.561408;,
  0.793949;0.607984;-0.000001;,
  0.561407;0.607982;0.561409;,
  0.000000;0.881277;0.472600;,
  -0.334177;0.881278;0.334179;,
  -0.472598;0.881278;-0.000001;,
  -0.334176;0.881280;-0.334175;,
  0.000000;0.881282;-0.472591;,
  0.334176;0.881280;-0.334175;,
  0.472598;0.881278;-0.000001;,
  0.334177;0.881278;0.334179;,
  0.000000;0.991548;0.129742;,
  -0.091740;0.991548;0.091741;,
  -0.129740;0.991548;-0.000000;,
  -0.091740;0.991548;-0.091741;,
  0.000000;0.991548;-0.129742;,
  0.091740;0.991548;-0.091741;,
  0.129740;0.991548;-0.000000;,
  0.091740;0.991548;0.091741;,
  0.000000;1.000000;0.000000;,
  -0.647288;0.406525;0.644791;,
  -0.651587;0.389542;0.650916;,
  -0.000933;0.384349;0.923187;,
  -0.003096;0.402009;0.915631;,
  -0.914120;0.405439;0.001907;,
  -0.920631;0.390433;0.000237;,
  -0.650002;0.400740;-0.645681;,
  -0.652759;0.386445;-0.651587;,
  -0.001420;0.397215;-0.917725;,
  -0.000941;0.380158;-0.924921;,
  0.648586;0.396574;-0.649665;,
  0.655063;0.375304;-0.655774;,
  0.918002;0.396576;0.000379;,
  0.927230;0.374493;0.000255;,
  0.647212;0.398103;0.650100;,
  0.654003;0.378143;0.655201;,
  -0.005255;0.419483;0.907748;,
  -0.642780;0.423321;0.638461;,
  -0.907387;0.420281;0.003570;,
  -0.647085;0.414936;-0.639616;,
  -0.001899;0.414100;-0.910229;,
  0.641782;0.417582;-0.643227;,
  0.908274;0.418375;0.000503;,
  0.640128;0.417845;0.644703;,
  -0.002319;0.801507;-0.597980;,
  0.435200;0.786639;-0.437950;,
  0.612073;0.790796;0.002991;,
  0.415254;0.808262;0.417465;,
  0.000000;0.821636;0.570012;,
  -0.403020;0.821686;0.402998;,
  -0.569919;0.821701;0.000011;,
  -0.409252;0.815953;-0.408330;,
  0.001174;-0.740986;0.671519;,
  -0.480627;-0.732570;0.482015;,
  -0.435200;-0.786639;0.437950;,
  0.002319;-0.801507;0.597980;,
  -0.678228;-0.734850;-0.001509;,
  -0.612073;-0.790796;-0.002991;,
  -0.471189;-0.744918;-0.472311;,
  -0.415254;-0.808262;-0.417465;,
  0.000000;-0.752633;-0.658440;,
  0.000000;-0.821636;-0.570012;,
  0.465570;-0.752661;-0.465560;,
  0.403020;-0.821686;-0.402998;,
  0.658396;-0.752672;-0.000006;,
  0.569919;-0.821701;-0.000011;,
  0.468471;-0.749338;0.468003;,
  0.409252;-0.815953;0.408330;,
  0.000000;0.000000;0.000000;,
  0.000000;-0.315435;0.948947;,
  -0.671007;-0.315435;0.671007;,
  -0.948947;-0.315435;-0.000000;,
  -0.671007;-0.315435;-0.671007;,
  0.000000;-0.315435;-0.948947;,
  0.671007;-0.315435;-0.671007;,
  0.948947;-0.315435;-0.000000;,
  0.671007;-0.315435;0.671007;,
  0.000000;0.135590;0.990765;,
  -0.700577;0.135589;0.700577;,
  -0.990765;0.135589;-0.000000;,
  -0.700577;0.135589;-0.700577;,
  0.000000;0.135590;-0.990765;,
  0.700577;0.135589;-0.700577;,
  0.990765;0.135589;-0.000000;,
  0.700577;0.135589;0.700577;;
  184;
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
  3;40,41,48;,
  3;41,42,48;,
  3;42,43,48;,
  3;43,44,48;,
  3;44,45,48;,
  3;45,46,48;,
  3;46,47,48;,
  3;47,40,48;,
  4;89,90,91,92;,
  4;90,93,94,91;,
  4;93,95,96,94;,
  4;95,97,98,96;,
  4;97,99,100,98;,
  4;99,101,102,100;,
  4;101,103,104,102;,
  4;103,89,92,104;,
  4;105,106,90,89;,
  4;106,107,93,90;,
  4;107,108,95,93;,
  4;108,109,97,95;,
  4;109,110,99,97;,
  4;110,111,101,99;,
  4;111,112,103,101;,
  4;112,105,89,103;,
  4;113,114,106,105;,
  4;114,115,107,106;,
  4;115,116,108,107;,
  4;116,117,109,108;,
  4;117,118,110,109;,
  4;118,119,111,110;,
  4;119,120,112,111;,
  4;120,113,105,112;,
  4;121,122,114,113;,
  4;122,123,115,114;,
  4;123,124,116,115;,
  4;124,125,117,116;,
  4;125,126,118,117;,
  4;126,127,119,118;,
  4;127,128,120,119;,
  4;128,121,113,120;,
  3;129,122,121;,
  3;129,123,122;,
  3;129,124,123;,
  3;129,125,124;,
  3;129,126,125;,
  3;129,127,126;,
  3;129,128,127;,
  3;129,121,128;,
  4;50,49,0,1;,
  4;51,50,1,2;,
  4;52,51,2,3;,
  4;53,52,3,4;,
  4;54,53,4,5;,
  4;55,54,5,6;,
  4;56,55,6,7;,
  4;49,56,7,0;,
  4;130,131,132,133;,
  4;134,135,131,130;,
  4;136,137,135,134;,
  4;138,139,137,136;,
  4;140,141,139,138;,
  4;142,143,141,140;,
  4;144,145,143,142;,
  4;133,132,145,144;,
  4;58,57,49,50;,
  4;59,58,50,51;,
  4;60,59,51,52;,
  4;61,60,52,53;,
  4;62,61,53,54;,
  4;63,62,54,55;,
  4;64,63,55,56;,
  4;57,64,56,49;,
  4;146,147,130,133;,
  4;147,148,134,130;,
  4;148,149,136,134;,
  4;149,150,138,136;,
  4;150,151,140,138;,
  4;151,152,142,140;,
  4;152,153,144,142;,
  4;153,146,133,144;,
  4;66,65,154,155;,
  4;67,66,155,156;,
  4;68,67,156,157;,
  4;69,68,157,158;,
  4;70,69,158,159;,
  4;71,70,159,160;,
  4;72,71,160,161;,
  4;65,72,161,154;,
  4;162,163,164,165;,
  4;163,166,167,164;,
  4;166,168,169,167;,
  4;168,170,171,169;,
  4;170,172,173,171;,
  4;172,174,175,173;,
  4;174,176,177,175;,
  4;176,162,165,177;,
  4;178,178,178,178;,
  4;178,178,178,178;,
  4;178,178,178,178;,
  4;178,178,178,178;,
  4;178,178,178,178;,
  4;178,178,178,178;,
  4;178,178,178,178;,
  4;178,178,178,178;,
  4;74,73,65,66;,
  4;75,74,66,67;,
  4;76,75,67,68;,
  4;77,76,68,69;,
  4;78,77,69,70;,
  4;79,78,70,71;,
  4;80,79,71,72;,
  4;73,80,72,65;,
  4;179,180,163,162;,
  4;180,181,166,163;,
  4;181,182,168,166;,
  4;182,183,170,168;,
  4;183,184,172,170;,
  4;184,185,174,172;,
  4;185,186,176,174;,
  4;186,179,162,176;,
  4;82,9,8,81;,
  4;82,81,73,74;,
  4;83,10,9,82;,
  4;83,82,74,75;,
  4;84,11,10,83;,
  4;84,83,75,76;,
  4;85,12,11,84;,
  4;85,84,76,77;,
  4;86,13,12,85;,
  4;86,85,77,78;,
  4;87,14,13,86;,
  4;87,86,78,79;,
  4;88,15,14,87;,
  4;88,87,79,80;,
  4;81,8,15,88;,
  4;81,88,80,73;,
  4;187,92,91,188;,
  4;187,188,180,179;,
  4;188,91,94,189;,
  4;188,189,181,180;,
  4;189,94,96,190;,
  4;189,190,182,181;,
  4;190,96,98,191;,
  4;190,191,183,182;,
  4;191,98,100,192;,
  4;191,192,184,183;,
  4;192,100,102,193;,
  4;192,193,185,184;,
  4;193,102,104,194;,
  4;193,194,186,185;,
  4;194,104,92,187;,
  4;194,187,179,186;;
 }
 MeshTextureCoords {
  89;
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
  0.000000;0.000000;;
 }
}
