namespace FSGL
{

static const GLchar* vertexShaderSource =
    "#version 100\n"
    "uniform mat4 projectionMatrix;\n"
    "uniform mat4 viewMatrix;\n"
    "uniform mat4 modelMatrix;\n"
    "const int kMaxBones = 64;\n"

    "uniform mat4 bonesMatrices[kMaxBones];\n"

    "attribute vec2 bone0info;\n"
    "attribute vec2 bone1info;\n"
    "attribute vec2 bone2info;\n"
    "attribute vec2 bone3info;\n"

    "attribute vec4 vertex;\n"
    "attribute vec2 uvIn;\n"

    "varying vec2 uvOut;\n"
    "void main() {\n"

    "int bone0Index = int(bone0info.x);\n"
    "float bone0weight = bone0info.y;\n"
    "mat4 bone0matrix = bonesMatrices[bone0Index];\n"

    "int bone1Index = int(bone1info.x);\n"
    "float bone1weight = bone1info.y;\n"
    "mat4 bone1matrix = bonesMatrices[bone1Index];\n"

    "int bone2Index = int(bone2info.x);\n"
    "float bone2weight = bone2info.y;\n"
    "mat4 bone2matrix = bonesMatrices[bone2Index];\n"

    "int bone3Index = int(bone3info.x);\n"
    "float bone3weight = bone3info.y;\n"
    "mat4 bone3matrix = bonesMatrices[bone3Index];\n"

    "vec4 animatedVertex =  bone0matrix * vertex * bone0weight +"
    "bone1matrix * vertex * bone1weight +"
    "bone2matrix * vertex * bone2weight +"
    "bone3matrix * vertex * bone3weight;\n"

    "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * animatedVertex;\n"
    "   uvOut = uvIn;\n"
    "}\n";

static const GLchar* fragmentShaderSource =
    "#version 100\n"
    "precision mediump int;\n"
    "precision mediump float;\n"
    "precision mediump sampler2D;\n"
    "precision mediump samplerCube;\n"
    "varying mediump vec2 uvOut;\n"
    "uniform sampler2D texture;\n"
    "uniform float brightness;\n"
    "void main() {\n"
    "vec4 color = texture2D(texture, uvOut);\n"
    "color.r = brightness * color.r;\n"
    "color.g = brightness * color.g;\n"
    "color.b = brightness * color.b;\n"
    "if (color.a < 0.5) {\n"
    "	discard;\n"
    "}\n"
    "   gl_FragColor = color;"
    "}\n";

}