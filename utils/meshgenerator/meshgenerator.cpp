
#include "utils/meshgenerator/meshgenerator.hpp"

void CubeTetrahedra(
    const uint32_t N,
    const float L,
    fvec3** const vertdata,
    uint32_t& vertsize,
    uint32_t** const ilistdata,
    uint32_t& ilistsize,
    uint32_t** const facelistdata,
    uint32_t& facelistsize,
    uint32_t** const edgelistdata,
    uint32_t& edgelistsize,
    const fvec3& bias)
{

	vertsize  = N * N * N;
	*vertdata = new fvec3[vertsize];

	ilistsize  = 4 * 6 * (N - 1) * (N - 1) * (N - 1);
	*ilistdata = new uint32_t[ilistsize];

	facelistsize  = 6 * 6 * (N - 1) * (N - 1);
	*facelistdata = new uint32_t[facelistsize];

	//edgelistsize  = 6 * (6 * (N - 1) + 4) * (N - 1);
	edgelistsize  = 6 * 6 * (N - 1) * (N - 1);
	*edgelistdata = new uint32_t[edgelistsize];

	for (uint32_t y = 0; y < N; y++) {
		float vy = -0.5 * L + L * (y / float(N - 1));
		for (uint32_t z = 0; z < N; z++) {
			float vz = -0.5 * L + L * (z / float(N - 1));
			for (uint32_t x = 0; x < N; x++) {
				float vx			   = -0.5 * L + L * (x / float(N - 1));
				(*vertdata)[N * N * y + N * z + x] = fvec3(vx, vy, vz) + bias;
			}
		}
	}

	for (uint32_t y = 0; y < N - 1; y++) {
		for (uint32_t z = 0; z < N - 1; z++) {
			for (uint32_t x = 0; x < N - 1; x++) {
				uint32_t Ind1 = N * N * y + N * z + x;
				uint32_t Ind0 = Ind1 + 1;
				uint32_t Ind2 = Ind0 + N;
				uint32_t Ind3 = Ind1 + N;

				uint32_t Ind4 = N * N + Ind0;
				uint32_t Ind5 = N * N + Ind1;
				uint32_t Ind6 = N * N + Ind2;
				uint32_t Ind7 = N * N + Ind3;

				uint32_t index				= (N - 1) * (N - 1) * y + (N - 1) * z + x;
				(*ilistdata)[4 * 6 * index + 4 * 0 + 0] = Ind0;
				(*ilistdata)[4 * 6 * index + 4 * 0 + 1] = Ind1;
				(*ilistdata)[4 * 6 * index + 4 * 0 + 2] = Ind2;
				(*ilistdata)[4 * 6 * index + 4 * 0 + 3] = Ind4;
				//TetIndList.emplace_back(Ind1);
				//TetIndList.emplace_back(Ind1);
				//TetIndList.emplace_back(Ind2);
				//TetIndList.emplace_back(Ind4);

				(*ilistdata)[4 * 6 * index + 4 * 1 + 0] = Ind6;
				(*ilistdata)[4 * 6 * index + 4 * 1 + 1] = Ind4;
				(*ilistdata)[4 * 6 * index + 4 * 1 + 2] = Ind2;
				(*ilistdata)[4 * 6 * index + 4 * 1 + 3] = Ind5;
				//TetIndList.emplace_back(Ind6);
				//TetIndList.emplace_back(Ind4);
				//TetIndList.emplace_back(Ind2);
				//TetIndList.emplace_back(Ind5);

				(*ilistdata)[4 * 6 * index + 4 * 2 + 0] = Ind4;
				(*ilistdata)[4 * 6 * index + 4 * 2 + 1] = Ind5;
				(*ilistdata)[4 * 6 * index + 4 * 2 + 2] = Ind1;
				(*ilistdata)[4 * 6 * index + 4 * 2 + 3] = Ind2;
				//TetIndList.emplace_back(Ind4);
				//TetIndList.emplace_back(Ind5);
				//TetIndList.emplace_back(Ind1);
				//TetIndList.emplace_back(Ind2);

				(*ilistdata)[4 * 6 * index + 4 * 3 + 0] = Ind1;
				(*ilistdata)[4 * 6 * index + 4 * 3 + 1] = Ind3;
				(*ilistdata)[4 * 6 * index + 4 * 3 + 2] = Ind2;
				(*ilistdata)[4 * 6 * index + 4 * 3 + 3] = Ind7;
				//TetIndList.emplace_back(Ind1);
				//TetIndList.emplace_back(Ind3);
				//TetIndList.emplace_back(Ind2);
				//TetIndList.emplace_back(Ind7);

				(*ilistdata)[4 * 6 * index + 4 * 4 + 0] = Ind5;
				(*ilistdata)[4 * 6 * index + 4 * 4 + 1] = Ind7;
				(*ilistdata)[4 * 6 * index + 4 * 4 + 2] = Ind1;
				(*ilistdata)[4 * 6 * index + 4 * 4 + 3] = Ind2;
				//TetIndList.emplace_back(Ind5);
				//TetIndList.emplace_back(Ind7);
				//TetIndList.emplace_back(Ind1);
				//TetIndList.emplace_back(Ind2);

				(*ilistdata)[4 * 6 * index + 4 * 5 + 0] = Ind5;
				(*ilistdata)[4 * 6 * index + 4 * 5 + 1] = Ind6;
				(*ilistdata)[4 * 6 * index + 4 * 5 + 2] = Ind7;
				(*ilistdata)[4 * 6 * index + 4 * 5 + 3] = Ind2;
				//TetIndList.emplace_back(Ind5);
				//TetIndList.emplace_back(Ind6);
				//TetIndList.emplace_back(Ind7);
				//TetIndList.emplace_back(Ind2);
			}
		}
	}

	//xy z+
	for (uint32_t x = 0; x < N - 1; x++) {
		for (uint32_t y = 0; y < N - 1; y++) {
			uint32_t I0							       = N * (N - 1) + N * N * y + x;
			uint32_t I1							       = I0 + 1;
			uint32_t I2							       = I0 + N * N;
			uint32_t I3							       = I0 + N * N + 1;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 0 + 6 * ((N - 1) * y + x) + 0] = I0;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 0 + 6 * ((N - 1) * y + x) + 1] = I1;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 0 + 6 * ((N - 1) * y + x) + 2] = I2;

			(*facelistdata)[6 * (N - 1) * (N - 1) * 0 + 6 * ((N - 1) * y + x) + 3] = I2;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 0 + 6 * ((N - 1) * y + x) + 4] = I1;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 0 + 6 * ((N - 1) * y + x) + 5] = I3;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 0 + (6 * (N - 1) + 2) * y + 6 * x + 0] = I0;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 0 + (6 * (N - 1) + 2) * y + 6 * x + 1] = I1;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 0 + (6 * (N - 1) + 2) * y + 6 * x + 2] = I1;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 0 + (6 * (N - 1) + 2) * y + 6 * x + 3] = I2;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 0 + (6 * (N - 1) + 2) * y + 6 * x + 4] = I2;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 0 + (6 * (N - 1) + 2) * y + 6 * x + 5] = I0;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 0 + 6 * ((N - 1) * y + x) + 0] = I0;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 0 + 6 * ((N - 1) * y + x) + 1] = I1;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 0 + 6 * ((N - 1) * y + x) + 2] = I1;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 0 + 6 * ((N - 1) * y + x) + 3] = I2;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 0 + 6 * ((N - 1) * y + x) + 4] = I2;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 0 + 6 * ((N - 1) * y + x) + 5] = I0;
		}
	}
	//xy z-
	for (uint32_t x = 0; x < N - 1; x++) {
		for (uint32_t y = 0; y < N - 1; y++) {
			uint32_t I0							       = N * N * y + x;
			uint32_t I1							       = I0 + 1;
			uint32_t I2							       = I0 + N * N;
			uint32_t I3							       = I0 + N * N + 1;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 1 + 6 * ((N - 1) * y + x) + 0] = I0;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 1 + 6 * ((N - 1) * y + x) + 1] = I3;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 1 + 6 * ((N - 1) * y + x) + 2] = I1;

			(*facelistdata)[6 * (N - 1) * (N - 1) * 1 + 6 * ((N - 1) * y + x) + 3] = I3;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 1 + 6 * ((N - 1) * y + x) + 4] = I0;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 1 + 6 * ((N - 1) * y + x) + 5] = I2;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 1 + (6 * (N - 1) + 2) * y + 6 * x + 0] = I0;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 1 + (6 * (N - 1) + 2) * y + 6 * x + 1] = I1;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 1 + (6 * (N - 1) + 2) * y + 6 * x + 2] = I1;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 1 + (6 * (N - 1) + 2) * y + 6 * x + 3] = I2;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 1 + (6 * (N - 1) + 2) * y + 6 * x + 4] = I2;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 1 + (6 * (N - 1) + 2) * y + 6 * x + 5] = I0;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 1 + 6 * ((N - 1) * y + x) + 0] = I0;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 1 + 6 * ((N - 1) * y + x) + 1] = I1;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 1 + 6 * ((N - 1) * y + x) + 2] = I1;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 1 + 6 * ((N - 1) * y + x) + 3] = I3;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 1 + 6 * ((N - 1) * y + x) + 4] = I3;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 1 + 6 * ((N - 1) * y + x) + 5] = I0;
		}
	}
	//yz x+
	for (uint32_t z = 0; z < N - 1; z++) {
		for (uint32_t y = 0; y < N - 1; y++) {
			uint32_t I0							       = N * N * y + N * z + N - 1;
			uint32_t I1							       = I0 + N;
			uint32_t I2							       = I0 + N * N;
			uint32_t I3							       = I0 + N * N + N;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 2 + 6 * ((N - 1) * z + y) + 0] = I0;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 2 + 6 * ((N - 1) * z + y) + 1] = I2;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 2 + 6 * ((N - 1) * z + y) + 2] = I1;

			(*facelistdata)[6 * (N - 1) * (N - 1) * 2 + 6 * ((N - 1) * z + y) + 3] = I2;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 2 + 6 * ((N - 1) * z + y) + 4] = I3;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 2 + 6 * ((N - 1) * z + y) + 5] = I1;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 2 + (6 * (N - 1) + 2) * z + 6 * y + 0] = I0;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 2 + (6 * (N - 1) + 2) * z + 6 * y + 1] = I1;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 2 + (6 * (N - 1) + 2) * z + 6 * y + 2] = I1;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 2 + (6 * (N - 1) + 2) * z + 6 * y + 3] = I2;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 2 + (6 * (N - 1) + 2) * z + 6 * y + 4] = I2;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 2 + (6 * (N - 1) + 2) * z + 6 * y + 5] = I0;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 2 + 6 * ((N - 1) * z + y) + 0] = I0;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 2 + 6 * ((N - 1) * z + y) + 1] = I1;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 2 + 6 * ((N - 1) * z + y) + 2] = I1;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 2 + 6 * ((N - 1) * z + y) + 3] = I2;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 2 + 6 * ((N - 1) * z + y) + 4] = I2;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 2 + 6 * ((N - 1) * z + y) + 5] = I0;
		}
	}
	//yz x-
	for (uint32_t z = 0; z < N - 1; z++) {
		for (uint32_t y = 0; y < N - 1; y++) {
			uint32_t I0							       = N * N * y + N * z;
			uint32_t I1							       = I0 + N;
			uint32_t I2							       = I0 + N * N;
			uint32_t I3							       = I0 + N * N + N;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 3 + 6 * ((N - 1) * z + y) + 0] = I0;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 3 + 6 * ((N - 1) * z + y) + 1] = I1;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 3 + 6 * ((N - 1) * z + y) + 2] = I3;

			(*facelistdata)[6 * (N - 1) * (N - 1) * 3 + 6 * ((N - 1) * z + y) + 3] = I3;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 3 + 6 * ((N - 1) * z + y) + 4] = I2;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 3 + 6 * ((N - 1) * z + y) + 5] = I0;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 3 + (6 * (N - 1) + 2) * z + 6 * y + 0] = I0;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 3 + (6 * (N - 1) + 2) * z + 6 * y + 1] = I1;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 3 + (6 * (N - 1) + 2) * z + 6 * y + 2] = I1;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 3 + (6 * (N - 1) + 2) * z + 6 * y + 3] = I2;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 3 + (6 * (N - 1) + 2) * z + 6 * y + 4] = I2;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 3 + (6 * (N - 1) + 2) * z + 6 * y + 5] = I0;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 3 + 6 * ((N - 1) * z + y) + 0] = I0;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 3 + 6 * ((N - 1) * z + y) + 1] = I1;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 3 + 6 * ((N - 1) * z + y) + 2] = I1;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 3 + 6 * ((N - 1) * z + y) + 3] = I3;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 3 + 6 * ((N - 1) * z + y) + 4] = I3;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 3 + 6 * ((N - 1) * z + y) + 5] = I0;
		}
	}
	//zx y+
	for (uint32_t z = 0; z < N - 1; z++) {
		for (uint32_t x = 0; x < N - 1; x++) {
			uint32_t I0							       = N * N * (N - 1) + N * z + x;
			uint32_t I1							       = I0 + N;
			uint32_t I2							       = I0 + 1;
			uint32_t I3							       = I0 + 1 + N;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 4 + 6 * ((N - 1) * x + z) + 0] = I0;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 4 + 6 * ((N - 1) * x + z) + 1] = I1;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 4 + 6 * ((N - 1) * x + z) + 2] = I3;

			(*facelistdata)[6 * (N - 1) * (N - 1) * 4 + 6 * ((N - 1) * x + z) + 3] = I3;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 4 + 6 * ((N - 1) * x + z) + 4] = I2;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 4 + 6 * ((N - 1) * x + z) + 5] = I0;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 4 + (6 * (N - 1) + 2) * x + 6 * z + 0] = I0;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 4 + (6 * (N - 1) + 2) * x + 6 * z + 1] = I1;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 4 + (6 * (N - 1) + 2) * x + 6 * z + 2] = I1;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 4 + (6 * (N - 1) + 2) * x + 6 * z + 3] = I2;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 4 + (6 * (N - 1) + 2) * x + 6 * z + 4] = I2;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 4 + (6 * (N - 1) + 2) * x + 6 * z + 5] = I0;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 4 + 6 * ((N - 1) * x + z) + 0] = I0;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 4 + 6 * ((N - 1) * x + z) + 1] = I1;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 4 + 6 * ((N - 1) * x + z) + 2] = I1;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 4 + 6 * ((N - 1) * x + z) + 3] = I3;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 4 + 6 * ((N - 1) * x + z) + 4] = I3;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 4 + 6 * ((N - 1) * x + z) + 5] = I0;
		}
	}
	//zx y-
	for (uint32_t z = 0; z < N - 1; z++) {
		for (uint32_t x = 0; x < N - 1; x++) {
			uint32_t I0							       = N * z + x;
			uint32_t I1							       = I0 + N;
			uint32_t I2							       = I0 + 1;
			uint32_t I3							       = I0 + 1 + N;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 5 + 6 * ((N - 1) * x + z) + 0] = I0;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 5 + 6 * ((N - 1) * x + z) + 1] = I3;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 5 + 6 * ((N - 1) * x + z) + 2] = I1;

			(*facelistdata)[6 * (N - 1) * (N - 1) * 5 + 6 * ((N - 1) * x + z) + 3] = I3;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 5 + 6 * ((N - 1) * x + z) + 4] = I0;
			(*facelistdata)[6 * (N - 1) * (N - 1) * 5 + 6 * ((N - 1) * x + z) + 5] = I2;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 5 + (6 * (N - 1) + 2) * x + 6 * z + 0] = I0;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 5 + (6 * (N - 1) + 2) * x + 6 * z + 1] = I1;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 5 + (6 * (N - 1) + 2) * x + 6 * z + 2] = I1;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 5 + (6 * (N - 1) + 2) * x + 6 * z + 3] = I2;

			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 5 + (6 * (N - 1) + 2) * x + 6 * z + 4] = I2;
			//(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 5 + (6 * (N - 1) + 2) * x + 6 * z + 5] = I0;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 5 + 6 * ((N - 1) * x + z) + 0] = I0;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 5 + 6 * ((N - 1) * x + z) + 1] = I1;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 5 + 6 * ((N - 1) * x + z) + 2] = I1;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 5 + 6 * ((N - 1) * x + z) + 3] = I3;

			(*edgelistdata)[6 * (N - 1) * (N - 1) * 5 + 6 * ((N - 1) * x + z) + 4] = I3;
			(*edgelistdata)[6 * (N - 1) * (N - 1) * 5 + 6 * ((N - 1) * x + z) + 5] = I0;
		}
	}

	/*
	//xy z+
	for (uint32_t y = 0; y < N - 1; y++) {
		for (uint32_t x = 0; x < N - 1; x++) {
			(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 0 + (6 * (N - 1) + 2) * y + 6 * x + 0] = Ind0;
			(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 0 + (6 * (N - 1) + 2) * y + 6 * x + 1] = Ind0 + 1;

			(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 0 + (6 * (N - 1) + 2) * y + 6 * x + 2] = Ind0 + 1;
			(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 0 + (6 * (N - 1) + 2) * y + 6 * x + 3] = Ind0 + 0 + N;

			(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 0 + (6 * (N - 1) + 2) * y + 6 * x + 4] = Ind0 + 0 + N;
			(*edgelistdata)[(6 * (N - 1) + 4) * (N - 1) * 0 + (6 * (N - 1) + 2) * y + 6 * x + 5] = Ind0;
		}
	}
	*/
}