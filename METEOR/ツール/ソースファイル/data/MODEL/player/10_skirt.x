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
 40;
 11.63359;-29.14088;10.02159;,
 16.47516;-31.91232;-9.33178;,
 6.43408;-3.46038;-0.25025;,
 4.35704;-3.89231;0.47356;,
 11.63359;-28.35816;-20.46678;,
 4.35704;-2.11289;-4.47186;,
 -0.05489;-26.88596;-25.07911;,
 -0.05489;-1.48132;-6.45055;,
 -11.74339;-28.35816;-20.46680;,
 -4.60207;-2.11289;-4.47186;,
 -16.58495;-31.91232;-9.33178;,
 -6.67911;-3.46038;-0.25025;,
 -11.74335;-29.14088;10.02159;,
 -4.60206;-3.89231;0.47356;,
 -0.05489;-14.76059;-3.85714;,
 -0.05489;-4.52388;2.45225;,
 -4.60206;-3.89231;0.47356;,
 -0.05489;-4.52388;2.45225;,
 -0.05489;2.78780;-0.38598;,
 4.35704;-3.89231;0.47356;,
 6.43408;-3.46038;-0.25025;,
 4.35704;-2.11289;-4.47186;,
 -0.05489;-1.48132;-6.45055;,
 -4.60207;-2.11289;-4.47186;,
 -6.67911;-3.46038;-0.25025;,
 -11.66817;-29.71683;18.55536;,
 -0.05489;-28.57182;23.22753;,
 -0.05489;-1.59381;4.77922;,
 -4.60206;-2.08821;2.76188;,
 11.55841;-29.71683;18.55536;,
 4.35704;-2.08821;2.76188;,
 16.36884;-32.48110;7.27584;,
 6.43408;-2.76660;-0.00629;,
 14.14637;-30.49299;-12.18921;,
 4.35704;-3.82140;-4.31038;,
 -16.47863;-32.48110;7.27584;,
 -6.67911;-2.76660;-0.00629;,
 -0.05489;-14.28755;2.81714;,
 -14.25617;-30.49300;-12.18923;,
 -0.05489;3.16043;-1.45883;;
 
 45;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 3;1,0,14;,
 3;4,1,14;,
 3;6,4,14;,
 3;8,6,14;,
 3;10,8,14;,
 3;3,15,0;,
 3;14,0,10;,
 3;15,13,0;,
 3;13,12,0;,
 3;12,10,0;,
 3;16,17,18;,
 3;17,19,18;,
 3;19,20,18;,
 3;20,21,18;,
 3;21,22,18;,
 3;22,23,18;,
 3;23,24,18;,
 3;24,16,18;,
 4;25,26,27,28;,
 4;26,29,30,27;,
 4;29,31,32,30;,
 4;31,33,34,32;,
 4;35,25,28,36;,
 3;26,25,37;,
 3;29,26,37;,
 3;31,29,37;,
 3;33,31,37;,
 3;35,38,37;,
 3;25,35,37;,
 3;28,27,39;,
 3;27,30,39;,
 3;30,32,39;,
 3;35,36,37;,
 3;36,39,37;,
 3;37,39,32;,
 3;37,32,33;,
 3;32,34,33;,
 3;37,38,35;,
 3;36,28,39;;
 
 MeshMaterialList {
  1;
  45;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  55;
  -0.364355;0.397676;0.842080;,
  0.169545;0.347501;0.922224;,
  0.872280;0.446786;0.198769;,
  0.669737;0.510157;-0.539623;,
  0.002616;0.598238;-0.801314;,
  -0.668460;0.508669;-0.542601;,
  -0.873995;0.443531;0.198525;,
  -0.343644;0.305705;0.887949;,
  -0.014541;0.321147;0.946918;,
  0.409073;0.365774;0.835984;,
  0.759413;0.546443;0.353117;,
  0.614529;0.651633;-0.444668;,
  0.003819;0.717759;-0.696281;,
  -0.610440;0.654740;-0.445733;,
  -0.825176;0.557497;0.091004;,
  -0.410777;-0.870762;0.270252;,
  0.002707;0.332234;0.943193;,
  -0.632518;0.493721;0.596792;,
  0.002583;0.571155;0.820838;,
  0.633929;0.495186;0.594075;,
  0.928535;0.367220;0.054522;,
  0.921673;0.276106;-0.272551;,
  0.744225;-0.667718;0.016775;,
  -0.810056;0.556320;0.185251;,
  -0.564545;0.640322;0.520843;,
  0.003756;0.692548;0.721362;,
  0.568363;0.637769;0.519821;,
  0.847261;0.513264;0.136781;,
  -0.734236;0.592180;0.331995;,
  -0.328285;-0.545679;-0.771014;,
  0.004223;0.869691;0.493579;,
  -0.720400;-0.693555;-0.002298;,
  -0.401393;-0.915392;0.030671;,
  -0.520871;-0.802664;0.290560;,
  -0.000001;-0.868269;0.496094;,
  0.520870;-0.802664;0.290559;,
  0.721159;-0.568782;-0.395496;,
  0.560227;-0.292565;-0.774953;,
  0.000000;-0.989902;0.141756;,
  0.265116;0.852010;-0.451434;,
  -0.683458;0.722295;-0.105714;,
  -0.259207;0.294787;0.919735;,
  0.000000;-0.819289;-0.573381;,
  0.531684;-0.766867;-0.359482;,
  -0.531684;-0.766867;-0.359482;,
  -0.733373;-0.677056;-0.061304;,
  -0.784608;-0.565087;0.255080;,
  0.733373;-0.677057;-0.061305;,
  -0.000001;-0.238026;-0.971259;,
  -0.000001;-0.238026;-0.971259;,
  0.000000;-0.238026;-0.971259;,
  -0.337207;-0.040575;-0.940556;,
  -0.622607;0.163109;-0.765347;,
  -0.770890;-0.423492;0.475796;,
  -0.744225;0.667718;-0.016775;;
  45;
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,0,7,14;,
  3;31,32,15;,
  3;33,31,15;,
  3;34,33,15;,
  3;35,34,15;,
  3;36,35,36;,
  3;9,8,1;,
  3;36,37,36;,
  3;8,7,1;,
  3;7,0,1;,
  3;38,38,32;,
  3;7,8,16;,
  3;8,9,16;,
  3;9,10,16;,
  3;10,11,39;,
  3;11,12,39;,
  3;12,13,39;,
  3;13,14,40;,
  3;41,7,16;,
  4;17,18,25,24;,
  4;18,19,26,25;,
  4;19,20,27,26;,
  4;20,21,21,27;,
  4;23,17,24,28;,
  3;42,43,29;,
  3;44,42,29;,
  3;45,44,29;,
  3;46,45,29;,
  3;47,22,47;,
  3;43,47,47;,
  3;24,25,30;,
  3;25,26,30;,
  3;26,27,30;,
  3;48,49,29;,
  3;49,50,29;,
  3;29,50,51;,
  3;29,51,52;,
  3;53,53,46;,
  3;54,54,23;,
  3;28,24,30;;
 }
 MeshTextureCoords {
  40;
  0.833470;0.762100;,
  0.816290;0.779570;,
  0.839380;0.719660;,
  0.843490;0.720530;,
  0.819720;0.783090;,
  0.842500;0.716530;,
  0.849590;0.785490;,
  0.851420;0.714890;,
  0.881100;0.783960;,
  0.860940;0.716490;,
  0.886770;0.780520;,
  0.864630;0.719630;,
  0.871400;0.762450;,
  0.860550;0.720520;,
  0.851610;0.742170;,
  0.851990;0.721820;,
  0.463610;0.927550;,
  0.448410;0.921260;,
  0.448410;0.943600;,
  0.433220;0.927550;,
  0.426930;0.942740;,
  0.433220;0.957930;,
  0.448410;0.964230;,
  0.463610;0.957930;,
  0.469900;0.942740;,
  0.899900;0.785760;,
  0.927380;0.786720;,
  0.924890;0.721860;,
  0.915990;0.722970;,
  0.952790;0.784580;,
  0.933050;0.723020;,
  0.956620;0.781530;,
  0.936280;0.724480;,
  0.945350;0.768160;,
  0.931700;0.726550;,
  0.892930;0.782870;,
  0.912180;0.724440;,
  0.924700;0.746110;,
  0.901220;0.768850;,
  0.924270;0.713660;;
 }
}
