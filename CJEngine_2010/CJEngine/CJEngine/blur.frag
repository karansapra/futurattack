varying float alti;

uniform sampler2D sampler0;

void main(void)
{
	vec4 txt_color;	
	txt_color = texture2D(sampler0,gl_TexCoord[0].st);
	
	float greyscale = (txt_color.x+txt_color.y+txt_color.z)/3.0f;

	if (alti < 0.0f)
		gl_FragColor = vec4(greyscale,greyscale,greyscale,txt_color.a);
	else
		gl_FragColor = vec4(txt_color.r*0.5f,txt_color.g+0.2f,txt_color.b*0.5f,txt_color.a);
}
