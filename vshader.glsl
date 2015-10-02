#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform highp mat4 mvMatrix;
uniform highp mat4 pMatrix;
uniform highp mat3 nMatrix;

attribute vec4 a_position;
attribute vec2 a_texcoord;
attribute vec3 a_normal;

varying vec2 v_texcoord;

varying vec3 vNormalEye;
varying vec3 vPositionEye3;

uniform highp vec3 lightPosition;
uniform lowp vec3 ambientColor;
uniform lowp vec3 diffuseColor;
uniform lowp vec3 specularColor;

void main()
{
    // Get vertex position in eye coordinates and send to the fragment shader
    vec4 vertexPositionEye4 = mvMatrix * a_position;
    vPositionEye3 = vertexPositionEye4.xyz / vertexPositionEye4.w;
    // Transform the normal to eye coordinates and send to fragment shader
    vNormalEye = normalize(nMatrix * a_normal);
    // Transform the geometry
    gl_Position = pMatrix * mvMatrix * a_position;

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = a_texcoord;
}
