#include<gl/freeglut.h>
#include<gl/glut.h>
#include<stdlib.h>
#include <cmath>
#include <iostream>
using namespace std;

//Deklarasi Fungsi Keyboard
float translateX = 0.0f;
float translateY = 0.0f;
float scaleCam = 1.0f;
float scaleObjek = 1.0f;
float rotateAngle = 0.0f;

//Deklarasi fungsi Mouse 
float xrot = 0;
float yrot = 0;
float xdiff = 0;
float ydiff = 0;

bool cartesius = false;
bool cartesius2 = false;

int windowWidth = 800;
int windowHeight = 600;

GLfloat intensitasCahaya[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat posisiCahaya[] = { 2.0f, 2.0f, 2.0f, 0.0f };
GLfloat posisiCahayaTeko[] = { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat posisiCahayaRuangan[] = { 1.0f, 1.0f, 1.0f, 8.0f };
GLfloat bahan_ambient[] = { 1, 1, 1, 1 };
GLfloat bahan_diffuse[] = { 1, 1, 1, 1 };
GLfloat bahan_specular[] = { -1.0f, 1.0f, -1.0f, 1.0f };
GLfloat bahan_shininess[] = { 90.0f };

void Note() {

	cout << "================================================================" << endl;
	cout << "\n\t\t\t \"ruang makan\" \n" << endl;
	cout << "================================================================" << endl;
	cout << "\n\t M Nizar Ariz  \t\t (2306059) " << endl;
	cout << "\n\t Sandra Oktavia  \t\t (2306037) " << endl;
	cout << "\n\t Fazriel Mutaqien \t\t (2306047) " << endl;

	cout << "================================================================" << endl;
	cout << "\n\t\t Tugas Besar Kelompok ... \n" << endl;
	cout << "================================================================" << endl;

	cout << "			Fungsi Keyboard  " << endl;
	cout << "______________________" << endl;
	cout << "| \'Z\' | Memperdekat Kamera  " << endl;
	cout << "| \'X\' | Untuk Memperjauh Kamera  " << endl;
	cout << "| \'J\' | Untuk Memperbesar Objek teko  " << endl;
	cout << "| \'H\' | Untuk Memperkecil Objek teko  " << endl;
	cout << "| \'Q\' | Untuk Membuat Objek gelas Berputar kekiri  " << endl;
	cout << "| \'E\' | Untuk Membuat Objek gelas Berputar kekanan  " << endl;
	cout << "| \'W\' | Untuk Menggerakkan view objek ke atas  " << endl;
	cout << "| \'A\' | Untuk Menggerakkan view objek ke kiri  " << endl;
	cout << "| \'S\' | Untuk Menggerakkan view objek ke bawah  " << endl;
	cout << "| \'D\' | Untuk Menggerakkan view objek ke kanan " << endl;
	cout << "| \'O\' | Untuk Menggerakkan objek Teko ke atas  " << endl;
	cout << "| \'K\' | Untuk Menggerakkan objek Teko ke kiri  " << endl;
	cout << "| \'L\' | Untuk Menggerakkan objek Teko ke bawah  " << endl;
	cout << "| \';\' | Untuk Menggerakkan objek Teko ke kanan \n" << endl;
	cout << "| \'2\' | Men-aktifkan Garis Cartecius" << endl;
	cout << "| \'3\' | Men-non-aktifkan Garis Cartecius" << endl;
	cout << "| \'4\' | Men-aktifkan Garis Cartecius 3D" << endl;
	cout << "| \'5\' | Men-non-aktifkan Garis Cartecius 3D" << endl;
	cout << "================================================================" << endl;

	cout << "			Garis Cartecius  " << endl;
	cout << "| 'Merah'| Positive X " << endl;
	cout << "| 'Hijau' | Positive Y " << endl;
	cout << "| 'Biru' | Positive Z /n" << endl;

	cout << "| 'Merah Tua '| Negative X " << endl;
	cout << "| 'Hijau Tua' | Negative Y " << endl;
	cout << "| 'Biru Tua' | Negative Z " << endl;
	cout << "================================================================" << endl;


}

void ukur(int lebar, int tinggi) {
	if (tinggi == 0) tinggi = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, lebar / tinggi, 10, 900);
	glTranslatef(0, 0, -200);// jarak object dari lembaran kerja
	glMatrixMode(GL_MODELVIEW);
}
void myinit(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	//	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	//	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	//	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	//	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	//
	////	glShadeModel(GL_FLAT);
	//	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glPointSize(10.0);
	glLineWidth(7.0f);
}




void DrawAnchoredGraph() {
	glDisable(GL_DEPTH_TEST);
	// Save the current projection matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	// Set orthographic projection for positioning in 2D
	glOrtho(0.0, windowWidth, 0.0, windowHeight, -1000.0, 1000.0);

	// Switch to model-view matrix and reset transformations
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_LIGHTING);

	// Translate the graph to the top-right corner
	float offsetX = windowWidth - 100.0f; // Offset from the right
	float offsetY = windowHeight - 100.0f; // Offset from the top
	glTranslatef(offsetX, offsetY, 0.0f);

	// Apply user-controlled rotations
	glRotatef(xrot, 1.0f, 0.0f, 0.0f); // Rotate around X-axis
	glRotatef(yrot, 0.0f, 1.0f, 0.0f); // Rotate around Y-axis

	glLineWidth(0.5f); // Thinner lines
	// Define nodes for the 3D "+" shape
	struct Node {
		float x, y, z;
	};
	Node nodes[] = {
		{0.0f, 50.0f, 0.0f},   // Top (Y+)
		{0.0f, -50.0f, 0.0f},  // Bottom (Y-)
		{-50.0f, 0.0f, 0.0f},  // Left (X-)
		{50.0f, 0.0f, 0.0f},   // Right (X+)
		{0.0f, 0.0f, 50.0f},   // Above (Z+)
		{0.0f, 0.0f, -50.0f}   // Below (Z-)
	};

	// Draw edges
	glColor3f(1.0f, 1.0f, 1.0f); // White
	glBegin(GL_LINES);
	for (int i = 0; i < 6; i++) {
		glVertex3f(nodes[i].x, nodes[i].y, nodes[i].z); // Connect each node to the origin
		glVertex3f(0.0f, 0.0f, 0.0f);
	}
	glEnd();

	// Draw nodes
	auto drawNode = [](float x, float y, float z, float radius) {
		glPushMatrix();
		glTranslatef(x, y, z); // Position the node
		glutSolidSphere(radius, 16, 16); // Draw a sphere at the node position
		glPopMatrix();
		};

	glColor3f(0.0f, 0.5f, 0.0f); // Dark Green
	drawNode(nodes[2].x, nodes[2].y, nodes[2].z, 5.0f); // (Y-)

	glColor3f(0.0f, 1.0f, 0.0f); // Green
	drawNode(nodes[3].x, nodes[3].y, nodes[3].z, 5.0f); // (Y+)

	glColor3f(0.0f, 0.0f, 1.0f);  // Blue
	drawNode(nodes[0].x, nodes[0].y, nodes[0].z, 5.0f); //  (Z+)

	glColor3f(0.0f, 0.0f, 0.5f);  // Dark Blue
	drawNode(nodes[1].x, nodes[1].y, nodes[1].z, 5.0f); // (Z-)

	glColor3f(1.0f, 0.0f, 0.0f); // Red
	drawNode(nodes[4].x, nodes[4].y, nodes[4].z, 5.0f); // (X+)

	glColor3f(0.5f, 0.0f, 0.0f); // Dark Red
	drawNode(nodes[5].x, nodes[5].y, nodes[5].z, 5.0f); // (X-)
	// Restore matrices
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}

void drawCartesianLines() {
	// Disable lighting to ensure no lighting effects on the lines
	glDisable(GL_LIGHTING);

	// Disable depth testing to ensure the lines are drawn in front of everything
	glDisable(GL_DEPTH_TEST);

	// Set line width for visibility
	glLineWidth(1.5f);

	glBegin(GL_LINES);

	// Horizontal line (Y-axis)
	glColor3f(0.0f, 1.0f, 0.0f); // Green for Y-axis
	glVertex3f(-600.0f, 0.0f, 0.0f); // Far left
	glVertex3f(600.0f, 0.0f, 0.0f);  // Far right

	// Vertical line (Z-axis)
	glColor3f(0.0f, 0.0f, 1.0f); // Blue for Z-axis
	glVertex3f(0.0f, -600.0f, 0.0f); // Bottom
	glVertex3f(0.0f, 600.0f, 0.0f);  // Top

	// Horizontal line (X-axis)
	glColor3f(1.0f, 0.0f, 0.0f); // Red for X-axis
	glVertex3f(0.0f, 0.0f, -600.0f); // Back
	glVertex3f(0.0f, 0.0f, 600.0f);  // Front

	glEnd();

	// Re-enable depth testing and lighting after drawing the lines
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void Cangkir(float radius, float height, int slices) {

	glLightfv(GL_LIGHT0, GL_POSITION, posisiCahayaTeko);
	glLightfv(GL_LIGHT0, GL_SPECULAR, intensitasCahaya);


	glRotatef(rotateAngle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= slices; ++i) {
		float theta = 2.0f * 3.1415926f * float(i) / float(slices);
		float x = radius * cos(theta);
		float y = radius * sin(theta);

		glVertex3f(x, y, 0.0f);
		glVertex3f(x, y, height);
	}
	glEnd();

	// Tutup bagian atas dan bawah
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i <= slices; ++i) {
		float theta = 2.0f * 3.1415926f * float(i) / float(slices);
		float x = radius * cos(theta);
		float y = radius * sin(theta);

		glVertex3f(x, y, 0.0f);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, height);
	for (int i = 0; i <= slices; ++i) {
		float theta = 2.0f * 3.1415926f * float(i) / float(slices);
		float x = radius * cos(theta);
		float y = radius * sin(theta);

		glVertex3f(x, y, height);
	}
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-4, 0, 5);
	glRotatef(180, 0, 10, 10);
	glutSolidTorus(1.0, 4.0, 50, 50);

}

void Ruangan() {
	//	Depan
	glLightfv(GL_LIGHT0, GL_POSITION, posisiCahayaRuangan);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, intensitasCahaya);

	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-200, -40, 200);
	glVertex3f(-200, 200, 200);
	glVertex3f(200, 200, 200);
	glVertex3f(200, -40, 200);
	glEnd();
	glPopMatrix();

	//	Belakang
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-200, -40, -200);
	glVertex3f(-200, 200, -200);
	glVertex3f(200, 200, -200);
	glVertex3f(200, -40, -200);
	glEnd();
	glPopMatrix();

	//	Kiri
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-200, -40, 200);
	glVertex3f(-200, 200, 200);
	glVertex3f(-200, 200, -200);
	glVertex3f(-200, -40, -200);
	glEnd();
	glPopMatrix();

	//	Kanan
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(200, -40, 200);
	glVertex3f(200, 200, 200);
	glVertex3f(200, 200, -200);
	glVertex3f(200, -40, -200);
	glEnd();
	glPopMatrix();

	//	Atas
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex3f(-200, 200, 200);
	glVertex3f(200, 200, 200);
	glVertex3f(-200, 200, -200);
	glVertex3f(200, 200, -200);
	glVertex3f(200, 200, 200);
	glVertex3f(200, 200, -200);
	glEnd();
	glPopMatrix();
}

void Dekor() {
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex3f(-100, 100, 199);
	glVertex3f(100, 100, 199);
	glVertex3f(100, 0, 199);
	glVertex3f(-100, 0, 199);
	glVertex3f(100, 0, 199);
	glVertex3f(-100, 100, 199);
	glEnd();
	glPopMatrix();

	//	Bingkai
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(-100, 100, 198);
	glVertex3f(-100, 0, 198);
	glVertex3f(-90, 0, 198);
	glVertex3f(-90, 100, 198);


	glVertex3f(-100, 100, 198);
	glVertex3f(-100, 0, 198);
	glVertex3f(-90, 0, 198);
	glVertex3f(-90, 100, 198);
	//	glVertex3f(100, 0, 199);
	//	glVertex3f(-100, 100, 199);
	glEnd();
	glPopMatrix();


}

void Lantai() {

	glLightfv(GL_LIGHT0, GL_POSITION, posisiCahaya);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, intensitasCahaya);
	glMaterialfv(GL_FRONT, GL_AMBIENT, bahan_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, bahan_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, bahan_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, bahan_shininess);

	//	    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	//    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	//    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	//    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	//
	//    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	//    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	//
	//    glEnable(GL_LIGHTING);
	//    glEnable(GL_LIGHT0);
	//    glEnable(GL_DEPTH_TEST);
	//
	//    // Inisialisasi material
	//    GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	//    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	//    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//    GLfloat mat_shininess[] = { 100.0f };
	//
	//    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	//    
		//Pola Lantai
	//	vertikal
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-200, -40, 160);
	glVertex3f(200, -40, 160);
	glVertex3f(-200, -40, 120);
	glVertex3f(200, -40, 120);
	glVertex3f(-200, -40, 80);
	glVertex3f(200, -40, 80);
	glVertex3f(-200, -40, 40);
	glVertex3f(200, -40, 40);
	glVertex3f(-200, -40, 0);
	glVertex3f(200, -40, 0);
	glVertex3f(-200, -40, -40);
	glVertex3f(200, -40, -40);
	glVertex3f(-200, -40, -80);
	glVertex3f(200, -40, -80);
	glVertex3f(-200, -40, -120);
	glVertex3f(200, -40, -120);
	glVertex3f(-200, -40, -160);
	glVertex3f(200, -40, -160);
	glEnd();
	glPopMatrix();

	//	Horizontal
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(160, -40, -200);
	glVertex3f(160, -40, 200);
	glVertex3f(120, -40, -200);
	glVertex3f(120, -40, 200);
	glVertex3f(80, -40, -200);
	glVertex3f(80, -40, 200);
	glVertex3f(40, -40, -200);
	glVertex3f(40, -40, 200);
	glVertex3f(0, -40, -200);
	glVertex3f(0, -40, 200);
	glVertex3f(-40, -40, -200);
	glVertex3f(-40, -40, 200);
	glVertex3f(-80, -40, -200);
	glVertex3f(-80, -40, 200);
	glVertex3f(-120, -40, -200);
	glVertex3f(-120, -40, 200);
	glVertex3f(-160, -40, -200);
	glVertex3f(-160, -40, 200);
	glEnd();
	glPopMatrix();

	//	Lantai Atas
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex3f(-200, -40, 200);
	glVertex3f(200, -40, 200);
	glVertex3f(-200, -40, -200);
	glVertex3f(200, -40, -200);
	glVertex3f(200, -40, 200);
	glVertex3f(200, -40, -200);
	glEnd();
	glPopMatrix();

	//	Lantai Bawah
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex3f(-200, -50, 200);
	glVertex3f(200, -50, 200);
	glVertex3f(-200, -50, -200);
	glVertex3f(200, -50, -200);
	glVertex3f(200, -50, 200);
	glVertex3f(200, -50, -200);
	glEnd();
	glPopMatrix();

	//	LantaiDepan
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0, 1, 1);
	glVertex3f(-200, -40, 200);
	glVertex3f(-200, -50, 200);
	glVertex3f(200, -50, 200);
	glVertex3f(200, -40, 200);
	glEnd();
	glPopMatrix();

	//	LantaiBelakang
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0, 1, 1);
	glVertex3f(-200, -40, -200);
	glVertex3f(-200, -50, -200);
	glVertex3f(200, -50, -200);
	glVertex3f(200, -40, -200);
	glEnd();
	glPopMatrix();

	//	LantaiSampingKanan
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0, 1, 1);
	glVertex3f(200, -40, -200);
	glVertex3f(200, -40, 200);
	glVertex3f(200, -50, 200);
	glVertex3f(200, -50, -200);
	glVertex3f(200, -50, 200);
	glVertex3f(200, -40, -200);
	glEnd();
	glPopMatrix();

	//	LantaiSampingKiri
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0, 1, 1);
	glVertex3f(-200, -40, -200);
	glVertex3f(-200, -40, 200);
	glVertex3f(-200, -50, 200);
	glVertex3f(-200, -50, -200);
	glVertex3f(-200, -50, 200);
	glVertex3f(-200, -40, -200);
	glEnd();
	glPopMatrix();


	//	glPushMatrix();
	//	glBegin(GL_POLYGON);
	//	glColor3f(1,1,1);
	//	glVertex3f(-200,-50,200);
	//	glVertex3f(200,-50,200);
	//	glVertex3f(-200,-50,-200);
	//	glVertex3f(200,-50,-200);
	//	glEnd();
	//	glPopMatrix();
	//
	//	glPushMatrix();
	//	glBegin(GL_POLYGON);
	//	glColor3f(1,1,1);
	//	glVertex3f(-200,-40,200);
	//	glVertex3f(200,-40,200);
	//	glVertex3f(-200,-40,-200);
	//	glVertex3f(200,-40,-200);
	//	glEnd();
	//	glPopMatrix();
	//
	//glPushMatrix();
	//	glBegin(GL_POLYGON);
	//	glColor3f(1,1,1);
	//	glVertex3f(-200,-40,200);
	//	glVertex3f(200,-40,200);
	//	glVertex3f(-200,-40,-200);
	//	glVertex3f(200,-40,-200);
	//	glEnd();
	//	glPopMatrix();

}


void Meja() {

	//ALAS MEJA
	glBegin(GL_POLYGON);//ATAS
	//	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	//	glEnable(GL_COLOR_MATERIAL);

	glColor3f(0.5, 0.2, 0);
	glVertex3f(-50, 15, 80);
	glVertex3f(50, 15, 80);
	glVertex3f(50, 15, -10);
	glVertex3f(-50, 15, -10);
	glEnd();
	glBegin(GL_POLYGON);//BAWAH
	glColor3f(0.5, 0.2, 0);
	glVertex3f(-50, 10, 80);
	glVertex3f(50, 10, 80);
	glVertex3f(50, 10, -10);
	glVertex3f(-50, 10, -10);
	glEnd();
	glBegin(GL_POLYGON);//SAMPING KANAN
	glColor3f(0.5, 0.2, 0);
	glVertex3f(50, 10, 80);
	glVertex3f(50, 15, 80);
	glVertex3f(50, 15, -10);
	glVertex3f(50, 10, -10);
	glEnd();
	glBegin(GL_POLYGON);//SAMPING KIRI
	glColor3f(0.5, 0.2, 0);
	glVertex3f(-50, 10, 80);
	glVertex3f(-50, 15, 80);
	glVertex3f(-50, 15, -10);
	glVertex3f(-50, 10, -10);
	glEnd();
	glBegin(GL_POLYGON);//DEPAN
	glColor3f(0.5, 0.2, 0);
	glVertex3f(-50, 10, 80);
	glVertex3f(-50, 15, 80);
	glVertex3f(50, 15, 80);
	glVertex3f(50, 10, 80);
	glEnd();
	glBegin(GL_POLYGON);//BELAKANG
	glColor3f(0.5, 0.2, 0);
	glVertex3f(-50, 10, -10);
	glVertex3f(-50, 15, -10);
	glVertex3f(50, 15, -10);
	glVertex3f(50, 10, -10);
	glEnd();

	//KAKI MEJA 1
	glBegin(GL_POLYGON);//ALAS BAWAH
	glColor3f(0.5, 0.2, 0);
	glVertex3f(-50, -40, 70);
	glVertex3f(-40, -40, 70);
	glVertex3f(-40, -40, 80);
	glVertex3f(-50, -40, 80);
	glEnd();
	glBegin(GL_POLYGON);//DEPAN
	glColor3f(0.5, 0.2, 0);
	glVertex3f(-50, 10, 80);
	glVertex3f(-40, 10, 80);
	glVertex3f(-40, -40, 80);
	glVertex3f(-50, -40, 80);
	glEnd();
	glBegin(GL_POLYGON);//BELAKANG
	glColor3f(0.5, 0.2, 0);
	glVertex3f(-50, 10, 70);
	glVertex3f(-40, 10, 70);
	glVertex3f(-40, -40, 70);
	glVertex3f(-50, -40, 70);
	glEnd();
	glBegin(GL_POLYGON);//KIRI
	glColor3f(0.5, 0.2, 0);
	glVertex3f(-50, 10, 70);
	glVertex3f(-50, -40, 70);
	glVertex3f(-50, -40, 80);
	glVertex3f(-50, 10, 80);
	glEnd();
	glBegin(GL_POLYGON);//KANAN
	glColor3f(0.5, 0.2, 0);
	glVertex3f(-40, 10, 70);
	glVertex3f(-40, -40, 70);
	glVertex3f(-40, -40, 80);
	glVertex3f(-40, 10, 80);
	glEnd();

	//KAKI MEJA 2
	glBegin(GL_POLYGON);//ALAS BAWAH
	glColor3f(0.5, 0.2, 0);
	glVertex3f(50, -40, 70);
	glVertex3f(40, -40, 70);
	glVertex3f(40, -40, 80);
	glVertex3f(50, -40, 80);
	glEnd();
	glBegin(GL_POLYGON);//DEPAN
	glColor3f(0.5, 0.2, 0);
	glVertex3f(50, 10, 80);
	glVertex3f(40, 10, 80);
	glVertex3f(40, -40, 80);
	glVertex3f(50, -40, 80);
	glEnd();
	glBegin(GL_POLYGON);//BELAKANG
	glColor3f(0.5, 0.2, 0);
	glVertex3f(50, 10, 70);
	glVertex3f(40, 10, 70);
	glVertex3f(40, -40, 70);
	glVertex3f(50, -40, 70);
	glEnd();
	glBegin(GL_POLYGON);//KIRI
	glColor3f(0.5, 0.2, 0);
	glVertex3f(50, 10, 70);
	glVertex3f(50, -40, 70);
	glVertex3f(50, -40, 80);
	glVertex3f(50, 10, 80);
	glEnd();
	glBegin(GL_POLYGON);//KANAN
	glColor3f(0.5, 0.2, 0);
	glVertex3f(40, 10, 70);
	glVertex3f(40, -40, 70);
	glVertex3f(40, -40, 80);
	glVertex3f(40, 10, 80);
	glEnd();

	//KAKI MEJA 3
	glBegin(GL_POLYGON);//ALAS BAWAH
	glColor3f(0.5, 0.2, 0);
	glVertex3f(-50, -40, 0);
	glVertex3f(-40, -40, 0);
	glVertex3f(-40, -40, -10);
	glVertex3f(-50, -40, -10);
	glEnd();
	glBegin(GL_POLYGON);//DEPAN
	glColor3f(0.5, 0.2, 0);
	glVertex3f(-50, 10, 0);
	glVertex3f(-40, 10, 0);
	glVertex3f(-40, -40, 0);
	glVertex3f(-50, -40, 0);
	glEnd();
	glBegin(GL_POLYGON);//BELAKANG
	glColor3f(0.5, 0.2, 0);
	glVertex3f(-50, 10, -10);
	glVertex3f(-40, 10, -10);
	glVertex3f(-40, -40, -10);
	glVertex3f(-50, -40, -10);
	glEnd();
	glBegin(GL_POLYGON);//KIRI
	glColor3f(0.5, 0.2, 0);
	glVertex3f(-50, 10, 0);
	glVertex3f(-50, -40, 0);
	glVertex3f(-50, -40, -10);
	glVertex3f(-50, 10, -10);
	glEnd();
	glBegin(GL_POLYGON);//KANAN
	glColor3f(0.5, 0.2, 0);
	glVertex3f(-40, 10, 0);
	glVertex3f(-40, -40, 0);
	glVertex3f(-40, -40, -10);
	glVertex3f(-40, 10, -10);
	glEnd();

	//KAKI MEJA 4
	glBegin(GL_POLYGON);//ALAS BAWAH
	glColor3f(0.5, 0.2, 0);
	glVertex3f(50, -40, 0);
	glVertex3f(40, -40, 0);
	glVertex3f(40, -40, -10);
	glVertex3f(50, -40, -10);
	glEnd();
	glBegin(GL_POLYGON);//DEPAN
	glColor3f(0.5, 0.2, 0);
	glVertex3f(50, 10, 0);
	glVertex3f(40, 10, 0);
	glVertex3f(40, -40, 0);
	glVertex3f(50, -40, 0);
	glEnd();
	glBegin(GL_POLYGON);//BELAKANG
	glColor3f(0.5, 0.2, 0);
	glVertex3f(50, 10, -10);
	glVertex3f(40, 10, -10);
	glVertex3f(40, -40, -10);
	glVertex3f(50, -40, -10);
	glEnd();
	glBegin(GL_POLYGON);//KIRI
	glColor3f(0.5, 0.2, 0);
	glVertex3f(50, 10, 0);
	glVertex3f(50, -40, 0);
	glVertex3f(50, -40, -10);
	glVertex3f(50, 10, -10);
	glEnd();
	glBegin(GL_POLYGON);//KANAN
	glColor3f(0.5, 0.2, 0);
	glVertex3f(40, 10, 0);
	glVertex3f(40, -40, 0);
	glVertex3f(40, -40, -10);
	glVertex3f(40, 10, -10);
	glEnd();

}

void Kursi() {

	//ALAS KURSI
	glBegin(GL_POLYGON);//BAWAh
	glColor3f(1, 1, 1);
	glVertex3f(-20, -15, -20);
	glVertex3f(20, -15, -20);
	glVertex3f(20, -15, -50);
	glVertex3f(-20, -15, -50);
	glEnd();
	glBegin(GL_POLYGON);//ATAS
	glColor3f(0.7f, 0.1f, 0.1f);
	glVertex3f(-20, -10, -20);
	glVertex3f(20, -10, -20);
	glVertex3f(20, -10, -50);
	glVertex3f(-20, -10, -50);
	glEnd();
	glBegin(GL_POLYGON);//SAMPING KANAN
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(20, -10, -20);
	glVertex3f(20, -15, -20);
	glVertex3f(20, -15, -50);
	glVertex3f(20, -10, -50);
	glEnd();
	glBegin(GL_POLYGON);//SAMPING KIRI
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(-20, -10, -20);
	glVertex3f(-20, -15, -20);
	glVertex3f(-20, -15, -50);
	glVertex3f(-20, -10, -50);
	glEnd();
	glBegin(GL_POLYGON);//DEPAN
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(-20, -10, -20);
	glVertex3f(-20, -15, -20);
	glVertex3f(20, -15, -20);
	glVertex3f(20, -10, -20);
	glEnd();
	glBegin(GL_POLYGON);//BELAKANG
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(-20, -10, -50);
	glVertex3f(-20, -15, -50);
	glVertex3f(20, -15, -50);
	glVertex3f(20, -10, -50);
	glEnd();

	//KAKI KURSI 1
	glBegin(GL_POLYGON);//ALAS BAWAH
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(-20, -40, -30);
	glVertex3f(-10, -40, -30);
	glVertex3f(-10, -40, -20);
	glVertex3f(-20, -40, -20);
	glEnd();
	glBegin(GL_POLYGON);//DEPAN
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(-20, -10, -20);
	glVertex3f(-10, -10, -20);
	glVertex3f(-10, -40, -20);
	glVertex3f(-20, -40, -20);
	glEnd();
	glBegin(GL_POLYGON);//BELAKANG
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(-20, -10, -30);
	glVertex3f(-10, -10, -30);
	glVertex3f(-10, -40, -30);
	glVertex3f(-20, -40, -30);
	glEnd();
	glBegin(GL_POLYGON);//KIRI
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(-20, -10, -30);
	glVertex3f(-20, -40, -30);
	glVertex3f(-20, -40, -20);
	glVertex3f(-20, -10, -20);
	glEnd();
	glBegin(GL_POLYGON);//KANAN
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(-10, -10, -30);
	glVertex3f(-10, -40, -30);
	glVertex3f(-10, -40, -20);
	glVertex3f(-10, -10, -20);
	glEnd();

	//KAKI KURSI 2
	glBegin(GL_POLYGON);//ALAS BAWAH
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(-10, -40, -50);
	glVertex3f(-20, -40, -50);
	glVertex3f(-20, -40, -40);
	glVertex3f(-10, -40, -40);
	glEnd();
	glBegin(GL_POLYGON);//ALAS ATAS
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(-10, 30, -50);
	glVertex3f(-20, 30, -50);
	glVertex3f(-20, 30, -40);
	glVertex3f(-10, 30, -40);
	glEnd();
	glBegin(GL_POLYGON);//DEPAN
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(-10, 30, -40);
	glVertex3f(-20, 30, -40);
	glVertex3f(-20, -40, -40);
	glVertex3f(-10, -40, -40);
	glEnd();
	glBegin(GL_POLYGON);//BELAKANG
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(-10, 30, -50);
	glVertex3f(-20, 30, -50);
	glVertex3f(-20, -40, -50);
	glVertex3f(-10, -40, -50);
	glEnd();
	glBegin(GL_POLYGON);//KIRI
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(-10, 30, -50);
	glVertex3f(-10, -40, -50);
	glVertex3f(-10, -40, -40);
	glVertex3f(-10, 30, -40);
	glEnd();
	glBegin(GL_POLYGON);//KANAN
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(-20, 30, -50);
	glVertex3f(-20, -40, -50);
	glVertex3f(-20, -40, -40);
	glVertex3f(-20, 30, -40);
	glEnd();

	//KAKI KURSI 3
	glBegin(GL_POLYGON);//ALAS BAWAH
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(20, -40, -30);
	glVertex3f(10, -40, -30);
	glVertex3f(10, -40, -20);
	glVertex3f(20, -40, -20);
	glEnd();
	glBegin(GL_POLYGON);//DEPAN
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(20, -10, -20);
	glVertex3f(10, -10, -20);
	glVertex3f(10, -40, -20);
	glVertex3f(20, -40, -20);
	glEnd();
	glBegin(GL_POLYGON);//BELAKANG
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(20, -10, -30);
	glVertex3f(10, -10, -30);
	glVertex3f(10, -40, -30);
	glVertex3f(20, -40, -30);
	glEnd();
	glBegin(GL_POLYGON);//KIRI
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(20, -10, -30);
	glVertex3f(20, -40, -30);
	glVertex3f(20, -40, -20);
	glVertex3f(20, -10, -20);
	glEnd();
	glBegin(GL_POLYGON);//KANAN
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(10, -10, -30);
	glVertex3f(10, -40, -30);
	glVertex3f(10, -40, -20);
	glVertex3f(10, -10, -20);
	glEnd();

	//KAKI KURSI 2
	glBegin(GL_POLYGON);//ALAS BAWAH
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(10, -40, -50);
	glVertex3f(20, -40, -50);
	glVertex3f(20, -40, -40);
	glVertex3f(10, -40, -40);
	glEnd();
	glBegin(GL_POLYGON);//ALAS ATAS
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(10, 30, -50);
	glVertex3f(20, 30, -50);
	glVertex3f(20, 30, -40);
	glVertex3f(10, 30, -40);
	glEnd();
	glBegin(GL_POLYGON);//DEPAN
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(10, 30, -40);
	glVertex3f(20, 30, -40);
	glVertex3f(20, -40, -40);
	glVertex3f(10, -40, -40);
	glEnd();
	glBegin(GL_POLYGON);//BELAKANG
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(10, 30, -50);
	glVertex3f(20, 30, -50);
	glVertex3f(20, -40, -50);
	glVertex3f(10, -40, -50);
	glEnd();
	glBegin(GL_POLYGON);//KIRI
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(10, 30, -50);
	glVertex3f(10, -40, -50);
	glVertex3f(10, -40, -40);
	glVertex3f(10, 30, -40);
	glEnd();
	glBegin(GL_POLYGON);//KANAN
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(20, 30, -50);
	glVertex3f(20, -40, -50);
	glVertex3f(20, -40, -40);
	glVertex3f(20, 30, -40);
	glEnd();

	//SENDERAN KURSI
	glBegin(GL_POLYGON);//DEPAN
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(-10, 30, -40);
	glVertex3f(-10, 10, -40);
	glVertex3f(10, 10, -40);
	glVertex3f(10, 30, -40);
	glEnd();
	glBegin(GL_POLYGON);//BELAKANG
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(-10, 30, -45);
	glVertex3f(-10, 10, -45);
	glVertex3f(10, 10, -45);
	glVertex3f(10, 30, -45);
	glEnd();
	glBegin(GL_POLYGON);//ATAS
	glColor3f(0.4f, 0.26f, 0.13f); // Dark Brown
	glVertex3f(-10, 30, -40);
	glVertex3f(-10, 30, -45);
	glVertex3f(10, 30, -45);
	glVertex3f(10, 30, -40);
	glEnd();
	glBegin(GL_POLYGON);//BAWAH
	glColor3f(1, 1, 1);
	glVertex3f(-10, 10, -40);
	glVertex3f(-10, 10, -45);
	glVertex3f(10, 10, -45);
	glVertex3f(10, 10, -40);
	glEnd();
}
void Teapot() {
	glLightfv(GL_LIGHT0, GL_POSITION, posisiCahayaTeko);
	glLightfv(GL_LIGHT0, GL_SPECULAR, intensitasCahaya);
	glTranslatef(translateX, 0, translateY);
	glTranslatef(0, 23, 30);
	glScalef(scaleObjek, scaleObjek, scaleObjek);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidTeapot(10);

}

void Pisin() {
	//	1
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(-40, 15, 30);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(1.5, 5.0, 50, 50);
	glPopMatrix();
	//	2
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(0, 15, 70);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(1.5, 5.0, 50, 50);
	glPopMatrix();
	//	3
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(0, 15, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(1.5, 5.0, 50, 50);
	glPopMatrix();
	//	4
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(40, 15, 30);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(1.5, 5.0, 50, 50);
	glPopMatrix();
}


void pola(void) {

	//Kursi 1

	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, posisiCahaya);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, intensitasCahaya);
	glTranslatef(0.0, 0.0, 0.0);
	Kursi();
	glRotatef(0, 0, 0, 0);
	glPopMatrix();

	//Kursi 2
	glPushMatrix();
	glTranslatef(-35.0, 0.0, 35.0);
	glRotatef(90, 0, 1, 0);
	Kursi();
	glPopMatrix();

	//Kursi 3
	glPushMatrix();
	glTranslatef(35.0, 0.0, 35.0);
	glRotatef(270, 0, 1, 0);
	Kursi();
	glPopMatrix();

	//Kursi 4
	glPushMatrix();
	glTranslatef(0.0, 0.0, 70.0);
	glRotatef(180, 0, 10, 0);
	Kursi();
	glPopMatrix();

	// Cangkir 1
	glPushMatrix();
	glTranslatef(-40.0, 25, 30);
	glRotatef(90, 90, 0, 0);
	Cangkir(5.0, 10.0, 20);
	glPopMatrix();

	//Cangkir 2
	glPushMatrix();
	glTranslatef(40.0, 25, 30);
	glRotatef(90, 90, 0, 0);
	Cangkir(5.0, 10.0, 20);
	glPopMatrix();

	//Cangkir 3
	glPushMatrix();
	glTranslatef(0.0, 25, 0);
	glRotatef(90, 90, 0, 0);
	Cangkir(5.0, 10.0, 20);
	glPopMatrix();

	//Cangkir 4
	glPushMatrix();
	glTranslatef(0.0, 25, 70);
	glRotatef(90, 90, 0, 0);
	Cangkir(5.0, 10.0, 20);
	glPopMatrix();

	//Teko
	glPushMatrix();
	Teapot();
	glPopMatrix();

	//Pisin
	glPushMatrix();
	Pisin();
	glPopMatrix();

}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
	case 'o': // Translasi ke Atas
		translateY -= 5.0f;
		break;
	case 'l': // Translasi ke Bawah
		translateY += 5.0f;
		break;
	case ';': // Translasi ke kanan
		translateX += 5.0f;
		break;
	case 'k': // Translasi ke kiri
		translateX -= 5.0f;
		break;
	case 's': // Translasi ke bawah
		xrot -= 5.0f;
		break;
	case 'w': // Translasi ke atas
		xrot += 5.0f;
		break;
	case 'a': // Translasi ke kiri
		yrot += 5.0f;
		break;
	case 'd': // Translasi ke kanan
		yrot -= 5.0f;
		break;
	case 'x': // Scale kecil
		scaleCam /= 1.1f;
		break;
	case 'z': // Scale besar
		scaleCam *= 1.1f;
		break;
	case 'h': // Scale Objek Teko kecil
		scaleObjek /= 1.1f;
		break;
	case 'j': // Scale Objek Teko besar
		scaleObjek *= 1.1f;
		break;
	case 'q': // Rotasi CCW
		rotateAngle -= 10.0f;
		break;
	case 'e': // Rotasi CW
		rotateAngle += 10.0f;
		break;

	case '2': // Enable 2D Cartesian lines
		cartesius = true;
		cout << "2D Cartesian lines enabled." << endl;
		break;
	case '3': // Disable 2D Cartesian lines
		cartesius = false;
		cout << "2D Cartesian lines disabled." << endl;
		break;
	case '4': // Enable 3D Cartesian lines
		cartesius2 = true;
		cout << "3D Cartesian lines enabled." << endl;
		break;
	case '5': // Disable 3D Cartesian lines
		cartesius2 = false;
		cout << "3D Cartesian lines disabled." << endl;
		break;

	}


	glutPostRedisplay();
}


void tampilan(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//	glTranslatef(xrot, yrot, -5.0f); // Menambahkan translasi X dan Y
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glScalef(scaleCam, scaleCam, scaleCam);
	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
	glRotatef(xrot, 1, 0, 0);
	glRotatef(yrot, 0, 1, 0);
	glPushMatrix();
	Ruangan();
	//	Dekor();
	Lantai();
	Meja();
	glPopMatrix();
	pola();

	if (cartesius) {
		drawCartesianLines();
	}

	if (cartesius2) {
		DrawAnchoredGraph();
	}

	glutSwapBuffers();

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(240, 80);
	glutInitWindowSize(750, 600);
	Note();
	glutCreateWindow("TB Kelompok 5");
	myinit();
	glutDisplayFunc(tampilan);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(ukur);
	glutMainLoop();
}
