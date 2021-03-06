#include <vector>
#include <cmath>
#include <iostream>

#include "utils/collision/DeformableBvh2D.hpp"

#include "utils/collision/primitive2d.hpp"
#include "utils/collision/basic3d.hpp"

constexpr float Epsilon = 0.001;

DeformableBvh2DNode::DeformableBvh2DNode(
    const DeformableBvh2D& root,
    const uint32_t* const elementdata,
    const uint32_t elementsize)
    : Root(root)
{
	if (elementsize == 3)
		this->Type = 1;
	else
		this->Type = 0;

	float maxX, minX, maxY, minY;
	maxX = root.vertdata[elementdata[0]].x;
	minX = root.vertdata[elementdata[0]].x;
	maxY = root.vertdata[elementdata[0]].y;
	minY = root.vertdata[elementdata[0]].y;

	for (uint32_t i = 0; i < elementsize; i++) {
		const fvec2& v = root.vertdata[elementdata[i]];

		if (v.x < minX)
			minX = v.x;
		if (maxX < v.x)
			maxX = v.x;
		if (v.y < minY)
			minY = v.y;
		if (maxY < v.y)
			maxY = v.y;
	}

	this->center  = fvec2((maxX + minX) / 2.0, (maxY + minY) / 2.0);
	this->Lengthx = std::max(maxX - minX, Epsilon);
	this->Lengthy = std::max(maxY - minY, Epsilon);

	if (this->Type == 1) {
		this->index0 = elementdata[0];
		this->index1 = elementdata[1];
		this->index2 = elementdata[2];

		this->RightChild = nullptr;
		this->LeftChild	 = nullptr;

	} else {
		std::vector<float> OrderedCoord;
		uint32_t TriSize = elementsize / 3;

		if (elementsize == 6) {
			this->RightChild = new DeformableBvh2DNode(root, elementdata, 3);
			this->LeftChild	 = new DeformableBvh2DNode(root, elementdata + 3, 3);
			return;
		} else {
			std::vector<uint32_t> RightElements;
			std::vector<uint32_t> LeftElements;

			if (this->Lengthx > this->Lengthy) {

				//x座標で分離
				for (uint32_t i = 0; i < TriSize; i++) {
					float cm = root.vertdata[elementdata[3 * i + 0]].x + root.vertdata[elementdata[3 * i + 1]].x + root.vertdata[elementdata[3 * i + 2]].x;
					OrderedCoord.insert(std::lower_bound(OrderedCoord.begin(), OrderedCoord.end(), cm), cm);
				}

				float SepPlane = OrderedCoord[TriSize / 2];

				for (uint32_t i = 0; i < TriSize; i++) {
					const fvec2& v0 = root.vertdata[elementdata[3 * i + 0]];
					const fvec2& v1 = root.vertdata[elementdata[3 * i + 1]];
					const fvec2& v2 = root.vertdata[elementdata[3 * i + 2]];

					float cm = v0.x + v1.x + v2.x;

					if (cm < SepPlane) {
						RightElements.emplace_back(elementdata[3 * i + 0]);
						RightElements.emplace_back(elementdata[3 * i + 1]);
						RightElements.emplace_back(elementdata[3 * i + 2]);
					} else {
						LeftElements.emplace_back(elementdata[3 * i + 0]);
						LeftElements.emplace_back(elementdata[3 * i + 1]);
						LeftElements.emplace_back(elementdata[3 * i + 2]);
					}
				}
			} else {

				//y座標で分離
				for (uint32_t i = 0; i < TriSize; i++) {
					float cm = root.vertdata[elementdata[3 * i + 0]].y + root.vertdata[elementdata[3 * i + 1]].y + root.vertdata[elementdata[3 * i + 2]].y;
					OrderedCoord.insert(std::lower_bound(OrderedCoord.begin(), OrderedCoord.end(), cm), cm);
				}

				float SepPlane = OrderedCoord[TriSize / 2];

				for (uint32_t i = 0; i < TriSize; i++) {
					const fvec2& v0 = root.vertdata[elementdata[3 * i + 0]];
					const fvec2& v1 = root.vertdata[elementdata[3 * i + 1]];
					const fvec2& v2 = root.vertdata[elementdata[3 * i + 2]];

					float cm = v0.y + v1.y + v2.y;

					if (cm < SepPlane) {
						RightElements.emplace_back(elementdata[3 * i + 0]);
						RightElements.emplace_back(elementdata[3 * i + 1]);
						RightElements.emplace_back(elementdata[3 * i + 2]);
					} else {
						LeftElements.emplace_back(elementdata[3 * i + 0]);
						LeftElements.emplace_back(elementdata[3 * i + 1]);
						LeftElements.emplace_back(elementdata[3 * i + 2]);
					}
				}
			}

			if (RightElements.size() == 0) {
				RightElements.emplace_back(LeftElements[LeftElements.size() - 3]);
				RightElements.emplace_back(LeftElements[LeftElements.size() - 2]);
				RightElements.emplace_back(LeftElements[LeftElements.size() - 1]);
				LeftElements.pop_back();
				LeftElements.pop_back();
				LeftElements.pop_back();
			}
			if (LeftElements.size() == 0) {
				LeftElements.emplace_back(RightElements[RightElements.size() - 3]);
				LeftElements.emplace_back(RightElements[RightElements.size() - 2]);
				LeftElements.emplace_back(RightElements[RightElements.size() - 1]);
				RightElements.pop_back();
				RightElements.pop_back();
				RightElements.pop_back();
			}

			this->RightChild = new DeformableBvh2DNode(root, RightElements.data(), RightElements.size());
			this->LeftChild	 = new DeformableBvh2DNode(root, LeftElements.data(), LeftElements.size());
		}
	}
}

void DeformableBvh2DNode::UpdateBvhNode()
{

	if (this->Type == 1) {
		const fvec2& v0 = this->Root.vertdata[this->index0];
		const fvec2& v1 = this->Root.vertdata[this->index1];
		const fvec2& v2 = this->Root.vertdata[this->index2];

		float maxx = std::max(std::max(v0.x, v1.x), v2.x);
		float minx = std::min(std::min(v0.x, v1.x), v2.x);
		float maxy = std::max(std::max(v0.y, v1.y), v2.y);
		float miny = std::min(std::min(v0.y, v1.y), v2.y);

		this->center  = fvec2((maxx + minx) / 2.0, (maxy + miny) / 2.0);
		this->Lengthx = std::max(maxx - minx, Epsilon);
		this->Lengthy = std::max(maxy - miny, Epsilon);
	} else {
		RightChild->UpdateBvhNode();
		LeftChild->UpdateBvhNode();

		float maxx, minx, maxy, miny;
		if (RightChild->center.x + (RightChild->Lengthx) / 2.0 > LeftChild->center.x + (LeftChild->Lengthx) / 2.0)
			maxx = RightChild->center.x + (RightChild->Lengthx) / 2.0;
		else
			maxx = LeftChild->center.x + (LeftChild->Lengthx) / 2.0;

		if (RightChild->center.x - (RightChild->Lengthx) / 2.0 < LeftChild->center.x - (LeftChild->Lengthx) / 2.0)
			minx = RightChild->center.x - (RightChild->Lengthx) / 2.0;
		else
			minx = LeftChild->center.x - (LeftChild->Lengthx) / 2.0;

		if (RightChild->center.y + (RightChild->Lengthy) / 2.0 > LeftChild->center.y + (LeftChild->Lengthy) / 2.0)
			maxy = RightChild->center.y + (RightChild->Lengthy) / 2.0;
		else
			maxy = LeftChild->center.y + (LeftChild->Lengthy) / 2.0;

		if (RightChild->center.y - (RightChild->Lengthy) / 2.0 < LeftChild->center.y - (LeftChild->Lengthy) / 2.0)
			miny = RightChild->center.y - (RightChild->Lengthy) / 2.0;
		else
			miny = LeftChild->center.y - (LeftChild->Lengthy) / 2.0;

		this->center  = fvec2((maxx + minx) / 2.0, (maxy + miny) / 2.0);
		this->Lengthx = std::max(maxx - minx, Epsilon);
		this->Lengthy = std::max(maxy - miny, Epsilon);
	}
}

bool Is_CollideNodeAABB(const DeformableBvh2DNode* const RNode, const DeformableBvh2DNode* const LNode)
{
	//sat

	if (RNode->center.x + RNode->Lengthx / 2.0 < LNode->center.x - LNode->Lengthx / 2.0)
		return false;
	if (RNode->center.x - RNode->Lengthx / 2.0 > LNode->center.x + LNode->Lengthx / 2.0)
		return false;

	if (RNode->center.y + RNode->Lengthy / 2.0 < LNode->center.y - LNode->Lengthy / 2.0)
		return false;
	if (RNode->center.y - RNode->Lengthy / 2.0 > LNode->center.y + LNode->Lengthy / 2.0)
		return false;

	return true;
}

void DetectCollisionNode(std::vector<ContactFeature>& ContactList, const DeformableBvh2DNode* const RNode, const DeformableBvh2DNode* const LNode)
{
	//RNodeとLNodeは別のオブジェクトであることが保証される
	//RNodeとLNodeはInnerでもLeafでもありえる

	if (RNode->Type == 0 && LNode->Type == 0) {

		//std::cout << "00" << std::endl;

		//RNode内部で起こる衝突
		DetectCollisionNode(ContactList, RNode->RightChild, RNode->LeftChild);
		DetectCollisionNode(ContactList, LNode->RightChild, LNode->LeftChild);

		if (Is_CollideNodeAABB(RNode, LNode)) {
			DetectCollisionNode(ContactList, RNode->RightChild, LNode->LeftChild);
			DetectCollisionNode(ContactList, RNode->RightChild, LNode->RightChild);
			DetectCollisionNode(ContactList, RNode->LeftChild, LNode->LeftChild);
			DetectCollisionNode(ContactList, RNode->LeftChild, LNode->RightChild);
		}
	} else if (RNode->Type == 0 && LNode->Type == 1) {
		//std::cout << "01" << std::endl;
		DetectCollisionNode(ContactList, RNode->RightChild, RNode->LeftChild);

		if (Is_CollideNodeAABB(RNode, LNode)) {
			DetectCollisionNode(ContactList, RNode->RightChild, LNode);
			DetectCollisionNode(ContactList, RNode->LeftChild, LNode);
		}
	} else if (RNode->Type == 1 && LNode->Type == 0) {
		//std::cout << "10" << std::endl;
		DetectCollisionNode(ContactList, LNode->RightChild, LNode->LeftChild);

		if (Is_CollideNodeAABB(RNode, LNode)) {
			DetectCollisionNode(ContactList, RNode, LNode->LeftChild);
			DetectCollisionNode(ContactList, RNode, LNode->RightChild);
		}
	} else if (RNode->Type == 1 && LNode->Type == 1) {
		if (Is_CollideNodeAABB(RNode, LNode)) {

			//隣接する要素同士の場合を除外
			//RNodeとLNodeが同一のrootを持つことを前提にしている
			//異なるrootに属するならそもそもこの作業は必要ない

			if (RNode->index0 == LNode->index0 || RNode->index0 == LNode->index1 || RNode->index0 == LNode->index2 || RNode->index1 == LNode->index0 || RNode->index1 == LNode->index1 || RNode->index1 == LNode->index2 || RNode->index2 == LNode->index0 || RNode->index2 == LNode->index1 || RNode->index2 == LNode->index2)
				return;

			if (Is_CollideTriangleTriangle(
				RNode->Root.vertdata[RNode->index0],
				RNode->Root.vertdata[RNode->index1],
				RNode->Root.vertdata[RNode->index2],
				LNode->Root.vertdata[LNode->index0],
				LNode->Root.vertdata[LNode->index1],
				LNode->Root.vertdata[LNode->index2]))
				ContactList.emplace_back(
				    RNode->index0,
				    RNode->index1,
				    RNode->index2,
				    LNode->index0,
				    LNode->index1,
				    LNode->index2);
		}
	}
}

//////////////////////////////////////////

DeformableBvh2D::DeformableBvh2D(
    const fvec2* const vertdata,
    const uint32_t vertsize,
    const uint32_t* const elementdata,
    const uint32_t elementsize,
    const uint32_t* const VtoElist,
    const uint32_t* const VtoEind)
    : vertdata(vertdata)
    , vertsize(vertsize)
    , elementdata(elementdata)
    , elementsize(elementsize)
    , VtoElist(VtoElist)
    , VtoEind(VtoEind)
{
	RootNode = new DeformableBvh2DNode((*this), elementdata, elementsize);
}

void DeformableBvh2D::UpdateBvh()
{
	RootNode->UpdateBvhNode();
}

void DeformableBvh2D::DetectSelfCollision(std::vector<ContactFeature>& ContactList)
{
	DetectCollisionNode(ContactList, RootNode->RightChild, RootNode->LeftChild);
}
