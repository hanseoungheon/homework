#include "Node.h"

Node::Node(const Bounds& bounds, int depth)
	:bounds(bounds), depth(depth)
{

}

Node::~Node()
{
	//노드를 모두 제거하는 함수 호촐.
	Clear();
}

void Node::Insert(Node* node)
{
	//완전히 겹치는지 확인하는 함수 구현.
	NodeIndex result = TestRegion(node->GetBounds());

	if (result == NodeIndex::Straddling)
	{
		points.emplace_back(node);
	}

	else if (result != NodeIndex::OutOfArea) //완전 포합되지는 안되 영역 밖에 있지는 말아야함.
	{
		//분할
		if (Subdivide())
		{
			//어느 영역에 포함됐는지 확인 후 하위 노드에 추가.
			if (result == NodeIndex::TopLeft)
			{
				topLeft->Insert(node);
			}
			else if (result == NodeIndex::TopRight)
			{
				topRight->Insert(node);
			}
			else if (result == NodeIndex::BottomLeft)
			{
				bottomLeft->Insert(node);
			}
			else if (result == NodeIndex::BottomRight)
			{
				bottomRight->Insert(node);
			}
		}
		else //그런데 더 이상 나눌 수 없을때=> 즉 깊이한계에 도달함 
		{
			points.emplace_back(node);
		}
	}
}

void Node::Query(const Bounds& queryBounds, 
	std::vector<Node*>& possibleNodes)
{
	//현재 노드 추가.
	possibleNodes.emplace_back(this);

	//하위 노드 검색(영역이 분할된 경우).

	//분할이 안됐으면 리턴시키기.
	if (IsDivided() == false)
	{
		return;
	}

	//됐으면 실행,

	std::vector<NodeIndex> quads = GetQuads(queryBounds);

	//루프로 처리.
	for (NodeIndex& index : quads)
	{
		if (index == NodeIndex::TopLeft)
		{
			topLeft->Query(queryBounds, possibleNodes);
		}
		else if (index == NodeIndex::TopRight)
		{
			topRight->Query(queryBounds, possibleNodes);
		}
		else if (index == NodeIndex::BottomLeft)
		{
			bottomLeft->Query(queryBounds, possibleNodes);
		}
		else if (index == NodeIndex::BottomRight)
		{
			bottomRight->Query(queryBounds, possibleNodes);
		}
	}
}

void Node::Clear()
{
	//현재 노드 정리.
	for (Node* node : points)
	{
		SafeDelete(node);
	}
	points.clear();
	//분할된 경우 자손 정리.

	if (IsDivided())
	{
		//자손 정리.
		topLeft->Clear();
		topRight->Clear();
		bottomLeft->Clear();
		bottomRight->Clear();

		//자손 정리후 자신 제거.
		SafeDelete(topLeft);
		SafeDelete(topRight);
		SafeDelete(bottomLeft);
		SafeDelete(bottomRight);
	}
}

NodeIndex Node::TestRegion(const Bounds& bounds)
{
	//한개만 겹쳐있으면 완전히 포함된것 아니면 그냥 여러 사분면에 걸쳐있는것.
	std::vector<NodeIndex> quads = GetQuads(bounds);

	//겹치는 곳이 없으면 아예 영역밖에 있음.(배열의 갯수가 0)
	if (quads.size() == 0)
	{
		return NodeIndex::OutOfArea;
	}

	//하나만 있는 경우(완전 포함상태), 해당 4분면 반환시키기.
	if (quads.size() == 1)
	{
		return quads[0];
	}


	//여러 영역과 겹치는 경우(배열의 요소 갯수가 2개 이상) 겹침반환시키기.
	return NodeIndex::Straddling;
}

std::vector<NodeIndex> Node::GetQuads(const Bounds& bounds)
{
	std::vector<NodeIndex> quads;

	//영역 계산에 필요한 변수.
	float x = this->bounds.GetX();
	float y = this->bounds.GetY();

	float halfWidth = this->bounds.GetWidth() / 2.0f;
	float halfHeight = this->bounds.GetHeight() / 2.0f;

	float centerX = x + halfWidth;
	float centerY = y + halfHeight;

	//왼쪽 영역과 겹쳤는지 확인.
	bool left = (bounds.GetX() < centerX) && (bounds.MaxX() >= x);
	//오른쪽 영역과 겹쳤는지 확인.
	bool right = (bounds.MaxX() >= centerX) && (bounds.GetX() < this->bounds.MaxX());
	//위쪽 영역과 겹쳤는지 확인.
	bool top = (bounds.GetY() < centerY) && (bounds.MaxY() >= y);
	//아래쪽 영역과 겹쳤는지 확인.
	bool bottom = (bounds.MaxY() >= centerY) && (bounds.GetY() < this->bounds.MaxY());

	if (top && left)
	{
		quads.emplace_back(NodeIndex::TopLeft);
	}
	if (top && right)
	{
		quads.emplace_back(NodeIndex::TopRight);
	}
	if (bottom && left)
	{
		quads.emplace_back(NodeIndex::BottomLeft);
	}
	if (bottom && right)
	{
		quads.emplace_back(NodeIndex::BottomRight);
	}

	return quads;
}

bool Node::Subdivide()
{
	//최대 깊이에 도달했는지 확인.
	//도달했다면 더 이상 분할 안함.
	if (depth == QuadTree::maxDepth) //최대로 도달할 수 있는 깊이 이건 사용자정의임.
	{
		return false;
	}

	//아직 분할 안됐으면 분할.
	if (!IsDivided())
	{
		//영역 나누기.
		//영역 계산을 위한 변수.
		float x = bounds.GetX();
		float y = bounds.GetY();
		float halfWidth = bounds.GetWidth() / 2.0f;
		float halfHeight = bounds.GetHeight() / 2.0f;

		topLeft = new Node(Bounds(x, y, halfWidth, halfHeight), depth + 1);
		topRight = new Node(Bounds(x + halfWidth, y, halfWidth, halfHeight), depth + 1);
		bottomLeft = new Node(Bounds(x, y + halfHeight, halfWidth, halfHeight), depth + 1);
		bottomRight = new Node(Bounds(x + halfWidth, y + halfHeight, halfWidth, halfHeight), 
			depth + 1);
	}


	return true;
}

bool Node::IsDivided()
{
	//자손 노드중 하나가 null이 아니면 분할이 완료된 상태.
	//자손노드는 모두 null이거나(분할 안됨) 모두 생선된 상태(분할 됨) 둘 중 하나임.
	return topLeft != nullptr;
}

