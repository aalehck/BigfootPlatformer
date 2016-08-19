struct point{
	int x;
	int y;
}; 

enum collisionEnum{
	COLLISION_TOP,
	COLLISION_BOTTOM,
	COLLISION_LEFT,
	COLLISION_RIGHT,
	COLLISION_NONE,
};

struct collisionState{
	point adjustLocation;
	collisionEnum collisionX;
	collisionEnum collisionY;
};

struct hitBox{
	int x;
	int y;
	int w;
	int h;
	int vx;
	int vy;
	bool isJumping;
};
