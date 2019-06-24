#include<windows.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<gl/glut.h>
#include<math.h>
#include<iostream>
#pragma region Class

#pragma region AboutKeyBoard

bool isDown = false;

int firstRDown = 0;

#pragma endregion

float r = 200.0f;


struct look {
	GLint initx;
	GLint inity;
	GLint endx;
	GLint endy;
}jlook;

float changex = 0;
float changey = 0;
float changez = 0;

float lookx = 0;
float looky = 0;
float lookz = 0;
float blookx = 0;
float blooky = 0;
float blookz = 0;


float vx = 0;
float vy = 0;
float vz = 0;
float angle = 0;

class window {
public:
	window() { wdw = 0; wdh = 0; };
	GLsizei wdw;
	GLsizei wdh;
}wind;

class Leaf {
public:
	void creatLeaf(GLint x, GLint y);
private:
	float time;//当生成是开始记录时间
	//记录落叶得位置
	float x;
	float y;
	float z;
};
class Man {
private:
	//头和身体公用一个position
	float pos;
	//观察人体知不同的一同模组
	float kneeR[3];
	float KneeL[3];
	float FootR[3];
	float FootL[3];
	float HandR[3];
	float HandL;
};
#pragma endregion

void SetupRC()
{
	glClearColor(1, 1, 1, 1);
}
void ChangeSize(GLsizei w,GLsizei h)
{
	glViewport(0, 0, w, h);

	if (h == 0)h = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, (GLfloat)w / (GLfloat)h, 1, 2000);
	wind.wdh = h;
	wind.wdw = w;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
//通过使用右键菜单控制状态 设定为不同的状态机
#pragma region WalkMan

#pragma region 手部旋转
float HandRot = 0;
#pragma endregion
#pragma region 腿部旋转

float BigLegRot = 0;
float SmallLegRot = 0;

#pragma endregion
float BLRotS = 2.5f;//大腿旋转速度
float SLRotS = 5.0f;//小腿旋转速度
float HRotS = 6.5f;
float PosTrans = 0.5f;//身体移动速度
float PosRot = 0.5f;
float ypos = 0.0f;

void WalkMan_Stand()
{

}
void WalkMan_Walk()
{
	

}
void WalkMan_Jump()
{
	if (ypos > 13.0f || ypos < -1.0f)
		PosTrans = -PosTrans;
	if (BigLegRot < -65.0f||BigLegRot >5.0f)
		BLRotS = -BLRotS;
	if (SmallLegRot > 130.0f || SmallLegRot <-10.0f)
		SLRotS = -SLRotS;
	
	if (HandRot < -182.0f || HandRot > 0.0f)
		HRotS = -HRotS;
	HandRot += HRotS;
	BigLegRot -= BLRotS;
	SmallLegRot += SLRotS;
	ypos -= PosTrans;
}
void Right_Hand()
{
	glPushMatrix();
	
	glTranslatef(15.0f, 15.0f, 0.0f);
	glRotatef(HandRot, 1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(5.0f, -25.0f, 0.0f);
	glEnd();
	glPopMatrix();
}
void Left_Hand()
{
	glPushMatrix();
	
	glTranslatef(-15.0f, 15.0f, 0.0f);
	glRotatef(HandRot, 1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-5.0f, -25.0f, 0.0f);
	glEnd();
	glPopMatrix();
}
void Left_Leg()
{
	glPushMatrix();
	glTranslatef(-5.0f, -15.0f, 0.0f);
	glRotatef(BigLegRot, 1, 0, 0);

	//大腿
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -10.0f, 0.0f);
	glEnd();


	glTranslatef(0.0f, -10.0f, 0.0f);
	glRotated(SmallLegRot, 1, 0, 0);
	//小腿
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -15.0f, 0.0f);
	glEnd();
	glPopMatrix();

}
void Right_Leg()
{
	glPushMatrix();
	glTranslatef(5.0f, -15.0f, 0.0f);//定位移动至有效位置定位
	glRotatef(BigLegRot, 1, 0, 0);//大腿旋转
	
	//大腿
	glBegin(GL_LINES);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f, -10.0f, 0.0f);
	glEnd();

	
	glTranslatef(0.0f, -10.0f, 0.0f);
	glRotated(SmallLegRot, 1, 0, 0);//小腿旋转
	//小腿
	glBegin(GL_LINES);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f, -15.0f, 0.0f);
	glEnd();
	glPopMatrix();

}
void WalkMan()
{
	//用来旋转
	glRotatef(PosRot,0,1,0);
	//用来跳跃
	glTranslatef(0.0f, ypos, 0.0f);

	//头部定位
	glTranslatef(0.0f, 65.0f, 0.0f);

	glColor3f(1, 0, 0);
	glutWireCube(30);
	//脖子定位
	glTranslatef(0.0f, -20.0f, 0.0f);

	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glEnd();
	//身体定位
	glTranslatef(0.0f,-45.0f,0.0f);
	glScalef(1.5f, 3.0f, 1.0f);
	glutWireCube(30);

	Right_Hand();
	Left_Hand();
	
	
	glColor3f(0, 0, 1);
	Right_Leg();
	Left_Leg();

	

	glLoadIdentity();
	
	

}

#pragma endregion
#pragma region Mouse

void LeftMouseDown(GLint button, GLint action, GLint mousex, GLint mousey)
{
	
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{

	}
	if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)
	{
		isDown = true;
		//备份移动之前的坐标
		blookx = lookx;
		blooky = looky;
		blookz = lookz;
		//按下保存当前坐标
		jlook.initx = mousex; jlook.inity = mousey;
		glutPostRedisplay();
		

	}
	if (button == GLUT_RIGHT_BUTTON && action == GLUT_UP)
	{
		//弹起时不在移动视角
		isDown = false;
	}
}
void RightMouseMove(GLint mousex, GLint mousey)
{
	//此时mousex和mousey是以屏幕坐标系为主 但我只是用其方向向量。不进行改变
	if (isDown) {
		jlook.endx = mousex;
		jlook.endy = mousey;

		float mathx = (jlook.initx - jlook.endx), mathy = -(jlook.inity - jlook.endy);
		float l = sqrt(mathx * mathx + mathy * mathy);

		vx = mathx;
		vy = mathy;
		angle = l / r;

		changex = mathx / l * r * sin(l / r);
		changey = mathy / l * r * sin(l / r);
		changez = r * (cos(l / r));


		lookx =blookx+changex;
		looky =blooky+ changey;
		lookz = r-pow((pow(r, 2) - pow(lookx, 2) + pow(lookx, 2)), 1 / 2);
		
		glutPostRedisplay();
		std::cout << "lookx:" << changex << "looky:" << changey << "lookz:" << changez << std::endl;
		std::cout << "max" << (pow(lookx, 2) + pow(lookx, 2)+ pow(lookz, 2)) << std::endl;
	}
}
#pragma endregion
#pragma region keyboard
void keyboard(unsigned char key,int x,int y)
{
	switch (key)
	{case 'z':
		WalkMan_Jump();
		break;
	case'x':
		SmallLegRot -= 5;
		break;
	case'd':
		PosRot += 5.0f;
		break;
	case'a':
		PosRot -= 5.0f;
		break;



	}
	glutPostRedisplay();

}

#pragma endregion
#pragma region FallLeaf

//点击时落下叶片，一段时间后消失
void FallLeaf()
{

}

#pragma endregion
void RenderScence() 
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 重置模型视图矩阵   
	glMatrixMode(GL_MODELVIEW);   
	glLoadIdentity(); 
	
	//将图形沿 z 轴负向移动   

	gluLookAt(lookx, looky, lookz, 0, 0, 0 , 0, 1, 0);
	//glRotated(angle, vx, vy, 0);
	
	glColor3f(0, 1, 0);
	glutWireCube(200);
	
	
	WalkMan();

	
	glutSwapBuffers();
}
int main(int argc, char* argv[])
{
	std::cout << "右键拖动改变视角，a d旋转 z长按跳跃";
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("CG6");
	glutDisplayFunc(RenderScence);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutKeyboardFunc(keyboard);
	glutMouseFunc(LeftMouseDown);
	glutMotionFunc(RightMouseMove);
	glutSwapBuffers();
	glutMainLoop();
}