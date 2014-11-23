uniform vec2 mousePos;

void main(void)
{
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}