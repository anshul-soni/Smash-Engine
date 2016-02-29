#pragma once
namespace SmashEngine
{
	class SphereCollider;
	class BoxCollider;
	class Body;

	class Collider
	{
	public:
		enum ColliderType
		{
			Sphere = 0,
			Box,
		};
		Collider(Body* body);
		virtual ~Collider();
		virtual ColliderType GetColliderType() const = 0;
		Body* GetBody() const;
		virtual bool TestPoint(const glm::vec3& point);
		virtual bool TestCollision(Collider* other);
		virtual bool TestSphere(SphereCollider* sphere) = 0;
		virtual bool TestBox(BoxCollider* box) = 0;
		virtual void DetectContacts(Collider* other);
		virtual void DetectSphere(SphereCollider* sphere) = 0;
		virtual void DetectBox(BoxCollider* box) = 0;
	protected:
		ColliderType colliderType;
		Body* body;
	};
	struct Segment
	{
		glm::vec3 p; // start point of segment
		glm::vec3 q; // end point of segment

		Segment(glm::vec3 p = glm::vec3(0), glm::vec3 q = glm::vec3(0))
			: p(p), q(q) {}
	};
	class BoxCollider:public Collider
	{
	public:
		BoxCollider(Body* b, const glm::vec3& scale);
		ColliderType GetColliderType()const override;
		void CalculateVertices();
		void CalculateEdges();
		bool TestPoint(const glm::vec3& point)override;
		bool TestSphere(SphereCollider* sphere)override;
		bool TestBox(BoxCollider* box)override;
		void DetectSphere(SphereCollider* sphere)override;
		void DetectBox(BoxCollider* box)override;
		bool TestLocalPoint(const glm::vec3& point);
		bool TestOverlap(BoxCollider* box, const glm::vec3& axis);
		float CalculateProjection(const glm::vec3& axis);
		void DetectPointFace(BoxCollider* boxB);
		~BoxCollider();
	private:
		// half-sizes of the box
		glm::vec3 extents;

		// vertices in world-space
		glm::vec3 vertices[8];

		// edges in world-space
		Segment edges[12];
	};
	class SphereCollider:public Collider
	{
	public:
		SphereCollider(Body* body,float scale);
		ColliderType GetColliderType()const override;
		float GetRadius() const;
		bool TestPoint(const glm::vec3& point)override;
		bool TestSphere(SphereCollider* sphere)override;
		bool TestBox(BoxCollider* box)override;
		void DetectSphere(SphereCollider* sphere)override;
		void DetectBox(BoxCollider* box)override;
		~SphereCollider();
	private:
		float radius;
	};
}
