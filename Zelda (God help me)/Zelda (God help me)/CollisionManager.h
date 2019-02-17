/*

COLLISION MANAGER

The Collision Manager is used to check for different types collisions between different types of colldiers.

It was created to easely give each game object a specific collider that fits their shape and purpouse,
and to then check for collisions with objects with the same or other types of colliders.

Instead of having to write specific collision code for each object, the object is instead given a collider and then it is automatically checked.

*/

#pragma once

class Collider;
class RectangleCollider;

class CollisionManager {
	bool check_collision(RectangleCollider *a, RectangleCollider *b);
public:
	bool check_collision(Collider *a, Collider *b);
};