varying float alti;

void main(void)
{
	vec4 clipCoord = gl_ModelViewProjectionMatrix * gl_Vertex;
	alti = clipCoord.y;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;	
	gl_FrontColor = gl_Color;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
