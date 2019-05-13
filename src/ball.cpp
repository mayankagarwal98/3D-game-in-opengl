#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotationx=0;
    this->rotationy=0;
    this->rotationz=0;
    speed = 0;
    this->lo_x={1,0,0};
    this->lo_y={0,1,0};
    this->lo_z={0,0,1};

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int vertexcount=0,n=30,vertexcount1=0; 
     static GLfloat vertex_buffer_data[100000] ;
     static GLfloat vertex_buffer_data1[100000] ;
     double r=0.5;     
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data[vertexcount++]=r*cos((2* M_PI*i)/n);
        vertex_buffer_data[vertexcount++]=r*sin((2* M_PI*i)/n);
        vertex_buffer_data[vertexcount++]=2;
        vertex_buffer_data[vertexcount++]=r*cos((2* M_PI*((i+1)%n))/n);
        vertex_buffer_data[vertexcount++]=r*sin((2* M_PI*((i+1)%n))/n);
        vertex_buffer_data[vertexcount++]=2;
        vertex_buffer_data[vertexcount++]=0.0f;
        vertex_buffer_data[vertexcount++]=0.0f;
        vertex_buffer_data[vertexcount++]=2;
    }
    //  for(int i=0;i<n;i++)
    // {
    //     vertex_buffer_data[vertexcount1++]=r*cos((2* M_PI*i)/n);
    //     vertex_buffer_data[vertexcount1++]=r*sin((2* M_PI*i)/n);
    //     vertex_buffer_data[vertexcount1++]=-2;
    //     vertex_buffer_data[vertexcount1++]=r*cos((2* M_PI*((i+1)%n))/n);
    //     vertex_buffer_data[vertexcount1++]=r*sin((2* M_PI*((i+1)%n))/n);
    //     vertex_buffer_data[vertexcount1++]=-2;
    //     vertex_buffer_data[vertexcount1++]=0.0f;
    //     vertex_buffer_data[vertexcount1++]=0.0f;
    //     vertex_buffer_data[vertexcount1++]=-2;
    // }
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data[vertexcount++]=r*cos((2* M_PI*i)/n);
        vertex_buffer_data[vertexcount++]=r*sin((2* M_PI*i)/n);
        vertex_buffer_data[vertexcount++]=2;
        vertex_buffer_data[vertexcount++]=r*cos((2* M_PI*((i+1)%n))/n);
        vertex_buffer_data[vertexcount++]=r*sin((2* M_PI*((i+1)%n))/n);
        vertex_buffer_data[vertexcount++]=2;
        vertex_buffer_data[vertexcount++]=r*cos((2* M_PI*i)/n);
        vertex_buffer_data[vertexcount++]=r*sin((2* M_PI*i)/n);
        vertex_buffer_data[vertexcount++]=-2;
        
        vertex_buffer_data[vertexcount++]=r*cos((2* M_PI*i)/n);
        vertex_buffer_data[vertexcount++]=r*sin((2* M_PI*i)/n);
        vertex_buffer_data[vertexcount++]=-2;
        vertex_buffer_data[vertexcount++]=r*cos((2* M_PI*((i+1)%n))/n);
        vertex_buffer_data[vertexcount++]=r*sin((2* M_PI*((i+1)%n))/n);
        vertex_buffer_data[vertexcount++]=-2;
        vertex_buffer_data[vertexcount++]=r*cos((2* M_PI*((i+1)%n))/n);
        vertex_buffer_data[vertexcount++]=r*sin((2* M_PI*((i+1)%n))/n);        
        vertex_buffer_data[vertexcount++]=2;

    }
     vertex_buffer_data1[vertexcount1++]=2;
     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=0;

     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=0;

     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=-2;

      vertex_buffer_data1[vertexcount1++]=-2;
     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=0;

     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=0;

     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=-2;

     vertex_buffer_data1[vertexcount1++]=3;
     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=2;

     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=2;

     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=1;

      vertex_buffer_data1[vertexcount1++]=-3;
     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=2;

     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=2;

     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=0;
     vertex_buffer_data1[vertexcount1++]=1;

    this->object = create3DObject(GL_TRIANGLES, vertexcount/3, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, vertexcount1/3, vertex_buffer_data1, {88,85,73}, GL_FILL);

}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotatex    = glm::rotate((float) (this->rotationx * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotatey    = glm::rotate((float) (this->rotationy * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotatez    = glm::rotate((float) (this->rotationz * M_PI / 180.0f), glm::vec3(0, 0, 1));
    this->rotation=rotatey*rotatex*rotatez;

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));

    this->lo_x={this->rotation[0][0],this->rotation[0][1],this->rotation[0][2]};
    this->lo_y={this->rotation[1][0],this->rotation[1][1],this->rotation[1][2]};
    this->lo_z={this->rotation[2][0],this->rotation[2][1],this->rotation[2][2]};

    Matrices.model *= (translate*this->rotation);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);

    draw3DObject(this->object);

}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->rotation += speed;
}

