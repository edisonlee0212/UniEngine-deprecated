#pragma once
#include "UniEngine.h"
#include <immintrin.h>

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
	struct StarInfo : ComponentDataBase
	{
		bool m_initialized = false;
	};
	
	/// <summary>
	/// Original color of the star
	/// </summary>
	struct OriginalColor : ComponentDataBase
	{
		glm::vec3 m_value;
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
		glm::vec3 m_value;
		float m_intensity = 1.0f;
	};
	/// <summary>
	/// The actual display color after selection system.
	/// </summary>
	struct DisplayColor : ComponentDataBase
	{
		glm::vec3 m_value;
		float m_intensity = 1.0f;
	};

	struct StarOrbitA : ComponentDataBase
	{
		double m_value;
	};

	struct StarOrbitB : ComponentDataBase
	{
		double m_value;
	};
	struct StarOrbitSpeedMultiplier : ComponentDataBase
	{
		double m_value;
	};

	struct StarTiltX : ComponentDataBase
	{
		double m_value;
	};

	struct StarTiltY : ComponentDataBase
	{
		double m_value;
	};

	struct StarTiltZ : ComponentDataBase
	{
		double m_value;
	};

	struct OrbitCenter : ComponentDataBase
	{
		glm::dvec3 m_value;
	};
	
	struct StarOrbit : ComponentDataBase
	{
		double m_a;
		double m_b;
		double m_speedMultiplier;
		
		double m_tiltX;
		double m_tiltY;
		double m_tiltZ;
		
		glm::dvec3 m_center;
		[[nodiscard]] glm::dvec3 GetPoint
		(const glm::dvec3& orbitOffset, const double& time, const bool& isStar = true) const
		{
			const double angle = isStar ? time / glm::sqrt(m_a + m_b) * m_speedMultiplier : time;

			glm::dvec3 point { glm::sin(glm::radians(angle)) * m_a , 0, glm::cos(glm::radians(angle)) * m_b };

			point = Rotate(glm::angleAxis(glm::radians(m_tiltX), glm::dvec3(1, 0, 0)), point);
			point = Rotate(glm::angleAxis(glm::radians(m_tiltY), glm::dvec3(0, 1, 0)), point);
			point = Rotate(glm::angleAxis(glm::radians(m_tiltZ), glm::dvec3(0, 0, 1)), point);

			point += m_center;
			point += orbitOffset;
			return point;
		}
		
		static glm::dvec3 RotateSIMD(const glm::qua<double>& rotation, const glm::dvec3& point)
		{
			const double dtwo[4] = { 2, 2, 2, 0 };
			const double dxyz[4] = { rotation.x,rotation.y,rotation.z,0 };
			const double dxxy[4] = { rotation.x,rotation.x,rotation.y,0 };
			const double dyzz[4] = { rotation.y,rotation.z,rotation.z,0 };
			const double dwww[4] = { rotation.w,rotation.w,rotation.w,0 };
			__m256d two = _mm256_load_pd(dtwo);
			__m256d xyz = _mm256_load_pd(dxyz);
			__m256d xxy = _mm256_load_pd(dxxy);
			__m256d yzz = _mm256_load_pd(dyzz);
			__m256d www = _mm256_load_pd(dwww);
			__m256d two_xyz = _mm256_mul_pd(xyz, two);
			__m256d two_yzz = _mm256_mul_pd(yzz, two);
			__m256d xxyyzz = _mm256_mul_pd(xyz, two_xyz);
			__m256d xyxzyz = _mm256_mul_pd(xxy, two_yzz);
			__m256d wxwywz = _mm256_mul_pd(www, two_xyz);
			//direcly calcuate needed vectors?
			double dxxyyzz[4], dxyxzyz[4], dwxwywz[4];
			_mm256_storeu_pd(dxxyyzz, xxyyzz);
			_mm256_storeu_pd(dxyxzyz, xyxzyz);
			_mm256_storeu_pd(dwxwywz, wxwywz);
			const double dyyxxxx[4] = { dxxyyzz[1],dxxyyzz[0],dxxyyzz[0],0 };
			const double dzzzzyy[4] = { dxxyyzz[2],dxxyyzz[2],dxxyyzz[1],0 };
			const double dxyyzxz[4] = { dxyxzyz[0],dxyxzyz[2],dxyxzyz[1],0 };
			const double dwzwxwy[4] = { dwxwywz[2],dwxwywz[0],dwxwywz[1],0 };
			const double dxzxyyz[4] = { dxyxzyz[1],dxyxzyz[0],dxyxzyz[2],0 };
			const double dwywzwx[4] = { dwxwywz[1],dwxwywz[2],dwxwywz[0],0 };
			const double done[4] = { 1,1,1,0 };
			const double dpxpypz[4] = { point.x,point.y,point.z,0 };
			const double dpypzpx[4] = { point.y,point.z,point.x,0 };
			const double dpzpxpy[4] = { point.z,point.x,point.y,0 };
			__m256d yyxxxx = _mm256_load_pd(dyyxxxx);
			__m256d zzzzyy = _mm256_load_pd(dzzzzyy);
			__m256d xyyzxz = _mm256_load_pd(dxyyzxz);
			__m256d wzwxwy = _mm256_load_pd(dwzwxwy);
			__m256d xzxyyz = _mm256_load_pd(dxzxyyz);
			__m256d wywzwx = _mm256_load_pd(dwywzwx);
			__m256d one = _mm256_load_pd(done);
			__m256d pxpypz = _mm256_load_pd(dpxpypz);
			__m256d pypzpx = _mm256_load_pd(dpypzpx);
			__m256d pzpxpy = _mm256_load_pd(dpzpxpy);
			__m256d c1 = _mm256_add_pd(yyxxxx, zzzzyy);
			c1 = _mm256_sub_pd(one, c1);
			c1 = _mm256_mul_pd(c1, pxpypz);
			__m256d c2 = _mm256_sub_pd(xyyzxz, wzwxwy);
			c2 = _mm256_mul_pd(c2, pypzpx);
			__m256d c3 = _mm256_add_pd(xzxyyz, wywzwx);
			c3 = _mm256_mul_pd(c2, pzpxpy);
			__m256d res = _mm256_add_pd(c1, c2);
			res = _mm256_add_pd(res, c3);
			double dres[4];
			_mm256_storeu_pd(dres, res);
			
			glm::dvec3 resvec;
			resvec.x = dres[0];
			resvec.y = dres[1];
			resvec.z = dres[2];
			
			return resvec;
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

	class StarClusterPattern
	{
		double m_diskA = 0;
		double m_diskB = 0;
		double m_coreA = 0;
		double m_coreB = 0;
		double m_centerA = 0;
		double m_centerB = 0;
		double m_coreDiameter = 0;
	public:
		std::string m_name = "Cluster Pattern";
		StarClusterIndex m_starClusterIndex;
		void OnGui();
		double m_ySpread = 0.05;
		double m_xzSpread = 0.015;
		
		double m_diskDiameter = 3000;
		double m_diskEccentricity = 0.5;
		
		double m_coreProportion = 0.4;
		double m_coreEccentricity = 0.7;
		
		double m_centerDiameter = 10;
		double m_centerEccentricity = 0.3;
		

		double m_diskSpeed = 1;
		double m_coreSpeed = 5;
		double m_centerSpeed = 10;

		double m_diskTiltX = 0;
		double m_diskTiltZ = 0;
		double m_coreTiltX = 0;
		double m_coreTiltZ = 0;
		double m_centerTiltX = 0;
		double m_centerTiltZ = 0;


		float m_diskEmissionIntensity = 3.0f;
		float m_coreEmissionIntensity = 2.0f;
		float m_centerEmissionIntensity = 1.0f;
		glm::vec3 m_diskColor = glm::vec3(0, 0, 1);
		glm::vec3 m_coreColor = glm::vec3(1, 1, 0);
		glm::vec3 m_centerColor = glm::vec3(1, 1, 1);

		double m_twist = 360;
		glm::dvec3 m_centerOffset = glm::dvec3(0);
		glm::dvec3 m_centerPosition = glm::dvec3(0);
		
		void Apply(const bool& forceUpdateAllStars = false, const bool& onlyUpdateColors = false);
		
		void SetAb()
		{
			m_diskA = m_diskDiameter * m_diskEccentricity;
			m_diskB = m_diskDiameter * (1 - m_diskEccentricity);
			m_centerA = m_centerDiameter * m_centerEccentricity;
			m_centerB = m_centerDiameter * (1 - m_centerEccentricity);
			m_coreDiameter = m_centerDiameter / 2 + m_centerDiameter / 2 +
				(m_diskA + m_diskB - m_centerDiameter / 2 - m_centerDiameter / 2)
				* m_coreProportion;
			m_coreA = m_coreDiameter * m_coreEccentricity;
			m_coreB = m_coreDiameter * (1 - m_coreEccentricity);
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
			orbit.m_tiltY = -m_twist * starOrbitProportion;
			orbit.m_center = m_centerOffset * (1 - starOrbitProportion) + m_centerPosition;
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

		[[nodiscard]] glm::vec3 GetColor(const double& proportion) const
		{
			glm::vec3 color = glm::vec3();
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
			return color;
		}

		[[nodiscard]] float GetIntensity(const double& proportion) const
		{
			float intensity = 1.0f;
			if (proportion > m_coreProportion)
			{
				//If the wave is outside the disk;
				const double actualProportion = (proportion - m_coreProportion) / (1 - m_coreProportion);
				intensity = m_coreEmissionIntensity * (1 - static_cast<float>(actualProportion)) + m_diskEmissionIntensity * static_cast<float>(actualProportion);
			}
			else
			{
				const double actualProportion = proportion / m_coreProportion;
				intensity = m_coreEmissionIntensity * static_cast<float>(actualProportion) + m_centerEmissionIntensity * (1 - static_cast<float>(actualProportion));
			}
			return intensity;
		}
	};

	class StarClusterSystem :
		public SystemBase
	{
		Entity m_rendererFront;
		Entity m_rendererBack;
		EntityQuery m_starQuery;
		EntityArchetype m_starArchetype;
		std::vector<StarClusterPattern> m_starClusterPatterns;
		bool m_useFront = true;
#pragma region Rendering
		std::vector<glm::mat4> m_frontMatrices;
		std::vector<glm::mat4> m_backMatrices;
		std::vector<glm::vec4> m_frontColors;
		std::vector<glm::vec4> m_backColors;

		GLVBO m_renderTransformBuffer;
		GLVBO m_renderColorBuffer;
		std::unique_ptr<GLProgram> m_starRenderProgram;
#pragma endregion

		bool m_useSimd = false;
		
		int m_counter = 0;
		
		float m_applyPositionTimer = 0;
		float m_copyPositionTimer = 0;
		float m_calcPositionTimer = 0;
		float m_calcPositionResult = 0;
		float m_speed = 0.0f;
		float m_size = 0.1f;
		float m_galaxyTime = 0.0;
		std::future<void> m_currentStatus;
		bool m_firstTime = true;
		void OnGui();
	public:
		void RenderStars(std::unique_ptr<CameraComponent>& camera, const glm::vec3& cameraPosition, const glm::quat& cameraRotation);
		void CalculateStarPositionAsync();
		void CalculateStarPositionSync();
		void ApplyPosition();
		void CopyPosition(const bool& reverse = false);
		void LateUpdate() override;
		void OnCreate() override;
		void Update() override;
		void PushStars(StarClusterPattern& pattern, const size_t& amount = 10000);
		void RandomlyRemoveStars(const size_t& amount = 10000);
		void ClearAllStars();
		void FixedUpdate() override;
		void OnStartRunning() override;
	};
}

