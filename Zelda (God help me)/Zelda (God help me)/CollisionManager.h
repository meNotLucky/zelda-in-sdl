#pragma once

class Collider;
class RectangleCollider;

class CollisionManager {
	bool check_collision(RectangleCollider *a, RectangleCollider *b);
public:
	bool check_collision(Collider *a, Collider *b);
};