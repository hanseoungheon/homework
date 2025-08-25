#include "Node.h"

Node::Node(const Bounds& bounds, int depth)
	:bounds(bounds), depth(depth)
{

}

Node::~Node()
{
	//��带 ��� �����ϴ� �Լ� ȣ��.
	Clear();
}

void Node::Insert(Node* node)
{
	//������ ��ġ���� Ȯ���ϴ� �Լ� ����.
	NodeIndex result = TestRegion(node->GetBounds());

	if (result == NodeIndex::Straddling)
	{
		points.emplace_back(node);
	}

	else if (result != NodeIndex::OutOfArea) //���� ���յ����� �ȵ� ���� �ۿ� ������ ���ƾ���.
	{
		//����
		if (Subdivide())
		{
			//��� ������ ���Եƴ��� Ȯ�� �� ���� ��忡 �߰�.
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
		else //�׷��� �� �̻� ���� �� ������=> �� �����Ѱ迡 ������ 
		{
			points.emplace_back(node);
		}
	}
}

void Node::Query(const Bounds& queryBounds, 
	std::vector<Node*>& possibleNodes)
{
	//���� ��� �߰�.
	possibleNodes.emplace_back(this);

	//���� ��� �˻�(������ ���ҵ� ���).

	//������ �ȵ����� ���Ͻ�Ű��.
	if (IsDivided() == false)
	{
		return;
	}

	//������ ����,

	std::vector<NodeIndex> quads = GetQuads(queryBounds);

	//������ ó��.
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
	//���� ��� ����.
	for (Node* node : points)
	{
		SafeDelete(node);
	}
	points.clear();
	//���ҵ� ��� �ڼ� ����.

	if (IsDivided())
	{
		//�ڼ� ����.
		topLeft->Clear();
		topRight->Clear();
		bottomLeft->Clear();
		bottomRight->Clear();

		//�ڼ� ������ �ڽ� ����.
		SafeDelete(topLeft);
		SafeDelete(topRight);
		SafeDelete(bottomLeft);
		SafeDelete(bottomRight);
	}
}

NodeIndex Node::TestRegion(const Bounds& bounds)
{
	//�Ѱ��� ���������� ������ ���ԵȰ� �ƴϸ� �׳� ���� ��и鿡 �����ִ°�.
	std::vector<NodeIndex> quads = GetQuads(bounds);

	//��ġ�� ���� ������ �ƿ� �����ۿ� ����.(�迭�� ������ 0)
	if (quads.size() == 0)
	{
		return NodeIndex::OutOfArea;
	}

	//�ϳ��� �ִ� ���(���� ���Ի���), �ش� 4�и� ��ȯ��Ű��.
	if (quads.size() == 1)
	{
		return quads[0];
	}


	//���� ������ ��ġ�� ���(�迭�� ��� ������ 2�� �̻�) ��ħ��ȯ��Ű��.
	return NodeIndex::Straddling;
}

std::vector<NodeIndex> Node::GetQuads(const Bounds& bounds)
{
	std::vector<NodeIndex> quads;

	//���� ��꿡 �ʿ��� ����.
	float x = this->bounds.GetX();
	float y = this->bounds.GetY();

	float halfWidth = this->bounds.GetWidth() / 2.0f;
	float halfHeight = this->bounds.GetHeight() / 2.0f;

	float centerX = x + halfWidth;
	float centerY = y + halfHeight;

	//���� ������ ���ƴ��� Ȯ��.
	bool left = (bounds.GetX() < centerX) && (bounds.MaxX() >= x);
	//������ ������ ���ƴ��� Ȯ��.
	bool right = (bounds.MaxX() >= centerX) && (bounds.GetX() < this->bounds.MaxX());
	//���� ������ ���ƴ��� Ȯ��.
	bool top = (bounds.GetY() < centerY) && (bounds.MaxY() >= y);
	//�Ʒ��� ������ ���ƴ��� Ȯ��.
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
	//�ִ� ���̿� �����ߴ��� Ȯ��.
	//�����ߴٸ� �� �̻� ���� ����.
	if (depth == QuadTree::maxDepth) //�ִ�� ������ �� �ִ� ���� �̰� �����������.
	{
		return false;
	}

	//���� ���� �ȵ����� ����.
	if (!IsDivided())
	{
		//���� ������.
		//���� ����� ���� ����.
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
	//�ڼ� ����� �ϳ��� null�� �ƴϸ� ������ �Ϸ�� ����.
	//�ڼճ��� ��� null�̰ų�(���� �ȵ�) ��� ������ ����(���� ��) �� �� �ϳ���.
	return topLeft != nullptr;
}

