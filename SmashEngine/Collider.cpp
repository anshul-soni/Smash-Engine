#include "stdafx.h"
#include "Collider.h"
#include "Physics.h"
#include "Body.h"
#include "Manifold.h"
#include "SignalManager.h"
#include "CollisionSignal.h"
#include "DrawSignal.h"
#define EPSILON 0.001f // to compensate for floating point errors while comparing floats
#define EPSILON2 0.00009f

namespace SmashEngine
{
	Collider::Collider(Body* b)
		: body(b)
	{	}

	Collider::~Collider()
	{
	}

	Body* Collider::GetBody() const
	{
		return body;
	}
	bool Collider::TestPoint(const glm::vec3& p)
	{
		return false;
	}

	bool Collider::TestCollision(Collider* other)
	{
		auto type = other->GetColliderType();
		SphereCollider* sphere;
		BoxCollider* box;
		switch (type)
		{
		case Sphere:
			sphere = static_cast<SphereCollider*>(other);

			if (TestSphere(sphere))
			{
				return true;
			}
			return false;
		case Box:
			box = static_cast<BoxCollider*>(other);

			if (TestBox(box))
			{
				return true;
			}
			return false;
		default:
			return false;
		}
	}

	void Collider::DetectContacts(Collider* other)
	{
		ColliderType type = other->GetColliderType();

		switch (type)
		{
		case Sphere:
		{
			SphereCollider* sphere = static_cast<SphereCollider*>(other);
			DetectSphere(sphere);
			break;
		}
		case Box:
		{
			BoxCollider* box = static_cast<BoxCollider*>(other);
			DetectBox(box);
			break;
		}
		}
	}

	SphereCollider::SphereCollider(Body* b, const float r)
		: Collider(b)
	{
		colliderType = Sphere;
		radius = r;
	}

	Collider::ColliderType SphereCollider::GetColliderType() const
	{
		return Sphere;
	}

	float SphereCollider::GetRadius() const
	{
		return radius;
	}

	bool SphereCollider::TestPoint(const glm::vec3& point)
	{
		glm::vec3 p1 = point;
		glm::vec3 p2 = body->GetPosition();

		float dist2 = glm::distance2(p1, p2);
		float radius2 = radius * radius;

		if ((dist2 - radius2) < EPSILON)
			return true;

		return false;
	}

	bool SphereCollider::TestSphere(SphereCollider* sphere)
	{
		glm::vec3 p1 = body->GetPosition();
		glm::vec3 p2 = sphere->GetBody()->GetPosition();

		glm::vec3 ab = p2 - p1;
		float distSq = glm::length2(ab);

		float r1 = radius;
		float r2 = sphere->radius;

		if ((distSq)-((r1 + r2)*(r1 + r2)) < EPSILON)
			return true;

		return false;
	}

	bool SphereCollider::TestBox(BoxCollider* box)
	{
		if (box->TestSphere(this))
			return true;

		return false;
	}

	void SphereCollider::DetectSphere(SphereCollider* sphere)
	{
		glm::vec3 p1 = body->GetPosition();
		glm::vec3 p2 = sphere->GetBody()->GetPosition();

		glm::vec3 ab = p2 - p1;
		float dist = glm::length(ab);
		float penetration = (radius + sphere->radius) - (dist);
		glm::vec3 normal = ab / dist;
		glm::vec3 contact = p1 + radius*normal;
		Manifold* m = new Manifold(body, sphere->GetBody());
		m->SetContactData(contact, normal, penetration);
		SignalManager::GetInstance().Signal(DrawSignal(contact));
		SignalManager::GetInstance().Signal(CollisionSignal(m));
	}


	void SphereCollider::DetectBox(BoxCollider* box)
	{
		box->DetectSphere(this);
	}

	SphereCollider::~SphereCollider()
	{
	}

	BoxCollider::BoxCollider(Body* b, const glm::vec3& extents)
		: Collider(b)
	{
		colliderType = Box;
		this->extents = extents;
	}

	Collider::ColliderType BoxCollider::GetColliderType() const
	{
		return Box;
	}


	void BoxCollider::CalculateVertices()
	{
		float hw = extents.x;
		float hh = extents.y;
		float hd = extents.z;
		// back face
		vertices[0] = body->LocalToWorld(glm::vec3(-hw, hh, -hd));
		vertices[1] = body->LocalToWorld(glm::vec3(hw, hh, -hd));
		vertices[2] = body->LocalToWorld(glm::vec3(hw, -hh, -hd));
		vertices[3] = body->LocalToWorld(glm::vec3(-hw, -hh, -hd));
		//front face
		vertices[4] = body->LocalToWorld(glm::vec3(-hw, hh, hd));
		vertices[5] = body->LocalToWorld(glm::vec3(hw, hh, hd));
		vertices[6] = body->LocalToWorld(glm::vec3(hw, -hh, hd));
		vertices[7] = body->LocalToWorld(glm::vec3(-hw, -hh, hd));
	}

	void BoxCollider::CalculateEdges()
	{
		// vertices in world-space
		glm::vec3 v[8];

		for (int i = 0; i < 8; i++)
			v[i] = vertices[i];

		edges[0] = Segment(v[0], v[1]);
		edges[1] = Segment(v[1], v[2]);
		edges[2] = Segment(v[2], v[3]);
		edges[3] = Segment(v[3], v[0]);
		edges[4] = Segment(v[4], v[5]);
		edges[5] = Segment(v[5], v[6]);
		edges[6] = Segment(v[6], v[7]);
		edges[7] = Segment(v[7], v[4]);
		edges[8] = Segment(v[0], v[4]);
		edges[9] = Segment(v[1], v[5]);
		edges[10] = Segment(v[3], v[7]);
		edges[11] = Segment(v[2], v[6]);
	}

	bool BoxCollider::TestPoint(const glm::vec3& point)
	{
		glm::vec3 p = body->WorldToLocal(point);
		glm::vec3 min = -extents;
		glm::vec3 max = extents;

		// To Do: Test if WorldToLocal is working correctly
		if ((p.x - min.x > EPSILON) && (p.x - max.x < EPSILON) &&
			(p.y - min.y > EPSILON) && (p.y - max.y < EPSILON) &&
			(p.z - min.z > EPSILON) && (p.z - max.z < EPSILON))
			return true;

		return false;
	}

	bool BoxCollider::TestLocalPoint(const glm::vec3& p)
	{
		glm::vec3 min = -extents;
		glm::vec3 max = extents;

		if ((p.x - min.x > EPSILON) && (p.x - max.x < EPSILON) &&
			(p.y - min.y > EPSILON) && (p.y - max.y < EPSILON) &&
			(p.z - min.z > EPSILON) && (p.z - max.z < EPSILON))
			return true;

		return false;
	}

	float BoxCollider::CalculateProjection(const glm::vec3& axis)
	{
		glm::mat3 R = body->GetRotationMatrix();
		glm::vec3 boxX = R[0];
		glm::vec3 boxY = R[1];
		glm::vec3 boxZ = R[2];

		glm::vec3 absAxis = glm::abs(axis);
		glm::vec3 absX = glm::abs(boxX);
		glm::vec3 absY = glm::abs(boxY);
		glm::vec3 absZ = glm::abs(boxZ);

		float projX = extents.x*(glm::dot(absX, absAxis));
		float projY = extents.y*(glm::dot(absY, absAxis));
		float projZ = extents.z*(glm::dot(absZ, absAxis));

		return (projX + projY + projZ);
	}

	bool BoxCollider::TestOverlap(BoxCollider* box, const glm::vec3& axis)
	{
		float p1 = this->CalculateProjection(axis);
		float p2 = box->CalculateProjection(axis);

		glm::vec3 ab = box->body->GetPosition() - body->GetPosition();
		float pab = std::fabs(glm::dot(ab, axis));

		if ((pab - (p1 + p2)) < EPSILON)
			return true;

		return false;
	}

	bool BoxCollider::TestSphere(SphereCollider* sphere)
	{
		glm::vec3 wPoint = sphere->GetBody()->GetPosition();

		// sphere pos in body-space
		glm::vec3 p = body->WorldToLocal(wPoint);

		// clamp sphere b/w [extents + radius]
		glm::vec3 min = -(extents + sphere->GetRadius()*glm::vec3(1));
		glm::vec3 max = -min;

		if (((p.x - min.x) > EPSILON) && ((p.x - max.x) < EPSILON) &&
			((p.y - min.y) > EPSILON) && ((p.y - max.y) < EPSILON) &&
			((p.z - min.z) > EPSILON) && ((p.z - max.z) < EPSILON))
			return true;

		return false;
	}


	bool BoxCollider::TestBox(BoxCollider* box)
	{
		glm::vec3 axes[15];
		int ai = 0; // axis index

		glm::mat3 R1 = body->GetRotationMatrix();
		glm::mat3 R2 = box->body->GetRotationMatrix();

		// 6 principal axes
		for (int i = 0; i < 3; i++)
			axes[ai++] = R1[i];
		for (int i = 0; i < 3; i++)
			axes[ai++] = R2[i];

		// 9 cross-products of principal axes
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				axes[ai++] = glm::cross(axes[i], axes[j + 3]) + glm::vec3(EPSILON); // to avoid zero cross product for parallel edges 
			}
		}

		for (int i = 0; i < 15; i++)
		{
			if (!TestOverlap(box, axes[i]))
				return false;
		}

		return true;
	}

	void BoxCollider::DetectSphere(SphereCollider* sphere)
	{
		// sphere center in world-space
		glm::vec3 cW = sphere->GetBody()->GetPosition();

		// sphere center in box's body-space
		glm::vec3 c = body->WorldToLocal(cW);

		// box min, max points in body-space
		glm::vec3 min = -extents;
		glm::vec3 max = extents;

		// find the closest point along each direction
		// the closest point could be a vertex of the box
		// or a point on one of the edges of the box
		// or a point on one of the faces of the box
		glm::vec3 closest(0);

		closest.x = c.x;
		if ((c.x - min.x) < EPSILON)
			closest.x = min.x;
		if ((c.x - max.x) > EPSILON)
			closest.x = max.x;

		closest.y = c.y;
		if ((c.y - min.y) < EPSILON)
			closest.y = min.y;
		if ((c.y - max.y) > EPSILON)
			closest.y = max.y;

		closest.z = c.z;
		if ((c.z - min.z) < EPSILON)
			closest.z = min.z;
		if ((c.z - max.z) > EPSILON)
			closest.z = max.z;

		float dist = glm::distance(closest, c);
		if (dist == 0)
		{
			int x = 1;
		}
		if ((dist - sphere->GetRadius()) > EPSILON)
			return; // eliminate false positives from broad phase

		glm::vec3 contact = body->LocalToWorld(closest);
		glm::vec3 normal = (cW - contact) / dist;
		float penetration = sphere->GetRadius() - dist;

		if (normal != normal)
		{
			int x = 1;
		}
		Manifold* m = new Manifold(body, sphere->GetBody());
		m->SetContactData(contact, normal, penetration);
		SignalManager::GetInstance().Signal(DrawSignal(contact));
		SignalManager::GetInstance().Signal(CollisionSignal(m));
	}

	void BoxCollider::DetectPointFace(BoxCollider* boxB)
	{
		Body* A = this->body;
		Body* B = boxB->body;
		glm::mat3 RA = A->GetRotationMatrix();
		glm::mat3 RB = B->GetRotationMatrix();

		// check if a vertex of B is inside A
		// Point-Face contacts
		for (int i = 0; i < 8; i++)
		{
			// vertex of B in A's body-space
			glm::vec3 vertB_A = A->WorldToLocal(boxB->vertices[i]);

			if (this->TestLocalPoint(vertB_A))
			{
				// a vertex of B is inside A
				// find the minmium penetration
				float depth = std::abs(extents.x - std::abs(vertB_A.x));
				float minDepth = depth;
				glm::vec3 normal = RA[0];
				if (vertB_A.x < 0) normal *= -1;

				depth = std::abs(extents.y - std::abs(vertB_A.y));
				if (depth < minDepth)
				{
					minDepth = depth;
					normal = RA[1];

					if (vertB_A.y < 0) normal *= -1;
				}

				depth = std::abs(extents.z - std::abs(vertB_A.z));
				if (depth < minDepth)
				{
					minDepth = depth;
					normal = RA[2];

					if (vertB_A.z < 0) normal *= -1;
				}

				if (normal != normal)
				{
					int x = 1;
				}
				Manifold* m = new Manifold(A, B);
				m->SetContactData(boxB->vertices[i], normal, minDepth);
				SignalManager::GetInstance().Signal(DrawSignal(boxB->vertices[i]));
				SignalManager::GetInstance().Signal(CollisionSignal(m));
			}
		}
	}

	BoxCollider::~BoxCollider()
	{
	}

	// Point-Face Ref: Game Physics Engine - Ian Millington
	// Edge-Edge Ref: Real-time Collision Detection - Christer Ericson
	void BoxCollider::DetectBox(BoxCollider* boxB)
	{
		CalculateVertices();
		boxB->CalculateVertices();
		CalculateEdges();
		boxB->CalculateEdges();
		// Detect Point-Face Contacts
		// Detect points of boxB inside this box
		this->DetectPointFace(boxB);

		// Detect points of this box inside boxB
		boxB->DetectPointFace(this);

		// all combinations of edgeA vs edgeB
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				// parameters to solve segment-segment overlap
				glm::vec3 d1 = edges[i].q - edges[i].p;
				glm::vec3 d2 = boxB->edges[j].q - boxB->edges[j].p;
				glm::vec3 r = edges[i].p - boxB->edges[j].p;
				float a, b, c, d, e, f, s, t;
				a = glm::dot(d1, d1);
				e = glm::dot(d2, d2);
				f = glm::dot(d2, r);
				b = glm::dot(d1, d2);
				c = glm::dot(d1, r);

				d = a*e - b*b;
				d += EPSILON;

				s = glm::clamp((b*f - c*e) / d, 0.0f, 1.0f);

				t = (b*s + f) / e;

				if (t < 0.0f)
				{
					t = 0.0f;
					s = glm::clamp(-c / a, 0.0f, 1.0f);
				}
				else if (t > 1.0f)
				{
					t = 1.0f;
					s = glm::clamp((b - c) / a, 0.0f, 1.0f);
				}

				glm::vec3 cA = edges[i].p + s*d1;
				glm::vec3 cB = boxB->edges[j].p + t*d2;
				float depth2 = glm::distance2(cA, cB);
				glm::vec3 contact, normal;
				glm::vec3 ab = boxB->body->GetPosition() - body->GetPosition();

				if (s < 0.01f || t < 0.01f || s + 0.01f > 1.0f || t + 0.01f > 1.0f)
				{
					// To Do : point-edge, point-point
				}
				if (depth2 < 0.01f)
				{
					float dA_cB = glm::distance2(body->GetPosition(), cB);
					float dA_cA = glm::distance2(body->GetPosition(), cA);
					if (dA_cB - dA_cA < EPSILON)
					{
						float dB_cA = glm::distance2(boxB->body->GetPosition(), cA);
						float dB_cB = glm::distance2(boxB->body->GetPosition(), cB);
						if (dB_cA - dB_cB < EPSILON)
						{
							contact = (cA + cB)*0.5f;
							normal = glm::cross(d1, d2);
							if (glm::length2(normal) < 0.001f)
							{
								normal = cB - cA;
							}
							normal = glm::normalize(normal);
							// normal should point from A to B
							if (glm::dot(ab, normal) < 0)
								normal *= -1.0f;
							float penetration = glm::sqrt(depth2);
							Manifold* m = new Manifold(body, boxB->body);
 							m->SetContactData(contact, normal, penetration);
							SignalManager::GetInstance().Signal(DrawSignal(contact));
							SignalManager::GetInstance().Signal(CollisionSignal(m));
						}
					}
				}
			}
		}
	}
}