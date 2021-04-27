#pragma once
#include "UniEngine.h"
using namespace UniEngine;
namespace Galaxy {
	/// <summary>
	/// The calculated precise position of the star.
	/// </summary>
	struct StarPosition : ComponentDataBase
	{
		glm::dvec3 m_value;
	};
	struct SelectionStatus : ComponentDataBase
	{
		int m_value;
	};
	/// <summary>
	/// The seed of the star, use this to calculate initial position.
	/// </summary>
	struct StarSeed : ComponentDataBase
	{
		float m_value;
	};
	/// <summary>
	/// This keep track of the position of the star in the list.
	/// </summary>
	struct StarIndex : ComponentDataBase
	{
		int m_value;
	};
	/// <summary>
	/// Original color of the star
	/// </summary>
	struct OriginalColor : ComponentDataBase
	{
		glm::vec4 m_value;
	};
	/// <summary>
	/// The deviation of its orbit
	/// </summary>
	struct StarOrbitOffset : ComponentDataBase
	{
		glm::dvec3 m_value;
	};
	/// <summary>
	/// This will help calculate the orbit. Smaller = close to center, bigger = close to disk
	/// </summary>
	struct StarOrbitProportion : ComponentDataBase
	{
		double m_value;
	};
	/// <summary>
	/// This will help calculate the orbit. Smaller = close to center, bigger = close to disk
	/// </summary>
	struct SurfaceColor : ComponentDataBase
	{
		glm::vec4 m_value;
	};
	/// <summary>
	/// The actual display color after selection system.
	/// </summary>
	struct DisplayColor : ComponentDataBase
	{
		glm::vec4 m_value;
	};

	struct StarOrbit : ComponentDataBase
	{
		double m_a;
		double m_b;
		double m_tiltY;
		double m_tiltX;
		double m_tiltZ;
		double m_speedMultiplier;
		glm::dvec3 m_center;
		[[nodiscard]] glm::dvec3 GetPoint(const glm::dvec3& orbitOffset, const double& time, const bool& isStar = true) const
		{
			const double angle = isStar ? time / glm::sqrt(m_a + m_b) * m_speedMultiplier : time;

			glm::dvec3 point;
			point.x = glm::sin(glm::radians(angle)) * m_a + orbitOffset.x;
			point.y = orbitOffset.y;
			point.z = glm::cos(glm::radians(angle)) * m_b + orbitOffset.z;
			
			point = Rotate(glm::angleAxis(glm::radians(m_tiltX), glm::dvec3(1, 0, 0)), point);
			point = Rotate(glm::angleAxis(glm::radians(m_tiltY), glm::dvec3(0, 1, 0)), point);
			point = Rotate(glm::angleAxis(glm::radians(m_tiltZ), glm::dvec3(0, 0, 1)), point);

			point.x += m_center.x;
			point.y += m_center.y;
			point.z += m_center.z;
			return point;
		}

		static glm::dvec3 Rotate(const glm::qua<double>& rotation, const glm::dvec3& point)
		{
			const double x = rotation.x * 2.0;
			const double y = rotation.y * 2.0;
			const double z = rotation.z * 2.0;
			const double xx = rotation.x * x;
			const double yy = rotation.y * y;
			const double zz = rotation.z * z;
			const double xy = rotation.x * y;
			const double xz = rotation.x * z;
			const double yz = rotation.y * z;
			const double wx = rotation.w * x;
			const double wy = rotation.w * y;
			const double wz = rotation.w * z;
			glm::dvec3 res;
			res.x = (1.0 - (yy + zz)) * point.x + (xy - wz) * point.y + (xz + wy) * point.z;
			res.y = (1.0 - (xx + zz)) * point.y + (yz - wx) * point.z + (xy + wz) * point.x;
			res.z = (1.0 - (xx + yy)) * point.z + (xz - wy) * point.x + (yz + wx) * point.y;
			return res;
		}
	};
	/// <summary>
	/// The star cluster it actually belongs to.
	/// </summary>
	struct StarClusterIndex : ComponentDataBase
	{
		int m_value = 0;
	};

	class StarClusterPattern : public PrivateComponentBase
	{
		double m_diskA = 0;
		double m_diskB = 0;
		double m_coreA = 0;
		double m_coreB = 0;
		double m_centerA = 0;
		double m_centerB = 0;
		double m_coreAb = 0;
	public:		
		void OnGui() override;
		double m_ySpread = 0.05;
		double m_xzSpread = 0.015;
		
		double m_diskAb = 3000;
		double m_diskEccentricity = 0.5;
		
		double m_coreProportion = 0.4;
		double m_coreEccentricity = 0.5;
		
		double m_centerAb = 10;
		double m_centerEccentricity = 0.5;
		

		double m_diskSpeed = 1;
		double m_coreSpeed = 5;
		double m_centerSpeed = 10;

		double m_diskTiltX = 0;
		double m_diskTiltZ = 0;
		double m_coreTiltX = 0;
		double m_coreTiltZ = 0;
		double m_centerTiltX = 0;
		double m_centerTiltZ = 0;

		glm::vec4 m_diskColor = glm::vec4(0, 0, 1, 1);
		glm::vec4 m_coreColor = glm::vec4(1, 1, 0, 1);
		glm::vec4 m_centerColor = glm::vec4(1, 1, 1, 1);

		double m_rotation = 360;
		glm::dvec3 m_centerPosition = glm::dvec3(0);

		void Apply();
		
		void SetAb()
		{
			m_diskA = m_diskAb * m_diskEccentricity;
			m_diskB = m_diskAb * (1 - m_diskEccentricity);
			m_centerA = m_centerAb * m_centerEccentricity;
			m_centerB = m_centerAb * (1 - m_centerEccentricity);
			m_coreAb = m_centerAb / 2 + m_centerAb / 2 +
				(m_diskA + m_diskB - m_centerAb / 2 - m_centerAb / 2)
				* m_coreProportion;
			m_coreA = m_coreAb * m_coreEccentricity;
			m_coreB = m_coreAb * (1 - m_coreEccentricity);
		}

		/// <summary>
		/// Set the ellipse by the proportion.
		/// </summary>
		/// <param name="starOrbitProportion">
		/// The position of the ellipse in the density waves, range is from 0 to 1
		/// </param>
		/// <param name="orbit">
		/// The ellipse will be reset by the proportion and the density wave properties.
		/// </param>
		[[nodiscard]] StarOrbit GetOrbit(const double& starOrbitProportion) const
		{
			StarOrbit orbit;
			if (starOrbitProportion > m_coreProportion)
			{
				//If the wave is outside the disk;
				const double actualProportion = (starOrbitProportion - m_coreProportion) / (1 - m_coreProportion);
				orbit.m_a = m_coreA + (m_diskA - m_coreA) * actualProportion;
				orbit.m_b = m_coreB + (m_diskB - m_coreB) * actualProportion;
				orbit.m_tiltX = m_coreTiltX - (m_coreTiltX - m_diskTiltX) * actualProportion;
				orbit.m_tiltZ = m_coreTiltZ - (m_coreTiltZ - m_diskTiltZ) * actualProportion;
				orbit.m_speedMultiplier = m_coreSpeed + (m_diskSpeed - m_coreSpeed) * actualProportion;
			}
			else
			{
				const double actualProportion = starOrbitProportion / m_coreProportion;
				orbit.m_a = m_centerA + (m_coreA - m_centerA) * actualProportion;
				orbit.m_b = m_centerB + (m_coreB - m_centerB) * actualProportion;
				orbit.m_tiltX = m_centerTiltX - (m_centerTiltX - m_coreTiltX) * actualProportion;
				orbit.m_tiltZ = m_centerTiltZ - (m_centerTiltZ - m_coreTiltZ) * actualProportion;
				orbit.m_speedMultiplier = m_centerSpeed + (m_coreSpeed - m_centerSpeed) * actualProportion;
			}
			orbit.m_tiltY = -m_rotation * starOrbitProportion;
			orbit.m_center = m_centerPosition * (1 - starOrbitProportion);
			return orbit;
		}

		[[nodiscard]] StarOrbitOffset GetOrbitOffset(const double& proportion) const
		{
			double offset = glm::sqrt(1 - proportion);
			StarOrbitOffset orbitOffset;
			glm::dvec3 d3;
			d3.y = glm::gaussRand(0.0, 1.0) * (m_diskA + m_diskB) * m_ySpread;
			d3.x = glm::gaussRand(0.0, 1.0) * (m_diskA + m_diskB) * m_xzSpread;
			d3.z = glm::gaussRand(0.0, 1.0) * (m_diskA + m_diskB) * m_xzSpread;
			orbitOffset.m_value = d3;
			return orbitOffset;
		}

		[[nodiscard]] glm::vec4 GetColor(const double& proportion) const
		{
			glm::vec4 color = glm::vec4();
			if (proportion > m_coreProportion)
			{
				//If the wave is outside the disk;
				const double actualProportion = (proportion - m_coreProportion) / (1 - m_coreProportion);
				color = m_coreColor * (1 - static_cast<float>(actualProportion)) + m_diskColor * static_cast<float>(actualProportion);
			}
			else
			{
				const double actualProportion = proportion / m_coreProportion;
				color = m_coreColor * static_cast<float>(actualProportion) + m_centerColor * (1 - static_cast<float>(actualProportion));
			}
			color = glm::normalize(color);
			return color;
		}
	};

	class StarClusterSystem :
		public SystemBase
	{
		EntityArchetype m_starClusterArchetype;
		Entity m_starClusterFront;
		Entity m_starClusterBack;

		Entity m_starClusterEntity;
		EntityQuery m_starQuery;
		EntityArchetype m_starArchetype;

		bool m_useFront = true;
		
		float m_applyPositionTimer = 0;
		float m_copyPositionTimer = 0;
		float m_calcPositionTimer = 0;
		float m_calcPositionResult = 0;
		float m_speed = 0.0f;
		float m_size = 0.1f;
		float m_galaxyTime = 0.0f;
		std::future<void> m_currentStatus;
		bool m_firstTime = true;
	public:
		void CalculateStarPositionAsync();
		void CalculateStarPositionSync();
		void ApplyPositionSync();
		void SetRenderer();
		void LateUpdate() override;
		void OnCreate() override;
		void Update() override;
		void FixedUpdate() override;
		void OnStartRunning() override;
	};
}

