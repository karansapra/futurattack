#include "collisions.h"

U16 DetectSphereAndSphere(Sphere & one, Sphere & two, CollisionData & data)
{
	if (data.contacts_lefts<=0)
		return 0;

	Vector3 p1 = one.body->position;
	Vector3 p2 = two.body->position;

	Vector3 midline = p1-p2;
	REAL size = midline.Length();

	if (size<=0 || size>=one.radius+two.radius)
		return 0;

	Vector3 normal = midline * ((REAL)1/size);

	Contact * contact = data.contacts;
	contact->contact_normal = normal;
}