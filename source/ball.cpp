#include "ball.h"
#include "main.h"
#include <iostream>
using namespace std;

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->x = x;
    this->y = y;
    this->z = 0;
    speed = 1;
    angleX = 0;
    angleY = 0;
    angleZ = 0;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // The below data is vertices for elongated square bipyramid
    static const GLfloat vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end

        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,

        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,

        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,

        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,

        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,

        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,

        // upper pyramid. has some extra triangles :/
         0.0f,0.0f, 2.5f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        0.0f,0.0f, 2.50f,

        1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 2.50f,
        -1.0f, 1.0f, 1.0f,
        
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        0.0f,0.0f, 2.5f,

        0.0f,0.0f, 2.5f,
        1.0f, 1.0f, 1.0f,
        -1.0f,1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 2.50f,
        1.0f,-1.0f, 1.0f,

        // lower pyramid
        0.0f,0.0f, -2.5f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,

        0.0f, 0.0f,-2.50f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        
        -1.0f,-1.0f,-1.0f,
        0.0f, 0.0f, -2.5f,
        -1.0f, 1.0f,-1.0f,

        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        0.0f,0.0f,-2.50f,
        -1.0f, 1.0f,-1.0f,
    };

    //The below data is vertice for hexagonal bipyramid
    static const GLfloat vertex_buffer_data1[] = {
        // UPPER PART
        -1.732f, 0.0f, 1.0f,
        0.0f, 0.0f, 2.0f,
        0.0f, 4.0f, 0.0f,

        0.0f, 0.0f, 02.0f,        
        1.732f, 0.0f, 01.0f,
        0.0f, 04.0f, 0.0f,  

        01.732f, 0.0f, 01.0f,    
        01.732f, 0.0f, -01.0f,  
        0.0f, 04.0f, 0.0f,  

        01.732f, 0.0f, -01.0f, 
        0.0f, 0.0f, -02.0f,  
        0.0f, 04.0f, 0.0f,  

        0.0f, 0.0f, -02.0f,  
        -01.732f, 0.0f, -01.0f,  
        0.0f, 04.0f, 0.0f,  

        -01.732f, 0.0f, -01.0f,  
        -01.732f, 0.0f, 01.0f,    
        0.0f, 04.0f, 0.0f,   

        // LOWER PART
        -01.732f, 0.0f, 01.0f,  
        0.0f, 0.0f, 02.0f,     
        0.0f, -4.0f, 0.0f, 
 
        0.0f, 0.0f, 02.0f,      
        01.732f, 0.0f, 01.0f, 
        0.0f, -04.0f, 0.0f,    

        01.732f, 0.0f, 01.0f,  
        01.732f, 0.0f, -01.0f,   
        0.0f, -04.0f, 0.0f,   

        01.732f, 0.0f, -01.0f,  
        0.0f, 0.0f, -02.0f,    
        0.0f, -04.0f, 0.0f,  

        0.0f, 0.0f, -02.0f,      
        -01.732f, 0.0f, -01.0f, 
        0.0f, -04.0f, 0.0f, 

        -01.732f, 0.0f, -01.0f,   
        -01.732f, 0.0f, 01.0f,   
        0.0f, -04.0f, 0.0f,  
    };
    
    // The below data is vertices for decagonal bipyramid
    static const GLfloat vertex_buffer_data2[] = {
           // TOP VIEW TRIANGLES
        -00.618f, 0.0f, 01.902f,
        00.618f, 0.0f, 01.902f,   
        0.0f, 04.0f, 0.0f, 

        01.618f, 0.0f, 01.1756f,   
        00.618f, 0.0f, 01.902f,  
        0.0f, 04.0f, 0.0f, 

        01.618f, 0.0f, 01.1756f, 
        02.0f, 0.0f, 0.0f,       
        0.0f, 04.0f, 0.0f,

        01.618f, 0.0f, -01.1756f,   
        02.0f, 0.0f, 0.0f,    
        0.0f, 04.0f, 0.0f, 

        01.618f, 0.0f, -01.1756f,  
        00.618f, 0.0f, -01.902f,  
        0.0f, 04.0f, 0.0f,     

        -00.618f, 0.0f, -01.902f,
        00.618f, 0.0f, -01.902f,  
        0.0f, 04.0f, 0.0f,  

        -00.618f, 0.0f, -01.902f,  
        -01.618f, 0.0f, -01.1756f,    
        0.0f, 04.0f, 0.0f,  

        -02.0f, 0.0f, 0.0f,      
        -01.618f, 0.0f, -01.1756f,   
        0.0f, 04.0f, 0.0f,  

        -02.0f, 0.0f, 0.0f,       
        -01.618f, 0.0f, 01.1756f,      
        0.0f, 04.0f, 0.0f,  

        -00.618f, 0.0f, 01.902f,   
        -01.618f, 0.0f, 01.1756f, 
        0.0f, 04.0f, 0.0f,     

        // BOTTOM VIEW TRIANGLES
        -00.618f, 0.0f, 01.902f,    
        00.618f, 0.0f, 01.902f,      
        0.0f, 0.0f, 0.0f,    

        01.618f, 0.0f, 01.1756f, 
        00.618f, 0.0f, 01.902f,      
        0.0f, 0.0f, 0.0f,  

        01.618f, 0.0f, 01.1756f,      
        02.0f, 0.0f, 0.0f,   
        0.0f, 0.0f, 0.0f, 

        01.618f, 0.0f, -01.1756f,    
        02.0f, 0.0f, 0.0f,    
        0.0f, 0.0f, 0.0f,  

        01.618f, 0.0f, -01.1756f,     
        00.618f, 0.0f, -01.902f,     
        0.0f, 0.0f, 0.0f, 

        -00.618f, 0.0f, -01.902f,  
        0.618f, 0.0f, -01.902f,  
        0.0f, 0.0f, 0.0f,      

        -0.618f, 0.0f, -01.902f,    
        -01.618f, 0.0f, -01.1756f,   
        0.0f, 0.0f, 0.0f, 

        -02.0f, 0.0f, 0.0f,         
        -01.618f, 0.0f, -01.1756f,   
        0.0f, 0.0f, 0.0f,  

        -02.0f, 0.0f, 0.0f,  
        -01.618f, 0.0f, 01.1756f, 
        0.0f, 0.0f, 0.0f,  

        -00.618f, 0.0f, 01.902f,     
        -01.618f, .0f, 01.1756f,     
        0.0f, 0.0f, 0.0f,       
    };

    // The below data is colors for upto 22 or something triangles
    static const GLfloat color_buffer_data[] = {
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };
    
    // a means elongated bipyramid, b means hexagonal bipyramid and c means decagonal
    if(giveShape() == 'a')
        this->object = create3DObject(GL_TRIANGLES, 22*3, vertex_buffer_data, color_buffer_data, GL_FILL);
    else if(giveShape() == 'b')
        this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data1, color_buffer_data, GL_FILL);
    else if(giveShape() == 'c')
        this->object = create3DObject(GL_TRIANGLES, 20*3, vertex_buffer_data2, color_buffer_data, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    int a = 0, b = 1, c = 0;

    // Translation handling for the shapes
    if(give() == 11){
        this->x += 1;
        set_position(this->x, this->y, this->z);
        funn(0);
    }
    else if(give() == 12){
        this->x -= 1;
        set_position(this->x, this->y, this->z);
        funn(0);
    }
    else if(give() == 13){
        this->y += 1;
        set_position(this->x, this->y, this->z);
        funn(0);
    }
    else if(give() == 14){
        this->y -= 1;
        set_position(this->x, this->y, this->z);
        funn(0);
    }
    else if(give() == 15){
        this->z += 1;
        set_position(this->x, this->y, this->z);
        funn(0);
    }
    else if(give() == 16){
        this->z -= 1;
        set_position(this->x, this->y, this->z);
        funn(0);
    }
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(a, b, c));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Ball::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

