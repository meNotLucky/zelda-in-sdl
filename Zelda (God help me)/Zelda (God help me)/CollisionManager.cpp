#include "CollisionManager.h"
#include "Collider.h"

bool CollisionManager::check_collision(RectangleCollider* a, RectangleCollider* b)
{
	SDL_Rect left = a->get_bounds();
	SDL_Rect right = b->get_bounds();

	if (left.x >= right.x + right.w)
		return false;
	if (left.x + left.w <= right.x)
		return false;
	if (left.y >= right.y + right.h)
		return false;
	if (left.y + left.h <= right.y)
		return false;

	return true;
}

bool CollisionManager::check_collision(Collider* a, Collider* b)
{
	if (a->get_type() == COLLIDERTYPE::RECTANGLE && b->get_type() == COLLIDERTYPE::RECTANGLE) {

		return check_collision(dynamic_cast<RectangleCollider*>(a), dynamic_cast<RectangleCollider*>(b));
	}

	return true;
}
