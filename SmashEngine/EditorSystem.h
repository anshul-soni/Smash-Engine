#pragma once
#include "System.h"

namespace SmashEngine
{
	class EditorSystem :
		public System
	{
	public:
		static EditorSystem& GetInstance();
		void Init()override;
		void Update(float dt)override;
		SystemType GetType()const override;
		void Release()override;
		~EditorSystem(void);
	private:
		const SystemType type;
		EditorSystem(void);
	};
}
