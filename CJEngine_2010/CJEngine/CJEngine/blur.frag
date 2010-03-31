varying float alti;

uniform sampler2D sampler0;

void main(void)
{
	vec4 txt_color;
	txt_color = texture2D(sampler0,gl_TexCoord[0].st);
	
	float greyscale = (txt_color.x+txt_color.y+txt_color.z)/3.0f;

	//gl_FragColor = vec4(1,1,1,1);
	
	if (alti > 200.0f)
		gl_FragColor = vec4(greyscale,greyscale,greyscale,txt_color.a);
	else
		gl_FragColor = txt_color;
	
}
