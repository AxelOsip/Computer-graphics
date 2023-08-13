#include "object.h"


void Object::readFile(ifstream &file){
	char ch;
	float num;
	int status = 0;			// data status: 0 - break, 
							//				1 - points, 
							//				2 - normals,
							//				3 - connections

	while(file.get(ch)){
		// cout << ch;
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
		if (ch == '\n')
			status = 0;
		
		if (status == 1){		// points
			cout << "read points:\n";
			int i = points.size;
			for (int j = 0; j < 3; j++){
				file >> num;
				points[i][j] = num;
			}
			points[i][3] = 1;
		}

		if (status == 2){		// polygon normals
			cout << "read normals:\n";
			int i = normals.size;
			for (int j = 0; j < 3; j++){
				file >> num;
				normals[i][j] = num;
			}
			normals[i][3] = 0;
		}

		if (status == 3){		// connections
			cout << "read connections:\n";
			int i = connections.size;
			for (int j = 0; j < 3; j++){
				file >> num;
				connections[i][j] = num;
			}
		}
	}
}
