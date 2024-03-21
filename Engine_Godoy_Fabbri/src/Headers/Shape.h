#pragma once

#include "Entity2D.h"
#include "Exports.h"

namespace ToToEng
{
	class TOTO_API Shape :
		public Entity2D
	{
	public:
		Shape(Renderer* renderer);
		~Shape() override;

		void draw() override;
	};
}