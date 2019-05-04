#include "camera.h"

#include "utils.h"

#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>

int jumped = 0;
int is_collided(float x, float y)
{
    if(y<8.2 && x<21.2 && x>-8.7){
        return true;
    }

    if(x<-8.7 && y>8.2 && y<23.9){
        return true;;
    }

    if(x<18.75 && x>-6.9 && y>9.5 && y<22.35) {
        return true;
    }

    if(y>22.35 && y<34.95 && x>5.85 && x<18.75){
        return true;
    }

    if(x<4 && x>-8.7 && y>23.9){
        return true;
    }

    if(x<21.2 && x>4 && y>36.7){
        return true;
    }

    if(y<36.7 && y>8.2 && x>21.2){
        return true;
    }

    return false;;
}
void init_camera(struct Camera* camera)
{
    camera->position.x = 4;
    camera->position.y = 8.7;
    camera->position.z = 4.3;

    camera->pose.x = 0;
    camera->pose.y = 0;
    camera->pose.z = 180;
}

void set_view_point(const struct Camera* camera)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(-(camera->pose.x + 90), 1.0, 0, 0);
	glRotatef(-(camera->pose.z - 90), 0, 0, 1.0);
	glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(struct Camera* camera, double horizontal, double vertical)
{
	camera->pose.z += horizontal;
	if(camera->pose.x <= 90.0 || camera->pose.x >= 270.0){
        camera->pose.x += vertical;
	}
	else if(camera->pose.x >= 90.0 && camera->pose.x < 200.0){
        camera->pose.x = 90.0;
	}
	else{
        camera->pose.x = 270.0;
	}


	if (camera->pose.z < 0) {
		camera->pose.z += 360.0;
	}

	if (camera->pose.z > 360.0) {
		camera->pose.z -= 360.0;
	}

	if (camera->pose.x < 0) {
		camera->pose.x += 360.0;
	}

	if (camera->pose.x > 360.0) {
		camera->pose.x -= 360.0;
	}
}
void move_camera_up(struct Camera* camera, double distance)
{
    if(camera->position.z >= 4.3 && jumped == 0){
    camera->position.z += distance;
    if(camera->position.z >= 4.5){
        jumped = 1;
        camera->position.z = 4.5;
    }
    }
    if(jumped == 1){
        camera->position.z -= distance;
        if(camera->position.z <= 4.3){
            jumped = 0;
            camera->position.z = 4.3;
        }
    }

}
void move_camera_forward(struct Camera* camera, double distance)
{
	double angle = degree_to_radian(camera->pose.z);
    if(!is_collided(camera->position.x,camera->position.y + sin(angle)*distance )){
    camera->position.y += sin(angle) * distance;
}
    if(!is_collided(camera->position.x + cos(angle) * distance ,camera->position.y)){
	camera->position.x += cos(angle) * distance;
    }
}

void move_camera_backward(struct Camera* camera, double distance)
{
	double angle = degree_to_radian(camera->pose.z);
    if(!is_collided(camera->position.x,camera->position.y - sin(angle)*distance )){
    camera->position.y -= sin(angle) * distance;
}
    if(!is_collided(camera->position.x - cos(angle) * distance ,camera->position.y)){
	camera->position.x -= cos(angle) * distance;
    }
}

void step_camera_left(struct Camera* camera, double distance)
{
	double angle = degree_to_radian(camera->pose.z + 90.0);
    if(!is_collided(camera->position.x,camera->position.y + sin(angle)*distance )){
        camera->position.y += sin(angle) * distance;
}
    if(!is_collided(camera->position.x + cos(angle) * distance ,camera->position.y)){
	camera->position.x += cos(angle) * distance;
    }
}

void step_camera_right(struct Camera* camera, double distance)
{
	double angle = degree_to_radian(camera->pose.z - 90.0);
    if(!is_collided(camera->position.x,camera->position.y + sin(angle)*distance )){
    camera->position.y += sin(angle) * distance;
}
    if(!is_collided(camera->position.x + cos(angle) * distance ,camera->position.y)){
	camera->position.x += cos(angle) * distance;
    }
}

