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
 196;
 -5.82757;19.23340;6.63049;,
 -5.30681;19.01769;6.63049;,
 -5.30681;19.01769;6.02028;,
 -5.82757;19.23340;6.02028;,
 -5.09110;18.49694;6.63049;,
 -5.09110;18.49694;6.02028;,
 -5.30681;17.97618;6.63049;,
 -5.30681;17.97618;6.02028;,
 -5.82757;17.76048;6.63049;,
 -5.82757;17.76048;6.02028;,
 -6.34832;17.97618;6.63049;,
 -6.34832;17.97618;6.02028;,
 -6.56403;18.49694;6.63049;,
 -6.56403;18.49694;6.02028;,
 -6.34832;19.01769;6.63049;,
 -6.34832;19.01769;6.02028;,
 -5.82757;19.23340;6.63049;,
 -5.82757;19.23340;6.02028;,
 -5.82757;18.49694;6.63049;,
 -5.82757;18.49694;6.63049;,
 -5.82757;18.49694;6.63049;,
 -5.82757;18.49694;6.63049;,
 -5.82757;18.49694;6.63049;,
 -5.82757;18.49694;6.63049;,
 -5.82757;18.49694;6.63049;,
 -5.82757;18.49694;6.63049;,
 -5.82757;18.49694;6.02028;,
 -5.82757;18.49694;6.02028;,
 -5.82757;18.49694;6.02028;,
 -5.82757;18.49694;6.02028;,
 -5.82757;18.49694;6.02028;,
 -5.82757;18.49694;6.02028;,
 -5.82757;18.49694;6.02028;,
 -5.82757;18.49694;6.02028;,
 -14.48197;19.23340;6.63049;,
 -13.96122;19.01769;6.63049;,
 -13.96122;19.01769;6.02028;,
 -14.48197;19.23340;6.02028;,
 -13.74551;18.49694;6.63049;,
 -13.74551;18.49694;6.02028;,
 -13.96122;17.97618;6.63049;,
 -13.96122;17.97618;6.02028;,
 -14.48197;17.76048;6.63049;,
 -14.48197;17.76048;6.02028;,
 -15.00273;17.97618;6.63049;,
 -15.00273;17.97618;6.02028;,
 -15.21844;18.49694;6.63049;,
 -15.21844;18.49694;6.02028;,
 -15.00273;19.01769;6.63049;,
 -15.00273;19.01769;6.02028;,
 -14.48197;19.23340;6.63049;,
 -14.48197;19.23340;6.02028;,
 -14.48197;18.49694;6.63049;,
 -14.48197;18.49694;6.63049;,
 -14.48197;18.49694;6.63049;,
 -14.48197;18.49694;6.63049;,
 -14.48197;18.49694;6.63049;,
 -14.48197;18.49694;6.63049;,
 -14.48197;18.49694;6.63049;,
 -14.48197;18.49694;6.63049;,
 -14.48197;18.49694;6.02028;,
 -14.48197;18.49694;6.02028;,
 -14.48197;18.49694;6.02028;,
 -14.48197;18.49694;6.02028;,
 -14.48197;18.49694;6.02028;,
 -14.48197;18.49694;6.02028;,
 -14.48197;18.49694;6.02028;,
 -14.48197;18.49694;6.02028;,
 -13.48708;19.53221;5.85038;,
 -6.97581;19.53221;5.85038;,
 -6.97581;17.46459;5.85038;,
 -13.48708;17.46459;5.85038;,
 -6.97581;19.53221;5.85038;,
 -6.97581;19.53221;6.40730;,
 -6.97581;17.46459;6.40730;,
 -6.97581;17.46459;5.85038;,
 -6.97581;19.53221;6.40730;,
 -13.48708;19.53221;6.40730;,
 -13.48708;17.46459;6.40730;,
 -6.97581;17.46459;6.40730;,
 -13.48708;19.53221;6.40730;,
 -13.48708;19.53221;5.85038;,
 -13.48708;17.46459;5.85038;,
 -13.48708;17.46459;6.40730;,
 -6.97581;19.53221;5.85038;,
 -13.48708;19.53221;5.85038;,
 -13.48708;17.46459;5.85038;,
 -6.97581;17.46459;5.85038;,
 -18.00239;20.23729;-6.13375;,
 29.22155;20.23729;-6.13375;,
 29.22155;0.23729;-6.13375;,
 -18.00239;0.23729;-6.13375;,
 29.22155;20.23729;-6.13375;,
 29.21493;20.22436;6.14136;,
 29.21493;0.22436;6.14136;,
 29.22155;0.23729;-6.13375;,
 29.21493;20.22436;6.14136;,
 -18.00901;20.22436;6.14136;,
 -18.00901;0.22436;6.14136;,
 29.21493;0.22436;6.14136;,
 -18.00901;20.22436;6.14136;,
 -18.00239;20.23729;-6.13375;,
 -18.00239;0.23729;-6.13375;,
 -18.00901;0.22436;6.14136;,
 -18.00239;0.23729;-6.13375;,
 29.22155;0.23729;-6.13375;,
 -19.34399;20.70410;-6.81103;,
 -15.97806;20.70410;-6.81103;,
 -15.97806;19.67041;-6.81103;,
 -19.34399;19.67041;-6.81103;,
 -3.75281;20.70410;-6.81103;,
 -3.75281;19.67041;-6.81103;,
 6.11263;20.70410;-6.81103;,
 6.11263;19.67041;-6.81103;,
 18.33789;20.70410;-6.81103;,
 18.33789;19.67041;-6.81103;,
 30.56315;20.70410;-6.81103;,
 30.56315;19.67041;-6.81103;,
 30.56315;20.70410;-2.27034;,
 30.56315;19.67041;-2.27034;,
 30.56315;20.70410;2.27034;,
 30.56315;19.67041;2.27034;,
 30.56315;20.70410;6.81103;,
 30.56315;19.67041;6.81103;,
 18.33789;20.70410;6.81103;,
 18.33789;19.67041;6.81103;,
 6.11263;20.70410;6.81103;,
 6.11263;19.67041;6.81103;,
 -3.75281;20.70410;6.81103;,
 -3.75281;19.67041;6.81103;,
 -15.97806;20.70410;6.81103;,
 -15.97806;19.67041;6.81103;,
 -19.34399;20.70410;6.81103;,
 -19.34399;19.67041;6.81103;,
 -19.34399;20.70410;2.27034;,
 -19.34399;19.67041;2.27034;,
 -19.34399;20.70410;-2.27034;,
 -19.34399;19.67041;-2.27034;,
 -15.97806;20.70410;6.60853;,
 -3.75281;20.70410;6.60853;,
 7.17650;20.61840;5.46501;,
 19.38793;20.61840;5.46501;,
 -15.97806;20.70410;-3.57761;,
 -3.75281;20.70410;-3.57761;,
 7.17650;20.61840;-1.99409;,
 19.38793;20.61840;-1.99409;,
 -15.97806;19.67041;2.27034;,
 -3.75281;19.67041;2.27034;,
 6.11263;19.67041;2.27034;,
 18.33789;19.67041;2.27034;,
 -15.97806;19.67041;-2.27034;,
 -3.75281;19.67041;-2.27034;,
 6.11263;19.67041;-2.27034;,
 18.33789;19.67041;-2.27034;,
 7.17650;20.61840;-1.99409;,
 19.38793;20.61840;-1.99409;,
 19.35082;18.31908;-1.71784;,
 7.14435;18.31908;-1.71784;,
 19.38793;20.61840;-1.99409;,
 19.38793;20.61840;5.46501;,
 19.35082;18.31908;5.22960;,
 19.35082;18.31908;-1.71784;,
 19.38793;20.61840;5.46501;,
 7.17650;20.61840;5.46501;,
 7.14435;18.31908;5.22960;,
 19.35082;18.31908;5.22960;,
 7.17650;20.61840;5.46501;,
 7.17650;20.61840;-1.99409;,
 7.14435;18.31908;-1.71784;,
 7.14435;18.31908;5.22960;,
 7.14435;18.31908;-1.71784;,
 19.35082;18.31908;-1.71784;,
 7.14435;18.31908;5.22960;,
 19.35082;18.31908;5.22960;,
 19.35082;18.31908;-1.71784;,
 7.14435;18.31908;-1.71784;,
 -15.98762;19.82258;5.85853;,
 -3.84188;19.82258;5.85853;,
 -3.84188;17.31098;5.85853;,
 -15.98762;17.31098;5.85853;,
 -3.84188;19.82258;5.85853;,
 -3.84188;19.82258;6.32943;,
 -3.84188;17.31098;6.32943;,
 -3.84188;17.31098;5.85853;,
 -3.84188;19.82258;6.32943;,
 -15.98762;19.82258;6.32943;,
 -15.98762;17.31098;6.32943;,
 -3.84188;17.31098;6.32943;,
 -15.98762;19.82258;6.32943;,
 -15.98762;19.82258;5.85853;,
 -15.98762;17.31098;5.85853;,
 -15.98762;17.31098;6.32943;,
 -3.84188;19.82258;5.85853;,
 -15.98762;19.82258;5.85853;,
 -15.98762;17.31098;5.85853;,
 -3.84188;17.31098;5.85853;;
 
 120;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 3;52,35,34;,
 3;53,38,35;,
 3;54,40,38;,
 3;55,42,40;,
 3;56,44,42;,
 3;57,46,44;,
 3;58,48,46;,
 3;59,50,48;,
 3;60,37,36;,
 3;61,36,39;,
 3;62,39,41;,
 3;63,41,43;,
 3;64,43,45;,
 3;65,45,47;,
 3;66,47,49;,
 3;67,49,51;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;80,73,84,85;,
 4;86,87,74,83;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;96,97,98,99;,
 4;100,101,102,103;,
 4;104,105,94,103;,
 4;106,107,108,109;,
 4;107,110,111,108;,
 4;110,112,113,111;,
 4;112,114,115,113;,
 4;114,116,117,115;,
 4;116,118,119,117;,
 4;118,120,121,119;,
 4;120,122,123,121;,
 4;122,124,125,123;,
 4;124,126,127,125;,
 4;126,128,129,127;,
 4;128,130,131,129;,
 4;130,132,133,131;,
 4;132,134,135,133;,
 4;134,136,137,135;,
 4;136,106,109,137;,
 4;132,130,138,134;,
 4;130,128,139,138;,
 4;128,126,140,139;,
 4;126,124,141,140;,
 4;124,122,120,141;,
 4;134,138,142,136;,
 4;138,139,143,142;,
 4;139,140,144,143;,
 4;141,120,118,145;,
 4;136,142,107,106;,
 4;142,143,110,107;,
 4;143,144,112,110;,
 4;144,145,114,112;,
 4;145,118,116,114;,
 4;135,146,131,133;,
 4;146,147,129,131;,
 4;147,148,127,129;,
 4;148,149,125,127;,
 4;149,121,123,125;,
 4;137,150,146,135;,
 4;150,151,147,146;,
 4;151,152,148,147;,
 4;152,153,149,148;,
 4;153,119,121,149;,
 4;109,108,150,137;,
 4;108,111,151,150;,
 4;111,113,152,151;,
 4;113,115,153,152;,
 4;115,117,119,153;,
 4;154,155,156,157;,
 4;158,159,160,161;,
 4;162,163,164,165;,
 4;166,167,168,169;,
 4;170,171,160,169;,
 4;157,156,155,154;,
 4;161,160,159,158;,
 4;165,164,163,162;,
 4;169,168,167,166;,
 4;172,173,174,175;,
 4;176,177,178,179;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;188,181,192,193;,
 4;194,195,182,191;;
 
 MeshMaterialList {
  6;
  120;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  1,
  3,
  3,
  3,
  3,
  3,
  1,
  3,
  3,
  3,
  3,
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
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.530400;0.530400;0.530400;1.000000;;
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
    "data\\TEXTURE\\haisuikou.png";
   }
  }
  Material {
   0.599216;0.800000;0.683922;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Kitchen.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\IH_off.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\grill.png";
   }
  }
 }
 MeshNormals {
  48;
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.707107;0.707107;0.000000;,
  1.000000;0.000001;0.000000;,
  0.707107;-0.707106;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.707107;-0.707107;0.000000;,
  -1.000000;0.000001;0.000000;,
  -0.707106;0.707107;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000001;1.000000;0.000000;,
  0.707107;0.707106;0.000000;,
  0.707108;-0.707106;-0.000000;,
  0.000001;-1.000000;-0.000000;,
  -0.707105;-0.707109;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.707105;0.707109;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000539;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.002121;0.999967;-0.007821;,
  0.002829;0.999496;-0.031617;,
  -0.003836;0.999487;-0.031786;,
  0.002640;0.999994;0.002074;,
  0.003520;0.999956;0.008694;,
  -0.003834;0.999953;0.008894;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.119287;-0.992860;,
  0.999870;-0.016137;-0.000000;,
  0.000000;-0.101848;0.994800;,
  -1.000000;0.000000;-0.000539;,
  0.000000;-0.999999;-0.001054;,
  0.000321;0.999878;-0.015642;,
  0.000321;0.998875;-0.047415;,
  -0.001918;0.998861;-0.047668;,
  -0.003836;0.999487;-0.031786;,
  -0.005753;0.999857;-0.015895;,
  -0.005751;0.999974;0.004447;,
  0.001359;0.999991;0.004147;,
  0.001359;0.999914;0.013041;,
  -0.001917;0.999909;0.013341;,
  -0.003834;0.999953;0.008894;,
  -0.999902;0.013983;0.000000;,
  0.000000;0.119287;0.992860;,
  -0.999870;0.016137;0.000000;,
  0.000000;0.101848;-0.994800;,
  0.999902;-0.013983;-0.000000;;
  120;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;10,11,11,10;,
  4;11,3,3,11;,
  4;3,12,12,3;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,10,10,16;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;9,9,9,9;,
  4;17,17,17,17;,
  4;0,0,0,0;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;27,27,27,27;,
  4;9,9,9,9;,
  4;18,18,18,18;,
  4;0,0,0,0;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;19,19,19,19;,
  4;19,19,19,19;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;20,33,21,20;,
  4;33,34,22,21;,
  4;34,35,23,22;,
  4;35,36,37,23;,
  4;20,20,20,20;,
  4;20,21,24,20;,
  4;21,22,25,24;,
  4;23,37,38,26;,
  4;20,20,20,20;,
  4;20,24,39,20;,
  4;24,25,40,39;,
  4;25,26,41,40;,
  4;26,38,42,41;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;43,43,43,43;,
  4;27,27,27,27;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;47,47,47,47;,
  4;20,20,20,20;,
  4;9,9,9,9;,
  4;17,17,17,17;,
  4;0,0,0,0;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;27,27,27,27;;
 }
 MeshTextureCoords {
  196;
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
  0.000000;0.000000;,
  1.000000;0.000000;,
  -0.467199;0.160971;,
  -0.298903;0.160971;,
  -0.298903;0.160520;,
  -0.467199;0.160520;,
  0.312359;0.160971;,
  0.312359;0.160520;,
  0.805631;0.160971;,
  0.805631;0.160520;,
  1.416894;0.160971;,
  1.416894;0.160520;,
  2.028158;0.160971;,
  2.028158;0.160520;,
  2.028158;0.387997;,
  2.028158;0.387546;,
  2.028158;0.615023;,
  2.028158;0.614572;,
  2.028158;0.842049;,
  2.028158;0.841598;,
  1.416894;0.842049;,
  1.416894;0.841598;,
  0.805631;0.842049;,
  0.805631;0.841598;,
  0.312359;0.842049;,
  0.312359;0.841598;,
  -0.298903;0.842049;,
  -0.298903;0.841598;,
  -0.467199;0.842049;,
  -0.467199;0.841598;,
  -0.467199;0.615023;,
  -0.467199;0.614572;,
  -0.467199;0.387997;,
  -0.467199;0.387546;,
  -0.298903;0.831924;,
  0.312359;0.831924;,
  0.858825;0.774713;,
  1.469396;0.774713;,
  -0.298903;0.322636;,
  0.312359;0.322636;,
  0.858825;0.401772;,
  1.469396;0.401772;,
  -0.298903;0.614572;,
  0.312359;0.614572;,
  0.805631;0.614572;,
  1.416894;0.614572;,
  -0.298903;0.387546;,
  0.312359;0.387546;,
  0.805631;0.387546;,
  1.416894;0.387546;,
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
  0.105319;0.855344;,
  0.737328;0.855365;,
  0.737334;0.167459;,
  0.105325;0.167438;,
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
