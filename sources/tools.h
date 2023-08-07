#define SUCCESS 	1
#define FAIL 		0

// Colors
#define CL_RED 		0x00ff0000
#define CL_GREEN 	0x0000ff00
#define CL_BLUE 	0x000000ff
#define CL_CYAN 	0x0000ffff
#define CL_MAGENTA	0x00ffff00
#define CL_YELLOW 	0x00ff00ff
#define CL_WHITE 	0x00ffffff
#define CL_BLACK 	0x00000000

// Affine matrix
#define MAT_mir_Ox 				imat3{1,0,0, 0,-1,0, 0,0,1};		// mirroring mftrix on the Ox axis (-)
#define MAT_mir_Oy 				imat3{-1,0,0, 0,1,0, 0,0,1};		// mirroring mftrix on the Oy axis (|)
#define MAT_mir_xy 				imat3{0,1,0, 1,0,0, 0,0,1};			// mirroring mftrix on the xy axis (/)
#define MAT_mir_mxy 			imat3{0,1,0, 1,0,0, 0,0,1};			// mirroring mftrix on the -xy axis (\)
#define MAT_shift(dx, dy)		imat3(1,0,dx, 0,1,dy, 0,0,1)		// transporting matrix to the (dx, dy) local cords
#define MAT_rot_clw(a)			imat3(cos(a),sin(a),1, cos(a),-sin(a),1, 0,0,1)	// rotating matrix clockwise
#define MAT_rot_ctclw(a) 		imat3(cos(a),-sin(a),1, cos(a),sin(a),1, 0,0,1)	// rotating matrix counterclockwise

