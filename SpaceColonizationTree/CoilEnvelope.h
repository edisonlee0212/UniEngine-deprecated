#pragma once
#include "Envelope.h"
namespace SCTree {
	class CoilEnvelope :
		public Envelope
	{
	public:
		CoilEnvelope(glm::vec3 spaceOffset, glm::vec3 spaceSize);
		bool IsInEnvelope(glm::vec3 point);
	};
}