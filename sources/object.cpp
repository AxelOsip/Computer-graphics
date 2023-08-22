#include "object.h"


void Object::readFile(ifstream &file){
	char ch;
	float num;
	int status = 0;			// data status: 0 - break, 
							//				1 - points, 
							//				2 - normals,
							//				3 - connections
							//				4 - normal id
	int id = 0;

	while(file.get(ch)){
		if (ch == '#'){		// skip comments
			status = 0;
			while(file.get(ch)){
				if (ch == '\n')
					break;
			}
			continue;
		}

		if (ch == 'v'){		// "v 0 0 0"
			status++;
			continue;
		}
		if (ch == 'n')		// "vn 0 0 0"
			status++;
		if (ch == 'f')		// "f 0 0 0"
			status = 3;
		if (ch == 's')		// "g 0"
			status = 4;
		if (ch == '\n')
			status = 0;
		
		if (status == 1){		// points
			int i = points.size;
			for (int j = 0; j < 3; j++){
				file >> num;
				points[i][j] = num;
			}
			points[i][3] = 1;
		}

		if (status == 2){		// normals
			int i = normals.size;
			for (int j = 0; j < 3; j++){
				file >> num;
				normals[i][j] = num;
			}
			normals[i][3] = 0;
		}

		if (status == 3){		// connections
			int i = connections.size;
			for (int j = 0; j < 3; j++){
				file >> num;
				connections[i][j] = num-1;
			}
			normal_id[i] = id-1;
		}

		if (status == 4){
			file >> num;
			id = num;
		}
	}
}


void Object::setMatrix(int s, int dx, int dy, int dz){
	center = vec4(dx,dy,dz,1);
	matrix = mat4(	s,0,0,dx,
					0,s,0,dy,
					0,0,s,dz,
					0,0,0,1);
}

void Object::scale(float s){
	matrix = matrix * MAT4_shift(-center.x, -center.y, -center.z);
	matrix = matrix * mat4(	s,0,0,0,
							0,s,0,0,
							0,0,s,0,
							0,0,0,1);
	matrix = matrix * MAT4_shift(center.x, center.y, center.z);
}

void Object::shift(int dx, int dy, int dz){
	center = center * MAT4_shift(dx,dy,dz);
	matrix = matrix * MAT4_shift(dx,dy,dz);
}