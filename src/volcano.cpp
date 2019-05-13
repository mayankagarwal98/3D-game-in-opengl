#include "volcano.h"
#include "main.h"

Volcano::Volcano(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int vertexcount=0,n=30,vertexcount1=0,r1=15,r2=5; 
    static GLfloat vertex_buffer_data[1000000] ;
    static GLfloat vertex_buffer_data1[1000000] ;

    for(int i=0;i<n;i++)
    {
        vertex_buffer_data1[vertexcount1++]=r1*cos((2*M_PI*i)/n);
        vertex_buffer_data1[vertexcount1++]=0;
        vertex_buffer_data1[vertexcount1++]=r1*sin((2*M_PI*i)/n);

        vertex_buffer_data1[vertexcount1++]=r1*cos((2*M_PI*((i+1)%n)/n)) ;
        vertex_buffer_data1[vertexcount1++]=0;
        vertex_buffer_data1[vertexcount1++]=r1*sin((2*M_PI*((i+1)%n)/n)) ;

        vertex_buffer_data1[vertexcount1++]=0;
        vertex_buffer_data1[vertexcount1++]=0;
        vertex_buffer_data1[vertexcount1++]=0;

    }
    float x1=0.1;
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data[vertexcount++]=r2*cos((2*M_PI*i)/n);
        vertex_buffer_data[vertexcount++]=10;
        vertex_buffer_data[vertexcount++]=r2*sin((2*M_PI*i)/n);

        vertex_buffer_data[vertexcount++]=r2*cos((2*M_PI*((i+1)%n)/n)) ;
        vertex_buffer_data[vertexcount++]=10;
        vertex_buffer_data[vertexcount++]=r2*sin((2*M_PI*((i+1)%n)/n)) ;

        vertex_buffer_data[vertexcount++]=(r2+x1)*cos((2*M_PI*i)/n);
        vertex_buffer_data[vertexcount++]=10;
        vertex_buffer_data[vertexcount++]=(r2+x1)*sin((2*M_PI*i)/n);

        vertex_buffer_data[vertexcount++]=r2*cos((2*M_PI*((i+1)%n)/n)) ;
        vertex_buffer_data[vertexcount++]=10;
        vertex_buffer_data[vertexcount++]=r2*sin((2*M_PI*((i+1)%n)/n)) ;

        vertex_buffer_data[vertexcount++]=r2*cos((2*M_PI*((i+1)%n)/n)) ;
        vertex_buffer_data[vertexcount++]=10;
        vertex_buffer_data[vertexcount++]=r2*sin((2*M_PI*((i+1)%n)/n)) ;

        vertex_buffer_data[vertexcount++]=(r2+x1)*cos((2*M_PI*((i+1)%n)/n));
        vertex_buffer_data[vertexcount++]=10;
        vertex_buffer_data[vertexcount++]=(r2+x1)*sin((2*M_PI*((i+1)%n)/n));



    }
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data[vertexcount++]=r1*cos((2*M_PI*i)/n);
        vertex_buffer_data[vertexcount++]=0;
        vertex_buffer_data[vertexcount++]=r1*sin((2*M_PI*i)/n);

        vertex_buffer_data[vertexcount++]=r1*cos((2*M_PI*((i+1)%n)/n)) ;
        vertex_buffer_data[vertexcount++]=0;
        vertex_buffer_data[vertexcount++]=r1*sin((2*M_PI*((i+1)%n)/n)) ;

        vertex_buffer_data[vertexcount++]=r2*cos((2*M_PI*i)/n);
        vertex_buffer_data[vertexcount++]=10;
        vertex_buffer_data[vertexcount++]=r2*sin((2*M_PI*i)/n);

        vertex_buffer_data[vertexcount++]=r2*cos((2*M_PI*i)/n);
        vertex_buffer_data[vertexcount++]=10;
        vertex_buffer_data[vertexcount++]=r2*sin((2*M_PI*i)/n);

        vertex_buffer_data[vertexcount++]=r2*cos((2*M_PI*((i+1)%n)/n)) ;
        vertex_buffer_data[vertexcount++]=10;
        vertex_buffer_data[vertexcount++]=r2*sin((2*M_PI*((i+1)%n)/n)) ;


        vertex_buffer_data[vertexcount++]=r1*cos((2*M_PI*((i+1)%n)/n)) ;
        vertex_buffer_data[vertexcount++]=0;
        vertex_buffer_data[vertexcount++]=r1*sin((2*M_PI*((i+1)%n)/n)) ;

    }

    this->object = create3DObject(GL_TRIANGLES, vertexcount/3, vertex_buffer_data,  COLOR_BROWN , GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, vertexcount1/3, vertex_buffer_data1,COLOR_YELLOW, GL_FILL);

}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);


}

void Volcano::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Volcano::tick() {
    this->rotation += speed;
}

