uniform vec2 mousePos;
uniform float lightDistance;
uniform vec3 lightColor;
void main (void) 
{ 
    float dist = sqrt(pow(mousePos.x-gl_FragCoord.x, 2)+pow(mousePos.y-gl_FragCoord.y, 2));
	lightColor.r -= (dist/lightDistance);
	lightColor.g -= (dist/lightDistance);
	lightColor.b -= (dist/lightDistance);
	gl_FragColor = vec4(lightColor, dist);
	
}